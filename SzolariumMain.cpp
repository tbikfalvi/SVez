//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <vector.h>
#include <stdio.h>

#include "HardwareKezeles.h"
#include "AdatBeolvasas.h"
#include "BerletEladas.h"
#include "BerletHasznalat.h"
#include "TermekEladas.h"
#include "Fizetes.h"
#include "DialogInput.h"
#include "TermekListaEladas.h"
#include "PasswordCheck.h"
#include "SzolariumMain.h"
#include "Language.h"
#include "ExtendedViewer.h"
#include "BerletPin.h"
#include "RendszerAdmin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormMain *FormMain;

//---------------------------------------------------------------------------
//
//
/****************************************************************************
*
* FO ABLAKKAL KAPCSOLATOS ALAPVETO, ALTALANOS FUGGVENYEK
*
****************************************************************************/

int convertCurrency( double p_dCurrency )
{
   return (int)(p_dCurrency * 100);
}

int convertCurrencyString( char *sValue )
{
   double fValue = atof( sValue );
   return (int)(fValue * 100);
}

AnsiString convertToCurrencyString( int p_nValue )
{
   int nEgesz = p_nValue / 100;
   int nMaradek = p_nValue % 100;

   AnsiString sRet = AnsiString( nEgesz ) + AnsiString( "." ) + AnsiString( nMaradek );

   return sRet;
}

//---------------------------------------------------------------------------
// Fõ ablak létrehozásakor lefutó függvény
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
   // Alap beállítások
   bErrorDuringBoot = false;

   // "Hint" üzenetek státusz sorban történõ megjelenítésének engedélyezése
   Application->ShowHint = TRUE;
   Application->OnHint = DisplayHint;
}
//---------------------------------------------------------------------------
// "Hint" üzenetek megjelenítése a státusz sorban
//---------------------------------------------------------------------------
void __fastcall TFormMain::DisplayHint(TObject *Sender)
{
   StatusBar->Panels->Items[0]->Text = GetLongHint(Application->Hint);
}
//---------------------------------------------------------------------------
// Fõ ablak aktivizálódásakor lefutó függvény
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormActivate(TObject *Sender)
{
   // Dátum / Idõ kiírása a státusz sorba
   StatusBar->Panels->Items[1]->Text = FormatDateTime("yyyy/mm/dd  hh:nn:ss",Now());

   if( FormExtendedViewer->pMainSettings == NULL )
   {
      FormExtendedViewer->pMainSettings = MainSettings;
      FormExtendedViewer->stSoliSettings = MainSettings->stSoliSettings;
      FormExtendedViewer->Width = Width;
      FormExtendedViewer->Height = Height;
      FormExtendedViewer->Left = MainSettings->GetIntegerValueFromRegistry( "ExtendedWindowLeft" );
      FormExtendedViewer->Top = MainSettings->GetIntegerValueFromRegistry( "ExtendedWindowTop" );
      FormExtendedViewer->InitPanels( FormMain->MainSettings->GetCountSolarium(),
                                      FormMain->nCountRow,
                                      FormMain->nCountColumn );
   }
}
//---------------------------------------------------------------------------
// Fõ timer függvény, lefut minden másodpercben
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerMainTimer(TObject *Sender)
{
   // Dátum / Idõ frissítése a státusz sorban
   StatusBar->Panels->Items[1]->Text = FormatDateTime("yyyy/mm/dd  hh:nn:ss",Now());

   if( !bErrorDuringBoot )
   {
      // Szolárium ablakok frissítése
      for( int i=0; i<(int)pSzolarium.size(); i++ )
      {
         pSzolarium[i]->StatuszUpdate();
         pSzolarium[i]->UpdateExtendedView( FormExtendedViewer->PanelSzolarium[i],
                                            FormExtendedViewer->Panel_Nev[i],
                                            FormExtendedViewer->Label_Status[i],
                                            FormExtendedViewer->Label_Visszaszamlalas[i],
                                            FormExtendedViewer->Label_Ido[i],
                                            FormExtendedViewer->Label_Informacio[i],
                                            FormExtendedViewer->Label_Penz[i],
                                            FormExtendedViewer->ProgressBarCso[i] );
      }
   }
}
//---------------------------------------------------------------------------
// Szoláriumok mûködését irányító, lekérdezõ timer függvény,
// lefut 3 tizedmásodpercenként
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerSolariumTimer(TObject *Sender)
{
   if( pHardware->bySerial_Error > 100 )
   {
      TimerSolarium->Interval = 0;
      int nRet = Application->MessageBox( FormLanguage->LangStr(STR_ERR_COMM_WITH_HARDWARE).c_str(), FormLanguage->LangStr(STR_MSGBOX_ERROR).c_str(), MB_ICONSTOP|MB_RETRYCANCEL );
      switch( nRet )
      {
         case IDRETRY:
            pHardware->bySerial_Error = 0;
            TimerSolarium->Interval = 300;
            break;

         case IDCANCEL:
            Close();
            break;
      }
   }
   pHardware->HW_Kezel();

   for(int i=0;i<(int)pSzolarium.size();i++)
   {
      pSzolarium[i]->bStopped = pHardware->LED_Modul[ i ].bStop;
      pSzolarium[i]->StatuszUpdateImmediate();
      pSzolarium[i]->UpdateExtendedView( FormExtendedViewer->PanelSzolarium[i],
                                         FormExtendedViewer->Panel_Nev[i],
                                         FormExtendedViewer->Label_Status[i],
                                         FormExtendedViewer->Label_Visszaszamlalas[i],
                                         FormExtendedViewer->Label_Ido[i],
                                         FormExtendedViewer->Label_Informacio[i],
                                         FormExtendedViewer->Label_Penz[i],
                                         FormExtendedViewer->ProgressBarCso[i] );
   }
   SzolariumStatusCheck();
}
//---------------------------------------------------------------------------
// Felhasználói beavatkozást ellenörzõ timer
// ha adott ideig nem volt felhasználói beavatkozás a jelszókérést
// minden beavatkozásra kéri a program
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerUserLockTimer(TObject *Sender)
{
   if( !bErrorDuringBoot )
   {
      TimerUserLock->Interval = 100;
      MainSettings->SetPasswordRequired( true );
   }
   else
   {
      TimerUserLock->Interval = 3000;
      bErrorDuringBoot = false;
   }

   if( !FormPasswordCheck->Visible && MainSettings->IsPasswordRequired() )
   {
      char  strLastUser[20];

      memset( strLastUser, 0, sizeof(strLastUser) );
      strcpy( strLastUser, MainSettings->GetCurrentUser() );

      FormPasswordCheck->pUser = pUser;
      FormPasswordCheck->AccessLevel = ACCESS_USER;
      FormPasswordCheck->EditCurrentUser->Text = AnsiString( MainSettings->GetCurrentUser() );
      FormPasswordCheck->BitBtnExit->Enabled = true;
      FormPasswordCheck->BitBtnExit->Visible = true;
      int nRet = FormPasswordCheck->ShowModal();
      FormPasswordCheck->BitBtnExit->Enabled = false;
      FormPasswordCheck->BitBtnExit->Visible = false;
      if( nRet == mrOk )
      {
         if( MainSettings->GetIntegerValueFromRegistry( "ShowExtendedWindow" ) )
         {
            FormExtendedViewer->Show();
            FormExtendedViewer->Left = MainSettings->GetIntegerValueFromRegistry( "ExtendedWindowLeft" );
            FormExtendedViewer->Top = MainSettings->GetIntegerValueFromRegistry( "ExtendedWindowTop" );
         }
         else
         {
            FormExtendedViewer->Hide();
         }

         FormMain->SetFocus();
         TimerUserLock->Interval = 0;
         TimerUserLock->Enabled = false;
         MainSettings->SetPasswordRequired( false );
         MainSettings->SetCurrentUser( FormPasswordCheck->EditUserNev->Text.c_str() );
         Caption = FormLanguage->LangStr(STR_APPLICATION_CAPTION) +
                   AnsiString( " # " ) +
                   strCaption +
                   AnsiString( " # - [" ) +
                   AnsiString( pUser->GetUserNev(FormPasswordCheck->EditUserNev->Text.c_str()) ) +
                   AnsiString( "] - " ) +
                   AnsiString( pUser->GetUserLevelStr(FormPasswordCheck->EditUserNev->Text.c_str()) );
         MainSettings->strLogMsg = AnsiString( "Login user [" ) +
                                   AnsiString( pUser->GetUserNev(MainSettings->GetCurrentUser()) ) +
                                   AnsiString( "]" );
         MainSettings->LOG2( MainSettings->strLogMsg );
         if( pUser->GetUserLevel(FormPasswordCheck->EditUserNev->Text.c_str()) < ACCESS_ADMIN )
         {
            MenuMain_SettingsHWTeszt->Enabled = false;
         }
         else
         {
            MenuMain_SettingsHWTeszt->Enabled = true;
         }
      }
      else if( nRet == mrAbort )
      {
         TimerUserLock->Interval = 0;
         if( ToolButtonExit->Enabled )
         {
            MenuMain_SystemExitClick( Sender );
         }
         else
         {
            Application->MessageBox( FormLanguage->LangStr(STR_ERR_SOLINUSE_CLOSEDENIED).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
            TimerUserLock->Interval = 100;
         }
      }
   }
}
//---------------------------------------------------------------------------
AnsiString TFormMain::GetErrorMessageText( int nIndex )
{
   AnsiString  strRet = "";

   if( nIndex < (int)ErrorList.size() )
   {
      if( ErrorList[nIndex].nErrCode > 0 )
      {
         strRet = FormLanguage->LangStr(ErrorList[nIndex].nErrCode);
      }
      else
      {
         strRet = AnsiString(ErrorList[nIndex].strErrText);
      }
   }

   return strRet;
}
//---------------------------------------------------------------------------
// Szolárium(ok) állapotát lekérdezõ függvény
// állapottól függõen beavatkozások engedélyezése, tiltása
// Státuszok:
//    STATUS_ALAP, STATUS_VETKOZES, STATUS_SZAUNAZAS, STATUS_BARNULAS, STATUS_UTOHUTES
//---------------------------------------------------------------------------
void TFormMain::SzolariumStatusCheck()
{
   int   i;

   //---------------------------------------------------
   // Aktuális szoláriumra vonatkozó vizsgálat
   //---------------------------------------------------
   // Szolárium státuszának lekérdezése
   char cStatus = pSzolarium[nCurrentSolarium]->StatuszLekerdezes();

   if( cStatus == STATUS_ALAP )
   {
      // Szolárium alap állapotban van
      // Szolárium adatai módosíthatóak
      MenuMain_SettingSzolarium->Enabled = true;
      MenuMain_SettingSzolarium->Hint = FormLanguage->LangStr(STR_HINT_MODIFY_SOLARIUM_DATA);
      ToolButtonSzolariumAdat->Enabled = true;
      // Szolárium indítható bérlettel, idõvel
      ToolButtonSzolariumIdo->Enabled = true;
      ToolButtonSzolariumBerlet->Enabled = true;
      // Szolárium vészleállító gomb nem elérhetõ
      ToolButtonSzolariumHalt->Enabled = false;
      // Szolárium elindító gomb
      ToolButtonSzolariumStart->Enabled = false;
   }
   else
   {
      // Szolárium nincs alap állapotban
      // Szolárium adatai NEM módosíthatóak
      MenuMain_SettingSzolarium->Enabled = false;
      MenuMain_SettingSzolarium->Hint = FormLanguage->LangStr(STR_HINT_SOLINUSE_MODDENIED);
      ToolButtonSzolariumAdat->Enabled = false;
      if( cStatus == STATUS_VETKOZES )
      {
         // Szolárium indítható bérlettel, idõvel
         ToolButtonSzolariumIdo->Enabled = true;
         ToolButtonSzolariumBerlet->Enabled = true;

         bool bFizetve = !pSzolarium[nCurrentSolarium]->StatuszFizetnikell();
         int nForint = pSzolarium[nCurrentSolarium]->GetForintBarnulas();

         if( nForint != 0 && bFizetve )
         {
            // Szolárium vészleállító gomb elérhetõ
            ToolButtonSzolariumHalt->Enabled = true;
         }
         else
         {
            // Szolárium vészleállító gomb nem elérhetõ
            ToolButtonSzolariumHalt->Enabled = false;
         }
         // Szolárium elindító gomb
         ToolButtonSzolariumStart->Enabled = true;
      }
      else
      {
         // Szolárium nem indítható bérlettel, idõvel
         ToolButtonSzolariumIdo->Enabled = false;
         ToolButtonSzolariumBerlet->Enabled = false;
         // Szolárium vészleállító gomb elérhetõ
         ToolButtonSzolariumHalt->Enabled = true;
         // Szolárium elindító gomb
//         ToolButtonSzolariumStart->Enabled = false;
         ToolButtonSzolariumStart->Enabled = pSzolarium[nCurrentSolarium]->bStopped;
      }
   }

   // NEM STERIL feliratot eltüntetõ gomb engedélyezése/tiltása
   ToolButtonSzolariumSteril->Enabled = !pSzolarium[nCurrentSolarium]->StatuszSteril();

   //---------------------------------------------------
   // Összes szoláriumra egyszerre vonatkozó vizsgálat
   //---------------------------------------------------
   // Ha nincs minden szolárium alap státuszban ->
   // -> nem lehet a program futását leállítani
   // -> ...
   for( i=0; i<(int)pSzolarium.size(); i++ )
   {
      if( pSzolarium[i]->StatuszLekerdezes() != STATUS_ALAP )
      {
         // valamelyik szolárium nincs alap állapotban
         // kilépõ menü és gomb letiltása
         MenuMain_SystemExit->Enabled = false;
         ToolButtonExit->Enabled = false;
         break;
      }
   }
   if( i == (int)pSzolarium.size() )
   {
      // az összes szolárium alap állapotban van
      // kilépõ menü és gomb engedélyezése
      MenuMain_SystemExit->Enabled = true;
      ToolButtonExit->Enabled = true;
   }
}
//---------------------------------------------------------------------------
// Fõablakban beírt szövegbõl (idõ, vonalkód) a felesleges karakter(ek) kitörlése
// Paraméterek:
//    nAction: az adatbeírást feldolgozó ablak által meghatározott feltételezett
//             adathoz tartozó beavatkozás;
//             értéke lehet:
//                ACTION_BARNULASIDO - barnulás idõ lett begépelve
//                ACTION_VONALKOD    - bérlet, termék vonalkód lett begépelve
//    EditAdat: az adatbeírást feldolgozó ablak szövegmezõjére mutató pointer
//---------------------------------------------------------------------------
int TFormMain::InputDataCheck( int nAction, TEdit *EditAdat )
{
/*   switch( nAction )
   {
      case ACTION_BARNULASIDO:
         if( EditAdat->Text.SubString( 1, 1 ).AnsiCompare( "I" ) == 0 )
         {
            // I betü eltávolítása, ha volt
            EditAdat->Text = EditAdat->Text.SubString( 2, EditAdat->Text.Length()-1 );
         }
         break;

      case ACTION_VONALKOD:
         if( EditAdat->Text.SubString( 1, 1 ).AnsiCompare( "V" ) == 0 ||
             EditAdat->Text.SubString( 1, 1 ).AnsiCompare( "B" ) == 0 )
         {
            // V illetve B betü eltávolítása, ha volt
            EditAdat->Text = EditAdat->Text.SubString( 2, EditAdat->Text.Length()-1 );
         }
         break;
   }*/
   return nAction;
}
//---------------------------------------------------------------------------

/****************************************************************************
*
* FELHASZNALOI BEAVATKOZASOK LEKEZELESE
*
****************************************************************************/

//---------------------------------------------------------------------------
// Felhasználói beavatkozás - billentyûzet használat - lekezelése
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
   if( Shift.Contains( ssCtrl ) )
   {
      // CTRL billentyû lenyomva
      // HotKey billentyû lekezelése
      KeyDownShorcut( Sender, Key );
   }
   else if( !Shift.Contains( ssAlt ) &&
            ((Key >= 65 && Key <= 90) ||
            (Key >= 96 && Key <= 105) ||
            (Key >= 48 && Key <= 57)) )
   {
      // ABC illetve szám billentyû lenyomva
      if( Key >= 96 && Key <= 105 )
      {
         // Numpad szám billentyû => normál szám billentyû
         Key -= 48;
      }
      // Adatbeírás feldolgozása ha alap állapotban van
      if( pSzolarium[nCurrentSolarium]->StatuszLekerdezes() <= STATUS_VETKOZES )
      {
         KeyDownProcess( Sender, Key, Shift);
      }
   }
   else
   {
      switch( Key )
      {
         case VK_LEFT:
         case VK_RIGHT:
         case VK_UP:
         case VK_DOWN:
            // Nyíl billentyû lenyomva
            // Aktuális szolárium megváltoztatása
            ActionSzolariumSelect( Key );
            break;

         case VK_ESCAPE:
         {
            // ESC billentyû lenyomva
            // Szolárium státusztól függõen ...
            char cStatus = pSzolarium[nCurrentSolarium]->StatuszLekerdezes();
            bool bSteril = pSzolarium[nCurrentSolarium]->StatuszSteril();
            bool bFizetve = !pSzolarium[nCurrentSolarium]->StatuszFizetnikell();
            int nForint = pSzolarium[nCurrentSolarium]->GetForintBarnulas();

            if( (cStatus == STATUS_ALAP && bSteril && bFizetve) ||
                (cStatus == STATUS_VETKOZES && nForint != 0 && !bFizetve ) ||
                (cStatus == STATUS_VETKOZES && nForint == 0 ) )
            {
               // Szolárium alap állapotban;
               // Felhasználói adatainak elõkeresése
               typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
               // Eddigi adatok (bérlethasználat, forint stb) törlése
               pSzolarium[nCurrentSolarium]->StartReset( stUser );
               pKosar->DeleteKosar( AnsiString(nCurrentSolarium).c_str() );
            }
            break;
         }
         case VK_RETURN:
            // Szolárium adatait kezelõ dialógus ablak megnyitása
            //MenuMain_SettingSzolariumClick( Sender );
            break;
         case VK_F1:
//            MenuMain_ListMaincashClick(Sender);
            break;
         case VK_F2:
//            MenuMain_ListDailycashClick(Sender);
            break;
         case VK_F3:
//            MenuMain_PenzBerletClick(Sender);
            break;
         case VK_F4:
//            MenuMain_ListGoodsClick(Sender);
            break;
         case VK_F5:
//            MenuMain_ListBerletOsszClick(Sender);
            break;
      }
   }
}
//---------------------------------------------------------------------------
// "hotkey" billentyûk - CTRL + billentyû lenyomásának lekezelése
//---------------------------------------------------------------------------
void TFormMain::KeyDownShorcut(TObject *Sender, WORD Key )
{
   switch( Key )
   {
      case 'F':
      case 'f':
         // Szoláriumhasználat kifizetve, Ft érték eltüntetése
         MenuMain_PenzKosarClick( Sender );
         break;
      case 'T':
      case 't':
         // Szolárium vészleállítása
         ToolButtonSzolariumHaltClick( Sender );
         break;
      case 'Z':
      case 'z':
         // Program "lock"-olása
         MenuMain_SystemLogoffClick(Sender);
         break;
      case 'B':
      case 'b':
         // Berlet eladás
         ToolButtonBerletEladasClick( Sender );
         break;
      case 'K':
      case 'k':
         // Kozmetikum kezeles
         ToolButtonTermekEladasClick( Sender );
         break;
      case 'S':
      case 's':
      {
         char sStatus = pSzolarium[nCurrentSolarium]->StatuszLekerdezes();
         // Szolárium státusztól függõen ...
         if( sStatus == STATUS_VETKOZES || sStatus == STATUS_BARNULAS )
         {
            // vetkõzés megszakítása, szaunázás / barnulás elindítása
            // STOP állapot lekezelése
            ToolButtonSzolariumStartClick( Sender );
            // Vetkõzési szakasz elindítása
            //pSzolarium[nCurrentSolarium]->Inditas();
         }
         else
         {
            // NEM STERIL felirat eltüntetése
            ToolButtonSzolariumSterilClick( Sender );
         }
         break;
      }
      case 'M':
      case 'm':
         // Muszak zaras
         MenuMain_SystemSessioncloseClick(Sender);
         break;
      case 'Q':
      case 'q':
         // Kilépés a programból
         MenuMain_SystemExitClick( Sender );
         break;
      case VK_F12:
      {
         // Csak ROOT user adatmanipulálás
         int   nRet = mrOk;
         typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );

         if( stUser.nUserLevel < ACCESS_ROOT )
         {
            FormPasswordCheck->pUser = pUser;
            FormPasswordCheck->AccessLevel = ACCESS_ROOT;
            FormPasswordCheck->EditCurrentUser->Text = AnsiString( MainSettings->GetCurrentUser() );
            nRet = FormPasswordCheck->ShowModal();
         }
         if( nRet == mrOk )
         {
            if( FormPasswordCheck->EditUserNev->Text.AnsiCompare( "root" ) == 0 )
            {
               SystemAdmin->pMainSettings = MainSettings;
               SystemAdmin->ShowModal();
            }
         }
         break;
      }
   }
}
//---------------------------------------------------------------------------
// Adatbeírás lekezelése
//---------------------------------------------------------------------------
void TFormMain::KeyDownProcess(TObject *Sender, WORD &Key, TShiftState Shift)
{
   AnsiString strTemp;

   // Aktuális szolárium adataihoz hozzáférés biztosítása
   FormDataRead->pSzolarium = pSzolarium[nCurrentSolarium];
   // A lenyomott billentyû beírása az ablak szöveg mezõjébe
   FormDataRead->EditAdat->Text = strTemp.StringOfChar( Key, 1 );

   // Adatbeolvasó ablak megnyitása
   if( FormDataRead->ShowModal() == mrOk )
   {
      // RENDBEN gomb lenyomása esetén felesleges karakterek kitörlése
//      switch( InputDataCheck( FormDataRead->nAction, FormDataRead->EditAdat ) )
      switch( FormDataRead->nAction )
      {
         case ACTION_BARNULASIDO:
            // Barnulási idõ beírva
            ActionSzolariumIdo( Sender, Key, Shift);
            break;

         case ACTION_VONALKOD:
         {
            // Bérlet / Termék vonalkód beírva

            // Vonalkód keresése a bérletek között
            typ_berlet stTemp = pBerletek->GetBerlet( FormDataRead->EditAdat->Text.c_str() );

            if( stTemp.nBerletTipus != 0 )
            {
               // Vonalkód bérlethez tartozik
               // Bérlethasználat elindítása
               ActionBerletHasznalat( stTemp );
            }
            else
            {
               // Vonalkód nem bérlethez tartozik
               // Vonalkód keresése a termékek között
               typ_termek stTermek = pTermek->GetTermekKod( FormDataRead->EditAdat->Text.c_str() );

               if( stTermek.nID != 0 )
               {
                  // Vonalkód termékhez tartozik
                  // Termékeladás elindítása
                  ActionTermekEladas( stTermek );
               }
               else
               {
                  // A beírt azonosító se bérlet, se termék
                  Application->MessageBox( FormLanguage->LangStr(STR_MSG_BARCODE_NOTEXISTS).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
               }
            }
            break;
         }/* case ACTION_VONALKOD */
      }/* switch( InputDataCheck ) */
   }/* if( FormDataRead->ShowModal() == mrOk ) */
}
//---------------------------------------------------------------------------
// Beírt barnulási idõ ellenõrzése és a szolárium felkészítése
//---------------------------------------------------------------------------
void TFormMain::ActionSzolariumIdo(TObject *Sender, WORD &Key, TShiftState Shift)
{
   // Barnulási idõ kiolvasása az adatbeírás ablakból
   int nBarnulas = FormDataRead->EditAdat->Text.ToInt();
   int nForint = 0;

   // Barnulási idõ kikeresése az aktuális szolárium Idõ/Forint táblázatából
   if( pSzolarium[nCurrentSolarium]->CheckBarnulasIdo( nBarnulas, &nForint ) )
   {
      pSzolarium[nCurrentSolarium]->strLogMsg = AnsiString( "Szolárium használat kp. fizetéssel [" ) +
                                                AnsiString( pSzolarium[nCurrentSolarium]->stAdat.strNev ) +
                                                AnsiString( "] [" ) +
                                                AnsiString( nBarnulas ) +
                                                AnsiString( "] perc [" ) +
                                                convertToCurrencyString( nForint ) +
                                                AnsiString( "] forint [" ) +
                                                AnsiString( pUser->GetUserNev(MainSettings->GetCurrentUser()) ) +
                                                AnsiString( "]" );
      pSzolarium[nCurrentSolarium]->LOG2( pSzolarium[nCurrentSolarium]->strLogMsg );
      // Aktuális szolárium elõkészítése, barnulási idõ és forint érték hozzáadás
      pSzolarium[nCurrentSolarium]->StartPrepare( nBarnulas*60, nForint );
      // Forint használat felvétele a kosárba
      ActionSzolariumKosarba( nForint );
      // Vetkõzési szakasz elindítása
      pSzolarium[nCurrentSolarium]->Inditas();
      // Hardware frissitese
      pHardware->LED_Modul[ nCurrentSolarium ].bSendIras = true;
   }
   else
   {
      // Barnulási idõ nem szerepel az aktuális szolárium Idõ/Forint táblázatában
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_SOLTIME_NOTEXISTS).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      // Adatbeolvasó ablak újrahívása idõpont megadással "I" betû az elején
      Key = 0;//73; // nem kell az I betü
      FormKeyDown( Sender, Key, Shift);
   }
}
//---------------------------------------------------------------------------
// Bérlet használatának lekezelése
//---------------------------------------------------------------------------
void TFormMain::ActionBerletHasznalat( typ_berlet stBerlet )
{
   // Hozzáférés a bérletek adatbázisához
   FormBerletHasznalat->pBerlet = pBerletek;
   // Adott bérlet adatainak átadása
   FormBerletHasznalat->stBerlet = stBerlet;
   // Registry olvasáshoz
   FormBerletHasznalat->pMainSettings = MainSettings;
   // Bérlethasználat ablak megnyitása
   if( FormBerletHasznalat->ShowModal() == mrOk )
   {
      // Nincs megadva még PIN kód a bérlethez
      if( stBerlet.nPin == 0 && MainSettings->GetBoolValueFromRegistry( "IsPINCodeNeeded", false ) )
      {
         if( Application->MessageBox( FormLanguage->LangStr(STR_NO_VALID_PIN).c_str(),
                                      FormLanguage->LangStr(STR_MSGBOX_QUESTION).c_str(),
                                      MB_ICONQUESTION|MB_YESNO ) == IDYES )
         {
            FormBerletPIN->ShowModal();
            stBerlet.nPin = FormBerletPIN->EditPIN->Text.ToInt();
            pBerletek->SetPIN( stBerlet.strVonalkod, stBerlet.nPin );
         }
      }
      // Felhasználandó egység kiolvasása a bérlethasználat ablakból
      int nBarnulas = 0;
      int nEgyseg = FormBerletHasznalat->ComboBoxHasznalat->ItemIndex+1;

      // Barnulási idõ kikeresése az aktuális szolárium Idõ/Forint táblázatából
//      if( pSzolarium[nCurrentSolarium]->GetBarnulasIdo( nEgyseg, &nBarnulas ) )

      // Barnulási idõ elõszedése a bérlettípusból
      typ_berlettipus stBerletTipus;

      memset( &stBerletTipus, 0, sizeof(typ_berlettipus) );
      stBerletTipus = pBerletek->GetBerletTipusID( stBerlet.nBerletTipus );

      // Ha a barnulási egységidõ nincs megadva, akkor nem lesz bérlethasználat
      if( stBerletTipus.nEgysegIdo > 0 )
      {
         nBarnulas = nEgyseg * stBerletTipus.nEgysegIdo;

         pSzolarium[nCurrentSolarium]->strLogMsg = AnsiString( "Szolárium használat bérlettel [" ) +
                                                   AnsiString( pSzolarium[nCurrentSolarium]->stAdat.strNev ) +
                                                   AnsiString( "] [" ) +
                                                   AnsiString( nBarnulas ) +
                                                   AnsiString( "] perc [" ) +
                                                   AnsiString( stBerlet.strVonalkod ) +
                                                   AnsiString( "] bérlet [" ) +
                                                   AnsiString( nEgyseg ) +
                                                   AnsiString( "] egység [" ) +
                                                   AnsiString( pUser->GetUserNev(MainSettings->GetCurrentUser()) ) +
                                                   AnsiString( "]" );
         pSzolarium[nCurrentSolarium]->LOG2( pSzolarium[nCurrentSolarium]->strLogMsg );
         // Aktuális szolárium elõkészítése, bérlet, barnulási idõ hozzáadás
         pSzolarium[nCurrentSolarium]->StartPrepare( stBerlet, nBarnulas*60, nEgyseg );
         // Felhasználandó egységek levonása a bérletrõl
         pBerletek->DecreaseBerletEgyseg( stBerlet.strVonalkod, nEgyseg );
         // Vetkõzési szakasz elindítása
         pSzolarium[nCurrentSolarium]->Inditas();
         // Hardware frissitese
         pHardware->LED_Modul[ nCurrentSolarium ].bSendIras = true;
      }
      else
      {
         // Hiányzik a szolárium Idõ/Forint táblázat adott eleme
         Application->MessageBox( FormLanguage->LangStr(STR_MSG_TIMETABLE_EMPTY).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      }
   }
}
//---------------------------------------------------------------------------
// Termék eladásának lekezelése
//---------------------------------------------------------------------------
void TFormMain::ActionTermekEladas( typ_termek stTermek )
{
   // Termék adatainak átadása a termékeladást kezelõ ablaknak
   FormTermekEladas->stTermek = stTermek;

   // Termékeladást kezelõ ablak megnyitása
   switch( FormTermekEladas->ShowModal() )
   {
      case mrOk:
      {
         // Készpénz fizetés azonnal
         // Fizetést kezelõ ablakban Kosárba gomb engedélyezése
         FormFizetes->BitBtnKosar->Enabled = true;
         // Pénzösszeg átadása a Fizetést kezelõ ablaknak
         FormFizetes->LabelFizetendo->Caption = FormTermekEladas->EditFizetendo->Text;
         // Fizetést kezelõ ablak megnyitása
         switch( FormFizetes->ShowModal() )
         {
            case mrOk:
            {
               // Kifizetve gomb megnyomva
               pKonyv->AddGeneralKonyv( MainSettings->GetCurrentMuszak(),
                                        0,
                                        FormTermekEladas->EditFizetendo->Text.ToDouble(),
                                        "" );
               // eladott terméket adott mennyiséggel
               // csökkenteni a termék adatbázisban
               ActionTermekDarabCsokkentes();

               // Felhasználói adatainak elõkeresése
               typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
               // Megjegyzés feltöltése a termék adattal
               AnsiString strTemp = AnsiString( stTermek.nDarab ) +
                                    FormLanguage->LangStr(STR_PIECE) +
                                    AnsiString( stTermek.strNev );
               pPenztar->strLogMsg = AnsiString( "Termek eladas [" ) +
                                     AnsiString( FormTermekEladas->EditVonalkod->Text ) +
                                     AnsiString( "/" ) +
                                     AnsiString( FormTermekEladas->EditAr->Text ) +
                                     AnsiString( "/" ) +
                                     AnsiString( FormTermekEladas->EditDarab->Text ) +
                                     AnsiString( "] user [" ) +
                                     AnsiString( pUser->GetUserNev(MainSettings->GetCurrentUser()) ) +
                                     AnsiString( "]" );
               pPenztar->LOG2( pPenztar->strLogMsg );
               // Bevétel hozzáadása a pénztárhoz
               pPenztar->PenztarBevetel( stUser, FormTermekEladas->EditFizetendo->Text.ToInt(), strTemp.c_str() );
               break;
            }
            case mrYes:
               // Kosárba gomb megnyomva
               // Termék felvétele a kosárba
               ActionTermekKosarba();
               // eladott terméket adott mennyiséggel
               // csökkenteni a termék adatbázisban
               ActionTermekDarabCsokkentes();
               break;
         }
         break;
      }
      case mrYes:
      {
         // Kosárba gomb megnyomva
         // Termék felvétele a kosárba
         ActionTermekKosarba();
         // eladott terméket adott mennyiséggel
         // csökkenteni a termék adatbázisban
         ActionTermekDarabCsokkentes();
         break;
      }
   }
}
//---------------------------------------------------------------------------
// Bérlet felvétele kosárba
//---------------------------------------------------------------------------
void TFormMain::ActionBerletKosarba()
{
   typ_kosar stKosar;

   memset( &stKosar, 0, sizeof(typ_kosar) );

   // Egyedi azonosító kiszámolása
   stKosar.nID = pKosar->GetKosarCount()+1;
   // Kosárelem típusa: 0 -> bérlet
   stKosar.nTipus = 0;
   // Adatok átadása a Bérleteladás ablakból a kosárnak
   strncpy( stKosar.strVonalkod, FormBerletEladas->EditVonalkod->Text.c_str(), sizeof(stKosar.strVonalkod)-2 );
   strcpy( stKosar.strNev, FormBerletEladas->ComboBoxTipus->Items->Strings[FormBerletEladas->ComboBoxTipus->ItemIndex].c_str() );
   stKosar.nAr = convertCurrency(FormBerletEladas->EditBTAr->Text.ToDouble());
   stKosar.nDarab = 1;
   // Bérlet felvétele a kosárba
   pKosar->AddKosar( stKosar );
}
//---------------------------------------------------------------------------
// Termék felvétele a kosárba
//---------------------------------------------------------------------------
void TFormMain::ActionTermekKosarba()
{
   typ_kosar stKosar;

   memset( &stKosar, 0, sizeof(typ_kosar) );

   // Egyedi azonosító kiszámolása
   stKosar.nID = pKosar->GetKosarCount()+1;
   // Kosárelem típusa: 1 -> termék
   stKosar.nTipus = 1;
   // Adatok átadása a Termékeladás ablakból a kosárnak
   strncpy( stKosar.strVonalkod, FormTermekEladas->EditVonalkod->Text.c_str(), sizeof(stKosar.strVonalkod)-2 );
   strncpy( stKosar.strNev, FormTermekEladas->EditNev->Text.c_str(), sizeof(stKosar.strNev)-2 );
   stKosar.nAr = convertCurrency(FormTermekEladas->EditAr->Text.ToDouble());
   stKosar.nDarab = FormTermekEladas->ComboBoxDarab->Items->Strings[FormTermekEladas->ComboBoxDarab->ItemIndex].ToInt();
   // Termék felvétele a kosárba
   pKosar->AddKosar( stKosar );
}
//---------------------------------------------------------------------------
// Szolárium forint használat felvétele a kosárba
//---------------------------------------------------------------------------
void TFormMain::ActionSzolariumKosarba( int nForint )
{
   typ_kosar stKosar;

   memset( &stKosar, 0, sizeof(typ_kosar) );

   // Egyedi azonosító kiszámolása
   stKosar.nID = pKosar->GetKosarCount()+1;
   // Kosárelem típusa: 2 -> szolárium
   stKosar.nTipus = 2;
   // Adatok átadása a kosárnak
   strcpy( stKosar.strVonalkod, AnsiString(nCurrentSolarium).c_str() );
   strcpy( stKosar.strNev, pSzolarium[nCurrentSolarium]->stAdat.strNev );
   stKosar.nAr = nForint;
   stKosar.nDarab = 1;
   // Szolárium forint használat felvétele a kosárba
   pKosar->AddKosar( stKosar );
}
//---------------------------------------------------------------------------
// Termék felvétele a kosárba
//---------------------------------------------------------------------------
void TFormMain::ActionTermekListaKosarba()
{
   typ_kosar stKosar;

   memset( &stKosar, 0, sizeof(typ_kosar) );

   // Egyedi azonosító kiszámolása
   stKosar.nID = pKosar->GetKosarCount()+1;
   // Kosárelem típusa: 1 -> termék
   stKosar.nTipus = 1;
   // Adatok átadása a Termékeladás ablakból a kosárnak
   strncpy( stKosar.strVonalkod, FormTermekListaEladas->EditVonalkod->Text.c_str(), sizeof(stKosar.strVonalkod)-2 );
   strncpy( stKosar.strNev, FormTermekListaEladas->EditNev->Text.c_str(), sizeof(stKosar.strNev)-2 );
   stKosar.nAr = convertCurrency(FormTermekListaEladas->EditAr->Text.ToDouble());
   stKosar.nDarab = FormTermekListaEladas->ComboBoxDarab->Items->Strings[FormTermekListaEladas->ComboBoxDarab->ItemIndex].ToInt();
   // Termék felvétele a kosárba
   pKosar->AddKosar( stKosar );
}
//---------------------------------------------------------------------------
// Termék eladásakor (kosárba rakásakor) a termékek számának raktárban csökkentése
//---------------------------------------------------------------------------
void TFormMain::ActionTermekDarabCsokkentes()
{
   DWORD nID = FormTermekEladas->EditID->Text.ToDouble();
   int nDarab = FormTermekEladas->ComboBoxDarab->Items->Strings[FormTermekEladas->ComboBoxDarab->ItemIndex].ToInt();
   int nCurrDarab = pTermek->GetTermekDarab( nID );

   pTermek->SetTermekDarab( nID, nCurrDarab-nDarab );
}
//---------------------------------------------------------------------------
// Termék eladásakor (kosárba rakásakor) a termékek számának raktárban csökkentése
//---------------------------------------------------------------------------
void TFormMain::ActionTermekListaDarabCsokkentes()
{
   DWORD nID = FormTermekListaEladas->EditID->Text.ToDouble();
   int nDarab = FormTermekListaEladas->ComboBoxDarab->Items->Strings[FormTermekListaEladas->ComboBoxDarab->ItemIndex].ToInt();
   int nCurrDarab = pTermek->GetTermekDarab( nID );

   pTermek->SetTermekDarab( nID, nCurrDarab-nDarab );
}
//---------------------------------------------------------------------------
// Aktuális szolárium kiválasztása a nyíl gombok segítségével
//---------------------------------------------------------------------------
void TFormMain::ActionSzolariumSelect( WORD Key )
{
   switch( Key )
   {
      // Aktuális szolárium megjelölésének visszavonása
      case VK_LEFT:
      case VK_RIGHT:
      case VK_UP:
      case VK_DOWN:
         pSzolarium[nCurrentSolarium]->Deselect();
         break;
   }
   switch( Key )
   {
      // Újonnan kiválasztandó szolárium megkeresése
      case VK_LEFT:
         // Balra mozgás esetén
         if( nCurrentSolarium%nCountColumn == 0 )
            nCurrentSolarium += nCountColumn;
         nCurrentSolarium--;
         break;

      case VK_RIGHT:
         // Jobbra mozgás esetén
         nCurrentSolarium++;
         if( nCurrentSolarium%nCountColumn == 0 )
            nCurrentSolarium -= nCountColumn;
         else if( nCurrentSolarium == MainSettings->GetCountSolarium() )
            nCurrentSolarium -= nCurrentSolarium%nCountColumn;
         break;

      case VK_UP:
         // Felfelé mozgás esetén
         if( nCurrentSolarium-nCountColumn < 0 )
         {
            nCurrentSolarium = nCountRow*(nCountColumn-1)+nCurrentSolarium-1;
            if( nCurrentSolarium > MainSettings->GetCountSolarium()-1 )
               nCurrentSolarium -= nCountColumn;
         }
         else
            nCurrentSolarium -= nCountColumn;
         break;

      case VK_DOWN:
         // Lefelé mozgás esetén
         if( nCurrentSolarium+nCountColumn > MainSettings->GetCountSolarium()-1 )
            nCurrentSolarium = nCurrentSolarium%nCountColumn;
         else
            nCurrentSolarium += nCountColumn;
         break;
   }
   switch( Key )
   {
      // Új aktuális szolárium megjelölése
      case VK_LEFT:
      case VK_RIGHT:
      case VK_UP:
      case VK_DOWN:
         if( nCurrentSolarium < 0 )
            nCurrentSolarium = 0;
         if( nCurrentSolarium > MainSettings->GetCountSolarium()-1 )
            nCurrentSolarium = MainSettings->GetCountSolarium()-1;
         pSzolarium[nCurrentSolarium]->Select();
         break;
   }
}
//---------------------------------------------------------------------------
// Egér gomblenyomás esetén aktuális szolárium kiválasztása
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TPanel *temppanel;
   TLabel *templabel;

   if( Sender->ClassNameIs( "TLabel" ) )
   {
      // Ha az egér kattintás nem a szolárium paneljára esett
      // akkor egy feliratra -> szülõ panelre mutató pointer megszerzése
      templabel = (TLabel*)Sender;
      temppanel = (TPanel*)templabel->Parent;
   }
   else if( Sender->ClassNameIs( "TPanel" ) )
   {
      // Ha az egér kattintás a szolárium paneljára esett
      // panelre mutató pointer megszerzése
      temppanel = (TPanel*)Sender;
   }
   else
      return;

   // Aktuális szolárium megjelölésének visszavonása
   pSzolarium[nCurrentSolarium]->Deselect();
   // Újonnan kiválasztandó szolárium megkeresése a panel alapján
   nCurrentSolarium = temppanel->TabOrder-2;
   // Új aktuális szolárium megjelölése
   pSzolarium[nCurrentSolarium]->Select();
}
//---------------------------------------------------------------------------
// Egér dupla kattintás lekezelése: aktuális szolárium adatait kezelõ
// ablak megnyitása
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDblClick(TObject *Sender)
{
//   MenuMain_SettingSzolariumClick(Sender);
}
//---------------------------------------------------------------------------

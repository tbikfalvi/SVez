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
// F� ablak l�trehoz�sakor lefut� f�ggv�ny
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
   // Alap be�ll�t�sok
   bErrorDuringBoot = false;

   // "Hint" �zenetek st�tusz sorban t�rt�n� megjelen�t�s�nek enged�lyez�se
   Application->ShowHint = TRUE;
   Application->OnHint = DisplayHint;
}
//---------------------------------------------------------------------------
// "Hint" �zenetek megjelen�t�se a st�tusz sorban
//---------------------------------------------------------------------------
void __fastcall TFormMain::DisplayHint(TObject *Sender)
{
   StatusBar->Panels->Items[0]->Text = GetLongHint(Application->Hint);
}
//---------------------------------------------------------------------------
// F� ablak aktiviz�l�d�sakor lefut� f�ggv�ny
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormActivate(TObject *Sender)
{
   // D�tum / Id� ki�r�sa a st�tusz sorba
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
// F� timer f�ggv�ny, lefut minden m�sodpercben
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerMainTimer(TObject *Sender)
{
   // D�tum / Id� friss�t�se a st�tusz sorban
   StatusBar->Panels->Items[1]->Text = FormatDateTime("yyyy/mm/dd  hh:nn:ss",Now());

   if( !bErrorDuringBoot )
   {
      // Szol�rium ablakok friss�t�se
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
// Szol�riumok m�k�d�s�t ir�ny�t�, lek�rdez� timer f�ggv�ny,
// lefut 3 tizedm�sodpercenk�nt
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
// Felhaszn�l�i beavatkoz�st ellen�rz� timer
// ha adott ideig nem volt felhaszn�l�i beavatkoz�s a jelsz�k�r�st
// minden beavatkoz�sra k�ri a program
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
// Szol�rium(ok) �llapot�t lek�rdez� f�ggv�ny
// �llapott�l f�gg�en beavatkoz�sok enged�lyez�se, tilt�sa
// St�tuszok:
//    STATUS_ALAP, STATUS_VETKOZES, STATUS_SZAUNAZAS, STATUS_BARNULAS, STATUS_UTOHUTES
//---------------------------------------------------------------------------
void TFormMain::SzolariumStatusCheck()
{
   int   i;

   //---------------------------------------------------
   // Aktu�lis szol�riumra vonatkoz� vizsg�lat
   //---------------------------------------------------
   // Szol�rium st�tusz�nak lek�rdez�se
   char cStatus = pSzolarium[nCurrentSolarium]->StatuszLekerdezes();

   if( cStatus == STATUS_ALAP )
   {
      // Szol�rium alap �llapotban van
      // Szol�rium adatai m�dos�that�ak
      MenuMain_SettingSzolarium->Enabled = true;
      MenuMain_SettingSzolarium->Hint = FormLanguage->LangStr(STR_HINT_MODIFY_SOLARIUM_DATA);
      ToolButtonSzolariumAdat->Enabled = true;
      // Szol�rium ind�that� b�rlettel, id�vel
      ToolButtonSzolariumIdo->Enabled = true;
      ToolButtonSzolariumBerlet->Enabled = true;
      // Szol�rium v�szle�ll�t� gomb nem el�rhet�
      ToolButtonSzolariumHalt->Enabled = false;
      // Szol�rium elind�t� gomb
      ToolButtonSzolariumStart->Enabled = false;
   }
   else
   {
      // Szol�rium nincs alap �llapotban
      // Szol�rium adatai NEM m�dos�that�ak
      MenuMain_SettingSzolarium->Enabled = false;
      MenuMain_SettingSzolarium->Hint = FormLanguage->LangStr(STR_HINT_SOLINUSE_MODDENIED);
      ToolButtonSzolariumAdat->Enabled = false;
      if( cStatus == STATUS_VETKOZES )
      {
         // Szol�rium ind�that� b�rlettel, id�vel
         ToolButtonSzolariumIdo->Enabled = true;
         ToolButtonSzolariumBerlet->Enabled = true;

         bool bFizetve = !pSzolarium[nCurrentSolarium]->StatuszFizetnikell();
         int nForint = pSzolarium[nCurrentSolarium]->GetForintBarnulas();

         if( nForint != 0 && bFizetve )
         {
            // Szol�rium v�szle�ll�t� gomb el�rhet�
            ToolButtonSzolariumHalt->Enabled = true;
         }
         else
         {
            // Szol�rium v�szle�ll�t� gomb nem el�rhet�
            ToolButtonSzolariumHalt->Enabled = false;
         }
         // Szol�rium elind�t� gomb
         ToolButtonSzolariumStart->Enabled = true;
      }
      else
      {
         // Szol�rium nem ind�that� b�rlettel, id�vel
         ToolButtonSzolariumIdo->Enabled = false;
         ToolButtonSzolariumBerlet->Enabled = false;
         // Szol�rium v�szle�ll�t� gomb el�rhet�
         ToolButtonSzolariumHalt->Enabled = true;
         // Szol�rium elind�t� gomb
//         ToolButtonSzolariumStart->Enabled = false;
         ToolButtonSzolariumStart->Enabled = pSzolarium[nCurrentSolarium]->bStopped;
      }
   }

   // NEM STERIL feliratot elt�ntet� gomb enged�lyez�se/tilt�sa
   ToolButtonSzolariumSteril->Enabled = !pSzolarium[nCurrentSolarium]->StatuszSteril();

   //---------------------------------------------------
   // �sszes szol�riumra egyszerre vonatkoz� vizsg�lat
   //---------------------------------------------------
   // Ha nincs minden szol�rium alap st�tuszban ->
   // -> nem lehet a program fut�s�t le�ll�tani
   // -> ...
   for( i=0; i<(int)pSzolarium.size(); i++ )
   {
      if( pSzolarium[i]->StatuszLekerdezes() != STATUS_ALAP )
      {
         // valamelyik szol�rium nincs alap �llapotban
         // kil�p� men� �s gomb letilt�sa
         MenuMain_SystemExit->Enabled = false;
         ToolButtonExit->Enabled = false;
         break;
      }
   }
   if( i == (int)pSzolarium.size() )
   {
      // az �sszes szol�rium alap �llapotban van
      // kil�p� men� �s gomb enged�lyez�se
      MenuMain_SystemExit->Enabled = true;
      ToolButtonExit->Enabled = true;
   }
}
//---------------------------------------------------------------------------
// F�ablakban be�rt sz�vegb�l (id�, vonalk�d) a felesleges karakter(ek) kit�rl�se
// Param�terek:
//    nAction: az adatbe�r�st feldolgoz� ablak �ltal meghat�rozott felt�telezett
//             adathoz tartoz� beavatkoz�s;
//             �rt�ke lehet:
//                ACTION_BARNULASIDO - barnul�s id� lett beg�pelve
//                ACTION_VONALKOD    - b�rlet, term�k vonalk�d lett beg�pelve
//    EditAdat: az adatbe�r�st feldolgoz� ablak sz�vegmez�j�re mutat� pointer
//---------------------------------------------------------------------------
int TFormMain::InputDataCheck( int nAction, TEdit *EditAdat )
{
/*   switch( nAction )
   {
      case ACTION_BARNULASIDO:
         if( EditAdat->Text.SubString( 1, 1 ).AnsiCompare( "I" ) == 0 )
         {
            // I bet� elt�vol�t�sa, ha volt
            EditAdat->Text = EditAdat->Text.SubString( 2, EditAdat->Text.Length()-1 );
         }
         break;

      case ACTION_VONALKOD:
         if( EditAdat->Text.SubString( 1, 1 ).AnsiCompare( "V" ) == 0 ||
             EditAdat->Text.SubString( 1, 1 ).AnsiCompare( "B" ) == 0 )
         {
            // V illetve B bet� elt�vol�t�sa, ha volt
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
// Felhaszn�l�i beavatkoz�s - billenty�zet haszn�lat - lekezel�se
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
   if( Shift.Contains( ssCtrl ) )
   {
      // CTRL billenty� lenyomva
      // HotKey billenty� lekezel�se
      KeyDownShorcut( Sender, Key );
   }
   else if( !Shift.Contains( ssAlt ) &&
            ((Key >= 65 && Key <= 90) ||
            (Key >= 96 && Key <= 105) ||
            (Key >= 48 && Key <= 57)) )
   {
      // ABC illetve sz�m billenty� lenyomva
      if( Key >= 96 && Key <= 105 )
      {
         // Numpad sz�m billenty� => norm�l sz�m billenty�
         Key -= 48;
      }
      // Adatbe�r�s feldolgoz�sa ha alap �llapotban van
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
            // Ny�l billenty� lenyomva
            // Aktu�lis szol�rium megv�ltoztat�sa
            ActionSzolariumSelect( Key );
            break;

         case VK_ESCAPE:
         {
            // ESC billenty� lenyomva
            // Szol�rium st�tuszt�l f�gg�en ...
            char cStatus = pSzolarium[nCurrentSolarium]->StatuszLekerdezes();
            bool bSteril = pSzolarium[nCurrentSolarium]->StatuszSteril();
            bool bFizetve = !pSzolarium[nCurrentSolarium]->StatuszFizetnikell();
            int nForint = pSzolarium[nCurrentSolarium]->GetForintBarnulas();

            if( (cStatus == STATUS_ALAP && bSteril && bFizetve) ||
                (cStatus == STATUS_VETKOZES && nForint != 0 && !bFizetve ) ||
                (cStatus == STATUS_VETKOZES && nForint == 0 ) )
            {
               // Szol�rium alap �llapotban;
               // Felhaszn�l�i adatainak el�keres�se
               typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
               // Eddigi adatok (b�rlethaszn�lat, forint stb) t�rl�se
               pSzolarium[nCurrentSolarium]->StartReset( stUser );
               pKosar->DeleteKosar( AnsiString(nCurrentSolarium).c_str() );
            }
            break;
         }
         case VK_RETURN:
            // Szol�rium adatait kezel� dial�gus ablak megnyit�sa
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
// "hotkey" billenty�k - CTRL + billenty� lenyom�s�nak lekezel�se
//---------------------------------------------------------------------------
void TFormMain::KeyDownShorcut(TObject *Sender, WORD Key )
{
   switch( Key )
   {
      case 'F':
      case 'f':
         // Szol�riumhaszn�lat kifizetve, Ft �rt�k elt�ntet�se
         MenuMain_PenzKosarClick( Sender );
         break;
      case 'T':
      case 't':
         // Szol�rium v�szle�ll�t�sa
         ToolButtonSzolariumHaltClick( Sender );
         break;
      case 'Z':
      case 'z':
         // Program "lock"-ol�sa
         MenuMain_SystemLogoffClick(Sender);
         break;
      case 'B':
      case 'b':
         // Berlet elad�s
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
         // Szol�rium st�tuszt�l f�gg�en ...
         if( sStatus == STATUS_VETKOZES || sStatus == STATUS_BARNULAS )
         {
            // vetk�z�s megszak�t�sa, szaun�z�s / barnul�s elind�t�sa
            // STOP �llapot lekezel�se
            ToolButtonSzolariumStartClick( Sender );
            // Vetk�z�si szakasz elind�t�sa
            //pSzolarium[nCurrentSolarium]->Inditas();
         }
         else
         {
            // NEM STERIL felirat elt�ntet�se
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
         // Kil�p�s a programb�l
         MenuMain_SystemExitClick( Sender );
         break;
      case VK_F12:
      {
         // Csak ROOT user adatmanipul�l�s
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
// Adatbe�r�s lekezel�se
//---------------------------------------------------------------------------
void TFormMain::KeyDownProcess(TObject *Sender, WORD &Key, TShiftState Shift)
{
   AnsiString strTemp;

   // Aktu�lis szol�rium adataihoz hozz�f�r�s biztos�t�sa
   FormDataRead->pSzolarium = pSzolarium[nCurrentSolarium];
   // A lenyomott billenty� be�r�sa az ablak sz�veg mez�j�be
   FormDataRead->EditAdat->Text = strTemp.StringOfChar( Key, 1 );

   // Adatbeolvas� ablak megnyit�sa
   if( FormDataRead->ShowModal() == mrOk )
   {
      // RENDBEN gomb lenyom�sa eset�n felesleges karakterek kit�rl�se
//      switch( InputDataCheck( FormDataRead->nAction, FormDataRead->EditAdat ) )
      switch( FormDataRead->nAction )
      {
         case ACTION_BARNULASIDO:
            // Barnul�si id� be�rva
            ActionSzolariumIdo( Sender, Key, Shift);
            break;

         case ACTION_VONALKOD:
         {
            // B�rlet / Term�k vonalk�d be�rva

            // Vonalk�d keres�se a b�rletek k�z�tt
            typ_berlet stTemp = pBerletek->GetBerlet( FormDataRead->EditAdat->Text.c_str() );

            if( stTemp.nBerletTipus != 0 )
            {
               // Vonalk�d b�rlethez tartozik
               // B�rlethaszn�lat elind�t�sa
               ActionBerletHasznalat( stTemp );
            }
            else
            {
               // Vonalk�d nem b�rlethez tartozik
               // Vonalk�d keres�se a term�kek k�z�tt
               typ_termek stTermek = pTermek->GetTermekKod( FormDataRead->EditAdat->Text.c_str() );

               if( stTermek.nID != 0 )
               {
                  // Vonalk�d term�khez tartozik
                  // Term�kelad�s elind�t�sa
                  ActionTermekEladas( stTermek );
               }
               else
               {
                  // A be�rt azonos�t� se b�rlet, se term�k
                  Application->MessageBox( FormLanguage->LangStr(STR_MSG_BARCODE_NOTEXISTS).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
               }
            }
            break;
         }/* case ACTION_VONALKOD */
      }/* switch( InputDataCheck ) */
   }/* if( FormDataRead->ShowModal() == mrOk ) */
}
//---------------------------------------------------------------------------
// Be�rt barnul�si id� ellen�rz�se �s a szol�rium felk�sz�t�se
//---------------------------------------------------------------------------
void TFormMain::ActionSzolariumIdo(TObject *Sender, WORD &Key, TShiftState Shift)
{
   // Barnul�si id� kiolvas�sa az adatbe�r�s ablakb�l
   int nBarnulas = FormDataRead->EditAdat->Text.ToInt();
   int nForint = 0;

   // Barnul�si id� kikeres�se az aktu�lis szol�rium Id�/Forint t�bl�zat�b�l
   if( pSzolarium[nCurrentSolarium]->CheckBarnulasIdo( nBarnulas, &nForint ) )
   {
      pSzolarium[nCurrentSolarium]->strLogMsg = AnsiString( "Szol�rium haszn�lat kp. fizet�ssel [" ) +
                                                AnsiString( pSzolarium[nCurrentSolarium]->stAdat.strNev ) +
                                                AnsiString( "] [" ) +
                                                AnsiString( nBarnulas ) +
                                                AnsiString( "] perc [" ) +
                                                convertToCurrencyString( nForint ) +
                                                AnsiString( "] forint [" ) +
                                                AnsiString( pUser->GetUserNev(MainSettings->GetCurrentUser()) ) +
                                                AnsiString( "]" );
      pSzolarium[nCurrentSolarium]->LOG2( pSzolarium[nCurrentSolarium]->strLogMsg );
      // Aktu�lis szol�rium el�k�sz�t�se, barnul�si id� �s forint �rt�k hozz�ad�s
      pSzolarium[nCurrentSolarium]->StartPrepare( nBarnulas*60, nForint );
      // Forint haszn�lat felv�tele a kos�rba
      ActionSzolariumKosarba( nForint );
      // Vetk�z�si szakasz elind�t�sa
      pSzolarium[nCurrentSolarium]->Inditas();
      // Hardware frissitese
      pHardware->LED_Modul[ nCurrentSolarium ].bSendIras = true;
   }
   else
   {
      // Barnul�si id� nem szerepel az aktu�lis szol�rium Id�/Forint t�bl�zat�ban
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_SOLTIME_NOTEXISTS).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      // Adatbeolvas� ablak �jrah�v�sa id�pont megad�ssal "I" bet� az elej�n
      Key = 0;//73; // nem kell az I bet�
      FormKeyDown( Sender, Key, Shift);
   }
}
//---------------------------------------------------------------------------
// B�rlet haszn�lat�nak lekezel�se
//---------------------------------------------------------------------------
void TFormMain::ActionBerletHasznalat( typ_berlet stBerlet )
{
   // Hozz�f�r�s a b�rletek adatb�zis�hoz
   FormBerletHasznalat->pBerlet = pBerletek;
   // Adott b�rlet adatainak �tad�sa
   FormBerletHasznalat->stBerlet = stBerlet;
   // Registry olvas�shoz
   FormBerletHasznalat->pMainSettings = MainSettings;
   // B�rlethaszn�lat ablak megnyit�sa
   if( FormBerletHasznalat->ShowModal() == mrOk )
   {
      // Nincs megadva m�g PIN k�d a b�rlethez
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
      // Felhaszn�land� egys�g kiolvas�sa a b�rlethaszn�lat ablakb�l
      int nBarnulas = 0;
      int nEgyseg = FormBerletHasznalat->ComboBoxHasznalat->ItemIndex+1;

      // Barnul�si id� kikeres�se az aktu�lis szol�rium Id�/Forint t�bl�zat�b�l
//      if( pSzolarium[nCurrentSolarium]->GetBarnulasIdo( nEgyseg, &nBarnulas ) )

      // Barnul�si id� el�szed�se a b�rlett�pusb�l
      typ_berlettipus stBerletTipus;

      memset( &stBerletTipus, 0, sizeof(typ_berlettipus) );
      stBerletTipus = pBerletek->GetBerletTipusID( stBerlet.nBerletTipus );

      // Ha a barnul�si egys�gid� nincs megadva, akkor nem lesz b�rlethaszn�lat
      if( stBerletTipus.nEgysegIdo > 0 )
      {
         nBarnulas = nEgyseg * stBerletTipus.nEgysegIdo;

         pSzolarium[nCurrentSolarium]->strLogMsg = AnsiString( "Szol�rium haszn�lat b�rlettel [" ) +
                                                   AnsiString( pSzolarium[nCurrentSolarium]->stAdat.strNev ) +
                                                   AnsiString( "] [" ) +
                                                   AnsiString( nBarnulas ) +
                                                   AnsiString( "] perc [" ) +
                                                   AnsiString( stBerlet.strVonalkod ) +
                                                   AnsiString( "] b�rlet [" ) +
                                                   AnsiString( nEgyseg ) +
                                                   AnsiString( "] egys�g [" ) +
                                                   AnsiString( pUser->GetUserNev(MainSettings->GetCurrentUser()) ) +
                                                   AnsiString( "]" );
         pSzolarium[nCurrentSolarium]->LOG2( pSzolarium[nCurrentSolarium]->strLogMsg );
         // Aktu�lis szol�rium el�k�sz�t�se, b�rlet, barnul�si id� hozz�ad�s
         pSzolarium[nCurrentSolarium]->StartPrepare( stBerlet, nBarnulas*60, nEgyseg );
         // Felhaszn�land� egys�gek levon�sa a b�rletr�l
         pBerletek->DecreaseBerletEgyseg( stBerlet.strVonalkod, nEgyseg );
         // Vetk�z�si szakasz elind�t�sa
         pSzolarium[nCurrentSolarium]->Inditas();
         // Hardware frissitese
         pHardware->LED_Modul[ nCurrentSolarium ].bSendIras = true;
      }
      else
      {
         // Hi�nyzik a szol�rium Id�/Forint t�bl�zat adott eleme
         Application->MessageBox( FormLanguage->LangStr(STR_MSG_TIMETABLE_EMPTY).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      }
   }
}
//---------------------------------------------------------------------------
// Term�k elad�s�nak lekezel�se
//---------------------------------------------------------------------------
void TFormMain::ActionTermekEladas( typ_termek stTermek )
{
   // Term�k adatainak �tad�sa a term�kelad�st kezel� ablaknak
   FormTermekEladas->stTermek = stTermek;

   // Term�kelad�st kezel� ablak megnyit�sa
   switch( FormTermekEladas->ShowModal() )
   {
      case mrOk:
      {
         // K�szp�nz fizet�s azonnal
         // Fizet�st kezel� ablakban Kos�rba gomb enged�lyez�se
         FormFizetes->BitBtnKosar->Enabled = true;
         // P�nz�sszeg �tad�sa a Fizet�st kezel� ablaknak
         FormFizetes->LabelFizetendo->Caption = FormTermekEladas->EditFizetendo->Text;
         // Fizet�st kezel� ablak megnyit�sa
         switch( FormFizetes->ShowModal() )
         {
            case mrOk:
            {
               // Kifizetve gomb megnyomva
               pKonyv->AddGeneralKonyv( MainSettings->GetCurrentMuszak(),
                                        0,
                                        FormTermekEladas->EditFizetendo->Text.ToDouble(),
                                        "" );
               // eladott term�ket adott mennyis�ggel
               // cs�kkenteni a term�k adatb�zisban
               ActionTermekDarabCsokkentes();

               // Felhaszn�l�i adatainak el�keres�se
               typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
               // Megjegyz�s felt�lt�se a term�k adattal
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
               // Bev�tel hozz�ad�sa a p�nzt�rhoz
               pPenztar->PenztarBevetel( stUser, FormTermekEladas->EditFizetendo->Text.ToInt(), strTemp.c_str() );
               break;
            }
            case mrYes:
               // Kos�rba gomb megnyomva
               // Term�k felv�tele a kos�rba
               ActionTermekKosarba();
               // eladott term�ket adott mennyis�ggel
               // cs�kkenteni a term�k adatb�zisban
               ActionTermekDarabCsokkentes();
               break;
         }
         break;
      }
      case mrYes:
      {
         // Kos�rba gomb megnyomva
         // Term�k felv�tele a kos�rba
         ActionTermekKosarba();
         // eladott term�ket adott mennyis�ggel
         // cs�kkenteni a term�k adatb�zisban
         ActionTermekDarabCsokkentes();
         break;
      }
   }
}
//---------------------------------------------------------------------------
// B�rlet felv�tele kos�rba
//---------------------------------------------------------------------------
void TFormMain::ActionBerletKosarba()
{
   typ_kosar stKosar;

   memset( &stKosar, 0, sizeof(typ_kosar) );

   // Egyedi azonos�t� kisz�mol�sa
   stKosar.nID = pKosar->GetKosarCount()+1;
   // Kos�relem t�pusa: 0 -> b�rlet
   stKosar.nTipus = 0;
   // Adatok �tad�sa a B�rletelad�s ablakb�l a kos�rnak
   strncpy( stKosar.strVonalkod, FormBerletEladas->EditVonalkod->Text.c_str(), sizeof(stKosar.strVonalkod)-2 );
   strcpy( stKosar.strNev, FormBerletEladas->ComboBoxTipus->Items->Strings[FormBerletEladas->ComboBoxTipus->ItemIndex].c_str() );
   stKosar.nAr = convertCurrency(FormBerletEladas->EditBTAr->Text.ToDouble());
   stKosar.nDarab = 1;
   // B�rlet felv�tele a kos�rba
   pKosar->AddKosar( stKosar );
}
//---------------------------------------------------------------------------
// Term�k felv�tele a kos�rba
//---------------------------------------------------------------------------
void TFormMain::ActionTermekKosarba()
{
   typ_kosar stKosar;

   memset( &stKosar, 0, sizeof(typ_kosar) );

   // Egyedi azonos�t� kisz�mol�sa
   stKosar.nID = pKosar->GetKosarCount()+1;
   // Kos�relem t�pusa: 1 -> term�k
   stKosar.nTipus = 1;
   // Adatok �tad�sa a Term�kelad�s ablakb�l a kos�rnak
   strncpy( stKosar.strVonalkod, FormTermekEladas->EditVonalkod->Text.c_str(), sizeof(stKosar.strVonalkod)-2 );
   strncpy( stKosar.strNev, FormTermekEladas->EditNev->Text.c_str(), sizeof(stKosar.strNev)-2 );
   stKosar.nAr = convertCurrency(FormTermekEladas->EditAr->Text.ToDouble());
   stKosar.nDarab = FormTermekEladas->ComboBoxDarab->Items->Strings[FormTermekEladas->ComboBoxDarab->ItemIndex].ToInt();
   // Term�k felv�tele a kos�rba
   pKosar->AddKosar( stKosar );
}
//---------------------------------------------------------------------------
// Szol�rium forint haszn�lat felv�tele a kos�rba
//---------------------------------------------------------------------------
void TFormMain::ActionSzolariumKosarba( int nForint )
{
   typ_kosar stKosar;

   memset( &stKosar, 0, sizeof(typ_kosar) );

   // Egyedi azonos�t� kisz�mol�sa
   stKosar.nID = pKosar->GetKosarCount()+1;
   // Kos�relem t�pusa: 2 -> szol�rium
   stKosar.nTipus = 2;
   // Adatok �tad�sa a kos�rnak
   strcpy( stKosar.strVonalkod, AnsiString(nCurrentSolarium).c_str() );
   strcpy( stKosar.strNev, pSzolarium[nCurrentSolarium]->stAdat.strNev );
   stKosar.nAr = nForint;
   stKosar.nDarab = 1;
   // Szol�rium forint haszn�lat felv�tele a kos�rba
   pKosar->AddKosar( stKosar );
}
//---------------------------------------------------------------------------
// Term�k felv�tele a kos�rba
//---------------------------------------------------------------------------
void TFormMain::ActionTermekListaKosarba()
{
   typ_kosar stKosar;

   memset( &stKosar, 0, sizeof(typ_kosar) );

   // Egyedi azonos�t� kisz�mol�sa
   stKosar.nID = pKosar->GetKosarCount()+1;
   // Kos�relem t�pusa: 1 -> term�k
   stKosar.nTipus = 1;
   // Adatok �tad�sa a Term�kelad�s ablakb�l a kos�rnak
   strncpy( stKosar.strVonalkod, FormTermekListaEladas->EditVonalkod->Text.c_str(), sizeof(stKosar.strVonalkod)-2 );
   strncpy( stKosar.strNev, FormTermekListaEladas->EditNev->Text.c_str(), sizeof(stKosar.strNev)-2 );
   stKosar.nAr = convertCurrency(FormTermekListaEladas->EditAr->Text.ToDouble());
   stKosar.nDarab = FormTermekListaEladas->ComboBoxDarab->Items->Strings[FormTermekListaEladas->ComboBoxDarab->ItemIndex].ToInt();
   // Term�k felv�tele a kos�rba
   pKosar->AddKosar( stKosar );
}
//---------------------------------------------------------------------------
// Term�k elad�sakor (kos�rba rak�sakor) a term�kek sz�m�nak rakt�rban cs�kkent�se
//---------------------------------------------------------------------------
void TFormMain::ActionTermekDarabCsokkentes()
{
   DWORD nID = FormTermekEladas->EditID->Text.ToDouble();
   int nDarab = FormTermekEladas->ComboBoxDarab->Items->Strings[FormTermekEladas->ComboBoxDarab->ItemIndex].ToInt();
   int nCurrDarab = pTermek->GetTermekDarab( nID );

   pTermek->SetTermekDarab( nID, nCurrDarab-nDarab );
}
//---------------------------------------------------------------------------
// Term�k elad�sakor (kos�rba rak�sakor) a term�kek sz�m�nak rakt�rban cs�kkent�se
//---------------------------------------------------------------------------
void TFormMain::ActionTermekListaDarabCsokkentes()
{
   DWORD nID = FormTermekListaEladas->EditID->Text.ToDouble();
   int nDarab = FormTermekListaEladas->ComboBoxDarab->Items->Strings[FormTermekListaEladas->ComboBoxDarab->ItemIndex].ToInt();
   int nCurrDarab = pTermek->GetTermekDarab( nID );

   pTermek->SetTermekDarab( nID, nCurrDarab-nDarab );
}
//---------------------------------------------------------------------------
// Aktu�lis szol�rium kiv�laszt�sa a ny�l gombok seg�ts�g�vel
//---------------------------------------------------------------------------
void TFormMain::ActionSzolariumSelect( WORD Key )
{
   switch( Key )
   {
      // Aktu�lis szol�rium megjel�l�s�nek visszavon�sa
      case VK_LEFT:
      case VK_RIGHT:
      case VK_UP:
      case VK_DOWN:
         pSzolarium[nCurrentSolarium]->Deselect();
         break;
   }
   switch( Key )
   {
      // �jonnan kiv�lasztand� szol�rium megkeres�se
      case VK_LEFT:
         // Balra mozg�s eset�n
         if( nCurrentSolarium%nCountColumn == 0 )
            nCurrentSolarium += nCountColumn;
         nCurrentSolarium--;
         break;

      case VK_RIGHT:
         // Jobbra mozg�s eset�n
         nCurrentSolarium++;
         if( nCurrentSolarium%nCountColumn == 0 )
            nCurrentSolarium -= nCountColumn;
         else if( nCurrentSolarium == MainSettings->GetCountSolarium() )
            nCurrentSolarium -= nCurrentSolarium%nCountColumn;
         break;

      case VK_UP:
         // Felfel� mozg�s eset�n
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
         // Lefel� mozg�s eset�n
         if( nCurrentSolarium+nCountColumn > MainSettings->GetCountSolarium()-1 )
            nCurrentSolarium = nCurrentSolarium%nCountColumn;
         else
            nCurrentSolarium += nCountColumn;
         break;
   }
   switch( Key )
   {
      // �j aktu�lis szol�rium megjel�l�se
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
// Eg�r gomblenyom�s eset�n aktu�lis szol�rium kiv�laszt�sa
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TPanel *temppanel;
   TLabel *templabel;

   if( Sender->ClassNameIs( "TLabel" ) )
   {
      // Ha az eg�r kattint�s nem a szol�rium panelj�ra esett
      // akkor egy feliratra -> sz�l� panelre mutat� pointer megszerz�se
      templabel = (TLabel*)Sender;
      temppanel = (TPanel*)templabel->Parent;
   }
   else if( Sender->ClassNameIs( "TPanel" ) )
   {
      // Ha az eg�r kattint�s a szol�rium panelj�ra esett
      // panelre mutat� pointer megszerz�se
      temppanel = (TPanel*)Sender;
   }
   else
      return;

   // Aktu�lis szol�rium megjel�l�s�nek visszavon�sa
   pSzolarium[nCurrentSolarium]->Deselect();
   // �jonnan kiv�lasztand� szol�rium megkeres�se a panel alapj�n
   nCurrentSolarium = temppanel->TabOrder-2;
   // �j aktu�lis szol�rium megjel�l�se
   pSzolarium[nCurrentSolarium]->Select();
}
//---------------------------------------------------------------------------
// Eg�r dupla kattint�s lekezel�se: aktu�lis szol�rium adatait kezel�
// ablak megnyit�sa
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDblClick(TObject *Sender)
{
//   MenuMain_SettingSzolariumClick(Sender);
}
//---------------------------------------------------------------------------

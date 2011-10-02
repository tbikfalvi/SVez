//---------------------------------------------------------------------------

#include <vcl.h>

#include "SzolariumMain.h"
#include "BerletEladas.h"
#include "Fizetes.h"
#include "TermekListaEladas.h"
#include "Kosar.h"
#include "ExtendedViewer.h"
//---------------------------------------------------------------------------

/****************************************************************************
*
* TOOLBAR GOMBOK LEKEZELESE
*
****************************************************************************/

//---------------------------------------------------------------------------
// Szolárium szauna, barnulás, utóhûtés szakasz leállítása és a következõ
// szakaszba léptetés
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonSzolariumHaltClick(TObject *Sender)
{
   // Felhasználói adatainak elõkeresése
   typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
   pSzolarium[nCurrentSolarium]->Veszleallitas( stUser );
}
//---------------------------------------------------------------------------
// Szolárium indítás gomb (START felirat szoláriumon)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonSzolariumStartClick(TObject *Sender)
{
   char sStatus = pSzolarium[nCurrentSolarium]->StatuszLekerdezes();

   if( sStatus == STATUS_VETKOZES )
   {
      // Vetkõzés megszakítása, következõ ciklus indítása
      pSzolarium[nCurrentSolarium]->StatuszVetkozesStop();
   }
   else if( sStatus == STATUS_BARNULAS && pSzolarium[nCurrentSolarium]->bStopped )
   {
      pSzolarium[nCurrentSolarium]->bStopped = false;
      pHardware->LED_Modul[ nCurrentSolarium ].bStop = false;
   }
}
//---------------------------------------------------------------------------
// NEM STERIL felirat eltüntetése
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonSzolariumSterilClick(TObject *Sender)
{
   pSzolarium[nCurrentSolarium]->Steril();
}
//---------------------------------------------------------------------------
// Bérleteladás folyamat
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonBerletEladasClick(TObject *Sender)
{
   if( pBerletek->GetBerletTipusCount() == 0 )
   {
      if( Application->MessageBox( "A rendszerben nincs bérlettípus tárolva.\n"
                                   "Bérlettípus hiányában nem lehet bérletet eladni.\n\n"
                                   "Létrehoz most új bérlettípust?",
                                   "Figyelmeztetés",
                                   MB_ICONEXCLAMATION|MB_YESNO|MB_DEFBUTTON1 ) == IDYES )
      {
         MenuMain_SettingsBerletekClick( Sender );
      }
   }
   if( pBerletek->GetBerletTipusCount() > 0 )
   {
      FormBerletEladas->pBerlet = pBerletek;
      FormBerletEladas->pTermek = pTermek;
      FormBerletEladas->pMainSettings = MainSettings;
      switch( FormBerletEladas->ShowModal() )
      {
         case mrOk:
            FormFizetes->BitBtnKosar->Enabled = true;
            FormFizetes->LabelFizetendo->Caption = FormBerletEladas->EditBTAr->Text;
            switch( FormFizetes->ShowModal() )
            {
               case mrOk:
               {
                  // Kifizetve gomb megnyomva
                  // pénzbevétel könyvelés
                  pKonyv->AddGeneralKonyv( MainSettings->GetCurrentMuszak(),
                                           FormBerletEladas->EditBTAr->Text.ToDouble(),
                                           0,
                                           "" );
                  // Felhasználói adatainak elõkeresése
                  typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
                  // Megjegyzés feltöltése a bérlet típusával
                  AnsiString strTemp = FormBerletEladas->ComboBoxTipus->Text;
                  // Bevétel hozzáadása a pénztárhoz felhasználó rögzítése nélkül
                  pPenztar->PenztarBevetel( stUser, FormBerletEladas->EditBTAr->Text.ToInt(), strTemp.c_str() );
                  pPenztar->strLogMsg = AnsiString( "Berlet eladas [" ) +
                                        AnsiString( FormBerletEladas->EditVonalkod->Text ) +
                                        AnsiString( "] user [" ) +
                                        AnsiString( pUser->GetUserNev(MainSettings->GetCurrentUser()) ) +
                                        AnsiString( "]" );
                  pPenztar->LOG2( pPenztar->strLogMsg );
                  break;
               }
               case mrYes:
                  // Kosarba
                  ActionBerletKosarba();
                  break;
               case mrCancel:
                  // Bérlet törlése az adatbázisból
                  pBerletek->DeleteBerlet( FormBerletEladas->EditVonalkod->Text.c_str(), true );
                  break;
            }
            break;

         case mrYes:
            // Kosarba
            ActionBerletKosarba();
            break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonTermekEladasClick(TObject *Sender)
{
   FormTermekListaEladas->pTermek = pTermek;
   FormTermekListaEladas->bFizetesEnabled = true;
   // Termékeladást kezelõ ablak megnyitása
   switch( FormTermekListaEladas->ShowModal() )
   {
      case mrOk:
      {
         // Készpénz fizetés azonnal
         // Fizetést kezelõ ablakban Kosárba gomb engedélyezése
         FormFizetes->BitBtnKosar->Enabled = true;
         // Pénzösszeg átadása a Fizetést kezelõ ablaknak
         FormFizetes->LabelFizetendo->Caption = FormTermekListaEladas->EditFizetendo->Text;
         // Fizetést kezelõ ablak megnyitása
         switch( FormFizetes->ShowModal() )
         {
            case mrOk:
            {
               // Kifizetve gomb megnyomva
               // pénzbevétel könyvelés
               pKonyv->AddGeneralKonyv( MainSettings->GetCurrentMuszak(),
                                        0,
                                        FormTermekListaEladas->EditFizetendo->Text.ToDouble(),
                                        "" );
               // eladott terméket adott mennyiséggel
               // csökkenteni a termék adatbázisban
               ActionTermekListaDarabCsokkentes();
               // Felhasználói adatainak elõkeresése
               typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
               // Megjegyzés feltöltése a termék adattal
               AnsiString strTemp = FormTermekListaEladas->ComboBoxDarab->Text +
                                    AnsiString( " db. " ) +
                                    FormTermekListaEladas->EditNev->Text;
               pPenztar->strLogMsg = AnsiString( "Termek eladas kosarbol [" ) +
                                     AnsiString( FormTermekListaEladas->EditVonalkod->Text ) +
                                     AnsiString( "/" ) +
                                     AnsiString( FormTermekListaEladas->EditAr->Text ) +
                                     AnsiString( "/" ) +
                                     AnsiString( FormTermekListaEladas->ComboBoxDarab->Text ) +
                                     AnsiString( "]" );
               pPenztar->LOG2( pPenztar->strLogMsg );
               // Bevétel hozzáadása a pénztárhoz felhasználó rögzítése nélkül
               pPenztar->PenztarBevetel( stUser, FormTermekListaEladas->EditFizetendo->Text.ToInt(), strTemp.c_str() );
               break;
            }
            case mrYes:
               // Kosárba gomb megnyomva
               // Termék felvétele a kosárba
               ActionTermekListaKosarba();
               // eladott terméket adott mennyiséggel
               // csökkenteni a termék adatbázisban
               ActionTermekListaDarabCsokkentes();
               break;
         }
         break;
      }
      case mrYes:
      {
         // Kosárba gomb megnyomva
         // Termék felvétele a kosárba
         ActionTermekListaKosarba();
         // eladott terméket adott mennyiséggel
         // csökkenteni a termék adatbázisban
         ActionTermekListaDarabCsokkentes();
         break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonSzolariumIdoClick(TObject *Sender)
{
   WORD        Key = 0; //73; // I
   TShiftState Shift;

   KeyDownProcess(Sender, Key, Shift);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonSzolariumBerletClick(TObject *Sender)
{
   WORD        Key = 0; //66; // B
   TShiftState Shift;

   KeyDownProcess(Sender, Key, Shift);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonUserLogoffClick(TObject *Sender)
{
   MenuMain_SystemLogoffClick(Sender);
}
//---------------------------------------------------------------------------

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
// Szol�rium szauna, barnul�s, ut�h�t�s szakasz le�ll�t�sa �s a k�vetkez�
// szakaszba l�ptet�s
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonSzolariumHaltClick(TObject *Sender)
{
   // Felhaszn�l�i adatainak el�keres�se
   typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
   pSzolarium[nCurrentSolarium]->Veszleallitas( stUser );
}
//---------------------------------------------------------------------------
// Szol�rium ind�t�s gomb (START felirat szol�riumon)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonSzolariumStartClick(TObject *Sender)
{
   char sStatus = pSzolarium[nCurrentSolarium]->StatuszLekerdezes();

   if( sStatus == STATUS_VETKOZES )
   {
      // Vetk�z�s megszak�t�sa, k�vetkez� ciklus ind�t�sa
      pSzolarium[nCurrentSolarium]->StatuszVetkozesStop();
   }
   else if( sStatus == STATUS_BARNULAS && pSzolarium[nCurrentSolarium]->bStopped )
   {
      pSzolarium[nCurrentSolarium]->bStopped = false;
      pHardware->LED_Modul[ nCurrentSolarium ].bStop = false;
   }
}
//---------------------------------------------------------------------------
// NEM STERIL felirat elt�ntet�se
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonSzolariumSterilClick(TObject *Sender)
{
   pSzolarium[nCurrentSolarium]->Steril();
}
//---------------------------------------------------------------------------
// B�rletelad�s folyamat
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonBerletEladasClick(TObject *Sender)
{
   if( pBerletek->GetBerletTipusCount() == 0 )
   {
      if( Application->MessageBox( "A rendszerben nincs b�rlett�pus t�rolva.\n"
                                   "B�rlett�pus hi�ny�ban nem lehet b�rletet eladni.\n\n"
                                   "L�trehoz most �j b�rlett�pust?",
                                   "Figyelmeztet�s",
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
                  // p�nzbev�tel k�nyvel�s
                  pKonyv->AddGeneralKonyv( MainSettings->GetCurrentMuszak(),
                                           FormBerletEladas->EditBTAr->Text.ToDouble(),
                                           0,
                                           "" );
                  // Felhaszn�l�i adatainak el�keres�se
                  typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
                  // Megjegyz�s felt�lt�se a b�rlet t�pus�val
                  AnsiString strTemp = FormBerletEladas->ComboBoxTipus->Text;
                  // Bev�tel hozz�ad�sa a p�nzt�rhoz felhaszn�l� r�gz�t�se n�lk�l
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
                  // B�rlet t�rl�se az adatb�zisb�l
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
   // Term�kelad�st kezel� ablak megnyit�sa
   switch( FormTermekListaEladas->ShowModal() )
   {
      case mrOk:
      {
         // K�szp�nz fizet�s azonnal
         // Fizet�st kezel� ablakban Kos�rba gomb enged�lyez�se
         FormFizetes->BitBtnKosar->Enabled = true;
         // P�nz�sszeg �tad�sa a Fizet�st kezel� ablaknak
         FormFizetes->LabelFizetendo->Caption = FormTermekListaEladas->EditFizetendo->Text;
         // Fizet�st kezel� ablak megnyit�sa
         switch( FormFizetes->ShowModal() )
         {
            case mrOk:
            {
               // Kifizetve gomb megnyomva
               // p�nzbev�tel k�nyvel�s
               pKonyv->AddGeneralKonyv( MainSettings->GetCurrentMuszak(),
                                        0,
                                        FormTermekListaEladas->EditFizetendo->Text.ToDouble(),
                                        "" );
               // eladott term�ket adott mennyis�ggel
               // cs�kkenteni a term�k adatb�zisban
               ActionTermekListaDarabCsokkentes();
               // Felhaszn�l�i adatainak el�keres�se
               typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
               // Megjegyz�s felt�lt�se a term�k adattal
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
               // Bev�tel hozz�ad�sa a p�nzt�rhoz felhaszn�l� r�gz�t�se n�lk�l
               pPenztar->PenztarBevetel( stUser, FormTermekListaEladas->EditFizetendo->Text.ToInt(), strTemp.c_str() );
               break;
            }
            case mrYes:
               // Kos�rba gomb megnyomva
               // Term�k felv�tele a kos�rba
               ActionTermekListaKosarba();
               // eladott term�ket adott mennyis�ggel
               // cs�kkenteni a term�k adatb�zisban
               ActionTermekListaDarabCsokkentes();
               break;
         }
         break;
      }
      case mrYes:
      {
         // Kos�rba gomb megnyomva
         // Term�k felv�tele a kos�rba
         ActionTermekListaKosarba();
         // eladott term�ket adott mennyis�ggel
         // cs�kkenteni a term�k adatb�zisban
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

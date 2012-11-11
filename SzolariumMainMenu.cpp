//---------------------------------------------------------------------------

#include <vcl.h>
#include <Filectrl.hpp>

#include "SzolariumMain.h"
#include "SzolariumAdat.h"
#include "PasswordChange.h"
#include "SystemSettings.h"
#include "PasswordCheck.h"
#include "BerletKezeles.h"
#include "TermekKezeles.h"
#include "HelpAbout.h"
#include "Lista.h"
#include "DialogComment.h"
#include "UserKezeles.h"
#include "Kosar.h"
#include "Fizetes.h"
#include "PenztarKezeles.h"
#include "HardwareTeszt.h"
#include "DialogSelectDir.h"
#include "AdatbazisKezeles.h"
#include "ExtendedViewer.h"
#include "Language.h"
#include "TermekTipusKezeles.h"

//---------------------------------------------------------------------------
// Összes adat mentése archiváláshoz
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SystemSaveClick(TObject *Sender)
{
   AnsiString  strDirectory;
   AnsiString  strFilename;
   AnsiString  strCurrDir = GetCurrentDir();

   if( FormDialogSelectDir->ShowModal() == mrOk )
   {
      strDirectory = FormDialogSelectDir->DirectoryListBox->Directory +
                     AnsiString( "\\" ) +
                     FormatDateTime("yyyy_mm_dd",Now());
      MainSettings->strLogMsg = AnsiString( "Adatbázis mentése [" ) +
                                strDirectory +
                                AnsiString( "] [" ) +
                                AnsiString( MainSettings->GetCurrentUser() ) +
                                AnsiString( "]" );
      MainSettings->LOG2( MainSettings->strLogMsg );
      if( !DirectoryExists(strDirectory) )
      {
         if( !CreateDir(strDirectory) )
         {
            Application->MessageBox( FormLanguage->LangStr(STR_ERR_UNABLE_CREATE_ARCHIVE).c_str(), FormLanguage->LangStr(STR_MSGBOX_ERROR).c_str(), MB_ICONHAND );
            return;
         }
      }
      SetCurrentDir( strCurrDir );
      pBerletek->SaveBerlet( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), BERLET_FILE ).c_str() );
//      CopyFile( BERLET_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), BERLET_FILE ).c_str(), false );
      pBerletek->SaveBerlethasznalat( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), BERLETHASZNALAT_FILE ).c_str() );
//      CopyFile( BERLETHASZNALAT_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), BERLETHASZNALAT_FILE ).c_str(), false );
      pBerletek->SaveBerlettipus( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), BERLETTIPUS_FILE ).c_str() );
//      CopyFile( BERLETTIPUS_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), BERLETTIPUS_FILE ).c_str(), false );
      pKonyv->SaveGeneralKonyv( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), KONYVGENERAL_FILE ).c_str() );
//      CopyFile( KONYVGENERAL_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), KONYVGENERAL_FILE ).c_str(), false );
      pKosar->SaveDataToFile( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), KOSAR_FILE ).c_str() );
//      CopyFile( KOSAR_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), KOSAR_FILE ).c_str(), false );
      MainSettings->SaveSettingsToFile( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), SETTINGS_FILE ).c_str() );
//      CopyFile( SETTINGS_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), SETTINGS_FILE ).c_str(), false );
      pPenztar->SaveDataToFile( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), PENZTAR_FILE ).c_str() );
//      CopyFile( PENZTAR_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), PENZTAR_FILE ).c_str(), false );
      pPenztar->SavePenztarActions( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), PENZTARLOG_FILE ).c_str() );
//      CopyFile( PENZTARLOG_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), PENZTARLOG_FILE ).c_str(), false );
      for( int i=0; i<MainSettings->GetCountSolarium(); i++ )
      {
         AnsiString  strFilename1;
         strFilename1 = strFilename1.sprintf( "%s%d.dat", SOLARIUM_FILE, i );
         strFilename = strFilename.sprintf( "%s\\%s%d.dat", strDirectory.c_str(), SOLARIUM_FILE );
         pSzolarium[i]->SaveDataToFile( strFilename.c_str() );
//         CopyFile( strFilename1.c_str(), strFilename.c_str(), false );
      }
      pKonyv->SaveSolariumKonyv( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), KONYVSZOLARIUM_FILE ).c_str() );
//      CopyFile( KONYVSZOLARIUM_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), KONYVSZOLARIUM_FILE ).c_str(), false );
      pUser->SaveDataToFile( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), USER_FILE ).c_str() );
//      CopyFile( USER_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), USER_FILE ).c_str(), false );
      pTermek->SaveDataToFile( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), TERMEK_FILE ).c_str() );
//      CopyFile( TERMEK_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), TERMEK_FILE ).c_str(), false );
      pTermekTipus->SaveDataToFile( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), TERMEKTIPUS_FILE ).c_str() );
//      CopyFile( TERMEKTIPUS_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), TERMEKTIPUS_FILE ).c_str(), false );
      pTermekTipus->SaveDataToFileAsg( strFilename.sprintf( "%s\\%s", strDirectory.c_str(), TERMEKTIPUSASG_FILE ).c_str() );
//      CopyFile( TERMEKTIPUSASG_FILE, strFilename.sprintf( "%s\\%s", strDirectory.c_str(), TERMEKTIPUSASG_FILE ).c_str(), false );
   }
}
//---------------------------------------------------------------------------
// Mûszak zárása
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SystemSessioncloseClick(TObject *Sender)
{
   AnsiString strMegjegyzes = FormLanguage->LangStr(STR_USER) +
                              AnsiString( ": " ) +
                              AnsiString( pUser->GetUserNev(MainSettings->GetCurrentUser()) ) +
                              AnsiString( " - " );
   if( FormCommentDialog->ShowModal() == mrOk )
   {
      strMegjegyzes += AnsiString( " " ) + AnsiString( FormCommentDialog->strMegjegyzes );
      pKonyv->AddGeneralKonyv( MainSettings->GetCurrentMuszak(),
                               0,
                               0,
                               strMegjegyzes.c_str() );
   }
   else
   {
      strMegjegyzes += AnsiString( " " ) + FormLanguage->LangStr(STR_MSG_SESSION_CLOSE);
      pKonyv->AddGeneralKonyv( MainSettings->GetCurrentMuszak(),
                               0,
                               0,
                               strMegjegyzes.c_str() );
   }
   MainSettings->strLogMsg = AnsiString( "Muszakzaras: muszak [" ) +
                             AnsiString( MainSettings->GetCurrentMuszak() ) +
                             AnsiString( "] user [" ) +
                             AnsiString( pUser->GetUserNev(MainSettings->GetCurrentUser()) ) +
                             AnsiString( "]" );
   MainSettings->LOG2( MainSettings->strLogMsg );
   MainSettings->MuszakZaras();
   for( int i=0; i<MainSettings->GetCountSolarium(); i++ )
   {
      pSzolarium[i]->dCurrentMuszak = MainSettings->GetCurrentMuszak();
      pKonyv->AddSzolariumKonyv( MainSettings->GetCurrentMuszak(), i, 0, 0, 0, 0, 0, 0, 0, pSzolarium[i]->stAdat.strNev );
   }
}
//---------------------------------------------------------------------------
// Felhasználó kilépése, jelszókérõ ablak megjelenítése timer-el
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SystemLogoffClick(TObject *Sender)
{
   MainSettings->strLogMsg = AnsiString( "Logoff user [" ) +
                             AnsiString( pUser->GetUserNev(MainSettings->GetCurrentUser()) ) +
                             AnsiString( "]" );
   MainSettings->LOG2( MainSettings->strLogMsg );
   TimerUserLock->Interval = 100;
   TimerUserLock->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SystemExitClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingVideoSize2Click(TObject *Sender)
{
   Width = 1024;
   Height = 768;
   FormExtendedViewer->Width = 1024;
   FormExtendedViewer->Height = 768;
   Position = poScreenCenter;
   MenuMain_SettingVideoSize2->Checked = true;
   MenuMain_SettingVideoSize3->Checked = false;
   MenuMain_SettingVideoSize4->Checked = false;
   StatusBar->Panels->Items[0]->Width = 824;
   ResizePanels();
   MainSettings->SaveApplicationParameters( Left, Top, 2 );
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingVideoSize3Click(TObject *Sender)
{
   Width = 1280;
   Height = 768;
   FormExtendedViewer->Width = 1280;
   FormExtendedViewer->Height = 768;
   Position = poScreenCenter;
   MenuMain_SettingVideoSize2->Checked = false;
   MenuMain_SettingVideoSize3->Checked = true;
   MenuMain_SettingVideoSize4->Checked = false;
   StatusBar->Panels->Items[0]->Width = 1080;
   ResizePanels();
   MainSettings->SaveApplicationParameters( Left, Top, 3 );
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingVideoSize4Click(TObject *Sender)
{
   Width = 1280;
   Height = 960;
   FormExtendedViewer->Width = 1280;
   FormExtendedViewer->Height = 960;
   Position = poScreenCenter;
   MenuMain_SettingVideoSize2->Checked = false;
   MenuMain_SettingVideoSize3->Checked = false;
   MenuMain_SettingVideoSize4->Checked = true;
   StatusBar->Panels->Items[0]->Width = 1080;
   ResizePanels();
   MainSettings->SaveApplicationParameters( Left, Top, 4 );
}
//---------------------------------------------------------------------------
// Szolárium panelok méretének frissítése
//---------------------------------------------------------------------------
void TFormMain::ResizePanels()
{
   for(int y=0,i=0;y<nCountRow&&i<(int)pSzolarium.size();y++)
   {
      for(int x=0;x<nCountColumn&&i<(int)pSzolarium.size();x++)
      {
         pSzolarium[i]->Resize( x*(ClientWidth/nCountColumn),
                                y*((ClientHeight-82)/nCountRow)+51,
                                (ClientWidth/nCountColumn),
                                ((ClientHeight-82)/nCountRow) );
         i++;
      }
   }
}
//---------------------------------------------------------------------------
// Szolárium adatait kezelõ dialógus ablak megnyitása
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingSzolariumClick(TObject *Sender)
{
   int   nRet = mrOk;
   typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );

   if( stUser.nUserLevel < ACCESS_ADMIN )
   {
      FormPasswordCheck->pUser = pUser;
      FormPasswordCheck->AccessLevel = ACCESS_ADMIN;
      FormPasswordCheck->EditCurrentUser->Text = AnsiString( MainSettings->GetCurrentUser() );
      nRet = FormPasswordCheck->ShowModal();
   }
   if( nRet == mrOk )
   {
      // Aktuális szolárium státuszának lekérdezése
      if( pSzolarium[nCurrentSolarium]->StatuszLekerdezes() != STATUS_ALAP )
      {
         // Szolárium nem alapállapotban van; adatkezelés megtagadása; státuszsorban infó
         StatusBar->Panels->Items[0]->Text = FormLanguage->LangStr(STR_ERR_UNABLE_DATAMOD);
      }
      else
      {
         // Adatkezelõ ablaknak az aktuális szolárium adatai átadása
         FormSzolariumAdat->FillControlsWithData( pSzolarium[nCurrentSolarium]->stAdat );
         // Adatkezelõ ablak megnyitása
         if( FormSzolariumAdat->ShowModal() == mrOk )
         {
            MainSettings->strLogMsg = AnsiString( "Szolarium adatmod: szoli [" ) +
                                      AnsiString( nCurrentSolarium ) +
                                      AnsiString( "] user [" ) +
                                      AnsiString( pUser->GetUserNev(MainSettings->GetCurrentUser()) ) +
                                      AnsiString( "]" );
            MainSettings->LOG2( MainSettings->strLogMsg );
            // MENTÉS gomb lenyomása esetén az aktuális szolárium adatainak felülírása
            FormSzolariumAdat->SaveDataFromControls( &pSzolarium[nCurrentSolarium]->stAdat );
            if( pSzolarium[nCurrentSolarium]->StatuszCsocserekell() &&
                pSzolarium[nCurrentSolarium]->stAdat.nCsoUzemora < pSzolarium[nCurrentSolarium]->stAdat.nCsoUzemoraMax )
            {
               pSzolarium[nCurrentSolarium]->CsoCserelve();
            }
            // Szolárium adat / megjelenítés frissítése / szolárium adatok mentése
            pSzolarium[nCurrentSolarium]->DataRefresh(true);
         }
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingFelhasznalokClick(TObject *Sender)
{
   int   nRet = mrOk;
   typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );

   if( stUser.nUserLevel < ACCESS_ADMIN )
   {
      FormPasswordCheck->pUser = pUser;
      FormPasswordCheck->AccessLevel = ACCESS_ADMIN;
      FormPasswordCheck->EditCurrentUser->Text = AnsiString( MainSettings->GetCurrentUser() );
      nRet = FormPasswordCheck->ShowModal();
   }
   if( nRet == mrOk )
   {
      if( FormPasswordCheck->EditUserNev->Text.AnsiCompare( "root" ) == 0 )
      {
         FormUserKezeles->LabelPassword->Visible = true;
         FormUserKezeles->EditPassword->Visible = true;
         FormUserKezeles->BitBtnPasswordReset->Visible = true;
         FormUserKezeles->BitBtnPasswordReset->Enabled = true;
      }
      else
      {
         FormUserKezeles->LabelPassword->Visible = false;
         FormUserKezeles->EditPassword->Visible = false;
         FormUserKezeles->BitBtnPasswordReset->Visible = false;
         FormUserKezeles->BitBtnPasswordReset->Enabled = false;
      }
      FormUserKezeles->pUser = pUser;
      FormUserKezeles->pMainSettings = MainSettings;
      FormUserKezeles->ShowModal();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingJelszoClick(TObject *Sender)
{
   typ_user stTemp = pUser->GetUserLogin( MainSettings->GetCurrentUser() );

   FormPasswordChange->Caption = FormLanguage->LangStr(STR_MSG_PASSWORD_CHANGE);
   FormPasswordChange->EditOldPassword->Text = AnsiString( stTemp.strJelszo );
   if( FormPasswordChange->ShowModal() == mrOk )
   {
      stTemp = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
      pUser->strLogMsg = AnsiString( "Felhasznalo jelszovaltoztatas: [" ) +
                         AnsiString( stTemp.strLoginNev ) +
                         AnsiString( "]" );
      pUser->LOG2( pUser->strLogMsg );
      strncpy( stTemp.strJelszo, FormPasswordChange->Edit2->Text.c_str(), sizeof(stTemp.strJelszo)-2 );
      pUser->ModifyUser( stTemp );
      if( strcmp( stTemp.strAzonosito, "Admin" ) == 0 )
      {
         MainSettings->ModifyPassword( ACCESS_ADMIN, FormPasswordChange->Edit2->Text.c_str() );
      }
      else if( strcmp( stTemp.strAzonosito, "User" ) == 0 )
      {
         MainSettings->ModifyPassword( ACCESS_USER, FormPasswordChange->Edit2->Text.c_str() );
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingSystemClick(TObject *Sender)
{
   bool  bTemp;
   char  strtmp[50];
   int   nTemp;
   int i;

   SComm->FillComboWithPorts( FormSystemSettings->ComboBoxPort );
   sprintf( strtmp, "COM%d", MainSettings->GetComPort() );
   for( i=0; i<FormSystemSettings->ComboBoxPort->Items->Count; i++ )
   {
      if( strcmp( FormSystemSettings->ComboBoxPort->Items->Strings[i].c_str(), strtmp ) == 0 )
         break;
   }
   FormSystemSettings->ComboBoxPort->ItemIndex = i;

   sprintf( strtmp, "%d", MainSettings->GetBaudRate() );
   for( i=0; i<FormSystemSettings->ComboBoxBaudRate->Items->Count; i++ )
   {
      if( strcmp( FormSystemSettings->ComboBoxBaudRate->Items->Strings[i].c_str(), strtmp ) == 0 )
         break;
   }
   FormSystemSettings->ComboBoxBaudRate->ItemIndex = i;
   FormSystemSettings->ComboBoxParity->ItemIndex = (int)MainSettings->GetParity();

   FormSystemSettings->ComboBoxLogLevel->ItemIndex = MainSettings->nGlobalLogLevel - 1;

   FormSystemSettings->CheckBoxAutoSave->Checked = MainSettings->bAutoSaveOnExit;
   FormSystemSettings->CheckBoxCardPIN->Checked = MainSettings->bCardUseWithPIN;

   FormSystemSettings->stSoliSettings = MainSettings->stSoliSettings;
   FormSystemSettings->stSoliSettings.StatusFontName = MainSettings->stSoliSettings.StatusFontName;
   FormSystemSettings->stSoliSettings.VisszaszamlalasFontName = MainSettings->stSoliSettings.VisszaszamlalasFontName;
   FormSystemSettings->stSoliSettings.IdoFontName = MainSettings->stSoliSettings.IdoFontName;
   FormSystemSettings->stSoliSettings.InformacioFontName = MainSettings->stSoliSettings.InformacioFontName;
   FormSystemSettings->stSoliSettings.PenzFontName = MainSettings->stSoliSettings.PenzFontName;
   FormSystemSettings->PanelWidth = pSzolarium[0]->PanelSzolarium->Width;
   FormSystemSettings->PanelHeight = pSzolarium[0]->PanelSzolarium->Height;
   FormSystemSettings->bExtended = FormExtendedViewer->Visible;
   if( FormSystemSettings->ShowModal() == mrOk )
   {
      MainSettings->strLogMsg = AnsiString( "Alkalmazas beallitasok modositasa [" ) +
                                AnsiString( MainSettings->GetCurrentUser() ) +
                                AnsiString( "]" );
      MainSettings->LOG2( MainSettings->strLogMsg );
      MainSettings->nGlobalLogLevel = FormSystemSettings->ComboBoxLogLevel->ItemIndex + 1;
      MainSettings->WriteLogLevelToRegistry( MainSettings->nGlobalLogLevel );
      MainSettings->bAutoSaveOnExit = FormSystemSettings->CheckBoxAutoSave->Checked;
      MainSettings->bCardUseWithPIN = FormSystemSettings->CheckBoxCardPIN->Checked;
      MainSettings->SetBoolValueInRegistry( "IsAutoSaveOnExit", MainSettings->bAutoSaveOnExit );
      MainSettings->SetBoolValueInRegistry( "IsPINCodeNeeded", MainSettings->bCardUseWithPIN );
      FormExtendedViewer->Visible = FormSystemSettings->bExtended;
      FormExtendedViewer->Left = MainSettings->GetIntegerValueFromRegistry( "ExtendedWindowLeft" );
      FormExtendedViewer->Top = MainSettings->GetIntegerValueFromRegistry( "ExtendedWindowTop" );
      MainSettings->SetIntegerValueInRegistry( "ShowExtendedWindow", FormExtendedViewer->Visible );
      FormMain->SetFocus();

      MainSettings->stSoliSettings = FormSystemSettings->stSoliSettings;

      MainSettings->SetIntegerValueInRegistry( "StatusTop", MainSettings->stSoliSettings.StatusTop );
      MainSettings->SetIntegerValueInRegistry( "StatusHeight", MainSettings->stSoliSettings.StatusHeight );
      MainSettings->SetIntegerValueInRegistry( "StatusFontSize", MainSettings->stSoliSettings.StatusFontSize );
      MainSettings->SetIntegerValueInRegistry( "StatusFontColorDef", MainSettings->stSoliSettings.StatusFontColorDef );
      MainSettings->SetIntegerValueInRegistry( "StatusFontColorPre", MainSettings->stSoliSettings.StatusFontColorPre );
      MainSettings->SetIntegerValueInRegistry( "StatusFontColorUse", MainSettings->stSoliSettings.StatusFontColorUse );
      MainSettings->SetIntegerValueInRegistry( "StatusFontHeight", MainSettings->stSoliSettings.StatusFontHeight );
      MainSettings->SetIntegerValueInRegistry( "VisszaszamlalasTop", MainSettings->stSoliSettings.VisszaszamlalasTop );
      MainSettings->SetIntegerValueInRegistry( "VisszaszamlalasHeight", MainSettings->stSoliSettings.VisszaszamlalasHeight );
      MainSettings->SetIntegerValueInRegistry( "VisszaszamlalasFontSize", MainSettings->stSoliSettings.VisszaszamlalasFontSize );
      MainSettings->SetIntegerValueInRegistry( "VisszaszamlalasFontColorDef", MainSettings->stSoliSettings.VisszaszamlalasFontColorDef );
      MainSettings->SetIntegerValueInRegistry( "VisszaszamlalasFontColorPre", MainSettings->stSoliSettings.VisszaszamlalasFontColorPre );
      MainSettings->SetIntegerValueInRegistry( "VisszaszamlalasFontColorUse", MainSettings->stSoliSettings.VisszaszamlalasFontColorUse );
      MainSettings->SetIntegerValueInRegistry( "VisszaszamlalasFontHeight", MainSettings->stSoliSettings.VisszaszamlalasFontHeight );
      MainSettings->SetIntegerValueInRegistry( "IdoTop", MainSettings->stSoliSettings.IdoTop );
      MainSettings->SetIntegerValueInRegistry( "IdoHeight", MainSettings->stSoliSettings.IdoHeight );
      MainSettings->SetIntegerValueInRegistry( "IdoFontSize", MainSettings->stSoliSettings.IdoFontSize );
      MainSettings->SetIntegerValueInRegistry( "IdoFontColorDef", MainSettings->stSoliSettings.IdoFontColorDef );
      MainSettings->SetIntegerValueInRegistry( "IdoFontColorPre", MainSettings->stSoliSettings.IdoFontColorPre );
      MainSettings->SetIntegerValueInRegistry( "IdoFontColorUse", MainSettings->stSoliSettings.IdoFontColorUse );
      MainSettings->SetIntegerValueInRegistry( "IdoFontHeight", MainSettings->stSoliSettings.IdoFontHeight );
      MainSettings->SetIntegerValueInRegistry( "InformacioTop", MainSettings->stSoliSettings.InformacioTop );
      MainSettings->SetIntegerValueInRegistry( "InformacioHeight", MainSettings->stSoliSettings.InformacioHeight );
      MainSettings->SetIntegerValueInRegistry( "InformacioFontSize", MainSettings->stSoliSettings.InformacioFontSize );
      MainSettings->SetIntegerValueInRegistry( "InformacioFontColorDef", MainSettings->stSoliSettings.InformacioFontColorDef );
      MainSettings->SetIntegerValueInRegistry( "InformacioFontColorPre", MainSettings->stSoliSettings.InformacioFontColorPre );
      MainSettings->SetIntegerValueInRegistry( "InformacioFontColorUse", MainSettings->stSoliSettings.InformacioFontColorUse );
      MainSettings->SetIntegerValueInRegistry( "InformacioFontHeight", MainSettings->stSoliSettings.InformacioFontHeight );
      MainSettings->SetIntegerValueInRegistry( "PenzTop", MainSettings->stSoliSettings.PenzTop );
      MainSettings->SetIntegerValueInRegistry( "PenzHeight", MainSettings->stSoliSettings.PenzHeight );
      MainSettings->SetIntegerValueInRegistry( "PenzFontSize", MainSettings->stSoliSettings.PenzFontSize );
      MainSettings->SetIntegerValueInRegistry( "PenzFontColorDef", MainSettings->stSoliSettings.PenzFontColorDef );
      MainSettings->SetIntegerValueInRegistry( "PenzFontColorPre", MainSettings->stSoliSettings.PenzFontColorPre );
      MainSettings->SetIntegerValueInRegistry( "PenzFontColorUse", MainSettings->stSoliSettings.PenzFontColorUse );
      MainSettings->SetIntegerValueInRegistry( "PenzFontHeight", MainSettings->stSoliSettings.PenzFontHeight );
      MainSettings->SetIntegerValueInRegistry( "ColorDefault", MainSettings->stSoliSettings.ColorDefault );
      MainSettings->SetIntegerValueInRegistry( "ColorPrepare", MainSettings->stSoliSettings.ColorPrepare );
      MainSettings->SetIntegerValueInRegistry( "ColorUsed", MainSettings->stSoliSettings.ColorUsed );
      MainSettings->SetStringValueInRegistry( "StatusFontName", MainSettings->stSoliSettings.StatusFontName );
      MainSettings->SetStringValueInRegistry( "VisszaszamlalasFontName", MainSettings->stSoliSettings.VisszaszamlalasFontName );
      MainSettings->SetStringValueInRegistry( "IdoFontName", MainSettings->stSoliSettings.IdoFontName );
      MainSettings->SetStringValueInRegistry( "InformacioFontName", MainSettings->stSoliSettings.InformacioFontName );
      MainSettings->SetStringValueInRegistry( "PenzFontName", MainSettings->stSoliSettings.PenzFontName );

      for( int i=0; i<(int)pSzolarium.size(); i++ )
      {
         pSzolarium[i]->stSoliSettings = MainSettings->stSoliSettings;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingsBerletekClick(TObject *Sender)
{
   int   nRet = mrOk;
   typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );

   if( stUser.nUserLevel < ACCESS_ADMIN )
   {
      FormPasswordCheck->pUser = pUser;
      FormPasswordCheck->AccessLevel = ACCESS_ADMIN;
      FormPasswordCheck->EditCurrentUser->Text = AnsiString( MainSettings->GetCurrentUser() );
      nRet = FormPasswordCheck->ShowModal();
   }
   if( nRet == mrOk )
   {
      if( FormPasswordCheck->EditUserNev->Text.AnsiCompare( "root" ) == 0 )
      {
         FormBerlet->EditBTID->Visible = true;
      }
      else
      {
         FormBerlet->EditBTID->Visible = false;
      }
      FormBerlet->pBerlet = pBerletek;
      FormBerlet->ShowModal();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingsTermekekClick(TObject *Sender)
{
   int   nRet = mrOk;
   typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );

   if( stUser.nUserLevel < ACCESS_ADMIN )
   {
      FormPasswordCheck->pUser = pUser;
      FormPasswordCheck->AccessLevel = ACCESS_ADMIN;
      FormPasswordCheck->EditCurrentUser->Text = AnsiString( MainSettings->GetCurrentUser() );
      nRet = FormPasswordCheck->ShowModal();
   }
   if( nRet == mrOk )
   {
      if( FormPasswordCheck->EditUserNev->Text.AnsiCompare( "root" ) == 0 )
      {
         FormTermekKezeles->EditID->Visible = true;
      }
      else
      {
         FormTermekKezeles->EditID->Visible = false;
      }
      FormTermekKezeles->pBerlet = pBerletek;
      FormTermekKezeles->pTermek = pTermek;
      FormTermekKezeles->pTermekTipus = pTermekTipus;
      FormTermekKezeles->ShowModal();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingsTermekTipusokClick(TObject *Sender)
{
   int   nRet = mrOk;
   typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );

   if( stUser.nUserLevel < ACCESS_ADMIN )
   {
      FormPasswordCheck->pUser = pUser;
      FormPasswordCheck->AccessLevel = ACCESS_ADMIN;
      FormPasswordCheck->EditCurrentUser->Text = AnsiString( MainSettings->GetCurrentUser() );
      nRet = FormPasswordCheck->ShowModal();
   }
   if( nRet == mrOk )
   {
      FormTermekTipus->pTermekTipus = pTermekTipus;
      FormTermekTipus->pTermek = pTermek;
      FormTermekTipus->ShowModal();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingsPenztarClick(TObject *Sender)
{
   int   nRet = mrOk;
   typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );

   if( stUser.nUserLevel < ACCESS_ADMIN )
   {
      FormPasswordCheck->pUser = pUser;
      FormPasswordCheck->AccessLevel = ACCESS_ADMIN;
      FormPasswordCheck->EditCurrentUser->Text = AnsiString( MainSettings->GetCurrentUser() );
      nRet = FormPasswordCheck->ShowModal();
   }
   if( nRet == mrOk )
   {
      MenuMain_ListPenztarClick(Sender);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingsHWTesztClick(TObject *Sender)
{
   FormHardverTeszt->pHardware = pHardware;
   FormHardverTeszt->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_PenzKosarClick(TObject *Sender)
{
   FormKosar->pKosar = pKosar;
   FormKosar->pBerletek = pBerletek;
   FormKosar->pTermek = pTermek;
   FormKosar->pMainSettings = MainSettings;
   if( FormKosar->ShowModal() == mrOk )
   {
      FormFizetes->BitBtnKosar->Enabled = false;
      FormFizetes->LabelFizetendo->Caption = FormKosar->LabelFizetendo->Caption;
      if( FormFizetes->ShowModal() == mrOk )
      {
         // Kifizetve gomb megnyomva
         for( int i=0; i<pKosar->GetKosarCount(); i++ )
         {
            typ_kosar   stTemp = pKosar->GetKosar( i );

            switch( stTemp.nTipus )
            {
               case 0: // bérlet
               {
                  pKonyv->AddGeneralKonyv( MainSettings->GetCurrentMuszak(),
                                           stTemp.nAr*stTemp.nDarab,
                                           0,
                                           "" );
                  // Felhasználói adatainak elõkeresése
                  typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
                  // Megjegyzés feltöltése a bérlet adataival
                  AnsiString strTemp = AnsiString( stTemp.strNev );
                  // Bevétel hozzáadása a pénztárhoz felhasználó rögzítése nélkül
                  pPenztar->PenztarBevetel( stUser, stTemp.nAr*stTemp.nDarab, strTemp.c_str() );
                  pPenztar->strLogMsg = AnsiString( "Berlet eladas kosarbol [" ) +
                                        AnsiString( stTemp.strVonalkod ) +
                                        AnsiString( "/" ) +
                                        convertToCurrencyString( stTemp.nAr ) +
                                        AnsiString( "/" ) +
                                        AnsiString( stTemp.nDarab ) +
                                        AnsiString( "]" );
                  pPenztar->LOG2( pPenztar->strLogMsg );
                  break;
               }
               case 1: // termék
               {
                  pKonyv->AddGeneralKonyv( MainSettings->GetCurrentMuszak(),
                                           0,
                                           stTemp.nAr*stTemp.nDarab,
                                           "" );
                  // Felhasználói adatainak elõkeresése
                  typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
                  // Megjegyzés feltöltése a termék adataival
                  AnsiString strTemp = AnsiString( stTemp.nDarab ) +
                                       AnsiString( " db. " ) +
                                       AnsiString( stTemp.strNev );
                  // Bevétel hozzáadása a pénztárhoz felhasználó rögzítése nélkül
                  pPenztar->PenztarBevetel( stUser, stTemp.nAr*stTemp.nDarab, strTemp.c_str() );
                  pPenztar->strLogMsg = AnsiString( "Termek eladas kosarbol [" ) +
                                        AnsiString( stTemp.strVonalkod ) +
                                        AnsiString( "/" ) +
                                        convertToCurrencyString( stTemp.nAr ) +
                                        AnsiString( "/" ) +
                                        AnsiString( stTemp.nDarab ) +
                                        AnsiString( "]" );
                  pPenztar->LOG2( pPenztar->strLogMsg );
                  break;
               }
               case 2: // szolárium használat
               {
                  // Felhasználói adatainak elõkeresése
                  typ_user stUser = pUser->GetUserLogin( MainSettings->GetCurrentUser() );
                  // Megjegyzés feltöltése a szolárium adataival
                  AnsiString strTemp = AnsiString( stTemp.strNev );
                  // Bevétel hozzáadása a pénztárhoz felhasználó rögzítése nélkül
                  pPenztar->PenztarBevetel( stUser, stTemp.nAr*stTemp.nDarab, strTemp.c_str() );
                  pPenztar->strLogMsg = AnsiString( "Szolarium hasznalat fizetve [" ) +
                                        AnsiString( stTemp.strNev ) +
                                        AnsiString( "/" ) +
                                        convertToCurrencyString( stTemp.nAr ) +
                                        AnsiString( "/" ) +
                                        AnsiString( stTemp.nDarab ) +
                                        AnsiString( "]" );
                  pPenztar->LOG2( pPenztar->strLogMsg );
                  if( atoi(stTemp.strVonalkod) > -1 && atoi(stTemp.strVonalkod) < (int)pSzolarium.size() )
                  {
                     pSzolarium[atoi(stTemp.strVonalkod)]->Fizetve();
                  }
                  break;
               }
            }
         }
         // Kosár kiürítése
         pKosar->EmptyKosar();
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_PenzPenztarClick(TObject *Sender)
{
   FormPenztarKezeles->pMainSettings = MainSettings;
   FormPenztarKezeles->pPenztar = pPenztar;
   FormPenztarKezeles->pUser = pUser;
   FormPenztarKezeles->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_ListBerletOsszClick(TObject *Sender)
{
   FormLista->nListaType = LISTA_BERLETOSSZ;
   FormLista->pMainSettings = MainSettings;
   FormLista->pBerletek = pBerletek;
   FormLista->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_ListBerletClick(TObject *Sender)
{
   FormLista->nListaType = LISTA_BERLET;
   FormLista->pMainSettings = MainSettings;
   FormLista->pBerletek = pBerletek;
   FormLista->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_ListBerletHasznalatClick(TObject *Sender)
{
   FormLista->nListaType = LISTA_BERLETHASZNALAT;
   FormLista->pMainSettings = MainSettings;
   FormLista->pBerletek = pBerletek;
   FormLista->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_ListGoodsClick(TObject *Sender)
{
   FormLista->nListaType = LISTA_TERMEK;
   FormLista->pMainSettings = MainSettings;
   FormLista->pTermek = pTermek;
   FormLista->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_ListMaincashClick(TObject *Sender)
{
   if( pUser->GetUserLevel(MainSettings->GetCurrentUser()) < ACCESS_ADMIN )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_ACCESS_DENIED).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONSTOP );
      return;
   }
   FormLista->nListaType = LISTA_FOKONYV;
   FormLista->pMainSettings = MainSettings;
   FormLista->dMuszakMax = MainSettings->GetCurrentMuszak();
   FormLista->EditMuszakID->Text = AnsiString( MainSettings->GetCurrentMuszak() );
   FormLista->nSzolariumCount = MainSettings->GetCountSolarium();
   FormLista->pKonyv = pKonyv;
   FormLista->pPenztar = pPenztar;
   FormLista->pUser = pUser;
   FormLista->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_ListDailycashClick(TObject *Sender)
{
   FormLista->nListaType = LISTA_NAPIKONYV;
   FormLista->pMainSettings = MainSettings;
   FormLista->dMuszakMax = MainSettings->GetCurrentMuszak();
   FormLista->EditMuszakID->Text = AnsiString( MainSettings->GetCurrentMuszak() );
   FormLista->nSzolariumCount = MainSettings->GetCountSolarium();
   FormLista->pKonyv = pKonyv;
   FormLista->pPenztar = pPenztar;
   FormLista->pUser = pUser;
   FormLista->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_ListMuszakClick(TObject *Sender)
{
   FormLista->nListaType = LISTA_MUSZAK;
   FormLista->pMainSettings = MainSettings;
   FormLista->dMuszakMax = MainSettings->GetCurrentMuszak();
   FormLista->EditMuszakID->Text = AnsiString( MainSettings->GetCurrentMuszak() );
   FormLista->nSzolariumCount = MainSettings->GetCountSolarium();
   FormLista->pKonyv = pKonyv;
   FormLista->pPenztar = pPenztar;
   FormLista->pUser = pUser;
   FormLista->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_ListPenztarClick(TObject *Sender)
{
   FormLista->nListaType = LISTA_PENZTAR;
   FormLista->pMainSettings = MainSettings;
   FormLista->dMuszakMax = MainSettings->GetCurrentMuszak();
   FormLista->EditMuszakID->Text = AnsiString( MainSettings->GetCurrentMuszak() );
   FormLista->nSzolariumCount = MainSettings->GetCountSolarium();
   FormLista->pKonyv = pKonyv;
   FormLista->pPenztar = pPenztar;
   FormLista->pUser = pUser;
   FormLista->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_HelpAboutClick(TObject *Sender)
{
   FormHelpAbout->LabelVersion->Caption = FormLanguage->LangStr(STR_INF_VERSION_NUMBER) + MainSettings->strVersionNumber;
   FormHelpAbout->LabelAdatfile->Caption = AnsiString( "MS: " ) + AnsiString( SETTINGS_FILE_VERSION ) +
                                           AnsiString( " SV: " ) + AnsiString( SOLARIUM_FILE_VERSION ) +
                                           AnsiString( "\nBTV: " ) + AnsiString( BERLETTIPUS_FILE_VERSION ) +
                                           AnsiString( " BV: " ) + AnsiString( BERLET_FILE_VERSION ) +
                                           AnsiString( " BHV: " ) + AnsiString( BERLETHASZNALAT_FILE_VERSION ) +
                                           AnsiString( "\nTV: " ) + AnsiString( TERMEK_FILE_VERSION ) +
                                           AnsiString( " KV: " ) + AnsiString( KOSAR_FILE_VERSION ) +
                                           AnsiString( " PV: " ) + AnsiString( PENZTAR_FILE_VERSION ) +
                                           AnsiString( "\nKGV: " ) + AnsiString( KONYV_GENERAL_FILE_VERSION ) +
                                           AnsiString( " KSV: " ) + AnsiString( KONYV_SZOLARIUM_FILE_VERSION ) +
                                           AnsiString( " UV: " ) + AnsiString( USER_FILE_VERSION );
   FormHelpAbout->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_Sol_IdoClick(TObject *Sender)
{
   ToolButtonSzolariumIdoClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_Sol_BerletClick(TObject *Sender)
{
   ToolButtonSzolariumBerletClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_Sol_VetkozesStopClick(TObject *Sender)
{
   ToolButtonSzolariumStartClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_Sol_SterilClick(TObject *Sender)
{
   ToolButtonSzolariumSterilClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_Sol_StopClick(TObject *Sender)
{
   ToolButtonSzolariumHaltClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_PenzBerletClick(TObject *Sender)
{
   ToolButtonBerletEladasClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_PenzTermekClick(TObject *Sender)
{
   ToolButtonTermekEladasClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SystemImport_BerletClick(TObject *Sender)
{
   if( pUser->GetUserLevel(MainSettings->GetCurrentUser()) < ACCESS_ADMIN )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_ACCESS_DENIED).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONSTOP );
      return;
   }
   if( OpenDialog->Execute() )
   {
      FILE  *file = NULL;
      int   nBerletTipus = 0;
      int   nBerlet = 0;

      FormMain->Update();
      TCursor Save_Cursor = Screen->Cursor;
      Screen->Cursor = crHourGlass;    // Show hourglass cursor
      try
      {
         if( (file = fopen( OpenDialog->FileName.c_str(), "rt" )) != NULL )
         {
            //7585	0	5800	2005.1.3-2007.1.3
            char  sLine[100];

            memset( sLine, 0, sizeof(sLine) );
            while( fgets( sLine, 99, file ) )
            {
               AnsiString        strLine = AnsiString( sLine );
               typ_berlettipus   stBerletTipus;
               typ_berlet        stBerlet;
               int               nPos;

               memset( &stBerletTipus, 0, sizeof(typ_berlettipus) );
               memset( &stBerlet, 0, sizeof(typ_berlet) );

               nPos = strLine.Pos('\t');
               if( nPos == 0 )
                  continue;

               strncpy( stBerlet.strVonalkod,
                        strLine.SubString( 1, nPos-1 ).c_str(),
                        19 );
               if( pBerletek->IsBerletExists( stBerlet.strVonalkod ) )
                  continue;

               strLine = strLine.SubString( nPos+1, strLine.Length()-nPos );
               nPos = strLine.Pos('\t');
               stBerlet.nEgyseg = strLine.SubString( 1, nPos-1 ).ToInt();

               strLine = strLine.SubString( nPos+1, strLine.Length()-nPos );
               nPos = strLine.Pos('\t');
               stBerletTipus.nAr = convertCurrency(strLine.SubString( 1, nPos-1 ).ToDouble());

               if( pBerletek->GetIDBerletTipusAr( stBerletTipus.nAr ) == 0 )
               {
                  strcpy( stBerletTipus.strNev, convertToCurrencyString(stBerletTipus.nAr).c_str() );
                  pBerletek->AddBerletTipus( stBerletTipus );
                  nBerletTipus++;
               }
               stBerlet.nBerletTipus = pBerletek->GetIDBerletTipusAr( stBerletTipus.nAr );

               strLine = strLine.SubString( nPos+1, strLine.Length()-nPos );
               nPos = strLine.Pos('-');
               strLine = strLine.SubString( nPos+1, strLine.Length()-nPos );
               nPos = strLine.Pos('.');
               stBerlet.nErvEv = strLine.SubString( 1, nPos-1 ).ToInt();

               strLine = strLine.SubString( nPos+1, strLine.Length()-nPos );
               nPos = strLine.Pos('.');
               stBerlet.nErvHo = strLine.SubString( 1, nPos-1 ).ToInt();

               strLine = strLine.SubString( nPos+1, strLine.Length()-nPos );
               nPos = strLine.Pos('\n');
               stBerlet.nErvNap = strLine.SubString( 1, nPos-1 ).ToInt();

               pBerletek->AddBerlet( stBerlet );
               nBerlet++;
            }
            fclose( file );

            AnsiString  strMessage;

            strMessage.sprintf( FormLanguage->LangStr(STR_MSG_IMPORT_FINISHED).c_str(),
                                OpenDialog->FileName.c_str(),
                                nBerlet,
                                nBerletTipus );
            Application->MessageBox( strMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_INFORMATION).c_str(), MB_ICONINFORMATION );
         }
      }
      __finally
      {
        Screen->Cursor = Save_Cursor; // always restore the cursor
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuMain_SettingsDBClick(TObject *Sender)
{
   if( pUser->GetUserLevel(MainSettings->GetCurrentUser()) < ACCESS_ADMIN )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_ACCESS_DENIED).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONSTOP );
      return;
   }
   FormAdatbazisKezeles->pBerletek = pBerletek;
   FormAdatbazisKezeles->pKonyv    = pKonyv;
   FormAdatbazisKezeles->pPenztar  = pPenztar;
   FormAdatbazisKezeles->ShowModal();
}
//---------------------------------------------------------------------------

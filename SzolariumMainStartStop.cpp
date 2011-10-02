//---------------------------------------------------------------------------

#include <vcl.h>
#include <Filectrl.hpp>
#include <process.h>
#include <Registry.hpp>

#include "SzolariumMain.h"
#include "Language.h"
#include "ExtendedViewer.h"

/****************************************************************************
*
* PROGRAM INDITASA, ADATOK BETOLTESE
*
****************************************************************************/
//---------------------------------------------------------------------------
void TFormMain::InitVariables()
{
   typ_error   stError;

   memset( &stError, 0, sizeof(typ_error) );

   nCountColumn      = 0;
   nCountRow         = 0;
   nCurrentSolarium  = 0;
   strMentesBat      = "mentes.bat";
   extLeft           = 50;
   extTop            = 50;

   try
   {
      AnsiString  strCurrDir = GetCurrentDir();
      AnsiString  strDirectory = GetCurrentDir()+AnsiString("\\Db");
      if( !DirectoryExists(strDirectory) )
      {
         if( !CreateDir(strDirectory) )
         {
            FILE  *file = NULL;

            if( (file = fopen( "fsv.log", "at" )) != NULL )
            {
               fputs( "H:sys001 Nem lehet létrehozni hiányzó Db könyvtárat\n", file );
               fclose( file );
            }
            throw Exception( AnsiString( "\n"
                                         "Hiba leírás: Operációs rendszer hiba."
                                         "Hiba kód: sys001" ) );
         }
      }

      //-------------------------------------------------------------------
      // MainSettings
      if( (MainSettings = new CS_MainSettings()) == NULL )
      {
         FILE  *file = NULL;

         if( (file = fopen( "fsv.log", "at" )) != NULL )
         {
            fputs( "H:sys002 Nem lehet létrehozni a MainSettings osztályt\n", file );
            fclose( file );
         }
         throw Exception( AnsiString( "\n"
                                      "Hiba leírás: Operációs rendszer hiba."
                                      "Hiba kód: sys002" ) );
      }
      if( MainSettings->bIsDatabaseOk )
      {
         stError.nErrCode = STR_ERR_GENERAL_SETTINGS_OK;
         stError.nErrType = 0;
      }
      else
      {
         stError.nErrCode = STR_ERR_GENERAL_SETTINGS_HIBA;
         stError.nErrType = 1;
      }
      ErrorList.push_back( stError );

      //-------------------------------------------------------------------
      //
      if( (pKosar = new CS_Kosar()) == NULL )
      {
         throw Exception( AnsiString( "\n"
                                      "Hiba leírás: Operációs rendszer hiba."
                                      "Hiba kód: sys003" ) );
      }
      if( pKosar->bIsDatabaseOk )
      {
         stError.nErrCode = STR_ERR_KOSAR_OK;
         stError.nErrType = 0;
      }
      else
      {
         stError.nErrCode = STR_ERR_KOSAR_HIBA;
         stError.nErrType = 1;
      }
      ErrorList.push_back( stError );

      //-------------------------------------------------------------------
      //
      if( (pBerletek = new CS_Berlet()) == NULL )
      {
         throw Exception( AnsiString( "\n"
                                      "Hiba leírás: Operációs rendszer hiba."
                                      "Hiba kód: sys004" ) );
      }
      if( (pBerletek->nDatabaseCode&1) == 1 )
      {
         stError.nErrCode = STR_ERR_BERLET_TIPUS_OK;
         stError.nErrType = 0;
         ErrorList.push_back( stError );
      }
      else
      {
         stError.nErrCode = STR_ERR_BERLET_TIPUS_HIBA;
         stError.nErrType = 1;
         ErrorList.push_back( stError );
      }
      if( (pBerletek->nDatabaseCode&2) == 2 )
      {
         stError.nErrCode = STR_ERR_BERLET_OK;
         stError.nErrType = 0;
         ErrorList.push_back( stError );
      }
      else
      {
         stError.nErrCode = STR_ERR_BERLET_HIBA;
         stError.nErrType = 1;
         ErrorList.push_back( stError );
      }
      if( (pBerletek->nDatabaseCode&4) == 4 )
      {
         stError.nErrCode = STR_ERR_BERLET_HASZNALAT_OK;
         stError.nErrType = 0;
         ErrorList.push_back( stError );
      }
      else
      {
         stError.nErrCode = STR_ERR_BERLET_HASZNALAT_HIBA;
         stError.nErrType = 1;
         ErrorList.push_back( stError );
      }

      //-------------------------------------------------------------------
      //
      if( (pTermek = new CS_Termek()) == NULL )
      {
         throw Exception( AnsiString( "\n"
                                      "Hiba leírás: Operációs rendszer hiba."
                                      "Hiba kód: sys005" ) );
      }

      //-------------------------------------------------------------------
      //
      if( (pUser = new CS_User(MainSettings)) == NULL )
      {
         throw Exception( AnsiString( "\n"
                                      "Hiba leírás: Operációs rendszer hiba."
                                      "Hiba kód: sys006" ) );
      }

      //-------------------------------------------------------------------
      //
      if( (pKonyv = new CS_Konyv()) == NULL )
      {
         throw Exception( AnsiString( "\n"
                                      "Hiba leírás: Operációs rendszer hiba."
                                      "Hiba kód: sys008" ) );
      }

      //-------------------------------------------------------------------
      //
      if( (pPenztar = new CS_Penztar()) == NULL )
      {
         throw Exception( AnsiString( "\n"
                                      "Hiba leírás: Operációs rendszer hiba."
                                      "Hiba kód: sys009" ) );
      }

      //-------------------------------------------------------------------
      //
      if( (pTermekTipus = new CS_TermekTipus()) == NULL )
      {
         throw Exception( AnsiString( "\n"
                                      "Hiba leírás: Operációs rendszer hiba."
                                      "Hiba kód: sys011" ) );
      }

      //-------------------------------------------------------------------
      //
      if( (SComm = new CS_SerialComm()) == NULL )
      {
         throw Exception( AnsiString( "\n"
                                      "Hiba leírás: Operációs rendszer hiba."
                                      "Hiba kód: sys007" ) );
      }

      //-------------------------------------------------------------------
      //
      if( (pHardware = new CS_Hardware()) == NULL )
      {
         throw Exception( AnsiString( "\n"
                                      "Hiba leírás: Operációs rendszer hiba."
                                      "Hiba kód: sys010" ) );
      }

      //-------------------------------------------------------------------
      //
      SetCurrentDir( strCurrDir );

      //-------------------------------------------------------------------
      //
      CalculateColumnRow();

      int VideoResolution;

      MainSettings->GetApplicationParameters( &Left, &Top, &VideoResolution );

      switch( VideoResolution )
      {
         case 2:
            Width = 1024;
            Height = 768;
            MenuMain_SettingVideoSize2->Checked = true;
            MenuMain_SettingVideoSize3->Checked = false;
            MenuMain_SettingVideoSize4->Checked = false;
            StatusBar->Panels->Items[0]->Width = 824;
            break;
         case 3:
            Width = 1280;
            Height = 768;
            MenuMain_SettingVideoSize2->Checked = false;
            MenuMain_SettingVideoSize3->Checked = true;
            MenuMain_SettingVideoSize4->Checked = false;
            StatusBar->Panels->Items[0]->Width = 1080;
            break;
         case 4:
            Width = 1280;
            Height = 960;
            MenuMain_SettingVideoSize2->Checked = false;
            MenuMain_SettingVideoSize3->Checked = false;
            MenuMain_SettingVideoSize4->Checked = true;
            StatusBar->Panels->Items[0]->Width = 1080;
            break;
      }

   }
   catch(const Exception& e)
   {
      AnsiString eMessage = FormLanguage->LangStr(STR_ERR_UNABLE_TO_CONTINUE) + e.Message;
      Application->MessageBox( eMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_ERROR).c_str(), MB_ICONSTOP );
      Application->Terminate();
   }

   TRegistry *Registry = new TRegistry;
   try
   {
      Registry->RootKey = HKEY_LOCAL_MACHINE;
      // false because we do not want to create it if it doesn’t exist
      if( Registry->OpenKey("SOFTWARE\\SzolariumVezerlo", false) )
      {
         MainSettings->nGlobalLogLevel = Registry->ReadInteger( "LogLevel" );
         MainSettings->bAutoSaveOnExit = MainSettings->GetBoolValueFromRegistry( "IsAutoSaveOnExit", false );
         MainSettings->bCardUseWithPIN = MainSettings->GetBoolValueFromRegistry( "IsPINCodeNeeded", false );
      }
      else
      {
         Registry->OpenKey("SOFTWARE\\SzolariumVezerlo", true);
         Registry->WriteInteger( "LogLevel", 1 );
         Registry->WriteBool( "IsAutoSaveOnExit", false );
      }
   }
   __finally
   {
      delete Registry;
   }

   for(int y=0,i=0;y<nCountRow&&i<MainSettings->GetCountSolarium();y++)
   {
      for(int x=0;x<nCountColumn&&i<MainSettings->GetCountSolarium();x++)
      {
         pSzolarium.push_back( new CS_Solarium( FormMain,
                                                i,
                                                x*(ClientWidth/nCountColumn),
                                                y*((ClientHeight-82)/nCountRow)+51,
                                                (ClientWidth/nCountColumn),
                                                ((ClientHeight-82)/nCountRow) ) );
         pSzolarium[i]->PanelSzolarium->OnMouseDown = FormMouseDown;
         pSzolarium[i]->Label_Status->OnMouseDown = FormMouseDown;
         pSzolarium[i]->Label_Visszaszamlalas->OnMouseDown = FormMouseDown;
         pSzolarium[i]->Label_Ido->OnMouseDown = FormMouseDown;
         pSzolarium[i]->Label_Informacio->OnMouseDown = FormMouseDown;
         pSzolarium[i]->Label_Penz->OnMouseDown = FormMouseDown;
         pSzolarium[i]->PanelSzolarium->OnDblClick = FormDblClick;
         pSzolarium[i]->Label_Status->OnDblClick = FormDblClick;
         pSzolarium[i]->Label_Visszaszamlalas->OnDblClick = FormDblClick;
         pSzolarium[i]->Label_Ido->OnDblClick = FormDblClick;
         pSzolarium[i]->Label_Informacio->OnDblClick = FormDblClick;
         pSzolarium[i]->Label_Penz->OnDblClick = FormDblClick;
         pSzolarium[i]->Deselect();
         pSzolarium[i]->pBerlet = pBerletek;
         pSzolarium[i]->pKonyv = pKonyv;
         pSzolarium[i]->pPenztar = pPenztar;
         pSzolarium[i]->dCurrentMuszak = MainSettings->GetCurrentMuszak();
         pSzolarium[i]->stSoliSettings = MainSettings->stSoliSettings;
         pKonyv->AddSzolariumKonyv( MainSettings->GetCurrentMuszak(), i, 0, 0, 0, 0, 0, 0, 0, pSzolarium[i]->stAdat.strNev );
         i++;
      }
   }

   pHardware->pSzolarium = pSzolarium;
   pHardware->SComm = SComm;

   pKonyv->AddGeneralKonyv( MainSettings->GetCurrentMuszak(), 0, 0, "" );

   pSzolarium[nCurrentSolarium]->Select();
   TimerUserLock->Interval = 100;
}
//---------------------------------------------------------------------------
void TFormMain::CalculateColumnRow()
{

   switch( MainSettings->GetCountSolarium() )
   {
      case 1:
      {
         nCountRow = 1;
         nCountColumn = 1;
         break;
      }
      case 2:
      {
         nCountRow = 1;
         nCountColumn = 2;
         break;
      }
      case 3:
      {
         nCountRow = 1;
         nCountColumn = 3;
         break;
      }
      case 4:
      {
         nCountRow = 2;
         nCountColumn = 2;
         break;
      }
      case 5:
      {
         nCountRow = 2;
         nCountColumn = 3;
         break;
      }
      case 6:
      {
         nCountRow = 2;
         nCountColumn = 3;
         break;
      }
      case 7:
      {
         nCountRow = 2;
         nCountColumn = 4;
         break;
      }
      case 8:
      {
         nCountRow = 2;
         nCountColumn = 4;
         break;
      }
      case 9:
      {
         nCountRow = 3;
         nCountColumn = 3;
         break;
      }
      case 10:
      {
         nCountRow = 3;
         nCountColumn = 4;
         break;
      }
      case 11:
      {
         nCountRow = 3;
         nCountColumn = 4;
         break;
      }
      case 12:
      {
         nCountRow = 3;
         nCountColumn = 4;
         break;
      }
      default:
      {
         double   nTemp = sqrt(MainSettings->GetCountSolarium());

         nCountColumn = floor( nTemp );
         if( nCountColumn*nCountColumn < MainSettings->GetCountSolarium() )
            nCountColumn++;

         nCountRow = MainSettings->GetCountSolarium()/nCountColumn;
         if( nCountRow*nCountColumn < MainSettings->GetCountSolarium() )
            nCountRow++;
         break;
      }
   }
}
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
   : TForm(Owner)
{
//   InitVariables();

}
/****************************************************************************
*
* PROGRAM LEALLITASA
*
****************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
   int i;

   pKonyv->AddGeneralKonyv( MainSettings->GetCurrentMuszak(), 0, 0, "" );

   for( i=0; i<(int)pSzolarium.size(); i++ )
   {
      if( pSzolarium[i]->StatuszLekerdezes() != STATUS_ALAP )
      {
         Application->MessageBox( FormLanguage->LangStr(STR_ERR_SOLINUSE_CLOSEDENIED).c_str(),
                                  FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                                  MB_ICONEXCLAMATION );
         Action = caNone;
         return;
      }
   }

   if( Application->MessageBox( FormLanguage->LangStr(STR_MSG_CONFIRM_EXIT).c_str(),
                                FormLanguage->LangStr(STR_MSGBOX_QUESTION).c_str(),
                                MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 ) == IDNO )
   {
      if( MainSettings->IsPasswordRequired() )
      {
         TimerUserLock->Interval = 100;
      }
      Action = caNone;
      return;
   }
   try
   {
      if( !CheckDatabase() )
      {
         Application->MessageBox( FormLanguage->LangStr(STR_ERR_DATABASE_INCONSISTENCY).c_str(),
                                  FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                                  MB_ICONEXCLAMATION );
         if( SaveDatabase() )
         {
            Application->MessageBox( FormLanguage->LangStr(STR_ERR_DATABASE_SAVE_OK).c_str(),
                                     FormLanguage->LangStr(STR_MSGBOX_INFORMATION).c_str(),
                                     MB_ICONINFORMATION );
         }
         else
         {
            Application->MessageBox( FormLanguage->LangStr(STR_ERR_DATABASE_SAVE_ERROR).c_str(),
                                     FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                                     MB_ICONEXCLAMATION );
         }
         Action = caNone;
         return;
      }
      if( MainSettings->bAutoSaveOnExit )
      {
         MenuMain_SystemSaveClick(Sender);
      }
      MainSettings->SetIntegerValueInRegistry( "ExtendedWindowLeft", FormExtendedViewer->Left );
      MainSettings->SetIntegerValueInRegistry( "ExtendedWindowTop", FormExtendedViewer->Top );
      TimerSolarium->Interval = 0;
      TimerSolarium->Enabled = false;
      delete pHardware;
      delete pPenztar;
      delete pKonyv;
      MainSettings->SaveApplicationParameters( Left, Top );

      for( i=0; i<(int)pSzolarium.size();i++ )
      {
         delete pSzolarium[i];
      }
      delete pUser;
      delete pTermek;
      delete pTermekTipus;
      delete pBerletek;
      delete pKosar;
      MainSettings->LOG1( "Alkalmazás bezárás" );
      delete MainSettings;
      SComm->ClosePort();
      delete SComm;
      if( FileExists( strMentesBat ) )
      {
         execl( strMentesBat.c_str(), strMentesBat.c_str(), NULL );
      }
   }
   catch(const Exception& e)
   {
/*
      AnsiString eMessage = "A program lezárásakor nem várt hiba lépett fel\n"
                            "az operációs rendszer hibája miatt.\n"
                            "Kérem értesítse a program készítõjét!\n" +
                            e.Message;
      Application->MessageBox( eMessage.c_str(), "Figyelmeztetés", MB_ICONEXCLAMATION );
*/
   }

   Action = caFree;
}
//---------------------------------------------------------------------------
bool TFormMain::CheckDatabase()
{
   bool bRet = true;

   if( pBerletek->CheckBerlettipus(pBerletek->sBerletTipusFile.c_str()) == false )
   {
      bRet = false;
   }
   if( pBerletek->CheckBerlet(pBerletek->sBerletFile.c_str()) == false )
   {
      bRet = false;
   }
   if( pBerletek->CheckBerlethasznalat(pBerletek->sBerletHasznalatFile.c_str()) == false )
   {
      bRet = false;
   }
   if( pKonyv->CheckGeneralKonyv(pKonyv->sKonyvGeneralFile.c_str()) == false )
   {
      bRet = false;
   }
   if( pKonyv->CheckSolariumKonyv(pKonyv->sKonyvSzolariumFile.c_str()) == false )
   {
      bRet = false;
   }
   if( pKosar->CheckDataToFile(pKosar->sKosarFile.c_str()) == false )
   {
      bRet = false;
   }
   if( MainSettings->CheckSettingsToFile(SETTINGS_FILE) == false )
   {
      bRet = false;
   }
   if( pPenztar->CheckDataToFile(pPenztar->sPenztarFile.c_str()) == false )
   {
      bRet = false;
   }
   if( pPenztar->CheckPenztarActions(pPenztar->sPenztarLogFile.c_str()) == false )
   {
      bRet = false;
   }
   if( pTermek->CheckDataToFile(pTermek->sTermekFile.c_str()) == false )
   {
      bRet = false;
   }
   if( pTermekTipus->CheckDataToFile(pTermekTipus->sTermekTipusFile.c_str()) == false )
   {
      bRet = false;
   }
   if( pTermekTipus->CheckDataToFileAsg(pTermekTipus->sTermekTipusAsgFile.c_str()) == false )
   {
      bRet = false;
   }
   if( pUser->CheckDataToFile(pUser->sUserFile.c_str()) == false )
   {
      bRet = false;
   }

   if( bRet )
   {
      for( int i=0; i<MainSettings->GetCountSolarium(); i++ )
      {
         if( pSzolarium[i]->CheckDataToFile(pSzolarium[i]->DataFileName.c_str()) == false )
         {
            bRet = false;
            break;
         }
      }
   }

   return bRet;
}
//---------------------------------------------------------------------------
bool TFormMain::SaveDatabase()
{
   bool bRet = true;

   if( !pBerletek->SaveBerlettipus(pBerletek->sBerletTipusFile.c_str()) ||
       !pBerletek->SaveBerlet(pBerletek->sBerletFile.c_str()) ||
       !pBerletek->SaveBerlethasznalat(pBerletek->sBerletHasznalatFile.c_str()) ||
       !pKonyv->SaveGeneralKonyv(pKonyv->sKonyvGeneralFile.c_str()) ||
       !pKonyv->SaveSolariumKonyv(pKonyv->sKonyvSzolariumFile.c_str()) ||
       !pKosar->SaveDataToFile(pKosar->sKosarFile.c_str()) ||
       !MainSettings->SaveSettingsToFile(SETTINGS_FILE) ||
       !pPenztar->SaveDataToFile(pPenztar->sPenztarFile.c_str()) ||
       !pPenztar->SavePenztarActions(pPenztar->sPenztarLogFile.c_str()) ||
       !pTermek->SaveDataToFile(pTermek->sTermekFile.c_str()) ||
       !pTermekTipus->SaveDataToFile(pTermekTipus->sTermekTipusFile.c_str()) ||
       !pTermekTipus->SaveDataToFileAsg(pTermekTipus->sTermekTipusAsgFile.c_str()) ||
       !pUser->SaveDataToFile(pUser->sUserFile.c_str()) )
   {
      bRet = false;
   }
   else
   {
      for( int i=0; i<MainSettings->GetCountSolarium(); i++ )
      {
         if( !pSzolarium[i]->SaveDataToFile(pSzolarium[i]->DataFileName.c_str()) )
         {
            bRet = false;
         }
      }
   }

   return bRet;
}
//---------------------------------------------------------------------------

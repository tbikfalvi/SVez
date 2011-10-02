//---------------------------------------------------------------------------

#include <vcl.h>
#include "Boot.h"
#include "SzolariumMain.h"
#include "Language.h"
#pragma hdrstop
USERES("Szolarium.res");
USEUNIT("ClassArchive.cpp");
USEUNIT("ClassUser.cpp");
USEUNIT("ClassBerlet.cpp");
USEUNIT("ClassGeneral.cpp");
USEUNIT("ClassHardware.cpp");
USEUNIT("ClassKonyv.cpp");
USEUNIT("ClassKosar.cpp");
USEUNIT("ClassMainSettings.cpp");
USEUNIT("ClassPenztar.cpp");
USEUNIT("ClassSerialComm.cpp");
USEUNIT("ClassSolarium.cpp");
USEUNIT("ClassTermek.cpp");
USEFORM("AdatbazisKezeles.cpp", FormAdatbazisKezeles);
USEFORM("AdatBeolvasas.cpp", FormDataRead);
USEFORM("BerletEladas.cpp", FormBerletEladas);
USEFORM("BerletHasznalat.cpp", FormBerletHasznalat);
USEFORM("BerletKezeles.cpp", FormBerlet);
USEFORM("Boot.cpp", FormBoot);
USEFORM("UserKezeles.cpp", FormUserKezeles);
USEFORM("DialogComment.cpp", FormCommentDialog);
USEFORM("DialogInput.cpp", FormInputDialog);
USEFORM("DialogSelectDir.cpp", FormDialogSelectDir);
USEFORM("ExtendedViewer.cpp", FormExtendedViewer);
USEFORM("Fizetes.cpp", FormFizetes);
USEFORM("HardwareTeszt.cpp", FormHardverTeszt);
USEFORM("HelpAbout.cpp", FormHelpAbout);
USEFORM("Kosar.cpp", FormKosar);
USEFORM("Lista.cpp", FormLista);
USEFORM("PasswordChange.cpp", FormPasswordChange);
USEFORM("PasswordCheck.cpp", FormPasswordCheck);
USEFORM("PenztarKezeles.cpp", FormPenztarKezeles);
USEFORM("SystemSettings.cpp", FormSystemSettings);
USEFORM("SzolariumAdat.cpp", FormSzolariumAdat);
USEFORM("SzolariumMain.cpp", FormMain);
USEUNIT("SzolariumMainMenu.cpp");
USEUNIT("SzolariumMainStartStop.cpp");
USEUNIT("SzolariumMainToolbar.cpp");
USEFORM("TermekEladas.cpp", FormTermekEladas);
USEFORM("TermekKezeles.cpp", FormTermekKezeles);
USEFORM("TermekListaEladas.cpp", FormTermekListaEladas);
USEFORM("Language.cpp", FormLanguage);
USEFORM("TermekTipusKezeles.cpp", FormTermekTipus);
USEUNIT("ClassTermekTipus.cpp");
USEFORM("BerletPin.cpp", FormBerletPIN);
USEFORM("RendszerAdmin.cpp", SystemAdmin);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   FILE  *file = NULL;

   if( (file = fopen( "fsv.log", "at" )) != NULL )
   {
      fputs( "\n", file );
      fputs( FormatDateTime("yyyy/mm/dd\thh:nn:ss\t",Now()).c_str(), file );
      fputs( "___________________________________________________________________\n", file );
      fputs( FormatDateTime("yyyy/mm/dd\thh:nn:ss\t",Now()).c_str(), file );
      fputs( "\n", file );
      fputs( FormatDateTime("yyyy/mm/dd\thh:nn:ss\t",Now()).c_str(), file );
      fputs( "Alkalmazás indítása\n", file );
      fclose( file );
   }

   try
   {
      Application->Initialize();
      Application->Title = "Szolárium Vezérlõ";
       Application->CreateForm(__classid(TFormMain), &FormMain);
       Application->CreateForm(__classid(TFormLanguage), &FormLanguage);
       Application->CreateForm(__classid(TFormBoot), &FormBoot);
       Application->CreateForm(__classid(TFormAdatbazisKezeles), &FormAdatbazisKezeles);
       Application->CreateForm(__classid(TFormDataRead), &FormDataRead);
       Application->CreateForm(__classid(TFormBerletEladas), &FormBerletEladas);
       Application->CreateForm(__classid(TFormBerletHasznalat), &FormBerletHasznalat);
       Application->CreateForm(__classid(TFormBerlet), &FormBerlet);
       Application->CreateForm(__classid(TFormUserKezeles), &FormUserKezeles);
       Application->CreateForm(__classid(TFormCommentDialog), &FormCommentDialog);
       Application->CreateForm(__classid(TFormInputDialog), &FormInputDialog);
       Application->CreateForm(__classid(TFormDialogSelectDir), &FormDialogSelectDir);
       Application->CreateForm(__classid(TFormExtendedViewer), &FormExtendedViewer);
       Application->CreateForm(__classid(TFormFizetes), &FormFizetes);
       Application->CreateForm(__classid(TFormHardverTeszt), &FormHardverTeszt);
       Application->CreateForm(__classid(TFormHelpAbout), &FormHelpAbout);
       Application->CreateForm(__classid(TFormKosar), &FormKosar);
       Application->CreateForm(__classid(TFormLista), &FormLista);
       Application->CreateForm(__classid(TFormPasswordChange), &FormPasswordChange);
       Application->CreateForm(__classid(TFormPasswordCheck), &FormPasswordCheck);
       Application->CreateForm(__classid(TFormPenztarKezeles), &FormPenztarKezeles);
       Application->CreateForm(__classid(TFormSystemSettings), &FormSystemSettings);
       Application->CreateForm(__classid(TFormSzolariumAdat), &FormSzolariumAdat);
       Application->CreateForm(__classid(TFormTermekEladas), &FormTermekEladas);
       Application->CreateForm(__classid(TFormTermekKezeles), &FormTermekKezeles);
       Application->CreateForm(__classid(TFormTermekListaEladas), &FormTermekListaEladas);
       Application->CreateForm(__classid(TFormTermekTipus), &FormTermekTipus);
       Application->CreateForm(__classid(TFormBerletPIN), &FormBerletPIN);
       Application->CreateForm(__classid(TSystemAdmin), &SystemAdmin);
       FormMain->InitVariables();
      FormBoot->Show();
      FormBoot->Update();
      FormBoot->LabelVersion->Caption = FormLanguage->LangStr(STR_INF_VERSION_NUMBER) + FormMain->MainSettings->strVersionNumber;
      if( !FormMain->pHardware->DEMO )
      {
         FormMain->pHardware->DEMO = FormMain->MainSettings->GetIntegerValueFromRegistry( "DemoMode", 1 );
      }

      int nSumError = 0;

      for( int i=0; i<(int)FormMain->ErrorList.size(); i++ )
      {
         nSumError += FormMain->ErrorList[i].nErrType;
         FormBoot->strLogLine = FormMain->GetErrorMessageText( i );
         FormBoot->AddBootMessage();
         Sleep( 500 );
      }

      if( nSumError > 0 )
      {
         FormBoot->strLogLine = FormLanguage->LangStr(STR_APPLICATION_INIT_HIBA);
      }
      else
      {
         FormBoot->strLogLine = FormLanguage->LangStr(STR_APPLICATION_INIT_OK);
      }
      FormBoot->AddBootMessage();
      if( FormMain->SComm != NULL && !FormMain->pHardware->DEMO )
      {
         FormMain->SComm->InitCommunication( FormMain->MainSettings->GetComPort(), FormMain->MainSettings->GetBaudRate(), FormMain->MainSettings->GetParity() );
         FormBoot->strLogLine.sprintf( FormLanguage->LangStr(STR_COM_OPEN).c_str(), FormMain->MainSettings->GetComPort() );
         FormBoot->AddBootMessage();
         int i;
         for( i=0; i<5; i++ )
         {
            if( FormMain->SComm->OpenPort() )
            {
               FormBoot->strLogLine.sprintf( FormLanguage->LangStr(STR_COM_OPEN_OK).c_str(), FormMain->MainSettings->GetComPort() );
               FormBoot->AddBootMessage(true);
               break;
            }
            Sleep( 1000 );
         }
         if( i == 5 )
         {
            FormBoot->strLogLine.sprintf( FormLanguage->LangStr(STR_COM_OPEN_FAILED).c_str(), FormMain->MainSettings->GetComPort() );
            FormBoot->AddBootMessage(true);
         }
         for( i=0; i<(int)FormMain->pSzolarium.size(); i++ )
         {
            FormMain->pHardware->LED_Modul[ i ].bVan = false;
            FormMain->pHardware->LED_Modul[ i ].bSendIras = false;
            FormMain->pHardware->LED_Modul[ i ].bSendStart = false;
            FormMain->pHardware->LED_Modul[ i ].bSendEnd = false;
            FormMain->pHardware->LED_Modul[ i ].bStop = false;
         }
         FormBoot->strLogLine = FormLanguage->LangStr(STR_HARDWARE_INIT);
         FormBoot->AddBootMessage();
         FormMain->pHardware->SComm = FormMain->SComm;
         FormMain->pHardware->bTest = true;
         FormMain->pHardware->wRelay = 0;
         FormBoot->strLogLine = FormLanguage->LangStr(STR_HARDWARE_CONNECT);
         FormBoot->AddBootMessage();
         if( FormMain->pHardware->bSearchHardware() )
         {
            FormBoot->strLogLine = FormLanguage->LangStr(STR_HARDWARE_CONNECT_OK);
            FormBoot->AddBootMessage(true);
            FormBoot->strLogLine = FormLanguage->LangStr(STR_MODUL_CHECK);
            FormBoot->AddBootMessage();
            for( i=0; i<MAX_MODUL_SZAM; i++ )
            {
               FormMain->pHardware->LED_Modul[ i ].bVan = false;
            }
            char strEEPROM[100];

            memset( strEEPROM, 0, sizeof(strEEPROM) );
            FormMain->pHardware->bReedEEprom( 0, strEEPROM);
            if( strEEPROM[0] == 0 )
            {
               sprintf( strEEPROM, "%02d ", (int)FormMain->pSzolarium.size() );
               FormMain->pHardware->bWriteEEprom( 0, strEEPROM );
            }
            FormMain->strCaption = AnsiString( strEEPROM+2 );
            FormBoot->strLogLine = AnsiString( strEEPROM );
            FormBoot->AddBootMessage();
            if( FormBoot->strLogLine.SubString(1,2).ToInt() < (int)FormMain->pSzolarium.size() )
            {
               throw Exception( FormLanguage->LangStr(STR_ERR_INVALID_SOLCOUNT) );
            }
            for( i=0; i<(int)FormMain->pSzolarium.size(); i++ )
            {
               FormBoot->strLogLine.sprintf( FormLanguage->LangStr(STR_MODUL_X_CHECK).c_str(), i+1 );
               FormBoot->AddBootMessage();

               //Kereses max 7-szer
               BYTE j = 0;
               do
               {
                  FormMain->pHardware->byLedModulKeres( i );
                  j++;
               }while( j<8 && !FormMain->pHardware->LED_Modul[ i ].bVan );

               if( FormMain->pHardware->LED_Modul[ i ].bVan )
               {
                  FormBoot->strLogLine.sprintf( FormLanguage->LangStr(STR_MODUL_X_CHECK_OK).c_str(), i+1 );
                  FormBoot->AddBootMessage(true);
               }
               else
               {
                  FormBoot->strLogLine.sprintf( FormLanguage->LangStr(STR_MODUL_X_CHECK_FAILED).c_str(), i+1 );
                  FormBoot->AddBootMessage(true);
               }
            }
            FormBoot->strLogLine = FormLanguage->LangStr(STR_MODUL_CHECK_FINISHED);
            FormBoot->AddBootMessage();
         }
         else
         {
            FormBoot->strLogLine = FormLanguage->LangStr(STR_HARDWARE_CONNECT_FAILED);
            FormBoot->AddBootMessage(true);
            FormMain->bErrorDuringBoot = true;
            throw Exception( FormLanguage->LangStr(STR_ERR_HARDWARE_COMM) );
         }
         FormBoot->strLogLine = FormLanguage->LangStr(STR_APPLICATION_START);
         FormBoot->AddBootMessage();
         Sleep(2000);
         FormMain->pHardware->bTest = false;
      }
      else if( FormMain->pHardware->DEMO )
      {
         FormBoot->strLogLine = FormLanguage->LangStr(STR_MODE_DEMO);
         FormBoot->AddBootMessage();
         FormBoot->strLogLine = FormLanguage->LangStr(STR_APPLICATION_START);
         FormBoot->AddBootMessage();
         Sleep(2000);
         FormMain->pHardware->bTest = false;
      }
      delete FormBoot;
      FormMain->TimerSolarium->Enabled = true;
      FormMain->TimerMain->Enabled = true;
      FormMain->TimerUserLock->Enabled = true;
      Application->Run();
   }
   catch (Exception &e)
   {
/*      FormMain->pHardware->DEMO = true;
      FormBoot->strLogLine = FormLanguage->LangStr(STR_MODE_DEMO);
      FormBoot->AddBootMessage();
      FormBoot->strLogLine = FormLanguage->LangStr(STR_APPLICATION_START);
      FormBoot->AddBootMessage();
      Sleep(5000);
      delete FormBoot;
      FormMain->TimerSolarium->Enabled = true;
      FormMain->TimerMain->Enabled = true;
      FormMain->TimerUserLock->Enabled = true;
      Application->Run();
*/      AnsiString eMessage = FormLanguage->LangStr(STR_ERR_UNABLE_TO_CONTINUE) + e.Message;
      Application->MessageBox( eMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_ERROR).c_str(), MB_ICONSTOP );
      Application->Terminate();
   }
   return 0;
}
//---------------------------------------------------------------------------

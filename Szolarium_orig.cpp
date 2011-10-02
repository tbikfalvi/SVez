//---------------------------------------------------------------------------

#include <vcl.h>
#include "Boot.h"
#include "SzolariumMain.h"
#include "Language.h"
#pragma hdrstop
USERES("Szolarium.res");
USEFORM("SzolariumMain.cpp", FormMain);
USEUNIT("ClassSolarium.cpp");
USEFORM("HelpAbout.cpp", FormHelpAbout);
USEFORM("SzolariumAdat.cpp", FormSzolariumAdat);
USEUNIT("ClassMainSettings.cpp");
USEFORM("PasswordChange.cpp", FormPasswordChange);
USEUNIT("ClassGeneral.cpp");
USEUNIT("ClassSerialComm.cpp");
USEFORM("SystemSettings.cpp", FormSystemSettings);
USEFORM("AdatBeolvasas.cpp", FormDataRead);
USEUNIT("ClassBerlet.cpp");
USEUNIT("ClassTermek.cpp");
USEFORM("BerletKezeles.cpp", FormBerlet);
USEFORM("BerletEladas.cpp", FormBerletEladas);
USEFORM("PasswordCheck.cpp", FormPasswordCheck);
USEFORM("BerletHasznalat.cpp", FormBerletHasznalat);
USEFORM("TermekKezeles.cpp", FormTermekKezeles);
USEFORM("DialogInput.cpp", FormInputDialog);
USEFORM("TermekEladas.cpp", FormTermekEladas);
USEFORM("Fizetes.cpp", FormFizetes);
USEFORM("Kosar.cpp", FormKosar);
USEUNIT("ClassKosar.cpp");
USEUNIT("ClassKonyv.cpp");
USEUNIT("SzolariumMainMenu.cpp");
USEUNIT("SzolariumMainStartStop.cpp");
USEFORM("Lista.cpp", FormLista);
USEUNIT("SzolariumMainToolbar.cpp");
USEFORM("TermekListaEladas.cpp", FormTermekListaEladas);
USEFORM("DialogComment.cpp", FormCommentDialog);
USEUNIT("ClassUser.cpp");
USEUNIT("ClassPenztar.cpp");
USEFORM("UserKezeles.cpp", FormUserKezeles);
USEFORM("PenztarKezeles.cpp", FormPenztarKezeles);
USEUNIT("ClassArchive.cpp");
USEFORM("HardwareTeszt.cpp", FormHardverTeszt);
USEUNIT("ClassHardware.cpp");
USEFORM("DialogSelectDir.cpp", FormDialogSelectDir);
USEFORM("Boot.cpp", FormBoot);
USEFORM("AdatbazisKezeles.cpp", FormAdatbazisKezeles);
USEFORM("ExtendedViewer.cpp", FormExtendedViewer);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
      Application->Initialize();
      Application->CreateForm(__classid(TFormMain), &FormMain);
       Application->CreateForm(__classid(TFormBoot), &FormBoot);
       FormMain->MainSettings->LOG1( "Alkalmazás indítása" );
       FormBoot->LabelVersion->Caption = AnsiString( STR_INF_VERSION_NUMBER ) + FormMain->MainSettings->strVersionNumber;
       FormBoot->Show();
       FormBoot->Update();
       Application->CreateForm(__classid(TFormHelpAbout), &FormHelpAbout);
       Application->CreateForm(__classid(TFormSzolariumAdat), &FormSzolariumAdat);
       Application->CreateForm(__classid(TFormPasswordChange), &FormPasswordChange);
       Application->CreateForm(__classid(TFormSystemSettings), &FormSystemSettings);
       Application->CreateForm(__classid(TFormDataRead), &FormDataRead);
       Application->CreateForm(__classid(TFormBerlet), &FormBerlet);
       Application->CreateForm(__classid(TFormBerletEladas), &FormBerletEladas);
       Application->CreateForm(__classid(TFormPasswordCheck), &FormPasswordCheck);
       Application->CreateForm(__classid(TFormBerletHasznalat), &FormBerletHasznalat);
       Application->CreateForm(__classid(TFormTermekKezeles), &FormTermekKezeles);
       Application->CreateForm(__classid(TFormInputDialog), &FormInputDialog);
       Application->CreateForm(__classid(TFormTermekEladas), &FormTermekEladas);
       Application->CreateForm(__classid(TFormFizetes), &FormFizetes);
       Application->CreateForm(__classid(TFormKosar), &FormKosar);
       Application->CreateForm(__classid(TFormLista), &FormLista);
       Application->CreateForm(__classid(TFormTermekListaEladas), &FormTermekListaEladas);
       Application->CreateForm(__classid(TFormCommentDialog), &FormCommentDialog);
       Application->CreateForm(__classid(TFormUserKezeles), &FormUserKezeles);
       Application->CreateForm(__classid(TFormPenztarKezeles), &FormPenztarKezeles);
       Application->CreateForm(__classid(TFormHardverTeszt), &FormHardverTeszt);
       Application->CreateForm(__classid(TFormDialogSelectDir), &FormDialogSelectDir);
       Application->CreateForm(__classid(TFormAdatbazisKezeles), &FormAdatbazisKezeles);
       Application->CreateForm(__classid(TFormExtendedViewer), &FormExtendedViewer);
      FormMain->pHardware->DEMO = FormMain->MainSettings->GetIntegerValueFromRegistry( "DemoMode", 1 );
      FormBoot->strLogLine = AnsiString( STR_APPLICATION_INIT_OK );
      FormBoot->AddBootMessage(true);
      if( FormMain->SComm != NULL )
      {
         FormMain->SComm->InitCommunication( FormMain->MainSettings->GetComPort(), FormMain->MainSettings->GetBaudRate(), FormMain->MainSettings->GetParity() );
         FormBoot->strLogLine.sprintf( STR_COM_OPEN, FormMain->MainSettings->GetComPort() );
         FormBoot->AddBootMessage();
         int i;
         for( i=0; i<5; i++ )
         {
            if( FormMain->SComm->OpenPort() )
            {
               FormBoot->strLogLine.sprintf( STR_COM_OPEN_OK, FormMain->MainSettings->GetComPort() );
               FormBoot->AddBootMessage(true);
               break;
            }
            Sleep( 1000 );
         }
         if( i == 5 )
         {
            FormBoot->strLogLine = AnsiString( STR_COM_OPEN_FAILED, FormMain->MainSettings->GetComPort() );
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
         if( FormMain->pHardware->DEMO )
         {
            FormBoot->strLogLine = AnsiString( STR_MODE_DEMO );
            FormBoot->AddBootMessage();
         }
         else
         {
            FormBoot->strLogLine = AnsiString( STR_HARDWARE_INIT );
            FormBoot->AddBootMessage();
            FormMain->pHardware->SComm = FormMain->SComm;
            FormMain->pHardware->bTest = true;
            FormMain->pHardware->wRelay = 0;
            FormBoot->strLogLine = AnsiString( STR_HARDWARE_CONNECT );
            FormBoot->AddBootMessage();
            if( FormMain->pHardware->bSearchHardware() )
            {
               FormBoot->strLogLine = AnsiString( STR_HARDWARE_CONNECT_OK );
               FormBoot->AddBootMessage(true);
               FormBoot->strLogLine = AnsiString( STR_MODUL_CHECK );
               FormBoot->AddBootMessage();
               for( i=0; i<MAX_MODUL_SZAM; i++ )
               {
                  FormMain->pHardware->LED_Modul[ i ].bVan = false;
               }
               for( i=0; i<(int)FormMain->pSzolarium.size(); i++ )
               {
                  FormBoot->strLogLine.sprintf( STR_MODUL_X_CHECK, i+1 );
                  FormBoot->AddBootMessage();
/*                  FormMain->pHardware->LED_Modul[ i ].bVan = false;
                  FormMain->pHardware->LED_Modul[ i ].bSendIras = false;
                  FormMain->pHardware->LED_Modul[ i ].bSendStart = false;
                  FormMain->pHardware->LED_Modul[ i ].bSendEnd = false;
                  FormMain->pHardware->LED_Modul[ i ].bStop = false;
*/
                  //Kereses max 7-szer
                  BYTE j = 0;
                  do
                  {
                     FormMain->pHardware->byLedModulKeres( i );
                     j++;
                  }while( j<8 && !FormMain->pHardware->LED_Modul[ i ].bVan );

                  if( FormMain->pHardware->LED_Modul[ i ].bVan )
                  {
                     FormBoot->strLogLine.sprintf( STR_MODUL_X_CHECK_OK, i+1 );
                     FormBoot->AddBootMessage(true);
                  }
                  else
                  {
                     FormBoot->strLogLine.sprintf( STR_MODUL_X_CHECK_FAILED, i+1 );
                     FormBoot->AddBootMessage(true);
                  }
               }
               FormBoot->strLogLine = AnsiString( STR_MODUL_CHECK_FINISHED );
               FormBoot->AddBootMessage();
            }
            else
            {
               FormBoot->strLogLine = AnsiString( STR_HARDWARE_CONNECT_FAILED );
               FormBoot->AddBootMessage(true);
               FormMain->bErrorDuringBoot = true;
               throw Exception( AnsiString( STR_ERR_HARDWARE_COMM ) );
            }
         }
         FormBoot->strLogLine = AnsiString( STR_APPLICATION_START );
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
      FormMain->pHardware->DEMO = 0;
      FormBoot->strLogLine = AnsiString( STR_MODE_DEMO );
      FormBoot->AddBootMessage();
      FormBoot->strLogLine = AnsiString( STR_APPLICATION_START );
      FormBoot->AddBootMessage();
      Sleep(5000);
      delete FormBoot;
      FormMain->TimerSolarium->Enabled = true;
      FormMain->TimerMain->Enabled = true;
      FormMain->TimerUserLock->Enabled = true;
      Application->Run();
//      AnsiString eMessage = STR_ERR_UNABLE_TO_CONTINUE + e.Message;
//      Application->MessageBox( eMessage.c_str(), STR_MSGBOX_ERROR, MB_ICONSTOP );
//      Application->Terminate();
   }
   return 0;
}
//---------------------------------------------------------------------------

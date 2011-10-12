//---------------------------------------------------------------------------

#include <vcl.h>
#include <Registry.hpp>
#pragma hdrstop

#include "SetupMain.h"
#include "SerialClass.h"
#include "HW_COMMAND.h"
#include "DialogSelectDir.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormInstallMain *FormInstallMain;
//---------------------------------------------------------------------------
__fastcall TFormInstallMain::TFormInstallMain(TComponent* Owner)
   : TForm(Owner)
{
   nCountSolarium = 0;

   SetIntegerValueInRegistry( "LogLevel", 1 );
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::FormShortCut(TWMKey &Msg, bool &Handled)
{
   if (Msg.CharCode == VK_RETURN)
   {
      Handled = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::FormActivate(TObject *Sender)
{
   strCurrDir = GetCurrentDir();
   if( strcmp( strCurrDir.AnsiLastChar(), "\\" ) != 0 )
      strCurrDir += AnsiString( "\\" );

   try
   {
      if( (pSComm = new CS_SerialComm()) == NULL )
      {
         throw Exception( AnsiString( "\n"
                                      "Hiba leírás: Operációs rendszer hiba."
                                      "Hiba kód: sys007" ) );
      }

      if( (pHardware = new CS_Hardware()) == NULL )
      {
         throw Exception( AnsiString( "\n"
                                      "Hiba leírás: Operációs rendszer hiba."
                                      "Hiba kód: sys010" ) );
      }
   }
   catch(const Exception& e)
   {
      AnsiString eMessage = LanguageStrings->Items->Strings[0];
      eMessage += e.Message;
      Application->MessageBox( eMessage.c_str(), "Hiba", MB_ICONSTOP );
      Application->Terminate();
   }
   BitBtnRefreshClick( Sender );
   BitBtnNext->Enabled = true;

   pHardware->SComm = pSComm;

   pPages.push_back( PanelDirectory );
   pPages.push_back( PanelSetupType );
   pPages.push_back( PanelSzolarium );
   pPages.push_back( PanelTablazat );
   pPages.push_back( PanelHadver );  
   pPages.push_back( PanelSummary );

   unsigned int i;

   for( i=0; i<pPages.size(); i++ )
   {
      pPages[i]->Visible = false;
      pPages[i]->Enabled = false;
   }

   nPageCount = 0;

   pPages[nPageCount]->Visible = true;
   pPages[nPageCount]->Enabled = true;
   LabelPageCaption->Caption = pPages[nPageCount]->Hint;

   FillControlsWithData();

//   FormDialogSelectDir->DriveComboBox->Drive = 'C';
//   FormDialogSelectDir->DirectoryListBox->Directory = "Program Files";
   EditDirectory->Text = "C:\\Program Files\\Sensolite";

   AnsiString  strTemp = GetStringValueFromRegistry( "InstallDir", "<not defined>" );

   if( strTemp.Length() > 0 && strTemp.AnsiCompare( "<not defined>" ) != 0 )
   {
      RB_Setup->Enabled = false;
      RB_Setup->Checked = false;
      RB_Update->Enabled = true;
      RB_Update->Checked = true;
      RB_Remove->Enabled = true;

//      FormDialogSelectDir->DriveComboBox->Drive = *strTemp.SubString(1,1).AnsiLastChar();
//      FormDialogSelectDir->DirectoryListBox->Directory = "";
      EditDirectory->Text = strTemp;
   }

   if( GetIntegerValueFromRegistry( "PanelCount", 0 ) > 0 )
   {
      nCountSolarium = GetIntegerValueFromRegistry( "PanelCount", 0 );
      EditSzolariumCount->Text = AnsiString( nCountSolarium );
      EditSzolariumCount->ReadOnly = true;
      EditSzolariumCount->Color = clBtnFace;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::TabControlTablazatChange(TObject *Sender)
{
   switch( TabControlTablazat->TabIndex )
   {
      case 0:
         GroupBoxTablazatNorm->Enabled = true;
         GroupBoxTablazatNorm->Visible = true;
         GroupBoxTablazatKedv->Enabled = false;
         GroupBoxTablazatKedv->Visible = false;
         break;
      case 1:
         GroupBoxTablazatNorm->Enabled = false;
         GroupBoxTablazatNorm->Visible = false;
         GroupBoxTablazatKedv->Enabled = true;
         GroupBoxTablazatKedv->Visible = true;
         break;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::BitBtnPrevClick(TObject *Sender)
{
   pPages[nPageCount]->Visible = false;
   pPages[nPageCount]->Enabled = false;
   nPageCount--;
   pPages[nPageCount]->Visible = true;
   pPages[nPageCount]->Enabled = true;
   LabelPageCaption->Caption = pPages[nPageCount]->Hint;
   pPages[nPageCount]->SetFocus();

   if( nPageCount == 0 )
   {
      BitBtnPrev->Enabled = false;
   }
   BitBtnNext->Enabled = true;
   BitBtnExit->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::BitBtnNextClick(TObject *Sender)
{
   if( pPages[nPageCount] == PanelHadver &&
       EditSzolariumCount->Text.Length() == 0 )
   {
      Application->MessageBox( LanguageStrings->Items->Strings[21].c_str(),
                               LanguageStrings->Items->Strings[12].c_str(),
                               MB_ICONEXCLAMATION );
      EditSzolariumCount->SetFocus();
      return;
   }

   pPages[nPageCount]->Visible = false;
   pPages[nPageCount]->Enabled = false;
   nPageCount++;
   pPages[nPageCount]->Visible = true;
   pPages[nPageCount]->Enabled = true;
   LabelPageCaption->Caption = pPages[nPageCount]->Hint;
   pPages[nPageCount]->SetFocus();

   if( nPageCount >= pPages.size()-1 )
   {
      BitBtnNext->Enabled = false;
   }
   BitBtnPrev->Enabled = true;

   if( pPages[nPageCount] == PanelHadver )
   {
/******** DEMO TELEPITESHEZ ********************
      BitBtnRefresh->Enabled = false;
      BitBtnTeszt->Enabled = false;
      BitBtnNext->Enabled = true;
***********************************************/
      BitBtnTeszt->SetFocus();
      BitBtnNext->Enabled = false;
      if( RB_Update->Checked )
      {
         BitBtnTesztClick(Sender);
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::BitBtnRefreshClick(TObject *Sender)
{
   pSComm->FillComboWithPorts( ComboBoxPort );

   ComboBoxPort->ItemIndex = 0;
   ComboBoxParity->ItemIndex = 0;
   ComboBoxBaudRate->ItemIndex = 3;

   if( ComboBoxPort->Items->Count > 0 )
      BitBtnTeszt->Enabled = true;
   else
      BitBtnTeszt->Enabled = false;

   BitBtnNext->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::ComboBoxPortChange(TObject *Sender)
{
   BitBtnExit->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::BitBtnTesztClick(TObject *Sender)
{
   try
   {
      int Port = atoi((ComboBoxPort->Items->Strings[ComboBoxPort->ItemIndex]).c_str()+3);
      DWORD BaudRate = atoi(ComboBoxBaudRate->Items->Strings[ComboBoxBaudRate->ItemIndex].c_str());
      DWORD Parity = ComboBoxParity->ItemIndex;

      pSComm->InitCommunication( Port, BaudRate, Parity );
      ListBoxLog->Items->Add( LanguageStrings->Items->Strings[1] );
      Update();
      if( pSComm->OpenPort() )
      {
         ListBoxLog->Items->Add( LanguageStrings->Items->Strings[2] );
         Update();
         pHardware->bTest = true;
         pHardware->wRelay = 0;

         if( pHardware->bSearchHardware() )
         {
            ListBoxLog->Items->Add( LanguageStrings->Items->Strings[3] );
            Update();
            BitBtnNext->Enabled = true;
            SetIntegerValueInRegistry( "ComPort", Port );
            SetIntegerValueInRegistry( "BaudRate", BaudRate );
            SetIntegerValueInRegistry( "Parity", Parity );

            if( EditSzolariumCount->Text.Length() == 0 )
            {
               EditSzolariumCount->Text = "0";
            }
            nCountSolarium = EditSzolariumCount->Text.ToInt();
            char strEEPROM[100];

            memset( strEEPROM, 0, sizeof(strEEPROM) );
            pHardware->bReedEEprom( 0, strEEPROM );
            if( strEEPROM[0] != 'ÿ' )
            {
               AnsiString strTemp = AnsiString( strEEPROM );
               if( strTemp.SubString(1,2).ToInt() < nCountSolarium ||
                   nCountSolarium == 0 )
               {
                  nCountSolarium = strTemp.SubString(1,2).ToInt();
                  EditSzolariumCount->Text = AnsiString( nCountSolarium );
               }
               AnsiString strMsg;
               strMsg = strMsg.sprintf( LangStr(20).c_str(),
                                        strTemp.SubString(1,2).c_str(),
                                        strTemp.SubString(3,strTemp.Length()-2).c_str() );
               if( Application->MessageBox( strMsg.c_str(),
                                            LanguageStrings->Items->Strings[17].c_str(),
                                            MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 ) == IDYES )
               {
                  nCountSolarium = strTemp.SubString(1,2).ToInt();
                  EditSzolariumCount->Text = AnsiString( nCountSolarium );
                  EditApplicationCaption->Text = strTemp.SubString(3,strTemp.Length()-2);
               }
            }
            BitBtnNext->Enabled = true;
         }
         else
         {
            ListBoxLog->Items->Add( LanguageStrings->Items->Strings[4] );
            Update();
            BitBtnNext->Enabled = false;
         }

         ListBoxLog->Items->Add( LanguageStrings->Items->Strings[5] );
         Update();
         pSComm->ClosePort();
      }
      else
      {
         ListBoxLog->Items->Add( LanguageStrings->Items->Strings[19] );
         Update();
         BitBtnNext->Enabled = false;
      }
   }
   catch(const Exception& e)
   {
      if( pHardware->bTest == true )
      {
         pSComm->ClosePort();
      }
      Application->MessageBox( e.Message.c_str(),
                               LanguageStrings->Items->Strings[12].c_str(),
                               MB_ICONEXCLAMATION );
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::BitBtnCancelClick(TObject *Sender)
{
   if( Application->MessageBox( LanguageStrings->Items->Strings[18].c_str(),
                                LanguageStrings->Items->Strings[17].c_str(),
                                MB_YESNO|MB_DEFBUTTON2|MB_ICONQUESTION ) == IDYES )
   {
      ModalResult = mrCancel;
      Close();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::BitBtnExitClick(TObject *Sender)
{
   try
   {
      FILE           *file = NULL;
      unsigned int   nSize = 0;
      AnsiString     strPath = EditDirectory->Text.c_str() + AnsiString( "\\" );
      AnsiString     strFile;

      SaveDataFromControls();

      MemoProgress->Visible = true;
      nLine = 0;

      if( RB_Setup->Checked )
      {
         AddProgressLine( LanguageStrings->Items->Strings[22] );

         nCountSolarium = EditSzolariumCount->Text.ToInt();
         char strEEPROM[100];

         int Port = atoi((ComboBoxPort->Items->Strings[ComboBoxPort->ItemIndex]).c_str()+3);
         DWORD BaudRate = atoi(ComboBoxBaudRate->Items->Strings[ComboBoxBaudRate->ItemIndex].c_str());
         DWORD Parity = ComboBoxParity->ItemIndex;

         pSComm->InitCommunication( Port, BaudRate, Parity );
         pSComm->OpenPort();
         memset( strEEPROM, 0, sizeof(strEEPROM) );
         if( pHardware->bSearchHardware() )
         {
            pHardware->bReedEEprom( 0, strEEPROM );
            if( strEEPROM[0] == 'ÿ' )
            {
               sprintf( strEEPROM, "%02d%s", nCountSolarium,
                                             EditApplicationCaption->Text.SubString(1,98).c_str() );
               pHardware->bWriteEEprom( 0, strEEPROM );
            }
            else
            {
               AnsiString strTemp = AnsiString( strEEPROM );
               if( strTemp.SubString(1,2).ToInt() < nCountSolarium )
               {
                  nCountSolarium = strTemp.SubString(1,2).ToInt();
                  EditSzolariumCount->Text = AnsiString( nCountSolarium );
               }
               EditSzolariumCount->Text = AnsiString( nCountSolarium );
               sprintf( strEEPROM, "%02d%s", strTemp.SubString(1,2).ToInt(),
                                             EditApplicationCaption->Text.SubString(1,98).c_str() );
               pHardware->bWriteEEprom( 0, strEEPROM );
            }
            AddProgressLine( LanguageStrings->Items->Strings[23], true );
         }
         else
         {
            AddProgressLine( LanguageStrings->Items->Strings[24], true );
         }
         pSComm->ClosePort();

         AddProgressLine( LanguageStrings->Items->Strings[25] );
         
         CreateDirectory( EditDirectory->Text.c_str(), NULL );

         SetStringValueInRegistry( "InstallDir", EditDirectory->Text );
         SetIntegerValueInRegistry( "PanelCount", nCountSolarium );
         SetIntegerValueInRegistry( "MainWindowLeft", 0 );
         SetIntegerValueInRegistry( "MainWindowTop", 0 );
         SetIntegerValueInRegistry( "WindowResolution", 2 );
         SetIntegerValueInRegistry( "CurrentSession", 1 );
         SetStringValueInRegistry( "CurrentUser", "Adminisztrátor" );
         SetIntegerValueInRegistry( "ShowExtendedWindow", 0 );
         SetIntegerValueInRegistry( "ExtendedWindowLeft", 0 );
         SetIntegerValueInRegistry( "ExtendedWindowTop", 0 );
         SetIntegerValueInRegistry( "DemoMode", 0 );

         AddProgressLine( LanguageStrings->Items->Strings[26], true );

         strFile.sprintf( "%s%s", strPath.c_str(), BERLETTIPUS_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), BERLETTIPUS_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         fwrite( BERLETTIPUS_FILE_VERSION, 10, 1, file );
         fwrite( &nSize, sizeof(unsigned int), 1, file );
         fclose( file );
         strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), BERLETTIPUS_FILE );
         AddProgressLine( true );

         strFile.sprintf( "%s%s", strPath.c_str(), BERLET_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), BERLET_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         fwrite( BERLET_FILE_VERSION, 10, 1, file );
         fwrite( &nSize, sizeof(unsigned int), 1, file );
         fclose( file );
         strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), BERLET_FILE );
         AddProgressLine( true );

         strFile.sprintf( "%s%s", strPath.c_str(), BERLETHASZNALAT_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), BERLETHASZNALAT_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         fwrite( BERLETHASZNALAT_FILE_VERSION, 10, 1, file );
         fwrite( &nSize, sizeof(unsigned int), 1, file );
         fclose( file );
         strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), BERLETHASZNALAT_FILE );
         AddProgressLine( true );

         strFile.sprintf( "%s%s", strPath.c_str(), KONYVGENERAL_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), KONYVGENERAL_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         fwrite( KONYV_GENERAL_FILE_VERSION, 10, 1, file );
         fwrite( &nSize, sizeof(unsigned int), 1, file );
         fclose( file );
         strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), KONYVGENERAL_FILE );
         AddProgressLine( true );

         strFile.sprintf( "%s%s", strPath.c_str(), KONYVSZOLARIUM_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), KONYVSZOLARIUM_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         fwrite( KONYV_SZOLARIUM_FILE_VERSION, 10, 1, file );
         fwrite( &nSize, sizeof(unsigned int), 1, file );
         fclose( file );
         strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), KONYVSZOLARIUM_FILE );
         AddProgressLine( true );

         strFile.sprintf( "%s%s", strPath.c_str(), KOSAR_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), KOSAR_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         fwrite( KOSAR_FILE_VERSION, 10, 1, file );
         fwrite( &nSize, sizeof(unsigned int), 1, file );
         fclose( file );
         strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), KOSAR_FILE );
         AddProgressLine( true );

         typ_penztar Penztar;

         memset( &Penztar, 0, sizeof(typ_penztar) );
         strFile.sprintf( "%s%s", strPath.c_str(), PENZTAR_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), PENZTAR_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         fwrite( PENZTAR_FILE_VERSION, 10, 1, file );
         fwrite( &Penztar, sizeof(typ_penztar), 1, file );
         fclose( file );
         strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), PENZTAR_FILE );
         AddProgressLine( true );

         strFile.sprintf( "%s%s", strPath.c_str(), PENZTARLOG_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), PENZTARLOG_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         fwrite( PENZTAR_FILE_VERSION, 10, 1, file );
         fclose( file );
         strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), PENZTARLOG_FILE );
         AddProgressLine( true );

         strFile.sprintf( "%s%s", strPath.c_str(), TERMEK_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), TERMEK_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         fwrite( TERMEK_FILE_VERSION, 10, 1, file );
         fwrite( &nSize, sizeof(unsigned int), 1, file );
         fclose( file );
         strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), TERMEK_FILE );
         AddProgressLine( true );

         strFile.sprintf( "%s%s", strPath.c_str(), TERMEKTIPUS_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), TERMEKTIPUS_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         fwrite( TERMEKTIPUS_FILE_VERSION, 10, 1, file );
         fwrite( &nSize, sizeof(unsigned int), 1, file );
         fclose( file );
         strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), TERMEKTIPUS_FILE );
         AddProgressLine( true );

         strFile.sprintf( "%s%s", strPath.c_str(), TERMEKTIPUSASG_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), TERMEKTIPUSASG_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         fwrite( TERMEKTIPUS_FILE_VERSION, 10, 1, file );
         fwrite( &nSize, sizeof(unsigned int), 1, file );
         fclose( file );
         strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), TERMEKTIPUSASG_FILE );
         AddProgressLine( true );

         strFile.sprintf( "%s%s", strPath.c_str(), USER_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), USER_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         fwrite( USER_FILE_VERSION, 10, 1, file );
         fwrite( &nSize, sizeof(unsigned int), 1, file );
         fclose( file );
         strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), USER_FILE );
         AddProgressLine( true );

         strcpy( strPasswordAdmin, "system" );
         strcpy( strPasswordUser, "xxxxxx" );

         pSComm->EnCode( strPasswordAdmin, sizeof(strPasswordAdmin) );
         pSComm->EnCode( strPasswordUser, sizeof(strPasswordUser) );

         strFile.sprintf( "%s%s", strPath.c_str(), SETTINGS_FILE );
         strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), SETTINGS_FILE );
         AddProgressLine();
         file = fopen( strFile.c_str(), "wb" );
         if( file != NULL )
         {
            fwrite( SETTINGS_FILE_VERSION, 10, 1, file );
            fwrite( &nCountSolarium, sizeof(int), 1, file );
            fwrite( strPasswordAdmin, sizeof(strPasswordAdmin), 1, file );
            fwrite( strPasswordUser, sizeof(strPasswordUser), 1, file );
            fclose( file );
            strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), SETTINGS_FILE );
            AddProgressLine( true );
         }

         for( int i=0; i<nCountSolarium; i++ )
         {
            AnsiString   DataFileName = AnsiString( "sdfsv" )+AnsiString( i )+AnsiString( ".dat" );

            memset( stAdat.strNev, 0, sizeof(stAdat.strNev) );
            sprintf( stAdat.strNev, "Szolárium %d", i+1 );
            pSComm->EnCode( stAdat.strNev, sizeof(stAdat.strNev) );

            strFile.sprintf( "%s%s", strPath.c_str(), DataFileName.c_str() );
            strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), DataFileName.c_str() );
            AddProgressLine();
            file = fopen( strFile.c_str(), "wb" );
            fwrite( SOLARIUM_FILE_VERSION, 10, 1, file );
            fwrite( &stAdat, sizeof(typ_szoliadat), 1, file );
            fclose( file );
            strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), DataFileName.c_str() );
            AddProgressLine( true );
         }
      }

      if( RB_Setup->Checked || RB_Update->Checked )
      {
         strFile.sprintf( "%s%s", strCurrDir.c_str(), "Files.lst" );
         if( (file = fopen( strFile.c_str(), "rt" )) != NULL )
         {
            char  strTmp[100];

            memset( strTmp, 0, sizeof(strTmp) );
            while( fgets( strTmp, sizeof(strTmp), file ) )
            {
               if( strTmp[ strlen(strTmp)-1 ] == '\n' )
                  strTmp[ strlen(strTmp)-1 ] = 0;
               pFiles.push_back( strTmp );
            }
            fclose( file );
         }
         else
         {
            pFiles.push_back( "vcl50.bpl" );
            pFiles.push_back( "vclx50.bpl" );
            pFiles.push_back( "borlndmm.dll" );
            pFiles.push_back( "cc3250mt.dll" );
            pFiles.push_back( "Sensolite.exe" );
            pFiles.push_back( "Sensolite.eng" );
            pFiles.push_back( "Sensolite.enu" );
            pFiles.push_back( "Sensolite.hun" );
            pFiles.push_back( "Sensolite.srl" );
            pFiles.push_back( "Felhasznaloi utmutato.pdf" );
         }

         for( unsigned int j=0; j<pFiles.size(); j++ )
         {
            AnsiString  strFrom;

            strProgress.sprintf( LanguageStrings->Items->Strings[31].c_str(), pFiles[j].c_str() );
            AddProgressLine();
            strFrom.sprintf( "%s%s", strCurrDir.c_str(), pFiles[j].c_str() );
            strFile.sprintf( "%s%s", strPath.c_str(), pFiles[j].c_str() );
            SetFileAttributes( strFile.c_str(), FILE_ATTRIBUTE_NORMAL );
            if( CopyFile( strFrom.c_str(), strFile.c_str(), false ) == 0 )
            {
               strProgress.sprintf( LanguageStrings->Items->Strings[33].c_str(), pFiles[j].c_str() );
               AddProgressLine( true );
               AnsiString strMsg;
               strMsg = LanguageStrings->Items->Strings[13] +
                        AnsiString( "\n\n" ) +
                        strFile;
               throw Exception( strMsg );
            }
            strProgress.sprintf( LanguageStrings->Items->Strings[32].c_str(), pFiles[j].c_str() );
            AddProgressLine( true );
         }
      }

      if( RB_Update->Checked )
      {
         //****************************************
         // "000.05.00" bérlet upgrade
         //****************************************
         char                 strTemp[10];
         unsigned int         nCount = 0;
         vector<typ_berlet>   Berlet;

         memset( strTemp, 0, sizeof(strTemp) );
         strFile.sprintf( "%s%s", strPath.c_str(), BERLET_FILE );
         file = fopen( strFile.c_str(), "rb" );
         if( file != NULL )
         {
            fread( strTemp, 10, 1, file );
            if( strcmp( "000.05.00", strTemp ) == 0 )
            {
               AddProgressLine( LanguageStrings->Items->Strings[34] );
               nCount = 0;
               fread( &nCount, sizeof(unsigned int), 1, file );
               if( nCount > 0 )
               {
                  typ_berlet_05   stTemp;
                  typ_berlet      stBerlet;
                  for( unsigned int i=0; i<nCount; i++ )
                  {
                     fread( &stTemp, sizeof(typ_berlet_05), 1, file );
                     strncpy( stBerlet.strVonalkod, stTemp.strVonalkod, sizeof(stBerlet.strVonalkod) );
                     strncpy( stBerlet.strMegjegyzes, stTemp.strMegjegyzes, sizeof(stBerlet.strMegjegyzes) );
                     stBerlet.nBerletTipus   = stTemp.nBerletTipus;
                     stBerlet.nEgyseg        = stTemp.nEgyseg;
                     stBerlet.nErvEv         = stTemp.nErvEv;
                     stBerlet.nErvHo         = stTemp.nErvHo;
                     stBerlet.nErvNap        = stTemp.nErvNap;
                     stBerlet.nPin           = 0;
                     Berlet.push_back( stBerlet );
                  }
               }
            }
            fclose( file );
         }
         if( strcmp( "000.05.00", strTemp ) == 0 )
         {
            file = fopen( strFile.c_str(), "wb" );
            if( file != NULL )
            {
               fwrite( BERLET_FILE_VERSION, 10, 1, file );
               fwrite( &nCount, sizeof(unsigned int), 1, file );
               for( unsigned int i=0; i<nCount; i++ )
               {
                  fwrite( &Berlet[i], sizeof(typ_berlet), 1, file );
               }
               fclose( file );
               AddProgressLine( LanguageStrings->Items->Strings[35], true );
            }
            else
            {
               AddProgressLine( LanguageStrings->Items->Strings[36], true );
            }
         }

         //****************************************
         // "000.01.00" termek upgrade
         //****************************************
         vector<typ_termek>   Termek;

         memset( strTemp, 0, sizeof(strTemp) );
         strFile.sprintf( "%s%s", strPath.c_str(), TERMEK_FILE );
         file = fopen( strFile.c_str(), "rb" );
         if( file != NULL )
         {
            memset( strTemp, 0, sizeof(strTemp) );
            fread( strTemp, 10, 1, file );
            if( strcmp( "000.01.00", strTemp ) == 0 )
            {
               AddProgressLine( LanguageStrings->Items->Strings[37] );
               nCount = 0;
               fread( &nCount, sizeof(unsigned int), 1, file );
               if( nCount > 0 )
               {
                  typ_termek_01   stTemp;
                  typ_termek      stTermek;
                  for( unsigned int i=0; i<nCount; i++ )
                  {
                     fread( &stTemp, sizeof(typ_termek_01), 1, file );
                     strncpy( stTermek.strVonalkod, stTemp.strVonalkod, sizeof(stTermek.strVonalkod) );
                     strncpy( stTermek.strNev, stTemp.strNev, sizeof(stTermek.strNev) );
                     stTermek.nID            = i;//stTemp.nID;
                     stTermek.nAr            = stTemp.nAr;
                     stTermek.nDarab         = stTemp.nDarab;
                     stTermek.nArBeszerzes   = stTemp.nAr;
                     Termek.push_back( stTermek );
                  }
               }
            }
            fclose( file );
         }
         if( strcmp( "000.01.00", strTemp ) == 0 )
         {
            file = fopen( strFile.c_str(), "wb" );
            if( file != NULL )
            {
               fwrite( TERMEK_FILE_VERSION, 10, 1, file );
               fwrite( &nCount, sizeof(unsigned int), 1, file );
               for( unsigned int i=0; i<nCount; i++ )
               {
                  fwrite( &Termek[i], sizeof(typ_termek), 1, file );
               }
               fclose( file );
               AddProgressLine( LanguageStrings->Items->Strings[38], true );
            }
            else
            {
               AddProgressLine( LanguageStrings->Items->Strings[39], true );
            }
         }

         //****************************************
         // termektipus upgrade
         //****************************************
         if( strAppVersion.SubString(1,1).AnsiCompare( "1" ) == 0 )
         {
            strFile.sprintf( "%s%s", strPath.c_str(), TERMEKTIPUS_FILE );
            strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), TERMEKTIPUS_FILE );
            AddProgressLine();
            file = fopen( strFile.c_str(), "wb" );
            fwrite( TERMEKTIPUS_FILE_VERSION, 10, 1, file );
            fwrite( &nSize, sizeof(unsigned int), 1, file );
            fclose( file );
            strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), TERMEKTIPUS_FILE );
            AddProgressLine( true );

            strFile.sprintf( "%s%s", strPath.c_str(), TERMEKTIPUSASG_FILE );
            strProgress.sprintf( LanguageStrings->Items->Strings[28].c_str(), TERMEKTIPUSASG_FILE );
            AddProgressLine();
            file = fopen( strFile.c_str(), "wb" );
            fwrite( TERMEKTIPUS_FILE_VERSION, 10, 1, file );
            fwrite( &nSize, sizeof(unsigned int), 1, file );
            fclose( file );
            strProgress.sprintf( LanguageStrings->Items->Strings[29].c_str(), TERMEKTIPUSASG_FILE );
            AddProgressLine( true );
         }
      }

      if( RB_Remove->Checked )
      {
         pFiles.clear();

         pFiles.push_back( "vcl50.bpl" );
         pFiles.push_back( "vclx50.bpl" );
         pFiles.push_back( "borlndmm.dll" );
         pFiles.push_back( "cc3250mt.dll" );
         pFiles.push_back( "Sensolite.exe" );
         pFiles.push_back( "Sensolite.eng" );
         pFiles.push_back( "Sensolite.enu" );
         pFiles.push_back( "Sensolite.hun" );
         pFiles.push_back( "Sensolite.srl" );
         for( int i=0; i<nCountSolarium; i++ )
         {
            AnsiString   DataFileName = AnsiString( "sdfsv" )+AnsiString( i )+AnsiString( ".dat" );
            pFiles.push_back( DataFileName.c_str() );
         }
         for( int i=0; i<nCountSolarium; i++ )
         {
            AnsiString   DataFileName = AnsiString( "Db\\1_sdfsv" )+AnsiString( i )+AnsiString( ".dat" );
            pFiles.push_back( DataFileName.c_str() );
         }
         for( int i=0; i<nCountSolarium; i++ )
         {
            AnsiString   DataFileName = AnsiString( "Db\\2_sdfsv" )+AnsiString( i )+AnsiString( ".dat" );
            pFiles.push_back( DataFileName.c_str() );
         }
         pFiles.push_back( BERLETTIPUS_FILE );
         strFile.sprintf( "Db\\1_%s", BERLETTIPUS_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", BERLETTIPUS_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( BERLET_FILE );
         strFile.sprintf( "Db\\1_%s", BERLET_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", BERLET_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( BERLETHASZNALAT_FILE );
         strFile.sprintf( "Db\\1_%s", BERLETHASZNALAT_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", BERLETHASZNALAT_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( KONYVGENERAL_FILE );
         strFile.sprintf( "Db\\1_%s", KONYVGENERAL_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", KONYVGENERAL_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( KONYVSZOLARIUM_FILE );
         strFile.sprintf( "Db\\1_%s", KONYVSZOLARIUM_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", KONYVSZOLARIUM_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( KOSAR_FILE );
         strFile.sprintf( "Db\\1_%s", KOSAR_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", KOSAR_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( PENZTAR_FILE );
         strFile.sprintf( "Db\\1_%s", PENZTAR_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", PENZTAR_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( PENZTARLOG_FILE );
         strFile.sprintf( "Db\\1_%s", PENZTARLOG_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", PENZTARLOG_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( TERMEK_FILE );
         strFile.sprintf( "Db\\1_%s", TERMEK_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", TERMEK_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( TERMEKTIPUS_FILE );
         strFile.sprintf( "Db\\1_%s", TERMEKTIPUS_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", TERMEKTIPUS_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( TERMEKTIPUSASG_FILE );
         strFile.sprintf( "Db\\1_%s", TERMEKTIPUSASG_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", TERMEKTIPUSASG_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( USER_FILE );
         strFile.sprintf( "Db\\1_%s", USER_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", USER_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( SETTINGS_FILE );
         strFile.sprintf( "Db\\1_%s", SETTINGS_FILE );
         pFiles.push_back( strFile.c_str() );
         strFile.sprintf( "Db\\2_%s", SETTINGS_FILE );
         pFiles.push_back( strFile.c_str() );

         pFiles.push_back( "fsv.log" );
         pFiles.push_back( "Felhasznaloi utmutato.pdf" );

         AddProgressLine( LanguageStrings->Items->Strings[40] );
         TRegistry *Registry = new TRegistry;
         try
         {
            Registry->RootKey = HKEY_LOCAL_MACHINE;
            Registry->DeleteKey("SOFTWARE\\SzolariumVezerlo");
         }
         __finally
         {
            delete Registry;
         }
         AddProgressLine( LanguageStrings->Items->Strings[41], true );
         for( unsigned int j=0; j<pFiles.size(); j++ )
         {
            strProgress.sprintf( LanguageStrings->Items->Strings[43].c_str(), pFiles[j].c_str() );
            AddProgressLine();
            strFile.sprintf( "%s%s", strPath.c_str(), pFiles[j].c_str() );
            SetFileAttributes( strFile.c_str(), FILE_ATTRIBUTE_NORMAL );
            if( DeleteFile( strFile.c_str() ) == 0 )
            {
               strProgress.sprintf( LanguageStrings->Items->Strings[45].c_str(), pFiles[j].c_str() );
               AddProgressLine( true );
               AnsiString strMsg;
               strMsg = LanguageStrings->Items->Strings[14] +
                        AnsiString( "\n\n" ) +
                        strFile;
               //throw Exception( strMsg );
            }
            else
            {
               strProgress.sprintf( LanguageStrings->Items->Strings[44].c_str(), pFiles[j].c_str() );
               AddProgressLine( true );
            }
         }

         strFile.sprintf( "%sDb", strPath.c_str() );
         strProgress.sprintf( LanguageStrings->Items->Strings[46].c_str(), strFile.c_str() );
         AddProgressLine();
         if( RemoveDirectory( strFile.c_str() ) )
         {
            strProgress.sprintf( LanguageStrings->Items->Strings[47].c_str(), strFile.c_str() );
            AddProgressLine();
         }
         else
         {
            strProgress.sprintf( LanguageStrings->Items->Strings[48].c_str(), strFile.c_str() );
            AddProgressLine();
         }
         strProgress.sprintf( LanguageStrings->Items->Strings[46].c_str(), strPath.c_str() );
         AddProgressLine();
         if( RemoveDirectory( strPath.c_str() ) )
         {
            strProgress.sprintf( LanguageStrings->Items->Strings[47].c_str(), strPath.c_str() );
            AddProgressLine();
         }
         else
         {
            strProgress.sprintf( LanguageStrings->Items->Strings[48].c_str(), strPath.c_str() );
            AddProgressLine();
         }
      }

      delete pSComm;
      delete pHardware;

      AnsiString strMsg;
      if( RB_Setup->Checked )
         strMsg = LanguageStrings->Items->Strings[6];
      if( RB_Update->Checked )
         strMsg = LanguageStrings->Items->Strings[8];
      if( RB_Remove->Checked )
         strMsg = LanguageStrings->Items->Strings[7];
      strMsg += " ";
      strMsg += LanguageStrings->Items->Strings[16];
      Application->MessageBox( strMsg.c_str(),
                               LanguageStrings->Items->Strings[15].c_str(),
                               MB_ICONINFORMATION );

      BitBtnCancel->Visible = false;
      BitBtnPrev->Visible = false;
      BitBtnNext->Visible = false;
      BitBtnExit->Visible = false;
      BitBtnExitApp->Visible = true;
      BitBtnExitApp->Enabled = true;
      BitBtnExitApp->SetFocus();
   }
   catch(const Exception& e)
   {
      Application->MessageBox( e.Message.c_str(),
                               LanguageStrings->Items->Strings[12].c_str(),
                               MB_ICONEXCLAMATION );
   }
}
//---------------------------------------------------------------------------
void TFormInstallMain::FillControlsWithData()
{
   unsigned short nHour, nMin, nSec, nMSec;

   memset( &stAdat, 0, sizeof(typ_szoliadat) );
   memset( &stAdat.stIdoForint, 0, sizeof(typ_idoforint) );
   memset( &stAdat.stIdoForintKedv, 0, sizeof(typ_idoforint) );

   Now().DecodeTime( &nHour, &nMin, &nSec, &nMSec );
   if( stAdat.nKedvezmenyIdoStart <= (nHour*60+nMin) &&
       (nHour*60+nMin) <= stAdat.nKedvezmenyIdoStop )
   {
      TabControlTablazat->TabIndex = 1;
   }
   else
   {
      TabControlTablazat->TabIndex = 0;
   }

   EditPerc0->Text = AnsiString( stAdat.stIdoForint[0].nPerc );
   EditPerc1->Text = AnsiString( stAdat.stIdoForint[1].nPerc );
   EditPerc2->Text = AnsiString( stAdat.stIdoForint[2].nPerc );
   EditPerc3->Text = AnsiString( stAdat.stIdoForint[3].nPerc );
   EditPerc4->Text = AnsiString( stAdat.stIdoForint[4].nPerc );
   EditPerc5->Text = AnsiString( stAdat.stIdoForint[5].nPerc );
   EditPerc6->Text = AnsiString( stAdat.stIdoForint[6].nPerc );
   EditPerc7->Text = AnsiString( stAdat.stIdoForint[7].nPerc );
   EditPerc8->Text = AnsiString( stAdat.stIdoForint[8].nPerc );
   EditPerc9->Text = AnsiString( stAdat.stIdoForint[9].nPerc );
   EditPerc10->Text = AnsiString( stAdat.stIdoForint[10].nPerc );
   EditPerc11->Text = AnsiString( stAdat.stIdoForint[11].nPerc );
   EditPerc12->Text = AnsiString( stAdat.stIdoForint[12].nPerc );
   EditPerc13->Text = AnsiString( stAdat.stIdoForint[13].nPerc );
   EditPerc14->Text = AnsiString( stAdat.stIdoForint[14].nPerc );
   EditPerc15->Text = AnsiString( stAdat.stIdoForint[15].nPerc );
   EditPerc16->Text = AnsiString( stAdat.stIdoForint[16].nPerc );
   EditPerc17->Text = AnsiString( stAdat.stIdoForint[17].nPerc );
   EditPerc18->Text = AnsiString( stAdat.stIdoForint[18].nPerc );
   EditPerc19->Text = AnsiString( stAdat.stIdoForint[19].nPerc );
   EditPerc20->Text = AnsiString( stAdat.stIdoForint[20].nPerc );
   EditPerc21->Text = AnsiString( stAdat.stIdoForint[21].nPerc );
   EditPerc22->Text = AnsiString( stAdat.stIdoForint[22].nPerc );
   EditPerc23->Text = AnsiString( stAdat.stIdoForint[23].nPerc );
   EditPerc24->Text = AnsiString( stAdat.stIdoForint[24].nPerc );
   EditPerc25->Text = AnsiString( stAdat.stIdoForint[25].nPerc );
   EditPerc26->Text = AnsiString( stAdat.stIdoForint[26].nPerc );
   EditPerc27->Text = AnsiString( stAdat.stIdoForint[27].nPerc );
   EditPerc28->Text = AnsiString( stAdat.stIdoForint[28].nPerc );
   EditPerc29->Text = AnsiString( stAdat.stIdoForint[29].nPerc );
   EditPerc30->Text = AnsiString( stAdat.stIdoForint[30].nPerc );
   EditPerc31->Text = AnsiString( stAdat.stIdoForint[31].nPerc );
   EditPerc32->Text = AnsiString( stAdat.stIdoForint[32].nPerc );
   EditPerc33->Text = AnsiString( stAdat.stIdoForint[33].nPerc );
   EditPerc34->Text = AnsiString( stAdat.stIdoForint[34].nPerc );
   EditPerc35->Text = AnsiString( stAdat.stIdoForint[35].nPerc );
   EditPerc36->Text = AnsiString( stAdat.stIdoForint[36].nPerc );
   EditPerc37->Text = AnsiString( stAdat.stIdoForint[37].nPerc );
   EditPerc38->Text = AnsiString( stAdat.stIdoForint[38].nPerc );
   EditPerc39->Text = AnsiString( stAdat.stIdoForint[39].nPerc );
   EditKPerc0->Text = AnsiString( stAdat.stIdoForintKedv[0].nPerc );
   EditKPerc1->Text = AnsiString( stAdat.stIdoForintKedv[1].nPerc );
   EditKPerc2->Text = AnsiString( stAdat.stIdoForintKedv[2].nPerc );
   EditKPerc3->Text = AnsiString( stAdat.stIdoForintKedv[3].nPerc );
   EditKPerc4->Text = AnsiString( stAdat.stIdoForintKedv[4].nPerc );
   EditKPerc5->Text = AnsiString( stAdat.stIdoForintKedv[5].nPerc );
   EditKPerc6->Text = AnsiString( stAdat.stIdoForintKedv[6].nPerc );
   EditKPerc7->Text = AnsiString( stAdat.stIdoForintKedv[7].nPerc );
   EditKPerc8->Text = AnsiString( stAdat.stIdoForintKedv[8].nPerc );
   EditKPerc9->Text = AnsiString( stAdat.stIdoForintKedv[9].nPerc );
   EditKPerc10->Text = AnsiString( stAdat.stIdoForintKedv[10].nPerc );
   EditKPerc11->Text = AnsiString( stAdat.stIdoForintKedv[11].nPerc );
   EditKPerc12->Text = AnsiString( stAdat.stIdoForintKedv[12].nPerc );
   EditKPerc13->Text = AnsiString( stAdat.stIdoForintKedv[13].nPerc );
   EditKPerc14->Text = AnsiString( stAdat.stIdoForintKedv[14].nPerc );
   EditKPerc15->Text = AnsiString( stAdat.stIdoForintKedv[15].nPerc );
   EditKPerc16->Text = AnsiString( stAdat.stIdoForintKedv[16].nPerc );
   EditKPerc17->Text = AnsiString( stAdat.stIdoForintKedv[17].nPerc );
   EditKPerc18->Text = AnsiString( stAdat.stIdoForintKedv[18].nPerc );
   EditKPerc19->Text = AnsiString( stAdat.stIdoForintKedv[19].nPerc );
   EditKPerc20->Text = AnsiString( stAdat.stIdoForintKedv[20].nPerc );
   EditKPerc21->Text = AnsiString( stAdat.stIdoForintKedv[21].nPerc );
   EditKPerc22->Text = AnsiString( stAdat.stIdoForintKedv[22].nPerc );
   EditKPerc23->Text = AnsiString( stAdat.stIdoForintKedv[23].nPerc );
   EditKPerc24->Text = AnsiString( stAdat.stIdoForintKedv[24].nPerc );
   EditKPerc25->Text = AnsiString( stAdat.stIdoForintKedv[25].nPerc );
   EditKPerc26->Text = AnsiString( stAdat.stIdoForintKedv[26].nPerc );
   EditKPerc27->Text = AnsiString( stAdat.stIdoForintKedv[27].nPerc );
   EditKPerc28->Text = AnsiString( stAdat.stIdoForintKedv[28].nPerc );
   EditKPerc29->Text = AnsiString( stAdat.stIdoForintKedv[29].nPerc );
   EditKPerc30->Text = AnsiString( stAdat.stIdoForintKedv[30].nPerc );
   EditKPerc31->Text = AnsiString( stAdat.stIdoForintKedv[31].nPerc );
   EditKPerc32->Text = AnsiString( stAdat.stIdoForintKedv[32].nPerc );
   EditKPerc33->Text = AnsiString( stAdat.stIdoForintKedv[33].nPerc );
   EditKPerc34->Text = AnsiString( stAdat.stIdoForintKedv[34].nPerc );
   EditKPerc35->Text = AnsiString( stAdat.stIdoForintKedv[35].nPerc );
   EditKPerc36->Text = AnsiString( stAdat.stIdoForintKedv[36].nPerc );
   EditKPerc37->Text = AnsiString( stAdat.stIdoForintKedv[37].nPerc );
   EditKPerc38->Text = AnsiString( stAdat.stIdoForintKedv[38].nPerc );
   EditKPerc39->Text = AnsiString( stAdat.stIdoForintKedv[39].nPerc );
   EditForint0->Text = AnsiString( stAdat.stIdoForint[0].nForint );
   EditForint1->Text = AnsiString( stAdat.stIdoForint[1].nForint );
   EditForint2->Text = AnsiString( stAdat.stIdoForint[2].nForint );
   EditForint3->Text = AnsiString( stAdat.stIdoForint[3].nForint );
   EditForint4->Text = AnsiString( stAdat.stIdoForint[4].nForint );
   EditForint5->Text = AnsiString( stAdat.stIdoForint[5].nForint );
   EditForint6->Text = AnsiString( stAdat.stIdoForint[6].nForint );
   EditForint7->Text = AnsiString( stAdat.stIdoForint[7].nForint );
   EditForint8->Text = AnsiString( stAdat.stIdoForint[8].nForint );
   EditForint9->Text = AnsiString( stAdat.stIdoForint[9].nForint );
   EditForint10->Text = AnsiString( stAdat.stIdoForint[10].nForint );
   EditForint11->Text = AnsiString( stAdat.stIdoForint[11].nForint );
   EditForint12->Text = AnsiString( stAdat.stIdoForint[12].nForint );
   EditForint13->Text = AnsiString( stAdat.stIdoForint[13].nForint );
   EditForint14->Text = AnsiString( stAdat.stIdoForint[14].nForint );
   EditForint15->Text = AnsiString( stAdat.stIdoForint[15].nForint );
   EditForint16->Text = AnsiString( stAdat.stIdoForint[16].nForint );
   EditForint17->Text = AnsiString( stAdat.stIdoForint[17].nForint );
   EditForint18->Text = AnsiString( stAdat.stIdoForint[18].nForint );
   EditForint19->Text = AnsiString( stAdat.stIdoForint[19].nForint );
   EditForint20->Text = AnsiString( stAdat.stIdoForint[20].nForint );
   EditForint21->Text = AnsiString( stAdat.stIdoForint[21].nForint );
   EditForint22->Text = AnsiString( stAdat.stIdoForint[22].nForint );
   EditForint23->Text = AnsiString( stAdat.stIdoForint[23].nForint );
   EditForint24->Text = AnsiString( stAdat.stIdoForint[24].nForint );
   EditForint25->Text = AnsiString( stAdat.stIdoForint[25].nForint );
   EditForint26->Text = AnsiString( stAdat.stIdoForint[26].nForint );
   EditForint27->Text = AnsiString( stAdat.stIdoForint[27].nForint );
   EditForint28->Text = AnsiString( stAdat.stIdoForint[28].nForint );
   EditForint29->Text = AnsiString( stAdat.stIdoForint[29].nForint );
   EditForint30->Text = AnsiString( stAdat.stIdoForint[30].nForint );
   EditForint31->Text = AnsiString( stAdat.stIdoForint[31].nForint );
   EditForint32->Text = AnsiString( stAdat.stIdoForint[32].nForint );
   EditForint33->Text = AnsiString( stAdat.stIdoForint[33].nForint );
   EditForint34->Text = AnsiString( stAdat.stIdoForint[34].nForint );
   EditForint35->Text = AnsiString( stAdat.stIdoForint[35].nForint );
   EditForint36->Text = AnsiString( stAdat.stIdoForint[36].nForint );
   EditForint37->Text = AnsiString( stAdat.stIdoForint[37].nForint );
   EditForint38->Text = AnsiString( stAdat.stIdoForint[38].nForint );
   EditForint39->Text = AnsiString( stAdat.stIdoForint[39].nForint );
   EditKForint0->Text = AnsiString( stAdat.stIdoForintKedv[0].nForint );
   EditKForint1->Text = AnsiString( stAdat.stIdoForintKedv[1].nForint );
   EditKForint2->Text = AnsiString( stAdat.stIdoForintKedv[2].nForint );
   EditKForint3->Text = AnsiString( stAdat.stIdoForintKedv[3].nForint );
   EditKForint4->Text = AnsiString( stAdat.stIdoForintKedv[4].nForint );
   EditKForint5->Text = AnsiString( stAdat.stIdoForintKedv[5].nForint );
   EditKForint6->Text = AnsiString( stAdat.stIdoForintKedv[6].nForint );
   EditKForint7->Text = AnsiString( stAdat.stIdoForintKedv[7].nForint );
   EditKForint8->Text = AnsiString( stAdat.stIdoForintKedv[8].nForint );
   EditKForint9->Text = AnsiString( stAdat.stIdoForintKedv[9].nForint );
   EditKForint10->Text = AnsiString( stAdat.stIdoForintKedv[10].nForint );
   EditKForint11->Text = AnsiString( stAdat.stIdoForintKedv[11].nForint );
   EditKForint12->Text = AnsiString( stAdat.stIdoForintKedv[12].nForint );
   EditKForint13->Text = AnsiString( stAdat.stIdoForintKedv[13].nForint );
   EditKForint14->Text = AnsiString( stAdat.stIdoForintKedv[14].nForint );
   EditKForint15->Text = AnsiString( stAdat.stIdoForintKedv[15].nForint );
   EditKForint16->Text = AnsiString( stAdat.stIdoForintKedv[16].nForint );
   EditKForint17->Text = AnsiString( stAdat.stIdoForintKedv[17].nForint );
   EditKForint18->Text = AnsiString( stAdat.stIdoForintKedv[18].nForint );
   EditKForint19->Text = AnsiString( stAdat.stIdoForintKedv[19].nForint );
   EditKForint20->Text = AnsiString( stAdat.stIdoForintKedv[20].nForint );
   EditKForint21->Text = AnsiString( stAdat.stIdoForintKedv[21].nForint );
   EditKForint22->Text = AnsiString( stAdat.stIdoForintKedv[22].nForint );
   EditKForint23->Text = AnsiString( stAdat.stIdoForintKedv[23].nForint );
   EditKForint24->Text = AnsiString( stAdat.stIdoForintKedv[24].nForint );
   EditKForint25->Text = AnsiString( stAdat.stIdoForintKedv[25].nForint );
   EditKForint26->Text = AnsiString( stAdat.stIdoForintKedv[26].nForint );
   EditKForint27->Text = AnsiString( stAdat.stIdoForintKedv[27].nForint );
   EditKForint28->Text = AnsiString( stAdat.stIdoForintKedv[28].nForint );
   EditKForint29->Text = AnsiString( stAdat.stIdoForintKedv[29].nForint );
   EditKForint30->Text = AnsiString( stAdat.stIdoForintKedv[30].nForint );
   EditKForint31->Text = AnsiString( stAdat.stIdoForintKedv[31].nForint );
   EditKForint32->Text = AnsiString( stAdat.stIdoForintKedv[32].nForint );
   EditKForint33->Text = AnsiString( stAdat.stIdoForintKedv[33].nForint );
   EditKForint34->Text = AnsiString( stAdat.stIdoForintKedv[34].nForint );
   EditKForint35->Text = AnsiString( stAdat.stIdoForintKedv[35].nForint );
   EditKForint36->Text = AnsiString( stAdat.stIdoForintKedv[36].nForint );
   EditKForint37->Text = AnsiString( stAdat.stIdoForintKedv[37].nForint );
   EditKForint38->Text = AnsiString( stAdat.stIdoForintKedv[38].nForint );
   EditKForint39->Text = AnsiString( stAdat.stIdoForintKedv[39].nForint );
}
//---------------------------------------------------------------------------
void TFormInstallMain::SaveDataFromControls()
{
   memset( &stAdat, 0, sizeof(typ_szoliadat) );
   memset( stAdat.strNev, 0, sizeof(stAdat.strNev) );

   try
   {
      nCountSolarium = EditSzolariumCount->Text.ToInt();
      stAdat.nIdoVetkozes = EditIdoVetkozes->Text.ToInt();
      stAdat.nIdoUtohutes = EditIdoUtohutes->Text.ToInt();
      stAdat.nIdoSzauna = EditIdoSzauna->Text.ToInt();
      stAdat.bShowCsoUzemora = CheckBoxCsoVisible->Checked;
      stAdat.nCsoUzemoraMax = EditCsoUzemoraMax->Text.ToInt()*3600;
      stAdat.nMaxBarnulas = EditIdoHasznalatMax->Text.ToInt();
      stAdat.nKedvezmenyIdoStart = EditKedvStartO->Text.ToInt()*60+EditKedvStartP->Text.ToInt();
      stAdat.nKedvezmenyIdoStop = EditKedvStopO->Text.ToInt()*60+EditKedvStopP->Text.ToInt();

      stAdat.stIdoForint[0].nPerc = EditPerc0->Text.ToInt();
      stAdat.stIdoForint[1].nPerc = EditPerc1->Text.ToInt();
      stAdat.stIdoForint[2].nPerc = EditPerc2->Text.ToInt();
      stAdat.stIdoForint[3].nPerc = EditPerc3->Text.ToInt();
      stAdat.stIdoForint[4].nPerc = EditPerc4->Text.ToInt();
      stAdat.stIdoForint[5].nPerc = EditPerc5->Text.ToInt();
      stAdat.stIdoForint[6].nPerc = EditPerc6->Text.ToInt();
      stAdat.stIdoForint[7].nPerc = EditPerc7->Text.ToInt();
      stAdat.stIdoForint[8].nPerc = EditPerc8->Text.ToInt();
      stAdat.stIdoForint[9].nPerc = EditPerc9->Text.ToInt();
      stAdat.stIdoForint[10].nPerc = EditPerc10->Text.ToInt();
      stAdat.stIdoForint[11].nPerc = EditPerc11->Text.ToInt();
      stAdat.stIdoForint[12].nPerc = EditPerc12->Text.ToInt();
      stAdat.stIdoForint[13].nPerc = EditPerc13->Text.ToInt();
      stAdat.stIdoForint[14].nPerc = EditPerc14->Text.ToInt();
      stAdat.stIdoForint[15].nPerc = EditPerc15->Text.ToInt();
      stAdat.stIdoForint[16].nPerc = EditPerc16->Text.ToInt();
      stAdat.stIdoForint[17].nPerc = EditPerc17->Text.ToInt();
      stAdat.stIdoForint[18].nPerc = EditPerc18->Text.ToInt();
      stAdat.stIdoForint[19].nPerc = EditPerc19->Text.ToInt();
      stAdat.stIdoForint[20].nPerc = EditPerc20->Text.ToInt();
      stAdat.stIdoForint[21].nPerc = EditPerc21->Text.ToInt();
      stAdat.stIdoForint[22].nPerc = EditPerc22->Text.ToInt();
      stAdat.stIdoForint[23].nPerc = EditPerc23->Text.ToInt();
      stAdat.stIdoForint[24].nPerc = EditPerc24->Text.ToInt();
      stAdat.stIdoForint[25].nPerc = EditPerc25->Text.ToInt();
      stAdat.stIdoForint[26].nPerc = EditPerc26->Text.ToInt();
      stAdat.stIdoForint[27].nPerc = EditPerc27->Text.ToInt();
      stAdat.stIdoForint[28].nPerc = EditPerc28->Text.ToInt();
      stAdat.stIdoForint[29].nPerc = EditPerc29->Text.ToInt();
      stAdat.stIdoForint[30].nPerc = EditPerc30->Text.ToInt();
      stAdat.stIdoForint[31].nPerc = EditPerc31->Text.ToInt();
      stAdat.stIdoForint[32].nPerc = EditPerc32->Text.ToInt();
      stAdat.stIdoForint[33].nPerc = EditPerc33->Text.ToInt();
      stAdat.stIdoForint[34].nPerc = EditPerc34->Text.ToInt();
      stAdat.stIdoForint[35].nPerc = EditPerc35->Text.ToInt();
      stAdat.stIdoForint[36].nPerc = EditPerc36->Text.ToInt();
      stAdat.stIdoForint[37].nPerc = EditPerc37->Text.ToInt();
      stAdat.stIdoForint[38].nPerc = EditPerc38->Text.ToInt();
      stAdat.stIdoForint[39].nPerc = EditPerc39->Text.ToInt();
      stAdat.stIdoForint[0].nForint = EditForint0->Text.ToInt();
      stAdat.stIdoForint[1].nForint = EditForint1->Text.ToInt();
      stAdat.stIdoForint[2].nForint = EditForint2->Text.ToInt();
      stAdat.stIdoForint[3].nForint = EditForint3->Text.ToInt();
      stAdat.stIdoForint[4].nForint = EditForint4->Text.ToInt();
      stAdat.stIdoForint[5].nForint = EditForint5->Text.ToInt();
      stAdat.stIdoForint[6].nForint = EditForint6->Text.ToInt();
      stAdat.stIdoForint[7].nForint = EditForint7->Text.ToInt();
      stAdat.stIdoForint[8].nForint = EditForint8->Text.ToInt();
      stAdat.stIdoForint[9].nForint = EditForint9->Text.ToInt();
      stAdat.stIdoForint[10].nForint = EditForint10->Text.ToInt();
      stAdat.stIdoForint[11].nForint = EditForint11->Text.ToInt();
      stAdat.stIdoForint[12].nForint = EditForint12->Text.ToInt();
      stAdat.stIdoForint[13].nForint = EditForint13->Text.ToInt();
      stAdat.stIdoForint[14].nForint = EditForint14->Text.ToInt();
      stAdat.stIdoForint[15].nForint = EditForint15->Text.ToInt();
      stAdat.stIdoForint[16].nForint = EditForint16->Text.ToInt();
      stAdat.stIdoForint[17].nForint = EditForint17->Text.ToInt();
      stAdat.stIdoForint[18].nForint = EditForint18->Text.ToInt();
      stAdat.stIdoForint[19].nForint = EditForint19->Text.ToInt();
      stAdat.stIdoForint[20].nForint = EditForint20->Text.ToInt();
      stAdat.stIdoForint[21].nForint = EditForint21->Text.ToInt();
      stAdat.stIdoForint[22].nForint = EditForint22->Text.ToInt();
      stAdat.stIdoForint[23].nForint = EditForint23->Text.ToInt();
      stAdat.stIdoForint[24].nForint = EditForint24->Text.ToInt();
      stAdat.stIdoForint[25].nForint = EditForint25->Text.ToInt();
      stAdat.stIdoForint[26].nForint = EditForint26->Text.ToInt();
      stAdat.stIdoForint[27].nForint = EditForint27->Text.ToInt();
      stAdat.stIdoForint[28].nForint = EditForint28->Text.ToInt();
      stAdat.stIdoForint[29].nForint = EditForint29->Text.ToInt();
      stAdat.stIdoForint[30].nForint = EditForint30->Text.ToInt();
      stAdat.stIdoForint[31].nForint = EditForint31->Text.ToInt();
      stAdat.stIdoForint[32].nForint = EditForint32->Text.ToInt();
      stAdat.stIdoForint[33].nForint = EditForint33->Text.ToInt();
      stAdat.stIdoForint[34].nForint = EditForint34->Text.ToInt();
      stAdat.stIdoForint[35].nForint = EditForint35->Text.ToInt();
      stAdat.stIdoForint[36].nForint = EditForint36->Text.ToInt();
      stAdat.stIdoForint[37].nForint = EditForint37->Text.ToInt();
      stAdat.stIdoForint[38].nForint = EditForint38->Text.ToInt();
      stAdat.stIdoForint[39].nForint = EditForint39->Text.ToInt();
      stAdat.stIdoForintKedv[0].nPerc = EditKPerc0->Text.ToInt();
      stAdat.stIdoForintKedv[1].nPerc = EditKPerc1->Text.ToInt();
      stAdat.stIdoForintKedv[2].nPerc = EditKPerc2->Text.ToInt();
      stAdat.stIdoForintKedv[3].nPerc = EditKPerc3->Text.ToInt();
      stAdat.stIdoForintKedv[4].nPerc = EditKPerc4->Text.ToInt();
      stAdat.stIdoForintKedv[5].nPerc = EditKPerc5->Text.ToInt();
      stAdat.stIdoForintKedv[6].nPerc = EditKPerc6->Text.ToInt();
      stAdat.stIdoForintKedv[7].nPerc = EditKPerc7->Text.ToInt();
      stAdat.stIdoForintKedv[8].nPerc = EditKPerc8->Text.ToInt();
      stAdat.stIdoForintKedv[9].nPerc = EditKPerc9->Text.ToInt();
      stAdat.stIdoForintKedv[10].nPerc = EditKPerc10->Text.ToInt();
      stAdat.stIdoForintKedv[11].nPerc = EditKPerc11->Text.ToInt();
      stAdat.stIdoForintKedv[12].nPerc = EditKPerc12->Text.ToInt();
      stAdat.stIdoForintKedv[13].nPerc = EditKPerc13->Text.ToInt();
      stAdat.stIdoForintKedv[14].nPerc = EditKPerc14->Text.ToInt();
      stAdat.stIdoForintKedv[15].nPerc = EditKPerc15->Text.ToInt();
      stAdat.stIdoForintKedv[16].nPerc = EditKPerc16->Text.ToInt();
      stAdat.stIdoForintKedv[17].nPerc = EditKPerc17->Text.ToInt();
      stAdat.stIdoForintKedv[18].nPerc = EditKPerc18->Text.ToInt();
      stAdat.stIdoForintKedv[19].nPerc = EditKPerc19->Text.ToInt();
      stAdat.stIdoForintKedv[20].nPerc = EditKPerc20->Text.ToInt();
      stAdat.stIdoForintKedv[21].nPerc = EditKPerc21->Text.ToInt();
      stAdat.stIdoForintKedv[22].nPerc = EditKPerc22->Text.ToInt();
      stAdat.stIdoForintKedv[23].nPerc = EditKPerc23->Text.ToInt();
      stAdat.stIdoForintKedv[24].nPerc = EditKPerc24->Text.ToInt();
      stAdat.stIdoForintKedv[25].nPerc = EditKPerc25->Text.ToInt();
      stAdat.stIdoForintKedv[26].nPerc = EditKPerc26->Text.ToInt();
      stAdat.stIdoForintKedv[27].nPerc = EditKPerc27->Text.ToInt();
      stAdat.stIdoForintKedv[28].nPerc = EditKPerc28->Text.ToInt();
      stAdat.stIdoForintKedv[29].nPerc = EditKPerc29->Text.ToInt();
      stAdat.stIdoForintKedv[30].nPerc = EditKPerc30->Text.ToInt();
      stAdat.stIdoForintKedv[31].nPerc = EditKPerc31->Text.ToInt();
      stAdat.stIdoForintKedv[32].nPerc = EditKPerc32->Text.ToInt();
      stAdat.stIdoForintKedv[33].nPerc = EditKPerc33->Text.ToInt();
      stAdat.stIdoForintKedv[34].nPerc = EditKPerc34->Text.ToInt();
      stAdat.stIdoForintKedv[35].nPerc = EditKPerc35->Text.ToInt();
      stAdat.stIdoForintKedv[36].nPerc = EditKPerc36->Text.ToInt();
      stAdat.stIdoForintKedv[37].nPerc = EditKPerc37->Text.ToInt();
      stAdat.stIdoForintKedv[38].nPerc = EditKPerc38->Text.ToInt();
      stAdat.stIdoForintKedv[39].nPerc = EditKPerc39->Text.ToInt();
      stAdat.stIdoForintKedv[0].nForint = EditKForint0->Text.ToInt();
      stAdat.stIdoForintKedv[1].nForint = EditKForint1->Text.ToInt();
      stAdat.stIdoForintKedv[2].nForint = EditKForint2->Text.ToInt();
      stAdat.stIdoForintKedv[3].nForint = EditKForint3->Text.ToInt();
      stAdat.stIdoForintKedv[4].nForint = EditKForint4->Text.ToInt();
      stAdat.stIdoForintKedv[5].nForint = EditKForint5->Text.ToInt();
      stAdat.stIdoForintKedv[6].nForint = EditKForint6->Text.ToInt();
      stAdat.stIdoForintKedv[7].nForint = EditKForint7->Text.ToInt();
      stAdat.stIdoForintKedv[8].nForint = EditKForint8->Text.ToInt();
      stAdat.stIdoForintKedv[9].nForint = EditKForint9->Text.ToInt();
      stAdat.stIdoForintKedv[10].nForint = EditKForint10->Text.ToInt();
      stAdat.stIdoForintKedv[11].nForint = EditKForint11->Text.ToInt();
      stAdat.stIdoForintKedv[12].nForint = EditKForint12->Text.ToInt();
      stAdat.stIdoForintKedv[13].nForint = EditKForint13->Text.ToInt();
      stAdat.stIdoForintKedv[14].nForint = EditKForint14->Text.ToInt();
      stAdat.stIdoForintKedv[15].nForint = EditKForint15->Text.ToInt();
      stAdat.stIdoForintKedv[16].nForint = EditKForint16->Text.ToInt();
      stAdat.stIdoForintKedv[17].nForint = EditKForint17->Text.ToInt();
      stAdat.stIdoForintKedv[18].nForint = EditKForint18->Text.ToInt();
      stAdat.stIdoForintKedv[19].nForint = EditKForint19->Text.ToInt();
      stAdat.stIdoForintKedv[20].nForint = EditKForint20->Text.ToInt();
      stAdat.stIdoForintKedv[21].nForint = EditKForint21->Text.ToInt();
      stAdat.stIdoForintKedv[22].nForint = EditKForint22->Text.ToInt();
      stAdat.stIdoForintKedv[23].nForint = EditKForint23->Text.ToInt();
      stAdat.stIdoForintKedv[24].nForint = EditKForint24->Text.ToInt();
      stAdat.stIdoForintKedv[25].nForint = EditKForint25->Text.ToInt();
      stAdat.stIdoForintKedv[26].nForint = EditKForint26->Text.ToInt();
      stAdat.stIdoForintKedv[27].nForint = EditKForint27->Text.ToInt();
      stAdat.stIdoForintKedv[28].nForint = EditKForint28->Text.ToInt();
      stAdat.stIdoForintKedv[29].nForint = EditKForint29->Text.ToInt();
      stAdat.stIdoForintKedv[30].nForint = EditKForint30->Text.ToInt();
      stAdat.stIdoForintKedv[31].nForint = EditKForint31->Text.ToInt();
      stAdat.stIdoForintKedv[32].nForint = EditKForint32->Text.ToInt();
      stAdat.stIdoForintKedv[33].nForint = EditKForint33->Text.ToInt();
      stAdat.stIdoForintKedv[34].nForint = EditKForint34->Text.ToInt();
      stAdat.stIdoForintKedv[35].nForint = EditKForint35->Text.ToInt();
      stAdat.stIdoForintKedv[36].nForint = EditKForint36->Text.ToInt();
      stAdat.stIdoForintKedv[37].nForint = EditKForint37->Text.ToInt();
      stAdat.stIdoForintKedv[38].nForint = EditKForint38->Text.ToInt();
      stAdat.stIdoForintKedv[39].nForint = EditKForint39->Text.ToInt();
   }
   catch(const Exception& e)
   {
      AnsiString eMessage = "Az egyik mezõben nem megfelelõ karakter található,\n"
                            "vagy a mezõ nincs kitöltve.\n\n"
                            "Kérem ellenõrizze, hogy ne legyen üres egyik mezõ se\n"
                            "és az adott mezõkben csak számok szerepeljenek!";
      Application->MessageBox( eMessage.c_str(), "Figyelmeztetés", MB_ICONEXCLAMATION );
   }
}
//---------------------------------------------------------------------------
void TFormInstallMain::SetIntegerValueInRegistry( AnsiString KeyName, int nValue )
{
   TRegistry *Registry = new TRegistry;
   try
   {
      Registry->RootKey = HKEY_LOCAL_MACHINE;
      Registry->OpenKey("SOFTWARE\\SzolariumVezerlo", true);
      Registry->WriteInteger( KeyName, nValue );
   }
   __finally
   {
      delete Registry;
   }
}
//---------------------------------------------------------------------------
void TFormInstallMain::SetStringValueInRegistry( AnsiString KeyName, AnsiString strValue )
{
   TRegistry *Registry = new TRegistry;
   try
   {
      Registry->RootKey = HKEY_LOCAL_MACHINE;
      Registry->OpenKey("SOFTWARE\\SzolariumVezerlo", true);
      Registry->WriteString( KeyName, strValue );
   }
   __finally
   {
      delete Registry;
   }
}
//---------------------------------------------------------------------------
int TFormInstallMain::GetIntegerValueFromRegistry( AnsiString KeyName, int nDefValue )
{
   int nRet = nDefValue;
   TRegistry *Registry = new TRegistry;

   try
   {
      Registry->RootKey = HKEY_LOCAL_MACHINE;
      if( Registry->OpenKey("SOFTWARE\\SzolariumVezerlo", false) )
      {
         nRet = Registry->ReadInteger( KeyName );
      }
   }
   catch (Exception &e)
   {
      SetIntegerValueInRegistry( KeyName, nDefValue );
   }
   delete Registry;

   return nRet;
}
//---------------------------------------------------------------------------
AnsiString TFormInstallMain::GetStringValueFromRegistry( AnsiString KeyName, AnsiString strDefValue )
{
   AnsiString strRet = strDefValue;
   TRegistry *Registry = new TRegistry;

   try
   {
      Registry->RootKey = HKEY_LOCAL_MACHINE;
      if( Registry->OpenKey("SOFTWARE\\SzolariumVezerlo", false) )
      {
         strRet = Registry->ReadString( KeyName );
      }
   }
   catch (Exception &e)
   {
      SetStringValueInRegistry( KeyName, strDefValue );
   }
   delete Registry;

   return strRet;
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::BitBtnChangeDirClick(TObject *Sender)
{
   FormDialogSelectDir->DriveComboBox->Drive = *EditDirectory->Text.SubString(1,1).AnsiLastChar();
   FormDialogSelectDir->DirectoryListBox->Directory = "";
   if( FormDialogSelectDir->ShowModal() )
   {
      AnsiString  strDir = FormDialogSelectDir->LabelDir->Caption;
      if( strcmp( strDir.AnsiLastChar(), "\\" ) != 0 )
         strDir += AnsiString( "\\" );
      strDir += AnsiString( "Sensolite" );

      EditDirectory->Text = strDir;
   }
}
//---------------------------------------------------------------------------
// CreateLink - uses the shell's IShellLink and IPersistFile interfaces
//   to create and store a shortcut to the specified object.
// Returns the result of calling the member functions of the interfaces.
// lpszPathObj - address of a buffer containing the path of the object
// lpszPathLink - address of a buffer containing the path where the
//   shell link is to be stored
// lpszDesc - address of a buffer containing the description of the
//   shell link
/*
HRESULT CreateLink(LPCSTR lpszPathObj,
    LPSTR lpszPathLink, LPSTR lpszDesc)
{
    HRESULT hres;
    IShellLink* psl;

    // Get a pointer to the IShellLink interface.
    hres = CoCreateInstance(&CLSID_ShellLink, NULL,
        CLSCTX_INPROC_SERVER, &IID_IShellLink, &psl);
    if (SUCCEEDED(hres)) {
        IPersistFile* ppf;

        // Set the path to the shortcut target, and add the
        // description.
        psl->lpVtbl->SetPath(psl, lpszPathObj);

        psl->lpVtbl->SetDescription(psl, lpszDesc);

       // Query IShellLink for the IPersistFile interface for saving the
       // shortcut in persistent storage.
        hres = psl->lpVtbl->QueryInterface(psl, &IID_IPersistFile,
            &ppf);

        if (SUCCEEDED(hres)) {
            WORD wsz[MAX_PATH];

            // Ensure that the string is ANSI.
            MultiByteToWideChar(CP_ACP, 0, lpszPathLink, -1,
                wsz, MAX_PATH);


            // Save the link by calling IPersistFile::Save.
            hres = ppf->lpVtbl->Save(ppf, wsz, TRUE);
            ppf->lpVtbl->Release(ppf);
        }
        psl->lpVtbl->Release(psl);
    }
    return hres;
}*/
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::RB_SetupClick(TObject *Sender)
{
   pPages.clear();

   pPages.push_back( PanelDirectory );
   pPages.push_back( PanelSetupType );
   pPages.push_back( PanelSzolarium );
   pPages.push_back( PanelTablazat );
   pPages.push_back( PanelHadver );  
   pPages.push_back( PanelSummary );

   BitBtnNext->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::RB_UpdateClick(TObject *Sender)
{
   pPages.clear();

   pPages.push_back( PanelDirectory );
   pPages.push_back( PanelSetupType );
   pPages.push_back( PanelHadver );  
   pPages.push_back( PanelSummary );

   BitBtnNext->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::RB_RemoveClick(TObject *Sender)
{
   pPages.clear();

   pPages.push_back( PanelDirectory );
   pPages.push_back( PanelSetupType );
   pPages.push_back( PanelSummary );

   BitBtnNext->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::PanelSummaryEnter(TObject *Sender)
{
   try
   {
      ListBoxSummary->Clear();

      ListBoxSummary->Items->Add( "" );
      if( RB_Setup->Checked )
         ListBoxSummary->Items->Add( LanguageStrings->Items->Strings[6] );
      if( RB_Update->Checked )
         ListBoxSummary->Items->Add( LanguageStrings->Items->Strings[8] );
      if( RB_Remove->Checked )
         ListBoxSummary->Items->Add( LanguageStrings->Items->Strings[7] );

      ListBoxSummary->Items->Add( "" );
      ListBoxSummary->Items->Add( LanguageStrings->Items->Strings[9] );
      ListBoxSummary->Items->Add( EditDirectory->Text );

      if( !RB_Remove->Checked )
      {
         ListBoxSummary->Items->Add( "" );
         ListBoxSummary->Items->Add( LanguageStrings->Items->Strings[10] );
         nCountSolarium = EditSzolariumCount->Text.ToInt();
         ListBoxSummary->Items->Add( AnsiString(nCountSolarium) );
      }

      if( RB_Update->Checked )
      {
         AnsiString strFile1, strFile2, strTmp;
         AnsiString strPath = EditDirectory->Text.c_str() + AnsiString( "\\" );

         ListBoxSummary->Items->Add( "" );
         ListBoxSummary->Items->Add( LanguageStrings->Items->Strings[11] );
         strFile1.sprintf( "%s%s", strPath.c_str(), "Sensolite.exe" );
         strFile2.sprintf( "%s%s", strCurrDir.c_str(), "Sensolite.exe" );
         strTmp.sprintf( "%s -> %s",
                         GetApplicationVersionNumber( strFile1.c_str() ).c_str(),
                         GetApplicationVersionNumber( strFile2.c_str() ).c_str() );
         strAppVersion = GetApplicationVersionNumber( strFile1.c_str() );
         ListBoxSummary->Items->Add( strTmp );
      }

      BitBtnExit->Enabled = true;
   }
   catch(const Exception& e)
   {
      Application->MessageBox( e.Message.c_str(),
                               LanguageStrings->Items->Strings[12].c_str(),
                               MB_ICONEXCLAMATION );
   }
}
//---------------------------------------------------------------------------
AnsiString TFormInstallMain::GetApplicationVersionNumber( LPTSTR lpszFilePath )
{
   AnsiString strVersionNumber;
   DWORD dwDummy;
   DWORD dwFVISize = GetFileVersionInfoSize( lpszFilePath , &dwDummy );
   LPBYTE lpVersionInfo = new BYTE[dwFVISize];

   GetFileVersionInfo( lpszFilePath , 0 , dwFVISize , lpVersionInfo );

   UINT uLen;
   VS_FIXEDFILEINFO *lpFfi;

   VerQueryValue( lpVersionInfo , _T("\\") , (LPVOID *)&lpFfi , &uLen );
   DWORD dwFileVersionMS = lpFfi->dwFileVersionMS;
   DWORD dwFileVersionLS = lpFfi->dwFileVersionLS;
   delete [] lpVersionInfo;

   DWORD dwLeftMost = HIWORD(dwFileVersionMS);
   DWORD dwSecondLeft = LOWORD(dwFileVersionMS);
   DWORD dwSecondRight = HIWORD(dwFileVersionLS);
   DWORD dwRightMost = LOWORD(dwFileVersionLS);

   strVersionNumber.sprintf( "%d.%d.%d.%d" , dwLeftMost, dwSecondLeft,dwSecondRight, dwRightMost );

   return strVersionNumber;
}
//---------------------------------------------------------------------------
AnsiString TFormInstallMain::LangStr( int LangId )
{
   char  s[1000];

   memset(s,0,sizeof(s));
   strncpy(s,LanguageStrings->Items->Strings[ LangId ].c_str(), 999);

   for( int i=0;i<(int)strlen(s)-1;i++ )
   {
      if( s[i] == '\\' && s[i+1] == 'n' )
      {
         s[i] = ' ';
         s[i+1] = '\n';
      }
      if( s[i] == '\\' && s[i+1] == 'r' )
      {
         s[i] = ' ';
         s[i+1] = '\r';
      }
   }
   return AnsiString(s);
}
//---------------------------------------------------------------------------
void TFormInstallMain::AddProgressLine( AnsiString strLine, bool isUpdate )
{
   strProgress = strLine;
   AddProgressLine( isUpdate );
}
//---------------------------------------------------------------------------
void TFormInstallMain::AddProgressLine( bool isUpdate )
{
   if( isUpdate )
   {
      MemoProgress->Lines->Delete( nLine );
   }
   nLine = MemoProgress->Lines->Add( strProgress );
   MemoProgress->Update();
   if( isUpdate )
   {
      Sleep( 250 );
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormInstallMain::BitBtnExitAppClick(TObject *Sender)
{
   ModalResult = mrOk;
   Close();
}
//---------------------------------------------------------------------------

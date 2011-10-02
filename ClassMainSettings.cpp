//---------------------------------------------------------------------------

#include <vcl.h>

#include <Registry.hpp>

#include <stdio.h>
#include <string.h>

#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
CS_MainSettings::CS_MainSettings()
{
   sSettingsFile = SETTINGS_FILE;

   GetApplicationVersionNumber();

   nGlobalLogLevel = 1;
   bAutoSaveOnExit = false;
   bCardUseWithPIN = false;

   memset( &stSettingsDefault, 0, sizeof(typ_settings) );
   memset( &stSettings, 0, sizeof(typ_settings) );

   strcpy( stSettingsDefault.strPasswordAdmin, "system" );
   strcpy( stSettingsDefault.strPasswordUser, "xxxxxx" );
   stSettingsDefault.nCountSolarium    = 1;

   stSettingsDefault.Left              = GetIntegerValueFromRegistry( "MainWindowLeft", 0 );
   stSettingsDefault.Top               = GetIntegerValueFromRegistry( "MainWindowTop", 0 );
   stSettingsDefault.VideoResolution   = GetIntegerValueFromRegistry( "WindowResolution", 2 );

   // Registry bejegyzések létrehozása, ha nincsenek 
   GetIntegerValueFromRegistry( "ExtendedWindowLeft", 0 );
   GetIntegerValueFromRegistry( "ExtendedWindowTop", 0 );

   stSettingsDefault.ComPort           = GetIntegerValueFromRegistry( "ComPort", 1 );
   stSettingsDefault.BaudRate          = GetIntegerValueFromRegistry( "BaudRate", 9600 );
   stSettingsDefault.Parity            = GetIntegerValueFromRegistry( "Parity", 0 );

   stSettingsDefault.dCurrentMuszak    = GetIntegerValueFromRegistry( "CurrentSession", 1 );

   strcpy( stSettingsDefault.strCurrentUser, GetStringValueFromRegistry( "CurrentUser", "Adminisztrátor" ).c_str() );

   stSettings = stSettingsDefault;

   stSoliSettingsDefault.StatusTop = 38;
   stSoliSettingsDefault.StatusHeight = 29;
   stSoliSettingsDefault.StatusFontSize = 14;
   stSoliSettingsDefault.StatusFontColorDef = clGreen;
   stSoliSettingsDefault.StatusFontColorPre = clGreen;
   stSoliSettingsDefault.StatusFontColorUse = clGreen;
   stSoliSettingsDefault.StatusFontHeight = -19;
   stSoliSettingsDefault.VisszaszamlalasTop = 61;
   stSoliSettingsDefault.VisszaszamlalasHeight = 43;
   stSoliSettingsDefault.VisszaszamlalasFontSize = 26;
   stSoliSettingsDefault.VisszaszamlalasFontColorDef = clBlack;
   stSoliSettingsDefault.VisszaszamlalasFontColorPre = clBlack;
   stSoliSettingsDefault.VisszaszamlalasFontColorUse = clBlack;
   stSoliSettingsDefault.VisszaszamlalasFontHeight = -35;
   stSoliSettingsDefault.IdoTop = 100;
   stSoliSettingsDefault.IdoHeight = 26;
   stSoliSettingsDefault.IdoFontSize = 16;
   stSoliSettingsDefault.IdoFontColorDef = clGreen;
   stSoliSettingsDefault.IdoFontColorPre = clGreen;
   stSoliSettingsDefault.IdoFontColorUse = clGreen;
   stSoliSettingsDefault.IdoFontHeight = -21;
   stSoliSettingsDefault.InformacioTop = 125;
   stSoliSettingsDefault.InformacioHeight = 29;
   stSoliSettingsDefault.InformacioFontSize = 14;
   stSoliSettingsDefault.InformacioFontColorDef = clMaroon;
   stSoliSettingsDefault.InformacioFontColorPre = clMaroon;
   stSoliSettingsDefault.InformacioFontColorUse = clMaroon;
   stSoliSettingsDefault.InformacioFontHeight = -19;
   stSoliSettingsDefault.PenzTop = 152;
   stSoliSettingsDefault.PenzHeight = 43;
   stSoliSettingsDefault.PenzFontSize = 26;
   stSoliSettingsDefault.PenzFontColorDef = clBlack;
   stSoliSettingsDefault.PenzFontColorPre = clBlack;
   stSoliSettingsDefault.PenzFontColorUse = clBlack;
   stSoliSettingsDefault.PenzFontHeight = -35;
   stSoliSettingsDefault.ColorDefault = 0x0007C776;
   stSoliSettingsDefault.ColorPrepare = 0x0000E1E1;
   stSoliSettingsDefault.ColorUsed = 0x004040FF;

   stSoliSettings = stSoliSettingsDefault;

   m_bPasswordRequired = true;

   bIsDatabaseOk = LoadSettingsFromFile(sSettingsFile.c_str());

   stSoliSettings.StatusTop = GetIntegerValueFromRegistry( "StatusTop", 38 );
   stSoliSettings.StatusHeight = GetIntegerValueFromRegistry( "StatusHeight", 29 );
   stSoliSettings.StatusFontSize = GetIntegerValueFromRegistry( "StatusFontSize", 14 );
   stSoliSettings.StatusFontColorDef = GetIntegerValueFromRegistry( "StatusFontColorDef", clGreen );
   stSoliSettings.StatusFontColorPre = GetIntegerValueFromRegistry( "StatusFontColorPre", clGreen );
   stSoliSettings.StatusFontColorUse = GetIntegerValueFromRegistry( "StatusFontColorUse", clGreen );
   stSoliSettings.StatusFontHeight = GetIntegerValueFromRegistry( "StatusFontHeight", -19 );
   stSoliSettings.VisszaszamlalasTop = GetIntegerValueFromRegistry( "VisszaszamlalasTop", 61 );
   stSoliSettings.VisszaszamlalasHeight = GetIntegerValueFromRegistry( "VisszaszamlalasHeight", 43 );
   stSoliSettings.VisszaszamlalasFontSize = GetIntegerValueFromRegistry( "VisszaszamlalasFontSize", 26 );
   stSoliSettings.VisszaszamlalasFontColorDef = GetIntegerValueFromRegistry( "VisszaszamlalasFontColorDef", clBlack );
   stSoliSettings.VisszaszamlalasFontColorPre = GetIntegerValueFromRegistry( "VisszaszamlalasFontColorPre", clBlack );
   stSoliSettings.VisszaszamlalasFontColorUse = GetIntegerValueFromRegistry( "VisszaszamlalasFontColorUse", clBlack );
   stSoliSettings.VisszaszamlalasFontHeight = GetIntegerValueFromRegistry( "VisszaszamlalasFontHeight", -35 );
   stSoliSettings.IdoTop = GetIntegerValueFromRegistry( "IdoTop", 100 );
   stSoliSettings.IdoHeight = GetIntegerValueFromRegistry( "IdoHeight", 26 );
   stSoliSettings.IdoFontSize = GetIntegerValueFromRegistry( "IdoFontSize", 16 );
   stSoliSettings.IdoFontColorDef = GetIntegerValueFromRegistry( "IdoFontColorDef", clGreen );
   stSoliSettings.IdoFontColorPre = GetIntegerValueFromRegistry( "IdoFontColorPre", clGreen );
   stSoliSettings.IdoFontColorUse = GetIntegerValueFromRegistry( "IdoFontColorUse", clGreen );
   stSoliSettings.IdoFontHeight = GetIntegerValueFromRegistry( "IdoFontHeight", -21 );
   stSoliSettings.InformacioTop = GetIntegerValueFromRegistry( "InformacioTop", 125 );
   stSoliSettings.InformacioHeight = GetIntegerValueFromRegistry( "InformacioHeight", 29 );
   stSoliSettings.InformacioFontSize = GetIntegerValueFromRegistry( "InformacioFontSize", 14 );
   stSoliSettings.InformacioFontColorDef = GetIntegerValueFromRegistry( "InformacioFontColorDef", clMaroon );
   stSoliSettings.InformacioFontColorPre = GetIntegerValueFromRegistry( "InformacioFontColorPre", clMaroon );
   stSoliSettings.InformacioFontColorUse = GetIntegerValueFromRegistry( "InformacioFontColorUse", clMaroon );
   stSoliSettings.InformacioFontHeight = GetIntegerValueFromRegistry( "InformacioFontHeight", -19 );
   stSoliSettings.PenzTop = GetIntegerValueFromRegistry( "PenzTop", 152 );
   stSoliSettings.PenzHeight = GetIntegerValueFromRegistry( "PenzHeight", 43 );
   stSoliSettings.PenzFontSize = GetIntegerValueFromRegistry( "PenzFontSize", 26 );
   stSoliSettings.PenzFontColorDef = GetIntegerValueFromRegistry( "PenzFontColorDef", clBlack );
   stSoliSettings.PenzFontColorPre = GetIntegerValueFromRegistry( "PenzFontColorPre", clBlack );
   stSoliSettings.PenzFontColorUse = GetIntegerValueFromRegistry( "PenzFontColorUse", clBlack );
   stSoliSettings.PenzFontHeight = GetIntegerValueFromRegistry( "PenzFontHeight", -35 );
   stSoliSettings.ColorDefault = GetIntegerValueFromRegistry( "ColorDefault", 0x0007C776 );
   stSoliSettings.ColorPrepare = GetIntegerValueFromRegistry( "ColorPrepare", 0x0000E1E1 );
   stSoliSettings.ColorUsed = GetIntegerValueFromRegistry( "ColorUsed", 0x004040FF );
   stSoliSettings.StatusFontName = GetStringValueFromRegistry( "StatusFontName", "Times New Roman" );
   stSoliSettings.VisszaszamlalasFontName = GetStringValueFromRegistry( "VisszaszamlalasFontName", "Times New Roman" );
   stSoliSettings.IdoFontName = GetStringValueFromRegistry( "IdoFontName", "Times New Roman" );
   stSoliSettings.InformacioFontName = GetStringValueFromRegistry( "InformacioFontName", "Times New Roman" );
   stSoliSettings.PenzFontName = GetStringValueFromRegistry( "PenzFontName", "Times New Roman" );
}
//---------------------------------------------------------------------------
CS_MainSettings::~CS_MainSettings()
{
   //
}
//---------------------------------------------------------------------------
bool CS_MainSettings::LoadSettingsFromFile( const char *strFile )
{
   FILE  *file = NULL;
   char  strTemp[10];
   int   nErrorMsgID;
   bool  bRet = false;

   memset( strTemp, 0, sizeof(strTemp) );

   file = fopen( strFile, "rb" );
   if( file != NULL )
   {
      fread( strTemp, 10, 1, file );
      if( strcmp( SETTINGS_FILE_VERSION, strTemp ) == 0 )
      {
         fread( &stSettings.nCountSolarium, sizeof(int), 1, file );
         fread( &stSettings.strPasswordAdmin, sizeof(stSettings.strPasswordAdmin), 1, file );
         fread( &stSettings.strPasswordUser, sizeof(stSettings.strPasswordUser), 1, file );

         DeCode( stSettings.strPasswordAdmin, sizeof(stSettings.strPasswordAdmin) );
         DeCode( stSettings.strPasswordUser, sizeof(stSettings.strPasswordUser) );

         bRet = true; 
      }
      else
      {
         LOG1( "#FV#CS_MainSettings::LoadSettingsFromFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( SETTINGS_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }

      fclose( file );
   }

   return bRet;
}
//---------------------------------------------------------------------------
bool CS_MainSettings::SaveSettingsToFile( const char *strFile )
{
   FILE  *file = NULL;
   bool   bRet = true;

   EnCode( stSettings.strPasswordAdmin, sizeof(stSettings.strPasswordAdmin) );
   EnCode( stSettings.strPasswordUser, sizeof(stSettings.strPasswordUser) );

   file = fopen( strFile, "wb" );
   if( file != NULL )
   {
      fwrite( SETTINGS_FILE_VERSION, 10, 1, file );
      fwrite( &stSettings.nCountSolarium, sizeof(stSettings.nCountSolarium), 1, file );
      fwrite( &stSettings.strPasswordAdmin, sizeof(stSettings.strPasswordAdmin), 1, file );
      fwrite( &stSettings.strPasswordUser, sizeof(stSettings.strPasswordUser), 1, file );
      fclose( file );
   }
   else
   {
      // nem sikerült létrehozni a file-t
      strLogMsg = AnsiString( "HIBA: Nem sikerült létrehozni: " ) + strFile;
      LOG1( strLogMsg );
      bRet = false;
   }

   DeCode( stSettings.strPasswordAdmin, sizeof(stSettings.strPasswordAdmin) );
   DeCode( stSettings.strPasswordUser, sizeof(stSettings.strPasswordUser) );

   SetIntegerValueInRegistry( "MainWindowLeft", stSettings.Left );
   SetIntegerValueInRegistry( "MainWindowTop", stSettings.Top );
   SetIntegerValueInRegistry( "WindowResolution", stSettings.VideoResolution );
   SetIntegerValueInRegistry( "ComPort", stSettings.ComPort );
   SetIntegerValueInRegistry( "BaudRate", stSettings.BaudRate );
   SetIntegerValueInRegistry( "Parity", stSettings.Parity );
   SetIntegerValueInRegistry( "CurrentSession", stSettings.dCurrentMuszak );
   SetStringValueInRegistry( "CurrentUser", stSettings.strCurrentUser );

   return bRet;
}
//---------------------------------------------------------------------------
bool CS_MainSettings::CheckSettingsToFile( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize,i;
   bool           bRet = true;

   file = fopen( strFile, "rb" );
   if( file != NULL )
   {
      // file megnyitása sikeres
      char strTemp[10];
      memset( strTemp, 0, sizeof(strTemp) );
      // verziószám kiolvasása
      fread( strTemp, 10, 1, file );
      if( strcmp( SETTINGS_FILE_VERSION, strTemp ) == 0 )
      {
         // verziószám egyezik
         //
         int   nCount = 0;
         // szoláriumok számának kiolvasása
         fread( &nCount, sizeof(int), 1, file );
         if( nCount != stSettings.nCountSolarium )
         {
            // szoláriumok száma nem egyezik
            //
            LOG1( "#FV#CS_MainSettings::CheckSettingsToFile" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a szoláriumok száma: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( stSettings.nCountSolarium ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( bRet )
         {
            // rekordok száma egyezik és van adat
            //
            char stTemp[20];

            // rekord beolvasása
            fread( &stTemp, sizeof(stTemp), 1, file );
            // szöveg dekódolása
            DeCode( stTemp, sizeof(stTemp) );
            // rekord ellenõrzése
            if( memcmp( &stSettings.strPasswordAdmin, &stTemp, sizeof(stTemp) ) != 0 )
            {
               // rekord nem egyezik
               //
               LOG1( "HIBA: Nem egyezik a rekord: [Admin] #FV#CS_MainSettings::CheckSettingsToFile" );
               bRet = false;
            }
            // rekord beolvasása
            fread( &stTemp, sizeof(stTemp), 1, file );
            // szöveg dekódolása
            DeCode( stTemp, sizeof(stTemp) );
            // rekord ellenõrzése
            if( memcmp( &stSettings.strPasswordUser, &stTemp, sizeof(stTemp) ) != 0 )
            {
               // rekord nem egyezik
               //
               LOG1( "HIBA: Nem egyezik a rekord: [User] #FV#CS_MainSettings::CheckSettingsToFile" );
               bRet = false;
            }
         }
      }
      else
      {
         // verziószám nem egyezik
         LOG1( "#FV#CS_MainSettings::CheckSettingsToFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( SETTINGS_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
         bRet = false;
      }
      fclose( file );
   }
   else
   {
      // nem lehetett megnyitni olvasásra a file-t
      strLogMsg = AnsiString( "HIBA: Nem sikerült ellenõrizni a mentést: " ) + strFile;
      LOG1( strLogMsg );
      bRet = false;
   }

   return bRet;
}
//---------------------------------------------------------------------------
void CS_MainSettings::SetCountSolarium( int nCount )
{
   stSettings.nCountSolarium = nCount;
}
//---------------------------------------------------------------------------
int CS_MainSettings::GetCountSolarium()
{
   return stSettings.nCountSolarium;
}
//---------------------------------------------------------------------------
bool CS_MainSettings::IsAccessGranted( int Level, char *Password )
{
   bool bRet = false;

   switch( Level )
   {
      case ACCESS_ADMIN:
         if( strcmp(Password, stSettings.strPasswordAdmin) == 0 )
            bRet = true;
         break;
      case ACCESS_USER:
         if( strcmp(Password, stSettings.strPasswordUser) == 0 )
            bRet = true;
         break;
   }

   return bRet;
}
//---------------------------------------------------------------------------
char* CS_MainSettings::GetAdminPassword()
{
   return stSettings.strPasswordAdmin;
}
//---------------------------------------------------------------------------
char* CS_MainSettings::GetUserPassword()
{
   return stSettings.strPasswordUser;
}
//---------------------------------------------------------------------------
void CS_MainSettings::SetPasswordRequired( bool bPasswordRequired )
{
   m_bPasswordRequired = bPasswordRequired;
}
//---------------------------------------------------------------------------
bool CS_MainSettings::IsPasswordRequired()
{
   return m_bPasswordRequired;
}
//---------------------------------------------------------------------------
void CS_MainSettings::ModifyPassword( int Level, char *Password )
{
   switch( Level )
   {
      case ACCESS_ADMIN:
         strcpy( stSettings.strPasswordAdmin, Password );
         break;
      case ACCESS_USER:
         strcpy( stSettings.strPasswordUser, Password );
         break;
   }

   if( SaveSettingsToFile(SETTINGS_FILE) &&
       CheckSettingsToFile(SETTINGS_FILE) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + AnsiString(SETTINGS_FILE);
      if( !SaveSettingsToFile(strFile.c_str()) ||
          !CheckSettingsToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: beállítások biztonsági mentés 1 sikertelen #FV#CS_MainSettings::ModifyPassword" );
      }

      strFile = AnsiString( "Db\\2_" ) + AnsiString(SETTINGS_FILE);
      if( !SaveSettingsToFile(strFile.c_str()) ||
          !CheckSettingsToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: beállítások biztonsági mentés 2 sikertelen #FV#CS_MainSettings::ModifyPassword" );
      }
   }
   else
   {
      LOG1( "HIBA: beállítások mentés sikertelen #FV#CS_MainSettings::ModifyPassword" );
   }
}
//---------------------------------------------------------------------------
void CS_MainSettings::SaveApplicationParameters( int Left, int Top, int VideoResolution )
{
   stSettings.Left = Left;
   stSettings.Top  = Top;
   stSettings.VideoResolution = VideoResolution;

   SetIntegerValueInRegistry( "MainWindowLeft", stSettings.Left );
   SetIntegerValueInRegistry( "MainWindowTop", stSettings.Top );
   SetIntegerValueInRegistry( "WindowResolution", stSettings.VideoResolution );
}
//---------------------------------------------------------------------------
void CS_MainSettings::SaveApplicationParameters( int Left, int Top )
{
   stSettings.Left = Left;
   stSettings.Top  = Top;

   SetIntegerValueInRegistry( "MainWindowLeft", stSettings.Left );
   SetIntegerValueInRegistry( "MainWindowTop", stSettings.Top );
   SetIntegerValueInRegistry( "WindowResolution", stSettings.VideoResolution );
}
//---------------------------------------------------------------------------
void CS_MainSettings::GetApplicationParameters( int *Left, int *Top, int *VideoResolution )
{
   *Left = stSettings.Left;
   *Top  = stSettings.Top;
   *VideoResolution = stSettings.VideoResolution;
}
//---------------------------------------------------------------------------
int CS_MainSettings::GetComPort()
{
   return stSettings.ComPort;
}
//---------------------------------------------------------------------------
DWORD CS_MainSettings::GetBaudRate()
{
   return stSettings.BaudRate;
}
//---------------------------------------------------------------------------
DWORD CS_MainSettings::GetParity()
{
   return stSettings.Parity;
}
//---------------------------------------------------------------------------
void CS_MainSettings::SaveCommParameters( int Port, DWORD BaudRate, DWORD Parity )
{
   stSettings.ComPort  = Port;
   stSettings.BaudRate = BaudRate;
   stSettings.Parity   = Parity;
}
//---------------------------------------------------------------------------
double CS_MainSettings::GetCurrentMuszak()
{
   return stSettings.dCurrentMuszak;
}
//---------------------------------------------------------------------------
char* CS_MainSettings::GetCurrentUser()
{
   return stSettings.strCurrentUser;
}
//---------------------------------------------------------------------------
void CS_MainSettings::SetCurrentUser( char *strLoginNev )
{
   strcpy( stSettings.strCurrentUser, strLoginNev );

   SetStringValueInRegistry( "CurrentUser", stSettings.strCurrentUser );
}
//---------------------------------------------------------------------------
void CS_MainSettings::ResetMuszak()
{
   stSettings.dCurrentMuszak = 0;

   SetIntegerValueInRegistry( "CurrentSession", stSettings.dCurrentMuszak );
}
//---------------------------------------------------------------------------
void CS_MainSettings::MuszakZaras()
{
   stSettings.dCurrentMuszak++;

   SetIntegerValueInRegistry( "CurrentSession", stSettings.dCurrentMuszak );
}
//---------------------------------------------------------------------------
void CS_MainSettings::SetIntegerValueInRegistry( AnsiString KeyName, int nValue )
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
void CS_MainSettings::SetStringValueInRegistry( AnsiString KeyName, AnsiString strValue )
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
void CS_MainSettings::SetBoolValueInRegistry( AnsiString KeyName, bool bValue )
{
   TRegistry *Registry = new TRegistry;
   try
   {
      Registry->RootKey = HKEY_LOCAL_MACHINE;
      Registry->OpenKey("SOFTWARE\\SzolariumVezerlo", true);
      Registry->WriteBool( KeyName, bValue );
   }
   __finally
   {
      delete Registry;
   }
}
//---------------------------------------------------------------------------
int CS_MainSettings::GetIntegerValueFromRegistry( AnsiString KeyName, int nDefValue )
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
AnsiString CS_MainSettings::GetStringValueFromRegistry( AnsiString KeyName, AnsiString strDefValue )
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
bool CS_MainSettings::GetBoolValueFromRegistry( AnsiString KeyName, bool bDefValue )
{
   bool bRet = bDefValue;
   TRegistry *Registry = new TRegistry;

   try
   {
      Registry->RootKey = HKEY_LOCAL_MACHINE;
      if( Registry->OpenKey("SOFTWARE\\SzolariumVezerlo", false) )
      {
         bRet = Registry->ReadBool( KeyName );
      }
   }
   catch (Exception &e)
   {
      SetBoolValueInRegistry( KeyName, bDefValue );
   }
   delete Registry;

   return bRet;
}
//---------------------------------------------------------------------------
void CS_MainSettings::GetApplicationVersionNumber()
{
   LPTSTR lpszFilePath = "Sensolite.exe";
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
//   DWORD dwRightMost = LOWORD(dwFileVersionLS);

//   strRet.sprintf( "%d.%d.%d.%d" , dwLeftMost, dwSecondLeft,dwSecondRight, dwRightMost );
   strVersionNumber.sprintf( "%d.%d.%d" , dwLeftMost, dwSecondLeft,dwSecondRight );
}
//---------------------------------------------------------------------------

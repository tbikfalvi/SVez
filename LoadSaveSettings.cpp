//---------------------------------------------------------------------------
/*
#include <vcl.h>

#include <Registry.hpp>

#include <stdio.h>
#include <string.h>

//#include "LoadSaveSettings.h"
#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
CS_MainSettings::CS_MainSettings()
{
   memset( &stSettingsDefault, 0, sizeof(typ_settings) );
   memset( &stSettings, 0, sizeof(typ_settings) );

   strcpy( stSettingsDefault.strPasswordAdmin, "system" );
   strcpy( stSettingsDefault.strPasswordUser, "xxxxxx" );
   stSettingsDefault.nCountSolarium    = 0;
   stSettingsDefault.Left              = 0;
   stSettingsDefault.Top               = 0;
   stSettingsDefault.VideoResolution   = 2;
   stSettingsDefault.ComPort           = 1;
   stSettingsDefault.BaudRate          = 9600;
   stSettingsDefault.Parity            = 0;
   stSettingsDefault.dCurrentMuszak    = 1;

   stSettings = stSettingsDefault;

   m_bPasswordRequired = true;

   LoadSettingsFromFile();
}
//---------------------------------------------------------------------------
CS_MainSettings::~CS_MainSettings()
{
   SaveSettingsToFile( "msfsv.dat" );
}
//---------------------------------------------------------------------------
void CS_MainSettings::LoadSettingsFromFile()
{
   FILE  *file = NULL;
   char  strTemp[10];

   memset( strTemp, 0, sizeof(strTemp) );

   file = fopen( "msfsv.dat", "rb" );
   if( file != NULL )
   {
      fread( strTemp, 10, 1, file );
      if( strcmp( SETTINGS_FILE_VERSION, strTemp ) == 0 )
      {
         fread( &stSettings, sizeof(typ_settings), 1, file );

         DeCode( stSettings.strPasswordAdmin, sizeof(stSettings.strPasswordAdmin) );
         DeCode( stSettings.strPasswordUser, sizeof(stSettings.strPasswordUser) );
      }
      fclose( file );
   }
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
      fwrite( &stSettings, sizeof(typ_settings), 1, file );
      fclose( file );
   }
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
}
//---------------------------------------------------------------------------
void CS_MainSettings::SaveApplicationParameters( int Left, int Top, int VideoResolution )
{
   stSettings.Left = Left;
   stSettings.Top  = Top;
   stSettings.VideoResolution = VideoResolution;
}
//---------------------------------------------------------------------------
void CS_MainSettings::SaveApplicationParameters( int Left, int Top )
{
   stSettings.Left = Left;
   stSettings.Top  = Top;
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
void CS_MainSettings::ResetMuszak()
{
   stSettings.dCurrentMuszak = 0;
}
//---------------------------------------------------------------------------
void CS_MainSettings::MuszakZaras()
{
   stSettings.dCurrentMuszak++;
}
//---------------------------------------------------------------------------

*/

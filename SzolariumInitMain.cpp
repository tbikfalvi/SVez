//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>

#include "SzolariumInitMain.h"
#include "Database.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TFormMain::EnCode( char *str, int size )
{
   for(int i=0;i<size;i++)
   {
      str[i] ^= 11;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::BitBtnOkClick(TObject *Sender)
{
   FILE          *file = NULL;
   unsigned int   nSize = 0;

   file = fopen( BERLETTIPUS_FILE, "wb" );
   fwrite( BERLETTIPUS_FILE_VERSION, 10, 1, file );
   fwrite( &nSize, sizeof(unsigned int), 1, file );
   fclose( file );

   file = fopen( BERLET_FILE, "wb" );
   fwrite( BERLET_FILE_VERSION, 10, 1, file );
   fwrite( &nSize, sizeof(unsigned int), 1, file );
   fclose( file );

   file = fopen( BERLETHASZNALAT_FILE, "wb" );
   fwrite( BERLETHASZNALAT_FILE_VERSION, 10, 1, file );
   fwrite( &nSize, sizeof(unsigned int), 1, file );
   fclose( file );

   file = fopen( KONYVGENERAL_FILE, "wb" );
   fwrite( KONYV_GENERAL_FILE_VERSION, 10, 1, file );
   fwrite( &nSize, sizeof(unsigned int), 1, file );
   fclose( file );

   file = fopen( KONYVSZOLARIUM_FILE, "wb" );
   fwrite( KONYV_SZOLARIUM_FILE_VERSION, 10, 1, file );
   fwrite( &nSize, sizeof(unsigned int), 1, file );
   fclose( file );

   file = fopen( KOSAR_FILE, "wb" );
   fwrite( KOSAR_FILE_VERSION, 10, 1, file );
   fwrite( &nSize, sizeof(unsigned int), 1, file );
   fclose( file );

   typ_settings   stSettingsDefault;
   
   memset( &stSettingsDefault, 0, sizeof(typ_settings) );

   strcpy( stSettingsDefault.strPasswordAdmin, "system" );
   strcpy( stSettingsDefault.strPasswordUser, "xxxxxx" );
   stSettingsDefault.nCountSolarium    = EditSzoliCount->Text.ToInt();
   stSettingsDefault.Left              = 0;
   stSettingsDefault.Top               = 0;
   stSettingsDefault.VideoResolution   = 2;
   stSettingsDefault.ComPort           = 1;
   stSettingsDefault.BaudRate          = 9600;
   stSettingsDefault.Parity            = 0;
   stSettingsDefault.dCurrentMuszak    = 1;
   strcpy( stSettingsDefault.strCurrentUser, "" );

   EnCode( stSettingsDefault.strPasswordAdmin, sizeof(stSettingsDefault.strPasswordAdmin) );
   EnCode( stSettingsDefault.strPasswordUser, sizeof(stSettingsDefault.strPasswordUser) );
   EnCode( stSettingsDefault.strCurrentUser, sizeof(stSettingsDefault.strCurrentUser) );

   file = fopen( SETTINGS_FILE, "wb" );
   if( file != NULL )
   {
      fwrite( SETTINGS_FILE_VERSION, 10, 1, file );
      fwrite( &stSettingsDefault, sizeof(typ_settings), 1, file );
      fclose( file );
   }

   typ_penztar Penztar;

   memset( &Penztar, 0, sizeof(typ_penztar) );
   file = fopen( PENZTAR_FILE, "wb" );
   fwrite( PENZTAR_FILE_VERSION, 10, 1, file );
   fwrite( &Penztar, sizeof(typ_penztar), 1, file );
   fclose( file );

   file = fopen( PENZTARLOG_FILE, "wb" );
   fwrite( PENZTAR_FILE_VERSION, 10, 1, file );
   fclose( file );

   for( int i=0; i<stSettingsDefault.nCountSolarium; i++ )
   {
      AnsiString     DataFileName = AnsiString( SOLARIUM_FILE )+AnsiString( i )+AnsiString( ".dat" );
      typ_szoliadat  stAdat;

      memset( &stAdat, 0, sizeof(typ_szoliadat) );
      sprintf( stAdat.strNev, "Szolárium %d", i );
      stAdat.bInfraSzolarium = false;
      stAdat.nIdoVetkozes = 60;
      stAdat.nIdoUtohutes = 60;
      stAdat.nIdoSzauna = 0;
      stAdat.nKedvezmenyIdoStart = 0;
      stAdat.nKedvezmenyIdoStop = 0;
      stAdat.nCsoUzemoraMax = 600*3600;
      stAdat.nCsoUzemora = 0;
      stAdat.bShowCsoUzemora = false;
      stAdat.nMaxBarnulas = 100;
      memset( &(stAdat.stIdoForint), 0, sizeof(typ_idoforint)*40 );
      memset( &(stAdat.stIdoForintKedv), 0, sizeof(typ_idoforint)*40 );

      EnCode( stAdat.strNev, sizeof(stAdat.strNev) );

      file = fopen( DataFileName.c_str(), "wb" );
      fwrite( SOLARIUM_FILE_VERSION, 10, 1, file );
      fwrite( &stAdat, sizeof(typ_szoliadat), 1, file );
      fclose( file );
   }

   file = fopen( TERMEK_FILE, "wb" );
   fwrite( TERMEK_FILE_VERSION, 10, 1, file );
   fwrite( &nSize, sizeof(unsigned int), 1, file );
   fclose( file );

   file = fopen( USER_FILE, "wb" );
   fwrite( USER_FILE_VERSION, 10, 1, file );
   fwrite( &nSize, sizeof(unsigned int), 1, file );
   fclose( file );

   Application->MessageBox( "Adatbázis létrehozva", "Információ", MB_ICONINFORMATION );

   Close();
}
//---------------------------------------------------------------------------

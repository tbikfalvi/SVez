//---------------------------------------------------------------------------

#include <vcl.h>
#include <Registry.hpp>

#include "Classes.h"
#include "Database.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
CS_FileManagement::CS_FileManagement()
{
   strLogFile = "fsv.log";
}
//---------------------------------------------------------------------------
CS_FileManagement::~CS_FileManagement()
{
}
//---------------------------------------------------------------------------
void CS_FileManagement::EnCode( char *str, int size )
{
   for(int i=0;i<size;i++)
   {
      str[i] ^= 11;
   }
}
//---------------------------------------------------------------------------
void CS_FileManagement::DeCode( char *str, int size )
{
   for(int i=0;i<size;i++)
   {
      str[i] ^= 11;
   }
}
//---------------------------------------------------------------------------
void CS_FileManagement::LOG1( AnsiString strLogMessage )
{
   LOG( strLogMessage, 1 );
}
//---------------------------------------------------------------------------
void CS_FileManagement::LOG2( AnsiString strLogMessage )
{
   LOG( strLogMessage, 2 );
}
//---------------------------------------------------------------------------
void CS_FileManagement::LOG3( AnsiString strLogMessage )
{
   LOG( strLogMessage, 3 );
}
//---------------------------------------------------------------------------
void CS_FileManagement::LOG4( AnsiString strLogMessage )
{
   LOG( strLogMessage, 4 );
}
//---------------------------------------------------------------------------
void CS_FileManagement::LOG( AnsiString strLogMessage, int nLogLevel )
{
   FILE  *file = NULL;

   if( nLogLevel > ReadLogLevelFromRegistry() )
      return;

   if( strcmp( strLogMessage.AnsiLastChar(), "\n" ) == 0 )
      strLogMessage = strLogMessage.SubString( 1, strLogMessage.Length()-1 );
   if( strcmp( strLogMessage.AnsiLastChar(), "\r" ) == 0 )
      strLogMessage = strLogMessage.SubString( 1, strLogMessage.Length()-1 );

   if( (file = fopen( strLogFile.c_str(), "at" )) != NULL )
   {
      fputs( FormatDateTime("yyyy/mm/dd\thh:nn:ss\t",Now()).c_str(), file );
      for( int i=1; i<nLogLevel; i++ )
         fputs( " ", file );
      fputs( strLogMessage.c_str(), file );
      fputs( "\n", file );
      fclose( file );
   }
}
//---------------------------------------------------------------------------
int CS_FileManagement::CompareFiles( AnsiString strFile1, AnsiString strFile2 )
{
   int    nRet = 0;

   int    iFileHandle;
   int    iFileLength;
   char  *pszBuffer1 = NULL;
   char  *pszBuffer2 = NULL;
   int    nFileDate1;
   int    nFileDate2;

   try
   {
      // 1. file d�tum�nak kiolvas�sa
      nFileDate1 = FileAge( strFile1 );
      // 1. file tartalm�nak kiolvas�sa
      if( (iFileHandle = FileOpen(strFile1, fmOpenRead)) != -1 )
      {
         iFileLength = FileSeek(iFileHandle,0,2);
         FileSeek(iFileHandle,0,0);
         pszBuffer1 = new char[iFileLength+1];
         memset( pszBuffer1, 0, sizeof(pszBuffer1) );
         FileRead(iFileHandle, pszBuffer1, iFileLength);
         FileClose(iFileHandle);
      }
      // 2. file d�tum�nak kiolvas�sa
      nFileDate2 = FileAge( strFile2 );
      // 2. file tartalm�nak kiolvas�sa
      if( (iFileHandle = FileOpen(strFile2, fmOpenRead)) != -1 )
      {
         iFileLength = FileSeek(iFileHandle,0,2);
         FileSeek(iFileHandle,0,0);
         pszBuffer2 = new char[iFileLength+1];
         memset( pszBuffer2, 0, sizeof(pszBuffer2) );
         FileRead(iFileHandle, pszBuffer2, iFileLength);
         FileClose(iFileHandle);
      }
   }
   catch(...)
   {
      // ha nem siker�lt hiba
      nRet = -1;
   }

   if( pszBuffer1 != NULL && pszBuffer2 != NULL && nRet == 0 )
   {
      // ha nem volt hiba �s volt tartalma a file-oknak
      // file-ok tartalm�nak �sszehasonl�t�sa
      if( memcmp( pszBuffer1, pszBuffer2, iFileLength ) != 0 )
      {
         // a k�t file tartalmilag nem egyezik
         if( nFileDate1 <= nFileDate2 )
         {
            // az els� file a r�gebbi
            nRet = 1;
         }
         else if( nFileDate1 > nFileDate2 )
         {
            // a m�sodik file a r�gebbi
            nRet = 2;
         }
      }
      else
      {
         // a k�t file tartalmilag megegyezik
         nRet = 0;
      }
   }

   // ideiglenes buffer-ek t�rl�se
   if( pszBuffer1 )
      delete [] pszBuffer1;
   if( pszBuffer2 )
      delete [] pszBuffer2;

   return nRet;
}
//---------------------------------------------------------------------------
bool CS_FileManagement::CheckAndCorrectDBFiles( char *strFileOriginal, int *nErrorMsgID )
{
   bool        bRet = true;

   AnsiString  strFileNameO = AnsiString( strFileOriginal );
   AnsiString  strFileName1;
   AnsiString  strFileName2;
   bool        bOriginalMissing = false;
   bool        bSecondary1Missing = false;
   bool        bSecondary2Missing = false;

   // file nevek meghat�roz�sa
   strFileName1.sprintf( "Db\\1_%s", strFileOriginal );
   strFileName2.sprintf( "Db\\1_%s", strFileOriginal );

   // file-ok l�tez�s�nek ellen�rz�se
   if( !FileExists( strFileNameO ) )
   {
      bOriginalMissing = true;
   }
   if( !FileExists( strFileName1 ) )
   {
      bSecondary1Missing = true;
   }
   if( !FileExists( strFileName2 ) )
   {
      bSecondary2Missing = true;
   }

   // file-ok l�tez�s�nek ellen�rz�se
   if( bOriginalMissing && bSecondary1Missing && bSecondary2Missing )
   {
      // egyik file sem l�tezik
      *nErrorMsgID = ERROR_DB_FILE_MISSING;
      bRet = false;
   }
   else if( (!bOriginalMissing && bSecondary1Missing) ||
            (!bOriginalMissing && bSecondary2Missing) )
   {
      // eredeti file l�tezik, de nincsenek meg a bizt. file-ok
      // bizt. file-ok l�trehoz�sa -> nincs sz�ks�g ellen�rz�sre
      //SaveSecondaryFiles( strFileNameO.c_str() );
   }
   else
   {
      // megvan az �sszes file
      // file-ok �sszehasonl�t�sa
      if( CompareFiles(strFileNameO, strFileName1) == 0 )
      {
         // az eredeti �s az 1. bizt. m�solat megegyezik
         if( CompareFiles(strFileNameO, strFileName2) != 0 )
         {
            // az eredeti �s a 2. bizt. m�solat nem egyezik meg
            // 2. bizt. m�solat fel�l�r�sa
            CopyFile( strFileNameO.c_str(), strFileName2.c_str(), false );
         }
      }
      else if( CompareFiles(strFileNameO, strFileName2) == 0 )
      {
         // az eredeti �s a 2. bizt. m�solat megegyezik
         // az eredeti �s az 1. bizt. m�solat nem egyezik meg
         // 1. bizt. m�solat fel�l�r�sa
         CopyFile( strFileNameO.c_str(), strFileName1.c_str(), false );
      }
      else if( CompareFiles(strFileName1, strFileName2) == 0 )
      {
         // az eredeti nem egyezik meg a bizt. m�solatokkal
         // a k�t bizt. m�solat megegyezik
         // eredeti fel�l�r�sa a bizt. m�solattal
         CopyFile( strFileName1.c_str(), strFileNameO.c_str(), false );
      }
      else
      {
         // egyik sem egyezik meg a m�sikkal
      }
   }

   return bRet;
}
//---------------------------------------------------------------------------
int CS_FileManagement::ReadLogLevelFromRegistry()
{
   int nRet = 1;
   TRegistry *Registry = new TRegistry;
   try
   {
      Registry->RootKey = HKEY_LOCAL_MACHINE;
      // false because we do not want to create it if it doesn�t exist
      if( Registry->OpenKey("SOFTWARE\\SzolariumVezerlo", false) )
      {
         nRet = Registry->ReadInteger( "LogLevel" );
      }
   }
   __finally
   {
      delete Registry;
   }
   return nRet;
}
//---------------------------------------------------------------------------
void CS_FileManagement::WriteLogLevelToRegistry( int nLogLevel )
{
   TRegistry *Registry = new TRegistry;
   try
   {
      Registry->RootKey = HKEY_LOCAL_MACHINE;
      Registry->OpenKey("SOFTWARE\\SzolariumVezerlo", true);
      Registry->WriteInteger( "LogLevel", nLogLevel );
   }
   __finally
   {
      delete Registry;
   }
}
//---------------------------------------------------------------------------

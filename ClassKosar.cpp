//---------------------------------------------------------------------------

#include <vcl.h>

#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
CS_Kosar::CS_Kosar()
{
   LOG4( "CS_Kosar::CS_Kosar" );

   sKosarFile = KOSAR_FILE;

   bIsDatabaseOk = LoadDataFromFile();
}
//---------------------------------------------------------------------------
CS_Kosar::~CS_Kosar()
{
   LOG4( "CS_Kosar::~CS_Kosar" );

   //SaveDataToFile( sKosarFile.c_str() );
}
//---------------------------------------------------------------------------
bool CS_Kosar::LoadDataFromFile()
{
   FILE  *file = NULL;
   char  strTemp[10];
   int   nCount = 0;
   int   nErrorMsgID;
   bool bRet = false;

   memset( strTemp, 0, sizeof(strTemp) );

   file = fopen( sKosarFile.c_str(), "rb" );
   if( file != NULL )
   {
      fread( strTemp, 10, 1, file );
      if( strcmp( KOSAR_FILE_VERSION, strTemp ) == 0 )
      {
         fread( &nCount, sizeof(int), 1, file );

         LOG4( strLogMsg.sprintf( "CS_Kosar::LoadDataFromFile - %d", nCount ) );
         if( nCount > 0 )
         {
            typ_kosar  stTemp;
            for( int i=0; i<nCount; i++ )
            {
               fread( &stTemp, sizeof(typ_kosar), 1, file );
               DeCode( stTemp.strNev, sizeof(stTemp.strNev) );
               Kosar.push_back( stTemp );
            }
         }
         bRet = true;
      }
      else
      {
         LOG1( "#FV#CS_Kosar::LoadDataFromFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( KOSAR_FILE_VERSION ) +
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
bool CS_Kosar::SaveDataToFile( const char *strFile )
{
   FILE  *file = NULL;
   int   nSize;
   bool           bRet = true;

   if( (file = fopen( strFile, "wb" )) != NULL )
   {
      fwrite( KOSAR_FILE_VERSION, 10, 1, file );

      nSize = (int)Kosar.size();

      LOG4( strLogMsg.sprintf( "CS_Kosar::SaveDataToFile - %d", nSize ) );

      fwrite( &nSize, sizeof(int), 1, file );
      for( int i=0; i<(int)Kosar.size(); i++ )
      {
         EnCode( Kosar[i].strNev, sizeof(Kosar[i].strNev) );
         EnCode( Kosar[i].strVonalkod, sizeof(Kosar[i].strVonalkod) );
         fwrite( &Kosar[i], sizeof(typ_kosar), 1, file );
         DeCode( Kosar[i].strNev, sizeof(Kosar[i].strNev) );
         DeCode( Kosar[i].strVonalkod, sizeof(Kosar[i].strVonalkod) );
      }

      fclose( file );
   }
   else
   {
      // nem sikerült létrehozni a file-t
      strLogMsg = AnsiString( "HIBA: Nem sikerült létrehozni: " ) + strFile;
      LOG1( strLogMsg );
      bRet = false;
   }

   return bRet;
}
//---------------------------------------------------------------------------
bool CS_Kosar::CheckDataToFile( const char *strFile )
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
      if( strcmp( KOSAR_FILE_VERSION, strTemp ) == 0 )
      {
         // verziószám egyezik
         //
         unsigned int   nCount = 0;
         // rekordok számának kiolvasása
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount != Kosar.size() )
         {
            // rekordok száma nem egyezik
            //
            LOG1( "#FV#CS_Kosar::CheckDataToFile" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordszám: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( Kosar.size() ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( nCount > 0 && bRet )
         {
            // rekordok száma egyezik és van adat
            //
            typ_kosar   stTemp;
            for( i=0; i<nCount; i++ )
            {
               // rekord beolvasása
               fread( &stTemp, sizeof(typ_kosar), 1, file );
               // szöveg dekódolása
               DeCode( stTemp.strNev, sizeof(stTemp.strNev) );
               DeCode( stTemp.strVonalkod, sizeof(stTemp.strVonalkod) );
               // rekord ellenõrzése
               if( memcmp( &Kosar[i], &stTemp, sizeof(typ_kosar) ) != 0 )
               {
                  // rekord nem egyezik
                  //
                  LOG1( "#FV#CS_Kosar::CheckDataToFile" );
                  strLogMsg = AnsiString( "HIBA: Nem egyezik a rekord: [" ) +
                              AnsiString( i ) +
                              AnsiString( "]" );
                  LOG1( strLogMsg );
                  bRet = false;
                  break;
               }
            }
         }
      }
      else
      {
         // verziószám nem egyezik
         LOG1( "#FV#CS_Kosar::CheckDataToFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( KOSAR_FILE_VERSION ) +
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
void CS_Kosar::AddKosar( typ_kosar stTemp )
{
   double i;
   for( i=1; ; i++ )
   {
      typ_kosar stTmp = GetKosarID( i );
      if( stTmp.nID == 0 )
         break;
   }
   stTemp.nID = i;

   Kosar.push_back( stTemp );

   if( SaveDataToFile(sKosarFile.c_str()) &&
       CheckDataToFile(sKosarFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sKosarFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: kosár biztonsági mentés 1 sikertelen #FV#CS_Kosar::AddKosar" );
      }

      strFile = AnsiString( "Db\\2_" ) + sKosarFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: kosár biztonsági mentés 2 sikertelen #FV#CS_Kosar::AddKosar" );
      }
   }
   else
   {
      LOG1( "HIBA: kosár mentés sikertelen #FV#CS_Kosar::AddKosar" );
   }
}
//---------------------------------------------------------------------------
bool CS_Kosar::DeleteKosar( int nID )
{
   int i;

   for( i=0; i<(int)Kosar.size(); i++ )
   {
      if( Kosar[i].nID == nID )
      {
         Kosar.erase( Kosar.begin()+i );

         if( SaveDataToFile(sKosarFile.c_str()) &&
             CheckDataToFile(sKosarFile.c_str()) )
         {
            AnsiString strFile;

            strFile = AnsiString( "Db\\1_" ) + sKosarFile;
            if( !SaveDataToFile(strFile.c_str()) ||
                !CheckDataToFile(strFile.c_str()) )
            {
               LOG1( "HIBA: kosár biztonsági mentés 1 sikertelen #FV#CS_Kosar::DeleteKosar" );
            }

            strFile = AnsiString( "Db\\2_" ) + sKosarFile;
            if( !SaveDataToFile(strFile.c_str()) ||
                !CheckDataToFile(strFile.c_str()) )
            {
               LOG1( "HIBA: kosár biztonsági mentés 2 sikertelen #FV#CS_Kosar::DeleteKosar" );
            }
         }
         else
         {
            LOG1( "HIBA: kosár mentés sikertelen #FV#CS_Kosar::DeleteKosar" );
         }
         break;
      }
   }

   if( i ==(int) Kosar.size() )
      return false;
   else
      return true;
}
//---------------------------------------------------------------------------
bool CS_Kosar::DeleteKosar( char *strVonalkod )
{
   int i;

   for( i=0; i<(int)Kosar.size(); i++ )
   {
      if( strcmp(Kosar[i].strVonalkod, strVonalkod) == 0 )
      {
         Kosar.erase( Kosar.begin()+i );

         if( SaveDataToFile(sKosarFile.c_str()) &&
             CheckDataToFile(sKosarFile.c_str()) )
         {
            AnsiString strFile;

            strFile = AnsiString( "Db\\1_" ) + sKosarFile;
            if( !SaveDataToFile(strFile.c_str()) ||
                !CheckDataToFile(strFile.c_str()) )
            {
               LOG1( "HIBA: kosár biztonsági mentés 1 sikertelen #FV#CS_Kosar::DeleteKosar" );
            }

            strFile = AnsiString( "Db\\2_" ) + sKosarFile;
            if( !SaveDataToFile(strFile.c_str()) ||
                !CheckDataToFile(strFile.c_str()) )
            {
               LOG1( "HIBA: kosár biztonsági mentés 2 sikertelen #FV#CS_Kosar::DeleteKosar" );
            }
         }
         else
         {
            LOG1( "HIBA: kosár mentés sikertelen #FV#CS_Kosar::DeleteKosar" );
         }
         break;
      }
   }

   if( i ==(int) Kosar.size() )
      return false;
   else
      return true;
}
//---------------------------------------------------------------------------
void CS_Kosar::EmptyKosar()
{
   int nSize = (int)Kosar.size();

   LOG4( strLogMsg.sprintf( "CS_Kosar::EmptyKosar - %d", nSize ) );

   for( int i=0; i<nSize; i++ )
   {
      Kosar.erase( Kosar.begin() );
   }

   if( SaveDataToFile(sKosarFile.c_str()) &&
       CheckDataToFile(sKosarFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sKosarFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: kosár biztonsági mentés 1 sikertelen #FV#CS_Kosar::EmptyKosar" );
      }

      strFile = AnsiString( "Db\\2_" ) + sKosarFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: kosár biztonsági mentés 2 sikertelen #FV#CS_Kosar::EmptyKosar" );
      }
   }
   else
   {
      LOG1( "HIBA: kosár mentés sikertelen #FV#CS_Kosar::EmptyKosar" );
   }
}
//---------------------------------------------------------------------------
typ_kosar CS_Kosar::GetKosar( int nCount )
{
   typ_kosar  stTemp;

   memset( &stTemp, 0, sizeof(typ_kosar) );

   if( nCount < (int)Kosar.size() )
      return Kosar[nCount];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
typ_kosar CS_Kosar::GetKosarID( int nID )
{
   typ_kosar  stTemp;
   int        i;

   memset( &stTemp, 0, sizeof(typ_kosar) );

   for( i=0; i<(int)Kosar.size(); i++ )
   {
      if( Kosar[i].nID == nID )
         break;
   }

   if( i < (int)Kosar.size() )
      return Kosar[i];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
int CS_Kosar::GetKosarCount()
{
   return Kosar.size();
}
//---------------------------------------------------------------------------
int CS_Kosar::GetKosarAr()
{
   int   nOsszeg = 0;

   for( int i=0; i<(int)Kosar.size(); i++ )
   {
      nOsszeg += Kosar[i].nAr * Kosar[i].nDarab;
   }

   return nOsszeg;
}
//---------------------------------------------------------------------------

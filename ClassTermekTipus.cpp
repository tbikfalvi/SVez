//---------------------------------------------------------------------------

#include <vcl.h>

#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
CS_TermekTipus::CS_TermekTipus()
{
   sTermekTipusFile = TERMEKTIPUS_FILE;
   sTermekTipusAsgFile = TERMEKTIPUSASG_FILE;

   LoadDataFromFile();
}
//---------------------------------------------------------------------------
CS_TermekTipus::~CS_TermekTipus()
{
   //SaveDataToFile( sTermekTipusFile.c_str() );
}
//---------------------------------------------------------------------------
void CS_TermekTipus::LoadDataFromFile()
{
   LoadTermektipus();
   LoadTermektipusAsg();
}
//---------------------------------------------------------------------------
void CS_TermekTipus::LoadTermektipus()
{
   FILE           *file = NULL;
   char           strTemp[10];
   unsigned int   nCount = 0;
   int            nErrorMsgID;

   memset( strTemp, 0, sizeof(strTemp) );

/*   if( !CheckAndCorrectDBFiles( sTermekTipusFile.c_str(), &nErrorMsgID ) )
   {
      AnsiString  strMsg;
      strMsg.sprintf( "\n\nError Code: sys113\nError ID: %d", nErrorMsgID );
      throw Exception( strMsg );
   }*/

   file = fopen( sTermekTipusFile.c_str(), "rb" );
   if( file != NULL )
   {
      fread( strTemp, 10, 1, file );
      if( strcmp( TERMEKTIPUS_FILE_VERSION, strTemp ) == 0 )
      {
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount > 0 )
         {
            typ_termektipus  stTemp;
            for( unsigned int i=0; i<nCount; i++ )
            {
               fread( &stTemp, sizeof(typ_termektipus), 1, file );
               DeCode( stTemp.strNev, sizeof(stTemp.strNev) );
               TermekTipus.push_back( stTemp );
            }
         }
      }
      else
      {
         LOG1( "#FV#CS_TermekTipus::LoadTermektipus" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( TERMEKTIPUS_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }
      fclose( file );
   }
}
//---------------------------------------------------------------------------
void CS_TermekTipus::LoadTermektipusAsg()
{
   FILE           *file = NULL;
   char           strTemp[10];
   unsigned int   nCount = 0;
   int            nErrorMsgID;

   memset( strTemp, 0, sizeof(strTemp) );

/*   if( !CheckAndCorrectDBFiles( sTermekTipusAsgFile.c_str(), &nErrorMsgID ) )
   {
      AnsiString  strMsg;
      strMsg.sprintf( "\n\nError Code: sys114\nError ID: %d", nErrorMsgID );
      throw Exception( strMsg );
   }*/

   file = fopen( sTermekTipusAsgFile.c_str(), "rb" );
   if( file != NULL )
   {
      fread( strTemp, 10, 1, file );
      if( strcmp( TERMEKTIPUS_FILE_VERSION, strTemp ) == 0 )
      {
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount > 0 )
         {
            typ_termektipusassign  stTemp;
            for( unsigned int i=0; i<nCount; i++ )
            {
               fread( &stTemp, sizeof(typ_termektipusassign), 1, file );
               TermekTipusAsg.push_back( stTemp );
            }
         }
      }
      else
      {
         LOG1( "#FV#CS_TermekTipus::LoadTermektipusAsg" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( TERMEKTIPUS_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }
      fclose( file );
   }
}
//---------------------------------------------------------------------------
bool CS_TermekTipus::SaveDataToFile( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize;
   bool           bRet = true;

   file = fopen( strFile, "wb" );
   if( file != NULL )
   {
      fwrite( TERMEKTIPUS_FILE_VERSION, 10, 1, file );

      nSize = TermekTipus.size();
      fwrite( &nSize, sizeof(unsigned int), 1, file );
      for( unsigned int i=0; i<TermekTipus.size(); i++ )
      {
         EnCode( TermekTipus[i].strNev, sizeof(TermekTipus[i].strNev) );
         fwrite( &TermekTipus[i], sizeof(typ_termektipus), 1, file );
         DeCode( TermekTipus[i].strNev, sizeof(TermekTipus[i].strNev) );
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
bool CS_TermekTipus::CheckDataToFile( const char *strFile )
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
      if( strcmp( TERMEKTIPUS_FILE_VERSION, strTemp ) == 0 )
      {
         // verziószám egyezik
         //
         unsigned int   nCount = 0;
         // rekordok számának kiolvasása
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount != TermekTipus.size() )
         {
            // rekordok száma nem egyezik
            //
            LOG1( "#FV#CS_TermekTipus::CheckDataToFile" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordszám: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( TermekTipus.size() ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( nCount > 0 && bRet )
         {
            // rekordok száma egyezik és van adat
            //
            typ_termektipus   stTemp;
            for( i=0; i<nCount; i++ )
            {
               // rekord beolvasása
               fread( &stTemp, sizeof(typ_termektipus), 1, file );
               // szöveg dekódolása
               DeCode( stTemp.strNev, sizeof(stTemp.strNev) );
               // rekord ellenõrzése
               if( memcmp( &TermekTipus[i], &stTemp, sizeof(typ_termektipus) ) != 0 )
               {
                  // rekord nem egyezik
                  //
                  LOG1( "#FV#CS_TermekTipus::CheckDataToFile" );
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
         LOG1( "#FV#CS_TermekTipus::CheckDataToFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( TERMEKTIPUS_FILE_VERSION ) +
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
bool CS_TermekTipus::SaveDataToFileAsg( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize;
   bool           bRet = true;

   file = fopen( strFile, "wb" );
   if( file != NULL )
   {
      fwrite( TERMEKTIPUS_FILE_VERSION, 10, 1, file );

      nSize = TermekTipusAsg.size();
      fwrite( &nSize, sizeof(unsigned int), 1, file );
      for( unsigned int i=0; i<TermekTipusAsg.size(); i++ )
      {
         fwrite( &TermekTipusAsg[i], sizeof(typ_termektipusassign), 1, file );
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
bool CS_TermekTipus::CheckDataToFileAsg( const char *strFile )
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
      if( strcmp( TERMEKTIPUS_FILE_VERSION, strTemp ) == 0 )
      {
         // verziószám egyezik
         //
         unsigned int   nCount = 0;
         // rekordok számának kiolvasása
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount != TermekTipusAsg.size() )
         {
            // rekordok száma nem egyezik
            //
            LOG1( "#FV#CS_TermekTipus::CheckDataToFileAsg" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordszám: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( TermekTipusAsg.size() ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( nCount > 0 && bRet )
         {
            // rekordok száma egyezik és van adat
            //
            typ_termektipusassign   stTemp;
            for( i=0; i<nCount; i++ )
            {
               // rekord beolvasása
               fread( &stTemp, sizeof(typ_termektipusassign), 1, file );
               // rekord ellenõrzése
               if( memcmp( &TermekTipusAsg[i], &stTemp, sizeof(typ_termektipusassign) ) != 0 )
               {
                  // rekord nem egyezik
                  //
                  LOG1( "#FV#CS_TermekTipus::CheckDataToFileAsg" );
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
         LOG1( "#FV#CS_TermekTipus::CheckDataToFileAsg" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( TERMEKTIPUS_FILE_VERSION ) +
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
void CS_TermekTipus::AddTermekTipus( typ_termektipus stTemp )
{
   double i;
   for( i=1; ; i++ )
   {
      typ_termektipus stTmp = GetTermekTipusId( i );
      if( stTmp.nID == 0 )
         break;
   }
   stTemp.nID = i;

   TermekTipus.push_back( stTemp );

   if( SaveDataToFile(sTermekTipusFile.c_str()) &&
       CheckDataToFile(sTermekTipusFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sTermekTipusFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termektípus biztonsági mentés 1 sikertelen #FV#CS_TermekTipus::AddTermekTipus" );
      }

      strFile = AnsiString( "Db\\2_" ) + sTermekTipusFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termektípus biztonsági mentés 2 sikertelen #FV#CS_TermekTipus::AddTermekTipus" );
      }
   }
   else
   {
      LOG1( "HIBA: termektípus mentés sikertelen #FV#CS_TermekTipus::AddTermekTipus" );
   }
}
//---------------------------------------------------------------------------
bool CS_TermekTipus::ModifyTermekTipus( typ_termektipus stTemp )
{
   double i;

   for(i=0;i<TermekTipus.size();i++)
   {
      if( TermekTipus[i].nID == stTemp.nID )
      {
         strcpy( TermekTipus[i].strNev, stTemp.strNev );
         break;
      }
   }

   if( SaveDataToFile(sTermekTipusFile.c_str()) &&
       CheckDataToFile(sTermekTipusFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sTermekTipusFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termektípus biztonsági mentés 1 sikertelen #FV#CS_TermekTipus::ModifyTermekTipus" );
      }

      strFile = AnsiString( "Db\\2_" ) + sTermekTipusFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termektípus biztonsági mentés 2 sikertelen #FV#CS_TermekTipus::ModifyTermekTipus" );
      }
   }
   else
   {
      LOG1( "HIBA: termektípus mentés sikertelen #FV#CS_TermekTipus::ModifyTermekTipus" );
   }

   if( i == TermekTipus.size() )
      return false;
   else
      return true;
}
//---------------------------------------------------------------------------
bool CS_TermekTipus::DeleteTermekTipus( DWORD nID )
{
   DWORD i;

   for(i=0;i<TermekTipus.size();i++)
   {
      if( TermekTipus[i].nID == nID )
      {
         TermekTipus.erase( TermekTipus.begin()+i );
         break;
      }
   }

   if( SaveDataToFile(sTermekTipusFile.c_str()) &&
       CheckDataToFile(sTermekTipusFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sTermekTipusFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termektípus biztonsági mentés 1 sikertelen #FV#CS_TermekTipus::DeleteTermekTipus" );
      }

      strFile = AnsiString( "Db\\2_" ) + sTermekTipusFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termektípus biztonsági mentés 2 sikertelen #FV#CS_TermekTipus::DeleteTermekTipus" );
      }
   }
   else
   {
      LOG1( "HIBA: termektípus mentés sikertelen #FV#CS_TermekTipus::DeleteTermekTipus" );
   }

   if( i == TermekTipus.size() )
      return false;
   else
      return true;
}
//---------------------------------------------------------------------------
typ_termektipus CS_TermekTipus::GetTermekTipusItem( double nCount )
{
   typ_termektipus  stTemp;

   memset( &stTemp, 0, sizeof(typ_termektipus) );

   if( nCount < TermekTipus.size() )
      return TermekTipus[nCount];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
typ_termektipus CS_TermekTipus::GetTermekTipusId( DWORD nID )
{
   typ_termektipus stTemp;
   double i;

   memset( &stTemp, 0, sizeof(typ_termektipus) );

   for(i=0;i<TermekTipus.size();i++)
   {
      if( TermekTipus[i].nID == nID )
      {
         break;
      }
   }

   if( i < TermekTipus.size() )
      return TermekTipus[i];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
DWORD CS_TermekTipus::GetTermekTipusNev( char *strNev )
{
   double i;

   for(i=0;i<TermekTipus.size();i++)
   {
      if( strcmp(TermekTipus[i].strNev, strNev) == 0 )
      {
         break;
      }
   }

   if( i < TermekTipus.size() )
      return TermekTipus[i].nID;
   else
      return 0;
}
//---------------------------------------------------------------------------
double CS_TermekTipus::GetTermekTipusCount()
{
   return TermekTipus.size();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void CS_TermekTipus::AddTermekTipusAsg( typ_termektipusassign stTemp )
{
   TermekTipusAsg.push_back( stTemp );

   if( SaveDataToFileAsg(sTermekTipusAsgFile.c_str()) &&
       CheckDataToFileAsg(sTermekTipusAsgFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sTermekTipusAsgFile;
      if( !SaveDataToFileAsg(strFile.c_str()) ||
          !CheckDataToFileAsg(strFile.c_str()) )
      {
         LOG1( "HIBA: termektípus asg biztonsági mentés 1 sikertelen #FV#CS_TermekTipus::AddTermekTipusAsg" );
      }

      strFile = AnsiString( "Db\\2_" ) + sTermekTipusAsgFile;
      if( !SaveDataToFileAsg(strFile.c_str()) ||
          !CheckDataToFileAsg(strFile.c_str()) )
      {
         LOG1( "HIBA: termektípus asg biztonsági mentés 2 sikertelen #FV#CS_TermekTipus::AddTermekTipusAsg" );
      }
   }
   else
   {
      LOG1( "HIBA: termektípus asg mentés sikertelen #FV#CS_TermekTipus::AddTermekTipusAsg" );
   }
}
//---------------------------------------------------------------------------
bool CS_TermekTipus::DeleteTermekTipusAsg( typ_termektipusassign stTemp )
{
   DWORD i;

   for(i=0;i<TermekTipusAsg.size();i++)
   {
      if( (TermekTipusAsg[i].nTermekID == stTemp.nTermekID && stTemp.nTTipusID == 0) ||
          (TermekTipusAsg[i].nTTipusID == stTemp.nTTipusID && stTemp.nTermekID == 0) )
      {
         TermekTipusAsg.erase( TermekTipusAsg.begin()+i );
      }
   }

   if( SaveDataToFileAsg(sTermekTipusAsgFile.c_str()) &&
       CheckDataToFileAsg(sTermekTipusAsgFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sTermekTipusAsgFile;
      if( !SaveDataToFileAsg(strFile.c_str()) ||
          !CheckDataToFileAsg(strFile.c_str()) )
      {
         LOG1( "HIBA: termektípus asg biztonsági mentés 1 sikertelen #FV#CS_TermekTipus::DeleteTermekTipusAsg" );
      }

      strFile = AnsiString( "Db\\2_" ) + sTermekTipusAsgFile;
      if( !SaveDataToFileAsg(strFile.c_str()) ||
          !CheckDataToFileAsg(strFile.c_str()) )
      {
         LOG1( "HIBA: termektípus asg biztonsági mentés 2 sikertelen #FV#CS_TermekTipus::DeleteTermekTipusAsg" );
      }
   }
   else
   {
      LOG1( "HIBA: termektípus asg mentés sikertelen #FV#CS_TermekTipus::DeleteTermekTipusAsg" );
   }

   if( i == TermekTipusAsg.size() )
      return false;
   else
      return true;
}
//---------------------------------------------------------------------------
typ_termektipusassign CS_TermekTipus::GetTermekTipusAsgItem( double nCount )
{
   typ_termektipusassign  stTemp;

   memset( &stTemp, 0, sizeof(typ_termektipusassign) );

   if( nCount < TermekTipusAsg.size() )
      return TermekTipusAsg[nCount];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
bool CS_TermekTipus::CheckTermekTipusAsg( typ_termektipusassign stTemp )
{
   double i;

   for(i=0;i<TermekTipusAsg.size();i++)
   {
      if( TermekTipusAsg[i].nTermekID == stTemp.nTermekID &&
          TermekTipusAsg[i].nTTipusID == stTemp.nTTipusID )
      {
         break;
      }
   }

   if( i < TermekTipusAsg.size() )
      return true;
   else
      return false;
}
//---------------------------------------------------------------------------
double CS_TermekTipus::GetTermekTipusAsgCount()
{
   return TermekTipusAsg.size();
}
//---------------------------------------------------------------------------

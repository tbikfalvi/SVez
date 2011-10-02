//---------------------------------------------------------------------------

#include <vcl.h>

#include "Classes.h"
#include "Database.h"

/****************************************************************************
*
* ÁLTALÁNOS FÜGGVÉNYEK
*
****************************************************************************/
//---------------------------------------------------------------------------
CS_Berlet::CS_Berlet()
{
   sBerletTipusFile = BERLETTIPUS_FILE;
   sBerletFile = BERLET_FILE;
   sBerletHasznalatFile = BERLETHASZNALAT_FILE;

   nDatabaseCode = 0;
   bIsDatabaseOk = LoadDataFromFile();
}
//---------------------------------------------------------------------------
CS_Berlet::~CS_Berlet()
{
   //
}
//---------------------------------------------------------------------------
bool CS_Berlet::LoadDataFromFile()
{
   FILE           *file = NULL;
   char           strTemp[10];
   unsigned int   nCount = 0;
   int            nErrorMsgID;

   //-------------------------------------------
   // Berlet tipusok beolvasasa
   //-------------------------------------------
   file = fopen( sBerletTipusFile.c_str(), "rb" );
   if( file != NULL )
   {
      memset( strTemp, 0, sizeof(strTemp) );
      fread( strTemp, 10, 1, file );
      if( strcmp( BERLETTIPUS_FILE_VERSION, strTemp ) == 0 )
      {
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount > 0 )
         {
            typ_berlettipus   stTemp;
            for( unsigned int i=0; i<nCount; i++ )
            {
               fread( &stTemp, sizeof(typ_berlettipus), 1, file );
               DeCode( stTemp.strNev, sizeof(stTemp.strNev) );
               BerletTipus.push_back( stTemp );
            }
            nDatabaseCode += 1;
         }
      }
      else
      {
         LOG1( "#FV#CS_Berlet::LoadDataFromFile - bérlettípus" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( BERLETTIPUS_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }
      fclose( file );
   }
   else
   {
      strLogMsg = AnsiString( "HIBA: Nem sikerült megnyitni: " ) + sBerletTipusFile;
      LOG1( strLogMsg );
   }

   //-------------------------------------------
   // Berletek beolvasasa
   //-------------------------------------------
   file = fopen( sBerletFile.c_str(), "rb" );
   if( file != NULL )
   {
      memset( strTemp, 0, sizeof(strTemp) );
      fread( strTemp, 10, 1, file );
      if( strcmp( BERLET_FILE_VERSION, strTemp ) == 0 )
      {
         nCount = 0;
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount > 0 )
         {
            typ_berlet   stTemp;
            for( unsigned int i=0; i<nCount; i++ )
            {
               fread( &stTemp, sizeof(typ_berlet), 1, file );
               DeCode( stTemp.strVonalkod, sizeof(stTemp.strVonalkod) );
               DeCode( stTemp.strMegjegyzes, sizeof(stTemp.strMegjegyzes) );
               Berlet.push_back( stTemp );
            }
            nDatabaseCode += 2;
         }
      }
      else
      {
         LOG1( "#FV#CS_Berlet::LoadDataFromFile - bérlet" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( BERLET_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }
      fclose( file );
   }
   else
   {
      strLogMsg = AnsiString( "HIBA: Nem sikerült megnyitni: " ) + sBerletFile;
      LOG1( strLogMsg );
   }

   //-------------------------------------------
   // Berlet hasznalatok beolvasasa
   //-------------------------------------------
   file = fopen( sBerletHasznalatFile.c_str(), "rb" );
   if( file != NULL )
   {
      memset( strTemp, 0, sizeof(strTemp) );
      fread( strTemp, 10, 1, file );
      if( strcmp( BERLETHASZNALAT_FILE_VERSION, strTemp ) == 0 )
      {
         nCount = 0;
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount > 0 )
         {
            typ_berlethasznalat   stTemp;
            for( unsigned int i=0; i<nCount; i++ )
            {
               fread( &stTemp, sizeof(typ_berlethasznalat), 1, file );
               DeCode( stTemp.strVonalkod, sizeof(stTemp.strVonalkod) );
               BerletHasznalat.push_back( stTemp );
            }
            nDatabaseCode += 4;
         }
      }
      else
      {
         LOG1( "#FV#CS_Berlet::LoadDataFromFile - bérlethasználat" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( BERLETHASZNALAT_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }
      fclose( file );
   }
   else
   {
      strLogMsg = AnsiString( "HIBA: Nem sikerült megnyitni: " ) + sBerletHasznalatFile;
      LOG1( strLogMsg );
   }

   if( nDatabaseCode == 7 )
      return true;
   else
      return false;
}
//---------------------------------------------------------------------------
bool CS_Berlet::SaveBerlettipus( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize, i;
   bool           bRet = true;

   file = fopen( strFile, "wb" );
   if( file != NULL )
   {
      fwrite( BERLETTIPUS_FILE_VERSION, 10, 1, file );

      nSize = BerletTipus.size();
      fwrite( &nSize, sizeof(unsigned int), 1, file );
      for( i=0; i<BerletTipus.size(); i++ )
      {
         EnCode( BerletTipus[i].strNev, sizeof(BerletTipus[i].strNev) );
         fwrite( &BerletTipus[i], sizeof(typ_berlettipus), 1, file );
         DeCode( BerletTipus[i].strNev, sizeof(BerletTipus[i].strNev) );
      }
      fclose( file );
   }
   else
   {
      strLogMsg = AnsiString( "HIBA: Nem sikerült létrehozni: " ) + strFile;
      LOG1( strLogMsg );
      bRet = false;
   }

   return bRet;
}
//---------------------------------------------------------------------------
bool CS_Berlet::CheckBerlettipus( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize, i;
   bool           bRet = true;

   file = fopen( strFile, "rb" );
   if( file != NULL )
   {
      char strTemp[10];
      memset( strTemp, 0, sizeof(strTemp) );
      fread( strTemp, 10, 1, file );
      if( strcmp( BERLETTIPUS_FILE_VERSION, strTemp ) == 0 )
      {
         unsigned int   nCount = 0;
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount != BerletTipus.size() )
         {
            LOG1( "#FV#CS_Berlet::CheckBerlettipus - 1" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordszám: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( BerletTipus.size() ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( nCount > 0 && bRet )
         {
            typ_berlettipus   stTemp;
            for( i=0; i<nCount; i++ )
            {
               fread( &stTemp, sizeof(typ_berlettipus), 1, file );
               DeCode( stTemp.strNev, sizeof(stTemp.strNev) );
               if( memcmp( &BerletTipus[i], &stTemp, sizeof(typ_berlettipus) ) != 0 )
               {
                  LOG1( "#FV#CS_Berlet::CheckBerlettipus - 2" );
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
         LOG1( "#FV#CS_Berlet::CheckBerlettipus - 3" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( BERLETTIPUS_FILE_VERSION ) +
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
      strLogMsg = AnsiString( "HIBA: Nem sikerült ellenõrizni a mentést: " ) + strFile;
      LOG1( strLogMsg );
      bRet = false;
   }

   return bRet;
}
//---------------------------------------------------------------------------
bool CS_Berlet::SaveBerlet( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize,i;
   bool           bRet = true;

   file = fopen( strFile, "wb" );
   if( file != NULL )
   {
      fwrite( BERLET_FILE_VERSION, 10, 1, file );

      nSize = Berlet.size();
      fwrite( &nSize, sizeof(unsigned int), 1, file );
      for( i=0; i<Berlet.size(); i++ )
      {
         EnCode( Berlet[i].strVonalkod, sizeof(Berlet[i].strVonalkod) );
         EnCode( Berlet[i].strMegjegyzes, sizeof(Berlet[i].strMegjegyzes) );
         fwrite( &Berlet[i], sizeof(typ_berlet), 1, file );
         DeCode( Berlet[i].strVonalkod, sizeof(Berlet[i].strVonalkod) );
         DeCode( Berlet[i].strMegjegyzes, sizeof(Berlet[i].strMegjegyzes) );
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
bool CS_Berlet::CheckBerlet( const char *strFile )
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
      if( strcmp( BERLET_FILE_VERSION, strTemp ) == 0 )
      {
         // verziószám egyezik
         //
         unsigned int   nCount = 0;
         // rekordok számának kiolvasása
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount != Berlet.size() )
         {
            // rekordok száma nem egyezik
            //
            LOG1( "#FV#CS_Berlet::CheckBerlet - 1" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordszám: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( Berlet.size() ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( nCount > 0 && bRet )
         {
            // rekordok száma egyezik és van adat
            //
            typ_berlet   stTemp;
            for( i=0; i<nCount; i++ )
            {
               // rekord beolvasása
               fread( &stTemp, sizeof(typ_berlet), 1, file );
               // szöveg dekódolása
               DeCode( stTemp.strVonalkod, sizeof(stTemp.strVonalkod) );
               DeCode( stTemp.strMegjegyzes, sizeof(stTemp.strMegjegyzes) );
               // rekord ellenõrzése
               if( memcmp( &Berlet[i], &stTemp, sizeof(typ_berlet) ) != 0 )
               {
                  // rekord nem egyezik
                  //
                  LOG1( "#FV#CS_Berlet::CheckBerlet - 2" );
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
         LOG1( "#FV#CS_Berlet::CheckBerlet - 3" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( BERLET_FILE_VERSION ) +
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
bool CS_Berlet::SaveBerlethasznalat( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize,i;
   bool           bRet = true;

   file = fopen( strFile, "wb" );
   if( file != NULL )
   {
      fwrite( BERLETHASZNALAT_FILE_VERSION, 10, 1, file );

      nSize = BerletHasznalat.size();
      fwrite( &nSize, sizeof(unsigned int), 1, file );
      for( i=0; i<BerletHasznalat.size(); i++ )
      {
         EnCode( BerletHasznalat[i].strVonalkod, sizeof(BerletHasznalat[i].strVonalkod) );
         fwrite( &BerletHasznalat[i], sizeof(typ_berlethasznalat), 1, file );
         DeCode( BerletHasznalat[i].strVonalkod, sizeof(BerletHasznalat[i].strVonalkod) );
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
bool CS_Berlet::CheckBerlethasznalat( const char *strFile )
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
      if( strcmp( BERLETHASZNALAT_FILE_VERSION, strTemp ) == 0 )
      {
         // verziószám egyezik
         //
         unsigned int   nCount = 0;
         // rekordok számának kiolvasása
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount != BerletHasznalat.size() )
         {
            // rekordok száma nem egyezik
            //
            LOG1( "#FV#CS_Berlet::CheckBerlethasznalat" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordszám: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( BerletHasznalat.size() ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( nCount > 0 && bRet )
         {
            // rekordok száma egyezik és van adat
            //
            typ_berlethasznalat   stTemp;
            for( i=0; i<nCount; i++ )
            {
               // rekord beolvasása
               fread( &stTemp, sizeof(typ_berlethasznalat), 1, file );
               // szöveg dekódolása
               DeCode( stTemp.strVonalkod, sizeof(stTemp.strVonalkod) );
               // rekord ellenõrzése
               if( memcmp( &BerletHasznalat[i], &stTemp, sizeof(typ_berlethasznalat) ) != 0 )
               {
                  // rekord nem egyezik
                  //
                  LOG1( "#FV#CS_Berlet::CheckBerlethasznalat" );
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
         LOG1( "#FV#CS_Berlet::CheckBerlethasznalat" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( BERLETHASZNALAT_FILE_VERSION ) +
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
/****************************************************************************
*
* BÉRLET TÍPUSOK KEZELESE
*
****************************************************************************/
//---------------------------------------------------------------------------
int CS_Berlet::GetBerletTipusCount()
{
   return (int)BerletTipus.size();
}
//---------------------------------------------------------------------------
void CS_Berlet::AddBerletTipus( typ_berlettipus stTemp )
{
   double i;
   for( i=1; ; i++ )
   {
      typ_berlettipus stTmp = GetBerletTipusID( i );
      if( stTmp.nID == 0 )
         break;
   }
   stTemp.nID = i;

   BerletTipus.push_back( stTemp );

   if( SaveBerlettipus(sBerletTipusFile.c_str()) &&
       CheckBerlettipus(sBerletTipusFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sBerletTipusFile;
      if( !SaveBerlettipus(strFile.c_str()) ||
          !CheckBerlettipus(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlettípus biztonsági mentés 1 sikertelen #FV#CS_Berlet::AddBerletTipus" );
      }

      strFile = AnsiString( "Db\\2_" ) + sBerletTipusFile;
      if( !SaveBerlettipus(strFile.c_str()) ||
          !CheckBerlettipus(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlettípus biztonsági mentés 2 sikertelen #FV#CS_Berlet::AddBerletTipus" );
      }
   }
   else
   {
      LOG1( "HIBA: bérlettípus mentés sikertelen #FV#CS_Berlet::AddBerletTipus" );
   }
}
//---------------------------------------------------------------------------
void CS_Berlet::ModifyBerletTipus( typ_berlettipus stTemp )
{
   for(int i=0;i<(int)BerletTipus.size();i++)
   {
      if( BerletTipus[i].nID == stTemp.nID )
      {
         strcpy( BerletTipus[i].strNev, stTemp.strNev );
         BerletTipus[i].nAr = stTemp.nAr;
         BerletTipus[i].nEgyseg = stTemp.nEgyseg;
         BerletTipus[i].nErvTolEv = stTemp.nErvTolEv;
         BerletTipus[i].nErvTolHo = stTemp.nErvTolHo;
         BerletTipus[i].nErvTolNap = stTemp.nErvTolNap;
         BerletTipus[i].nErvIgEv = stTemp.nErvIgEv;
         BerletTipus[i].nErvIgHo = stTemp.nErvIgHo;
         BerletTipus[i].nErvIgNap = stTemp.nErvIgNap;
         BerletTipus[i].nErvNapok = stTemp.nErvNapok;
         BerletTipus[i].nEgysegIdo = stTemp.nEgysegIdo;
         break;
      }
   }

   if( SaveBerlettipus(sBerletTipusFile.c_str()) &&
       CheckBerlettipus(sBerletTipusFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sBerletTipusFile;
      if( !SaveBerlettipus(strFile.c_str()) ||
          !CheckBerlettipus(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlettípus biztonsági mentés 1 sikertelen #FV#CS_Berlet::ModifyBerletTipus" );
      }

      strFile = AnsiString( "Db\\2_" ) + sBerletTipusFile;
      if( !SaveBerlettipus(strFile.c_str()) ||
          !CheckBerlettipus(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlettípus biztonsági mentés 2 sikertelen #FV#CS_Berlet::ModifyBerletTipus" );
      }
   }
   else
   {
      LOG1( "HIBA: bérlettípus mentés sikertelen #FV#CS_Berlet::ModifyBerletTipus" );
   }
}
//---------------------------------------------------------------------------
bool CS_Berlet::DeleteBerletTipus( int nID )
{
   int   i;

   for(i=0;i<(int)BerletTipus.size();i++)
   {
      if( BerletTipus[i].nID == nID )
      {
         BerletTipus.erase( BerletTipus.begin()+i );
         break;
      }
   }

   if( SaveBerlettipus(sBerletTipusFile.c_str()) &&
       CheckBerlettipus(sBerletTipusFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sBerletTipusFile;
      if( !SaveBerlettipus(strFile.c_str()) ||
          !CheckBerlettipus(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlettípus biztonsági mentés 1 sikertelen #FV#CS_Berlet::DeleteBerletTipus" );
      }

      strFile = AnsiString( "Db\\2_" ) + sBerletTipusFile;
      if( !SaveBerlettipus(strFile.c_str()) ||
          !CheckBerlettipus(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlettípus biztonsági mentés 2 sikertelen #FV#CS_Berlet::DeleteBerletTipus" );
      }
   }
   else
   {
      LOG1( "HIBA: bérlettípus mentés sikertelen #FV#CS_Berlet::DeleteBerletTipus" );
   }

   return true;
}
//---------------------------------------------------------------------------
typ_berlettipus CS_Berlet::GetBerletTipus( char *strNev )
{
   int i;
   typ_berlettipus   stTemp;

   memset(&stTemp, 0, sizeof(typ_berlettipus) );

   for(i=0;i<(int)BerletTipus.size();i++)
   {
      if( strcmp(BerletTipus[i].strNev, strNev) == 0 )
         break;
   }

   if( i < (int)BerletTipus.size() )
      return BerletTipus[i];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
typ_berlettipus CS_Berlet::GetBerletTipus( int nCount )
{
   typ_berlettipus   stTemp;

   memset(&stTemp, 0, sizeof(typ_berlettipus) );

   if( nCount < (int)BerletTipus.size() )
      return BerletTipus[nCount];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
typ_berlettipus CS_Berlet::GetBerletTipusID( int nID )
{
   int i;
   typ_berlettipus   stTemp;

   memset(&stTemp, 0, sizeof(typ_berlettipus) );

   for(i=0;i<(int)BerletTipus.size();i++)
   {
      if( BerletTipus[i].nID == nID )
         break;
   }

   if( i < (int)BerletTipus.size() )
      return BerletTipus[i];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
int CS_Berlet::GetIDBerletTipusAr( int nAr )
{
   int i;

   for(i=0;i<(int)BerletTipus.size();i++)
   {
      if( BerletTipus[i].nAr == nAr )
         break;
   }

   if( i < (int)BerletTipus.size() )
      return BerletTipus[i].nID;
   else
      return 0;
}
/****************************************************************************
*
* BÉRLETEK KEZELESE
*
****************************************************************************/
//---------------------------------------------------------------------------
void CS_Berlet::AddBerlet( typ_berlet stTemp )
{
   Berlet.push_back( stTemp );

   if( SaveBerlet(sBerletFile.c_str()) &&
       CheckBerlet(sBerletFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sBerletFile;
      if( !SaveBerlet(strFile.c_str()) ||
          !CheckBerlet(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlet biztonsági mentés 1 sikertelen #FV#CS_Berlet::AddBerlet" );
      }

      strFile = AnsiString( "Db\\2_" ) + sBerletFile;
      if( !SaveBerlet(strFile.c_str()) ||
          !CheckBerlet(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlet biztonsági mentés 2 sikertelen #FV#CS_Berlet::AddBerlet" );
      }
   }
   else
   {
      LOG1( "HIBA: bérlet mentés sikertelen #FV#CS_Berlet::AddBerlet" );
   }
}
//---------------------------------------------------------------------------
bool CS_Berlet::DeleteBerlet( char *strVonalkod, bool bNeedToSave )
{
   DWORD i;

   for(i=0;i<Berlet.size();i++)
   {
      if( strcmp(Berlet[i].strVonalkod, strVonalkod) == 0 )
      {
         Berlet.erase( Berlet.begin()+i );
         break;
      }
   }

   if( bNeedToSave )
   {
      if( SaveBerlet(sBerletFile.c_str()) &&
          CheckBerlet(sBerletFile.c_str()) )
      {
         AnsiString strFile;

         strFile = AnsiString( "Db\\1_" ) + sBerletFile;
         if( !SaveBerlet(strFile.c_str()) ||
             !CheckBerlet(strFile.c_str()) )
         {
            LOG1( "HIBA: bérlet biztonsági mentés 1 sikertelen #FV#CS_Berlet::DeleteBerlet" );
         }

         strFile = AnsiString( "Db\\2_" ) + sBerletFile;
         if( !SaveBerlet(strFile.c_str()) ||
             !CheckBerlet(strFile.c_str()) )
         {
            LOG1( "HIBA: bérlet biztonsági mentés 2 sikertelen #FV#CS_Berlet::DeleteBerlet" );
         }
      }
      else
      {
         LOG1( "HIBA: bérlet mentés sikertelen #FV#CS_Berlet::DeleteBerlet" );
      }
   }

   if( i == Berlet.size() )
      return false;
   else
      return true;
}
//---------------------------------------------------------------------------
bool CS_Berlet::IsBerletExists( char *strVonalkod )
{
   DWORD i;

   for(i=0;i<Berlet.size();i++)
   {
      if( strcmp( Berlet[i].strVonalkod, strVonalkod ) == 0 )
         break;
   }

   if( i < Berlet.size() )
      return true;
   else
      return false;
}
//---------------------------------------------------------------------------
typ_berlet CS_Berlet::GetBerlet( char *strVonalkod )
{
   DWORD i;
   typ_berlet  stTemp;

   memset( &stTemp, 0, sizeof(typ_berlet) );

   for(i=0;i<Berlet.size();i++)
   {
      if( strcmpi( Berlet[i].strVonalkod, strVonalkod ) == 0 )
         break;
   }

   if( i < Berlet.size() )
      return Berlet[i];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
typ_berlet CS_Berlet::GetBerletItem( DWORD dwCount )
{
   typ_berlet  stTemp;

   memset( &stTemp, 0, sizeof(typ_berlet) );

   if( dwCount < Berlet.size() )
      return Berlet[dwCount];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
DWORD CS_Berlet::GetBerletCount()
{
   return Berlet.size();
}
//---------------------------------------------------------------------------
void CS_Berlet::SetBerletEgyseg( char *strVonalkod, int nEgyseg )
{
   for(DWORD i=0;i<Berlet.size();i++)
   {
      if( strcmp( Berlet[i].strVonalkod, strVonalkod ) == 0 )
      {
         Berlet[i].nEgyseg = nEgyseg;
         break;
      }
   }

   if( SaveBerlet(sBerletFile.c_str()) &&
       CheckBerlet(sBerletFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sBerletFile;
      if( !SaveBerlet(strFile.c_str()) ||
          !CheckBerlet(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlet biztonsági mentés 1 sikertelen #FV#CS_Berlet::SetBerletEgyseg" );
      }

      strFile = AnsiString( "Db\\2_" ) + sBerletFile;
      if( !SaveBerlet(strFile.c_str()) ||
          !CheckBerlet(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlet biztonsági mentés 2 sikertelen #FV#CS_Berlet::SetBerletEgyseg" );
      }
   }
   else
   {
      LOG1( "HIBA: bérlet mentés sikertelen #FV#CS_Berlet::SetBerletEgyseg" );
   }
}
//---------------------------------------------------------------------------
int CS_Berlet::GetBerletEgyseg( char *strVonalkod )
{
   int nRet = -1;

   for(DWORD i=0;i<Berlet.size();i++)
   {
      if( strcmp( Berlet[i].strVonalkod, strVonalkod ) == 0 )
      {
         nRet = Berlet[i].nEgyseg;
         break;
      }
   }
   return nRet;
}
//---------------------------------------------------------------------------
void CS_Berlet::DecreaseBerletEgyseg( char *strVonalkod, int nEgyseg )
{
   for(DWORD i=0;i<Berlet.size();i++)
   {
      if( strcmp( Berlet[i].strVonalkod, strVonalkod ) == 0 )
      {
         Berlet[i].nEgyseg -= nEgyseg;
         AddBerletHasznalat( strVonalkod, nEgyseg );
         break;
      }
   }

   if( SaveBerlet(sBerletFile.c_str()) &&
       CheckBerlet(sBerletFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sBerletFile;
      if( !SaveBerlet(strFile.c_str()) ||
          !CheckBerlet(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlet biztonsági mentés 1 sikertelen #FV#CS_Berlet::DecreaseBerletEgyseg" );
      }

      strFile = AnsiString( "Db\\2_" ) + sBerletFile;
      if( !SaveBerlet(strFile.c_str()) ||
          !CheckBerlet(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlet biztonsági mentés 2 sikertelen #FV#CS_Berlet::DecreaseBerletEgyseg" );
      }
   }
   else
   {
      LOG1( "HIBA: bérlet mentés sikertelen #FV#CS_Berlet::DecreaseBerletEgyseg" );
   }
}
//---------------------------------------------------------------------------
void CS_Berlet::IncreaseBerletEgyseg( char *strVonalkod, int nEgyseg )
{
   for(DWORD i=0;i<Berlet.size();i++)
   {
      if( strcmp( Berlet[i].strVonalkod, strVonalkod ) == 0 )
      {
         Berlet[i].nEgyseg += nEgyseg;
         AddBerletHasznalat( strVonalkod, (nEgyseg*(-1)) );
         break;
      }
   }

   if( SaveBerlet(sBerletFile.c_str()) &&
       CheckBerlet(sBerletFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sBerletFile;
      if( !SaveBerlet(strFile.c_str()) ||
          !CheckBerlet(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlet biztonsági mentés 1 sikertelen #FV#CS_Berlet::IncreaseBerletEgyseg" );
      }

      strFile = AnsiString( "Db\\2_" ) + sBerletFile;
      if( !SaveBerlet(strFile.c_str()) ||
          !CheckBerlet(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlet biztonsági mentés 2 sikertelen #FV#CS_Berlet::IncreaseBerletEgyseg" );
      }
   }
   else
   {
      LOG1( "HIBA: bérlet mentés sikertelen #FV#CS_Berlet::IncreaseBerletEgyseg" );
   }
}
//---------------------------------------------------------------------------
void CS_Berlet::SetPIN( char *strVonalkod, int nPin )
{
   for(DWORD i=0;i<Berlet.size();i++)
   {
      if( strcmp( Berlet[i].strVonalkod, strVonalkod ) == 0 )
      {
         Berlet[i].nPin = nPin;
         break;
      }
   }

   if( SaveBerlet(sBerletFile.c_str()) &&
       CheckBerlet(sBerletFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sBerletFile;
      if( !SaveBerlet(strFile.c_str()) ||
          !CheckBerlet(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlet biztonsági mentés 1 sikertelen #FV#CS_Berlet::SetPIN" );
      }

      strFile = AnsiString( "Db\\2_" ) + sBerletFile;
      if( !SaveBerlet(strFile.c_str()) ||
          !CheckBerlet(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlet biztonsági mentés 2 sikertelen #FV#CS_Berlet::SetPIN" );
      }
   }
   else
   {
      LOG1( "HIBA: bérlet mentés sikertelen #FV#CS_Berlet::SetPIN" );
   }
}
/****************************************************************************
*
* BÉRLET HASZNÁLAT KEZELESE
*
****************************************************************************/
//---------------------------------------------------------------------------
void CS_Berlet::AddBerletHasznalat( char *strVonalkod, int nEgyseg )
{
   typ_berlethasznalat  stTemp;
   unsigned short       nYear, nMonth, nDay;
   unsigned short       nHour, nMin, nSec, nMsec;

   Now().DecodeDate( &nYear, &nMonth, &nDay );
   Now().DecodeTime( &nHour, &nMin, &nSec, &nMsec );

   memset( &stTemp, 0, sizeof(typ_berlethasznalat) );

   strcpy( stTemp.strVonalkod, strVonalkod );
   stTemp.nEv     = nYear;
   stTemp.nHo     = nMonth;
   stTemp.nNap    = nDay;
   stTemp.nOra    = nHour;
   stTemp.nPerc   = nMin;
   stTemp.nEgyseg = nEgyseg;

   BerletHasznalat.push_back( stTemp );

   if( SaveBerlethasznalat(sBerletHasznalatFile.c_str()) &&
       CheckBerlethasznalat(sBerletHasznalatFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sBerletHasznalatFile;
      if( !SaveBerlethasznalat(strFile.c_str()) ||
          !CheckBerlethasznalat(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlethasznalat biztonsági mentés 1 sikertelen #FV#CS_Berlet::AddBerletHasznalat" );
      }

      strFile = AnsiString( "Db\\2_" ) + sBerletHasznalatFile;
      if( !SaveBerlethasznalat(strFile.c_str()) ||
          !CheckBerlethasznalat(strFile.c_str()) )
      {
         LOG1( "HIBA: bérlethasznalat biztonsági mentés 2 sikertelen #FV#CS_Berlet::AddBerletHasznalat" );
      }
   }
   else
   {
      LOG1( "HIBA: bérlethasznalat mentés sikertelen #FV#CS_Berlet::AddBerletHasznalat" );
   }
}
//---------------------------------------------------------------------------
bool CS_Berlet::DeleteBerletHasznalat( typ_berlethasznalat stTemp, bool bNeedToSave )
{
   DWORD i;

   for(i=0;i<BerletHasznalat.size();i++)
   {
      if( strcmp(BerletHasznalat[i].strVonalkod, stTemp.strVonalkod) == 0 &&
          BerletHasznalat[i].nEv == stTemp.nEv &&
          BerletHasznalat[i].nHo == stTemp.nHo &&
          BerletHasznalat[i].nNap == stTemp.nNap &&
          BerletHasznalat[i].nOra == stTemp.nOra &&
          BerletHasznalat[i].nPerc == stTemp.nPerc )
      {
         if( bNeedToSave )
            IncreaseBerletEgyseg( BerletHasznalat[i].strVonalkod, BerletHasznalat[i].nEgyseg );
         BerletHasznalat.erase( BerletHasznalat.begin()+i );
         break;
      }
   }

   if( bNeedToSave )
   {
      if( SaveBerlethasznalat(sBerletHasznalatFile.c_str()) &&
          CheckBerlethasznalat(sBerletHasznalatFile.c_str()) )
      {
         AnsiString strFile;

         strFile = AnsiString( "Db\\1_" ) + sBerletHasznalatFile;
         if( !SaveBerlethasznalat(strFile.c_str()) ||
             !CheckBerlethasznalat(strFile.c_str()) )
         {
            LOG1( "HIBA: bérlethasznalat biztonsági mentés 1 sikertelen #FV#CS_Berlet::DeleteBerletHasznalat" );
         }

         strFile = AnsiString( "Db\\2_" ) + sBerletHasznalatFile;
         if( !SaveBerlethasznalat(strFile.c_str()) ||
             !CheckBerlethasznalat(strFile.c_str()) )
         {
            LOG1( "HIBA: bérlethasznalat biztonsági mentés 2 sikertelen #FV#CS_Berlet::DeleteBerletHasznalat" );
         }
      }
      else
      {
         LOG1( "HIBA: bérlethasznalat mentés sikertelen #FV#CS_Berlet::DeleteBerletHasznalat" );
      }
   }

   if( i == BerletHasznalat.size() )
      return false;
   else
      return true;
}
//---------------------------------------------------------------------------
typ_berlethasznalat CS_Berlet::GetBerletHasznalat( double dDate, char *strVonalkod )
{
   typ_berlethasznalat  stTemp;
   TDateTime            sDate = dDate;
   unsigned short       nYear, nMonth, nDay;
   unsigned short       nHour, nMin, nSec, nMsec;
   DWORD                i;

   sDate.DecodeDate( &nYear, &nMonth, &nDay );
   sDate.DecodeTime( &nHour, &nMin, &nSec, &nMsec );

   memset( &stTemp, 0, sizeof(typ_berlethasznalat) );

   for(i=0;i<BerletHasznalat.size();i++)
   {
      if( strcmp(BerletHasznalat[i].strVonalkod, strVonalkod) == 0 &&
          BerletHasznalat[i].nEv == nYear &&
          BerletHasznalat[i].nHo == nMonth &&
          BerletHasznalat[i].nNap == nDay &&
          BerletHasznalat[i].nOra == nHour &&
          BerletHasznalat[i].nPerc == nMin )
      {
         break;
      }
   }

   if( i < BerletHasznalat.size() )
      return BerletHasznalat[i];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
typ_berlethasznalat CS_Berlet::GetBerletHasznalatItem( DWORD dwCount )
{
   typ_berlethasznalat  stTemp;

   memset( &stTemp, 0, sizeof(typ_berlethasznalat) );

   if( dwCount < BerletHasznalat.size() )
      return BerletHasznalat[dwCount];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
DWORD CS_Berlet::GetBerletHasznalatCount()
{
   return BerletHasznalat.size();
}
//---------------------------------------------------------------------------

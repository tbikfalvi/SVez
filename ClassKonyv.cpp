//---------------------------------------------------------------------------

#include <vcl.h>

#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
// Osztály példány létrehozásakor alap adatok inicializálása
// osztály specifikus "adatbázis" betöltése
//---------------------------------------------------------------------------
CS_Konyv::CS_Konyv()
{
   sKonyvGeneralFile = KONYVGENERAL_FILE;
   sKonyvSzolariumFile = KONYVSZOLARIUM_FILE;

   LoadDataFromFile();
}
//---------------------------------------------------------------------------
// Osztály példány megszûnésekor az osztály specifikus "adatbázis" mentése
//---------------------------------------------------------------------------
CS_Konyv::~CS_Konyv()
{
   //SaveDataToFile();
}
//---------------------------------------------------------------------------
// "Adatbázis" betöltése
//---------------------------------------------------------------------------
void CS_Konyv::LoadDataFromFile()
{
   FILE           *file = NULL;
   char           strTemp[10];
   unsigned int   nCount = 0;
   int            nErrorMsgID;

   memset( strTemp, 0, sizeof(strTemp) );

/*   if( !CheckAndCorrectDBFiles( sKonyvGeneralFile.c_str(), &nErrorMsgID ) )
   {
      AnsiString  strMsg;
      strMsg.sprintf( "\n\nError Code: sys104\nError ID: %d", nErrorMsgID );
      throw Exception( strMsg );
   }*/

   // Általános könyvelést tartalmazó file megnyitása
   file = fopen( sKonyvGeneralFile.c_str(), "rb" );
   if( file != NULL )
   {
      // File verzió kiolvasása
      fread( strTemp, 10, 1, file );
      // File verzió ellenõrzése
      if( strcmp( KONYV_GENERAL_FILE_VERSION, strTemp ) == 0 )
      {
         // File verzió megegyezik a programban tárolt verzióval
         // Adat rekordok számának kiolvasása
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount > 0 )
         {
            // Adat rekordok kiolvasása, dekódolása, felvétele az "adatbázisba"
            typ_konyv_general   stTemp;
            for( unsigned int i=0; i<nCount; i++ )
            {
               fread( &stTemp, sizeof(typ_konyv_general), 1, file );
               DeCode( stTemp.strMegjegyzes, sizeof(stTemp.strMegjegyzes) );
               KonyvGeneral.push_back( stTemp );
            }
         }
      }
      else
      {
         LOG1( "#FV#CS_Konyv::LoadDataFromFile - general könyv" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( KONYV_GENERAL_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }
      fclose( file );
   }

   memset( strTemp, 0, sizeof(strTemp) );

/*   if( !CheckAndCorrectDBFiles( sKonyvSzolariumFile.c_str(), &nErrorMsgID ) )
   {
      AnsiString  strMsg;
      strMsg.sprintf( "\n\nError Code: sys105\nError ID: %d", nErrorMsgID );
      throw Exception( strMsg );
   }*/

   // Szolárium specifikus könyvelést tartalmazó file megnyitása
   file = fopen( sKonyvSzolariumFile.c_str(), "rb" );
   if( file != NULL )
   {
      // File verzió kiolvasása
      fread( strTemp, 10, 1, file );
      // File verzió ellenõrzése
      if( strcmp( KONYV_SZOLARIUM_FILE_VERSION, strTemp ) == 0 )
      {
         // File verzió megegyezik a programban tárolt verzióval
         // Adat rekordok számának kiolvasása
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount > 0 )
         {
            // Adat rekordok kiolvasása, dekódolása, felvétele az "adatbázisba"
            typ_konyv_szolarium   stTemp;
            for( unsigned int i=0; i<nCount; i++ )
            {
               fread( &stTemp, sizeof(typ_konyv_szolarium), 1, file );
               DeCode( stTemp.strSzolarium, sizeof(stTemp.strSzolarium) );
               KonyvSzolarium.push_back( stTemp );
            }
         }
      }
      else
      {
         LOG1( "#FV#CS_Konyv::LoadDataFromFile - szolárium könyv" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( KONYV_GENERAL_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }
      fclose( file );
   }
}
//---------------------------------------------------------------------------
// "Adatbázis" mentése
//---------------------------------------------------------------------------
/*void CS_Konyv::SaveDataToFile()
{
   SaveGeneralKonyv( sKonyvGeneralFile.c_str() );
   SaveSolariumKonyv( sKonyvSzolariumFile.c_str() );
}*/
//---------------------------------------------------------------------------
bool CS_Konyv::SaveGeneralKonyv( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize;
   bool           bRet = true;

   // Általános könyvelést tartalmazó file megnyitása (felülírása)
   if( (file = fopen( strFile, "wb" )) != NULL )
   {
      // File verzió kiírása
      fwrite( KONYV_GENERAL_FILE_VERSION, 10, 1, file );

      // Adat rekordok számának kiírása
      nSize = KonyvGeneral.size();
      fwrite( &nSize, sizeof(unsigned int), 1, file );
      // Adat rekordok kódolása, kiírása (és dekódolása a további használat miatt)
      for( unsigned int i=0; i<KonyvGeneral.size(); i++ )
      {
         EnCode( KonyvGeneral[i].strMegjegyzes, sizeof(KonyvGeneral[i].strMegjegyzes) );
         fwrite( &KonyvGeneral[i], sizeof(typ_konyv_general), 1, file );
         DeCode( KonyvGeneral[i].strMegjegyzes, sizeof(KonyvGeneral[i].strMegjegyzes) );
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
bool CS_Konyv::CheckGeneralKonyv( const char *strFile )
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
      if( strcmp( KONYV_GENERAL_FILE_VERSION, strTemp ) == 0 )
      {
         unsigned int   nCount = 0;
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount != KonyvGeneral.size() )
         {
            LOG1( "#FV#CS_Konyv::CheckGeneralKonyv" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordszám: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( KonyvGeneral.size() ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( nCount > 0 && bRet )
         {
            typ_konyv_general   stTemp;
            for( i=0; i<nCount; i++ )
            {
               fread( &stTemp, sizeof(typ_konyv_general), 1, file );
               DeCode( stTemp.strMegjegyzes, sizeof(stTemp.strMegjegyzes) );
               if( memcmp( &KonyvGeneral[i], &stTemp, sizeof(typ_konyv_general) ) != 0 )
               {
                  LOG1( "#FV#CS_Konyv::CheckGeneralKonyv" );
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
         LOG1( "#FV#CS_Konyv::CheckGeneralKonyv" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( KONYV_GENERAL_FILE_VERSION ) +
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
bool CS_Konyv::SaveSolariumKonyv( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize;
   bool           bRet = true;

   // Szolárium specifikus könyvelést tartalmazó file megnyitása (felülírása)
   if( (file = fopen( strFile, "wb" )) != NULL )
   {
      // File verzió kiírása
      fwrite( KONYV_SZOLARIUM_FILE_VERSION, 10, 1, file );

      // Adat rekordok számának kiírása
      nSize = KonyvSzolarium.size();
      fwrite( &nSize, sizeof(unsigned int), 1, file );
      // Adat rekordok kódolása, kiírása (és dekódolása a további használat miatt)
      for( unsigned int i=0; i<KonyvSzolarium.size(); i++ )
      {
         EnCode( KonyvSzolarium[i].strSzolarium, sizeof(KonyvSzolarium[i].strSzolarium) );
         fwrite( &KonyvSzolarium[i], sizeof(typ_konyv_szolarium), 1, file );
         DeCode( KonyvSzolarium[i].strSzolarium, sizeof(KonyvSzolarium[i].strSzolarium) );
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
bool CS_Konyv::CheckSolariumKonyv( const char *strFile )
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
      if( strcmp( KONYV_SZOLARIUM_FILE_VERSION, strTemp ) == 0 )
      {
         // verziószám egyezik
         //
         unsigned int   nCount = 0;
         // rekordok számának kiolvasása
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount != KonyvSzolarium.size() )
         {
            // rekordok száma nem egyezik
            //
            LOG1( "#FV#CS_Konyv::CheckSolariumKonyv" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordszám: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( KonyvSzolarium.size() ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( nCount > 0 && bRet )
         {
            // rekordok száma egyezik és van adat
            //
            typ_konyv_szolarium   stTemp;
            for( i=0; i<nCount; i++ )
            {
               // rekord beolvasása
               fread( &stTemp, sizeof(typ_konyv_szolarium), 1, file );
               // szöveg dekódolása
               DeCode( stTemp.strSzolarium, sizeof(stTemp.strSzolarium) );
               // rekord ellenõrzése
               if( memcmp( &KonyvSzolarium[i], &stTemp, sizeof(typ_konyv_szolarium) ) != 0 )
               {
                  // rekord nem egyezik
                  //
                  LOG1( "#FV#CS_Konyv::CheckSolariumKonyv" );
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
         LOG1( "#FV#CS_Konyv::CheckSolariumKonyv" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( KONYV_SZOLARIUM_FILE_VERSION ) +
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
// Könyvelési rekordok számának visszaadása
//---------------------------------------------------------------------------
double CS_Konyv::GetGeneralKonyvCount()
{
   return KonyvGeneral.size();
}
//---------------------------------------------------------------------------
// Könyv rekord kikeresése az adatbázisban elfoglalt hely alapján
//---------------------------------------------------------------------------
typ_konyv_general CS_Konyv::GetGeneralKonyv( double dCount )
{
   typ_konyv_general stGKonyv;

   memset( &stGKonyv, 0, sizeof(typ_konyv_general) );

   if( dCount < KonyvGeneral.size() )
      return KonyvGeneral[dCount];
   else
      return stGKonyv;
}
//---------------------------------------------------------------------------
// Könyv rekord kikeresése ID alapján
//---------------------------------------------------------------------------
typ_konyv_general CS_Konyv::GetGeneralKonyvID( double dID )
{
   typ_konyv_general stGKonyv;
   double            i;

   memset( &stGKonyv, 0, sizeof(typ_konyv_general) );

   for( i=0; i<KonyvGeneral.size(); i++ )
   {
      if( KonyvGeneral[i].dID == dID )
         break;
   }

   if( i < KonyvGeneral.size() )
      return KonyvGeneral[i];
   else
      return stGKonyv;
}
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CS_Konyv::DeleteGeneralKonyv( double dID, bool bNeedToSave )
{
   for( unsigned int i=0; i<KonyvGeneral.size(); i++ )
   {
      if( KonyvGeneral[i].dID == dID )
      {
         KonyvGeneral.erase( KonyvGeneral.begin()+i );
         break;
      }
   }
   if( bNeedToSave )
   {
      if( SaveGeneralKonyv(sKonyvGeneralFile.c_str()) &&
          CheckGeneralKonyv(sKonyvGeneralFile.c_str()) )
      {
         AnsiString strFile;

         strFile = AnsiString( "Db\\1_" ) + sKonyvGeneralFile;
         if( !SaveGeneralKonyv(strFile.c_str()) ||
             !CheckGeneralKonyv(strFile.c_str()) )
         {
            LOG1( "HIBA: könyvelés biztonsági mentés 1 sikertelen #FV#CS_Konyv::DeleteGeneralKonyv" );
         }

         strFile = AnsiString( "Db\\2_" ) + sKonyvGeneralFile;
         if( !SaveGeneralKonyv(strFile.c_str()) ||
             !CheckGeneralKonyv(strFile.c_str()) )
         {
            LOG1( "HIBA: könyvelés biztonsági mentés 2 sikertelen #FV#CS_Konyv::DeleteGeneralKonyv" );
         }
      }
      else
      {
         LOG1( "HIBA: könyvelés mentés sikertelen #FV#CS_Konyv::DeleteGeneralKonyv" );
      }
   }
}
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CS_Konyv::AddGeneralKonyv( double dMuszakID,
                                double dBerletFtBevetel,
                                double dTermekFtBevetel,
                                char *strMegjegyzes )
{
   typ_konyv_general stTemp;
   unsigned short    nYear, nMonth, nDay;
   double            i;

   // Aktuális dátum kinyerése
   Now().DecodeDate( &nYear, &nMonth, &nDay );
   TDateTime   currDateTime = TDateTime( nYear, nMonth, nDay );

   // Egyedi azonosító megadása
   double dID = currDateTime;
   // Kezdõ és végdátum megadása egyelõre mai dátummal, idõvel
   double dStartDateTime = Now();
   double dStopDateTime  = Now();

   // Ideiglenes könyvelési rekord kitöltése
   stTemp.dID              = dID;
   stTemp.dMuszakID        = dMuszakID;
   stTemp.dStartDateTime   = dStartDateTime;
   stTemp.dStopDateTime    = dStopDateTime;
   stTemp.dBerletFtBevetel = dBerletFtBevetel;
   stTemp.dTermekFtBevetel = dTermekFtBevetel;
   strncpy( stTemp.strMegjegyzes, strMegjegyzes, 995 );

   // Aktuális dátummal és egyezõ mûszak azonosítóval
   // eltárolt korábbi rekord kikeresése
   for( i=0; i<KonyvGeneral.size(); i++ )
   {
      if( KonyvGeneral[i].dID == dID &&
          KonyvGeneral[i].dMuszakID == dMuszakID )
      {
         // Aktuális dátummal már van eltárolt rekord
         // Rekord adatainak módosítása, frissítése
         KonyvGeneral[i].dStopDateTime = dStopDateTime;
         KonyvGeneral[i].dBerletFtBevetel += dBerletFtBevetel;
         KonyvGeneral[i].dTermekFtBevetel += dTermekFtBevetel;
         strncpy( KonyvGeneral[i].strMegjegyzes, strMegjegyzes, 995 );
         break;
      }
   }

   if( i == KonyvGeneral.size() )
   {
      // Aktuális dátummal még nem volt eltárolva rekord
      // Ideiglenesen kitöltött rekord mentése
      KonyvGeneral.push_back( stTemp );
   }

   if( SaveGeneralKonyv(sKonyvGeneralFile.c_str()) &&
       CheckGeneralKonyv(sKonyvGeneralFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sKonyvGeneralFile;
      if( !SaveGeneralKonyv(strFile.c_str()) ||
          !CheckGeneralKonyv(strFile.c_str()) )
      {
         LOG1( "HIBA: könyvelés biztonsági mentés 1 sikertelen #FV#CS_Konyv::AddGeneralKonyv" );
      }

      strFile = AnsiString( "Db\\2_" ) + sKonyvGeneralFile;
      if( !SaveGeneralKonyv(strFile.c_str()) ||
          !CheckGeneralKonyv(strFile.c_str()) )
      {
         LOG1( "HIBA: könyvelés biztonsági mentés 2 sikertelen #FV#CS_Konyv::AddGeneralKonyv" );
      }
   }
   else
   {
      LOG1( "HIBA: könyvelés mentés sikertelen #FV#CS_Konyv::AddGeneralKonyv" );
   }
}
//---------------------------------------------------------------------------
double CS_Konyv::GetSzolariumKonyvCount()
{
   return KonyvSzolarium.size();
}
//---------------------------------------------------------------------------
typ_konyv_szolarium CS_Konyv::GetSzolariumKonyv( double dCount )
{
   typ_konyv_szolarium stSKonyv;

   memset( &stSKonyv, 0, sizeof(typ_konyv_szolarium) );

   if( dCount < KonyvSzolarium.size() )
      return KonyvSzolarium[dCount];
   else
      return stSKonyv;
}
//---------------------------------------------------------------------------
typ_konyv_szolarium CS_Konyv::GetSzolariumKonyvID( double dID )
{
   typ_konyv_szolarium  stSKonyv;
   double               i;

   memset( &stSKonyv, 0, sizeof(typ_konyv_szolarium) );

   for( i=0; i<KonyvSzolarium.size(); i++ )
   {
      if( KonyvSzolarium[i].dID == dID )
         break;
   }

   if( i < KonyvSzolarium.size() )
      return KonyvSzolarium[i];
   else
      return stSKonyv;
}
//---------------------------------------------------------------------------
void CS_Konyv::DeleteSzolariumKonyv( double dID, bool bNeedToSave )
{
   for( unsigned int i=0; i<KonyvSzolarium.size(); i++ )
   {
      if( KonyvSzolarium[i].dID == dID )
      {
         KonyvSzolarium.erase( KonyvSzolarium.begin()+i );
         break;
      }
   }
   if( bNeedToSave )
   {
      if( SaveSolariumKonyv(sKonyvSzolariumFile.c_str()) &&
          CheckSolariumKonyv(sKonyvSzolariumFile.c_str()) )
      {
         AnsiString strFile;

         strFile = AnsiString( "Db\\1_" ) + sKonyvSzolariumFile;
         if( !SaveSolariumKonyv(strFile.c_str()) ||
             !CheckSolariumKonyv(strFile.c_str()) )
         {
            LOG1( "HIBA: szolárium könyv biztonsági mentés 1 sikertelen #FV#CS_Konyv::DeleteSzolariumKonyv" );
         }

         strFile = AnsiString( "Db\\2_" ) + sKonyvSzolariumFile;
         if( !SaveSolariumKonyv(strFile.c_str()) ||
             !CheckSolariumKonyv(strFile.c_str()) )
         {
            LOG1( "HIBA: szolárium könyv biztonsági mentés 2 sikertelen #FV#CS_Konyv::DeleteSzolariumKonyv" );
         }
      }
      else
      {
         LOG1( "HIBA: szolárium könyv mentés sikertelen #FV#CS_Konyv::DeleteSzolariumKonyv" );
      }
   }
}
//---------------------------------------------------------------------------
void CS_Konyv::AddSzolariumKonyv( double dMuszakID,
                                  int nSzolariumID,
                                  double dUzemeltIdo,
                                  double dUzemeltBerletIdo,
                                  double dUzemeltBerletEgyseg,
                                  double dUzemeltFtIdo,
                                  double dUzemeltFt,
                                  double dUzemeltMegszakitott,
                                  double dCsoUzemora,
                                  char *strSzolarium )
{
   typ_konyv_szolarium  stTemp;
   unsigned short       nYear, nMonth, nDay;
   double               i;

   // Aktuális dátum kinyerése
   Now().DecodeDate( &nYear, &nMonth, &nDay );
   TDateTime   currDateTime = TDateTime( nYear, nMonth, nDay );

   // Egyedi azonosító megadása
   double dID = currDateTime;

   // Ideiglenes könyvelési rekord kitöltése
   stTemp.dID                  = dID;
   stTemp.dMuszakID            = dMuszakID;
   stTemp.nSzolariumID         = nSzolariumID;
   stTemp.dUzemeltIdo          = dUzemeltIdo;
   stTemp.dUzemeltBerletIdo    = dUzemeltBerletIdo;
   stTemp.dUzemeltBerletEgyseg = dUzemeltBerletEgyseg;
   stTemp.dUzemeltFtIdo        = dUzemeltFtIdo;
   stTemp.dUzemeltFt           = dUzemeltFt;
   stTemp.dUzemeltMegszakitott = dUzemeltMegszakitott;
   stTemp.dCsoUzemora          = dCsoUzemora;
   strcpy( stTemp.strSzolarium, strSzolarium );

   // Aktuális dátummal, egyezõ mûszak és egyezõ szolárium
   // azonosítóval eltárolt korábbi rekord kikeresése
   for( i=0; i<KonyvSzolarium.size(); i++ )
   {
      if( KonyvSzolarium[i].dID == dID &&
          KonyvSzolarium[i].dMuszakID == dMuszakID &&
          KonyvSzolarium[i].nSzolariumID == nSzolariumID )
      {
         // Aktuális dátummal már van eltárolt rekord
         // Rekord adatainak módosítása, frissítése
         KonyvSzolarium[i].dUzemeltIdo          += dUzemeltIdo;
         KonyvSzolarium[i].dUzemeltBerletIdo    += dUzemeltBerletIdo;
         KonyvSzolarium[i].dUzemeltBerletEgyseg += dUzemeltBerletEgyseg;
         KonyvSzolarium[i].dUzemeltFtIdo        += dUzemeltFtIdo;
         KonyvSzolarium[i].dUzemeltFt           += dUzemeltFt;
         KonyvSzolarium[i].dUzemeltMegszakitott += dUzemeltMegszakitott;
         KonyvSzolarium[i].dCsoUzemora          += dCsoUzemora;
         strcpy( KonyvSzolarium[i].strSzolarium, strSzolarium );
         break;
      }
   }

   if( i == KonyvSzolarium.size() )
   {
      // Aktuális dátummal még nem volt eltárolva rekord
      // Ideiglenesen kitöltött rekord mentése
      KonyvSzolarium.push_back( stTemp );
   }

   if( SaveSolariumKonyv(sKonyvSzolariumFile.c_str()) &&
       CheckSolariumKonyv(sKonyvSzolariumFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sKonyvSzolariumFile;
      if( !SaveSolariumKonyv(strFile.c_str()) ||
          !CheckSolariumKonyv(strFile.c_str()) )
      {
         LOG1( "HIBA: szolárium könyv biztonsági mentés 1 sikertelen #FV#CS_Konyv::AddSzolariumKonyv" );
      }

      strFile = AnsiString( "Db\\2_" ) + sKonyvSzolariumFile;
      if( !SaveSolariumKonyv(strFile.c_str()) ||
          !CheckSolariumKonyv(strFile.c_str()) )
      {
         LOG1( "HIBA: szolárium könyv biztonsági mentés 2 sikertelen #FV#CS_Konyv::AddSzolariumKonyv" );
      }
   }
   else
   {
      LOG1( "HIBA: szolárium könyv mentés sikertelen #FV#CS_Konyv::AddSzolariumKonyv" );
   }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>

#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
// Oszt�ly p�ld�ny l�trehoz�sakor alap adatok inicializ�l�sa
// oszt�ly specifikus "adatb�zis" bet�lt�se
//---------------------------------------------------------------------------
CS_Konyv::CS_Konyv()
{
   sKonyvGeneralFile = KONYVGENERAL_FILE;
   sKonyvSzolariumFile = KONYVSZOLARIUM_FILE;

   LoadDataFromFile();
}
//---------------------------------------------------------------------------
// Oszt�ly p�ld�ny megsz�n�sekor az oszt�ly specifikus "adatb�zis" ment�se
//---------------------------------------------------------------------------
CS_Konyv::~CS_Konyv()
{
   //SaveDataToFile();
}
//---------------------------------------------------------------------------
// "Adatb�zis" bet�lt�se
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

   // �ltal�nos k�nyvel�st tartalmaz� file megnyit�sa
   file = fopen( sKonyvGeneralFile.c_str(), "rb" );
   if( file != NULL )
   {
      // File verzi� kiolvas�sa
      fread( strTemp, 10, 1, file );
      // File verzi� ellen�rz�se
      if( strcmp( KONYV_GENERAL_FILE_VERSION, strTemp ) == 0 )
      {
         // File verzi� megegyezik a programban t�rolt verzi�val
         // Adat rekordok sz�m�nak kiolvas�sa
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount > 0 )
         {
            // Adat rekordok kiolvas�sa, dek�dol�sa, felv�tele az "adatb�zisba"
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
         LOG1( "#FV#CS_Konyv::LoadDataFromFile - general k�nyv" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verzi�sz�m: [" ) +
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

   // Szol�rium specifikus k�nyvel�st tartalmaz� file megnyit�sa
   file = fopen( sKonyvSzolariumFile.c_str(), "rb" );
   if( file != NULL )
   {
      // File verzi� kiolvas�sa
      fread( strTemp, 10, 1, file );
      // File verzi� ellen�rz�se
      if( strcmp( KONYV_SZOLARIUM_FILE_VERSION, strTemp ) == 0 )
      {
         // File verzi� megegyezik a programban t�rolt verzi�val
         // Adat rekordok sz�m�nak kiolvas�sa
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount > 0 )
         {
            // Adat rekordok kiolvas�sa, dek�dol�sa, felv�tele az "adatb�zisba"
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
         LOG1( "#FV#CS_Konyv::LoadDataFromFile - szol�rium k�nyv" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verzi�sz�m: [" ) +
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
// "Adatb�zis" ment�se
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

   // �ltal�nos k�nyvel�st tartalmaz� file megnyit�sa (fel�l�r�sa)
   if( (file = fopen( strFile, "wb" )) != NULL )
   {
      // File verzi� ki�r�sa
      fwrite( KONYV_GENERAL_FILE_VERSION, 10, 1, file );

      // Adat rekordok sz�m�nak ki�r�sa
      nSize = KonyvGeneral.size();
      fwrite( &nSize, sizeof(unsigned int), 1, file );
      // Adat rekordok k�dol�sa, ki�r�sa (�s dek�dol�sa a tov�bbi haszn�lat miatt)
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
      strLogMsg = AnsiString( "HIBA: Nem siker�lt l�trehozni: " ) + strFile;
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
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordsz�m: [" ) +
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
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verzi�sz�m: [" ) +
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
      strLogMsg = AnsiString( "HIBA: Nem siker�lt ellen�rizni a ment�st: " ) + strFile;
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

   // Szol�rium specifikus k�nyvel�st tartalmaz� file megnyit�sa (fel�l�r�sa)
   if( (file = fopen( strFile, "wb" )) != NULL )
   {
      // File verzi� ki�r�sa
      fwrite( KONYV_SZOLARIUM_FILE_VERSION, 10, 1, file );

      // Adat rekordok sz�m�nak ki�r�sa
      nSize = KonyvSzolarium.size();
      fwrite( &nSize, sizeof(unsigned int), 1, file );
      // Adat rekordok k�dol�sa, ki�r�sa (�s dek�dol�sa a tov�bbi haszn�lat miatt)
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
      strLogMsg = AnsiString( "HIBA: Nem siker�lt l�trehozni: " ) + strFile;
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
      // file megnyit�sa sikeres
      char strTemp[10];
      memset( strTemp, 0, sizeof(strTemp) );
      // verzi�sz�m kiolvas�sa
      fread( strTemp, 10, 1, file );
      if( strcmp( KONYV_SZOLARIUM_FILE_VERSION, strTemp ) == 0 )
      {
         // verzi�sz�m egyezik
         //
         unsigned int   nCount = 0;
         // rekordok sz�m�nak kiolvas�sa
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount != KonyvSzolarium.size() )
         {
            // rekordok sz�ma nem egyezik
            //
            LOG1( "#FV#CS_Konyv::CheckSolariumKonyv" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordsz�m: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( KonyvSzolarium.size() ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( nCount > 0 && bRet )
         {
            // rekordok sz�ma egyezik �s van adat
            //
            typ_konyv_szolarium   stTemp;
            for( i=0; i<nCount; i++ )
            {
               // rekord beolvas�sa
               fread( &stTemp, sizeof(typ_konyv_szolarium), 1, file );
               // sz�veg dek�dol�sa
               DeCode( stTemp.strSzolarium, sizeof(stTemp.strSzolarium) );
               // rekord ellen�rz�se
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
         // verzi�sz�m nem egyezik
         LOG1( "#FV#CS_Konyv::CheckSolariumKonyv" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verzi�sz�m: [" ) +
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
      // nem lehetett megnyitni olvas�sra a file-t
      strLogMsg = AnsiString( "HIBA: Nem siker�lt ellen�rizni a ment�st: " ) + strFile;
      LOG1( strLogMsg );
      bRet = false;
   }

   return bRet;
}
//---------------------------------------------------------------------------
// K�nyvel�si rekordok sz�m�nak visszaad�sa
//---------------------------------------------------------------------------
double CS_Konyv::GetGeneralKonyvCount()
{
   return KonyvGeneral.size();
}
//---------------------------------------------------------------------------
// K�nyv rekord kikeres�se az adatb�zisban elfoglalt hely alapj�n
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
// K�nyv rekord kikeres�se ID alapj�n
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
            LOG1( "HIBA: k�nyvel�s biztons�gi ment�s 1 sikertelen #FV#CS_Konyv::DeleteGeneralKonyv" );
         }

         strFile = AnsiString( "Db\\2_" ) + sKonyvGeneralFile;
         if( !SaveGeneralKonyv(strFile.c_str()) ||
             !CheckGeneralKonyv(strFile.c_str()) )
         {
            LOG1( "HIBA: k�nyvel�s biztons�gi ment�s 2 sikertelen #FV#CS_Konyv::DeleteGeneralKonyv" );
         }
      }
      else
      {
         LOG1( "HIBA: k�nyvel�s ment�s sikertelen #FV#CS_Konyv::DeleteGeneralKonyv" );
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

   // Aktu�lis d�tum kinyer�se
   Now().DecodeDate( &nYear, &nMonth, &nDay );
   TDateTime   currDateTime = TDateTime( nYear, nMonth, nDay );

   // Egyedi azonos�t� megad�sa
   double dID = currDateTime;
   // Kezd� �s v�gd�tum megad�sa egyel�re mai d�tummal, id�vel
   double dStartDateTime = Now();
   double dStopDateTime  = Now();

   // Ideiglenes k�nyvel�si rekord kit�lt�se
   stTemp.dID              = dID;
   stTemp.dMuszakID        = dMuszakID;
   stTemp.dStartDateTime   = dStartDateTime;
   stTemp.dStopDateTime    = dStopDateTime;
   stTemp.dBerletFtBevetel = dBerletFtBevetel;
   stTemp.dTermekFtBevetel = dTermekFtBevetel;
   strncpy( stTemp.strMegjegyzes, strMegjegyzes, 995 );

   // Aktu�lis d�tummal �s egyez� m�szak azonos�t�val
   // elt�rolt kor�bbi rekord kikeres�se
   for( i=0; i<KonyvGeneral.size(); i++ )
   {
      if( KonyvGeneral[i].dID == dID &&
          KonyvGeneral[i].dMuszakID == dMuszakID )
      {
         // Aktu�lis d�tummal m�r van elt�rolt rekord
         // Rekord adatainak m�dos�t�sa, friss�t�se
         KonyvGeneral[i].dStopDateTime = dStopDateTime;
         KonyvGeneral[i].dBerletFtBevetel += dBerletFtBevetel;
         KonyvGeneral[i].dTermekFtBevetel += dTermekFtBevetel;
         strncpy( KonyvGeneral[i].strMegjegyzes, strMegjegyzes, 995 );
         break;
      }
   }

   if( i == KonyvGeneral.size() )
   {
      // Aktu�lis d�tummal m�g nem volt elt�rolva rekord
      // Ideiglenesen kit�lt�tt rekord ment�se
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
         LOG1( "HIBA: k�nyvel�s biztons�gi ment�s 1 sikertelen #FV#CS_Konyv::AddGeneralKonyv" );
      }

      strFile = AnsiString( "Db\\2_" ) + sKonyvGeneralFile;
      if( !SaveGeneralKonyv(strFile.c_str()) ||
          !CheckGeneralKonyv(strFile.c_str()) )
      {
         LOG1( "HIBA: k�nyvel�s biztons�gi ment�s 2 sikertelen #FV#CS_Konyv::AddGeneralKonyv" );
      }
   }
   else
   {
      LOG1( "HIBA: k�nyvel�s ment�s sikertelen #FV#CS_Konyv::AddGeneralKonyv" );
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
            LOG1( "HIBA: szol�rium k�nyv biztons�gi ment�s 1 sikertelen #FV#CS_Konyv::DeleteSzolariumKonyv" );
         }

         strFile = AnsiString( "Db\\2_" ) + sKonyvSzolariumFile;
         if( !SaveSolariumKonyv(strFile.c_str()) ||
             !CheckSolariumKonyv(strFile.c_str()) )
         {
            LOG1( "HIBA: szol�rium k�nyv biztons�gi ment�s 2 sikertelen #FV#CS_Konyv::DeleteSzolariumKonyv" );
         }
      }
      else
      {
         LOG1( "HIBA: szol�rium k�nyv ment�s sikertelen #FV#CS_Konyv::DeleteSzolariumKonyv" );
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

   // Aktu�lis d�tum kinyer�se
   Now().DecodeDate( &nYear, &nMonth, &nDay );
   TDateTime   currDateTime = TDateTime( nYear, nMonth, nDay );

   // Egyedi azonos�t� megad�sa
   double dID = currDateTime;

   // Ideiglenes k�nyvel�si rekord kit�lt�se
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

   // Aktu�lis d�tummal, egyez� m�szak �s egyez� szol�rium
   // azonos�t�val elt�rolt kor�bbi rekord kikeres�se
   for( i=0; i<KonyvSzolarium.size(); i++ )
   {
      if( KonyvSzolarium[i].dID == dID &&
          KonyvSzolarium[i].dMuszakID == dMuszakID &&
          KonyvSzolarium[i].nSzolariumID == nSzolariumID )
      {
         // Aktu�lis d�tummal m�r van elt�rolt rekord
         // Rekord adatainak m�dos�t�sa, friss�t�se
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
      // Aktu�lis d�tummal m�g nem volt elt�rolva rekord
      // Ideiglenesen kit�lt�tt rekord ment�se
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
         LOG1( "HIBA: szol�rium k�nyv biztons�gi ment�s 1 sikertelen #FV#CS_Konyv::AddSzolariumKonyv" );
      }

      strFile = AnsiString( "Db\\2_" ) + sKonyvSzolariumFile;
      if( !SaveSolariumKonyv(strFile.c_str()) ||
          !CheckSolariumKonyv(strFile.c_str()) )
      {
         LOG1( "HIBA: szol�rium k�nyv biztons�gi ment�s 2 sikertelen #FV#CS_Konyv::AddSzolariumKonyv" );
      }
   }
   else
   {
      LOG1( "HIBA: szol�rium k�nyv ment�s sikertelen #FV#CS_Konyv::AddSzolariumKonyv" );
   }
}
//---------------------------------------------------------------------------

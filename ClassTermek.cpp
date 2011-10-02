//---------------------------------------------------------------------------

#include <vcl.h>

#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
CS_Termek::CS_Termek()
{
   // Alap változók értékfeltöltése
   sTermekFile = TERMEK_FILE;

   // Adatbázis betöltése
   LoadDataFromFile();
}
//---------------------------------------------------------------------------
CS_Termek::~CS_Termek()
{
   //SaveDataToFile( sTermekFile.c_str() );
}
//---------------------------------------------------------------------------
void CS_Termek::LoadDataFromFile()
{
   LOG4("#FV#CS_Termek::LoadDataFromFile - START");

   FILE           *file = NULL;
   char           strTemp[10];
   unsigned int   nCount = 0;
   int            nErrorMsgID;

   memset( strTemp, 0, sizeof(strTemp) );

   // Termékeket tartalmazó állomány megnyitása olvasásra
   file = fopen( sTermekFile.c_str(), "rb" );
   if( file != NULL )
   {
      // File megnyitás sikeres
      LOG3( AnsiString("LOAD: Termék állomány [")+
            AnsiString(sTermekFile)+
            AnsiString("] sikeresen megnyitva") );

      // File verziószám kiolvasása
      fread( strTemp, 10, 1, file );
      LOG3( AnsiString("Verziószám: [")+AnsiString(strTemp)+AnsiString("]") );
      if( strcmp( TERMEK_FILE_VERSION, strTemp ) == 0 )
      {
         // File verziószám egyezik
         LOG3("Verziószám egyezik");

         // Rekordok számának kiolvasása
         fread( &nCount, sizeof(unsigned int), 1, file );
         LOG3( AnsiString("Rekordok száma: [")+AnsiString(nCount)+AnsiString("]") );
         if( nCount > 0 )
         {
            // Vannak a file-ban adatrekordok
            typ_termek  stTemp;
            for( unsigned int i=0; i<nCount; i++ )
            {
               // Rekord beolvasása
               fread( &stTemp, sizeof(typ_termek), 1, file );
               // Rekord szöveges részeinek dekódolása
               DeCode( stTemp.strVonalkod, sizeof(stTemp.strVonalkod) );
               DeCode( stTemp.strNev, sizeof(stTemp.strNev) );
               LOG4( AnsiString("[")+
                     AnsiString(i)+
                     AnsiString("] [")+
                     AnsiString(stTemp.nID)+
                     AnsiString("] [")+
                     AnsiString(stTemp.strVonalkod)+
                     AnsiString("] [")+
                     AnsiString(stTemp.strNev)+
                     AnsiString("]") );
               // Rekord felvétele a memóriába
               Termek.push_back( stTemp );
            }
         }
         LOG3("Belovasás vége");
      }
      else
      {
         // Verziószám nem egyezik
         LOG1( "#FV#CS_Termek::LoadDataFromFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( TERMEK_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }
      fclose( file );
   }
   else
   {
      // Nem sikerült megnyitni az adatállományt
      LOG1( "#FV#CS_Termek::LoadDataFromFile" );
      strLogMsg = AnsiString( "HIBA: Nem sikerült megnyitni az adatállományt" );
      LOG1( strLogMsg );
   }

   LOG4("#FV#CS_Termek::LoadDataFromFile - END");
}
//---------------------------------------------------------------------------
bool CS_Termek::SaveDataToFile( const char *strFile )
{
   LOG4("#FV#CS_Termek::SaveDataToFile - START");

   FILE          *file = NULL;
   unsigned int   nSize,i;
   bool           bRet = true;

   // Termékeket tartalmazó állomány megnyitása írásra
   file = fopen( strFile, "wb" );
   if( file != NULL )
   {
      // File megnyitás sikeres
      LOG3( AnsiString("SAVE: Termék állomány [")+
            AnsiString(strFile)+
            AnsiString("] sikeresen megnyitva") );
      // File verziószám kiírása
      fwrite( TERMEK_FILE_VERSION, 10, 1, file );
      LOG3( AnsiString("Verziószám: [")+
            AnsiString(TERMEK_FILE_VERSION)+
            AnsiString("]") );
      // Rekordok számának lekérdezése
      nSize = Termek.size();
      // Rekordok számának kiírása
      fwrite( &nSize, sizeof(unsigned int), 1, file );
      LOG3( AnsiString("Rekordszám: [")+
            AnsiString(nSize)+
            AnsiString("]") );
      // Rekordok kiírása
      for( i=0; i<Termek.size(); i++ )
      {
         // Rekord szöveges részeinek kódolása
         EnCode( Termek[i].strVonalkod, sizeof(Termek[i].strVonalkod) );
         EnCode( Termek[i].strNev, sizeof(Termek[i].strNev) );
         // Rekord kiírása
         fwrite( &Termek[i], sizeof(typ_termek), 1, file );
         // Rekord szöveges részeinek visszakódolása
         DeCode( Termek[i].strVonalkod, sizeof(Termek[i].strVonalkod) );
         DeCode( Termek[i].strNev, sizeof(Termek[i].strNev) );
      }
      LOG3( AnsiString("Kiírt rekordok: [")+
            AnsiString(i)+
            AnsiString("]") );

      fclose( file );
      LOG3( "Kiírás vége" );
   }
   else
   {
      // Nem sikerült létrehozni a file-t
      strLogMsg = AnsiString( "HIBA: Nem sikerült létrehozni: " ) + strFile;
      LOG1( strLogMsg );
      bRet = false;
   }

   LOG4("#FV#CS_Termek::SaveDataToFile - END");

   return bRet;
}
//---------------------------------------------------------------------------
bool CS_Termek::CheckDataToFile( const char *strFile )
{
   LOG4("#FV#CS_Termek::CheckDataToFile - START");

   FILE          *file = NULL;
   unsigned int   nSize,i;
   bool           bRet = true;

   // Termékeket tartalmazó állomány megnyitása olvasásra
   file = fopen( strFile, "rb" );
   if( file != NULL )
   {
      // File megnyitása sikeres
      LOG3( AnsiString("CHECK: Termék állomány [")+
            AnsiString(strFile)+
            AnsiString("] sikeresen megnyitva") );
      char strTemp[10];
      memset( strTemp, 0, sizeof(strTemp) );
      // verziószám kiolvasása
      fread( strTemp, 10, 1, file );
      LOG3( AnsiString("Verziószám: [")+
            AnsiString(strTemp)+
            AnsiString("]") );
      if( strcmp( TERMEK_FILE_VERSION, strTemp ) == 0 )
      {
         // verziószám egyezik
         //
         unsigned int   nCount = 0;
         // rekordok számának kiolvasása
         fread( &nCount, sizeof(unsigned int), 1, file );
         LOG3( AnsiString("Rekordszám: [")+
               AnsiString(nCount)+
               AnsiString("]") );
         if( nCount != Termek.size() )
         {
            // rekordok száma nem egyezik
            //
            LOG1( "#FV#CS_Termek::CheckDataToFile" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordszám: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( Termek.size() ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( nCount > 0 && bRet )
         {
            // rekordok száma egyezik és van adat
            //
            typ_termek   stTemp;
            for( i=0; i<nCount; i++ )
            {
               // rekord beolvasása
               fread( &stTemp, sizeof(typ_termek), 1, file );
               // szöveg dekódolása
               DeCode( stTemp.strVonalkod, sizeof(stTemp.strVonalkod) );
               DeCode( stTemp.strNev, sizeof(stTemp.strNev) );
               // rekord ellenõrzése
               if( memcmp( &Termek[i], &stTemp, sizeof(typ_termek) ) != 0 )
               {
                  // rekord nem egyezik
                  //
                  LOG1( "#FV#CS_Termek::CheckDataToFile" );
                  strLogMsg = AnsiString( "HIBA: Nem egyezik a rekord: [" ) +
                              AnsiString( stTemp.strVonalkod )+
                              AnsiString( "] [" )+
                              AnsiString( Termek[i].strVonalkod )+
                              AnsiString( "]" );
                  LOG1( strLogMsg );
                  strLogMsg = AnsiString( "File: [" )+
                              AnsiString( stTemp.nID )+
                              AnsiString( "] [" )+
                              AnsiString( stTemp.strVonalkod )+
                              AnsiString( "] [" )+
                              AnsiString( stTemp.strNev )+
                              AnsiString( "] [" )+
                              AnsiString( stTemp.nAr )+
                              AnsiString( "] [" )+
                              AnsiString( stTemp.nDarab )+
                              AnsiString( "] [" )+
                              AnsiString( stTemp.nArBeszerzes )+
                              AnsiString( "]" );
                  LOG3( strLogMsg );
                  strLogMsg = AnsiString( "Db  : [" )+
                              AnsiString( Termek[i].nID )+
                              AnsiString( "] [" )+
                              AnsiString( Termek[i].strVonalkod )+
                              AnsiString( "] [" )+
                              AnsiString( Termek[i].strNev )+
                              AnsiString( "] [" )+
                              AnsiString( Termek[i].nAr )+
                              AnsiString( "] [" )+
                              AnsiString( Termek[i].nDarab )+
                              AnsiString( "] [" )+
                              AnsiString( Termek[i].nArBeszerzes )+
                              AnsiString( "]" );
                  LOG3( strLogMsg );
                  bRet = false;
               }
            }
         }
      }
      else
      {
         // verziószám nem egyezik
         LOG1( "#FV#CS_Termek::CheckDataToFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( TERMEK_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
         bRet = false;
      }
      fclose( file );
      LOG3( "Ellenõrzés vége" );
   }
   else
   {
      // nem lehetett megnyitni olvasásra a file-t
      strLogMsg = AnsiString( "HIBA: Nem sikerült ellenõrizni a mentést: " ) + strFile;
      LOG1( strLogMsg );
      bRet = false;
   }

   LOG4("#FV#CS_Termek::CheckDataToFile - END");

   return bRet;
}
//---------------------------------------------------------------------------
void CS_Termek::AddTermek( typ_termek stTemp )
{
   LOG4("#FV#CS_Termek::AddTermek - START");

   // legelsõ nem használt ID kikeresése
   double i;
   for( i=1; ; i++ )
   {
      typ_termek stTmp = GetTermekId( i );
      if( stTmp.nID == 0 )
         break;
   }
   stTemp.nID = i;
   LOG3( AnsiString("Új termék azonosító: [")+
         AnsiString(stTemp.nID)+
         AnsiString("]") );

   // Termék felvétele a memóriába
   Termek.push_back( stTemp );
   LOG3( AnsiString( "Termék felvéve memóriába: [" )+
         AnsiString( stTemp.nID )+
         AnsiString( "] [" )+
         AnsiString( stTemp.strVonalkod )+
         AnsiString( "] [" )+
         AnsiString( stTemp.strNev )+
         AnsiString( "] [" )+
         AnsiString( stTemp.nAr )+
         AnsiString( "] [" )+
         AnsiString( stTemp.nDarab )+
         AnsiString( "] [" )+
         AnsiString( stTemp.nArBeszerzes )+
         AnsiString( "]" ) );

   // Termék adatbázis mentése és ellenõrzése
   LOG3( "Termék adatbázis mentése és ellenõrzése" );
   if( SaveDataToFile(sTermekFile.c_str()) &&
       CheckDataToFile(sTermekFile.c_str()) )
   {
      // Mentés és ellenõrzés sikeres
      AnsiString strFile;

      // Termék adatbázis mentése és ellenõrzése az 1-es pótállományba
      LOG3( "Termék adatbázis mentése és ellenõrzése az 1-es pótállományba" );
      strFile = AnsiString( "Db\\1_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztonsági mentés 1 sikertelen #FV#CS_Termek::AddTermek" );
      }

      // Termék adatbázis mentése és ellenõrzése a 2-es pótállományba
      LOG3( "Termék adatbázis mentése és ellenõrzése a 2-es pótállományba" );
      strFile = AnsiString( "Db\\2_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztonsági mentés 2 sikertelen #FV#CS_Termek::AddTermek" );
      }
   }
   else
   {
      LOG1( "HIBA: termek mentés sikertelen #FV#CS_Termek::AddTermek" );
   }

   LOG4("#FV#CS_Termek::AddTermek - END");
}
//---------------------------------------------------------------------------
bool CS_Termek::ModifyTermek( typ_termek stTemp )
{
   LOG4("#FV#CS_Termek::ModifyTermek - START");

   double i;

   for(i=0;i<Termek.size();i++)
   {
      if( Termek[i].nID == stTemp.nID )
      {
         strcpy( Termek[i].strNev, stTemp.strNev );
         strcpy( Termek[i].strVonalkod, stTemp.strVonalkod );
         Termek[i].nAr = stTemp.nAr;
         Termek[i].nDarab = stTemp.nDarab;
         Termek[i].nArBeszerzes = stTemp.nArBeszerzes;
         break;
      }
   }

   // Termék adatbázis mentése és ellenõrzése
   if( SaveDataToFile(sTermekFile.c_str()) &&
       CheckDataToFile(sTermekFile.c_str()) )
   {
      AnsiString strFile;

      // Termék adatbázis mentése és ellenõrzése az 1-es pótállományba
      strFile = AnsiString( "Db\\1_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztonsági mentés 1 sikertelen #FV#CS_Termek::ModifyTermek" );
      }

      // Termék adatbázis mentése és ellenõrzése a 2-es pótállományba
      strFile = AnsiString( "Db\\2_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztonsági mentés 2 sikertelen #FV#CS_Termek::ModifyTermek" );
      }
   }
   else
   {
      LOG1( "HIBA: termek mentés sikertelen #FV#CS_Termek::ModifyTermek" );
   }

   if( i == Termek.size() )
   {
      LOG4("#FV#CS_Termek::ModifyTermek - END false");
      return false;
   }
   else
   {
      LOG4("#FV#CS_Termek::ModifyTermek - END true");
      return true;
   }
}
//---------------------------------------------------------------------------
bool CS_Termek::DeleteTermek( DWORD nID )
{
   DWORD i;

   for(i=0;i<Termek.size();i++)
   {
      if( Termek[i].nID == nID )
      {
         Termek.erase( Termek.begin()+i );
         break;
      }
   }

   if( SaveDataToFile(sTermekFile.c_str()) &&
       CheckDataToFile(sTermekFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztonsági mentés 1 sikertelen #FV#CS_Termek::DeleteTermek" );
      }

      strFile = AnsiString( "Db\\2_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztonsági mentés 2 sikertelen #FV#CS_Termek::DeleteTermek" );
      }
   }
   else
   {
      LOG1( "HIBA: termek mentés sikertelen #FV#CS_Termek::DeleteTermek" );
   }

   if( i == Termek.size() )
      return false;
   else
      return true;
}
//---------------------------------------------------------------------------
typ_termek CS_Termek::GetTermekItem( double nCount )
{
   typ_termek  stTemp;

   memset( &stTemp, 0, sizeof(typ_termek) );

   if( nCount < Termek.size() )
      return Termek[nCount];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
typ_termek CS_Termek::GetTermekId( DWORD nID )
{
   typ_termek stTemp;
   double i;

   memset( &stTemp, 0, sizeof(typ_termek) );

   for(i=0;i<Termek.size();i++)
   {
      if( Termek[i].nID == nID )
      {
         break;
      }
   }

   if( i < Termek.size() )
      return Termek[i];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
typ_termek CS_Termek::GetTermekKod( char *strVonalkod )
{
   typ_termek stTemp;
   double i;

   memset( &stTemp, 0, sizeof(typ_termek) );

   for(i=0;i<Termek.size();i++)
   {
      if( strcmpi(Termek[i].strVonalkod, strVonalkod ) == 0 )
      {
         break;
      }
   }

   if( i < Termek.size() )
      return Termek[i];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
typ_termek CS_Termek::GetTermekNev( char *strNev )
{
   typ_termek stTemp;
   double i;

   memset( &stTemp, 0, sizeof(typ_termek) );

   for(i=0;i<Termek.size();i++)
   {
      if( strcmp(Termek[i].strNev, strNev ) == 0 )
      {
         break;
      }
   }

   if( i < Termek.size() )
      return Termek[i];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
double CS_Termek::GetTermekCount()
{
   return Termek.size();
}
//---------------------------------------------------------------------------
int CS_Termek::GetTermekDarab( DWORD nID )
{
   typ_termek  stTemp = GetTermekId( nID );

   return stTemp.nDarab;
}
//---------------------------------------------------------------------------
bool CS_Termek::SetTermekDarab( DWORD nID, int nDarab )
{
   typ_termek stTemp;
   double i;

   memset( &stTemp, 0, sizeof(typ_termek) );

   for(i=0;i<Termek.size();i++)
   {
      if( Termek[i].nID == nID )
      {
         Termek[i].nDarab = nDarab;
         break;
      }
   }

   if( SaveDataToFile(sTermekFile.c_str()) &&
       CheckDataToFile(sTermekFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztonsági mentés 1 sikertelen #FV#CS_Termek::SetTermekDarab" );
      }

      strFile = AnsiString( "Db\\2_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztonsági mentés 2 sikertelen #FV#CS_Termek::SetTermekDarab" );
      }
   }
   else
   {
      LOG1( "HIBA: termek mentés sikertelen #FV#CS_Termek::SetTermekDarab" );
   }

   if( i < Termek.size() )
      return true;
   else
      return false;
}
//---------------------------------------------------------------------------

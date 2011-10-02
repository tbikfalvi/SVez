//---------------------------------------------------------------------------

#include <vcl.h>

#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
CS_Termek::CS_Termek()
{
   // Alap v�ltoz�k �rt�kfelt�lt�se
   sTermekFile = TERMEK_FILE;

   // Adatb�zis bet�lt�se
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

   // Term�keket tartalmaz� �llom�ny megnyit�sa olvas�sra
   file = fopen( sTermekFile.c_str(), "rb" );
   if( file != NULL )
   {
      // File megnyit�s sikeres
      LOG3( AnsiString("LOAD: Term�k �llom�ny [")+
            AnsiString(sTermekFile)+
            AnsiString("] sikeresen megnyitva") );

      // File verzi�sz�m kiolvas�sa
      fread( strTemp, 10, 1, file );
      LOG3( AnsiString("Verzi�sz�m: [")+AnsiString(strTemp)+AnsiString("]") );
      if( strcmp( TERMEK_FILE_VERSION, strTemp ) == 0 )
      {
         // File verzi�sz�m egyezik
         LOG3("Verzi�sz�m egyezik");

         // Rekordok sz�m�nak kiolvas�sa
         fread( &nCount, sizeof(unsigned int), 1, file );
         LOG3( AnsiString("Rekordok sz�ma: [")+AnsiString(nCount)+AnsiString("]") );
         if( nCount > 0 )
         {
            // Vannak a file-ban adatrekordok
            typ_termek  stTemp;
            for( unsigned int i=0; i<nCount; i++ )
            {
               // Rekord beolvas�sa
               fread( &stTemp, sizeof(typ_termek), 1, file );
               // Rekord sz�veges r�szeinek dek�dol�sa
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
               // Rekord felv�tele a mem�ri�ba
               Termek.push_back( stTemp );
            }
         }
         LOG3("Belovas�s v�ge");
      }
      else
      {
         // Verzi�sz�m nem egyezik
         LOG1( "#FV#CS_Termek::LoadDataFromFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verzi�sz�m: [" ) +
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
      // Nem siker�lt megnyitni az adat�llom�nyt
      LOG1( "#FV#CS_Termek::LoadDataFromFile" );
      strLogMsg = AnsiString( "HIBA: Nem siker�lt megnyitni az adat�llom�nyt" );
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

   // Term�keket tartalmaz� �llom�ny megnyit�sa �r�sra
   file = fopen( strFile, "wb" );
   if( file != NULL )
   {
      // File megnyit�s sikeres
      LOG3( AnsiString("SAVE: Term�k �llom�ny [")+
            AnsiString(strFile)+
            AnsiString("] sikeresen megnyitva") );
      // File verzi�sz�m ki�r�sa
      fwrite( TERMEK_FILE_VERSION, 10, 1, file );
      LOG3( AnsiString("Verzi�sz�m: [")+
            AnsiString(TERMEK_FILE_VERSION)+
            AnsiString("]") );
      // Rekordok sz�m�nak lek�rdez�se
      nSize = Termek.size();
      // Rekordok sz�m�nak ki�r�sa
      fwrite( &nSize, sizeof(unsigned int), 1, file );
      LOG3( AnsiString("Rekordsz�m: [")+
            AnsiString(nSize)+
            AnsiString("]") );
      // Rekordok ki�r�sa
      for( i=0; i<Termek.size(); i++ )
      {
         // Rekord sz�veges r�szeinek k�dol�sa
         EnCode( Termek[i].strVonalkod, sizeof(Termek[i].strVonalkod) );
         EnCode( Termek[i].strNev, sizeof(Termek[i].strNev) );
         // Rekord ki�r�sa
         fwrite( &Termek[i], sizeof(typ_termek), 1, file );
         // Rekord sz�veges r�szeinek visszak�dol�sa
         DeCode( Termek[i].strVonalkod, sizeof(Termek[i].strVonalkod) );
         DeCode( Termek[i].strNev, sizeof(Termek[i].strNev) );
      }
      LOG3( AnsiString("Ki�rt rekordok: [")+
            AnsiString(i)+
            AnsiString("]") );

      fclose( file );
      LOG3( "Ki�r�s v�ge" );
   }
   else
   {
      // Nem siker�lt l�trehozni a file-t
      strLogMsg = AnsiString( "HIBA: Nem siker�lt l�trehozni: " ) + strFile;
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

   // Term�keket tartalmaz� �llom�ny megnyit�sa olvas�sra
   file = fopen( strFile, "rb" );
   if( file != NULL )
   {
      // File megnyit�sa sikeres
      LOG3( AnsiString("CHECK: Term�k �llom�ny [")+
            AnsiString(strFile)+
            AnsiString("] sikeresen megnyitva") );
      char strTemp[10];
      memset( strTemp, 0, sizeof(strTemp) );
      // verzi�sz�m kiolvas�sa
      fread( strTemp, 10, 1, file );
      LOG3( AnsiString("Verzi�sz�m: [")+
            AnsiString(strTemp)+
            AnsiString("]") );
      if( strcmp( TERMEK_FILE_VERSION, strTemp ) == 0 )
      {
         // verzi�sz�m egyezik
         //
         unsigned int   nCount = 0;
         // rekordok sz�m�nak kiolvas�sa
         fread( &nCount, sizeof(unsigned int), 1, file );
         LOG3( AnsiString("Rekordsz�m: [")+
               AnsiString(nCount)+
               AnsiString("]") );
         if( nCount != Termek.size() )
         {
            // rekordok sz�ma nem egyezik
            //
            LOG1( "#FV#CS_Termek::CheckDataToFile" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordsz�m: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( Termek.size() ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( nCount > 0 && bRet )
         {
            // rekordok sz�ma egyezik �s van adat
            //
            typ_termek   stTemp;
            for( i=0; i<nCount; i++ )
            {
               // rekord beolvas�sa
               fread( &stTemp, sizeof(typ_termek), 1, file );
               // sz�veg dek�dol�sa
               DeCode( stTemp.strVonalkod, sizeof(stTemp.strVonalkod) );
               DeCode( stTemp.strNev, sizeof(stTemp.strNev) );
               // rekord ellen�rz�se
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
         // verzi�sz�m nem egyezik
         LOG1( "#FV#CS_Termek::CheckDataToFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verzi�sz�m: [" ) +
                     AnsiString( TERMEK_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
         bRet = false;
      }
      fclose( file );
      LOG3( "Ellen�rz�s v�ge" );
   }
   else
   {
      // nem lehetett megnyitni olvas�sra a file-t
      strLogMsg = AnsiString( "HIBA: Nem siker�lt ellen�rizni a ment�st: " ) + strFile;
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

   // legels� nem haszn�lt ID kikeres�se
   double i;
   for( i=1; ; i++ )
   {
      typ_termek stTmp = GetTermekId( i );
      if( stTmp.nID == 0 )
         break;
   }
   stTemp.nID = i;
   LOG3( AnsiString("�j term�k azonos�t�: [")+
         AnsiString(stTemp.nID)+
         AnsiString("]") );

   // Term�k felv�tele a mem�ri�ba
   Termek.push_back( stTemp );
   LOG3( AnsiString( "Term�k felv�ve mem�ri�ba: [" )+
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

   // Term�k adatb�zis ment�se �s ellen�rz�se
   LOG3( "Term�k adatb�zis ment�se �s ellen�rz�se" );
   if( SaveDataToFile(sTermekFile.c_str()) &&
       CheckDataToFile(sTermekFile.c_str()) )
   {
      // Ment�s �s ellen�rz�s sikeres
      AnsiString strFile;

      // Term�k adatb�zis ment�se �s ellen�rz�se az 1-es p�t�llom�nyba
      LOG3( "Term�k adatb�zis ment�se �s ellen�rz�se az 1-es p�t�llom�nyba" );
      strFile = AnsiString( "Db\\1_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztons�gi ment�s 1 sikertelen #FV#CS_Termek::AddTermek" );
      }

      // Term�k adatb�zis ment�se �s ellen�rz�se a 2-es p�t�llom�nyba
      LOG3( "Term�k adatb�zis ment�se �s ellen�rz�se a 2-es p�t�llom�nyba" );
      strFile = AnsiString( "Db\\2_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztons�gi ment�s 2 sikertelen #FV#CS_Termek::AddTermek" );
      }
   }
   else
   {
      LOG1( "HIBA: termek ment�s sikertelen #FV#CS_Termek::AddTermek" );
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

   // Term�k adatb�zis ment�se �s ellen�rz�se
   if( SaveDataToFile(sTermekFile.c_str()) &&
       CheckDataToFile(sTermekFile.c_str()) )
   {
      AnsiString strFile;

      // Term�k adatb�zis ment�se �s ellen�rz�se az 1-es p�t�llom�nyba
      strFile = AnsiString( "Db\\1_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztons�gi ment�s 1 sikertelen #FV#CS_Termek::ModifyTermek" );
      }

      // Term�k adatb�zis ment�se �s ellen�rz�se a 2-es p�t�llom�nyba
      strFile = AnsiString( "Db\\2_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztons�gi ment�s 2 sikertelen #FV#CS_Termek::ModifyTermek" );
      }
   }
   else
   {
      LOG1( "HIBA: termek ment�s sikertelen #FV#CS_Termek::ModifyTermek" );
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
         LOG1( "HIBA: termek biztons�gi ment�s 1 sikertelen #FV#CS_Termek::DeleteTermek" );
      }

      strFile = AnsiString( "Db\\2_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztons�gi ment�s 2 sikertelen #FV#CS_Termek::DeleteTermek" );
      }
   }
   else
   {
      LOG1( "HIBA: termek ment�s sikertelen #FV#CS_Termek::DeleteTermek" );
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
         LOG1( "HIBA: termek biztons�gi ment�s 1 sikertelen #FV#CS_Termek::SetTermekDarab" );
      }

      strFile = AnsiString( "Db\\2_" ) + sTermekFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: termek biztons�gi ment�s 2 sikertelen #FV#CS_Termek::SetTermekDarab" );
      }
   }
   else
   {
      LOG1( "HIBA: termek ment�s sikertelen #FV#CS_Termek::SetTermekDarab" );
   }

   if( i < Termek.size() )
      return true;
   else
      return false;
}
//---------------------------------------------------------------------------

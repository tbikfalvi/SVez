//---------------------------------------------------------------------------

#include <vcl.h>

#include "Classes.h"
#include "Database.h"
#include "Language.h"
//---------------------------------------------------------------------------
CS_Penztar::CS_Penztar()
{
   sPenztarFile = PENZTAR_FILE;
   sPenztarLogFile = PENZTARLOG_FILE;

   Penztar.nCurrentCash = 0;
   Penztar.nStartingCash = 0;

   LoadDataFromFile();
}
//---------------------------------------------------------------------------
CS_Penztar::~CS_Penztar()
{
   //SaveDataToFile( sPenztarFile.c_str() );
}
//---------------------------------------------------------------------------
void CS_Penztar::LoadDataFromFile()
{
   LoadPenztar();
   LoadPenztarLog();
}
//---------------------------------------------------------------------------
void CS_Penztar::LoadPenztar()
{
   FILE  *file = NULL;
   char  strTemp[10];
   int   nErrorMsgID;

   memset( strTemp, 0, sizeof(strTemp) );

/*   if( !CheckAndCorrectDBFiles( sPenztarFile.c_str(), &nErrorMsgID ) )
   {
      AnsiString  strMsg;
      strMsg.sprintf( "\n\nError Code: sys108\nError ID: %d", nErrorMsgID );
      throw Exception( strMsg );
   }*/

   file = fopen( sPenztarFile.c_str(), "rb" );
   if( file != NULL )
   {
      fread( strTemp, 10, 1, file );
      if( strcmp( PENZTAR_FILE_VERSION, strTemp ) == 0 )
      {
         fread( &Penztar, sizeof(typ_penztar), 1, file );
      }
      else
      {
         LOG1( "#FV#CS_Penztar::LoadPenztar" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( PENZTAR_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }
      fclose( file );
   }
}
//---------------------------------------------------------------------------
void CS_Penztar::LoadPenztarLog()
{
   FILE  *file = NULL;
   char  strTemp[10];
   int   nErrorMsgID;

   memset( strTemp, 0, sizeof(strTemp) );

/*   if( !CheckAndCorrectDBFiles( sPenztarLogFile.c_str(), &nErrorMsgID ) )
   {
      AnsiString  strMsg;
      strMsg.sprintf( "\n\nError Code: sys109\nError ID: %d", nErrorMsgID );
      throw Exception( strMsg );
   }*/

   file = fopen( sPenztarLogFile.c_str(), "rb" );
   if( file != NULL )
   {
      fread( strTemp, 10, 1, file );
      if( strcmp( PENZTAR_FILE_VERSION, strTemp ) == 0 )
      {
         typ_penztar_action stTemp;
         while( fread( &stTemp, sizeof(typ_penztar_action), 1, file ) )
         {
            PenztarAction.push_back( stTemp );
         }
      }
      else
      {
         LOG1( "#FV#CS_Penztar::LoadPenztarLog" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( PENZTAR_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }
      fclose( file );
   }
}
//---------------------------------------------------------------------------
bool CS_Penztar::SaveDataToFile( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize;
   bool           bRet = true;

   file = fopen( strFile, "wb" );
   if( file != NULL )
   {
      fwrite( PENZTAR_FILE_VERSION, 10, 1, file );
      fwrite( &Penztar, sizeof(typ_penztar), 1, file );

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
bool CS_Penztar::CheckDataToFile( const char *strFile )
{
   FILE          *file = NULL;
   bool           bRet = true;

   file = fopen( strFile, "rb" );
   if( file != NULL )
   {
      // file megnyitása sikeres
      char strTemp[10];
      memset( strTemp, 0, sizeof(strTemp) );
      // verziószám kiolvasása
      fread( strTemp, 10, 1, file );
      if( strcmp( PENZTAR_FILE_VERSION, strTemp ) == 0 )
      {
         // verziószám egyezik
         //
         typ_penztar   stTemp;
         // rekord beolvasása
         fread( &stTemp, sizeof(typ_penztar), 1, file );
         // rekord ellenõrzése
         if( memcmp( &Penztar, &stTemp, sizeof(typ_penztar) ) != 0 )
         {
            // rekord nem egyezik
            //
            LOG1( "#FV#CS_Penztar::CheckDataToFile" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekord" );
            LOG1( strLogMsg );
            bRet = false;
         }
      }
      else
      {
         // verziószám nem egyezik
         LOG1( "#FV#CS_Penztar::CheckDataToFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( PENZTAR_FILE_VERSION ) +
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
bool CS_Penztar::SavePenztarCashMod( typ_user stUser, char Action, int nCash, char *strMegjegyzes )
{
   typ_penztar_action    stTemp;
   FILE                 *file = NULL;
   char                  strTemp[10];
   bool                  bRet = true;

   memset( &stTemp, 0, sizeof(typ_penztar_action) );
   stTemp.dID        = stUser.dID;
   stTemp.dDateTime  = Now();
   stTemp.Action     = Action;
   stTemp.nCash      = nCash;
   strcpy( stTemp.strLoginNev, stUser.strLoginNev );
   strncpy( stTemp.strMegjegyzes, strMegjegyzes, 99 );

   PenztarAction.push_back( stTemp );

   file = fopen( sPenztarLogFile.c_str(), "rb" );
   if( file != NULL )
   {
      fread( strTemp, 10, 1, file );
      fclose( file );
      if( strcmp( PENZTAR_FILE_VERSION, strTemp ) != 0 )
      {
         RenameFile( sPenztarLogFile, FormatDateTime("yyyymmdd",Now())+sPenztarFile );
         file = fopen( sPenztarLogFile.c_str(), "wb" );
         fwrite( PENZTAR_FILE_VERSION, 10, 1, file );
         fclose( file );
      }
   }
   else
   {
      file = fopen( sPenztarLogFile.c_str(), "wb" );
      if( file != NULL )
      {
         fwrite( PENZTAR_FILE_VERSION, 10, 1, file );
         fclose( file );
      }
      else
      {
         // nem sikerült létrehozni a file-t
         strLogMsg = AnsiString( "HIBA: Nem sikerült létrehozni: " ) + sPenztarLogFile;
         LOG1( strLogMsg );
         bRet = false;
      }
   }

   file = fopen( sPenztarLogFile.c_str(), "ab" );
   if( file != NULL )
   {
      fwrite( &stTemp, sizeof(typ_penztar_action), 1, file );
      fclose( file );
   }
   else
   {
      // nem sikerült hozzáfûzni a file-t
      strLogMsg = AnsiString( "HIBA: Nem sikerült hozzáfûzni: " ) + sPenztarLogFile;
      LOG1( strLogMsg );
      bRet = false;
   }

   return bRet;
}
//---------------------------------------------------------------------------
void CS_Penztar::PenztarNyitas( typ_user stUser, int nCash )
{
   SavePenztarCashMod( stUser, ACTION_PENZTAR_NYITAS, nCash, FormLanguage->LangStr(STR_CASSA_OPEN).c_str() );
   Penztar.nCurrentCash = Penztar.nStartingCash = nCash;
}
//---------------------------------------------------------------------------
void CS_Penztar::PenztarBevetel( typ_user stUser, int nCash, char *strMegjegyzes )
{
   SavePenztarCashMod( stUser, ACTION_PENZTAR_BEVET, nCash, strMegjegyzes );
   Penztar.nCurrentCash += nCash;

   if( SaveDataToFile(sPenztarFile.c_str()) /*&&
       CheckDataToFile(sPenztarFile.c_str())*/ )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sPenztarFile;
      if( !SaveDataToFile(strFile.c_str()) /*||
          !CheckDataToFile(strFile.c_str())*/ )
      {
         LOG1( "HIBA: penztar biztonsági mentés 1 sikertelen #FV#CS_Penztar::PenztarBevetel" );
      }

      strFile = AnsiString( "Db\\2_" ) + sPenztarFile;
      if( !SaveDataToFile(strFile.c_str()) /*||
          !CheckDataToFile(strFile.c_str())*/ )
      {
         LOG1( "HIBA: penztar biztonsági mentés 2 sikertelen #FV#CS_Penztar::PenztarBevetel" );
      }
   }
   else
   {
      LOG1( "HIBA: penztar mentés sikertelen #FV#CS_Penztar::PenztarBevetel" );
   }
}
//---------------------------------------------------------------------------
void CS_Penztar::PenztarKiadas( typ_user stUser, int nCash, char *strMegjegyzes )
{
   if( stUser.dID )
   {
      SavePenztarCashMod( stUser, ACTION_PENZTAR_KIADAS, nCash, strMegjegyzes );
   }
   Penztar.nCurrentCash -= nCash;

   if( SaveDataToFile(sPenztarFile.c_str()) /*&&
       CheckDataToFile(sPenztarFile.c_str())*/ )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sPenztarFile;
      if( !SaveDataToFile(strFile.c_str()) /*||
          !CheckDataToFile(strFile.c_str())*/ )
      {
         LOG1( "HIBA: penztar biztonsági mentés 1 sikertelen #FV#CS_Penztar::PenztarKiadas" );
      }

      strFile = AnsiString( "Db\\2_" ) + sPenztarFile;
      if( !SaveDataToFile(strFile.c_str()) /*||
          !CheckDataToFile(strFile.c_str())*/ )
      {
         LOG1( "HIBA: penztar biztonsági mentés 2 sikertelen #FV#CS_Penztar::PenztarKiadas" );
      }
   }
   else
   {
      LOG1( "HIBA: penztar mentés sikertelen #FV#CS_Penztar::PenztarKiadas" );
   }
}
//---------------------------------------------------------------------------
int CS_Penztar::GetPenztarNyitas()
{
   return Penztar.nStartingCash;
}
//---------------------------------------------------------------------------
int CS_Penztar::GetPenztarEgyenleg()
{
   return Penztar.nCurrentCash;
}
//---------------------------------------------------------------------------
double CS_Penztar::GetPenztarActionCount()
{
   return PenztarAction.size();
}
//---------------------------------------------------------------------------
typ_penztar_action CS_Penztar::GetPenztarAction( double dCount )
{
   typ_penztar_action  stTemp;

   memset( &stTemp, 0, sizeof(typ_penztar_action) );

   if( dCount < PenztarAction.size() )
      return PenztarAction[dCount];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
void CS_Penztar::DeletePenztarAction( double dDateTime, bool bNeedToSave )
{
   for( unsigned int i=0; i<PenztarAction.size(); i++ )
   {
      if( PenztarAction[i].dDateTime == dDateTime )
      {
         PenztarAction.erase( PenztarAction.begin()+i );
         break;
      }
   }
   if( bNeedToSave )
   {
      if( SavePenztarActions(sPenztarLogFile.c_str()) &&
          CheckPenztarActions(sPenztarLogFile.c_str()) )
      {
         AnsiString strFile;

         strFile = AnsiString( "Db\\1_" ) + sPenztarLogFile;
         if( !SavePenztarActions(strFile.c_str()) ||
             !CheckPenztarActions(strFile.c_str()) )
         {
            LOG1( "HIBA: penztarlog biztonsági mentés 1 sikertelen #FV#CS_Penztar::DeletePenztarAction" );
         }

         strFile = AnsiString( "Db\\2_" ) + sPenztarLogFile;
         if( !SavePenztarActions(strFile.c_str()) ||
             !CheckPenztarActions(strFile.c_str()) )
         {
            LOG1( "HIBA: penztarlog biztonsági mentés 2 sikertelen #FV#CS_Penztar::DeletePenztarAction" );
         }
      }
      else
      {
         LOG1( "HIBA: penztarlog mentés sikertelen #FV#CS_Penztar::DeletePenztarAction" );
      }
   }
}
//---------------------------------------------------------------------------
bool CS_Penztar::SavePenztarActions( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize;
   bool           bRet = true;

   file = fopen( strFile, "wb" );
   if( file != NULL )
   {
      fwrite( PENZTAR_FILE_VERSION, 10, 1, file );

      for( unsigned int i=0; i<PenztarAction.size(); i++ )
      {
         fwrite( &PenztarAction[i], sizeof(typ_penztar_action), 1, file );
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
bool CS_Penztar::CheckPenztarActions( const char *strFile )
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
      if( strcmp( PENZTAR_FILE_VERSION, strTemp ) == 0 )
      {
         // verziószám egyezik
         //
         unsigned int         nCount = 0;
         typ_penztar_action   stTemp;

         // rekord beolvasása
         while( fread( &stTemp, sizeof(typ_penztar_action), 1, file ) )
         {
            if( nCount >= PenztarAction.size() )
            {
               LOG1( "#FV#CS_Penztar::CheckPenztarActions" );
               strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordszam: [" ) +
                           AnsiString( PenztarAction.size() ) +
                           AnsiString( "] [" ) +
                           AnsiString( nCount ) +
                           AnsiString( "]" );
               LOG1( strLogMsg );
               bRet = false;
               break;
            }
            // rekord ellenõrzése
            if( memcmp( &PenztarAction[nCount], &stTemp, sizeof(typ_penztar_action) ) != 0 )
            {
               // rekord nem egyezik
               //
               LOG1( "#FV#CS_Penztar::CheckPenztarActions" );
               strLogMsg = AnsiString( "HIBA: Nem egyezik a rekord: [" ) +
                           AnsiString( nCount ) +
                           AnsiString( "]" );
               LOG1( strLogMsg );
               bRet = false;
               break;
            }
            nCount++;
         }
      }
      else
      {
         // verziószám nem egyezik
         LOG1( "#FV#CS_Penztar::CheckPenztarActions" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( PENZTAR_FILE_VERSION ) +
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

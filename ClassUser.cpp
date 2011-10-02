//---------------------------------------------------------------------------

#include <vcl.h>

#include "Classes.h"
#include "Database.h"
#include "Language.h"
//---------------------------------------------------------------------------
CS_User::CS_User( CS_MainSettings *MainSettings )
{
   typ_userlevel  stTemp;

   sUserFile = USER_FILE;
   pMainSettings = MainSettings;

   LoadDataFromFile();

   strcpy( stTemp.strUserLevel, "" );
   sUserLevel.push_back( stTemp );
   strcpy( stTemp.strUserLevel, "" );
   sUserLevel.push_back( stTemp );
   strcpy( stTemp.strUserLevel, "" );
   sUserLevel.push_back( stTemp );
   strcpy( stTemp.strUserLevel, "" );
   sUserLevel.push_back( stTemp );
   strcpy( stTemp.strUserLevel, "" );
   sUserLevel.push_back( stTemp );
   strcpy( stTemp.strUserLevel, "" );
   sUserLevel.push_back( stTemp );
   strcpy( stTemp.strUserLevel, "" );
   sUserLevel.push_back( stTemp );
   strcpy( stTemp.strUserLevel, FormLanguage->LangStr(STR_OPERATOR).c_str() );
   sUserLevel.push_back( stTemp );
   strcpy( stTemp.strUserLevel, FormLanguage->LangStr(STR_ADMINISTRATOR).c_str() );
   sUserLevel.push_back( stTemp );
   strcpy( stTemp.strUserLevel, FormLanguage->LangStr(STR_SYSTEM_ADMINISTRATOR).c_str() );
   sUserLevel.push_back( stTemp );
}
//---------------------------------------------------------------------------
CS_User::~CS_User()
{
   //SaveDataToFile( sUserFile.c_str() );
}
//---------------------------------------------------------------------------
void CS_User::LoadDataFromFile()
{
   FILE           *file = NULL;
   char           strTemp[10];
   unsigned int   nCount = 0;
   typ_user       stTemp;

   memset( strTemp, 0, sizeof(strTemp) );

   strcpy( stTemp.strAzonosito, ";;<\vq\x0E\x0F\vL\v\v\v\v\v\v\v\vñ\x19\v" );
   strcpy( stTemp.strLoginNev, "ydd\v\x1E\x16PË-1\v·ò\x19\v\bG\x16P" );
   strcpy( stTemp.strNevCsalad, "Yneoxqny+Jofbebxqyêdy\vI\v\v\v\n\v\v\vÒ€=uÛM”\v7\v\v\vñ\x19\v×\f<u½\f<u;~\vJ\x1F\v\v\vÇê”\vKB\vJ\x13ñ\x19\vGi”\v7ñ\x19\vQÅ\rK\x14\v\v\vè\b\v\vëê”\v" );
   strcpy( stTemp.strJelszo, "Hdyine=Ojggjx\v\vJï\vJ" );
   memset( stTemp.strMegjegyzes, 0, sizeof(stTemp.strMegjegyzes) );
   stTemp.nUserLevel = ACCESS_ROOT;
   stTemp.dID = 1;
   DeCode( stTemp.strAzonosito, sizeof(stTemp.strAzonosito) );
   DeCode( stTemp.strLoginNev, sizeof(stTemp.strLoginNev) );
   DeCode( stTemp.strNevCsalad, sizeof(stTemp.strNevCsalad) );
   DeCode( stTemp.strJelszo, sizeof(stTemp.strJelszo) );
   User.push_back( stTemp );

   stTemp.dID = 2;
   strcpy( stTemp.strAzonosito, "Admin" );
   strcpy( stTemp.strLoginNev, FormLanguage->LangStr(STR_ADMINISTRATOR).c_str() );
   strcpy( stTemp.strNevCsalad, FormLanguage->LangStr(STR_ADMINISTRATOR).c_str() );
   strcpy( stTemp.strJelszo, pMainSettings->GetAdminPassword() );
   strcpy( stTemp.strMegjegyzes, FormLanguage->LangStr(STR_DEFAULT_ADMIN_COMMENT).c_str() );
   stTemp.nUserLevel = ACCESS_ADMIN;
   User.push_back( stTemp );

   stTemp.dID = 3;
   strcpy( stTemp.strAzonosito, "User" );
   strcpy( stTemp.strLoginNev, FormLanguage->LangStr(STR_OPERATOR).c_str() );
   strcpy( stTemp.strNevCsalad, FormLanguage->LangStr(STR_OPERATOR).c_str() );
   strcpy( stTemp.strJelszo, pMainSettings->GetUserPassword() );
   strcpy( stTemp.strMegjegyzes, FormLanguage->LangStr(STR_DEFAULT_OPERATOR_COMMENT).c_str() );
   stTemp.nUserLevel = ACCESS_USER;
   User.push_back( stTemp );

   int   nErrorMsgID;

/*   if( !CheckAndCorrectDBFiles( sUserFile.c_str(), &nErrorMsgID ) )
   {
      AnsiString  strMsg;
      strMsg.sprintf( "\n\nError Code: sys112\nError ID: %d", nErrorMsgID );
      throw Exception( strMsg );
   }*/

   file = fopen( sUserFile.c_str(), "rb" );
   if( file != NULL )
   {
      fread( strTemp, 10, 1, file );
      if( strcmp( USER_FILE_VERSION, strTemp ) == 0 )
      {
         fread( &nCount, sizeof(unsigned int), 1, file );

         if( nCount > 0 )
         {
            for( unsigned int i=0; i<nCount; i++ )
            {
               fread( &stTemp, sizeof(typ_user), 1, file );
               DeCode( stTemp.strAzonosito, sizeof(stTemp.strAzonosito) );
               DeCode( stTemp.strLoginNev, sizeof(stTemp.strLoginNev) );
               DeCode( stTemp.strNevCsalad, sizeof(stTemp.strNevCsalad) );
               DeCode( stTemp.strJelszo, sizeof(stTemp.strJelszo) );
               DeCode( stTemp.strMegjegyzes, sizeof(stTemp.strMegjegyzes) );
               User.push_back( stTemp );
            }
         }
      }
      else
      {
         LOG1( "#FV#CS_User::LoadDataFromFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( USER_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }
      fclose( file );
   }
}
//---------------------------------------------------------------------------
bool CS_User::SaveDataToFile( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize;
   bool           bRet = true;

   if( (file = fopen( strFile, "wb" )) != NULL )
   {
      fwrite( USER_FILE_VERSION, 10, 1, file );

      nSize = User.size()-3;
      fwrite( &nSize, sizeof(unsigned int), 1, file );
      for( unsigned int i=0; i<User.size(); i++ )
      {
         if( User[i].dID > 3 )
         {
            EnCode( User[i].strAzonosito, sizeof(User[i].strAzonosito) );
            EnCode( User[i].strLoginNev, sizeof(User[i].strLoginNev) );
            EnCode( User[i].strNevCsalad, sizeof(User[i].strNevCsalad) );
            EnCode( User[i].strJelszo, sizeof(User[i].strJelszo) );
            EnCode( User[i].strMegjegyzes, sizeof(User[i].strMegjegyzes) );
            fwrite( &User[i], sizeof(typ_user), 1, file );
            DeCode( User[i].strAzonosito, sizeof(User[i].strAzonosito) );
            DeCode( User[i].strLoginNev, sizeof(User[i].strLoginNev) );
            DeCode( User[i].strNevCsalad, sizeof(User[i].strNevCsalad) );
            DeCode( User[i].strJelszo, sizeof(User[i].strJelszo) );
            DeCode( User[i].strMegjegyzes, sizeof(User[i].strMegjegyzes) );
         }
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
bool CS_User::CheckDataToFile( const char *strFile )
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
      if( strcmp( USER_FILE_VERSION, strTemp ) == 0 )
      {
         // verziószám egyezik
         //
         unsigned int   nCount = 0;
         // rekordok számának kiolvasása
         fread( &nCount, sizeof(unsigned int), 1, file );
         if( nCount != User.size()-3 )
         {
            // rekordok száma nem egyezik
            //
            LOG1( "#FV#CS_User::CheckDataToFile" );
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekordszám: [" ) +
                        AnsiString( nCount ) +
                        AnsiString( "] [" ) +
                        AnsiString( User.size() ) +
                        AnsiString( "]" );
            LOG1( strLogMsg );
            bRet = false;
         }
         if( nCount > 0 && bRet )
         {
            // rekordok száma egyezik és van adat
            //
            typ_user   stTemp;
            for( i=0; i<nCount; i++ )
            {
               // rekord beolvasása
               fread( &stTemp, sizeof(typ_user), 1, file );
               // szöveg dekódolása
               DeCode( stTemp.strAzonosito, sizeof(stTemp.strAzonosito) );
               DeCode( stTemp.strLoginNev, sizeof(stTemp.strLoginNev) );
               DeCode( stTemp.strNevCsalad, sizeof(stTemp.strNevCsalad) );
               DeCode( stTemp.strJelszo, sizeof(stTemp.strJelszo) );
               DeCode( stTemp.strMegjegyzes, sizeof(stTemp.strMegjegyzes) );
               // rekord ellenõrzése
               if( memcmp( &User[i+3], &stTemp, sizeof(typ_user) ) != 0 )
               {
                  // rekord nem egyezik
                  //
                  LOG1( "#FV#CS_User::CheckDataToFile" );
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
         LOG1( "#FV#CS_User::CheckDataToFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verziószám: [" ) +
                     AnsiString( USER_FILE_VERSION ) +
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
void CS_User::AddUser( typ_user stTemp )
{
   double i;
   for( i=1; ; i++ )
   {
      typ_user stTmp = GetUserID( i );
      if( stTmp.dID == 0 )
         break;
   }
   stTemp.dID = i;

   User.push_back( stTemp );

   if( SaveDataToFile(sUserFile.c_str()) &&
       CheckDataToFile(sUserFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sUserFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: user biztonsági mentés 1 sikertelen #FV#CS_User::AddUser" );
      }

      strFile = AnsiString( "Db\\2_" ) + sUserFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: user biztonsági mentés 2 sikertelen #FV#CS_User::AddUser" );
      }
   }
   else
   {
      LOG1( "HIBA: user mentés sikertelen#FV#CS_User::AddUser" );
   }
}
//---------------------------------------------------------------------------
bool CS_User::ModifyUser( typ_user stTemp )
{
   double i;

   for( i=0; i<User.size(); i++ )
   {
      if( strcmp(User[i].strLoginNev, stTemp.strLoginNev) == 0 )
      {
         strcpy( User[i].strAzonosito, stTemp.strAzonosito );
         strcpy( User[i].strLoginNev, stTemp.strLoginNev );
         strcpy( User[i].strNevCsalad, stTemp.strNevCsalad );
         strcpy( User[i].strJelszo, stTemp.strJelszo );
         strcpy( User[i].strMegjegyzes, stTemp.strMegjegyzes );
         User[i].nUserLevel = stTemp.nUserLevel;
         break;
      }
   }

   if( SaveDataToFile(sUserFile.c_str()) &&
       CheckDataToFile(sUserFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sUserFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: user biztonsági mentés 1 sikertelen #FV#CS_User::ModifyUser" );
      }

      strFile = AnsiString( "Db\\2_" ) + sUserFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: user biztonsági mentés 2 sikertelen #FV#CS_User::ModifyUser" );
      }
   }
   else
   {
      LOG1( "HIBA: user mentés sikertelen #FV#CS_User::ModifyUser" );
   }

   if( i == User.size() )
      return false;
   else
      return true;
}
//---------------------------------------------------------------------------
bool CS_User::DeleteUser( char *strLoginNev )
{
   unsigned int i;

   for( i=0; i<User.size(); i++ )
   {
      if( strcmpi(User[i].strLoginNev, strLoginNev) == 0 )
      {
         User.erase( User.begin()+i );
         break;
      }
   }

   if( SaveDataToFile(sUserFile.c_str()) &&
       CheckDataToFile(sUserFile.c_str()) )
   {
      AnsiString strFile;

      strFile = AnsiString( "Db\\1_" ) + sUserFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: user biztonsági mentés 1 sikertelen #FV#CS_User::DeleteUser" );
      }

      strFile = AnsiString( "Db\\2_" ) + sUserFile;
      if( !SaveDataToFile(strFile.c_str()) ||
          !CheckDataToFile(strFile.c_str()) )
      {
         LOG1( "HIBA: user biztonsági mentés 2 sikertelen #FV#CS_User::DeleteUser" );
      }
   }
   else
   {
      LOG1( "HIBA: user mentés sikertelen #FV#CS_User::DeleteUser" );
   }

   if( i == User.size() )
      return false;
   else
      return true;
}
//---------------------------------------------------------------------------
typ_user CS_User::GetUserItem( double dCount )
{
   typ_user  stTemp;

   memset( &stTemp, 0, sizeof(typ_user) );

   if( dCount < User.size() )
      return User[dCount];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
typ_user CS_User::GetUserID( double dID )
{
   int i;
   typ_user   stTemp;

   memset(&stTemp, 0, sizeof(typ_user) );

   for(i=0;i<(int)User.size();i++)
   {
      if( User[i].dID == dID )
         break;
   }

   if( i < (int)User.size() )
      return User[i];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
typ_user CS_User::GetUserLogin( char *strLoginNev )
{
   typ_user stTemp;
   double i;

   memset( &stTemp, 0, sizeof(typ_user) );

   for( i=0; i<User.size(); i++ )
   {
      if( strcmpi( User[i].strLoginNev, strLoginNev) == 0 )
      {
         break;
      }
   }

   if( i < User.size() )
      return User[i];
   else
      return stTemp;
}
//---------------------------------------------------------------------------
double CS_User::GetUserCount()
{
   return User.size();
}
//---------------------------------------------------------------------------
char* CS_User::GetUserNev( char *strLoginNev )
{
   typ_user stTemp = GetUserLogin( strLoginNev );

   return stTemp.strNevCsalad;
}
//---------------------------------------------------------------------------
int CS_User::GetUserLevel( char *strLoginNev )
{
   typ_user stTemp = GetUserLogin( strLoginNev );

   return stTemp.nUserLevel;
}
//---------------------------------------------------------------------------
char* CS_User::GetUserLevelStr( char *strLoginNev )
{
   typ_user stTemp = GetUserLogin( strLoginNev );

   return sUserLevel[stTemp.nUserLevel].strUserLevel;
}
//---------------------------------------------------------------------------

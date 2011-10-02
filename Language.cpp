//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormLanguage *FormLanguage;
//---------------------------------------------------------------------------
__fastcall TFormLanguage::TFormLanguage(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
AnsiString TFormLanguage::LangStr( int LangId )
{
   char  s[1000];

   memset(s,0,sizeof(s));

   if( LangId > 0 )
   {
      strncpy(s,LstLanguage->Items->Strings[ LangId-1 ].c_str(), 999);

      for( int i=0;i<(int)strlen(s)-1;i++ )
      {
         if( s[i] == '\\' && s[i+1] == 'n' )
         {
            s[i] = ' ';
            s[i+1] = '\n';
         }
         if( s[i] == '\\' && s[i+1] == 'r' )
         {
            s[i] = ' ';
            s[i+1] = '\r';
         }
      }
   }
   return AnsiString(s);
}
//---------------------------------------------------------------------------

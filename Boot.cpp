//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Boot.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormBoot *FormBoot;
//---------------------------------------------------------------------------
__fastcall TFormBoot::TFormBoot(TComponent* Owner)
   : TForm(Owner)
{
   nLine = 0;
}
//---------------------------------------------------------------------------
void __fastcall TFormBoot::FormActivate(TObject *Sender)
{
   strLogLine = FormLanguage->LangStr(STR_APPLICATION_START);
   AddBootMessage();
}
//---------------------------------------------------------------------------
void TFormBoot::AddBootMessage( bool bOverwrite )
{
   if( bOverwrite )
   {
      BootDisplay->Lines->Delete( nLine );
   }
   nLine = BootDisplay->Lines->Add( strLogLine );
   Update();
}
//---------------------------------------------------------------------------

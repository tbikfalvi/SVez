//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RendszerAdmin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSystemAdmin *SystemAdmin;
//---------------------------------------------------------------------------
__fastcall TSystemAdmin::TSystemAdmin(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSystemAdmin::FormActivate(TObject *Sender)
{
   //   
}
//---------------------------------------------------------------------------
void __fastcall TSystemAdmin::BtnCodeClick(TObject *Sender)
{
   char  strTemp[1000];

   memset( strTemp, 0, sizeof(strTemp) );
   strncpy( strTemp, EditKod->Text.c_str(), sizeof(strTemp) );
   pMainSettings->DeCode( strTemp, sizeof(strTemp) );
   EditKod->Text = AnsiString( strTemp );
}
//---------------------------------------------------------------------------

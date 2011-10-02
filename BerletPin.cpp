//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BerletPin.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormBerletPIN *FormBerletPIN;
//---------------------------------------------------------------------------
__fastcall TFormBerletPIN::TFormBerletPIN(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormBerletPIN::FormActivate(TObject *Sender)
{
   EditPIN->Text = "";
   EditPIN->Height = 32;
   EditPIN->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormBerletPIN::EditPINChange(TObject *Sender)
{
   if( EditPIN->Text.Length() == 0 )
      return;
      
   try
   {
      EditPIN->Text.ToInt();
   }
   catch(const Exception& e)
   {
      AnsiString eMessage = FormLanguage->LangStr(STR_MSG_USENUMBERONLY);
      Application->MessageBox( eMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      return;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormBerletPIN::BitBtnOkClick(TObject *Sender)
{
   if( EditPIN->Text.Length() != 4 )
   {
      AnsiString eMessage = FormLanguage->LangStr(STR_PIN_MUST_4_DIGIT);
      Application->MessageBox( eMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      ModalResult = mrNone;
   }
   else
   {
      ModalResult = mrOk;
   }
}
//---------------------------------------------------------------------------

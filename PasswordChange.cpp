//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Classes.h"
#include "Database.h"
#include "PasswordChange.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPasswordChange *FormPasswordChange;
//---------------------------------------------------------------------------
__fastcall TFormPasswordChange::TFormPasswordChange(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormPasswordChange::FormActivate(TObject *Sender)
{
   if( EditOldPassword->Text.Length() == 0 )
   {
      Edit1->Enabled = false;
      Edit1->Visible = false;
      Edit2->SetFocus();
   }
   else
   {
      Edit1->Enabled = true;
      Edit1->Visible = true;
      Edit1->SetFocus();
   }
   Edit1->Text = "";
   Edit2->Text = "";
   Edit3->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TFormPasswordChange::BitBtnOkClick(TObject *Sender)
{
   if( Edit1->Text.AnsiCompare( EditOldPassword->Text ) != 0 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_INVALID_OLDPASS).c_str(), FormLanguage->LangStr(STR_MSGBOX_USERERROR).c_str(), MB_ICONEXCLAMATION );
      Edit1->SetFocus();
      return;
   }
   if( Edit2->Text.Length() == 0 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_MISSING_NEWPASS).c_str(), FormLanguage->LangStr(STR_MSGBOX_USERERROR).c_str(), MB_ICONEXCLAMATION );
      Edit2->SetFocus();
      return;
   }
   if( Edit3->Text.Length() == 0 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_MISSING_NEWPASS).c_str(), FormLanguage->LangStr(STR_MSGBOX_USERERROR).c_str(), MB_ICONEXCLAMATION );
      Edit3->SetFocus();
      return;
   }
   if( Edit2->Text != Edit3->Text )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_TYPOERR_NEWPASS).c_str(), FormLanguage->LangStr(STR_MSGBOX_USERERROR).c_str(), MB_ICONEXCLAMATION );
      Edit2->SetFocus();
      return;
   }
   
   ModalResult = mrOk;
}
//---------------------------------------------------------------------------

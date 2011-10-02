//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DialogComment.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormCommentDialog *FormCommentDialog;
//---------------------------------------------------------------------------
__fastcall TFormCommentDialog::TFormCommentDialog(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormCommentDialog::FormActivate(TObject *Sender)
{
   memset( strMegjegyzes, 0, sizeof(strMegjegyzes) );
   MemoComment->Clear();
   MemoComment->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormCommentDialog::FormShortCut(TWMKey &Msg, bool &Handled)
{
   if (Msg.CharCode == VK_RETURN)
   {
      Handled = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormCommentDialog::BitBtnOkClick(TObject *Sender)
{
   strncpy( strMegjegyzes, MemoComment->Text.c_str(), sizeof(strMegjegyzes)-2 );
}
//---------------------------------------------------------------------------

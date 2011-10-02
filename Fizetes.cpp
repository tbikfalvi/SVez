//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Fizetes.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormFizetes *FormFizetes;
//---------------------------------------------------------------------------
__fastcall TFormFizetes::TFormFizetes(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormFizetes::FormActivate(TObject *Sender)
{
   bNeedToCheck = true;
   EditFizetett->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormFizetes::FormShortCut(TWMKey &Msg, bool &Handled)
{
//   if (Msg.CharCode == VK_RETURN)
//   {
//      Handled = true;
//   }
}
//---------------------------------------------------------------------------
void __fastcall TFormFizetes::EditFizetettChange(TObject *Sender)
{
   if( !bNeedToCheck || EditFizetett->Text.Length() == 0 )
      return;

   try
   {
      int nFizetendo  = LabelFizetendo->Caption.ToInt();
      int nFizetett   = EditFizetett->Text.ToInt();
      int nVisszajaro = nFizetett - nFizetendo;

      if( nFizetett > nFizetendo )
      {
         LabelVisszajaro->Caption = AnsiString( nVisszajaro );
      }
      else
      {
         LabelVisszajaro->Caption = AnsiString( 0 );
      }
   }
   catch(const Exception& e)
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_USENUMBERONLY).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormFizetes::BitBtnOkClick(TObject *Sender)
{
   bNeedToCheck = false;

   EditFizetett->Text       = "";
   LabelFizetendo->Caption  = "";
   LabelVisszajaro->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall TFormFizetes::BitBtnKosarClick(TObject *Sender)
{
   bNeedToCheck = false;

   EditFizetett->Text       = "";
   LabelFizetendo->Caption  = "";
   LabelVisszajaro->Caption = "";
}
//---------------------------------------------------------------------------

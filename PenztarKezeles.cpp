//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PenztarKezeles.h"
#include "DialogInput.h"
#include "DialogComment.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPenztarKezeles *FormPenztarKezeles;
//---------------------------------------------------------------------------
__fastcall TFormPenztarKezeles::TFormPenztarKezeles(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormPenztarKezeles::FormActivate(TObject *Sender)
{
   LabelCash->Caption = AnsiString( pPenztar->GetPenztarEgyenleg() );

   stUser = pUser->GetUserLogin( pMainSettings->GetCurrentUser() );
   BitBtnPlus->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormPenztarKezeles::BitBtnPlusClick(TObject *Sender)
{
   FormInputDialog->Caption = FormLanguage->LangStr(STR_CAPTION_PAYTOCASSA);
   FormInputDialog->LabelText->Caption = FormLanguage->LangStr(STR_TOTALCASH_INCOME);
   FormInputDialog->EditText->Text = "";
   if( FormInputDialog->ShowModal() == mrOk )
   {
      try
      {
         FormInputDialog->EditText->Text.ToInt();
      }
      catch(const Exception& e)
      {
         AnsiString eMessage;
         eMessage.sprintf( FormLanguage->LangStr(STR_INVALID_NUMBER_ENTERED).c_str(), FormInputDialog->EditText->Text.c_str() );
         Application->MessageBox( eMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
         return;
      }
/*
      if( pPenztar->GetPenztarEgyenleg() == 0 )
      {
         pPenztar->PenztarNyitas( stUser, 0 );
      }
*/
      if( FormCommentDialog->ShowModal() == mrOk )
      {
         pPenztar->PenztarBevetel( stUser,
                                   FormInputDialog->EditText->Text.ToInt(),
                                   FormCommentDialog->strMegjegyzes );
      }
      else
      {
         pPenztar->PenztarBevetel( stUser,
                                   FormInputDialog->EditText->Text.ToInt(),
                                   FormLanguage->LangStr(STR_NO_COMMENT).c_str() );
      }
      pPenztar->strLogMsg = AnsiString( "Penztar feltoltese [" ) +
                            AnsiString( FormInputDialog->EditText->Text ) +
                            AnsiString( "]" );
      pPenztar->LOG2( pPenztar->strLogMsg );

      LabelCash->Caption = AnsiString( pPenztar->GetPenztarEgyenleg() );
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormPenztarKezeles::BitBtnMinusClick(TObject *Sender)
{
   FormInputDialog->Caption = FormLanguage->LangStr(STR_CAPTION_GETFROMCASSA);
   FormInputDialog->LabelText->Caption = FormLanguage->LangStr(STR_TOTALCASH_OUTCOME);
   FormInputDialog->EditText->Text = "";
   if( FormInputDialog->ShowModal() == mrOk )
   {
      try
      {
         FormInputDialog->EditText->Text.ToInt();
      }
      catch(const Exception& e)
      {
         AnsiString eMessage;
         eMessage.sprintf( FormLanguage->LangStr(STR_INVALID_NUMBER_ENTERED).c_str(), FormInputDialog->EditText->Text.c_str() );
         Application->MessageBox( eMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
         return;
      }
      if( FormCommentDialog->ShowModal() == mrOk )
      {
         pPenztar->PenztarKiadas( stUser,
                                  FormInputDialog->EditText->Text.ToInt(),
                                  FormCommentDialog->strMegjegyzes );
      }
      else
      {
         pPenztar->PenztarKiadas( stUser,
                                  FormInputDialog->EditText->Text.ToInt(),
                                  FormLanguage->LangStr(STR_NO_COMMENT).c_str() );
      }
      pPenztar->strLogMsg = AnsiString( "Penztar csokkentese [" ) +
                            AnsiString( FormInputDialog->EditText->Text ) +
                            AnsiString( "]" );
      pPenztar->LOG2( pPenztar->strLogMsg );

      LabelCash->Caption = AnsiString( pPenztar->GetPenztarEgyenleg() );
   }
}
//---------------------------------------------------------------------------

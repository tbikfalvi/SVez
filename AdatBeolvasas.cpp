//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AdatBeolvasas.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDataRead *FormDataRead;
//---------------------------------------------------------------------------
__fastcall TFormDataRead::TFormDataRead(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormDataRead::FormActivate(TObject *Sender)
{
   LabelInfo->Caption = FormLanguage->LangStr(STR_CAPTION_DATAREAD);
   EditAdat->SetFocus();
   EditAdat->SelStart = EditAdat->Text.Length();
   CheckTypedValue();
}
//---------------------------------------------------------------------------
void __fastcall TFormDataRead::EditAdatChange(TObject *Sender)
{
   EditAdat->Text = EditAdat->Text.UpperCase();
   EditAdat->SelStart = EditAdat->Text.Length();
   CheckTypedValue();
}
//---------------------------------------------------------------------------
void TFormDataRead::CheckTypedValue()
{
   if( EditAdat->Text.Length() > 3 )
   {
      LabelInfo->Caption = FormLanguage->LangStr(STR_CAPTION_VONALKOD_READ);
      nAction = ACTION_VONALKOD;
   }
   else if( EditAdat->Text.Length() < 4 )
   {
      LabelInfo->Caption = FormLanguage->LangStr(STR_CAPTION_SOLTIME);
      nAction = ACTION_BARNULASIDO;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormDataRead::BitBtnOkClick(TObject *Sender)
{
   AnsiString  strTemp;

   switch( nAction )
   {
      case ACTION_BARNULASIDO:
      {
         try
         {
            int nBarnulas = EditAdat->Text.ToInt()+(pSzolarium->GetBarnulasIdo()/60);
            if( nBarnulas > pSzolarium->GetMaxBarnulas() )
            {
               AnsiString eMessage = FormLanguage->LangStr(STR_MSG_SOLTIME_OVERFLOW);
               Application->MessageBox( eMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
               ModalResult = mrNone;
               return;
            }
         }
         catch(const Exception& e)
         {
            AnsiString eMessage;
            eMessage.sprintf( FormLanguage->LangStr(STR_MSG_INVALID_SOLTIME_VALUE).c_str(), EditAdat->Text.c_str() );
            Application->MessageBox( eMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
            ModalResult = mrNone;
            return;
         }
         break;
      }
   }
   ModalResult = mrOk;
}
//---------------------------------------------------------------------------

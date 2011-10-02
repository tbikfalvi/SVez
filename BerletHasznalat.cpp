//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BerletHasznalat.h"
#include "BerletPin.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormBerletHasznalat *FormBerletHasznalat;
//---------------------------------------------------------------------------
__fastcall TFormBerletHasznalat::TFormBerletHasznalat(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormBerletHasznalat::FormActivate(TObject *Sender)
{
   stBTipus = pBerlet->GetBerletTipusID( stBerlet.nBerletTipus );

   EditMegjegyzes->Text = AnsiString( stBerlet.strMegjegyzes );
   EditTipus->Text      = AnsiString( stBTipus.strNev );
   EditEgyseg->Text     = AnsiString( stBerlet.nEgyseg );
   EditErvenyes->Text   = AnsiString( stBerlet.nErvEv )+
                                      AnsiString( "/" )+
                                      AnsiString( stBerlet.nErvHo )+
                                      AnsiString( "/" )+
                                      AnsiString( stBerlet.nErvNap );
   ComboBoxHasznalat->Clear();

   TDateTime   currDate = Now();
   TDateTime   ervDate = TDateTime( stBerlet.nErvEv, stBerlet.nErvHo,stBerlet.nErvNap );

   if( stBerlet.nEgyseg > 0 )
   {
      ComboBoxHasznalat->Enabled = true;
      BitBtnOk->Enabled = true;
      for( int i=1; i<stBerlet.nEgyseg+1; i++ )
      {
         ComboBoxHasznalat->Items->Add( AnsiString( i ) );
      }
      ComboBoxHasznalat->ItemIndex = 0;
      ComboBoxHasznalat->SetFocus();

      if( currDate > ervDate )
      {
         ComboBoxHasznalat->Enabled = false;
         BitBtnOk->Enabled = false;
         Application->MessageBox( FormLanguage->LangStr(STR_CARD_DATE_EXPIRED).c_str(), FormLanguage->LangStr(STR_MSGBOX_INFORMATION).c_str(), MB_ICONEXCLAMATION );
         if( currDate > ervDate+61 )
            pBerlet->DeleteBerlet( stBerlet.strVonalkod );
         BitBtnCancel->SetFocus();
      }
      else
      {
         ComboBoxHasznalat->Enabled = true;
         BitBtnOk->Enabled = true;
         ComboBoxHasznalat->SetFocus();
      }
   }
   else
   {
      ComboBoxHasznalat->Enabled = false;
      BitBtnOk->Enabled = false;
      Application->MessageBox( FormLanguage->LangStr(STR_CARD_NOMORE_UNIT).c_str(), FormLanguage->LangStr(STR_MSGBOX_INFORMATION).c_str(), MB_ICONEXCLAMATION );
      if( currDate > ervDate+61 )
         pBerlet->DeleteBerlet( stBerlet.strVonalkod );
      BitBtnCancel->SetFocus();
   }
   ComboBoxHasznalat->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormBerletHasznalat::BitBtnOkClick(TObject *Sender)
{
   if( pMainSettings->GetBoolValueFromRegistry( "IsPINCodeNeeded", false ) )
   {
      FormBerletPIN->ShowModal();
      if( FormBerletPIN->EditPIN->Text.ToInt() != stBerlet.nPin )
      {
         AnsiString eMessage = FormLanguage->LangStr(STR_PIN_INVALID);
         Application->MessageBox( eMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
         ModalResult = mrNone;
      }
      else
      {
         ModalResult = mrOk;
      }
   }
   else
   {
      ModalResult = mrOk;
   }
}
//---------------------------------------------------------------------------



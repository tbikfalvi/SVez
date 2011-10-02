//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TermekEladas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTermekEladas *FormTermekEladas;
//---------------------------------------------------------------------------
__fastcall TFormTermekEladas::TFormTermekEladas(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekEladas::FormActivate(TObject *Sender)
{
   EditID->Text = AnsiString( stTermek.nID );
   EditNev->Text = AnsiString( stTermek.strNev );
   EditVonalkod->Text = AnsiString( stTermek.strVonalkod );
   EditAr->Text = AnsiString( stTermek.nAr );
   EditDarab->Text = AnsiString( stTermek.nDarab );

   ComboBoxDarab->Clear();
   for( int i=0; i<stTermek.nDarab; i++ )
   {
      ComboBoxDarab->Items->Add( AnsiString(i+1) );
   }
   if( stTermek.nDarab == 0 )
   {
      BitBtnOk->Enabled = false;
      BitBtnKosar->Enabled = false;
   }
   else if( stTermek.nDarab > 0 )
   {
      BitBtnOk->Enabled = true;
      BitBtnKosar->Enabled = true;
   }
   ComboBoxDarab->ItemIndex = 0;
   EditFizetendo->Text = AnsiString( stTermek.nAr );
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekEladas::FormShortCut(TWMKey &Msg, bool &Handled)
{
   if (Msg.CharCode == VK_RETURN)
   {
      Handled = true;
      if( BitBtnOk->Enabled )
      {
         ModalResult = mrOk;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekEladas::ComboBoxDarabChange(TObject *Sender)
{
   int nDarab = ComboBoxDarab->Items->Strings[ComboBoxDarab->ItemIndex].ToInt();
   int nAr = EditAr->Text.ToInt();

   EditFizetendo->Text = AnsiString( nDarab*nAr );
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DialogInput.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormInputDialog *FormInputDialog;
//---------------------------------------------------------------------------
__fastcall TFormInputDialog::TFormInputDialog(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormInputDialog::FormActivate(TObject *Sender)
{
   EditText->SetFocus();   
}
//---------------------------------------------------------------------------


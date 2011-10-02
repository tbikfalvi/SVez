//---------------------------------------------------------------------------

#ifndef DialogInputH
#define DialogInputH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormInputDialog : public TForm
{
__published:	// IDE-managed Components
   TLabel *LabelText;
   TEdit *EditText;
   TBitBtn *BitBtnCancel;
   TBitBtn *BitBtnOk;
   void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormInputDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInputDialog *FormInputDialog;
//---------------------------------------------------------------------------
#endif

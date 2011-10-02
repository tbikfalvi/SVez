//---------------------------------------------------------------------------

#ifndef BerletPinH
#define BerletPinH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormBerletPIN : public TForm
{
__published:	// IDE-managed Components
   TLabel *Label1;
   TEdit *EditPIN;
   TBitBtn *BitBtnOk;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall EditPINChange(TObject *Sender);
   void __fastcall BitBtnOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormBerletPIN(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBerletPIN *FormBerletPIN;
//---------------------------------------------------------------------------
#endif

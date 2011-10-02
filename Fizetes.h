//---------------------------------------------------------------------------

#ifndef FizetesH
#define FizetesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormFizetes : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TLabel *Label1;
   TLabel *LabelFizetendo;
   TLabel *Label3;
   TLabel *Label2;
   TLabel *Label4;
   TLabel *Label5;
   TLabel *Label6;
   TLabel *LabelVisszajaro;
   TLabel *Label8;
   TLabel *Label7;
   TEdit *EditFizetett;
   TLabel *Label9;
   TBitBtn *BitBtnOk;
   TBitBtn *BitBtnKosar;
   TBitBtn *BitBtnCancel;
   void __fastcall EditFizetettChange(TObject *Sender);
   void __fastcall BitBtnOkClick(TObject *Sender);
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall BitBtnKosarClick(TObject *Sender);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
private:	// User declarations
public:		// User declarations
   __fastcall TFormFizetes(TComponent* Owner);

   bool bNeedToCheck;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormFizetes *FormFizetes;
//---------------------------------------------------------------------------
#endif

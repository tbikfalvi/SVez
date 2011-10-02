//---------------------------------------------------------------------------

#ifndef SzolariumInitMainH
#define SzolariumInitMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TLabel *Label1;
   TEdit *EditSzoliCount;
   TBitBtn *BitBtnOk;
   void __fastcall BitBtnOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormMain(TComponent* Owner);

   void EnCode( char *str, int size );
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif

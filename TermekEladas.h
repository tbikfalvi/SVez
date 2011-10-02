//---------------------------------------------------------------------------

#ifndef TermekEladasH
#define TermekEladasH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>

//#include "ClassTermek.h"
#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
class TFormTermekEladas : public TForm
{
__published:	// IDE-managed Components
   TBitBtn *BitBtnOk;
   TBitBtn *BitBtnKosar;
   TBitBtn *BitBtnCancel;
   TGroupBox *GroupBox1;
   TLabel *Label1;
   TEdit *EditNev;
   TLabel *Label2;
   TEdit *EditVonalkod;
   TLabel *Label3;
   TEdit *EditAr;
   TLabel *Label4;
   TEdit *EditDarab;
   TGroupBox *GroupBox2;
   TLabel *Label5;
   TComboBox *ComboBoxDarab;
   TEdit *EditFizetendo;
   TLabel *Label6;
   TEdit *EditID;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall ComboBoxDarabChange(TObject *Sender);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
private:	// User declarations
public:		// User declarations
   __fastcall TFormTermekEladas(TComponent* Owner);

   typ_termek stTermek;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTermekEladas *FormTermekEladas;
//---------------------------------------------------------------------------
#endif

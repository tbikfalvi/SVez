//---------------------------------------------------------------------------

#ifndef TermekListaEladasH
#define TermekListaEladasH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------

//#include "ClassTermek.h"
#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
class TFormTermekListaEladas : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TStringGrid *StringGridTermek;
   TEdit *EditSearchNev;
   TEdit *EditSearchVonalkod;
   TBitBtn *BitBtnOk;
   TBitBtn *BitBtnKosar;
   TBitBtn *BitBtnCancel;
   TGroupBox *GroupBox2;
   TLabel *Label5;
   TLabel *Label6;
   TComboBox *ComboBoxDarab;
   TEdit *EditFizetendo;
   TGroupBox *GroupBox3;
   TLabel *Label1;
   TEdit *EditNev;
   TEdit *EditVonalkod;
   TEdit *EditAr;
   TEdit *EditDarab;
   TEdit *EditID;
   TBitBtn *BitBtnSortCode;
   TBitBtn *BitBtnSortName;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall StringGridTermekClick(TObject *Sender);
   void __fastcall EditSearchNevChange(TObject *Sender);
   void __fastcall EditSearchVonalkodChange(TObject *Sender);
   void __fastcall ComboBoxDarabChange(TObject *Sender);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
   void __fastcall BitBtnSortNameClick(TObject *Sender);
   void __fastcall BitBtnSortCodeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormTermekListaEladas(TComponent* Owner);

   CS_Termek   *pTermek;
   typ_termek   stTermek;

   bool bFizetesEnabled;

   void FillListTermekek( TObject *Sender );
   void SortListTermekek( int nCell );
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTermekListaEladas *FormTermekListaEladas;
//---------------------------------------------------------------------------
#endif

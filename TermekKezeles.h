//---------------------------------------------------------------------------

#ifndef TermekKezelesH
#define TermekKezelesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------

#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
class TFormTermekKezeles : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TBitBtn *BitBtnOk;
   TStringGrid *StringGridTermek;
   TGroupBox *GroupBox2;
   TLabel *Label1;
   TEdit *EditNev;
   TLabel *Label2;
   TEdit *EditVonalkod;
   TLabel *Label3;
   TEdit *EditAr;
   TLabel *Label4;
   TEdit *EditDarab;
   TBitBtn *BitBtnSaveModify;
   TBitBtn *BitBtnModify;
   TBitBtn *BitBtnDelete;
   TBitBtn *BitBtnNew;
   TBitBtn *BitBtnCancel;
   TEdit *EditID;
   TEdit *EditSearchNev;
   TEdit *EditSearchVonalkod;
   TBitBtn *BitBtnPlus;
   TBitBtn *BitBtnMinus;
   TLabel *Label5;
   TLabel *Label6;
   TListBox *ListBoxAssigned;
   TBitBtn *BitBtnAdd;
   TBitBtn *BitBtnRemove;
   TListBox *ListBoxAll;
   TLabel *Label7;
   TEdit *EditArBeszerzes;
   TBitBtn *BitBtnSortName;
   TBitBtn *BitBtnSortCode;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall BitBtnNewClick(TObject *Sender);
   void __fastcall BitBtnModifyClick(TObject *Sender);
   void __fastcall BitBtnDeleteClick(TObject *Sender);
   void __fastcall BitBtnSaveModifyClick(TObject *Sender);
   void __fastcall BitBtnCancelClick(TObject *Sender);
   void __fastcall StringGridTermekClick(TObject *Sender);
   void __fastcall EditSearchNevChange(TObject *Sender);
   void __fastcall EditSearchVonalkodChange(TObject *Sender);
   void __fastcall BitBtnOkClick(TObject *Sender);
   void __fastcall BitBtnPlusClick(TObject *Sender);
   void __fastcall BitBtnMinusClick(TObject *Sender);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
   void __fastcall EditVonalkodExit(TObject *Sender);
   void __fastcall BitBtnAddClick(TObject *Sender);
   void __fastcall BitBtnRemoveClick(TObject *Sender);
   void __fastcall BitBtnSortNameClick(TObject *Sender);
   void __fastcall BitBtnSortCodeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormTermekKezeles(TComponent* Owner);

   CS_Berlet   *pBerlet;
   CS_Termek   *pTermek;
   CS_TermekTipus    *pTermekTipus;

   void FillListTermekek( TObject *Sender );
   void SelectTermekInList( DWORD nID );
   void SortListTermekek( int nCell );
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTermekKezeles *FormTermekKezeles;
//---------------------------------------------------------------------------
#endif

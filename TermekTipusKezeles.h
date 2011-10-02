//---------------------------------------------------------------------------

#ifndef TermekTipusKezelesH
#define TermekTipusKezelesH
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
class TFormTermekTipus : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBoxTermekTipusok;
   TBitBtn *ButtonTTNew;
   TBitBtn *ButtonTTDelete;
   TStringGrid *StringGridTermekTipus;
   TBitBtn *ButtonTTModify;
   TGroupBox *GroupBoxTermekTipus;
   TLabel *Label1;
   TEdit *EditTTNev;
   TBitBtn *ButtonTTSave;
   TEdit *EditTTID;
   TBitBtn *ButtonTTCancel;
   TBitBtn *BitBtnOk;
   TLabel *Label2;
   TListBox *ListBoxAssigned;
   TLabel *Label3;
   TListBox *ListBoxAll;
   TBitBtn *BitBtnAdd;
   TBitBtn *BitBtnRemove;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
   void __fastcall BitBtnOkClick(TObject *Sender);
   void __fastcall ButtonTTNewClick(TObject *Sender);
   void __fastcall ButtonTTModifyClick(TObject *Sender);
   void __fastcall ButtonTTDeleteClick(TObject *Sender);
   void __fastcall StringGridTermekTipusClick(TObject *Sender);
   void __fastcall ButtonTTCancelClick(TObject *Sender);
   void __fastcall ButtonTTSaveClick(TObject *Sender);
   void __fastcall BitBtnAddClick(TObject *Sender);
   void __fastcall BitBtnRemoveClick(TObject *Sender);
private:	// User declarations

public:		// User declarations
   __fastcall TFormTermekTipus(TComponent* Owner);

   CS_TermekTipus    *pTermekTipus;
   CS_Termek         *pTermek;

   void FillListTermekTipusok();
   bool AdatEllenorzes();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTermekTipus *FormTermekTipus;
//---------------------------------------------------------------------------
#endif

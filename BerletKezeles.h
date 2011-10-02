//---------------------------------------------------------------------------

#ifndef BerletKezelesH
#define BerletKezelesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>

//#include "ClassBerlet.h"
#include "Classes.h"
#include "Database.h"
#include <Grids.hpp>

//---------------------------------------------------------------------------
class TFormBerlet : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBoxBerletTipus;
   TLabel *Label1;
   TEdit *EditBTNev;
   TLabel *Label2;
   TEdit *EditBTAr;
   TLabel *Label3;
   TEdit *EditBTEgyseg;
   TLabel *Label4;
   TEdit *EditBTErvTolEv;
   TLabel *Label5;
   TEdit *EditBTErvTolHo;
   TLabel *Label6;
   TEdit *EditBTErvTolNap;
   TEdit *EditBTErvIgEv;
   TLabel *Label7;
   TEdit *EditBTErvIgHo;
   TLabel *Label8;
   TEdit *EditBTErvIgNap;
   TLabel *Label9;
   TLabel *Label10;
   TLabel *Label11;
   TEdit *EditBTErvNapok;
   TLabel *Label12;
   TGroupBox *GroupBoxBerletTipusok;
   TBitBtn *BitBtnOk;
   TBitBtn *ButtonBTNew;
   TBitBtn *ButtonBTDelete;
   TBitBtn *ButtonBTSave;
   TEdit *EditBTID;
   TStringGrid *StringGridBerletTipus;
   TBitBtn *ButtonBTCancel;
   TBitBtn *ButtonBTModify;
   TLabel *Label13;
   TEdit *EditBTEgysegido;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall ListBoxBerletTipusokClick(TObject *Sender);
   void __fastcall ButtonBTNewClick(TObject *Sender);
   void __fastcall ButtonBTDeleteClick(TObject *Sender);
   void __fastcall ButtonBTSaveClick(TObject *Sender);
   void __fastcall BitBtnOkClick(TObject *Sender);
   void __fastcall ButtonBTModifyClick(TObject *Sender);
   void __fastcall ButtonBTCancelClick(TObject *Sender);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
private:	// User declarations
public:		// User declarations

   CS_Berlet   *pBerlet;

   __fastcall TFormBerlet(TComponent* Owner);

   void FillListBerletTipusok();
   bool AdatEllenorzes();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBerlet *FormBerlet;
//---------------------------------------------------------------------------
#endif

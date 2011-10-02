//---------------------------------------------------------------------------

#ifndef BerletEladasH
#define BerletEladasH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>

//#include "ClassBerlet.h"
//#include "ClassTermek.h"
#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
class TFormBerletEladas : public TForm
{
__published:	// IDE-managed Components
   TBitBtn *BitBtnOk;
   TBitBtn *BitBtnCancel;
   TGroupBox *GroupBox1;
   TLabel *Label2;
   TComboBox *ComboBoxTipus;
   TLabel *Label3;
   TEdit *EditBTEgyseg;
   TLabel *Label4;
   TEdit *EditBTErvTolEv;
   TLabel *Label6;
   TEdit *EditBTErvTolHo;
   TLabel *Label7;
   TEdit *EditBTErvTolNap;
   TLabel *Label9;
   TEdit *EditBTErvIgEv;
   TLabel *Label8;
   TEdit *EditBTErvIgHo;
   TLabel *Label10;
   TEdit *EditBTErvIgNap;
   TLabel *Label11;
   TLabel *Label12;
   TEdit *EditBTAr;
   TEdit *EditBTID;
   TLabel *Label13;
   TEdit *EditVonalkod;
   TBitBtn *BitBtnKosar;
   TLabel *Label1;
   TEdit *EditMegjegyzes;
   void __fastcall BitBtnOkClick(TObject *Sender);
   void __fastcall ComboBoxTipusChange(TObject *Sender);
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall BitBtnKosarClick(TObject *Sender);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
   void __fastcall EditVonalkodExit(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormBerletEladas(TComponent* Owner);

   CS_Berlet   *pBerlet;
   CS_Termek   *pTermek;
   CS_MainSettings   *pMainSettings;

   void FillListBerletTipusok();
   void FillListSorszamok();
   void BerletAdatbazisba();
   bool VonalkodEllenorzes();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBerletEladas *FormBerletEladas;
//---------------------------------------------------------------------------
#endif

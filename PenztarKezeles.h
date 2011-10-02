//---------------------------------------------------------------------------

#ifndef PenztarKezelesH
#define PenztarKezelesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Classes.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormPenztarKezeles : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TLabel *LabelCash;
   TLabel *Label2;
   TBitBtn *BitBtnOk;
   TGroupBox *GroupBox2;
   TBitBtn *BitBtnPlus;
   TBitBtn *BitBtnMinus;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall BitBtnPlusClick(TObject *Sender);
   void __fastcall BitBtnMinusClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormPenztarKezeles(TComponent* Owner);

   CS_MainSettings   *pMainSettings;
   CS_Penztar        *pPenztar;
   CS_User           *pUser;

   typ_user           stUser;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPenztarKezeles *FormPenztarKezeles;
//---------------------------------------------------------------------------
#endif

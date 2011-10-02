//---------------------------------------------------------------------------

#ifndef UserKezelesH
#define UserKezelesH
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
class TFormUserKezeles : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TStringGrid *StringGridUser;
   TBitBtn *BitBtnModify;
   TBitBtn *BitBtnDelete;
   TBitBtn *BitBtnNew;
   TBitBtn *BitBtnOk;
   TGroupBox *GroupBox2;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TEdit *EditNev;
   TEdit *EditAzonosito;
   TEdit *EditLogin;
   TBitBtn *BitBtnSaveModify;
   TBitBtn *BitBtnCancel;
   TMemo *MemoMegjegyzes;
   TLabel *Label5;
   TComboBox *ComboBoxUserGroup;
   TEdit *EditID;
   TEdit *EditPassword;
   TBitBtn *BitBtnPassword;
   TLabel *LabelPassword;
   TBitBtn *BitBtnPasswordReset;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall StringGridUserClick(TObject *Sender);
   void __fastcall BitBtnNewClick(TObject *Sender);
   void __fastcall BitBtnModifyClick(TObject *Sender);
   void __fastcall BitBtnDeleteClick(TObject *Sender);
   void __fastcall BitBtnSaveModifyClick(TObject *Sender);
   void __fastcall BitBtnCancelClick(TObject *Sender);
   void __fastcall BitBtnOkClick(TObject *Sender);
   void __fastcall BitBtnPasswordClick(TObject *Sender);
   void __fastcall BitBtnPasswordResetClick(TObject *Sender);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
private:	// User declarations
public:		// User declarations
   __fastcall TFormUserKezeles(TComponent* Owner);

   CS_MainSettings   *pMainSettings;
   CS_User           *pUser;

   void FillListUserek( TObject *Sender );
};
//---------------------------------------------------------------------------
extern PACKAGE TFormUserKezeles *FormUserKezeles;
//---------------------------------------------------------------------------
#endif

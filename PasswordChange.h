//---------------------------------------------------------------------------

#ifndef PasswordChangeH
#define PasswordChangeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>

//#include "LoadSaveSettings.h"
#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
class TFormPasswordChange : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TLabel *Label1;
   TEdit *Edit1;
   TLabel *Label2;
   TEdit *Edit2;
   TEdit *Edit3;
   TLabel *Label3;
   TBitBtn *BitBtnCancel;
   TBitBtn *BitBtnOk;
   TEdit *EditOldPassword;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall BitBtnOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   CS_MainSettings *Settings;
   int Level;
   __fastcall TFormPasswordChange(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPasswordChange *FormPasswordChange;
//---------------------------------------------------------------------------
#endif

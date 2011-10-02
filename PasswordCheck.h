//---------------------------------------------------------------------------

#ifndef PasswordCheckH
#define PasswordCheckH
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
class TFormPasswordCheck : public TForm
{
__published:	// IDE-managed Components
   TBitBtn *BitBtnOk;
   TBitBtn *BitBtn1;
   TLabel *LabelPassword;
   TEdit *EditPassword;
   TLabel *LabelUserNev;
   TComboBox *EditUserNev;
   TEdit *EditCurrentUser;
   TBitBtn *BitBtnExit;
   void __fastcall BitBtnOkClick(TObject *Sender);
   void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormPasswordCheck(TComponent* Owner);

   CS_User           *pUser;
   int                AccessLevel;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPasswordCheck *FormPasswordCheck;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef AdatBeolvasasH
#define AdatBeolvasasH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>

//#include "LoadSaveSettings.h"
//#include "ClassSolarium.h"
#include "Classes.h"
#include "Database.h"

#define ACTION_BARNULASIDO     1
#define ACTION_VONALKOD        2

//---------------------------------------------------------------------------
class TFormDataRead : public TForm
{
__published:	// IDE-managed Components
   TEdit *EditAdat;
   TBitBtn *BitBtnOk;
   TBitBtn *BitBtnCancel;
   TLabel *LabelInfo;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall EditAdatChange(TObject *Sender);
   void __fastcall BitBtnOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormDataRead(TComponent* Owner);

   CS_Solarium    *pSzolarium;
   int             nAction;

   void CheckTypedValue();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDataRead *FormDataRead;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef DialogCommentH
#define DialogCommentH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormCommentDialog : public TForm
{
__published:	// IDE-managed Components
   TMemo *MemoComment;
   TBitBtn *BitBtnCancel;
   TBitBtn *BitBtnOk;
   void __fastcall BitBtnOkClick(TObject *Sender);
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
private:	// User declarations
public:		// User declarations
   __fastcall TFormCommentDialog(TComponent* Owner);

   char  strMegjegyzes[1000];
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCommentDialog *FormCommentDialog;
//---------------------------------------------------------------------------
#endif

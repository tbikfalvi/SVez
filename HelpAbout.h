//---------------------------------------------------------------------------

#ifndef HelpAboutH
#define HelpAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFormHelpAbout : public TForm
{
__published:	// IDE-managed Components
   TImage *Image1;
   TButton *ButtonOk;
   TLabel *Label1;
   TLabel *LabelVersion;
   TLabel *LabelAdatfile;
   TGroupBox *GroupBox1;
private:	// User declarations
public:		// User declarations
   __fastcall TFormHelpAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormHelpAbout *FormHelpAbout;
//---------------------------------------------------------------------------
#endif

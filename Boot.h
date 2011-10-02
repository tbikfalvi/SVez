//---------------------------------------------------------------------------

#ifndef BootH
#define BootH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormBoot : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TImage *Image1;
   TLabel *Label1;
   TLabel *LabelVersion;
   TMemo *BootDisplay;
   TEdit *BootHWInfo;
   void __fastcall FormActivate(TObject *Sender);
private:	// User declarations

   int   nLine;

public:		// User declarations
   __fastcall TFormBoot(TComponent* Owner);

   AnsiString  strLogLine;

   void AddBootMessage( bool bOverwrite=false );
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBoot *FormBoot;
//---------------------------------------------------------------------------
#endif

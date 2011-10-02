//---------------------------------------------------------------------------

#ifndef KosarH
#define KosarH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>

//#include "ClassKosar.h"
//#include "ClassBerlet.h"
//#include "ClassTermek.h"
#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
class TFormKosar : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TGroupBox *GroupBox2;
   TStringGrid *StringGridKosar;
   TBitBtn *BitBtnClose;
   TLabel *Label1;
   TLabel *LabelFizetendo;
   TLabel *Label3;
   TBitBtn *BitBtnDelete;
   TBitBtn *BitBtnBerletAdd;
   TBitBtn *BitBtnTermekAdd;
   TBitBtn *BitBtnFizetes;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall BitBtnDeleteClick(TObject *Sender);
   void __fastcall StringGridKosarClick(TObject *Sender);
   void __fastcall BitBtnBerletAddClick(TObject *Sender);
   void __fastcall BitBtnTermekAddClick(TObject *Sender);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
private:	// User declarations
public:		// User declarations
   __fastcall TFormKosar(TComponent* Owner);

   CS_Kosar      *pKosar;
   CS_Berlet     *pBerletek;
   CS_Termek     *pTermek;
   CS_MainSettings   *pMainSettings;

   AnsiString     KosarTipus[3];

   void FillListKosar( TObject *Sender );
};
//---------------------------------------------------------------------------
extern PACKAGE TFormKosar *FormKosar;
//---------------------------------------------------------------------------
#endif

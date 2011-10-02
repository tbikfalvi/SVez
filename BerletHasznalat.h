//---------------------------------------------------------------------------

#ifndef BerletHasznalatH
#define BerletHasznalatH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>

//#include "ClassBerlet.h"
#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
class TFormBerletHasznalat : public TForm
{
__published:	// IDE-managed Components
   TBitBtn *BitBtnOk;
   TBitBtn *BitBtnCancel;
   TGroupBox *GroupBox1;
   TLabel *Label1;
   TEdit *EditTipus;
   TLabel *Label2;
   TEdit *EditEgyseg;
   TLabel *Label3;
   TEdit *EditErvenyes;
   TGroupBox *GroupBox2;
   TLabel *Label4;
   TComboBox *ComboBoxHasznalat;
   TEdit *EditMegjegyzes;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall BitBtnOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormBerletHasznalat(TComponent* Owner);

   CS_Berlet         *pBerlet;
   CS_MainSettings   *pMainSettings;

   typ_berlet         stBerlet;
   typ_berlettipus    stBTipus;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBerletHasznalat *FormBerletHasznalat;
//---------------------------------------------------------------------------
#endif

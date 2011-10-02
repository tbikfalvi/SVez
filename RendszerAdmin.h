//---------------------------------------------------------------------------

#ifndef RendszerAdminH
#define RendszerAdminH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include "Classes.h"
#include "Database.h"
//---------------------------------------------------------------------------
class TSystemAdmin : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TRadioButton *RB_Berlet;
   TRadioButton *RB_Berlettipus;
   TRadioButton *RB_Berlethasznalat;
   TRadioButton *RB_Konyv;
   TRadioButton *RB_Solkonyv;
   TRadioButton *RB_Penztarkonyv;
   TGroupBox *GroupBox2;
   TStringGrid *RekordLista;
   TRadioButton *RB_Szolarium;
   TGroupBox *GroupBox3;
   TEdit *EditKod;
   TButton *BtnCode;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall BtnCodeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations

   CS_MainSettings   *pMainSettings;

   __fastcall TSystemAdmin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSystemAdmin *SystemAdmin;
//---------------------------------------------------------------------------
#endif

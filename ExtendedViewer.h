//---------------------------------------------------------------------------

#ifndef ExtendedViewerH
#define ExtendedViewerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <vector.h>
#include "Classes.h"
#include "Database.h"
//---------------------------------------------------------------------------
class TFormExtendedViewer : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
   __fastcall TFormExtendedViewer(TComponent* Owner);

   CS_MainSettings      *pMainSettings;
   typ_szolisettings     stSoliSettings;
   vector<TPanel*>       PanelSzolarium;
   vector<TPanel*>       Panel_Nev;
   vector<TLabel*>       Label_Status;
   vector<TLabel*>       Label_Visszaszamlalas;
   vector<TLabel*>       Label_Ido;
   vector<TLabel*>       Label_Informacio;
   vector<TLabel*>       Label_Penz;
   vector<TProgressBar*> ProgressBarCso;

   void InitPanels(int nCountSolarium,int nCountRow,int nCountColumn);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormExtendedViewer *FormExtendedViewer;
//---------------------------------------------------------------------------
#endif

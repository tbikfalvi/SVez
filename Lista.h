//---------------------------------------------------------------------------

#ifndef ListaH
#define ListaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------

#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------
class TFormLista : public TForm
{
__published:	// IDE-managed Components
   TBitBtn *BitBtnOk;
   TPrintDialog *PrintDialog;
   TBitBtn *BitBtnPrint;
   TGroupBox *GB_FilterDatum;
   TLabel *Label1;
   TDateTimePicker *DTPickerStart;
   TLabel *Label2;
   TButton *BtnStartPrevWeek;
   TButton *BtnStartPrevDay;
   TButton *BtnStartNextDay;
   TButton *BtnStartNextWeek;
   TButton *BtnStopPrevWeek;
   TButton *BtnStopPrevDay;
   TDateTimePicker *DTPickerStop;
   TButton *BtnStopNextDay;
   TButton *BtnStopNextWeek;
   TGroupBox *GB_FilterMuszak;
   TLabel *Label3;
   TButton *BtnPrevMuszak;
   TEdit *EditMuszakID;
   TButton *BtnNextMuszak;
   TBitBtn *BitBtnSave;
   TGroupBox *GB_FilterBerlet;
   TLabel *Label4;
   TTabControl *TabControlLista;
   TRichEdit *RichEditLista;
   TSaveDialog *SaveDialog;
   TEdit *EditBerlet;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall BitBtnPrintClick(TObject *Sender);
   void __fastcall BtnStartPrevWeekClick(TObject *Sender);
   void __fastcall BtnStartPrevDayClick(TObject *Sender);
   void __fastcall BtnStartNextDayClick(TObject *Sender);
   void __fastcall BtnStartNextWeekClick(TObject *Sender);
   void __fastcall BtnStopPrevWeekClick(TObject *Sender);
   void __fastcall BtnStopPrevDayClick(TObject *Sender);
   void __fastcall BtnStopNextDayClick(TObject *Sender);
   void __fastcall BtnStopNextWeekClick(TObject *Sender);
   void __fastcall BitBtnOkClick(TObject *Sender);
   void __fastcall BtnPrevMuszakClick(TObject *Sender);
   void __fastcall BtnNextMuszakClick(TObject *Sender);
   void __fastcall DTPickerStartChange(TObject *Sender);
   void __fastcall DTPickerStopChange(TObject *Sender);
   void __fastcall BitBtnSaveClick(TObject *Sender);
   void __fastcall TabControlListaChange(TObject *Sender);
   void __fastcall EditBerletChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormLista(TComponent* Owner);

   AnsiString         strLine;
   int                nListaType;
   CS_MainSettings   *pMainSettings;
   CS_Berlet         *pBerletek;
   CS_Termek         *pTermek;
   CS_Konyv          *pKonyv;
   CS_Penztar        *pPenztar;
   CS_User           *pUser;
   bool               bFilter;
   double             dMuszakMax;
   int                nSzolariumCount;
   int                nTabPrevious;

   void SetControls();
   void FillLista();
   void FillBerletLista();
   void FillBerletHasznalatLista();
   void FillTermekLista();
   void FillKonyvLista();
   void FillSzoliLista();
   void FillPenztarLista();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLista *FormLista;
//---------------------------------------------------------------------------
#endif

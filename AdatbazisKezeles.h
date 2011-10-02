//---------------------------------------------------------------------------

#ifndef AdatbazisKezelesH
#define AdatbazisKezelesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Classes.h"
#include "Database.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormAdatbazisKezeles : public TForm
{
__published:	// IDE-managed Components
   TBitBtn *BitBtnOk;
   TGroupBox *GB_FilterDatum;
   TLabel *Label1;
   TLabel *Label2;
   TDateTimePicker *DTPickerStart;
   TButton *BtnStartPrevWeek;
   TButton *BtnStartPrevDay;
   TButton *BtnStartNextDay;
   TButton *BtnStartNextWeek;
   TButton *BtnStopPrevWeek;
   TButton *BtnStopPrevDay;
   TDateTimePicker *DTPickerStop;
   TButton *BtnStopNextDay;
   TButton *BtnStopNextWeek;
   TGroupBox *GroupBox1;
   TGroupBox *GroupBox2;
   TRadioButton *RadioBerlet;
   TRadioButton *RadioBerlethasznalat;
   TRadioButton *RadioFokonyv;
   TRadioButton *RadioSzolariumkonyv;
   TLabel *Label3;
   TLabel *Label4;
   TRadioButton *RadioPenztar;
   TRadioButton *RadioDBDelete;
   TGroupBox *GroupBox3;
   TBitBtn *BitBtnExecute;
   void __fastcall BitBtnOkClick(TObject *Sender);
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall BtnStartPrevWeekClick(TObject *Sender);
   void __fastcall BtnStartPrevDayClick(TObject *Sender);
   void __fastcall BtnStartNextDayClick(TObject *Sender);
   void __fastcall BtnStartNextWeekClick(TObject *Sender);
   void __fastcall BtnStopPrevWeekClick(TObject *Sender);
   void __fastcall BtnStopPrevDayClick(TObject *Sender);
   void __fastcall BtnStopNextDayClick(TObject *Sender);
   void __fastcall BtnStopNextWeekClick(TObject *Sender);
   void __fastcall RadioBerletClick(TObject *Sender);
   void __fastcall RadioBerlethasznalatClick(TObject *Sender);
   void __fastcall RadioFokonyvClick(TObject *Sender);
   void __fastcall RadioSzolariumkonyvClick(TObject *Sender);
   void __fastcall RadioPenztarClick(TObject *Sender);
   void __fastcall RadioDBDeleteClick(TObject *Sender);
   void __fastcall BitBtnExecuteClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormAdatbazisKezeles(TComponent* Owner);

   CS_Berlet            *pBerletek;
   CS_Konyv             *pKonyv;
   CS_Penztar           *pPenztar;

   AnsiString  strAction;
   AnsiString  strDB;
   int         nDBType;
   int         nActionType;

   void ExecuteDBAction();
   void DeleteBerlet();
   void DeleteBerletHasznalat();
   void DeleteFoKonyv();
   void DeleteSzolariumKonyv();
   void DeletePenztarKonyv();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAdatbazisKezeles *FormAdatbazisKezeles;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef HardwareTesztH
#define HardwareTesztH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include "Classes.h"
#include "Database.h"
//---------------------------------------------------------------------------
class TFormHardverTeszt : public TForm
{
__published:	// IDE-managed Components
   TBitBtn *BitBtnOk;
   TGroupBox *GroupBox1;
   TBitBtn *BitBtnHWInit;
   TGroupBox *GroupBox2;
   TGroupBox *GroupBox3;
   TListBox *ListBoxLog;
   TCheckBox *ChkRelay01;
   TCheckBox *ChkRelay02;
   TCheckBox *ChkRelay03;
   TCheckBox *ChkRelay04;
   TCheckBox *ChkRelay08;
   TCheckBox *ChkRelay07;
   TCheckBox *ChkRelay06;
   TCheckBox *ChkRelay05;
   TCheckBox *ChkRelay12;
   TCheckBox *ChkRelay11;
   TCheckBox *ChkRelay10;
   TCheckBox *ChkRelay09;
   TCheckBox *ChkRelay16;
   TCheckBox *ChkRelay15;
   TCheckBox *ChkRelay14;
   TCheckBox *ChkRelay13;
   TBitBtn *BitBtnLedModulKeres;
   TBitBtn *BitBtnLedModulTeszt;
   TBitBtn *BitBtnLedModulCimSet;
   TBitBtn *BitBtnRelayRunTest;
   TBitBtn *BitBtnHWTeszt;
   TCheckBox *CheckLedModulOnOff;
   TBitBtn *BitBtnBitBtnLedModulGombFigyeles;
   TEdit *EditEEPROM;
   TBitBtn *BitBtnWriteEEPROM;
   TBitBtn *BitBtnReadEEPROM;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall BitBtnHWTesztClick(TObject *Sender);
   void __fastcall BitBtnHWInitClick(TObject *Sender);
   void __fastcall BitBtnLedModulKeresClick(TObject *Sender);
   void __fastcall BitBtnLedModulTesztClick(TObject *Sender);
   void __fastcall BitBtnLedModulCimSetClick(TObject *Sender);
   void __fastcall BitBtnRelayRunTestClick(TObject *Sender);
   void __fastcall ChkRelay01Click(TObject *Sender);
   void __fastcall ChkRelay02Click(TObject *Sender);
   void __fastcall ChkRelay03Click(TObject *Sender);
   void __fastcall ChkRelay04Click(TObject *Sender);
   void __fastcall ChkRelay05Click(TObject *Sender);
   void __fastcall ChkRelay06Click(TObject *Sender);
   void __fastcall ChkRelay07Click(TObject *Sender);
   void __fastcall ChkRelay08Click(TObject *Sender);
   void __fastcall ChkRelay09Click(TObject *Sender);
   void __fastcall ChkRelay10Click(TObject *Sender);
   void __fastcall ChkRelay11Click(TObject *Sender);
   void __fastcall ChkRelay12Click(TObject *Sender);
   void __fastcall BitBtnOkClick(TObject *Sender);
   void __fastcall CheckLedModulOnOffClick(TObject *Sender);
   void __fastcall BitBtnBitBtnLedModulGombFigyelesClick(TObject *Sender);
   void __fastcall BitBtnWriteEEPROMClick(TObject *Sender);
   void __fastcall BitBtnReadEEPROMClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormHardverTeszt(TComponent* Owner);

   CS_Hardware       *pHardware;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormHardverTeszt *FormHardverTeszt;
//---------------------------------------------------------------------------
#endif

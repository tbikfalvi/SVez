//---------------------------------------------------------------------------

#ifndef SystemSettingsH
#define SystemSettingsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include "Database.h"
#include <ImgList.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormSystemSettings : public TForm
{
__published:	// IDE-managed Components
   TBitBtn *BitBtnOk;
   TBitBtn *BitBtnCancel;
   TGroupBox *GroupBox1;
   TLabel *Label1;
   TComboBox *ComboBoxPort;
   TLabel *Label2;
   TComboBox *ComboBoxBaudRate;
   TLabel *Label3;
   TComboBox *ComboBoxParity;
   TGroupBox *GroupBoxSzolarium;
   TPanel *PanelSzolarium;
   TPanel *Panel_Nev;
   TLabel *Label_Status;
   TLabel *Label_Visszaszamlalas;
   TLabel *Label_Ido;
   TLabel *Label_Informacio;
   TLabel *Label_Penz;
   TProgressBar *ProgressBarCso;
   TFontDialog *FontDialog;
   TBevel *BevelSelection;
   TBitBtn *BitBtnFont;
   TBitBtn *BitBtnUp;
   TBitBtn *BitBtnDown;
   TColorDialog *ColorDialog;
   TRadioButton *RB_Alap;
   TRadioButton *RB_Var;
   TRadioButton *RB_Use;
   TBitBtn *BitBtnColor;
   TGroupBox *GroupBoxLogLevel;
   TLabel *Label4;
   TComboBox *ComboBoxLogLevel;
   TGroupBox *GroupBoxExtended;
   TImageList *ImageList;
   TPanel *PanelExtended;
   TImage *Image1;
   TImage *Image2;
   TGroupBox *GroupBox2;
   TCheckBox *CheckBoxAutoSave;
   TGroupBox *GroupBox3;
   TCheckBox *CheckBoxCardPIN;
   TLabel *Label5;
   void __fastcall BitBtnOkClick(TObject *Sender);
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall BitBtnFontClick(TObject *Sender);
   void __fastcall Label_StatusClick(TObject *Sender);
   void __fastcall Label_VisszaszamlalasClick(TObject *Sender);
   void __fastcall Label_IdoClick(TObject *Sender);
   void __fastcall Label_InformacioClick(TObject *Sender);
   void __fastcall Label_PenzClick(TObject *Sender);
   void __fastcall BitBtnUpClick(TObject *Sender);
   void __fastcall BitBtnDownClick(TObject *Sender);
   void __fastcall BitBtnColorClick(TObject *Sender);
   void __fastcall RB_AlapClick(TObject *Sender);
   void __fastcall RB_VarClick(TObject *Sender);
   void __fastcall RB_UseClick(TObject *Sender);
   void __fastcall PanelExtendedClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFormSystemSettings(TComponent* Owner);

   typ_szolisettings    stSoliSettings;
   int                  PanelWidth;
   int                  PanelHeight;
   int                  CurrentLabel;
   bool                 bExtended;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSystemSettings *FormSystemSettings;
//---------------------------------------------------------------------------
#endif

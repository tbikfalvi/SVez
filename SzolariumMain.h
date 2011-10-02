//---------------------------------------------------------------------------

#ifndef SzolariumMainH
#define SzolariumMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
#include "Classes.h"
#include "Database.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
   TMainMenu *MenuMain;
   TMenuItem *MenuMain_System;
   TMenuItem *MenuMain_SystemExit;
   TTimer *TimerMain;
   TMenuItem *MenuMain_Settings;
   TMenuItem *MenuMain_SettingVideoSize;
   TMenuItem *MenuMain_SettingVideoSize2;
   TMenuItem *MenuMain_SettingVideoSize3;
   TMenuItem *MenuMain_SettingVideoSize4;
   TStatusBar *StatusBar;
   TMenuItem *MenuMain_SettingVideo;
   TMenuItem *MenuMain_SystemLogoff;
   TMenuItem *MenuMain_SystemSave;
   TMenuItem *MenuMain_SystemSessionclose;
   TMenuItem *N1;
   TMenuItem *N2;
   TMenuItem *MenuMain_List;
   TMenuItem *MenuMain_ListMaincash;
   TMenuItem *MenuMain_ListDailycash;
   TMenuItem *N3;
   TMenuItem *MenuMain_ListBerlet;
   TMenuItem *MenuMain_ListGoods;
   TMenuItem *MenuMain_Help;
   TMenuItem *MenuMain_HelpAbout;
   TMenuItem *MenuMain_SettingSzolarium;
   TMenuItem *MenuMain_SettingJelszavak;
   TMenuItem *MenuMain_SettingJelszoAdmin;
   TMenuItem *MenuMain_SettingJelszoUser;
   TTimer *TimerSolarium;
   TMenuItem *MenuMain_SettingSystem;
   TMenuItem *MenuMain_SettingsBerletek;
   TToolBar *ToolBar1;
   TToolButton *ToolButtonExit;
   TToolButton *ToolSeparator0;
   TToolButton *ToolSeparator1;
   TImageList *ImageListToolBar;
   TToolButton *ToolButtonSzolariumHalt;
   TToolButton *ToolSeparator4;
   TToolButton *ToolButtonSzolariumSteril;
   TToolButton *ToolSeparator5;
   TToolButton *ToolButtonBerletManage;
   TToolButton *ToolSeparatorSystem;
   TToolButton *ToolButtonTermekManage;
   TImageList *ImageListToolBarDisabled;
   TToolButton *ToolSeparator9;
   TToolButton *ToolButtonBevasarlokosar;
   TToolButton *ToolButtonBerletEladas;
   TToolButton *ToolSeparator6;
   TToolButton *ToolSeparator7;
   TToolButton *ToolButtonTermekEladas;
   TMenuItem *MenuMain_SettingsTermekek;
   TToolButton *ToolButtonSzolariumAdat;
   TToolButton *ToolButton1;
   TMenuItem *N5;
   TMenuItem *N6;
   TToolButton *ToolButtonSzolariumStart;
   TToolButton *ToolButton2;
   TToolButton *ToolButtonSzolariumIdo;
   TToolButton *ToolButtonSzolariumBerlet;
   TToolButton *ToolButton5;
   TToolButton *ToolButton6;
   TTimer *TimerUserLock;
   TMenuItem *MenuMain_SettingFelhasznalok;
   TToolButton *ToolButton3;
   TToolButton *ToolButtonUserManage;
   TToolButton *ToolButton4;
   TToolButton *ToolButtonCassa;
   TMenuItem *MenuMain_Penz;
   TMenuItem *MenuMain_PenzKosar;
   TMenuItem *MenuMain_PenzPenztar;
   TMenuItem *MenuMain_SettingJelszo;
   TMenuItem *N8;
   TMenuItem *MenuMain_SettingsPenztar;
   TMenuItem *MenuMain_SettingsHWTeszt;
   TMenuItem *MenuMain_ListMuszak;
   TMenuItem *N4;
   TMenuItem *MenuMain_ListBerletHasznalat;
   TMenuItem *N7;
   TMenuItem *MenuMain_ListPenztar;
   TMenuItem *MenuMain_Sol;
   TMenuItem *MenuMain_Sol_Ido;
   TMenuItem *MenuMain_Sol_Berlet;
   TMenuItem *N9;
   TMenuItem *MenuMain_Sol_VetkozesStop;
   TMenuItem *MenuMain_Sol_Steril;
   TMenuItem *N10;
   TMenuItem *MenuMain_Sol_Stop;
   TMenuItem *MenuMain_PenzBerlet;
   TMenuItem *MenuMain_PenzTermek;
   TMenuItem *N11;
   TToolButton *ToolButton7;
   TToolButton *ToolButtonUserLogoff;
   TMenuItem *N12;
   TMenuItem *MenuMain_SystemImport;
   TMenuItem *MenuMain_SystemImport_Berlet;
   TOpenDialog *OpenDialog;
   TMenuItem *MenuMain_ListBerletOssz;
   TMenuItem *MenuMain_SettingsDB;
   TToolButton *ToolButton8;
   TToolButton *ToolButtonTermekTipusManage;
   TMenuItem *MenuMain_SettingsTermekTipusok;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall MenuMain_SystemExitClick(TObject *Sender);
   void __fastcall MenuMain_SettingVideoSize2Click(TObject *Sender);
   void __fastcall MenuMain_SettingVideoSize3Click(TObject *Sender);
   void __fastcall MenuMain_SettingVideoSize4Click(TObject *Sender);
   void __fastcall TimerMainTimer(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall DisplayHint(TObject *Sender);
   void __fastcall MenuMain_HelpAboutClick(TObject *Sender);
   void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
   void __fastcall MenuMain_SystemSaveClick(TObject *Sender);
   void __fastcall MenuMain_SettingSzolariumClick(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall FormDblClick(TObject *Sender);
   void __fastcall TimerSolariumTimer(TObject *Sender);
   void __fastcall MenuMain_SettingSystemClick(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall MenuMain_SettingsBerletekClick(TObject *Sender);
   void __fastcall ToolButtonSzolariumHaltClick(TObject *Sender);
   void __fastcall ToolButtonSzolariumSterilClick(TObject *Sender);
   void __fastcall ToolButtonBerletEladasClick(TObject *Sender);
   void __fastcall MenuMain_SettingsTermekekClick(TObject *Sender);
   void __fastcall MenuMain_ListBerletClick(TObject *Sender);
   void __fastcall MenuMain_ListGoodsClick(TObject *Sender);
   void __fastcall ToolButtonTermekEladasClick(TObject *Sender);
   void __fastcall MenuMain_ListMaincashClick(TObject *Sender);
   void __fastcall ToolButtonSzolariumIdoClick(TObject *Sender);
   void __fastcall ToolButtonSzolariumBerletClick(TObject *Sender);
   void __fastcall ToolButtonSzolariumStartClick(TObject *Sender);
   void __fastcall MenuMain_SystemSessioncloseClick(TObject *Sender);
   void __fastcall TimerUserLockTimer(TObject *Sender);
   void __fastcall MenuMain_SystemLogoffClick(TObject *Sender);
   void __fastcall MenuMain_SettingFelhasznalokClick(TObject *Sender);
   void __fastcall MenuMain_PenzKosarClick(TObject *Sender);
   void __fastcall MenuMain_PenzPenztarClick(TObject *Sender);
   void __fastcall MenuMain_SettingJelszoClick(TObject *Sender);
   void __fastcall MenuMain_SettingsPenztarClick(TObject *Sender);
   void __fastcall MenuMain_ListDailycashClick(TObject *Sender);
   void __fastcall MenuMain_ListMuszakClick(TObject *Sender);
   void __fastcall MenuMain_ListBerletHasznalatClick(TObject *Sender);
   void __fastcall MenuMain_SettingsHWTesztClick(TObject *Sender);
   void __fastcall MenuMain_ListPenztarClick(TObject *Sender);
   void __fastcall MenuMain_Sol_IdoClick(TObject *Sender);
   void __fastcall MenuMain_Sol_BerletClick(TObject *Sender);
   void __fastcall MenuMain_Sol_VetkozesStopClick(TObject *Sender);
   void __fastcall MenuMain_Sol_SterilClick(TObject *Sender);
   void __fastcall MenuMain_Sol_StopClick(TObject *Sender);
   void __fastcall MenuMain_PenzBerletClick(TObject *Sender);
   void __fastcall MenuMain_PenzTermekClick(TObject *Sender);
   void __fastcall ToolButtonUserLogoffClick(TObject *Sender);
   void __fastcall MenuMain_SystemImport_BerletClick(TObject *Sender);
   void __fastcall MenuMain_ListBerletOsszClick(TObject *Sender);
   void __fastcall MenuMain_SettingsDBClick(TObject *Sender);
   void __fastcall MenuMain_SettingsTermekTipusokClick(TObject *Sender);
private:	// User declarations

   int      nCurrentSolarium;
   AnsiString  strMentesBat;

   void CalculateColumnRow();
   void ResizePanels();
   void SzolariumStatusCheck();
   int InputDataCheck( int nAction, TEdit *EditAdat );
   void KeyDownShorcut(TObject *Sender, WORD Key );
   void KeyDownProcess(TObject *Sender, WORD &Key, TShiftState Shift);
   void ActionSzolariumIdo(TObject *Sender, WORD &Key, TShiftState Shift);
   void ActionBerletHasznalat( typ_berlet stBerlet );
   void ActionTermekEladas( typ_termek stTermek );
   void ActionTermekDarabCsokkentes();
   void ActionTermekListaDarabCsokkentes();
   void ActionBerletKosarba();
   void ActionTermekKosarba();
   void ActionSzolariumKosarba( int nForint );
   void ActionTermekListaKosarba();
   void ActionSzolariumSelect( WORD Key );

public:		// User declarations
   __fastcall TFormMain(TComponent* Owner);

   int      nCountColumn;
   int      nCountRow;
   bool                  bErrorDuringBoot;
   CS_MainSettings      *MainSettings;
   CS_Berlet            *pBerletek;
   CS_Termek            *pTermek;
   CS_TermekTipus       *pTermekTipus;
   CS_Kosar             *pKosar;
   CS_Konyv             *pKonyv;
   CS_User              *pUser;
   CS_Penztar           *pPenztar;
   CS_Hardware          *pHardware;
   CS_SerialComm        *SComm;
   vector<CS_Solarium*>  pSzolarium;
   vector<typ_error>     ErrorList;
   int                   extLeft, extTop;
   AnsiString            strCaption;

   void InitVariables();
   bool CheckDatabase();
   bool SaveDatabase();
   AnsiString GetErrorMessageText( int nIndex );
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif

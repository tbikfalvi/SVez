//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ExtendedViewer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormExtendedViewer *FormExtendedViewer;
//---------------------------------------------------------------------------
__fastcall TFormExtendedViewer::TFormExtendedViewer(TComponent* Owner)
   : TForm(Owner)
{
   pMainSettings = NULL;
}
//---------------------------------------------------------------------------
void TFormExtendedViewer::InitPanels(int nCountSolarium,int nCountRow,int nCountColumn)
{
   bool bDebugShowAllText = false;
   
   for(int y=0,i=0;y<nCountRow&&i<pMainSettings->GetCountSolarium();y++)
   {
      for(int x=0;x<nCountColumn&&i<pMainSettings->GetCountSolarium();x++)
      {
         int nLeft   = x*(ClientWidth/nCountColumn);
         int nTop    = y*(ClientHeight/nCountRow);
         int nWidth  = ClientWidth/nCountColumn;
         int nHeight = ClientHeight/nCountRow;

         PanelSzolarium.push_back( new TPanel( FormExtendedViewer ) );
         PanelSzolarium[i]->Parent = (TWinControl*)FormExtendedViewer;
         PanelSzolarium[i]->BevelWidth = 2;
         PanelSzolarium[i]->Left = nLeft;
         PanelSzolarium[i]->Top = nTop;
         PanelSzolarium[i]->Width = nWidth;
         PanelSzolarium[i]->Height = nHeight;
         PanelSzolarium[i]->Color = (TColor)stSoliSettings.ColorDefault;

         Panel_Nev.push_back( new TPanel( PanelSzolarium[i] ) );
         Panel_Nev[i]->Parent = PanelSzolarium[i];
         Panel_Nev[i]->Caption = AnsiString( "Szolarium" ) + AnsiString( i+1 );
         Panel_Nev[i]->Left = 2;
         Panel_Nev[i]->Top = 2;
         Panel_Nev[i]->Height = 30;
         Panel_Nev[i]->Width = nWidth-4;
         Panel_Nev[i]->Font->Name = "Times New Roman";
         Panel_Nev[i]->Font->Size = 14;
         Panel_Nev[i]->Font->Color = clCaptionText;
         Panel_Nev[i]->Color = clInactiveCaption;
         Panel_Nev[i]->Font->Color = clInactiveCaptionText;

         Label_Status.push_back( new TLabel( PanelSzolarium[i] ) );
         Label_Status[i]->Parent = PanelSzolarium[i];
         Label_Status[i]->AutoSize = false;
         Label_Status[i]->Caption = "SZOLÁRIUM STÁTUSZ";
         Label_Status[i]->Left = 5;
         Label_Status[i]->Top = stSoliSettings.StatusTop; // 38;
         Label_Status[i]->Height = stSoliSettings.StatusHeight; // 29;
         Label_Status[i]->Width = nWidth-10;
         Label_Status[i]->Alignment = taCenter;
         Label_Status[i]->Font->Name = "Times New Roman";
         Label_Status[i]->Font->Size = stSoliSettings.StatusFontSize; // 14;
         Label_Status[i]->Font->Style = TFontStyles()<< fsBold;
         Label_Status[i]->Font->Color = (TColor)stSoliSettings.StatusFontColorDef; // clGreen;
         Label_Status[i]->Font->Height = stSoliSettings.StatusFontHeight;
         Label_Status[i]->Visible = bDebugShowAllText;
         Label_Status[i]->Font->Color = (TColor)stSoliSettings.StatusFontColorDef;

         Label_Visszaszamlalas.push_back( new TLabel( PanelSzolarium[i] ) );
         Label_Visszaszamlalas[i]->Parent = PanelSzolarium[i];
         Label_Visszaszamlalas[i]->AutoSize = false;
         Label_Visszaszamlalas[i]->Caption = "00 : 00";
         Label_Visszaszamlalas[i]->Left = 5;
         Label_Visszaszamlalas[i]->Top = stSoliSettings.VisszaszamlalasTop; // 61;
         Label_Visszaszamlalas[i]->Height = stSoliSettings.VisszaszamlalasHeight; // 43;
         Label_Visszaszamlalas[i]->Width = nWidth-10;
         Label_Visszaszamlalas[i]->Alignment = taCenter;
         Label_Visszaszamlalas[i]->Font->Name = "Times New Roman";
         Label_Visszaszamlalas[i]->Font->Size = stSoliSettings.VisszaszamlalasFontSize; // 26;
         Label_Visszaszamlalas[i]->Font->Style = TFontStyles()<< fsBold;
         Label_Visszaszamlalas[i]->Font->Color = (TColor)stSoliSettings.VisszaszamlalasFontColorDef; // clBlack;
         Label_Visszaszamlalas[i]->Font->Height = stSoliSettings.VisszaszamlalasFontHeight;
         Label_Visszaszamlalas[i]->Visible = bDebugShowAllText;
         Label_Visszaszamlalas[i]->Font->Color = (TColor)stSoliSettings.VisszaszamlalasFontColorDef;

         Label_Ido.push_back( new TLabel( PanelSzolarium[i] ) );
         Label_Ido[i]->Parent = PanelSzolarium[i];
         Label_Ido[i]->AutoSize = false;
         Label_Ido[i]->Caption = "00 : 00";
         Label_Ido[i]->Left = 5;
         Label_Ido[i]->Top = stSoliSettings.IdoTop;// 100;
         Label_Ido[i]->Height = stSoliSettings.IdoHeight;// 26;
         Label_Ido[i]->Width = nWidth-10;
         Label_Ido[i]->Alignment = taCenter;
         Label_Ido[i]->Font->Name = "Times New Roman";
         Label_Ido[i]->Font->Size = stSoliSettings.IdoFontSize;// 16;
         Label_Ido[i]->Font->Style = TFontStyles()<< fsBold;
         Label_Ido[i]->Font->Color = (TColor)stSoliSettings.IdoFontColorDef;// clGreen;
         Label_Ido[i]->Font->Height = stSoliSettings.IdoFontHeight;
         Label_Ido[i]->Visible = bDebugShowAllText;
         Label_Ido[i]->Font->Color = (TColor)stSoliSettings.IdoFontColorDef;

         Label_Informacio.push_back( new TLabel( PanelSzolarium[i] ) );
         Label_Informacio[i]->Parent = PanelSzolarium[i];
         Label_Informacio[i]->AutoSize = false;
         Label_Informacio[i]->Caption = "SZOLARIUM INFO";
         Label_Informacio[i]->Left = 5;
         Label_Informacio[i]->Top = stSoliSettings.InformacioTop;// 125;
         Label_Informacio[i]->Height = stSoliSettings.InformacioHeight;// 29;
         Label_Informacio[i]->Width = nWidth-10;
         Label_Informacio[i]->Alignment = taCenter;
         Label_Informacio[i]->Font->Name = "Times New Roman";
         Label_Informacio[i]->Font->Size = stSoliSettings.InformacioFontSize;// 14;
         Label_Informacio[i]->Font->Style = TFontStyles()<< fsBold;
         Label_Informacio[i]->Font->Color = (TColor)stSoliSettings.InformacioFontColorDef;// clMaroon;
         Label_Informacio[i]->Font->Height = stSoliSettings.InformacioFontHeight;
         Label_Informacio[i]->Visible = bDebugShowAllText;
         Label_Informacio[i]->Font->Color = (TColor)stSoliSettings.InformacioFontColorDef;

         Label_Penz.push_back( new TLabel( PanelSzolarium[i] ) );
         Label_Penz[i]->Parent = PanelSzolarium[i];
         Label_Penz[i]->AutoSize = false;
         Label_Penz[i]->Caption = "100 Ft.";
         Label_Penz[i]->Left = 5;
         Label_Penz[i]->Top = stSoliSettings.PenzTop;// 152;
         Label_Penz[i]->Height = stSoliSettings.PenzHeight;// 43;
         Label_Penz[i]->Width = nWidth-10;
         Label_Penz[i]->Alignment = taCenter;
         Label_Penz[i]->Font->Name = "Times New Roman";
         Label_Penz[i]->Font->Size = stSoliSettings.PenzFontSize;// 26;
         Label_Penz[i]->Font->Style = TFontStyles()<< fsBold;
         Label_Penz[i]->Font->Color = (TColor)stSoliSettings.PenzFontColorDef;// clBlack;
         Label_Penz[i]->Font->Height = stSoliSettings.PenzFontHeight;
         Label_Penz[i]->Visible = bDebugShowAllText;
         Label_Penz[i]->Font->Color = (TColor)stSoliSettings.PenzFontColorDef;

         ProgressBarCso.push_back( new TProgressBar( PanelSzolarium[i] ) );
         ProgressBarCso[i]->Parent = PanelSzolarium[i];
         ProgressBarCso[i]->Visible = true;
         ProgressBarCso[i]->Left = 5;
         ProgressBarCso[i]->Top = Height-8;
         ProgressBarCso[i]->Height = 6;
         ProgressBarCso[i]->Width = nWidth-10;
         ProgressBarCso[i]->Smooth = true;
         ProgressBarCso[i]->Max = 100;
         ProgressBarCso[i]->Position = 0;

         i++;
      }
   }
}
//---------------------------------------------------------------------------

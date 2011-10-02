//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SystemSettings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSystemSettings *FormSystemSettings;
//---------------------------------------------------------------------------

#define PANEL_WIDTH              556
#define PANEL_HEIGHT             533
#define BUTTON_LEFT              440
#define GroupBoxSzolariumWidth   366
#define GroupBoxSzolariumHeight  336

//---------------------------------------------------------------------------
__fastcall TFormSystemSettings::TFormSystemSettings(TComponent* Owner)
   : TForm(Owner)
{
   int Left   = 10;
   int Top    = 100;

   Panel_Nev->Color = clActiveCaption;
   Panel_Nev->Font->Color = clCaptionText;
   PanelSzolarium->Color = (TColor)0x0007C776;
   Label_Status->Font->Color = clGreen;

   PanelSzolarium->Left = Left;
   PanelSzolarium->Top = Top;
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::FormActivate(TObject *Sender)
{
   PanelSzolarium->Width = PanelWidth;
   PanelSzolarium->Height = PanelHeight;

   if( bExtended )
   {
      PanelExtended->BevelOuter = bvLowered;
      Image1->Visible = false;
      Image2->Visible = true;
   }
   else
   {
      PanelExtended->BevelOuter = bvRaised;
      Image1->Visible = true;
      Image2->Visible = false;
   }

   if( PanelWidth > 341 )
   {
      // Szolárium panel szélesebb mint a default érték
      GroupBoxSzolarium->Width = GroupBoxSzolariumWidth + PanelWidth - 341;
   }
   else
   {
      // Szolárium panel kisebb mint a default érték
      GroupBoxSzolarium->Width = GroupBoxSzolariumWidth;
   }

   if( GroupBoxSzolarium->Width > Width-20 )
   {
      // A szolárium panel túllóg a dialógus ablakon
      Width = GroupBoxSzolarium->Width + 20;
   }
   else
   {
      // A szolárium panel elfér a dialógus ablakban
      Width = PANEL_WIDTH;
   }

   if( PanelHeight > 226 )
   {
      // A szolárium panel túllóg a dialógus ablakon
      Height = PANEL_HEIGHT + PanelHeight - 226;
      GroupBoxSzolarium->Height = GroupBoxSzolariumHeight + PanelHeight - 226;
   }
   else
   {
      // A szolárium panel elfér a dialógus ablakban
      Height = PANEL_HEIGHT;
      GroupBoxSzolarium->Height = GroupBoxSzolariumHeight;
   }

   Panel_Nev->Width = PanelWidth-4;
   Label_Status->Width = PanelWidth-10;
   Label_Visszaszamlalas->Width = PanelWidth-10;
   Label_Ido->Width = PanelWidth-10;
   Label_Informacio->Width = PanelWidth-10;
   Label_Penz->Width = PanelWidth-10;
   ProgressBarCso->Width = PanelWidth-10;

   Label_Status->Top = 38+(PanelHeight-214)/2;
   Label_Visszaszamlalas->Top = 61+(PanelHeight-214)/2;
   Label_Ido->Top = 100+(PanelHeight-214)/2;
   Label_Informacio->Top = 125+(PanelHeight-214)/2;
   Label_Penz->Top = 152+(PanelHeight-214)/2;
   ProgressBarCso->Top = PanelHeight-8;

   Label_Status->Top = stSoliSettings.StatusTop;
   Label_Status->Height = stSoliSettings.StatusHeight;
   Label_Status->Font->Name = stSoliSettings.StatusFontName;
   Label_Status->Font->Size = stSoliSettings.StatusFontSize;
   Label_Status->Font->Color = (TColor)stSoliSettings.StatusFontColorDef;
   Label_Status->Font->Height = stSoliSettings.StatusFontHeight;
   Label_Visszaszamlalas->Top = stSoliSettings.VisszaszamlalasTop;
   Label_Visszaszamlalas->Height = stSoliSettings.VisszaszamlalasHeight;
   Label_Visszaszamlalas->Font->Name = stSoliSettings.VisszaszamlalasFontName;
   Label_Visszaszamlalas->Font->Size = stSoliSettings.VisszaszamlalasFontSize;
   Label_Visszaszamlalas->Font->Color = (TColor)stSoliSettings.VisszaszamlalasFontColorDef;
   Label_Visszaszamlalas->Font->Height = stSoliSettings.VisszaszamlalasFontHeight;
   Label_Ido->Top = stSoliSettings.IdoTop;
   Label_Ido->Height = stSoliSettings.IdoHeight;
   Label_Ido->Font->Name = stSoliSettings.IdoFontName;
   Label_Ido->Font->Size = stSoliSettings.IdoFontSize;
   Label_Ido->Font->Color = (TColor)stSoliSettings.IdoFontColorDef;
   Label_Ido->Font->Height = stSoliSettings.IdoFontHeight;
   Label_Informacio->Top = stSoliSettings.InformacioTop;
   Label_Informacio->Height = stSoliSettings.InformacioHeight;
   Label_Informacio->Font->Name = stSoliSettings.InformacioFontName;
   Label_Informacio->Font->Size = stSoliSettings.InformacioFontSize;
   Label_Informacio->Font->Color = (TColor)stSoliSettings.InformacioFontColorDef;
   Label_Informacio->Font->Height = stSoliSettings.InformacioFontHeight;
   Label_Penz->Top = stSoliSettings.PenzTop;
   Label_Penz->Height = stSoliSettings.PenzHeight;
   Label_Penz->Font->Name = stSoliSettings.PenzFontName;
   Label_Penz->Font->Size = stSoliSettings.PenzFontSize;
   Label_Penz->Font->Color = (TColor)stSoliSettings.PenzFontColorDef;
   Label_Penz->Font->Height = stSoliSettings.PenzFontHeight;

   CurrentLabel = 1;
   BevelSelection->Left = Label_Status->Left;
   BevelSelection->Top = Label_Status->Top;
   BevelSelection->Width = Label_Status->Width;
   BevelSelection->Height = Label_Status->Height;

   RB_AlapClick(Sender);
   RB_Alap->Checked = true;
   RB_Var->Checked = false;
   RB_Use->Checked = false;

   ComboBoxLogLevel->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::BitBtnOkClick(TObject *Sender)
{
   stSoliSettings.StatusTop = FormSystemSettings->Label_Status->Top;
   stSoliSettings.StatusHeight = FormSystemSettings->Label_Status->Height;
   stSoliSettings.StatusFontName = FormSystemSettings->Label_Status->Font->Name;
   stSoliSettings.StatusFontSize = FormSystemSettings->Label_Status->Font->Size;
   stSoliSettings.StatusFontHeight = FormSystemSettings->Label_Status->Font->Height;
   stSoliSettings.VisszaszamlalasTop = FormSystemSettings->Label_Visszaszamlalas->Top;
   stSoliSettings.VisszaszamlalasHeight = FormSystemSettings->Label_Visszaszamlalas->Height;
   stSoliSettings.VisszaszamlalasFontName = FormSystemSettings->Label_Visszaszamlalas->Font->Name;
   stSoliSettings.VisszaszamlalasFontSize = FormSystemSettings->Label_Visszaszamlalas->Font->Size;
   stSoliSettings.VisszaszamlalasFontHeight = FormSystemSettings->Label_Visszaszamlalas->Font->Height;
   stSoliSettings.IdoTop = FormSystemSettings->Label_Ido->Top;
   stSoliSettings.IdoHeight = FormSystemSettings->Label_Ido->Height;
   stSoliSettings.IdoFontName = FormSystemSettings->Label_Ido->Font->Name;
   stSoliSettings.IdoFontSize = FormSystemSettings->Label_Ido->Font->Size;
   stSoliSettings.IdoFontHeight = FormSystemSettings->Label_Ido->Font->Height;
   stSoliSettings.InformacioTop = FormSystemSettings->Label_Informacio->Top;
   stSoliSettings.InformacioHeight = FormSystemSettings->Label_Informacio->Height;
   stSoliSettings.InformacioFontName = FormSystemSettings->Label_Informacio->Font->Name;
   stSoliSettings.InformacioFontSize = FormSystemSettings->Label_Informacio->Font->Size;
   stSoliSettings.InformacioFontHeight = FormSystemSettings->Label_Informacio->Font->Height;
   stSoliSettings.PenzTop = FormSystemSettings->Label_Penz->Top;
   stSoliSettings.PenzHeight = FormSystemSettings->Label_Penz->Height;
   stSoliSettings.PenzFontName = FormSystemSettings->Label_Penz->Font->Name;
   stSoliSettings.PenzFontSize = FormSystemSettings->Label_Penz->Font->Size;
   stSoliSettings.PenzFontHeight = FormSystemSettings->Label_Penz->Font->Height;

   ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::BitBtnFontClick(TObject *Sender)
{
   switch( CurrentLabel )
   {
      case 1:
         FontDialog->Font = Label_Status->Font;
         break;
      case 2:
         FontDialog->Font = Label_Visszaszamlalas->Font;
         break;
      case 3:
         FontDialog->Font = Label_Ido->Font;
         break;
      case 4:
         FontDialog->Font = Label_Informacio->Font;
         break;
      case 5:
         FontDialog->Font = Label_Penz->Font;
         break;
   }
   if( FontDialog->Execute() )
   {
      switch( CurrentLabel )
      {
         case 1:
            Label_Status->Font->Name = FontDialog->Font->Name;
            Label_Status->Font->Size = FontDialog->Font->Size;
            Label_Status->Font->Color = FontDialog->Font->Color;
            Label_Status->Font->Height = FontDialog->Font->Height;
            Label_Status->AutoSize = true;
            Label_Status->AutoSize = false;
            Label_Status->Width = PanelWidth-10;
            BevelSelection->Left = Label_Status->Left;
            BevelSelection->Top = Label_Status->Top;
            BevelSelection->Width = Label_Status->Width;
            BevelSelection->Height = Label_Status->Height;
            if( RB_Alap->Checked )
            {
               stSoliSettings.StatusFontColorDef = FontDialog->Font->Color;
            }
            else if( RB_Var->Checked )
            {
               stSoliSettings.StatusFontColorPre = FontDialog->Font->Color;
            }
            else if( RB_Use->Checked )
            {
               stSoliSettings.StatusFontColorUse = FontDialog->Font->Color;
            }
            break;
         case 2:
            Label_Visszaszamlalas->Font->Name = FontDialog->Font->Name;
            Label_Visszaszamlalas->Font->Size = FontDialog->Font->Size;
            Label_Visszaszamlalas->Font->Color = FontDialog->Font->Color;
            Label_Visszaszamlalas->Font->Height = FontDialog->Font->Height;
            Label_Visszaszamlalas->AutoSize = true;
            Label_Visszaszamlalas->AutoSize = false;
            Label_Visszaszamlalas->Width = PanelWidth-10;
            BevelSelection->Left = Label_Visszaszamlalas->Left;
            BevelSelection->Top = Label_Visszaszamlalas->Top;
            BevelSelection->Width = Label_Visszaszamlalas->Width;
            BevelSelection->Height = Label_Visszaszamlalas->Height;
            if( RB_Alap->Checked )
            {
               stSoliSettings.VisszaszamlalasFontColorDef = FontDialog->Font->Color;
            }
            else if( RB_Var->Checked )
            {
               stSoliSettings.VisszaszamlalasFontColorPre = FontDialog->Font->Color;
            }
            else if( RB_Use->Checked )
            {
               stSoliSettings.VisszaszamlalasFontColorUse = FontDialog->Font->Color;
            }
            break;
         case 3:
            Label_Ido->Font->Name = FontDialog->Font->Name;
            Label_Ido->Font->Size = FontDialog->Font->Size;
            Label_Ido->Font->Color = FontDialog->Font->Color;
            Label_Ido->Font->Height = FontDialog->Font->Height;
            Label_Ido->AutoSize = true;
            Label_Ido->AutoSize = false;
            Label_Ido->Width = PanelWidth-10;
            BevelSelection->Left = Label_Ido->Left;
            BevelSelection->Top = Label_Ido->Top;
            BevelSelection->Width = Label_Ido->Width;
            BevelSelection->Height = Label_Ido->Height;
            if( RB_Alap->Checked )
            {
               stSoliSettings.IdoFontColorDef = FontDialog->Font->Color;
            }
            else if( RB_Var->Checked )
            {
               stSoliSettings.IdoFontColorPre = FontDialog->Font->Color;
            }
            else if( RB_Use->Checked )
            {
               stSoliSettings.IdoFontColorUse = FontDialog->Font->Color;
            }
            break;
         case 4:
            Label_Informacio->Font->Name = FontDialog->Font->Name;
            Label_Informacio->Font->Size = FontDialog->Font->Size;
            Label_Informacio->Font->Color = FontDialog->Font->Color;
            Label_Informacio->Font->Height = FontDialog->Font->Height;
            Label_Informacio->AutoSize = true;
            Label_Informacio->AutoSize = false;
            Label_Informacio->Width = PanelWidth-10;
            BevelSelection->Left = Label_Informacio->Left;
            BevelSelection->Top = Label_Informacio->Top;
            BevelSelection->Width = Label_Informacio->Width;
            BevelSelection->Height = Label_Informacio->Height;
            if( RB_Alap->Checked )
            {
               stSoliSettings.InformacioFontColorDef = FontDialog->Font->Color;
            }
            else if( RB_Var->Checked )
            {
               stSoliSettings.InformacioFontColorPre = FontDialog->Font->Color;
            }
            else if( RB_Use->Checked )
            {
               stSoliSettings.InformacioFontColorUse = FontDialog->Font->Color;
            }
            break;
         case 5:
            Label_Penz->Font->Name = FontDialog->Font->Name;
            Label_Penz->Font->Size = FontDialog->Font->Size;
            Label_Penz->Font->Color = FontDialog->Font->Color;
            Label_Penz->Font->Height = FontDialog->Font->Height;
            Label_Penz->AutoSize = true;
            Label_Penz->AutoSize = false;
            Label_Penz->Width = PanelWidth-10;
            BevelSelection->Left = Label_Penz->Left;
            BevelSelection->Top = Label_Penz->Top;
            BevelSelection->Width = Label_Penz->Width;
            BevelSelection->Height = Label_Penz->Height;
            if( RB_Alap->Checked )
            {
               stSoliSettings.PenzFontColorDef = FontDialog->Font->Color;
            }
            else if( RB_Var->Checked )
            {
               stSoliSettings.PenzFontColorPre = FontDialog->Font->Color;
            }
            else if( RB_Use->Checked )
            {
               stSoliSettings.PenzFontColorUse = FontDialog->Font->Color;
            }
            break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::Label_StatusClick(TObject *Sender)
{
   CurrentLabel = 1;
   BevelSelection->Left = Label_Status->Left;
   BevelSelection->Top = Label_Status->Top;
   BevelSelection->Width = Label_Status->Width;
   BevelSelection->Height = Label_Status->Height;
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::Label_VisszaszamlalasClick(TObject *Sender)
{
   CurrentLabel = 2;
   BevelSelection->Left = Label_Visszaszamlalas->Left;
   BevelSelection->Top = Label_Visszaszamlalas->Top;
   BevelSelection->Width = Label_Visszaszamlalas->Width;
   BevelSelection->Height = Label_Visszaszamlalas->Height;
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::Label_IdoClick(TObject *Sender)
{
   CurrentLabel = 3;
   BevelSelection->Left = Label_Ido->Left;
   BevelSelection->Top = Label_Ido->Top;
   BevelSelection->Width = Label_Ido->Width;
   BevelSelection->Height = Label_Ido->Height;
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::Label_InformacioClick(TObject *Sender)
{
   CurrentLabel = 4;
   BevelSelection->Left = Label_Informacio->Left;
   BevelSelection->Top = Label_Informacio->Top;
   BevelSelection->Width = Label_Informacio->Width;
   BevelSelection->Height = Label_Informacio->Height;
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::Label_PenzClick(TObject *Sender)
{
   CurrentLabel = 5;
   BevelSelection->Left = Label_Penz->Left;
   BevelSelection->Top = Label_Penz->Top;
   BevelSelection->Width = Label_Penz->Width;
   BevelSelection->Height = Label_Penz->Height;
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::BitBtnUpClick(TObject *Sender)
{
   switch( CurrentLabel )
   {
      case 1:
         Label_Status->Top--;
         break;
      case 2:
         Label_Visszaszamlalas->Top--;
         break;
      case 3:
         Label_Ido->Top--;
         break;
      case 4:
         Label_Informacio->Top--;
         break;
      case 5:
         Label_Penz->Top--;
         break;
   }
   BevelSelection->Top--;
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::BitBtnDownClick(TObject *Sender)
{
   switch( CurrentLabel )
   {
      case 1:
         Label_Status->Top++;
         break;
      case 2:
         Label_Visszaszamlalas->Top++;
         break;
      case 3:
         Label_Ido->Top++;
         break;
      case 4:
         Label_Informacio->Top++;
         break;
      case 5:
         Label_Penz->Top++;
         break;
   }
   BevelSelection->Top++;
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::BitBtnColorClick(TObject *Sender)
{
   if( ColorDialog->Execute() )
   {
      PanelSzolarium->Color = ColorDialog->Color;
      if( RB_Alap->Checked )
      {
         stSoliSettings.ColorDefault = ColorDialog->Color;
      }
      else if( RB_Var->Checked )
      {
         stSoliSettings.ColorPrepare = ColorDialog->Color;
      }
      else if( RB_Use->Checked )
      {
         stSoliSettings.ColorUsed = ColorDialog->Color;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::RB_AlapClick(TObject *Sender)
{
   PanelSzolarium->Color = (TColor)stSoliSettings.ColorDefault;
   Label_Status->Font->Color = (TColor)stSoliSettings.StatusFontColorDef;
   Label_Visszaszamlalas->Font->Color = (TColor)stSoliSettings.VisszaszamlalasFontColorDef;
   Label_Ido->Font->Color = (TColor)stSoliSettings.IdoFontColorDef;
   Label_Informacio->Font->Color = (TColor)stSoliSettings.InformacioFontColorDef;
   Label_Penz->Font->Color = (TColor)stSoliSettings.PenzFontColorDef;
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::RB_VarClick(TObject *Sender)
{
   PanelSzolarium->Color = (TColor)stSoliSettings.ColorPrepare;
   Label_Status->Font->Color = (TColor)stSoliSettings.StatusFontColorPre;
   Label_Visszaszamlalas->Font->Color = (TColor)stSoliSettings.VisszaszamlalasFontColorPre;
   Label_Ido->Font->Color = (TColor)stSoliSettings.IdoFontColorPre;
   Label_Informacio->Font->Color = (TColor)stSoliSettings.InformacioFontColorPre;
   Label_Penz->Font->Color = (TColor)stSoliSettings.PenzFontColorPre;
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::RB_UseClick(TObject *Sender)
{
   PanelSzolarium->Color = (TColor)stSoliSettings.ColorUsed;
   Label_Status->Font->Color = (TColor)stSoliSettings.StatusFontColorUse;
   Label_Visszaszamlalas->Font->Color = (TColor)stSoliSettings.VisszaszamlalasFontColorUse;
   Label_Ido->Font->Color = (TColor)stSoliSettings.IdoFontColorUse;
   Label_Informacio->Font->Color = (TColor)stSoliSettings.InformacioFontColorUse;
   Label_Penz->Font->Color = (TColor)stSoliSettings.PenzFontColorUse;
}
//---------------------------------------------------------------------------
void __fastcall TFormSystemSettings::PanelExtendedClick(TObject *Sender)
{
   if( bExtended )
   {
      PanelExtended->BevelOuter = bvRaised;
      bExtended = false;
      Image1->Visible = true;
      Image2->Visible = false;
   }
   else
   {
      PanelExtended->BevelOuter = bvLowered;
      bExtended = true;
      Image1->Visible = false;
      Image2->Visible = true;
   }
}
//---------------------------------------------------------------------------


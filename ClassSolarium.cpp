//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>

#include "Classes.h"
#include "Database.h"
#include "Language.h"
//---------------------------------------------------------------------------
CS_Solarium::CS_Solarium( TObject* FormParent,
                          int nID,
                          int Left,
                          int Top,
                          int Width,
                          int Height )
{
   bDebugShowAllText = false;

   nSzolariumID = nID;
   memset( stAdat.strNev, 0, sizeof(stAdat.strNev) );
   sprintf( stAdat.strNev, FormLanguage->LangStr(STR_SOLARIUM_X).c_str(), nID+1 );
   stAdat.bInfraSzolarium = false;
   stAdat.nIdoVetkozes = 60;
   stAdat.nIdoUtohutes = 60;
   stAdat.nIdoSzauna = 0;
   stAdat.nKedvezmenyIdoStart = 0;
   stAdat.nKedvezmenyIdoStop = 0;
   stAdat.nCsoUzemoraMax = 600*3600;
   stAdat.nCsoUzemora = 0;
   stAdat.bShowCsoUzemora = false;
   stAdat.nMaxBarnulas = 100;
   memset( &(stAdat.stIdoForint), 0, sizeof(typ_idoforint)*40 );
   memset( &(stAdat.stIdoForintKedv), 0, sizeof(typ_idoforint)*40 );

   cSolariumStatus            = 0;
   nIdoVisszaszamlalas        = 0;
   nIdoKovStatus              = 0;
   nIdoBarnulas               = 0;
   nIdoMegszakitott           = 0;
   nForintBarnulas            = 0;
   bStatusSteril              = true;
   bCsoCsereSzukseges         = false;
   bFizetniKell               = false;
   bCsovekKikapcsolva         = false;
   bStopped                   = false;

   nBerletEgyseg              = 0;
   nIdoBerlet                 = 0;

   bPanelSelected             = false;

   PanelSzolarium = new TPanel( FormParent );
   PanelSzolarium->Parent = (TWinControl*)FormParent;
   PanelSzolarium->BevelWidth = 2;

   Panel_Nev = new TPanel( PanelSzolarium );
   Panel_Nev->Parent = PanelSzolarium;
   Panel_Nev->Caption = AnsiString( stAdat.strNev );
   Panel_Nev->Left = 2;
   Panel_Nev->Top = 2;
   Panel_Nev->Height = 30;
   Panel_Nev->Font->Name = "Times New Roman";
   Panel_Nev->Font->Size = 14;
   Panel_Nev->Font->Color = clCaptionText;

   Label_Status = new TLabel( PanelSzolarium );
   Label_Status->Parent = PanelSzolarium;
   Label_Status->AutoSize = false;
   Label_Status->Caption = "SZOL�RIUM ST�TUSZ";
   Label_Status->Left = 5;
   Label_Status->Top = stSoliSettings.StatusTop; // 38;
   Label_Status->Height = stSoliSettings.StatusHeight; // 29;
   Label_Status->Alignment = taCenter;
   Label_Status->Font->Name = stSoliSettings.StatusFontName; //"Times New Roman";
   Label_Status->Font->Size = stSoliSettings.StatusFontSize; // 14;
   Label_Status->Font->Style = TFontStyles()<< fsBold;
   Label_Status->Font->Color = (TColor)stSoliSettings.StatusFontColorDef; // clGreen;
   Label_Status->Font->Height = stSoliSettings.StatusFontHeight;
   Label_Status->Visible = bDebugShowAllText;

   Label_Visszaszamlalas = new TLabel( PanelSzolarium );
   Label_Visszaszamlalas->Parent = PanelSzolarium;
   Label_Visszaszamlalas->AutoSize = false;
   Label_Visszaszamlalas->Caption = "00 : 00";
   Label_Visszaszamlalas->Left = 5;
   Label_Visszaszamlalas->Top = stSoliSettings.VisszaszamlalasTop; // 61;
   Label_Visszaszamlalas->Height = stSoliSettings.VisszaszamlalasHeight; // 43;
   Label_Visszaszamlalas->Alignment = taCenter;
   Label_Visszaszamlalas->Font->Name = stSoliSettings.VisszaszamlalasFontName; // "Times New Roman";
   Label_Visszaszamlalas->Font->Size = stSoliSettings.VisszaszamlalasFontSize; // 26;
   Label_Visszaszamlalas->Font->Style = TFontStyles()<< fsBold;
   Label_Visszaszamlalas->Font->Color = (TColor)stSoliSettings.VisszaszamlalasFontColorDef; // clBlack;
   Label_Visszaszamlalas->Font->Height = stSoliSettings.VisszaszamlalasFontHeight;
   Label_Visszaszamlalas->Visible = bDebugShowAllText;

   Label_Ido = new TLabel( PanelSzolarium );
   Label_Ido->Parent = PanelSzolarium;
   Label_Ido->AutoSize = false;
   Label_Ido->Caption = "00 : 00";
   Label_Ido->Left = 5;
   Label_Ido->Top = stSoliSettings.IdoTop;// 100;
   Label_Ido->Height = stSoliSettings.IdoHeight;// 26;
   Label_Ido->Alignment = taCenter;
   Label_Ido->Font->Name = stSoliSettings.IdoFontName;// "Times New Roman";
   Label_Ido->Font->Size = stSoliSettings.IdoFontSize;// 16;
   Label_Ido->Font->Style = TFontStyles()<< fsBold;
   Label_Ido->Font->Color = (TColor)stSoliSettings.IdoFontColorDef;// clGreen;
   Label_Ido->Font->Height = stSoliSettings.IdoFontHeight;
   Label_Ido->Visible = bDebugShowAllText;

   Label_Informacio = new TLabel( PanelSzolarium );
   Label_Informacio->Parent = PanelSzolarium;
   Label_Informacio->AutoSize = false;
   Label_Informacio->Caption = "SZOLARIUM INFO";
   Label_Informacio->Left = 5;
   Label_Informacio->Top = stSoliSettings.InformacioTop;// 125;
   Label_Informacio->Height = stSoliSettings.InformacioHeight;// 29;
   Label_Informacio->Alignment = taCenter;
   Label_Informacio->Font->Name = stSoliSettings.InformacioFontName; // "Times New Roman";
   Label_Informacio->Font->Size = stSoliSettings.InformacioFontSize; // 14;
   Label_Informacio->Font->Style = TFontStyles()<< fsBold;
   Label_Informacio->Font->Color = (TColor)stSoliSettings.InformacioFontColorDef;// clMaroon;
   Label_Informacio->Font->Height = stSoliSettings.InformacioFontHeight;
   Label_Informacio->Visible = bDebugShowAllText;

   Label_Penz = new TLabel( PanelSzolarium );
   Label_Penz->Parent = PanelSzolarium;
   Label_Penz->AutoSize = false;
   Label_Penz->Caption = "100 Ft.";
   Label_Penz->Left = 5;
   Label_Penz->Top = stSoliSettings.PenzTop;// 152;
   Label_Penz->Height = stSoliSettings.PenzHeight;// 43;
   Label_Penz->Alignment = taCenter;
   Label_Penz->Font->Name = stSoliSettings.PenzFontName;// "Times New Roman";
   Label_Penz->Font->Size = stSoliSettings.PenzFontSize;// 26;
   Label_Penz->Font->Style = TFontStyles()<< fsBold;
   Label_Penz->Font->Color = (TColor)stSoliSettings.PenzFontColorDef;// clBlack;
   Label_Penz->Font->Height = stSoliSettings.PenzFontHeight;
   Label_Penz->Visible = bDebugShowAllText;

   ProgressBarCso = new TProgressBar( PanelSzolarium );
   ProgressBarCso->Parent = PanelSzolarium;
   ProgressBarCso->Visible = stAdat.bShowCsoUzemora;
   ProgressBarCso->Left = 5;
   ProgressBarCso->Top = 210;
   ProgressBarCso->Height = 6;
   ProgressBarCso->Smooth = true;
   ProgressBarCso->Max = stAdat.nCsoUzemoraMax;
   ProgressBarCso->Position = stAdat.nCsoUzemora;

   Resize( Left, Top, Width, Height );

   DataFileName = AnsiString( SOLARIUM_FILE )+AnsiString( nID )+AnsiString( ".dat" );
   LoadDataFromFile();
   DataRefresh();
}
//---------------------------------------------------------------------------
CS_Solarium::~CS_Solarium()
{
   //SaveDataToFile( DataFileName.c_str() );
   delete PanelSzolarium;
}
//---------------------------------------------------------------------------
void CS_Solarium::Select()
{
   bPanelSelected = true;
   Panel_Nev->Color = clActiveCaption;
   Panel_Nev->Font->Color = clCaptionText;
}
//---------------------------------------------------------------------------
void CS_Solarium::Deselect()
{
   bPanelSelected = false;
   Panel_Nev->Color = clInactiveCaption;
   Panel_Nev->Font->Color = clInactiveCaptionText;
}
//---------------------------------------------------------------------------
void CS_Solarium::ShowHideUzemora( bool bVisible )
{
   ProgressBarCso->Visible = bVisible;
}
//---------------------------------------------------------------------------
void CS_Solarium::Resize( int Left, int Top, int Width, int Height )
{
   PanelSzolarium->Left = Left;
   PanelSzolarium->Top = Top;
   PanelSzolarium->Width = Width;
   PanelSzolarium->Height = Height;

   Panel_Nev->Width = Width-4;
   Label_Status->Width = Width-10;
   Label_Visszaszamlalas->Width = Width-10;
   Label_Ido->Width = Width-10;
   Label_Informacio->Width = Width-10;
   Label_Penz->Width = Width-10;
   ProgressBarCso->Width = Width-10;

   Label_Status->Top = 38+(Height-214)/2;
   Label_Visszaszamlalas->Top = 61+(Height-214)/2;
   Label_Ido->Top = 100+(Height-214)/2;
   Label_Informacio->Top = 125+(Height-214)/2;
   Label_Penz->Top = 152+(Height-214)/2;
   ProgressBarCso->Top = Height-8;
}
//---------------------------------------------------------------------------
void CS_Solarium::StatuszBeallitas( char nStatus )
{
   char  strTemp[100];

   memset( strTemp, 0, sizeof(strTemp) );
   cSolariumStatus = nStatus;

   switch( cSolariumStatus )
   {
      case STATUS_ALAP:
         nIdoBarnulas      = 0;
         nIdoMegszakitott  = 0;
         nForintBarnulas   = 0;
         nBerletEgyseg     = 0;
         nIdoBerlet        = 0;
         for( int i=0; i<(int)BerletHasznal.size(); )
         {
            BerletHasznal.erase( BerletHasznal.begin() );
         }
         Label_Status->Caption = "";
         Label_Status->Visible = false;
         Label_Visszaszamlalas->Caption = "";
         Label_Visszaszamlalas->Visible = false;
         Label_Ido->Caption = "";
         Label_Ido->Visible = false;
         break;

      case STATUS_VETKOZES:
         nIdoVisszaszamlalas = stAdat.nIdoVetkozes;
         nIdoKovStatus = nIdoBarnulas;
         Label_Status->Caption = FormLanguage->LangStr(STR_STATUS_UNDRESS);
         Label_Status->Visible = true;
         break;

      case STATUS_SZAUNAZAS:
         Label_Status->Caption = FormLanguage->LangStr(STR_STATUS_SAUNA);
         Label_Status->Visible = true;
         break;

      case STATUS_VARAKOZAS:
         Label_Status->Caption = FormLanguage->LangStr(STR_STATUS_WAIT);
         Label_Status->Visible = true;
         break;

      case STATUS_BARNULAS:
      {
         Label_Status->Caption = FormLanguage->LangStr(STR_STATUS_SOLARIUM_USE);
         Label_Status->Visible = true;

         strLogMsg = AnsiString( "Szol�rium haszn�lat k�nyvel�s [" ) +
                     AnsiString( stAdat.strNev ) +
                     AnsiString( "] [" ) +
                     AnsiString( nIdoBarnulas ) +
                     AnsiString( "] id� [" ) +
                     AnsiString( nForintBarnulas ) +
                     AnsiString( "] forintid� [" ) +
                     AnsiString( nIdoBerlet ) +
                     AnsiString( "] b�rletid� [" ) +
                     AnsiString( nBerletEgyseg ) +
                     AnsiString( "] egys�g" );
         LOG2( strLogMsg );
         pKonyv->AddSzolariumKonyv( dCurrentMuszak,            // dMuszakID
                                    nSzolariumID,              // nSzolariumID
                                    nIdoBarnulas,              // dUzemeltIdo
                                    nIdoBerlet,                // dUzemeltBerletIdo
                                    nBerletEgyseg,             // dUzemeltBerletEgyseg
                                    nIdoBarnulas-nIdoBerlet,   // dUzemeltFtIdo
                                    nForintBarnulas,           // dUzemeltFt
                                    0,                         // dUzemeltMegszakitott
                                    0,                         // dCsoUzemora
                                    stAdat.strNev );
         nForintBarnulas = 0;
         DataRefresh( true );
         break;
      }
      case STATUS_UTOHUTES:
      {
         Label_Status->Caption = FormLanguage->LangStr(STR_STATUS_POSTPROCESS);
         Label_Status->Visible = true;
         sprintf( strTemp, "%02d : %02d", nIdoVisszaszamlalas/60, nIdoVisszaszamlalas%60 );
         Label_Visszaszamlalas->Caption = AnsiString( strTemp );
         Label_Visszaszamlalas->Visible = true;
         Label_Ido->Caption = "";
         Label_Ido->Visible = false;
         bStatusSteril = false;

         pKonyv->AddSzolariumKonyv( dCurrentMuszak,            // dMuszakID
                                    nSzolariumID,              // nSzolariumID
                                    0,                         // dUzemeltIdo
                                    0,                         // dUzemeltBerletIdo
                                    0,                         // dUzemeltBerletEgyseg
                                    0,                         // dUzemeltFtIdo
                                    0,                         // dUzemeltFt
                                    nIdoMegszakitott,              // dUzemeltMegszakitott
                                    nIdoBarnulas-nIdoMegszakitott, // dCsoUzemora
                                    stAdat.strNev );
         DataRefresh( true );
         break;
      }
   }
   switch( cSolariumStatus )
   {
      case STATUS_VETKOZES:
      case STATUS_SZAUNAZAS:
      case STATUS_BARNULAS:
         sprintf( strTemp, "%02d : %02d", nIdoVisszaszamlalas/60, nIdoVisszaszamlalas%60 );
         Label_Visszaszamlalas->Caption = AnsiString( strTemp );
         Label_Visszaszamlalas->Visible = true;
         sprintf( strTemp, "%02d : %02d", nIdoKovStatus/60, nIdoKovStatus%60 );
         Label_Ido->Caption = AnsiString( strTemp );
         Label_Ido->Visible = true;
         break;
   }
}
//---------------------------------------------------------------------------
void CS_Solarium::StatuszUpdate()
{
   char  strTemp[100];

   memset( strTemp, 0, sizeof(strTemp) );

   if( cSolariumStatus != STATUS_ALAP )
   {
      nIdoVisszaszamlalas--;
      sprintf( strTemp, "%02d : %02d", nIdoVisszaszamlalas/60, nIdoVisszaszamlalas%60 );
      Label_Visszaszamlalas->Caption = AnsiString( strTemp );
   }
   if( cSolariumStatus == STATUS_BARNULAS )
   {
      stAdat.nCsoUzemora++;
      ProgressBarCso->Position = stAdat.nCsoUzemora;
      if( ProgressBarCso->Position >= ProgressBarCso->Max )
      {
         bCsoCsereSzukseges = true;
      }
   }
   if( nIdoVisszaszamlalas < 1 )
   {
      switch( cSolariumStatus )
      {
         case STATUS_VETKOZES:
            if( stAdat.bInfraSzolarium && stAdat.nIdoSzauna > 0 )
            {
               nIdoVisszaszamlalas = stAdat.nIdoSzauna;
               nIdoKovStatus = nIdoBarnulas;
               StatuszBeallitas( STATUS_SZAUNAZAS );
            }
            else
            {
               nIdoVisszaszamlalas = nIdoBarnulas;
               nIdoKovStatus = stAdat.nIdoUtohutes;
               StatuszBeallitas( STATUS_BARNULAS );
            }
            break;

         case STATUS_SZAUNAZAS:
            nIdoVisszaszamlalas = 3;
            nIdoKovStatus = nIdoBarnulas;
            StatuszBeallitas( STATUS_VARAKOZAS );
            break;

         case STATUS_VARAKOZAS:
            nIdoVisszaszamlalas = nIdoBarnulas;
            nIdoKovStatus = stAdat.nIdoUtohutes;
            StatuszBeallitas( STATUS_BARNULAS );
            break;

         case STATUS_BARNULAS:
            nIdoVisszaszamlalas = stAdat.nIdoUtohutes;
            nIdoKovStatus = 0;
            StatuszBeallitas( STATUS_UTOHUTES );
            break;

         case STATUS_UTOHUTES:
            nIdoVisszaszamlalas = 0;
            nIdoKovStatus = 0;
            StatuszBeallitas( STATUS_ALAP );
            break;
      }
   }
}
//---------------------------------------------------------------------------
void CS_Solarium::UpdateExtendedView( TPanel *pPanelSzolarium,
                                      TPanel *pPanel_Nev,
                                      TLabel *pLabel_Status,
                                      TLabel *pLabel_Visszaszamlalas,
                                      TLabel *pLabel_Ido,
                                      TLabel *pLabel_Informacio,
                                      TLabel *pLabel_Penz,
                                      TProgressBar *pProgressBarCso )
{
   pPanelSzolarium->Color = PanelSzolarium->Color;

   pPanel_Nev->Caption = Panel_Nev->Caption;

   pLabel_Status->Top = stSoliSettings.StatusTop; // 38;
   pLabel_Status->Height = stSoliSettings.StatusHeight; // 29;
   pLabel_Status->Font->Name = stSoliSettings.StatusFontName; // 14;
   pLabel_Status->Font->Size = stSoliSettings.StatusFontSize; // 14;
   pLabel_Status->Font->Height = stSoliSettings.StatusFontHeight;
   pLabel_Status->Font->Color = Label_Status->Font->Color;
   pLabel_Status->Caption = Label_Status->Caption;
   pLabel_Status->Visible = Label_Status->Visible;

   pLabel_Visszaszamlalas->Top = stSoliSettings.VisszaszamlalasTop; // 61;
   pLabel_Visszaszamlalas->Height = stSoliSettings.VisszaszamlalasHeight; // 43;
   pLabel_Visszaszamlalas->Font->Name = stSoliSettings.VisszaszamlalasFontName; // 26;
   pLabel_Visszaszamlalas->Font->Size = stSoliSettings.VisszaszamlalasFontSize; // 26;
   pLabel_Visszaszamlalas->Font->Height = stSoliSettings.VisszaszamlalasFontHeight;
   pLabel_Visszaszamlalas->Font->Color = Label_Visszaszamlalas->Font->Color;
   pLabel_Visszaszamlalas->Caption = Label_Visszaszamlalas->Caption;
   pLabel_Visszaszamlalas->Visible = Label_Visszaszamlalas->Visible;

   pLabel_Ido->Top = stSoliSettings.IdoTop;// 100;
   pLabel_Ido->Height = stSoliSettings.IdoHeight;// 26;
   pLabel_Ido->Font->Name = stSoliSettings.IdoFontName;// 16;
   pLabel_Ido->Font->Size = stSoliSettings.IdoFontSize;// 16;
   pLabel_Ido->Font->Height = stSoliSettings.IdoFontHeight;
   pLabel_Ido->Font->Color = Label_Ido->Font->Color;
   pLabel_Ido->Caption = Label_Ido->Caption;
   pLabel_Ido->Visible = Label_Ido->Visible;

   pLabel_Informacio->Top = stSoliSettings.InformacioTop;// 125;
   pLabel_Informacio->Height = stSoliSettings.InformacioHeight;// 29;
   pLabel_Informacio->Font->Name = stSoliSettings.InformacioFontName;// 14;
   pLabel_Informacio->Font->Size = stSoliSettings.InformacioFontSize;// 14;
   pLabel_Informacio->Font->Height = stSoliSettings.InformacioFontHeight;
   pLabel_Informacio->Font->Color = Label_Informacio->Font->Color;
   pLabel_Informacio->Caption = Label_Informacio->Caption;
   pLabel_Informacio->Visible = Label_Informacio->Visible;

   pLabel_Penz->Top = stSoliSettings.PenzTop;// 152;
   pLabel_Penz->Height = stSoliSettings.PenzHeight;// 43;
   pLabel_Penz->Font->Name = stSoliSettings.PenzFontName;// 26;
   pLabel_Penz->Font->Size = stSoliSettings.PenzFontSize;// 26;
   pLabel_Penz->Font->Height = stSoliSettings.PenzFontHeight;
   pLabel_Penz->Font->Color = Label_Penz->Font->Color;
   pLabel_Penz->Caption = Label_Penz->Caption;
   pLabel_Penz->Visible = Label_Penz->Visible;

   pProgressBarCso->Visible = ProgressBarCso->Visible;
   pProgressBarCso->Max = ProgressBarCso->Max;
   pProgressBarCso->Position = ProgressBarCso->Position;
}
//---------------------------------------------------------------------------
void CS_Solarium::StatuszUpdateImmediate()
{
   Label_Status->Top = stSoliSettings.StatusTop; // 38;
   Label_Status->Height = stSoliSettings.StatusHeight; // 29;
   Label_Status->Font->Name = stSoliSettings.StatusFontName; // 14;
   Label_Status->Font->Size = stSoliSettings.StatusFontSize; // 14;
   Label_Status->Font->Height = stSoliSettings.StatusFontHeight;

   Label_Visszaszamlalas->Top = stSoliSettings.VisszaszamlalasTop; // 61;
   Label_Visszaszamlalas->Height = stSoliSettings.VisszaszamlalasHeight; // 43;
   Label_Visszaszamlalas->Font->Name = stSoliSettings.VisszaszamlalasFontName; // 26;
   Label_Visszaszamlalas->Font->Size = stSoliSettings.VisszaszamlalasFontSize; // 26;
   Label_Visszaszamlalas->Font->Height = stSoliSettings.VisszaszamlalasFontHeight;

   Label_Ido->Top = stSoliSettings.IdoTop;// 100;
   Label_Ido->Height = stSoliSettings.IdoHeight;// 26;
   Label_Ido->Font->Name = stSoliSettings.IdoFontName;// 16;
   Label_Ido->Font->Size = stSoliSettings.IdoFontSize;// 16;
   Label_Ido->Font->Height = stSoliSettings.IdoFontHeight;

   Label_Informacio->Top = stSoliSettings.InformacioTop;// 125;
   Label_Informacio->Height = stSoliSettings.InformacioHeight;// 29;
   Label_Informacio->Font->Name = stSoliSettings.InformacioFontName;// 14;
   Label_Informacio->Font->Size = stSoliSettings.InformacioFontSize;// 14;
   Label_Informacio->Font->Height = stSoliSettings.InformacioFontHeight;

   Label_Penz->Top = stSoliSettings.PenzTop;// 152;
   Label_Penz->Height = stSoliSettings.PenzHeight;// 43;
   Label_Penz->Font->Name = stSoliSettings.PenzFontName;// 26;
   Label_Penz->Font->Size = stSoliSettings.PenzFontSize;// 26;
   Label_Penz->Font->Height = stSoliSettings.PenzFontHeight;

   if( bCsoCsereSzukseges )
   {
      Label_Informacio->Caption = FormLanguage->LangStr(STR_TUBECHANGE_REQUIRED);
      Label_Informacio->Visible = true;
   }
   else
   {
      if( !bStatusSteril )
      {
         Label_Informacio->Caption = FormLanguage->LangStr(STR_NOT_STERIL);
         Label_Informacio->Visible = true;
      }
      else
      {
         Label_Informacio->Caption = "";
         Label_Informacio->Visible = false;
      }
   }
   if( cSolariumStatus == STATUS_BARNULAS )
   {
      if( bStopped )
         Label_Status->Caption = FormLanguage->LangStr(STR_STATUS_SOLARIUM_HALTED);
      else
         Label_Status->Caption = FormLanguage->LangStr(STR_STATUS_SOLARIUM_USE);
   }
   switch( cSolariumStatus )
   {
      case STATUS_SZAUNAZAS:
      case STATUS_BARNULAS:
         PanelSzolarium->Color = (TColor)stSoliSettings.ColorUsed;
         Label_Status->Font->Color = (TColor)stSoliSettings.StatusFontColorUse;
         Label_Visszaszamlalas->Font->Color = (TColor)stSoliSettings.VisszaszamlalasFontColorUse;
         Label_Ido->Font->Color = (TColor)stSoliSettings.IdoFontColorUse;
         Label_Informacio->Font->Color = (TColor)stSoliSettings.InformacioFontColorUse;
         Label_Penz->Font->Color = (TColor)stSoliSettings.PenzFontColorUse;
         break;

      case STATUS_VETKOZES:
      case STATUS_UTOHUTES:
         PanelSzolarium->Color = (TColor)stSoliSettings.ColorPrepare;
         Label_Status->Font->Color = (TColor)stSoliSettings.StatusFontColorPre;
         Label_Visszaszamlalas->Font->Color = (TColor)stSoliSettings.VisszaszamlalasFontColorPre;
         Label_Ido->Font->Color = (TColor)stSoliSettings.IdoFontColorPre;
         Label_Informacio->Font->Color = (TColor)stSoliSettings.InformacioFontColorPre;
         Label_Penz->Font->Color = (TColor)stSoliSettings.PenzFontColorPre;
         break;

      case STATUS_ALAP:
         PanelSzolarium->Color = (TColor)stSoliSettings.ColorDefault;
         Label_Status->Font->Color = (TColor)stSoliSettings.StatusFontColorDef;
         Label_Visszaszamlalas->Font->Color = (TColor)stSoliSettings.VisszaszamlalasFontColorDef;
         Label_Ido->Font->Color = (TColor)stSoliSettings.IdoFontColorDef;
         Label_Informacio->Font->Color = (TColor)stSoliSettings.InformacioFontColorDef;
         Label_Penz->Font->Color = (TColor)stSoliSettings.PenzFontColorDef;
         break;
   }
}
//---------------------------------------------------------------------------
// Szauna haszn�lat ciklus�ban a szauna haszn�lat le�ll�t�sa �s a
// szol�rium �trak�sa a k�vetkez� st�tuszba
//---------------------------------------------------------------------------
void CS_Solarium::StatuszSzaunaStop()
{
   if( cSolariumStatus == STATUS_SZAUNAZAS )
   {
      nIdoVisszaszamlalas = 1;
      StatuszUpdate();
   }
}
//---------------------------------------------------------------------------
// Szol�rium vetk�z�si ciklus�ban a vetk�z�s le�ll�t�sa �s a
// szol�rium �trak�sa a k�vetkez� st�tuszba
//---------------------------------------------------------------------------
void CS_Solarium::StatuszVetkozesStop()
{
   if( cSolariumStatus == STATUS_VETKOZES )
   {
      nIdoVisszaszamlalas = 1;
      StatuszUpdate();
   }
}
//---------------------------------------------------------------------------
// Szol�rium Timer/id� lek�rdez�se
//---------------------------------------------------------------------------
int CS_Solarium::GetSzoliIdo()
{
   return nIdoVisszaszamlalas;
}
//---------------------------------------------------------------------------
// Szol�rium Barnul�s id� lek�rdez�se
//---------------------------------------------------------------------------
int CS_Solarium::GetBarnulasIdo()
{
   return nIdoBarnulas;
}
//---------------------------------------------------------------------------
// Szol�rium vetk�z�si szakasz ind�t�sa
//---------------------------------------------------------------------------
void CS_Solarium::Inditas()
{
   StatuszBeallitas( STATUS_VETKOZES );
}
//---------------------------------------------------------------------------
void CS_Solarium::Fizetve()
{
   Label_Penz->Caption = "";
   Label_Penz->Visible = false;
   bFizetniKell = false;
}
//---------------------------------------------------------------------------
void CS_Solarium::Steril()
{
   if( !bStatusSteril && Label_Informacio->Caption.AnsiCompare(FormLanguage->LangStr(STR_NOT_STERIL))==0 )
   {
      bStatusSteril = true;
   }
}
//---------------------------------------------------------------------------
void CS_Solarium::Veszleallitas( typ_user stUser )
{
   if( cSolariumStatus < STATUS_SZAUNAZAS )
   {
      StartReset( stUser );
      return;
   }

   if( cSolariumStatus == STATUS_BARNULAS )
   {
      nIdoMegszakitott = nIdoVisszaszamlalas;
   }
   nIdoVisszaszamlalas = 1;
   StatuszUpdate();
}
//---------------------------------------------------------------------------
void CS_Solarium::CsoCserelve()
{
   bCsoCsereSzukseges = false;
   stAdat.nCsoUzemora = 0;
   DataRefresh();
}
//---------------------------------------------------------------------------
char CS_Solarium::StatuszLekerdezes()
{
   return cSolariumStatus;
}
//---------------------------------------------------------------------------
bool CS_Solarium::StatuszSteril()
{
   return bStatusSteril;
}
//---------------------------------------------------------------------------
bool CS_Solarium::StatuszCsocserekell()
{
   return bCsoCsereSzukseges;
}
//---------------------------------------------------------------------------
bool CS_Solarium::StatuszFizetnikell()
{
   return bFizetniKell;
}
//---------------------------------------------------------------------------
// Szol�rium adat / megjelen�t�s friss�t�se
//---------------------------------------------------------------------------
void CS_Solarium::DataRefresh( bool bNeedToSave )
{
   // Szol�rium n�v
   Panel_Nev->Caption = AnsiString( stAdat.strNev );

   // Cs��zem�ra cs�k l�that�s�ga, adatai
   ProgressBarCso->Visible = stAdat.bShowCsoUzemora;
   ProgressBarCso->Max = stAdat.nCsoUzemoraMax;
   ProgressBarCso->Position = stAdat.nCsoUzemora;
   if( ProgressBarCso->Position >= ProgressBarCso->Max )
   {
      bCsoCsereSzukseges = true;
   }
   if( bNeedToSave )
   {
      if( SaveDataToFile(DataFileName.c_str()) &&
          CheckDataToFile(DataFileName.c_str()) )
      {
         AnsiString strFile;

         strFile = AnsiString( "Db\\1_" ) + DataFileName;
         if( !SaveDataToFile(strFile.c_str()) ||
             !CheckDataToFile(strFile.c_str()) )
         {
            LOG1( "HIBA: szol�rium biztons�gi ment�s 1 sikertelen #FV#CS_Solarium::DataRefresh" );
         }

         strFile = AnsiString( "Db\\2_" ) + DataFileName;
         if( !SaveDataToFile(strFile.c_str()) ||
             !CheckDataToFile(strFile.c_str()) )
         {
            LOG1( "HIBA: szol�rium biztons�gi ment�s 2 sikertelen #FV#CS_Solarium::DataRefresh" );
         }
      }
      else
      {
         LOG1( "HIBA: szol�rium ment�s sikertelen #FV#CS_Solarium::DataRefresh" );
      }
   }
}
//---------------------------------------------------------------------------
void CS_Solarium::LoadDataFromFile()
{
   FILE  *file = NULL;
   char  strTemp[10];
   int   nErrorMsgID;

   memset( strTemp, 0, sizeof(strTemp) );

/*   if( !CheckAndCorrectDBFiles( DataFileName.c_str(), &nErrorMsgID ) )
   {
      AnsiString  strMsg;
      strMsg.sprintf( "\n\nError Code: sys110\nError ID: %d", nErrorMsgID );
      throw Exception( strMsg );
   }*/

   file = fopen( DataFileName.c_str(), "rb" );
   if( file != NULL )
   {
      fread( strTemp, 10, 1, file );
      if( strcmp( SOLARIUM_FILE_VERSION, strTemp ) == 0 )
      {
         fread( &stAdat, sizeof(typ_szoliadat), 1, file );
      }
      else
      {
         LOG1( "#FV#CS_Solarium::LoadDataFromFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verzi�sz�m: [" ) +
                     AnsiString( SOLARIUM_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "] [" ) +
                     AnsiString( DataFileName ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
      }
      fclose( file );

      DeCode( stAdat.strNev, sizeof(stAdat.strNev) );
   }
   else
   {
      EnCode( stAdat.strNev, sizeof(stAdat.strNev) );

      file = fopen( DataFileName.c_str(), "wb" );
      fwrite( SOLARIUM_FILE_VERSION, 10, 1, file );
      fwrite( &stAdat, sizeof(typ_szoliadat), 1, file );
      fclose( file );

      DeCode( stAdat.strNev, sizeof(stAdat.strNev) );
   }
}
//---------------------------------------------------------------------------
bool CS_Solarium::SaveDataToFile( const char *strFile )
{
   FILE  *file = NULL;
   bool           bRet = true;

   EnCode( stAdat.strNev, sizeof(stAdat.strNev) );

   file = fopen( strFile, "wb" );
   if( file != NULL )
   {
      fwrite( SOLARIUM_FILE_VERSION, 10, 1, file );
      fwrite( &stAdat, sizeof(typ_szoliadat), 1, file );
      fclose( file );
   }
   else
   {
      // nem siker�lt l�trehozni a file-t
      strLogMsg = AnsiString( "HIBA: Nem siker�lt l�trehozni: " ) + strFile;
      LOG1( strLogMsg );
      bRet = false;
   }

   DeCode( stAdat.strNev, sizeof(stAdat.strNev) );

   return bRet;
}
//---------------------------------------------------------------------------
bool CS_Solarium::CheckDataToFile( const char *strFile )
{
   FILE          *file = NULL;
   unsigned int   nSize,i;
   bool           bRet = true;

   file = fopen( strFile, "rb" );
   if( file != NULL )
   {
      // file megnyit�sa sikeres
      char strTemp[10];
      memset( strTemp, 0, sizeof(strTemp) );
      // verzi�sz�m kiolvas�sa
      fread( strTemp, 10, 1, file );
      if( strcmp( SOLARIUM_FILE_VERSION, strTemp ) == 0 )
      {
         // verzi�sz�m egyezik
         //
         typ_szoliadat   stTemp;

         // rekord beolvas�sa
         fread( &stTemp, sizeof(typ_szoliadat), 1, file );
         // sz�veg dek�dol�sa
         DeCode( stTemp.strNev, sizeof(stTemp.strNev) );
         // rekord ellen�rz�se
         if( memcmp( &stAdat, &stTemp, sizeof(typ_szoliadat) ) != 0 )
         {
            // rekord nem egyezik
            //
            strLogMsg = AnsiString( "HIBA: Nem egyezik a rekord #FV#CS_Solarium::CheckDataToFile [" ) +
                        AnsiString( nSzolariumID ) +
                        AnsiString( "]" ); 
            LOG1( strLogMsg );
            bRet = false;
         }
      }
      else
      {
         // verzi�sz�m nem egyezik
         LOG1( "#FV#CS_Solarium::CheckDataToFile" );
         strLogMsg = AnsiString( "HIBA: Nem egyezik a verzi�sz�m: [" ) +
                     AnsiString( SOLARIUM_FILE_VERSION ) +
                     AnsiString( "] [" ) +
                     AnsiString( strTemp ) +
                     AnsiString( "]" );
         LOG1( strLogMsg );
         bRet = false;
      }
      fclose( file );
   }
   else
   {
      // nem lehetett megnyitni olvas�sra a file-t
      strLogMsg = AnsiString( "HIBA: Nem siker�lt ellen�rizni a ment�st: " ) + strFile;
      LOG1( strLogMsg );
      bRet = false;
   }

   return bRet;
}
//---------------------------------------------------------------------------
// Param�terk�nt �tadott barnul�si id� kikeres�se a szol�rium
// Id�/Forint t�bl�zat�b�l �s a Forint �rt�k visszaad�sa
// Visszat�r�si �rt�k:
//    true  -> a barnul�si id�t megtal�lta az adott t�bl�zatban
//    false -> a barnul�si id�t nem tal�lta meg az adott t�bl�zatban
//---------------------------------------------------------------------------
bool CS_Solarium::CheckBarnulasIdo( int nBarnulas, int *nForint )
{
   bool bRet = false;

   *nForint = 0;

   if( nBarnulas > 0 )
   {
      // Barnul�si id� val�s �rt�ket tartalmaz
      // Aktu�lis id�pont �s a kedvezm�nyes id�szak �sszehasonl�t�sa
      if( CheckKedvezmenyIdo() )
      {
         // Az aktu�lis id�pont beleesik a kedvezm�nyes id�szakba
         // Barnul�si id� kikeres�se a kedvezm�nyes t�bl�zatb�l
         for( int i=0; i<40; i++ )
         {
            if( stAdat.stIdoForintKedv[i].nPerc == nBarnulas )
            {
               // Barnul�si id� szerepel a t�bl�zatban
               *nForint = stAdat.stIdoForintKedv[i].nForint;
               bRet = true;
               break;
            }
         }
      }
      else
      {
         // Az aktu�lis id�pont nem esik bele a kedvezm�nyes id�szakba
         // Barnul�si id� kikeres�se a norm�l t�bl�zatb�l
         for( int i=0; i<40; i++ )
         {
            if( stAdat.stIdoForint[i].nPerc == nBarnulas )
            {
               // Barnul�si id� szerepel a t�bl�zatban
               *nForint = stAdat.stIdoForint[i].nForint;
               bRet = true;
               break;
            }
         }
      }
   }
   return bRet;
}
//---------------------------------------------------------------------------
// Aktu�lis id�pont �s a kedvezm�nyes id�szak �sszehasonl�t�sa
//---------------------------------------------------------------------------
bool CS_Solarium::CheckKedvezmenyIdo()
{
   if( stAdat.nKedvezmenyIdoStart == 0 &&
       stAdat.nKedvezmenyIdoStop == 0 )
   {
      // nincs beallitva kedvezmenyes idoszak
      return false;
   }

   unsigned short nHour, nMin, nSec, nMSec;
   bool bRet = false;

   Now().DecodeTime( &nHour, &nMin, &nSec, &nMSec );

   if( stAdat.nKedvezmenyIdoStart <= stAdat.nKedvezmenyIdoStop )
   {
        // nincs napvaltas
      if( stAdat.nKedvezmenyIdoStart <= (nHour*60+nMin) &&
          (nHour*60+nMin) <= stAdat.nKedvezmenyIdoStop )
      {
         bRet = true;
      }
   }
   else if( stAdat.nKedvezmenyIdoStart > stAdat.nKedvezmenyIdoStop )
   {
        // napvaltas
        if( stAdat.nKedvezmenyIdoStart <= (nHour*60+nMin) ||
            (nHour*60+nMin) <= stAdat.nKedvezmenyIdoStop )
      {
         bRet = true;
      }
   }

   return bRet;
}
//---------------------------------------------------------------------------
// Szol�rium be�ll�t�sa kezd� adatokkal a m�k�d�s megkezd�s�hez b�rlet haszn�latkor
//---------------------------------------------------------------------------
void CS_Solarium::StartPrepare( typ_berlet stBerlet, int nBarnulas, int nForint )
{
   typ_berlethasznalat  stTemp;
   unsigned short       nYear, nMonth, nDay;
   unsigned short       nHour, nMin, nSec, nMsec;

   Now().DecodeDate( &nYear, &nMonth, &nDay );
   Now().DecodeTime( &nHour, &nMin, &nSec, &nMsec );

   memset( &stTemp, 0, sizeof(typ_berlethasznalat) );

   strcpy( stTemp.strVonalkod, stBerlet.strVonalkod );
   stTemp.nEv     = nYear;
   stTemp.nHo     = nMonth;
   stTemp.nNap    = nDay;
   stTemp.nOra    = nHour;
   stTemp.nPerc   = nMin;
   stTemp.nEgyseg = nForint;

   // B�rlet felv�tele a szol�rium list�j�ba
   BerletHasznal.push_back( stTemp );
   // A b�rlethez tartoz� szol�rium haszn�latot t�rol� v�ltoz�k b�v�t�se
   nBerletEgyseg += nForint;
   nIdoBerlet += nBarnulas;

   // Feliratok megjelen�t�se; szol�rium haszn�latot t�rol� v�ltoz�k b�v�t�se
   StartPrepare( nBarnulas, 0 );
}
//---------------------------------------------------------------------------
// Szol�rium be�ll�t�sa kezd� adatokkal a m�k�d�s megkezd�s�hez
//---------------------------------------------------------------------------
void CS_Solarium::StartPrepare( int nBarnulas, int nForint )
{
   char  strTemp[100];

   // A szol�rium haszn�latot t�rol� v�ltoz�k b�v�t�se
   nIdoBarnulas += nBarnulas;
   nForintBarnulas += nForint;

   // Visszasz�ml�l�si id� kiirat�sa
   memset( strTemp, 0, sizeof(strTemp) );
   sprintf( strTemp, "%02d : %02d", nIdoBarnulas/60, nIdoBarnulas%60 );
   Label_Visszaszamlalas->Caption = AnsiString( strTemp );
   Label_Visszaszamlalas->Visible = true;

   // Ha p�nzzel lett ind�tva a szol�rium ...
   if( nForintBarnulas > 0 )
   {
      // fizet�st jelz� felirat megjelen�t�se
      bFizetniKell = true;
      sprintf( strTemp, "%d %s", nForintBarnulas, FormLanguage->LangStr(STR_CURRENCY).c_str() );
      Label_Penz->Caption = AnsiString( strTemp );
      Label_Penz->Visible = true;
   }
   strLogMsg = AnsiString( "[" ) +
               AnsiString( stAdat.strNev ) +
               AnsiString( "] [" ) +
               AnsiString( nIdoBarnulas/60 ) +
               AnsiString( "] perc [" ) +
               AnsiString( nForintBarnulas ) +
               AnsiString( "] forint" );
   LOG2( strLogMsg );
}
//---------------------------------------------------------------------------
// Szol�rium alap �llapotban a m�g el nem ind�tott b�rlet haszn�lat
// illetve fizetett haszn�lat visszavon�sa, szol�rium alap �llapotba hoz�sa
//---------------------------------------------------------------------------
void CS_Solarium::StartReset( typ_user stUser )
{
   // Ha a szol�rium alap �llapotban van �S
   // a steril, illetve a fizet�s felirat nincs fenn
   // VAGY
   // a szol�rium vetk�z�s �llapotban van
   if( (cSolariumStatus == STATUS_ALAP && bStatusSteril && !bFizetniKell) ||
       cSolariumStatus == STATUS_VETKOZES )
   {
      strLogMsg = AnsiString( "Szol�rium haszn�lat megszak�t�sa [" ) +
                  AnsiString( stAdat.strNev ) +
                  AnsiString( "] [" ) +
                  AnsiString( stUser.strLoginNev ) +
                  AnsiString( "]" );
      LOG2( strLogMsg );
      // Ha a szol�rium haszn�latra b�rlet is r� lett vezetve, akkor a b�rlet
      // felhaszn�l�s t�rl�se a b�rletb�l, felhaszn�lt egys�gek visszavezet�se
      for( int i=0; i<(int)BerletHasznal.size(); )
      {
         strLogMsg = AnsiString( "B�rlethaszn�lat visszavon�sa [" ) +
                     AnsiString( BerletHasznal[i].strVonalkod ) +
                     AnsiString( "] [" ) +
                     AnsiString( BerletHasznal[i].nEgyseg ) +
                     AnsiString( "] egys�g" );
         LOG2( strLogMsg );
         //pBerlet->SetBerletEgyseg( BerletHasznal[i].strVonalkod, BerletHasznal[i].nEgyseg );
         pBerlet->IncreaseBerletEgyseg( BerletHasznal[i].strVonalkod, BerletHasznal[i].nEgyseg );
         //pBerlet->DeleteBerletHasznalat( BerletHasznal[i] );
         BerletHasznal.erase( BerletHasznal.begin() );
      }

      // Ha m�r el volt k�nyvelve k�szp�nzfizet�s a p�nzt�rk�nyvbe,
      // akkor annak a negat�v �rt�k�t be kell �rni a p�nzt�rk�nyvbe
      if( nForintBarnulas > 0 && !bFizetniKell )
      {
         strLogMsg = AnsiString( "K�szp�nz visszavon�sa [" ) +
                     AnsiString( nForintBarnulas ) +
                     AnsiString( "] forint" );
         LOG2( strLogMsg );
         AnsiString  strMsg = AnsiString( stAdat.strNev ) + " - " + FormLanguage->LangStr(STR_INF_SOLARIUM_STOPPED);
         pPenztar->PenztarKiadas( stUser, nForintBarnulas, strMsg.c_str() );
      }

      // St�tusz v�ltoz� �t�ll�t�sa ALAP �llapotba
      cSolariumStatus = STATUS_ALAP;

      // A szol�rium haszn�latot t�rol� v�ltoz�k kinull�z�sa
      nIdoBarnulas      = 0;
      nIdoMegszakitott  = 0;
      nForintBarnulas   = 0;
      nBerletEgyseg     = 0;
      nIdoBerlet        = 0;
      bFizetniKell      = false;

      // Szol�rium m�k�d�si feliratok t�rl�se, elt�ntet�se
      Label_Status->Caption = "";
      Label_Status->Visible = false;
      Label_Visszaszamlalas->Caption = "";
      Label_Visszaszamlalas->Visible = false;
      Label_Ido->Caption = "";
      Label_Ido->Visible = false;
      Label_Penz->Caption = "";
      Label_Penz->Visible = false;

      // Szol�rium st�tusz friss�t�se
      StatuszUpdate();
   }
}
//---------------------------------------------------------------------------
// Megadott egys�ghez kisz�molja a barnul�si id�t a
// forint/id� t�bl�zat 1. elem�b�l
//---------------------------------------------------------------------------
bool CS_Solarium::GetBarnulasIdo( int nEgyseg, int *nBarnulas )
{
   bool bRet = false;

   // Megn�zi, hogy a kedvezm�nyes id�szakban vagyunk-e
   if( CheckKedvezmenyIdo() )
   {
      // A kedvezm�nyes id�szak �rv�nyes
      if( stAdat.stIdoForintKedv[0].nPerc != 0 )
      {
         // Barnul�si id� kisz�mol�sa a kedvezm�nyes t�bl�b�l
         *nBarnulas = stAdat.stIdoForintKedv[0].nPerc * nEgyseg;
         bRet = true;
      }
   }
   else
   {
      // Norm�l id�szak �rv�nyes
      if( stAdat.stIdoForint[0].nPerc != 0 )
      {
         // Barnul�si id� kisz�mol�sa a norm�l t�bl�b�l
         *nBarnulas = stAdat.stIdoForint[0].nPerc * nEgyseg;
         bRet = true;
      }
   }

   return bRet;
}
//---------------------------------------------------------------------------
// Visszat�r a szol�rium be�ll�tott max. barnul�si idej�vel
//---------------------------------------------------------------------------
int CS_Solarium::GetMaxBarnulas()
{
   return stAdat.nMaxBarnulas;
}
//---------------------------------------------------------------------------
bool CS_Solarium::CsovekKikapcsolva()
{
   return bCsovekKikapcsolva;
}
//---------------------------------------------------------------------------
int CS_Solarium::GetForintBarnulas()
{
   return nForintBarnulas;
}
//---------------------------------------------------------------------------

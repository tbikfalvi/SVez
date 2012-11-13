//---------------------------------------------------------------------------

#include <vcl.h>
#include <Printers.hpp>

#pragma hdrstop

#include "Lista.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormLista *FormLista;
//---------------------------------------------------------------------------
__fastcall TFormLista::TFormLista(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::FormActivate(TObject *Sender)
{
   RichEditLista->SetFocus();
   TabControlLista->Tabs->Clear();
   switch( nListaType )
   {
      case LISTA_BERLETOSSZ:
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_CARDS) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_CARDS_OBSOLETE) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_CARDS_USE) );
         TabControlLista->TabIndex = 0;
         break;

      case LISTA_BERLET:
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_CARDS) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_CARDS_OBSOLETE) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_CARDS_USE) );
         TabControlLista->TabIndex = 1;
         break;

      case LISTA_BERLETHASZNALAT:
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_CARDS) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_CARDS_OBSOLETE) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_CARDS_USE) );
         TabControlLista->TabIndex = 2;
         break;

      case LISTA_TERMEK:
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_PRODUCTS) );
         TabControlLista->TabIndex = 0;
         break;

      case LISTA_FOKONYV:
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_MAIN) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_DAY) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_SHIFT) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_CASH) );
         TabControlLista->TabIndex = 0;
         break;

      case LISTA_NAPIKONYV:
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_MAIN) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_DAY) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_SHIFT) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_CASH) );
         TabControlLista->TabIndex = 1;
         break;

      case LISTA_MUSZAK:
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_MAIN) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_DAY) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_SHIFT) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_CASH) );
         TabControlLista->TabIndex = 2;
         break;

      case LISTA_PENZTAR:
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_MAIN) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_DAY) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_SHIFT) );
         TabControlLista->Tabs->Add( FormLanguage->LangStr(STR_CAPTION_BOOK_CASH) );
         TabControlLista->TabIndex = 3;
         break;
   }
   SetControls();
   FillLista();
   nTabPrevious = TabControlLista->TabIndex;
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::TabControlListaChange(TObject *Sender)
{
   switch( nListaType )
   {
      case LISTA_BERLETOSSZ:
      case LISTA_BERLET:
      case LISTA_BERLETHASZNALAT:
      {
         switch( TabControlLista->TabIndex )
         {
            case 0:
               nListaType = LISTA_BERLETOSSZ;
               break;
            case 1:
               nListaType = LISTA_BERLET;
               break;
            case 2:
               nListaType = LISTA_BERLETHASZNALAT;
               break;
         }
         break;
      }
      case LISTA_TERMEK:
      {
         switch( TabControlLista->TabIndex )
         {
            case 0:
               nListaType = LISTA_TERMEK;
               break;
         }
         break;
      }
      case LISTA_FOKONYV:
      case LISTA_NAPIKONYV:
      case LISTA_MUSZAK:
      case LISTA_PENZTAR:
      {
         switch( TabControlLista->TabIndex )
         {
            case 0:
               if( pUser->GetUserLevel(pMainSettings->GetCurrentUser()) < ACCESS_ADMIN )
               {
                  Application->MessageBox( FormLanguage->LangStr(STR_MSG_ACCESS_DENIED).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONSTOP );
                  TabControlLista->TabIndex = nTabPrevious;
               }
               else
               {
                  nListaType = LISTA_FOKONYV;
               }
               break;
            case 1:
               nListaType = LISTA_NAPIKONYV;
               break;
            case 2:
               nListaType = LISTA_MUSZAK;
               break;
            case 3:
               nListaType = LISTA_PENZTAR;
               break;
         }
         break;
      }
   }
   nTabPrevious = TabControlLista->TabIndex;
   SetControls();
   FillLista();
}
//---------------------------------------------------------------------------
void TFormLista::SetControls()
{
   switch( nListaType )
   {
      case LISTA_BERLETOSSZ:
         GB_FilterMuszak->Enabled = false;
         GB_FilterMuszak->Visible = false;
         GB_FilterDatum->Enabled = false;
         GB_FilterDatum->Visible = false;
         GB_FilterBerlet->Enabled = false;
         GB_FilterBerlet->Visible = false;
         Caption = FormLanguage->LangStr(STR_CAPTION_ALLSOLDCARD);
         break;

      case LISTA_BERLET:
         GB_FilterMuszak->Enabled = false;
         GB_FilterMuszak->Visible = false;
         GB_FilterDatum->Enabled = true;
         GB_FilterDatum->Visible = true;
         GB_FilterBerlet->Enabled = false;
         GB_FilterBerlet->Visible = false;
         BtnStartPrevWeek->Enabled = true;
         BtnStartPrevDay->Enabled = true;
         DTPickerStart->Enabled = true;
         BtnStartNextDay->Enabled = true;
         BtnStartNextWeek->Enabled = true;
         BtnStopPrevWeek->Enabled = true;
         BtnStopPrevDay->Enabled = true;
         DTPickerStop->Enabled = true;
         BtnStopNextDay->Enabled = true;
         BtnStopNextWeek->Enabled = true;
         Caption = FormLanguage->LangStr(STR_CAPTION_DATESOLDCARD);
         DTPickerStart->Date = Now();
         DTPickerStop->Date = DTPickerStart->Date+30;
         break;

      case LISTA_BERLETHASZNALAT:
         GB_FilterMuszak->Enabled = false;
         GB_FilterMuszak->Visible = false;
         GB_FilterDatum->Enabled = false;
         GB_FilterDatum->Visible = false;
         GB_FilterBerlet->Enabled = true;
         GB_FilterBerlet->Visible = true;
         Caption = FormLanguage->LangStr(STR_CAPTION_USEDSOLDCARD);
         break;

      case LISTA_TERMEK:
         GB_FilterMuszak->Enabled = false;
         GB_FilterMuszak->Visible = false;
         GB_FilterDatum->Enabled = false;
         GB_FilterDatum->Visible = false;
         GB_FilterBerlet->Enabled = false;
         GB_FilterBerlet->Visible = false;
         Caption = FormLanguage->LangStr(STR_CAPTION_PRODUCTINSTOCK);
         break;

      case LISTA_FOKONYV:
         GB_FilterMuszak->Enabled = false;
         GB_FilterMuszak->Visible = false;
         GB_FilterDatum->Enabled = true;
         GB_FilterDatum->Visible = true;
         GB_FilterBerlet->Enabled = false;
         GB_FilterBerlet->Visible = false;
         BtnStartPrevWeek->Enabled = true;
         BtnStartPrevDay->Enabled = true;
         DTPickerStart->Enabled = true;
         BtnStartNextDay->Enabled = true;
         BtnStartNextWeek->Enabled = true;
         BtnStopPrevWeek->Enabled = true;
         BtnStopPrevDay->Enabled = true;
         DTPickerStop->Enabled = true;
         BtnStopNextDay->Enabled = true;
         BtnStopNextWeek->Enabled = true;
         Caption = FormLanguage->LangStr(STR_CAPTION_DATEMAINBOOK);
         DTPickerStop->Date = Now();
         DTPickerStart->Date = DTPickerStop->Date-30;
         break;

      case LISTA_NAPIKONYV:
         GB_FilterMuszak->Enabled = false;
         GB_FilterMuszak->Visible = false;
         GB_FilterDatum->Enabled = true;
         GB_FilterDatum->Visible = true;
         GB_FilterBerlet->Enabled = false;
         GB_FilterBerlet->Visible = false;
         BtnStopPrevWeek->Enabled = false;
         BtnStopPrevDay->Enabled = false;
         DTPickerStop->Enabled = false;
         BtnStopNextDay->Enabled = false;
         BtnStopNextWeek->Enabled = false;
         Caption = FormLanguage->LangStr(STR_CAPTION_DATEDAYBOOK);
         DTPickerStart->Date = Now();
         DTPickerStop->Date = Now();
         if( pUser->GetUserLevel(pMainSettings->GetCurrentUser()) < ACCESS_ADMIN )
         {
            BtnStartPrevWeek->Enabled = false;
            BtnStartPrevDay->Enabled = false;
            DTPickerStart->Enabled = false;
            BtnStartNextDay->Enabled = false;
            BtnStartNextWeek->Enabled = false;
         }
         else
         {
            BtnStartPrevWeek->Enabled = true;
            BtnStartPrevDay->Enabled = true;
            DTPickerStart->Enabled = true;
            BtnStartNextDay->Enabled = true;
            BtnStartNextWeek->Enabled = true;
         }
         break;

      case LISTA_MUSZAK:
         GB_FilterMuszak->Enabled = true;
         GB_FilterMuszak->Visible = true;
         GB_FilterDatum->Enabled = false;
         GB_FilterDatum->Visible = false;
         GB_FilterBerlet->Enabled = false;
         GB_FilterBerlet->Visible = false;
         Caption = FormLanguage->LangStr(STR_CAPTION_IDSHIFTBOOK);
         if( pUser->GetUserLevel(pMainSettings->GetCurrentUser()) < ACCESS_ADMIN )
         {
            GB_FilterMuszak->Enabled = false;
         }
         break;

      case LISTA_PENZTAR:
         GB_FilterMuszak->Enabled = false;
         GB_FilterMuszak->Visible = false;
         GB_FilterDatum->Enabled = true;
         GB_FilterDatum->Visible = true;
         GB_FilterBerlet->Enabled = false;
         GB_FilterBerlet->Visible = false;
         BtnStartPrevWeek->Enabled = true;
         BtnStartPrevDay->Enabled = true;
         DTPickerStart->Enabled = true;
         BtnStartNextDay->Enabled = true;
         BtnStartNextWeek->Enabled = true;
         BtnStopPrevWeek->Enabled = true;
         BtnStopPrevDay->Enabled = true;
         DTPickerStop->Enabled = true;
         BtnStopNextDay->Enabled = true;
         BtnStopNextWeek->Enabled = true;
         Caption = FormLanguage->LangStr(STR_CAPTION_CASHINOUT);
         if( pUser->GetUserLevel(pMainSettings->GetCurrentUser()) < ACCESS_ADMIN )
         {
            BtnStartPrevWeek->Enabled = false;
            BtnStartPrevDay->Enabled = false;
            DTPickerStart->Enabled = false;
            BtnStartNextDay->Enabled = false;
            BtnStartNextWeek->Enabled = false;
            BtnStopPrevWeek->Enabled = false;
            BtnStopPrevDay->Enabled = false;
            DTPickerStop->Enabled = false;
            BtnStopNextDay->Enabled = false;
            BtnStopNextWeek->Enabled = false;
            DTPickerStop->Date = Now();
            DTPickerStart->Date = Now();
         }
         else
         {
            DTPickerStop->Date = Now();
            DTPickerStart->Date = Now();//DTPickerStop->Date-30;
         }
         break;
   }
}
//---------------------------------------------------------------------------
void TFormLista::FillLista()
{
   RichEditLista->Clear();

   switch( nListaType )
   {
      case LISTA_BERLETOSSZ:
      case LISTA_BERLET:
         FillBerletLista();
         break;

      case LISTA_BERLETHASZNALAT:
         FillBerletHasznalatLista();
         break;

      case LISTA_TERMEK:
         FillTermekLista();
         break;

      case LISTA_FOKONYV:
         FillSzoliLista();
         FillKonyvLista();
         break;

      case LISTA_NAPIKONYV:
         FillSzoliLista();
         FillKonyvLista();
         break;

      case LISTA_MUSZAK:
         FillSzoliLista();
         FillKonyvLista();
         break;

      case LISTA_PENZTAR:
         FillPenztarLista();
         break;
   }
}
//---------------------------------------------------------------------------
void TFormLista::FillBerletLista()
{
   int   nLength[] = { 15, 30, 30, 13, 13 };
   int   nL;
   int   nTemp;

   strLine = "";

   strLine += FormLanguage->LangStr(STR_BARCODE);
   for( nL=0; nL<(int)(nLength[0]-strlen(FormLanguage->LangStr(STR_BARCODE).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_CARD_TYPE);
   for( nL=0; nL<(int)(nLength[1]-strlen(FormLanguage->LangStr(STR_CARD_TYPE).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_COMMENT);
   for( nL=0; nL<(int)(nLength[2]-strlen(FormLanguage->LangStr(STR_COMMENT).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_VALID);
   for( nL=0; nL<(int)(nLength[3]-strlen(FormLanguage->LangStr(STR_VALID).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_CURR_UNIT);
   for( nL=0; nL<(int)(nLength[4]-strlen(FormLanguage->LangStr(STR_CURR_UNIT).c_str())); nL++ ) strLine += " ";

   RichEditLista->Lines->Add( strLine );

   nTemp = strLine.Length();
   strLine = "";
   for( nL=0; nL<nTemp; nL++ ) strLine += "—";

   RichEditLista->Lines->Add( strLine );

   for( double i=0; i<pBerletek->GetBerletCount(); i++ )
   {
      typ_berlet  stTemp = pBerletek->GetBerletItem( i );
      typ_berlettipus   stTTemp = pBerletek->GetBerletTipusID( stTemp.nBerletTipus );

      if( GB_FilterDatum->Enabled )
      {
         TDate DBerlet = TDate( stTemp.nErvEv, stTemp.nErvHo, stTemp.nErvNap );
         if( DBerlet < DTPickerStart->Date || DTPickerStop->Date < DBerlet )
            continue;
      }

      char strDate[11];
      memset( strDate, 0, sizeof(strDate) );
      sprintf( strDate, "%d/%02d/%02d", stTemp.nErvEv, stTemp.nErvHo, stTemp.nErvNap );

      strLine = "";
      strLine += AnsiString( stTemp.strVonalkod );
      for( nL=0; nL<(int)(nLength[0]-strlen(stTemp.strVonalkod)); nL++ ) strLine += " ";
      strLine += AnsiString( stTTemp.strNev );
      for( nL=0; nL<(int)(nLength[1]-strlen(stTTemp.strNev)); nL++ ) strLine += " ";
      strLine += AnsiString( stTemp.strMegjegyzes );
      for( nL=0; nL<(int)(nLength[2]-strlen(stTemp.strMegjegyzes)); nL++ ) strLine += " ";
      strLine += AnsiString( strDate );
      for( nL=0; nL<(int)(nLength[3]-strlen(strDate)); nL++ ) strLine += " ";
      strLine += AnsiString( stTemp.nEgyseg );
      for( nL=0; nL<(int)(nLength[4]-AnsiString(stTemp.nEgyseg).Length()); nL++ ) strLine += " ";

      RichEditLista->Lines->Add( strLine );
   }
}
//---------------------------------------------------------------------------
void TFormLista::FillBerletHasznalatLista()
{
   int   nLength[] = { 15, 26, 30 };
   int   nL;
   int   nTemp;

   strLine = "";

   strLine += FormLanguage->LangStr(STR_BARCODE);
   for( nL=0; nL<(int)(nLength[0]-strlen(FormLanguage->LangStr(STR_BARCODE).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_DATE_TIME);
   for( nL=0; nL<(int)(nLength[1]-strlen(FormLanguage->LangStr(STR_DATE_TIME).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_USED_UNIT);
   for( nL=0; nL<(int)(nLength[2]-strlen(FormLanguage->LangStr(STR_USED_UNIT).c_str())); nL++ ) strLine += " ";

   RichEditLista->Lines->Add( strLine );

   nTemp = strLine.Length();
   strLine = "";
   for( nL=0; nL<nTemp; nL++ ) strLine += "—";

   RichEditLista->Lines->Add( strLine );

   for( double i=0; i<pBerletek->GetBerletHasznalatCount(); i++ )
   {
      typ_berlethasznalat  stTemp = pBerletek->GetBerletHasznalatItem( i );

      if( strstr(stTemp.strVonalkod,EditBerlet->Text.c_str()) == 0 )
         continue;

      char strDate[20];
      memset( strDate, 0, sizeof(strDate) );
      sprintf( strDate, "%d/%02d/%02d %02d:%02d", stTemp.nEv,
                                                  stTemp.nHo,
                                                  stTemp.nNap,
                                                  stTemp.nOra,
                                                  stTemp.nPerc );

      strLine = "";
      strLine += AnsiString( stTemp.strVonalkod );
      for( nL=0; nL<(int)(nLength[0]-strlen(stTemp.strVonalkod)); nL++ ) strLine += " ";
      strLine += AnsiString( strDate );
      for( nL=0; nL<(int)(nLength[1]-strlen(strDate)); nL++ ) strLine += " ";
      strLine += AnsiString( stTemp.nEgyseg );
      for( nL=0; nL<(int)(nLength[2]-AnsiString(stTemp.nEgyseg).Length()); nL++ ) strLine += " ";

      RichEditLista->Lines->Add( strLine );
   }
}
//---------------------------------------------------------------------------
void TFormLista::FillTermekLista()
{
   int   nLength[] = { 15, 30, 13, 13 };
   int   nL;
   int   nTemp;

   strLine = "";

   strLine += FormLanguage->LangStr(STR_BARCODE);
   for( nL=0; nL<(int)(nLength[0]-strlen(FormLanguage->LangStr(STR_BARCODE).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_DESIGNATION);
   for( nL=0; nL<(int)(nLength[1]-strlen(FormLanguage->LangStr(STR_DESIGNATION).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_UNITPRICE);
   for( nL=0; nL<(int)(nLength[2]-strlen(FormLanguage->LangStr(STR_UNITPRICE).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_STOCK);
   for( nL=0; nL<(int)(nLength[3]-strlen(FormLanguage->LangStr(STR_STOCK).c_str())); nL++ ) strLine += " ";

   RichEditLista->Lines->Add( strLine );

   nTemp = strLine.Length();
   strLine = "";
   for( nL=0; nL<nTemp; nL++ ) strLine += "—";

   RichEditLista->Lines->Add( strLine );

   for( double i=0; i<pTermek->GetTermekCount(); i++ )
   {
      typ_termek  stTemp = pTermek->GetTermekItem( i );

      strLine = "";
      strLine += AnsiString( stTemp.strVonalkod );
      for( nL=0; nL<(int)(nLength[0]-strlen(stTemp.strVonalkod)); nL++ ) strLine += " ";
      strLine += AnsiString( stTemp.strNev );
      for( nL=0; nL<(int)(nLength[1]-strlen(stTemp.strNev)); nL++ ) strLine += " ";
      strLine += convertToCurrencyString( stTemp.nAr );
      for( nL=0; nL<(int)(nLength[2]-convertToCurrencyString(stTemp.nAr).Length()); nL++ ) strLine += " ";
      strLine += AnsiString( stTemp.nDarab );
      for( nL=0; nL<(int)(nLength[3]-AnsiString(stTemp.nDarab).Length()); nL++ ) strLine += " ";

      RichEditLista->Lines->Add( strLine );
   }
}
//---------------------------------------------------------------------------
void TFormLista::FillPenztarLista()
{
   int   nLength[] = { 20, 50, 10, 10, 49 };
   int   nL;
   int   nTemp;

   strLine = "";

   strLine += FormLanguage->LangStr(STR_DATE);
   for( nL=0; nL<(int)(nLength[0]-strlen(FormLanguage->LangStr(STR_DATE).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_USER);
   for( nL=0; nL<(int)(nLength[1]-strlen(FormLanguage->LangStr(STR_USER).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_EVENT);
   for( nL=0; nL<(int)(nLength[2]-strlen(FormLanguage->LangStr(STR_EVENT).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_SUM);
   for( nL=0; nL<(int)(nLength[3]-strlen(FormLanguage->LangStr(STR_SUM).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_COMMENT);
   for( nL=0; nL<(int)(nLength[4]-strlen(FormLanguage->LangStr(STR_COMMENT).c_str())); nL++ ) strLine += " ";

   RichEditLista->Lines->Add( strLine );

   nTemp = strLine.Length();
   strLine = "";
   for( nL=0; nL<nTemp-2; nL++ ) strLine += "—";

   RichEditLista->Lines->Add( strLine );

   for( double i=0; i<pPenztar->GetPenztarActionCount(); i++ )
   {
      typ_penztar_action   stTemp = pPenztar->GetPenztarAction( i );
      typ_user             stUser = pUser->GetUserLogin( stTemp.strLoginNev );
      char                 strTemp[50];

      TDate DDate = TDate( stTemp.dDateTime );
      if( DDate < DTPickerStart->Date || DTPickerStop->Date < DDate )
         continue;

      strLine = "";
      strLine += FormatDateTime("yyyy/mm/dd hh:nn:ss",stTemp.dDateTime );
      for( nL=0; nL<(int)(nLength[0]-19); nL++ ) strLine += " ";
      strncpy( strTemp, stUser.strNevCsalad, 45 );
      if( strlen(stUser.strNevCsalad) > 45 )
         strcat( strTemp, "..." );
      strLine += AnsiString( strTemp );
      for( nL=0; nL<(int)(nLength[1]-strlen(strTemp)); nL++ ) strLine += " ";
      switch( stTemp.Action )
      {
         case ACTION_PENZTAR_NYITAS:
            strLine += FormLanguage->LangStr(STR_OPEN);
            for( nL=0; nL<(int)(nLength[2]-6); nL++ ) strLine += " ";
            break;
         case ACTION_PENZTAR_BEVET:
            strLine += FormLanguage->LangStr(STR_INCOME);
            for( nL=0; nL<(int)(nLength[2]-7); nL++ ) strLine += " ";
            break;
         case ACTION_PENZTAR_KIADAS:
            strLine += FormLanguage->LangStr(STR_OUTCOME);
            for( nL=0; nL<(int)(nLength[2]-5); nL++ ) strLine += " ";
            break;
      }
      strLine += convertToCurrencyString( stTemp.nCash );
      for( nL=0; nL<(int)(nLength[3]-convertToCurrencyString(stTemp.nCash).Length()); nL++ ) strLine += " ";
      strncpy(strTemp, stTemp.strMegjegyzes, 45 );
      if( strlen(stTemp.strMegjegyzes) > 45 )
         strcat( strTemp, "..." );
      strLine += AnsiString( strTemp );
      for( nL=0; nL<(int)(nLength[4]-strlen(strTemp)); nL++ ) strLine += " ";

      RichEditLista->Lines->Add( strLine );
   }

   strLine = "";
   for( nL=0; nL<137; nL++ ) strLine += "—";
   RichEditLista->Lines->Add( strLine );

   strLine = "";
   for( nL=0; nL<(int)(nLength[0]); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_CASH_CURRENT_VALUE);
   for( nL=0; nL<(int)(nLength[1]-FormLanguage->LangStr(STR_CASH_CURRENT_VALUE).Length()); nL++ ) strLine += " ";
   for( nL=0; nL<(int)(nLength[2]); nL++ ) strLine += " ";
   strLine += convertToCurrencyString( pPenztar->GetPenztarEgyenleg() );
   for( nL=0; nL<(int)(nLength[3]-convertToCurrencyString(pPenztar->GetPenztarEgyenleg()).Length()); nL++ ) strLine += " ";

   RichEditLista->Lines->Add( strLine );
}
//---------------------------------------------------------------------------
void TFormLista::FillSzoliLista()
{
   int   nLength[] = { 30, 12, 12, 14, 12, 14, 14 };
   int   nL;

   strLine  = "                              ";
   strLine += FormLanguage->LangStr(STR_CAPTION_SOLUSED);
   RichEditLista->Lines->Add( strLine );

   strLine  = FormLanguage->LangStr(STR_CAPTION_SOL_SPACES);
   strLine += FormLanguage->LangStr(STR_CAPTION_LIST_SOLTIMES);
   RichEditLista->Lines->Add( strLine );

   strLine = "";
   for( nL=0; nL<137; nL++ ) strLine += "—";
   RichEditLista->Lines->Add( strLine );

   char                 strTemp[15];
   AnsiString           strSzolarium         = "";
   unsigned int         dSumUzemeltIdo          = 0;
   unsigned int         dSumUzemeltBerletIdo    = 0;
   unsigned int         dSumUzemeltBerletEgyseg = 0;
   unsigned int         dSumUzemeltFtIdo        = 0;
   unsigned int         dSumUzemeltMegszakitott = 0;
   unsigned int         dSumCsoUzemora          = 0;

   for( int nSCount=0; nSCount<nSzolariumCount; nSCount++ )
   {
      unsigned int         dUzemeltIdo          = 0;
      unsigned int         dUzemeltBerletIdo    = 0;
      unsigned int         dUzemeltBerletEgyseg = 0;
      unsigned int         dUzemeltFtIdo        = 0;
      unsigned int         dUzemeltMegszakitott = 0;
      unsigned int         dCsoUzemora          = 0;

      strSzolarium = "";
      for( double i=0; i<pKonyv->GetSzolariumKonyvCount(); i++ )
      {
         typ_konyv_szolarium  stTemp = pKonyv->GetSzolariumKonyv( i );

         if( stTemp.nSzolariumID != nSCount )
         {
            continue;
         }

         if( GB_FilterDatum->Enabled )
         {
            if( stTemp.dID < DTPickerStart->Date ||
                stTemp.dID > DTPickerStop->Date )
            {
               continue;
            }
         }
         if( GB_FilterMuszak->Enabled && EditMuszakID->Text.ToDouble() != stTemp.dMuszakID )
         {
            continue;
         }

         strSzolarium          = AnsiString( stTemp.strSzolarium );
         dUzemeltIdo          += stTemp.dUzemeltIdo;
         dUzemeltBerletIdo    += stTemp.dUzemeltBerletIdo;
         dUzemeltBerletEgyseg += stTemp.dUzemeltBerletEgyseg;
         dUzemeltFtIdo        += stTemp.dUzemeltFtIdo;
         dUzemeltMegszakitott += stTemp.dUzemeltMegszakitott;
         dCsoUzemora          += stTemp.dCsoUzemora;
      }

      dSumUzemeltIdo          += dUzemeltIdo;
      dSumUzemeltBerletIdo    += dUzemeltBerletIdo;
      dSumUzemeltBerletEgyseg += dUzemeltBerletEgyseg;
      dSumUzemeltFtIdo        += dUzemeltFtIdo;
      dSumUzemeltMegszakitott += dUzemeltMegszakitott;
      dSumCsoUzemora          += dCsoUzemora;

      strLine = "";

      if( strSzolarium.Length() > 0 )
      {
         strLine += strSzolarium;
         for( nL=0; nL<(int)(nLength[0]-strSzolarium.Length()); nL++ ) strLine += " ";

         memset( strTemp, 0, sizeof(strTemp) );
         sprintf( strTemp, "%03d:%02d:%02d", (dUzemeltIdo/3600),
                                             ((dUzemeltIdo%3600)/60),
                                             (dUzemeltIdo%60) );
         strLine += AnsiString( strTemp );
         for( nL=0; nL<(int)(nLength[1]-strlen(strTemp)); nL++ ) strLine += " ";

         memset( strTemp, 0, sizeof(strTemp) );
         sprintf( strTemp, "%03d:%02d:%02d", dUzemeltBerletIdo/3600, (dUzemeltBerletIdo%3600)/60, dUzemeltBerletIdo%60 );
         strLine += AnsiString( strTemp );
         for( nL=0; nL<(int)(nLength[2]-strlen(strTemp)); nL++ ) strLine += " ";

         strLine += AnsiString( dUzemeltBerletEgyseg );
         for( nL=0; nL<(int)(nLength[3]-AnsiString(dUzemeltBerletEgyseg).Length()); nL++ ) strLine += " ";

         memset( strTemp, 0, sizeof(strTemp) );
         sprintf( strTemp, "%03d:%02d:%02d", dUzemeltFtIdo/3600, (dUzemeltFtIdo%3600)/60, dUzemeltFtIdo%60 );
         strLine += AnsiString( strTemp );
         for( nL=0; nL<(int)(nLength[4]-strlen(strTemp)); nL++ ) strLine += " ";

         memset( strTemp, 0, sizeof(strTemp) );
         sprintf( strTemp, "%03d:%02d:%02d", dUzemeltMegszakitott/3600, (dUzemeltMegszakitott%3600)/60, dUzemeltMegszakitott%60 );
         strLine += AnsiString( strTemp );
         for( nL=0; nL<(int)(nLength[5]-strlen(strTemp)); nL++ ) strLine += " ";

         memset( strTemp, 0, sizeof(strTemp) );
         sprintf( strTemp, "%03d:%02d:%02d", dCsoUzemora/3600, (dCsoUzemora%3600)/60, dCsoUzemora%60 );
         strLine += AnsiString( strTemp );
         for( nL=0; nL<(int)(nLength[6]-strlen(strTemp)); nL++ ) strLine += " ";
      }
      RichEditLista->Lines->Add( strLine );
   }

   strLine = "";
   for( nL=0; nL<137; nL++ ) strLine += "—";
   RichEditLista->Lines->Add( strLine );

   strLine = "";
   strSzolarium = "";
   for( nL=0; nL<(int)(nLength[0]-strSzolarium.Length()); nL++ ) strLine += " ";

   memset( strTemp, 0, sizeof(strTemp) );
   sprintf( strTemp, "%03d:%02d:%02d", (dSumUzemeltIdo/3600),
                                       ((dSumUzemeltIdo%3600)/60),
                                       (dSumUzemeltIdo%60) );
   strLine += AnsiString( strTemp );
   for( nL=0; nL<(int)(nLength[1]-strlen(strTemp)); nL++ ) strLine += " ";

   memset( strTemp, 0, sizeof(strTemp) );
   sprintf( strTemp, "%03d:%02d:%02d", dSumUzemeltBerletIdo/3600, (dSumUzemeltBerletIdo%3600)/60, dSumUzemeltBerletIdo%60 );
   strLine += AnsiString( strTemp );
   for( nL=0; nL<(int)(nLength[2]-strlen(strTemp)); nL++ ) strLine += " ";

   strLine += AnsiString( dSumUzemeltBerletEgyseg );
   for( nL=0; nL<(int)(nLength[3]-AnsiString(dSumUzemeltBerletEgyseg).Length()); nL++ ) strLine += " ";

   memset( strTemp, 0, sizeof(strTemp) );
   sprintf( strTemp, "%03d:%02d:%02d", dSumUzemeltFtIdo/3600, (dSumUzemeltFtIdo%3600)/60, dSumUzemeltFtIdo%60 );
   strLine += AnsiString( strTemp );
   for( nL=0; nL<(int)(nLength[4]-strlen(strTemp)); nL++ ) strLine += " ";

   memset( strTemp, 0, sizeof(strTemp) );
   sprintf( strTemp, "%03d:%02d:%02d", dSumUzemeltMegszakitott/3600, (dSumUzemeltMegszakitott%3600)/60, dSumUzemeltMegszakitott%60 );
   strLine += AnsiString( strTemp );
   for( nL=0; nL<(int)(nLength[5]-strlen(strTemp)); nL++ ) strLine += " ";

   memset( strTemp, 0, sizeof(strTemp) );
   sprintf( strTemp, "%03d:%02d:%02d", dSumCsoUzemora/3600, (dSumCsoUzemora%3600)/60, dSumCsoUzemora%60 );
   strLine += AnsiString( strTemp );
   for( nL=0; nL<(int)(nLength[6]-strlen(strTemp)); nL++ ) strLine += " ";

   RichEditLista->Lines->Add( strLine );

   strLine = "";
   RichEditLista->Lines->Add( strLine );
}
//---------------------------------------------------------------------------
void TFormLista::FillKonyvLista()
{
   int   nLength[] = { 18, 18, 13, 13, 17, 17 };
   int   nL;

   strLine = "";
   for( nL=0; nL<137; nL++ ) strLine += "=";
   RichEditLista->Lines->Add( strLine );

   strLine = "";
   RichEditLista->Lines->Add( strLine );

   strLine = "";
   strLine += FormLanguage->LangStr(STR_START);
   for( nL=0; nL<(int)(nLength[0]-strlen(FormLanguage->LangStr(STR_START).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_STOP);
   for( nL=0; nL<(int)(nLength[1]-strlen(FormLanguage->LangStr(STR_STOP).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_CARD_CURRENCY);
   for( nL=0; nL<(int)(nLength[2]-strlen(FormLanguage->LangStr(STR_CARD_CURRENCY).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_PRODUCT_CURRENCY);
   for( nL=0; nL<(int)(nLength[3]-strlen(FormLanguage->LangStr(STR_PRODUCT_CURRENCY).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_SOLARIUM_CURRENCY);
   for( nL=0; nL<(int)(nLength[4]-strlen(FormLanguage->LangStr(STR_SOLARIUM_CURRENCY).c_str())); nL++ ) strLine += " ";
   strLine += FormLanguage->LangStr(STR_SUM_CURRENCY);
   for( nL=0; nL<(int)(nLength[5]-strlen(FormLanguage->LangStr(STR_SUM_CURRENCY).c_str())); nL++ ) strLine += " ";
   RichEditLista->Lines->Add( strLine );

   strLine = "";
   for( nL=0; nL<137; nL++ ) strLine += "—";
   RichEditLista->Lines->Add( strLine );

   typ_konyv_general stTemp;
   double            dStartDate     = Now();
   double            dStopDate      = 0;
   double            dBerletBevetel = 0;
   double            dTermekBevetel = 0;

   for( double i=0; i<pKonyv->GetGeneralKonyvCount(); i++ )
   {
      stTemp = pKonyv->GetGeneralKonyv( i );

      if( GB_FilterDatum->Enabled )
      {
         if( stTemp.dStartDateTime < DTPickerStart->Date ||
             stTemp.dStopDateTime > DTPickerStop->Date )
         {
            continue;
         }
      }
      if( GB_FilterMuszak->Enabled && EditMuszakID->Text.ToDouble() != stTemp.dMuszakID )
      {
         continue;
      }

      if( dStartDate > stTemp.dStartDateTime )
      {
         dStartDate = stTemp.dStartDateTime;
      }
      if( dStopDate < stTemp.dStopDateTime )
      {
         dStopDate = stTemp.dStopDateTime;
      }
      dBerletBevetel += stTemp.dBerletFtBevetel;
      dTermekBevetel += stTemp.dTermekFtBevetel;
   }

   unsigned int dSumUzemeltFt = 0;

   for( int nSCount=0; nSCount<nSzolariumCount; nSCount++ )
   {
      unsigned int dUzemeltFt = 0;

      for( double i=0; i<pKonyv->GetSzolariumKonyvCount(); i++ )
      {
         typ_konyv_szolarium  stTemp;
         stTemp = pKonyv->GetSzolariumKonyv( i );

         if( stTemp.nSzolariumID != nSCount )
         {
            continue;
         }
         if( stTemp.dID < DTPickerStart->Date ||
             stTemp.dID > DTPickerStop->Date )
         {
            continue;
         }
         dUzemeltFt += stTemp.dUzemeltFt;
      }
      dSumUzemeltFt += dUzemeltFt;
   }

   strLine = "";
   if( dStopDate > 0 )
   {
      strLine += FormatDateTime("yyyy/mm/dd hh:nn",dStartDate);
      for( nL=0; nL<(int)(nLength[0]-16); nL++ ) strLine += " ";
      strLine += FormatDateTime("yyyy/mm/dd hh:nn",dStopDate);
      for( nL=0; nL<(int)(nLength[1]-16); nL++ ) strLine += " ";
      strLine += convertToCurrencyString( dBerletBevetel );
      for( nL=0; nL<(int)(nLength[2]-convertToCurrencyString(dBerletBevetel).Length()); nL++ ) strLine += " ";
      strLine += convertToCurrencyString( dTermekBevetel );
      for( nL=0; nL<(int)(nLength[3]-convertToCurrencyString(dTermekBevetel).Length()); nL++ ) strLine += " ";
      strLine += convertToCurrencyString( dSumUzemeltFt );
      for( nL=0; nL<(int)(nLength[4]-convertToCurrencyString(dSumUzemeltFt).Length()); nL++ ) strLine += " ";
      strLine += convertToCurrencyString( dBerletBevetel+dTermekBevetel+dSumUzemeltFt );
      for( nL=0; nL<(int)(nLength[5]-convertToCurrencyString(dBerletBevetel+dTermekBevetel+dSumUzemeltFt).Length()); nL++ ) strLine += " ";
   }
   RichEditLista->Lines->Add( strLine );

   strLine = "";
   RichEditLista->Lines->Add( strLine );

   if( GB_FilterMuszak->Enabled )
   {
      strLine = "";
      for( nL=0; nL<137; nL++ ) strLine += "=";
      RichEditLista->Lines->Add( strLine );

      strLine = "";
      RichEditLista->Lines->Add( strLine );

      strLine = "";
      strLine += FormLanguage->LangStr(STR_COMMENT);
      RichEditLista->Lines->Add( strLine );

      strLine = "";
      for( nL=0; nL<137; nL++ ) strLine += "—";
      RichEditLista->Lines->Add( strLine );

      strLine = "";
      for( double i=0; i<pKonyv->GetGeneralKonyvCount(); i++ )
      {
         stTemp = pKonyv->GetGeneralKonyv( i );

         if( GB_FilterMuszak->Enabled && EditMuszakID->Text.ToDouble() != stTemp.dMuszakID )
         {
            continue;
         }

         strLine += AnsiString( stTemp.strMegjegyzes );
      }
      RichEditLista->Lines->Add( strLine );
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BtnStartPrevWeekClick(TObject *Sender)
{
   DTPickerStart->Date = DTPickerStart->Date-7;
   if( !DTPickerStop->Enabled )
      BtnStopPrevWeekClick(Sender);
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BtnStartPrevDayClick(TObject *Sender)
{
   DTPickerStart->Date = DTPickerStart->Date-1;
   if( !DTPickerStop->Enabled )
      BtnStopPrevDayClick(Sender);
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::DTPickerStartChange(TObject *Sender)
{
   if( !DTPickerStop->Enabled )
      DTPickerStop->Date = DTPickerStart->Date;
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BtnStartNextDayClick(TObject *Sender)
{
   DTPickerStart->Date = DTPickerStart->Date+1;
   if( !DTPickerStop->Enabled )
      BtnStopNextDayClick(Sender);
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BtnStartNextWeekClick(TObject *Sender)
{
   DTPickerStart->Date = DTPickerStart->Date+7;
   if( !DTPickerStop->Enabled )
      BtnStopNextWeekClick(Sender);
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BtnStopPrevWeekClick(TObject *Sender)
{
   DTPickerStop->Date = DTPickerStop->Date-7;
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BtnStopPrevDayClick(TObject *Sender)
{
   DTPickerStop->Date = DTPickerStop->Date-1;
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::DTPickerStopChange(TObject *Sender)
{
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BtnStopNextDayClick(TObject *Sender)
{
   DTPickerStop->Date = DTPickerStop->Date+1;
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BtnStopNextWeekClick(TObject *Sender)
{
   DTPickerStop->Date = DTPickerStop->Date+7;
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BtnPrevMuszakClick(TObject *Sender)
{
   if( EditMuszakID->Text.ToDouble() > 1 )
   {
      EditMuszakID->Text = AnsiString( EditMuszakID->Text.ToDouble()-1 );
   }
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BtnNextMuszakClick(TObject *Sender)
{
   if( EditMuszakID->Text.ToDouble() < dMuszakMax )
   {
      EditMuszakID->Text = AnsiString( EditMuszakID->Text.ToDouble()+1 );
   }
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::EditBerletChange(TObject *Sender)
{
   FillLista();
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BitBtnSaveClick(TObject *Sender)
{
   if( SaveDialog->Execute() )
   {
      FILE *file;

      if( (file = fopen( SaveDialog->FileName.c_str(), "wt" )) != NULL )
      {
         AnsiString  strMessage;

         fputs( RichEditLista->Text.c_str(), file );
         fclose(file);

         strMessage.sprintf( FormLanguage->LangStr(STR_LIST_SAVEDTOFILE).c_str(), SaveDialog->FileName.c_str() );
         Application->MessageBox( strMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_INFORMATION).c_str(), MB_ICONINFORMATION );
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BitBtnPrintClick(TObject *Sender)
{
   if( PrintDialog->Execute() )
   {
      TPrinter *Prntr = Printer();
      switch( nListaType )
      {
         case LISTA_BERLET:
            Prntr->Orientation = poPortrait;
            break;

         case LISTA_TERMEK:
            Prntr->Orientation = poPortrait;
            break;

         case LISTA_FOKONYV:
            Prntr->Orientation = poLandscape;
            break;
      }
      RichEditLista->PageRect = Rect(200,200,Prntr->PageWidth-200,Prntr->PageHeight-200);
      RichEditLista->Print( Caption );
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormLista::BitBtnOkClick(TObject *Sender)
{
   GB_FilterDatum->Enabled = false;
}
//---------------------------------------------------------------------------

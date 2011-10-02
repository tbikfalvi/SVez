//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AdatbazisKezeles.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAdatbazisKezeles *FormAdatbazisKezeles;
//---------------------------------------------------------------------------
__fastcall TFormAdatbazisKezeles::TFormAdatbazisKezeles(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::FormActivate(TObject *Sender)
{
   pKonyv->LOG4( "TFormAdatbazisKezeles::FormActivate" );

   nDBType = 0;
   nActionType = 0;

   DTPickerStart->Date = Now();
   DTPickerStop->Date = Now();

   RadioBerlet->Checked = false;
   RadioBerlethasznalat->Checked = false;
   RadioFokonyv->Checked = false;
   RadioSzolariumkonyv->Checked = false;
   RadioPenztar->Checked = false;
   RadioDBDelete->Checked = false;

   RadioDBDelete->Enabled = false;
   BitBtnExecute->Enabled = false;

   BtnStartPrevWeek->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::BitBtnOkClick(TObject *Sender)
{
   pKonyv->LOG4( "TFormAdatbazisKezeles::BitBtnOkClick" );

   ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::BtnStartPrevWeekClick(TObject *Sender)
{
   DTPickerStart->Date = DTPickerStart->Date-7;
   if( !DTPickerStop->Enabled )
      BtnStopPrevWeekClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::BtnStartPrevDayClick(TObject *Sender)
{
   DTPickerStart->Date = DTPickerStart->Date-1;
   if( !DTPickerStop->Enabled )
      BtnStopPrevDayClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::BtnStartNextDayClick(TObject *Sender)
{
   DTPickerStart->Date = DTPickerStart->Date+1;
   if( !DTPickerStop->Enabled )
      BtnStopNextDayClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::BtnStartNextWeekClick(TObject *Sender)
{
   DTPickerStart->Date = DTPickerStart->Date+7;
   if( !DTPickerStop->Enabled )
      BtnStopNextWeekClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::BtnStopPrevWeekClick(TObject *Sender)
{
   DTPickerStop->Date = DTPickerStop->Date-7;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::BtnStopPrevDayClick(TObject *Sender)
{
   DTPickerStop->Date = DTPickerStop->Date-1;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::BtnStopNextDayClick(TObject *Sender)
{
   DTPickerStop->Date = DTPickerStop->Date+1;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::BtnStopNextWeekClick(TObject *Sender)
{
   DTPickerStop->Date = DTPickerStop->Date+7;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::RadioBerletClick(TObject *Sender)
{
   nDBType = 1;
   strDB = RadioBerlet->Caption;
   RadioDBDelete->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::RadioBerlethasznalatClick(TObject *Sender)
{
   nDBType = 2;
   strDB = RadioBerlethasznalat->Caption;
   RadioDBDelete->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::RadioFokonyvClick(TObject *Sender)
{
   nDBType = 3;
   strDB = RadioFokonyv->Caption;
   RadioDBDelete->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::RadioSzolariumkonyvClick(TObject *Sender)
{
   nDBType = 4;
   strDB = RadioSzolariumkonyv->Caption;
   RadioDBDelete->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::RadioPenztarClick(TObject *Sender)
{
   nDBType = 5;
   strDB = RadioPenztar->Caption;
   RadioDBDelete->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::RadioDBDeleteClick(TObject *Sender)
{
   nActionType = 1;
   strAction = RadioDBDelete->Caption;
   BitBtnExecute->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdatbazisKezeles::BitBtnExecuteClick(TObject *Sender)
{
   pKonyv->LOG4( "TFormAdatbazisKezeles::BitBtnExecuteClick" );

   AnsiString  strMessage;
   TDate       DDate = Now();

   if( (int)DTPickerStart->Date == (int)DDate || (int)DTPickerStop->Date == (int)DDate )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_NODELETE_TODAY).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      return;
   }

   strMessage.sprintf( FormLanguage->LangStr(STR_MSG_ACTION_INFO).c_str(),
                       strAction.c_str(),
                       FormatDateTime("yyyy/mm/dd",DTPickerStart->Date),
                       FormatDateTime("yyyy/mm/dd",DTPickerStop->Date),
                       strDB.c_str() );
   Application->MessageBox( strMessage.c_str(),
                            FormLanguage->LangStr(STR_MSGBOX_INFORMATION).c_str(),
                            MB_ICONINFORMATION );
   if( Application->MessageBox( FormLanguage->LangStr(STR_MSG_DELETE_CONFIRM).c_str(),
                                FormLanguage->LangStr(STR_MSGBOX_QUESTION).c_str(),
                                MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 ) == IDYES )
   {
      pKonyv->strLogMsg = AnsiString( "Adatbazis kezeles [" ) +
                          strAction +
                          AnsiString( "/" ) +
                          FormatDateTime("yyyy/mm/dd",DTPickerStart->Date) +
                          AnsiString( "/" ) +
                          FormatDateTime("yyyy/mm/dd",DTPickerStop->Date) +
                          AnsiString( "/" ) +
                          strDB +
                          AnsiString( "]" );
      pKonyv->LOG2( pKonyv->strLogMsg );
      ExecuteDBAction();
   }
}
//---------------------------------------------------------------------------
void TFormAdatbazisKezeles::ExecuteDBAction()
{
   pKonyv->LOG4( "TFormAdatbazisKezeles::ExecuteDBAction" );

   switch( nDBType )
   {
      case 1:
         switch( nActionType )
         {
            case 1:
               DeleteBerlet();
               break;
         }
         break;

      case 2:
         switch( nActionType )
         {
            case 1:
               DeleteBerletHasznalat();
               break;
         }
         break;

      case 3:
         switch( nActionType )
         {
            case 1:
               DeleteFoKonyv();
               break;
         }
         break;

      case 4:
         switch( nActionType )
         {
            case 1:
               DeleteSzolariumKonyv();
               break;
         }
         break;

      case 5:
         switch( nActionType )
         {
            case 1:
               DeletePenztarKonyv();
               break;
         }
         break;
   }
}
//---------------------------------------------------------------------------
void TFormAdatbazisKezeles::DeleteBerlet()
{
   pKonyv->LOG4( "TFormAdatbazisKezeles::DeleteBerlet" );

   AnsiString  strMessage;

   strMessage.sprintf( "Bérlet adatok törlése %s - %s",
                       DTPickerStart->Date.FormatString( "yyyy/mm/dd" ),
                       DTPickerStop->Date.FormatString( "yyyy/mm/dd" ) );
   pKonyv->LOG2( strMessage );

   double      dCount = 0;

   for( double i=0; i<pBerletek->GetBerletCount(); /*törlés miatt i++ lent*/ )
   {
      typ_berlet  stTemp = pBerletek->GetBerletItem( i );

      TDate DDatum = TDate( stTemp.nErvEv, stTemp.nErvHo, stTemp.nErvNap );
      if( DDatum < DTPickerStart->Date || DTPickerStop->Date < DDatum )
      {
         i++;
         continue;
      }
      pBerletek->DeleteBerlet( stTemp.strVonalkod, false );
      dCount++;
   }

   pBerletek->SaveBerlet( pBerletek->sBerletFile.c_str() );
   strMessage.sprintf( FormLanguage->LangStr(STR_MSG_DELETE_SUMMARY).c_str(), dCount );
   Application->MessageBox( strMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_INFORMATION).c_str(), MB_ICONINFORMATION );
}
//---------------------------------------------------------------------------
void TFormAdatbazisKezeles::DeleteBerletHasznalat()
{
   pKonyv->LOG4( "TFormAdatbazisKezeles::DeleteBerletHasznalat" );

   AnsiString  strMessage;

   strMessage.sprintf( "Bérlet használatok törlése %s - %s",
                       DTPickerStart->Date.FormatString( "yyyy/mm/dd" ),
                       DTPickerStop->Date.FormatString( "yyyy/mm/dd" ) );
   pKonyv->LOG2( strMessage );

   double      dCount = 0;

   for( double i=0; i<pBerletek->GetBerletHasznalatCount(); /*törlés miatt i++ lent*/ )
   {
      typ_berlethasznalat  stTemp = pBerletek->GetBerletHasznalatItem( i );

      TDate DDatum = TDate( stTemp.nEv, stTemp.nHo, stTemp.nNap );
      if( DDatum < DTPickerStart->Date || DTPickerStop->Date < DDatum )
      {
         i++;
         continue;
      }
      pBerletek->DeleteBerletHasznalat( stTemp, false );
      dCount++;
   }

   pBerletek->SaveBerlethasznalat( pBerletek->sBerletHasznalatFile.c_str() );
   strMessage.sprintf( FormLanguage->LangStr(STR_MSG_DELETE_SUMMARY).c_str(), dCount );
   Application->MessageBox( strMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_INFORMATION).c_str(), MB_ICONINFORMATION );
}
//---------------------------------------------------------------------------
void TFormAdatbazisKezeles::DeleteFoKonyv()
{
   pKonyv->LOG4( "TFormAdatbazisKezeles::DeleteFoKonyv" );

   AnsiString  strMessage;

   strMessage.sprintf( "Fökönyv adatok törlése %s - %s",
                       DTPickerStart->Date.FormatString( "yyyy/mm/dd" ),
                       DTPickerStop->Date.FormatString( "yyyy/mm/dd" ) );
   pKonyv->LOG2( strMessage );

   double      dCount = 0;

   for( double i=0; i<pKonyv->GetGeneralKonyvCount(); /*törlés miatt i++ lent*/ )
   {
      typ_konyv_general stTemp = pKonyv->GetGeneralKonyv( i );

      if( stTemp.dStartDateTime < DTPickerStart->Date ||
          stTemp.dStopDateTime > DTPickerStop->Date )
      {
         i++;
         continue;
      }
      pKonyv->DeleteGeneralKonyv( stTemp.dID, false );
      dCount++;
   }

   pKonyv->SaveGeneralKonyv( pKonyv->sKonyvGeneralFile.c_str() );
   strMessage.sprintf( FormLanguage->LangStr(STR_MSG_DELETE_SUMMARY).c_str(), dCount );
   Application->MessageBox( strMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_INFORMATION).c_str(), MB_ICONINFORMATION );
}
//---------------------------------------------------------------------------
void TFormAdatbazisKezeles::DeleteSzolariumKonyv()
{
   pKonyv->LOG4( "TFormAdatbazisKezeles::DeleteSzolariumKonyv" );

   AnsiString  strMessage;

   strMessage.sprintf( "Szolárium könyv adatok törlése %s - %s",
                       DTPickerStart->Date.FormatString( "yyyy/mm/dd" ),
                       DTPickerStop->Date.FormatString( "yyyy/mm/dd" ) );
   pKonyv->LOG2( strMessage );

   double      dCount = 0;

   for( double i=0; i<pKonyv->GetSzolariumKonyvCount(); /*törlés miatt i++ lent*/ )
   {
      typ_konyv_szolarium  stTemp = pKonyv->GetSzolariumKonyv( i );

      if( stTemp.dID < DTPickerStart->Date ||
          stTemp.dID > DTPickerStop->Date )
      {
         i++;
         continue;
      }
      pKonyv->DeleteSzolariumKonyv( stTemp.dID, false );
      dCount++;
   }

   pKonyv->SaveSolariumKonyv( pKonyv->sKonyvSzolariumFile.c_str() );
   strMessage.sprintf( FormLanguage->LangStr(STR_MSG_DELETE_SUMMARY).c_str(), dCount );
   Application->MessageBox( strMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_INFORMATION).c_str(), MB_ICONINFORMATION );
}
//---------------------------------------------------------------------------
void TFormAdatbazisKezeles::DeletePenztarKonyv()
{
   pKonyv->LOG4( "TFormAdatbazisKezeles::DeletePenztarKonyv" );

   AnsiString  strMessage;

   strMessage.sprintf( "Pénztárkönyv adatok törlése %s - %s",
                       DTPickerStart->Date.FormatString( "yyyy/mm/dd" ),
                       DTPickerStop->Date.FormatString( "yyyy/mm/dd" ) );
   pKonyv->LOG2( strMessage );

   double      dCount = 0;

   for( double i=0; i<pPenztar->GetPenztarActionCount(); /*törlés miatt i++ lent*/ )
   {
      typ_penztar_action   stTemp = pPenztar->GetPenztarAction( i );

      TDate DDate = TDate( stTemp.dDateTime );
      if( DDate < DTPickerStart->Date || DTPickerStop->Date < DDate )
      {
         i++;
         continue;
      }
      pPenztar->DeletePenztarAction( stTemp.dDateTime, false );
      dCount++;
   }

   pPenztar->SavePenztarActions( pPenztar->sPenztarLogFile.c_str() );
   strMessage.sprintf( FormLanguage->LangStr(STR_MSG_DELETE_SUMMARY).c_str(), dCount );
   Application->MessageBox( strMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_INFORMATION).c_str(), MB_ICONINFORMATION );
}
//---------------------------------------------------------------------------

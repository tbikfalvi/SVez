//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BerletKezeles.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormBerlet *FormBerlet;
//---------------------------------------------------------------------------
__fastcall TFormBerlet::TFormBerlet(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormBerlet::FormActivate(TObject *Sender)
{
   StringGridBerletTipus->ColWidths[0] = 0;
   StringGridBerletTipus->ColWidths[1] = 200;
   StringGridBerletTipus->ColWidths[2] = 65;
   StringGridBerletTipus->ColWidths[3] = 65;

   FillListBerletTipusok();
   StringGridBerletTipus->SetFocus();
   ListBoxBerletTipusokClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormBerlet::FormShortCut(TWMKey &Msg, bool &Handled)
{
   if (Msg.CharCode == VK_RETURN)
   {
      Handled = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormBerlet::BitBtnOkClick(TObject *Sender)
{
   ModalResult = mrOk;
}
/****************************************************************************
*
* BÉRLET TÍPUSOK KEZELESE
*
****************************************************************************/
//---------------------------------------------------------------------------
void TFormBerlet::FillListBerletTipusok()
{
   int i;
   typ_berlettipus   stTemp;

   for( i=0; i<StringGridBerletTipus->RowCount; i++ )
      StringGridBerletTipus->Rows[i]->Clear();

   if( pBerlet->GetBerletTipusCount() == 0 )
      StringGridBerletTipus->RowCount = 2;
   else
      StringGridBerletTipus->RowCount = pBerlet->GetBerletTipusCount()+1;
   StringGridBerletTipus->FixedRows = 1;
   StringGridBerletTipus->Cells[0][0] = "0";
   StringGridBerletTipus->Cells[1][0] = FormLanguage->LangStr(STR_NAME);
   StringGridBerletTipus->Cells[2][0] = FormLanguage->LangStr(STR_UNIT);
   StringGridBerletTipus->Cells[3][0] = FormLanguage->LangStr(STR_PRICE);

   for( i=0; i<(int)pBerlet->GetBerletTipusCount(); i++ )
   {
      stTemp = pBerlet->GetBerletTipus( i );

      StringGridBerletTipus->Cells[0][i+1] = AnsiString( stTemp.nID );
      StringGridBerletTipus->Cells[1][i+1] = AnsiString( stTemp.strNev );
      StringGridBerletTipus->Cells[2][i+1] = AnsiString( stTemp.nEgyseg );
      StringGridBerletTipus->Cells[3][i+1] = convertToCurrencyString( stTemp.nAr );
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormBerlet::ListBoxBerletTipusokClick(TObject *Sender)
{
   typ_berlettipus   stTemp;

   memset( &stTemp, 0, sizeof(stTemp) );

   ButtonBTModify->Enabled = false;
   ButtonBTDelete->Enabled = false;

   TStrings *Items = StringGridBerletTipus->Rows[StringGridBerletTipus->Row];
   if( !Items->Strings[0].IsEmpty() )
   {
      stTemp = pBerlet->GetBerletTipusID( Items->Strings[0].ToDouble() );

      ButtonBTModify->Enabled = true;
      ButtonBTDelete->Enabled = true;
   }

   EditBTID->Text = AnsiString( stTemp.nID );
   EditBTNev->Text = AnsiString( stTemp.strNev );
   EditBTAr->Text = convertToCurrencyString( stTemp.nAr );
   EditBTEgyseg->Text = AnsiString( stTemp.nEgyseg );
   EditBTErvTolEv->Text = AnsiString( stTemp.nErvTolEv );
   EditBTErvTolHo->Text = AnsiString( stTemp.nErvTolHo );
   EditBTErvTolNap->Text = AnsiString( stTemp.nErvTolNap );
   EditBTErvIgEv->Text = AnsiString( stTemp.nErvIgEv );
   EditBTErvIgHo->Text = AnsiString( stTemp.nErvIgHo );
   EditBTErvIgNap->Text = AnsiString( stTemp.nErvIgNap );
   EditBTErvNapok->Text = AnsiString( stTemp.nErvNapok );
   EditBTEgysegido->Text = AnsiString( stTemp.nEgysegIdo );

   EditBTNev->Enabled = false;
   EditBTAr->Enabled = false;
   EditBTEgyseg->Enabled = false;
   EditBTErvTolEv->Enabled = false;
   EditBTErvTolHo->Enabled = false;
   EditBTErvTolNap->Enabled = false;
   EditBTErvIgEv->Enabled = false;
   EditBTErvIgHo->Enabled = false;
   EditBTErvIgNap->Enabled = false;
   EditBTErvNapok->Enabled = false;
   EditBTEgysegido->Enabled = false;

   ButtonBTNew->Enabled = true;

   ButtonBTSave->Enabled = false;
   ButtonBTSave->Caption = FormLanguage->LangStr(STR_BTN_MODIFY);
   ButtonBTCancel->Enabled = false;

   BitBtnOk->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormBerlet::ButtonBTNewClick(TObject *Sender)
{
/*   int i,j;
   typ_berlettipus   stTemp;

   for( i=0, j=1; i<(int)pBerlet->GetBerletTipusCount(); i++, j++ )
   {
      stTemp = pBerlet->GetBerletTipus( i );
      if( j != stTemp.nID )
      {
         break;
      }
   }*/
//   EditBTID->Text = AnsiString( j );
   EditBTID->Text = "0";
   EditBTNev->Enabled = true;
   EditBTNev->Text = "";
   EditBTAr->Enabled = true;
   EditBTAr->Text = "";
   EditBTEgyseg->Enabled = true;
   EditBTEgyseg->Text = "";
   EditBTErvTolEv->Enabled = true;
   EditBTErvTolEv->Text = "";
   EditBTErvTolHo->Enabled = true;
   EditBTErvTolHo->Text = "";
   EditBTErvTolNap->Enabled = true;
   EditBTErvTolNap->Text = "";
   EditBTErvIgEv->Enabled = true;
   EditBTErvIgEv->Text = "";
   EditBTErvIgHo->Enabled = true;
   EditBTErvIgHo->Text = "";
   EditBTErvIgNap->Enabled = true;
   EditBTErvIgNap->Text = "";
   EditBTErvNapok->Enabled = true;
   EditBTErvNapok->Text = "";
   EditBTEgysegido->Enabled = true;
   EditBTEgysegido->Text = "";

   ButtonBTNew->Enabled = false;
   ButtonBTModify->Enabled = false;
   ButtonBTDelete->Enabled = false;

   ButtonBTSave->Enabled = true;
   ButtonBTSave->Caption = FormLanguage->LangStr(STR_BTN_SAVE);
   ButtonBTCancel->Enabled = true;

   EditBTNev->SetFocus();
   StringGridBerletTipus->Enabled = false;

   BitBtnOk->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormBerlet::ButtonBTModifyClick(TObject *Sender)
{
   EditBTNev->Enabled = true;
   EditBTAr->Enabled = true;
   EditBTEgyseg->Enabled = true;
   EditBTErvTolEv->Enabled = true;
   EditBTErvTolHo->Enabled = true;
   EditBTErvTolNap->Enabled = true;
   EditBTErvIgEv->Enabled = true;
   EditBTErvIgHo->Enabled = true;
   EditBTErvIgNap->Enabled = true;
   EditBTErvNapok->Enabled = true;
   EditBTEgysegido->Enabled = true;

   ButtonBTNew->Enabled = false;
   ButtonBTModify->Enabled = false;
   ButtonBTDelete->Enabled = false;

   ButtonBTSave->Enabled = true;
   ButtonBTSave->Caption = FormLanguage->LangStr(STR_BTN_MODIFY);
   ButtonBTCancel->Enabled = true;

   EditBTNev->SetFocus();
   StringGridBerletTipus->Enabled = false;

   BitBtnOk->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormBerlet::ButtonBTDeleteClick(TObject *Sender)
{
   if( Application->MessageBox( FormLanguage->LangStr(STR_CARDTYPE_DELETE_CONFIRM).c_str(),
                                FormLanguage->LangStr(STR_MSGBOX_QUESTION).c_str(),
                                MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 ) == IDYES )
   {
      TStrings *Items = StringGridBerletTipus->Rows[StringGridBerletTipus->Row];

      pBerlet->strLogMsg = AnsiString( "Berlettipus torlese [" ) +
                           AnsiString( Items->Strings[1] ) +
                           AnsiString( "]" );
      pBerlet->LOG2( pBerlet->strLogMsg );
      if( !pBerlet->DeleteBerletTipus( Items->Strings[0].ToInt() ) )
      {
         Application->MessageBox( FormLanguage->LangStr(STR_ERR_CARDTYPE_NOTEXISTS).c_str(),
                                  FormLanguage->LangStr(STR_MSGBOX_ERROR).c_str(),
                                  MB_ICONSTOP );
      }
      FillListBerletTipusok();
      StringGridBerletTipus->SetFocus();
      ListBoxBerletTipusokClick(Sender);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormBerlet::ButtonBTCancelClick(TObject *Sender)
{
   StringGridBerletTipus->Enabled = true;
   StringGridBerletTipus->SetFocus();

   ListBoxBerletTipusokClick(Sender);
}
//---------------------------------------------------------------------------
bool TFormBerlet::AdatEllenorzes()
{
   if( !EditBTNev->Text.Length() )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_ERR_CARDTYPE_NAME_MISSING).c_str(),
                               FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                               MB_ICONEXCLAMATION );
      EditBTNev->SetFocus();
      return false;
   }
   if( EditBTAr->Text.IsEmpty() )
      EditBTAr->Text = "0.00";
   if( EditBTEgyseg->Text.IsEmpty() )
      EditBTEgyseg->Text = "0";
   if( EditBTErvTolEv->Text.IsEmpty() )
      EditBTErvTolEv->Text = "0";
   if( EditBTErvTolHo->Text.IsEmpty() )
      EditBTErvTolHo->Text = "0";
   if( EditBTErvTolNap->Text.IsEmpty() )
      EditBTErvTolNap->Text = "0";
   if( EditBTErvIgEv->Text.IsEmpty() )
      EditBTErvIgEv->Text = "0";
   if( EditBTErvIgHo->Text.IsEmpty() )
      EditBTErvIgHo->Text = "0";
   if( EditBTErvIgNap->Text.IsEmpty() )
      EditBTErvIgNap->Text = "0";
   if( EditBTErvNapok->Text.IsEmpty() )
      EditBTErvNapok->Text = "0";
   if( EditBTEgysegido->Text.IsEmpty() )
      EditBTEgysegido->Text = "0";

   return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormBerlet::ButtonBTSaveClick(TObject *Sender)
{
   typ_berlettipus   stTemp;

   if( !AdatEllenorzes() )
      return;

   try
   {
      stTemp.nID        = EditBTID->Text.ToInt();
      strncpy( stTemp.strNev, EditBTNev->Text.c_str(), sizeof(stTemp.strNev)-2 );
      stTemp.nAr        = convertCurrencyString(EditBTAr->Text.c_str());
      stTemp.nEgyseg    = EditBTEgyseg->Text.ToInt();
      stTemp.nErvTolEv  = EditBTErvTolEv->Text.ToInt();
      stTemp.nErvTolHo  = EditBTErvTolHo->Text.ToInt();
      stTemp.nErvTolNap = EditBTErvTolNap->Text.ToInt();
      stTemp.nErvIgEv   = EditBTErvIgEv->Text.ToInt();
      stTemp.nErvIgHo   = EditBTErvIgHo->Text.ToInt();
      stTemp.nErvIgNap  = EditBTErvIgNap->Text.ToInt();
      stTemp.nErvNapok  = EditBTErvNapok->Text.ToInt();
      stTemp.nEgysegIdo = EditBTEgysegido->Text.ToInt();
   }
   catch(const Exception& e)
   {
      AnsiString eMessage = FormLanguage->LangStr(STR_MSG_USENUMBERONLY);
      Application->MessageBox( eMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_ERROR).c_str(), MB_ICONSTOP );
      return;
   }

   if( !ButtonBTSave->Caption.AnsiCompare( FormLanguage->LangStr(STR_BTN_SAVE) ) )
   {
      pBerlet->strLogMsg = AnsiString( "Uj berlettipus felvetele [" );
      pBerlet->AddBerletTipus( stTemp );
      FillListBerletTipusok();
   }
   else if( !ButtonBTSave->Caption.AnsiCompare( FormLanguage->LangStr(STR_BTN_MODIFY) ) )
   {
      pBerlet->strLogMsg = AnsiString( "Uj berlettipus felvetele [" );
      pBerlet->ModifyBerletTipus( stTemp );
      FillListBerletTipusok();
   }
   pBerlet->strLogMsg += AnsiString( stTemp.strNev );
   pBerlet->strLogMsg += AnsiString( "]" );
   pBerlet->LOG2( pBerlet->strLogMsg );

   StringGridBerletTipus->Enabled = true;
   StringGridBerletTipus->SetFocus();
   for( int i=0; i<StringGridBerletTipus->RowCount; i++ )
   {
      TStrings *Items = StringGridBerletTipus->Rows[i];
      if( Items->Strings[0].ToDouble() == stTemp.nID )
      {
         StringGridBerletTipus->Row = i;
         ListBoxBerletTipusokClick(Sender);
         break;
      }
   }
}
//---------------------------------------------------------------------------

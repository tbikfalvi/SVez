//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TermekKezeles.h"
#include "DialogInput.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTermekKezeles *FormTermekKezeles;
//---------------------------------------------------------------------------
__fastcall TFormTermekKezeles::TFormTermekKezeles(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::FormActivate(TObject *Sender)
{
   StringGridTermek->ColWidths[0] = 0;
   StringGridTermek->ColWidths[1] = 252;
   StringGridTermek->ColWidths[2] = 130;
   StringGridTermek->ColWidths[3] = 80;
   StringGridTermek->ColWidths[4] = 80;
   StringGridTermek->ColWidths[5] = 70;

   FillListTermekek( Sender );
   EditSearchNev->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::FormShortCut(TWMKey &Msg, bool &Handled)
{
   if (Msg.CharCode == VK_RETURN)
   {
      Handled = true;
   }
}
//---------------------------------------------------------------------------
void TFormTermekKezeles::FillListTermekek( TObject *Sender )
{
   int i;
   typ_termek   stTemp;

   for( i=0; i<StringGridTermek->RowCount; i++ )
      StringGridTermek->Rows[i]->Clear();

   if( pTermek->GetTermekCount() == 0 )
      StringGridTermek->RowCount = 2;
   else
      StringGridTermek->RowCount = pTermek->GetTermekCount()+1;
   StringGridTermek->FixedRows = 1;
   StringGridTermek->Cells[0][0] = "0";
   StringGridTermek->Cells[1][0] = FormLanguage->LangStr(STR_PRODUCT);
   StringGridTermek->Cells[2][0] = FormLanguage->LangStr(STR_BARCODE);
   StringGridTermek->Cells[3][0] = FormLanguage->LangStr(STR_UNITPRICE);
   StringGridTermek->Cells[4][0] = FormLanguage->LangStr(STR_UNITPRICE_BUY);
   StringGridTermek->Cells[5][0] = FormLanguage->LangStr(STR_STOCK);

   for( i=0; i<(int)pTermek->GetTermekCount(); i++ )
   {
      stTemp = pTermek->GetTermekItem( i );

      StringGridTermek->Cells[0][i+1] = AnsiString( stTemp.nID );
      StringGridTermek->Cells[1][i+1] = AnsiString( stTemp.strNev );
      StringGridTermek->Cells[2][i+1] = AnsiString( stTemp.strVonalkod );
      StringGridTermek->Cells[3][i+1] = convertToCurrencyString( stTemp.nAr );
      StringGridTermek->Cells[4][i+1] = convertToCurrencyString( stTemp.nArBeszerzes );
      StringGridTermek->Cells[5][i+1] = AnsiString( stTemp.nDarab );
   }

   if( !BitBtnSortName->Enabled )
   {
      SortListTermekek( 1 );
   }
   else if( !BitBtnSortCode->Enabled )
   {
      SortListTermekek( 2 );
   }

   StringGridTermek->Row = 1;
   StringGridTermekClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::StringGridTermekClick(TObject *Sender)
{
   typ_termek  stTemp;

   memset( &stTemp, 0, sizeof(stTemp) );

   BitBtnNew->Enabled = true;
   BitBtnModify->Enabled = false;
   BitBtnDelete->Enabled = false;
   BitBtnPlus->Enabled = false;
   BitBtnMinus->Enabled = false;
   BitBtnOk->Enabled = true;
   EditSearchNev->Enabled = true;
   EditSearchVonalkod->Enabled = true;
   TStrings *Items = StringGridTermek->Rows[StringGridTermek->Row];
   if( !Items->Strings[0].IsEmpty() )
   {
      BitBtnModify->Enabled = true;
      BitBtnDelete->Enabled = true;
      BitBtnPlus->Enabled = true;
      BitBtnMinus->Enabled = true;

      stTemp.nID = Items->Strings[0].ToDouble();
      strcpy( stTemp.strNev, Items->Strings[1].c_str() );
      strcpy( stTemp.strVonalkod, Items->Strings[2].c_str() );
      stTemp.nAr = convertCurrencyString(Items->Strings[3].c_str());
      stTemp.nArBeszerzes = convertCurrencyString(Items->Strings[4].c_str());
      stTemp.nDarab = Items->Strings[5].ToInt();

      ListBoxAssigned->Clear();
      ListBoxAll->Clear();
      for( int i=0; i<(int)pTermekTipus->GetTermekTipusCount(); i++ )
      {
         typ_termektipusassign   stAsg;
         typ_termektipus         stTermekTipus;

         stTermekTipus = pTermekTipus->GetTermekTipusItem( i );

         stAsg.nTermekID = stTemp.nID;
         stAsg.nTTipusID = stTermekTipus.nID;

         if( pTermekTipus->CheckTermekTipusAsg( stAsg ) )
         {
            ListBoxAssigned->Items->Add( stTermekTipus.strNev );
         }
         else
         {
            ListBoxAll->Items->Add( stTermekTipus.strNev );
         }
      }
   }

   EditID->Text = AnsiString( stTemp.nID );
   EditNev->Enabled = false;
   EditNev->Text = AnsiString( stTemp.strNev );
   EditVonalkod->Enabled = false;
   EditVonalkod->Text = AnsiString( stTemp.strVonalkod );
   EditAr->Enabled = false;
   EditAr->Text = convertToCurrencyString( stTemp.nAr );
   EditArBeszerzes->Enabled = false;
   EditArBeszerzes->Text = convertToCurrencyString( stTemp.nArBeszerzes );
   EditDarab->Enabled = false;
   EditDarab->Text = AnsiString( stTemp.nDarab );
   ListBoxAssigned->Enabled = false;
   BitBtnAdd->Enabled = false;
   BitBtnRemove->Enabled = false;
   ListBoxAll->Enabled = false;
}
//---------------------------------------------------------------------------
void TFormTermekKezeles::SelectTermekInList( DWORD nID )
{
   int i;

   for( i=1; i<StringGridTermek->RowCount; i++ )
   {
      TStrings *Items = StringGridTermek->Rows[i];
      if( Items->Strings[0].ToDouble() == nID )
      {
         StringGridTermek->Row = i;
         break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::EditSearchNevChange(TObject *Sender)
{
   for( int i=1; i<StringGridTermek->RowCount; i++ )
   {
      TStrings *Items = StringGridTermek->Rows[i];
      if( Items->Strings[1].UpperCase().Pos(EditSearchNev->Text.UpperCase()) > 0 )
      {
         StringGridTermek->Row = i;
         break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::BitBtnSortNameClick(TObject *Sender)
{
   BitBtnSortName->Enabled = false;
   BitBtnSortCode->Enabled = true;
   SortListTermekek( 1 );
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::EditSearchVonalkodChange(
      TObject *Sender)
{
   for( int i=1; i<StringGridTermek->RowCount; i++ )
   {
      TStrings *Items = StringGridTermek->Rows[i];
      if( Items->Strings[2].UpperCase().Pos(EditSearchVonalkod->Text.UpperCase()) > 0 )
      {
         StringGridTermek->Row = i;
         break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::BitBtnSortCodeClick(TObject *Sender)
{
   BitBtnSortName->Enabled = true;
   BitBtnSortCode->Enabled = false;
   SortListTermekek( 2 );
}
//---------------------------------------------------------------------------
void TFormTermekKezeles::SortListTermekek( int nCell )
{
   bool  bCsere;
   int i,j;

   for( i=2; i<StringGridTermek->RowCount; i++ )
   {
      j = i-1;
      do
      {
         bCsere = false;
         TStrings *ItemsBubble = StringGridTermek->Rows[j+1];
         TStrings *Items = StringGridTermek->Rows[j];

         if( strcmp( ItemsBubble->Strings[nCell].UpperCase().c_str(), Items->Strings[nCell].UpperCase().c_str() ) < 0 )
         {
            bCsere = true;
            typ_termek  stTemp;

            stTemp.nID = Items->Strings[0].ToDouble();
            strcpy( stTemp.strNev, Items->Strings[1].c_str() );
            strcpy( stTemp.strVonalkod, Items->Strings[2].c_str() );
            stTemp.nAr = convertCurrencyString(Items->Strings[3].c_str());
            stTemp.nArBeszerzes = convertCurrencyString(Items->Strings[4].c_str());
            stTemp.nDarab = Items->Strings[5].ToInt();

            StringGridTermek->Cells[0][j] = ItemsBubble->Strings[0];
            StringGridTermek->Cells[1][j] = ItemsBubble->Strings[1];
            StringGridTermek->Cells[2][j] = ItemsBubble->Strings[2];
            StringGridTermek->Cells[3][j] = ItemsBubble->Strings[3];
            StringGridTermek->Cells[4][j] = ItemsBubble->Strings[4];
            StringGridTermek->Cells[5][j] = ItemsBubble->Strings[5];

            StringGridTermek->Cells[0][j+1] = AnsiString( stTemp.nID );
            StringGridTermek->Cells[1][j+1] = AnsiString( stTemp.strNev );
            StringGridTermek->Cells[2][j+1] = AnsiString( stTemp.strVonalkod );
            StringGridTermek->Cells[3][j+1] = convertToCurrencyString( stTemp.nAr );
            StringGridTermek->Cells[4][j+1] = convertToCurrencyString( stTemp.nArBeszerzes );
            StringGridTermek->Cells[5][j+1] = AnsiString( stTemp.nDarab );
         }
         j--;
      } while( j>0 && bCsere);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::BitBtnNewClick(TObject *Sender)
{
   int i;
   DWORD j;
   typ_termek   stTemp;

   for( i=0, j=1; i<(int)pTermek->GetTermekCount(); i++, j++ )
   {
      stTemp = pTermek->GetTermekItem( i );
      if( j != stTemp.nID )
      {
         break;
      }
   }
   EditID->Text = AnsiString( j );
   EditNev->Enabled = true;
   EditNev->Text = "";
   EditVonalkod->Enabled = true;
   EditVonalkod->Text = "";
   EditAr->Enabled = true;
   EditAr->Text = "";
   EditArBeszerzes->Enabled = true;
   EditArBeszerzes->Text = "";
   EditDarab->Enabled = true;
   EditDarab->Text = "";
   ListBoxAssigned->Enabled = true;
   BitBtnAdd->Enabled = true;
   BitBtnRemove->Enabled = true;
   ListBoxAll->Enabled = true;

   BitBtnSaveModify->Enabled = true;
   BitBtnSaveModify->Caption = FormLanguage->LangStr(STR_BTN_SAVE);
   BitBtnCancel->Enabled = true;

   BitBtnOk->Enabled = false;
   BitBtnNew->Enabled = false;
   EditSearchNev->Enabled = false;
   EditSearchVonalkod->Enabled = false;
   BitBtnModify->Enabled = false;
   BitBtnDelete->Enabled = false;
   BitBtnPlus->Enabled = false;
   BitBtnMinus->Enabled = false;

   EditNev->SetFocus();
   StringGridTermek->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::BitBtnModifyClick(TObject *Sender)
{
   EditNev->Enabled = true;
   EditVonalkod->Enabled = true;
   EditAr->Enabled = true;
   EditArBeszerzes->Enabled = true;
   EditDarab->Enabled = true;
   ListBoxAssigned->Enabled = true;
   BitBtnAdd->Enabled = true;
   BitBtnRemove->Enabled = true;
   ListBoxAll->Enabled = true;

   BitBtnSaveModify->Enabled = true;
   BitBtnSaveModify->Caption = FormLanguage->LangStr(STR_BTN_MODIFY);
   BitBtnCancel->Enabled = true;

   EditNev->SetFocus();
   StringGridTermek->Enabled = false;

   BitBtnOk->Enabled = false;
   BitBtnNew->Enabled = false;
   EditSearchNev->Enabled = false;
   EditSearchVonalkod->Enabled = false;
   BitBtnModify->Enabled = false;
   BitBtnDelete->Enabled = false;
   BitBtnPlus->Enabled = false;
   BitBtnMinus->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::BitBtnDeleteClick(TObject *Sender)
{
   if( Application->MessageBox( FormLanguage->LangStr(STR_MSG_DELPRODUCT_CONFIRM).c_str(), FormLanguage->LangStr(STR_MSGBOX_QUESTION).c_str(), MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 ) == IDYES )
   {
      TStrings *Items = StringGridTermek->Rows[StringGridTermek->Row];

      BitBtnNew->Enabled = false;
      BitBtnModify->Enabled = false;
      BitBtnDelete->Enabled = false;
      BitBtnPlus->Enabled = false;
      BitBtnMinus->Enabled = false;

      pTermek->strLogMsg = AnsiString( "Termek torlese [" ) +
                           AnsiString( Items->Strings[2] ) +
                           AnsiString( "/" ) +
                           AnsiString( Items->Strings[1] ) +
                           AnsiString( "]" );
      pTermek->LOG2( pTermek->strLogMsg );
      pTermek->DeleteTermek( Items->Strings[0].ToDouble() );
      FillListTermekek( Sender );
      StringGridTermek->SetFocus();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::BitBtnSaveModifyClick(TObject *Sender)
{
   typ_termek  stTemp;

   memset( &stTemp, 0, sizeof(stTemp) );

   if( EditNev->Text.Length() == 0 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_PRODNAME_MISSING).c_str(),
                               FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                               MB_ICONEXCLAMATION );
      EditNev->SetFocus();
      return;
   }
   else
   {
      stTemp = pTermek->GetTermekNev( EditNev->Text.c_str() );
      if( stTemp.nID != EditID->Text.ToDouble() && stTemp.nID )
      {
         Application->MessageBox( FormLanguage->LangStr(STR_MSG_PRODNAME_INUSE).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
         EditNev->SetFocus();
         return;
      }
   }
   if( EditVonalkod->Text.Length() == 0 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_PRODBARCODE_MISSING).c_str(),
                               FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                               MB_ICONEXCLAMATION );
      EditVonalkod->SetFocus();
      return;
   }
   else
   {
      stTemp = pTermek->GetTermekKod( EditVonalkod->Text.c_str() );
      if( stTemp.nID != EditID->Text.ToDouble() && stTemp.nID )
      {
         AnsiString  strMessage;
         strMessage.sprintf( FormLanguage->LangStr(STR_MSG_PRODBARCODE_INUSE).c_str(), stTemp.strNev );
         Application->MessageBox( strMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
         EditVonalkod->SetFocus();
         return;
      }
      // vonalkód keresése a bérleteknél, hiba, ha megtalálta
      typ_berlet stBerlet = pBerlet->GetBerlet( EditVonalkod->Text.c_str() );

      if( stBerlet.nBerletTipus != 0 )
      {
         Application->MessageBox( FormLanguage->LangStr(STR_MSG_BARCODE_INUSE).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
         EditVonalkod->SetFocus();
         return;
      }
   }
   if( EditAr->Text.Length() == 0 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_PRODPRICE_MISSING).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      EditAr->SetFocus();
      return;
   }
   if( EditArBeszerzes->Text.Length() == 0 )
   {
      EditArBeszerzes->Text = EditAr->Text;
   }
   if( EditDarab->Text.Length() == 0 )
   {
      EditDarab->Text = "0";
   }

   stTemp.nID = EditID->Text.ToDouble();
   strncpy( stTemp.strNev, EditNev->Text.c_str(), sizeof(stTemp.strNev)-2 );
   strncpy( stTemp.strVonalkod, EditVonalkod->Text.c_str(), sizeof(stTemp.strVonalkod)-2 );
   stTemp.nAr = convertCurrencyString(EditAr->Text.c_str());
   stTemp.nDarab = EditDarab->Text.ToInt();
   stTemp.nArBeszerzes = convertCurrencyString(EditArBeszerzes->Text.c_str());

   typ_termektipusassign stAsg;

   stAsg.nTermekID = stTemp.nID;
   stAsg.nTTipusID = 0;
   pTermekTipus->DeleteTermekTipusAsg( stAsg );

   for( int i=0; i<ListBoxAssigned->Items->Count; i++ )
   {
      stAsg.nTTipusID = pTermekTipus->GetTermekTipusNev( ListBoxAssigned->Items->Strings[i].c_str() );
      pTermekTipus->AddTermekTipusAsg( stAsg );
   }

   if( BitBtnSaveModify->Caption.AnsiCompare(FormLanguage->LangStr(STR_BTN_SAVE)) == 0 )
   {
      pTermek->strLogMsg = AnsiString( "Uj termek felvetele [" );
      pTermek->AddTermek( stTemp );
   }
   else if( BitBtnSaveModify->Caption.AnsiCompare(FormLanguage->LangStr(STR_BTN_MODIFY)) == 0 )
   {
      pTermek->strLogMsg = AnsiString( "Termek modositasa [" );
      if( !pTermek->ModifyTermek( stTemp ) )
      {
         Application->MessageBox( FormLanguage->LangStr(STR_MSG_PROD_NOTEXISTS).c_str(), FormLanguage->LangStr(STR_MSGBOX_ERROR).c_str(), MB_ICONSTOP );
         EditNev->SetFocus();
         return;
      }
   }
   pTermek->strLogMsg += AnsiString( stTemp.strVonalkod ) +
                         AnsiString( "/" ) +
                         AnsiString( stTemp.strNev ) +
                         AnsiString( "/" ) +
                         AnsiString( stTemp.nDarab ) +
                         AnsiString( "]" );
   pTermek->LOG2( pTermek->strLogMsg );

   BitBtnCancelClick(Sender);
   FillListTermekek( Sender );
   SelectTermekInList( stTemp.nID );
   StringGridTermek->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::BitBtnCancelClick(TObject *Sender)
{
   StringGridTermek->Enabled = true;
   StringGridTermek->SetFocus();

   EditNev->Enabled = false;
   EditVonalkod->Enabled = false;
   EditAr->Enabled = false;
   EditArBeszerzes->Enabled = false;
   EditDarab->Enabled = false;

   BitBtnSaveModify->Enabled = false;
   BitBtnCancel->Enabled = false;

   StringGridTermekClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::BitBtnOkClick(TObject *Sender)
{
   ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::BitBtnPlusClick(TObject *Sender)
{
   typ_termek  stTemp;

   memset( &stTemp, 0, sizeof(stTemp) );

   TStrings *Items = StringGridTermek->Rows[StringGridTermek->Row];
   if( !Items->Strings[0].IsEmpty() )
   {
      stTemp.nID = Items->Strings[0].ToDouble();
      strcpy( stTemp.strNev, Items->Strings[1].c_str() );
      strcpy( stTemp.strVonalkod, Items->Strings[2].c_str() );
      stTemp.nAr = convertCurrencyString(Items->Strings[3].c_str());
      stTemp.nArBeszerzes = convertCurrencyString(Items->Strings[4].c_str());
      stTemp.nDarab = Items->Strings[5].ToInt();
   }

   FormInputDialog->Caption = FormLanguage->LangStr(STR_MSG_PRODCOUNT_INCREASE);
   FormInputDialog->LabelText->Caption = FormLanguage->LangStr(STR_MSG_WITH_PIECES);
   FormInputDialog->EditText->Text = "";
   if( FormInputDialog->ShowModal() == mrOk )
   {
      try
      {
         stTemp.nDarab += FormInputDialog->EditText->Text.ToInt();
         pTermek->strLogMsg = AnsiString( "Termek darabszam noveles [" ) +
                              AnsiString( stTemp.strVonalkod ) +
                              AnsiString( "/" ) +
                              AnsiString( stTemp.strNev ) +
                              AnsiString( "/" ) +
                              AnsiString( stTemp.nDarab ) +
                              AnsiString( " (" ) +
                              AnsiString( FormInputDialog->EditText->Text ) +
                              AnsiString( ")]" );
         pTermek->LOG2( pTermek->strLogMsg );
         pTermek->ModifyTermek( stTemp );
         FillListTermekek( Sender );
         SelectTermekInList( stTemp.nID );
         StringGridTermek->SetFocus();
      }
      catch(const Exception& e)
      {
         Application->MessageBox( FormLanguage->LangStr(STR_MSG_USENUMBERONLY).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::BitBtnMinusClick(TObject *Sender)
{
   typ_termek  stTemp;

   memset( &stTemp, 0, sizeof(stTemp) );

   TStrings *Items = StringGridTermek->Rows[StringGridTermek->Row];
   if( !Items->Strings[0].IsEmpty() )
   {
      stTemp.nID = Items->Strings[0].ToDouble();
      strcpy( stTemp.strNev, Items->Strings[1].c_str() );
      strcpy( stTemp.strVonalkod, Items->Strings[2].c_str() );
      stTemp.nAr = convertCurrencyString(Items->Strings[3].c_str());
      stTemp.nArBeszerzes = convertCurrencyString(Items->Strings[4].c_str());
      stTemp.nDarab = Items->Strings[5].ToInt();
   }

   FormInputDialog->Caption = FormLanguage->LangStr(STR_MSG_PRODCOUNT_DECREASE);
   FormInputDialog->LabelText->Caption = FormLanguage->LangStr(STR_MSG_WITH_PIECES);
   FormInputDialog->EditText->Text = AnsiString( stTemp.nDarab );
   if( FormInputDialog->ShowModal() == mrOk )
   {
      try
      {
         stTemp.nDarab -= FormInputDialog->EditText->Text.ToInt();
         if( stTemp.nDarab < 0 )
            stTemp.nDarab = 0;
         pTermek->strLogMsg = AnsiString( "Termek darabszam csokkentes [" ) +
                              AnsiString( stTemp.strVonalkod ) +
                              AnsiString( "/" ) +
                              AnsiString( stTemp.strNev ) +
                              AnsiString( "/" ) +
                              AnsiString( stTemp.nDarab ) +
                              AnsiString( " (" ) +
                              AnsiString( FormInputDialog->EditText->Text ) +
                              AnsiString( ")]" );
         pTermek->LOG2( pTermek->strLogMsg );
         pTermek->ModifyTermek( stTemp );
         FillListTermekek( Sender );
         SelectTermekInList( stTemp.nID );
         StringGridTermek->SetFocus();
      }
      catch(const Exception& e)
      {
         Application->MessageBox( FormLanguage->LangStr(STR_MSG_USENUMBERONLY).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::EditVonalkodExit(TObject *Sender)
{
   if( EditVonalkod->Text.Length() < 5 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_BARCODE_TOOSHORT).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      BitBtnSaveModify->Enabled = false;
   }
   else
   {
      BitBtnSaveModify->Enabled = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::BitBtnAddClick(TObject *Sender)
{
   for( int i=0; i<ListBoxAll->Items->Count; )
   {
      if( ListBoxAll->Selected[i] )
      {
         ListBoxAssigned->Items->Add( ListBoxAll->Items->Strings[i] );
         ListBoxAll->Items->Delete( i );
      }
      else
      {
         i++;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekKezeles::BitBtnRemoveClick(TObject *Sender)
{
   for( int i=0; i<ListBoxAssigned->Items->Count; )
   {
      if( ListBoxAssigned->Selected[i] )
      {
         ListBoxAll->Items->Add( ListBoxAssigned->Items->Strings[i] );
         ListBoxAssigned->Items->Delete( i );
      }
      else
      {
         i++;
      }
   }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TermekTipusKezeles.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTermekTipus *FormTermekTipus;
//---------------------------------------------------------------------------
__fastcall TFormTermekTipus::TFormTermekTipus(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekTipus::FormActivate(TObject *Sender)
{
   StringGridTermekTipus->ColWidths[0] = 0;
   StringGridTermekTipus->ColWidths[1] = 325;
   StringGridTermekTipus->ColWidths[2] = 5;

   FillListTermekTipusok();

   ListBoxAssigned->Clear();
   ListBoxAll->Clear();
   for( int i=0; i<(int)pTermek->GetTermekCount(); i++ )
   {
      typ_termek              stTermek;

      stTermek = pTermek->GetTermekItem( i );
      ListBoxAll->Items->Add( stTermek.strNev );
   }

   StringGridTermekTipus->SetFocus();
   StringGridTermekTipusClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekTipus::FormShortCut(TWMKey &Msg, bool &Handled)
{
   if (Msg.CharCode == VK_RETURN)
   {
      Handled = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekTipus::BitBtnOkClick(TObject *Sender)
{
   ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void TFormTermekTipus::FillListTermekTipusok()
{
   int i;
   typ_termektipus   stTemp;

   for( i=0; i<StringGridTermekTipus->RowCount; i++ )
      StringGridTermekTipus->Rows[i]->Clear();

   if( pTermekTipus->GetTermekTipusCount() == 0 )
      StringGridTermekTipus->RowCount = 2;
   else
      StringGridTermekTipus->RowCount = pTermekTipus->GetTermekTipusCount()+1;
   StringGridTermekTipus->FixedRows = 1;
   StringGridTermekTipus->Cells[0][0] = "0";
   StringGridTermekTipus->Cells[1][0] = FormLanguage->LangStr(STR_NAME);
   StringGridTermekTipus->Cells[2][0] = "";

   for( i=0; i<(int)pTermekTipus->GetTermekTipusCount(); i++ )
   {
      stTemp = pTermekTipus->GetTermekTipusItem( i );

      StringGridTermekTipus->Cells[0][i+1] = AnsiString( stTemp.nID );
      StringGridTermekTipus->Cells[1][i+1] = AnsiString( stTemp.strNev );
      StringGridTermekTipus->Cells[2][i+1] = "";
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekTipus::StringGridTermekTipusClick(TObject *Sender)
{
   typ_termektipus   stTemp;

   memset( &stTemp, 0, sizeof(stTemp) );

   ButtonTTModify->Enabled = false;
   ButtonTTDelete->Enabled = false;

   TStrings *Items = StringGridTermekTipus->Rows[StringGridTermekTipus->Row];
   if( !Items->Strings[0].IsEmpty() )
   {
      stTemp = pTermekTipus->GetTermekTipusId( Items->Strings[0].ToDouble() );

      ButtonTTModify->Enabled = true;
      ButtonTTDelete->Enabled = true;

      ListBoxAssigned->Clear();
      ListBoxAll->Clear();
      for( int i=0; i<(int)pTermek->GetTermekCount(); i++ )
      {
         typ_termektipusassign   stAsg;
         typ_termek              stTermek;

         stTermek = pTermek->GetTermekItem( i );

         stAsg.nTermekID = stTermek.nID;
         stAsg.nTTipusID = stTemp.nID;

         if( pTermekTipus->CheckTermekTipusAsg( stAsg ) )
         {
            ListBoxAssigned->Items->Add( stTermek.strNev );
         }
         else
         {
            ListBoxAll->Items->Add( stTermek.strNev );
         }
      }
   }

   EditTTID->Text = AnsiString( stTemp.nID );
   EditTTNev->Text = AnsiString( stTemp.strNev );

   EditTTNev->Enabled = false;
   ListBoxAssigned->Enabled = false;
   BitBtnAdd->Enabled = false;
   BitBtnRemove->Enabled = false;
   ListBoxAll->Enabled = false;

   ButtonTTNew->Enabled = true;

   ButtonTTSave->Enabled = false;
   ButtonTTSave->Caption = FormLanguage->LangStr(STR_BTN_MODIFY);
   ButtonTTCancel->Enabled = false;

   BitBtnOk->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekTipus::ButtonTTNewClick(TObject *Sender)
{
   int i,j;
   typ_termektipus   stTemp;

   for( i=0, j=1; i<(int)pTermekTipus->GetTermekTipusCount(); i++, j++ )
   {
      stTemp = pTermekTipus->GetTermekTipusItem( i );
      if( j != (int)stTemp.nID )
      {
         break;
      }
   }
   EditTTID->Text = AnsiString( j );
   EditTTNev->Enabled = true;
   EditTTNev->Text = "";
   ListBoxAssigned->Enabled = true;
   BitBtnAdd->Enabled = true;
   BitBtnRemove->Enabled = true;
   ListBoxAll->Enabled = true;

   ListBoxAssigned->Clear();
   ListBoxAll->Clear();
   for( int i=0; i<(int)pTermek->GetTermekCount(); i++ )
   {
      typ_termek              stTermek;

      stTermek = pTermek->GetTermekItem( i );
      ListBoxAll->Items->Add( stTermek.strNev );
   }

   ButtonTTNew->Enabled = false;
   ButtonTTModify->Enabled = false;
   ButtonTTDelete->Enabled = false;

   ButtonTTSave->Enabled = true;
   ButtonTTSave->Caption = FormLanguage->LangStr(STR_BTN_SAVE);
   ButtonTTCancel->Enabled = true;

   EditTTNev->SetFocus();
   StringGridTermekTipus->Enabled = false;

   BitBtnOk->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekTipus::ButtonTTModifyClick(TObject *Sender)
{
   EditTTNev->Enabled = true;
   ListBoxAssigned->Enabled = true;
   BitBtnAdd->Enabled = true;
   BitBtnRemove->Enabled = true;
   ListBoxAll->Enabled = true;

   ButtonTTNew->Enabled = false;
   ButtonTTModify->Enabled = false;
   ButtonTTDelete->Enabled = false;

   ButtonTTSave->Enabled = true;
   ButtonTTSave->Caption = FormLanguage->LangStr(STR_BTN_MODIFY);
   ButtonTTCancel->Enabled = true;

   EditTTNev->SetFocus();
   StringGridTermekTipus->Enabled = false;

   BitBtnOk->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekTipus::ButtonTTDeleteClick(TObject *Sender)
{
   if( Application->MessageBox( FormLanguage->LangStr(STR_PRODUCTTYPE_DELETE_CONFIRM).c_str(),
                                FormLanguage->LangStr(STR_MSGBOX_QUESTION).c_str(),
                                MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 ) == IDYES )
   {
      TStrings *Items = StringGridTermekTipus->Rows[StringGridTermekTipus->Row];

      pTermekTipus->strLogMsg = AnsiString( "Termektipus torles [" ) +
                                AnsiString( Items->Strings[1] ) +
                                AnsiString( "]" );
      pTermekTipus->LOG2( pTermekTipus->strLogMsg );
      if( !pTermekTipus->DeleteTermekTipus( Items->Strings[0].ToInt() ) )
      {
         Application->MessageBox( FormLanguage->LangStr(STR_ERR_PRODUCTTYPE_NOTEXISTS).c_str(),
                                  FormLanguage->LangStr(STR_MSGBOX_ERROR).c_str(),
                                  MB_ICONSTOP );
      }
      FillListTermekTipusok();
      StringGridTermekTipus->SetFocus();
      StringGridTermekTipusClick(Sender);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekTipus::ButtonTTCancelClick(TObject *Sender)
{
   StringGridTermekTipus->Enabled = true;
   StringGridTermekTipus->SetFocus();

   StringGridTermekTipusClick(Sender);
}
//---------------------------------------------------------------------------
bool TFormTermekTipus::AdatEllenorzes()
{
   if( !EditTTNev->Text.Length() )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_ERR_PRODUCTTYPE_NAME_MISSING).c_str(),
                               FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                               MB_ICONEXCLAMATION );
      EditTTNev->SetFocus();
      return false;
   }

   typ_termektipus   stTemp;

   stTemp.nID = EditTTID->Text.ToInt();
   strncpy( stTemp.strNev, EditTTNev->Text.c_str(), sizeof(stTemp.strNev)-2 );

   DWORD nID = pTermekTipus->GetTermekTipusNev(stTemp.strNev);

   if( nID > 0 && nID != stTemp.nID )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_ERR_PRODUCTTYPE_NAME_EXISTS).c_str(),
                               FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                               MB_ICONEXCLAMATION );
      EditTTNev->SetFocus();
      return false;
   }

   return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekTipus::ButtonTTSaveClick(TObject *Sender)
{
   typ_termektipus   stTemp;

   if( !AdatEllenorzes() )
      return;

   try
   {
      stTemp.nID = EditTTID->Text.ToInt();
      strncpy( stTemp.strNev, EditTTNev->Text.c_str(), sizeof(stTemp.strNev)-2 );
   }
   catch(const Exception& e)
   {
      AnsiString eMessage = FormLanguage->LangStr(STR_MSG_USENUMBERONLY);
      Application->MessageBox( eMessage.c_str(), FormLanguage->LangStr(STR_MSGBOX_ERROR).c_str(), MB_ICONSTOP );
      return;
   }

   if( !ButtonTTSave->Caption.AnsiCompare( FormLanguage->LangStr(STR_BTN_SAVE) ) )
   {
      pTermekTipus->strLogMsg = AnsiString( "Uj termektipus felvetele [" );
      pTermekTipus->AddTermekTipus( stTemp );
      FillListTermekTipusok();
   }
   else if( !ButtonTTSave->Caption.AnsiCompare( FormLanguage->LangStr(STR_BTN_MODIFY) ) )
   {
      pTermekTipus->strLogMsg = AnsiString( "Termektipus modositasa [" );
      pTermekTipus->ModifyTermekTipus( stTemp );
      FillListTermekTipusok();
   }
   pTermekTipus->strLogMsg += AnsiString( stTemp.strNev ) +
                              AnsiString( "]" );
   pTermekTipus->LOG2( pTermekTipus->strLogMsg );

   typ_termektipusassign stAsg;

   stAsg.nTermekID = 0;
   stAsg.nTTipusID = stTemp.nID;
   pTermekTipus->DeleteTermekTipusAsg( stAsg );

   for( int i=0; i<ListBoxAssigned->Items->Count; i++ )
   {
      typ_termek stTermek = pTermek->GetTermekNev( ListBoxAssigned->Items->Strings[i].c_str() );

      stAsg.nTermekID = stTermek.nID;
      pTermekTipus->AddTermekTipusAsg( stAsg );
   }

   StringGridTermekTipus->Enabled = true;
   StringGridTermekTipus->SetFocus();
   for( int i=0; i<StringGridTermekTipus->RowCount; i++ )
   {
      TStrings *Items = StringGridTermekTipus->Rows[i];
      if( Items->Strings[0].ToDouble() == stTemp.nID )
      {
         StringGridTermekTipus->Row = i;
         StringGridTermekTipusClick(Sender);
         break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekTipus::BitBtnAddClick(TObject *Sender)
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
void __fastcall TFormTermekTipus::BitBtnRemoveClick(TObject *Sender)
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

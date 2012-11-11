//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TermekListaEladas.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTermekListaEladas *FormTermekListaEladas;
//---------------------------------------------------------------------------
__fastcall TFormTermekListaEladas::TFormTermekListaEladas(TComponent* Owner)
   : TForm(Owner)
{
   bFizetesEnabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekListaEladas::FormActivate(TObject *Sender)
{
   StringGridTermek->ColWidths[0] = 0;
   StringGridTermek->ColWidths[1] = 252;
   StringGridTermek->ColWidths[2] = 130;
   StringGridTermek->ColWidths[3] = 80;
   StringGridTermek->ColWidths[4] = 80;

   FillListTermekek( Sender );

   if( !bFizetesEnabled )
      BitBtnOk->Enabled = false;

   EditSearchNev->Text = "";
   EditSearchVonalkod->Text = "";
   EditSearchNev->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekListaEladas::FormShortCut(TWMKey &Msg, bool &Handled)
{
   if (Msg.CharCode == VK_RETURN)
   {
      Handled = true;
      if( BitBtnOk->Enabled )
      {
         ModalResult = mrOk;
      }
   }
}
//---------------------------------------------------------------------------
void TFormTermekListaEladas::FillListTermekek( TObject *Sender )
{
   int i;
   typ_termek   stTemp;

   for( i=0; i<StringGridTermek->RowCount; i++ )
      StringGridTermek->Rows[0]->Clear();

   if( pTermek->GetTermekCount() == 0 )
   {
      StringGridTermek->RowCount = 2;
      BitBtnOk->Enabled = false;
      BitBtnKosar->Enabled = false;
   }
   else
   {
      StringGridTermek->RowCount = pTermek->GetTermekCount()+1;
      BitBtnOk->Enabled = true;
      BitBtnKosar->Enabled = true;
   }
   StringGridTermek->FixedRows = 1;
   StringGridTermek->Cells[0][0] = "0";
   StringGridTermek->Cells[1][0] = FormLanguage->LangStr(STR_PRODUCT);
   StringGridTermek->Cells[2][0] = FormLanguage->LangStr(STR_BARCODE);
   StringGridTermek->Cells[3][0] = FormLanguage->LangStr(STR_UNITPRICE);
   StringGridTermek->Cells[4][0] = FormLanguage->LangStr(STR_STOCK);

   for( i=0; i<(int)pTermek->GetTermekCount(); i++ )
   {
      stTemp = pTermek->GetTermekItem( i );

      StringGridTermek->Cells[0][i+1] = AnsiString( stTemp.nID );
      StringGridTermek->Cells[1][i+1] = AnsiString( stTemp.strNev );
      StringGridTermek->Cells[2][i+1] = AnsiString( stTemp.strVonalkod );
      StringGridTermek->Cells[3][i+1] = convertToCurrencyString( stTemp.nAr );
      StringGridTermek->Cells[4][i+1] = AnsiString( stTemp.nDarab );
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
void __fastcall TFormTermekListaEladas::StringGridTermekClick(TObject *Sender)
{
   memset( &stTermek, 0, sizeof(stTermek) );

   TStrings *Items = StringGridTermek->Rows[StringGridTermek->Row];
   if( !Items->Strings[0].IsEmpty() )
   {
      stTermek.nID = Items->Strings[0].ToDouble();
      strcpy( stTermek.strNev, Items->Strings[1].c_str() );
      strcpy( stTermek.strVonalkod, Items->Strings[2].c_str() );
      stTermek.nAr = convertCurrency(Items->Strings[3].ToDouble());
      stTermek.nDarab = Items->Strings[4].ToInt();

      EditID->Text = AnsiString( stTermek.nID );
      EditNev->Text = AnsiString( stTermek.strNev );
      EditVonalkod->Text = AnsiString( stTermek.strVonalkod );
      EditAr->Text = convertToCurrencyString( stTermek.nAr );
      EditDarab->Text = AnsiString( stTermek.nDarab );

      ComboBoxDarab->Clear();
      for( int i=0; i<stTermek.nDarab; i++ )
      {
         ComboBoxDarab->Items->Add( AnsiString(i+1) );
      }
      if( stTermek.nDarab == 0 )
      {
         BitBtnOk->Enabled = false;
         BitBtnKosar->Enabled = false;
      }
      else if( stTermek.nDarab > 0 )
      {
         BitBtnOk->Enabled = true;
         BitBtnKosar->Enabled = true;
      }
      ComboBoxDarab->ItemIndex = 0;
      EditFizetendo->Text = convertToCurrencyString( stTermek.nAr );
   }
   if( !bFizetesEnabled )
      BitBtnOk->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekListaEladas::EditSearchNevChange(TObject *Sender)
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
void __fastcall TFormTermekListaEladas::EditSearchVonalkodChange(TObject *Sender)
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
void TFormTermekListaEladas::SortListTermekek( int nCell )
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
            stTemp.nAr = convertCurrency(Items->Strings[3].ToDouble());
            stTemp.nDarab = Items->Strings[4].ToInt();

            StringGridTermek->Cells[0][j] = ItemsBubble->Strings[0];
            StringGridTermek->Cells[1][j] = ItemsBubble->Strings[1];
            StringGridTermek->Cells[2][j] = ItemsBubble->Strings[2];
            StringGridTermek->Cells[3][j] = ItemsBubble->Strings[3];
            StringGridTermek->Cells[4][j] = ItemsBubble->Strings[4];

            StringGridTermek->Cells[0][j+1] = AnsiString( stTemp.nID );
            StringGridTermek->Cells[1][j+1] = AnsiString( stTemp.strNev );
            StringGridTermek->Cells[2][j+1] = AnsiString( stTemp.strVonalkod );
            StringGridTermek->Cells[3][j+1] = convertToCurrencyString( stTemp.nAr );
            StringGridTermek->Cells[4][j+1] = AnsiString( stTemp.nDarab );
         }
         j--;
      } while( j>0 && bCsere);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekListaEladas::ComboBoxDarabChange(TObject *Sender)
{
   int nDarab = ComboBoxDarab->Items->Strings[ComboBoxDarab->ItemIndex].ToInt();
   int nAr = stTermek.nAr;

   EditFizetendo->Text = convertToCurrencyString( nDarab*nAr );
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekListaEladas::BitBtnSortNameClick(TObject *Sender)
{
   BitBtnSortName->Enabled = false;
   BitBtnSortCode->Enabled = true;
   SortListTermekek( 1 );
   StringGridTermek->Row = 1;
   StringGridTermekClick(Sender);
   EditSearchNev->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormTermekListaEladas::BitBtnSortCodeClick(TObject *Sender)
{
   BitBtnSortName->Enabled = true;
   BitBtnSortCode->Enabled = false;
   SortListTermekek( 2 );
   StringGridTermek->Row = 1;
   StringGridTermekClick(Sender);
   EditSearchVonalkod->SetFocus();
}
//---------------------------------------------------------------------------

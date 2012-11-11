//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Kosar.h"
#include "BerletEladas.h"
#include "TermekListaEladas.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormKosar *FormKosar;
//---------------------------------------------------------------------------
__fastcall TFormKosar::TFormKosar(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormKosar::FormActivate(TObject *Sender)
{
   KosarTipus[0] = FormLanguage->LangStr(STR_CARD).c_str();
   KosarTipus[1] = FormLanguage->LangStr(STR_PRODUCT).c_str();
   KosarTipus[2] = FormLanguage->LangStr(STR_SOLARIUM).c_str();

   StringGridKosar->ColWidths[0] = 0;
   StringGridKosar->ColWidths[1] = 90;
   StringGridKosar->ColWidths[2] = 250;
   StringGridKosar->ColWidths[3] = 80;
   StringGridKosar->ColWidths[4] = 90;

   FillListKosar( Sender );
   StringGridKosar->SetFocus();
   StringGridKosarClick(Sender);
}
//---------------------------------------------------------------------------
void TFormKosar::FillListKosar( TObject *Sender )
{
   int i;
   typ_kosar   stTemp;

   for( i=0; i<StringGridKosar->RowCount; i++ )
      StringGridKosar->Rows[i]->Clear();

   if( pKosar->GetKosarCount() == 0 )
      StringGridKosar->RowCount = 2;
   else
      StringGridKosar->RowCount = pKosar->GetKosarCount()+1;
   StringGridKosar->FixedRows = 1;
   StringGridKosar->Cells[0][0] = "0";
   StringGridKosar->Cells[1][0] = FormLanguage->LangStr(STR_PRODUCT);
   StringGridKosar->Cells[2][0] = FormLanguage->LangStr(STR_DESIGNATION);
   StringGridKosar->Cells[3][0] = FormLanguage->LangStr(STR_UNITPRICE);
   StringGridKosar->Cells[4][0] = FormLanguage->LangStr(STR_COUNTOF);

   for( i=0; i<(int)pKosar->GetKosarCount(); i++ )
   {
      stTemp = pKosar->GetKosar( i );

      StringGridKosar->Cells[0][i+1] = AnsiString( stTemp.nID );
      StringGridKosar->Cells[1][i+1] = KosarTipus[stTemp.nTipus];
      StringGridKosar->Cells[2][i+1] = AnsiString( stTemp.strNev );
      StringGridKosar->Cells[3][i+1] = convertToCurrencyString( stTemp.nAr );
      StringGridKosar->Cells[4][i+1] = AnsiString( stTemp.nDarab );
   }
   StringGridKosar->Row = 1;
   StringGridKosarClick(Sender);
   LabelFizetendo->Caption = AnsiString( pKosar->GetKosarAr()/100 );
   if( pKosar->GetKosarAr() > 0 )
   {
      BitBtnFizetes->Enabled = true;
   }
   else
   {
      BitBtnFizetes->Enabled = false;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormKosar::StringGridKosarClick(TObject *Sender)
{
   TStrings *Items = StringGridKosar->Rows[StringGridKosar->Row];
   if( !Items->Strings[0].IsEmpty() )
   {
      BitBtnDelete->Enabled = true;
   }
}
//---------------------------------------------------------------------------
// Bérlet / Termék törlése a kosárból
//---------------------------------------------------------------------------
void __fastcall TFormKosar::BitBtnDeleteClick(TObject *Sender)
{
   // Kiválasztott elem adatainak kinyerése
   TStrings *Items = StringGridKosar->Rows[StringGridKosar->Row];
   if( !Items->Strings[0].IsEmpty() )
   {
      // Bérlet / Termék kiválasztva törlésre
      // A kiválasztott elem adatainak kinyerése
      typ_kosar stTemp = pKosar->GetKosarID( Items->Strings[0].ToInt() );
      switch( stTemp.nTipus )
      {
         case 0:
            // A kiválasztott elem egy eladásra kosárba felvett bérlet
            // Törlés az eladott bérletek adatbázisából
            pBerletek->DeleteBerlet( stTemp.strVonalkod );
            break;

         case 1:
         {
            // A kiválasztott elem egy eladásra kosárba felvett termék
            // Termék adatainak kinyerése
            typ_termek stTermek = pTermek->GetTermekKod( stTemp.strVonalkod );
            // Termék darabszám visszanövelése adott mennyiséggel
            pTermek->SetTermekDarab( stTermek.nID,
                                     pTermek->GetTermekDarab( stTermek.nID ) + stTemp.nDarab );
            break;
         }
         case 2:
            // A kiválasztott elem egy szolárium használat
            Application->MessageBox( FormLanguage->LangStr(STR_MSG_USESOL_DELETE_DENIED).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
            return;
      }
      // Kiválasztott elem törlése a kosárból
      pKosar->DeleteKosar( Items->Strings[0].ToInt() );
   }
   FillListKosar( Sender );
   StringGridKosar->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormKosar::BitBtnBerletAddClick(TObject *Sender)
{
   if( pBerletek->GetBerletTipusCount() == 0 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_CARD_NOTEXISTS).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      return;
   }
   FormBerletEladas->pBerlet = pBerletek;
   FormBerletEladas->pTermek = pTermek;
   FormBerletEladas->pMainSettings = pMainSettings;
   FormBerletEladas->BitBtnOk->Enabled = false;
   if( FormBerletEladas->ShowModal() == mrYes )
   {
      typ_kosar stKosar;

      memset( &stKosar, 0, sizeof(typ_kosar) );

      stKosar.nID = pKosar->GetKosarCount()+1;
      strncpy( stKosar.strVonalkod, FormBerletEladas->EditVonalkod->Text.c_str(), sizeof(stKosar.strVonalkod)-2 );
      stKosar.nTipus = 0;
      strcpy( stKosar.strNev, FormBerletEladas->ComboBoxTipus->Items->Strings[FormBerletEladas->ComboBoxTipus->ItemIndex].c_str() );
      stKosar.nAr = convertCurrency(FormBerletEladas->EditBTAr->Text.ToDouble());
      stKosar.nDarab = 1;

      pKosar->AddKosar( stKosar );
      FillListKosar( Sender );
      StringGridKosar->SetFocus();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormKosar::BitBtnTermekAddClick(TObject *Sender)
{
   FormTermekListaEladas->pTermek = pTermek;
   FormTermekListaEladas->bFizetesEnabled = false;
   if( FormTermekListaEladas->ShowModal() == mrYes )
   {
      typ_kosar stKosar;

      memset( &stKosar, 0, sizeof(typ_kosar) );

      // Egyedi azonosító kiszámolása
      stKosar.nID = pKosar->GetKosarCount()+1;
      // Kosárelem típusa: 1 -> termék
      stKosar.nTipus = 1;
      // Adatok átadása a Termékeladás ablakból a kosárnak
      strncpy( stKosar.strVonalkod, FormTermekListaEladas->EditVonalkod->Text.c_str(), sizeof(stKosar.strVonalkod)-2 );
      strncpy( stKosar.strNev, FormTermekListaEladas->EditNev->Text.c_str(), sizeof(stKosar.strNev)-2 );
      stKosar.nAr = convertCurrency(FormTermekListaEladas->EditAr->Text.ToDouble());
      stKosar.nDarab = FormTermekListaEladas->ComboBoxDarab->Items->Strings[FormTermekListaEladas->ComboBoxDarab->ItemIndex].ToInt();
      // Termék felvétele a kosárba
      pKosar->AddKosar( stKosar );

      DWORD nID = FormTermekListaEladas->EditID->Text.ToDouble();
      int nDarab = FormTermekListaEladas->ComboBoxDarab->Items->Strings[FormTermekListaEladas->ComboBoxDarab->ItemIndex].ToInt();
      int nCurrDarab = pTermek->GetTermekDarab( nID );

      pTermek->SetTermekDarab( nID, nCurrDarab-nDarab );

      FillListKosar( Sender );
      StringGridKosar->SetFocus();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormKosar::FormShortCut(TWMKey &Msg, bool &Handled)
{
   if (Msg.CharCode == VK_RETURN)
   {
      Handled = true;
      if( BitBtnFizetes->Enabled )
      {
         ModalResult = mrOk;
      }
   }
}
//---------------------------------------------------------------------------


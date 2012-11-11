//---------------------------------------------------------------------------

#include <vcl.h>
#include <string.h>
#pragma hdrstop

#include "BerletEladas.h"
#include "BerletPin.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormBerletEladas *FormBerletEladas;
//---------------------------------------------------------------------------
__fastcall TFormBerletEladas::TFormBerletEladas(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormBerletEladas::FormActivate(TObject *Sender)
{
   EditVonalkod->Text = "";
   EditMegjegyzes->Text = "";

   FillListBerletTipusok();
   ComboBoxTipus->ItemIndex = 0;
   ComboBoxTipusChange(Sender);

   EditVonalkod->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormBerletEladas::FormShortCut(TWMKey &Msg, bool &Handled)
{
   if (Msg.CharCode == VK_RETURN)
   {
      Handled = true;
   }
}
//---------------------------------------------------------------------------
void TFormBerletEladas::FillListBerletTipusok()
{
   typ_berlettipus   stTemp;

   ComboBoxTipus->Clear();
   for(int i=0;i<pBerlet->GetBerletTipusCount();i++)
   {
      stTemp = pBerlet->GetBerletTipus( i );
      ComboBoxTipus->Items->Add( AnsiString(stTemp.strNev) );
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormBerletEladas::ComboBoxTipusChange(TObject *Sender)
{
   typ_berlettipus   stTemp;

   stTemp = pBerlet->GetBerletTipus( ComboBoxTipus->Items->Strings[ComboBoxTipus->ItemIndex].c_str() );
   EditBTEgyseg->Text = AnsiString( stTemp.nEgyseg );
   EditBTID->Text = AnsiString( stTemp.nID );
   if( stTemp.nErvTolEv == 0 )
      EditBTErvTolEv->Text = FormatDateTime("yyyy",Now());
   else
      EditBTErvTolEv->Text = AnsiString( stTemp.nErvTolEv );

   if( stTemp.nErvTolHo == 0 )
      EditBTErvTolHo->Text = FormatDateTime("mm",Now());
   else
      EditBTErvTolHo->Text = AnsiString( stTemp.nErvTolHo );

   if( stTemp.nErvTolNap == 0 )
      EditBTErvTolNap->Text = FormatDateTime("dd",Now());
   else
      EditBTErvTolNap->Text = AnsiString( stTemp.nErvTolNap );

   if( stTemp.nErvIgEv == 0 )
      EditBTErvIgEv->Text = FormatDateTime("yyyy",Now()+stTemp.nErvNapok);
   else
      EditBTErvIgEv->Text = AnsiString( stTemp.nErvIgEv );

   if( stTemp.nErvIgHo == 0 )
      EditBTErvIgHo->Text = FormatDateTime("mm",Now()+stTemp.nErvNapok);
   else
      EditBTErvIgHo->Text = AnsiString( stTemp.nErvIgHo );

   if( stTemp.nErvIgNap == 0 )
      EditBTErvIgNap->Text = FormatDateTime("dd",Now()+stTemp.nErvNapok);
   else
      EditBTErvIgNap->Text = AnsiString( stTemp.nErvIgNap );

   EditBTAr->Text = convertToCurrencyString( stTemp.nAr );
}
//---------------------------------------------------------------------------
void TFormBerletEladas::BerletAdatbazisba()
{
   typ_berlet   stTemp;

   // Bérlet mentése az adatok közé
   strncpy( stTemp.strVonalkod, EditVonalkod->Text.c_str(), sizeof(stTemp.strVonalkod)-2 );
   strncpy( stTemp.strMegjegyzes, EditMegjegyzes->Text.c_str(), sizeof(stTemp.strMegjegyzes)-2 );
   stTemp.nBerletTipus = EditBTID->Text.ToInt();
   stTemp.nEgyseg = EditBTEgyseg->Text.ToInt();
   stTemp.nErvEv = EditBTErvIgEv->Text.ToInt();
   stTemp.nErvHo = EditBTErvIgHo->Text.ToInt();
   stTemp.nErvNap = EditBTErvIgNap->Text.ToInt();
   if( pMainSettings->GetBoolValueFromRegistry( "IsPINCodeNeeded", false ) )
   {
      FormBerletPIN->ShowModal();
      stTemp.nPin = FormBerletPIN->EditPIN->Text.ToInt();
   }
   else
   {
      stTemp.nPin = 0;
   }
   pBerlet->strLogMsg = AnsiString( "Berlet eladas kp fizetessel [" ) +
                        AnsiString( stTemp.strVonalkod ) +
                        AnsiString( "]" );
   pBerlet->AddBerlet( stTemp );
}
//---------------------------------------------------------------------------
void __fastcall TFormBerletEladas::BitBtnOkClick(TObject *Sender)
{
   if( VonalkodEllenorzes() )
   {
      BerletAdatbazisba();
      pBerlet->LOG2( pBerlet->strLogMsg );
      ModalResult = mrOk;
   }
   else
   {
      ModalResult = mrNone;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormBerletEladas::BitBtnKosarClick(TObject *Sender)
{
   if( VonalkodEllenorzes() )
   {
      BerletAdatbazisba();
      ModalResult = mrYes;
   }
   else
   {
      ModalResult = mrNone;
   }
}
//---------------------------------------------------------------------------
bool TFormBerletEladas::VonalkodEllenorzes()
{
   bool bRet = false;

   if( EditVonalkod->Text.Length() == 0 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_MISSING_BARCODE).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      EditVonalkod->SetFocus();
   }
   else
   {
      typ_berlet stBerlet = pBerlet->GetBerlet( EditVonalkod->Text.c_str() );

      if( stBerlet.nBerletTipus != 0 )
      {
         Application->MessageBox( FormLanguage->LangStr(STR_MSG_BARCODE_CARD_EXISTS).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
         EditVonalkod->SetFocus();
      }
      else
      {
         // vonalkód keresése a termékeknél, hiba, ha megtalálta
         typ_termek stTermek = pTermek->GetTermekKod( EditVonalkod->Text.c_str() );
         if( strcmp(stTermek.strVonalkod,EditVonalkod->Text.c_str()) == 0 )
         {
            AnsiString  strMessage;
            strMessage.sprintf( FormLanguage->LangStr(STR_MSG_BARCODE_PROD_EXISTS).c_str(), stTermek.strNev );
            Application->MessageBox( strMessage.c_str(),
                                     FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                                     MB_ICONEXCLAMATION );
            EditVonalkod->SetFocus();
         }
         else
         {
            bRet = true;
         }
      }
   }
   return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TFormBerletEladas::EditVonalkodExit(TObject *Sender)
{
   if( EditVonalkod->Text.Length() < 4 && EditVonalkod->Text.Length() > 0 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_BARCODE_TOOSHORT).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      BitBtnOk->Enabled = false;
      BitBtnKosar->Enabled = false;
   }
   else
   {
      BitBtnOk->Enabled = true;
      BitBtnKosar->Enabled = true;
   }
}
//---------------------------------------------------------------------------


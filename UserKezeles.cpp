//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <string.h>

#include "UserKezeles.h"
#include "PasswordChange.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormUserKezeles *FormUserKezeles;
//---------------------------------------------------------------------------
__fastcall TFormUserKezeles::TFormUserKezeles(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormUserKezeles::FormActivate(TObject *Sender)
{
   StringGridUser->ColWidths[0] = 0;
   StringGridUser->ColWidths[1] = 390;
   StringGridUser->ColWidths[2] = 150;

   FillListUserek( Sender );
   StringGridUser->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormUserKezeles::FormShortCut(TWMKey &Msg, bool &Handled)
{
   if (Msg.CharCode == VK_RETURN)
   {
      Handled = true;
   }
}
//---------------------------------------------------------------------------
void TFormUserKezeles::FillListUserek( TObject *Sender )
{
   int i;
   typ_user stTemp;

   for( i=0; i<StringGridUser->RowCount; i++ )
      StringGridUser->Rows[i]->Clear();

   if( pUser->GetUserCount() == 0 )
      StringGridUser->RowCount = 2;
   else
      StringGridUser->RowCount = pUser->GetUserCount();
   StringGridUser->FixedRows = 1;
   StringGridUser->Cells[0][0] = FormLanguage->LangStr(STR_IDENTIFIER);
   StringGridUser->Cells[1][0] = FormLanguage->LangStr(STR_USER_NAME);
   StringGridUser->Cells[2][0] = FormLanguage->LangStr(STR_LOGIN_NAME);

   for( i=1; i<(int)pUser->GetUserCount(); i++ )
   {
      stTemp = pUser->GetUserItem( i );

      StringGridUser->Cells[0][i] = AnsiString( stTemp.strAzonosito );
      StringGridUser->Cells[1][i] = AnsiString( stTemp.strNevCsalad );
      StringGridUser->Cells[2][i] = AnsiString( stTemp.strLoginNev );
   }
   StringGridUser->Row = 1;
   StringGridUserClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormUserKezeles::StringGridUserClick(TObject *Sender)
{
   typ_user  stTemp;

   memset( &stTemp, 0, sizeof(stTemp) );

   TStrings *Items = StringGridUser->Rows[StringGridUser->Row];
   if( !Items->Strings[2].IsEmpty() )
   {
      stTemp = pUser->GetUserLogin( Items->Strings[2].c_str() );

      if( strcmp( stTemp.strAzonosito, "Admin" ) == 0 ||
          strcmp( stTemp.strAzonosito, "User" ) == 0 )
      {
         BitBtnModify->Enabled = false;
         BitBtnDelete->Enabled = false;
         EditPassword->PasswordChar = 0;
      }
      else
      {
         BitBtnModify->Enabled = true;
         if( strcmp(pMainSettings->GetCurrentUser(),stTemp.strLoginNev) == 0 )
         {
            BitBtnDelete->Enabled = false;
         }
         else
         {
            BitBtnDelete->Enabled = true;
         }
         EditPassword->PasswordChar = '*';
      }
      BitBtnPassword->Enabled = true;
   }

   BitBtnNew->Enabled = true;
   EditNev->Enabled = false;
   //EditAzonosito->Enabled = false;
   EditLogin->Enabled = false;
   ComboBoxUserGroup->Enabled = false;
   MemoMegjegyzes->Enabled = false;
   BitBtnOk->Enabled = true;

   EditID->Text         = AnsiString( stTemp.dID );
   EditPassword->Text   = AnsiString( stTemp.strJelszo );
   EditNev->Text        = AnsiString( stTemp.strNevCsalad );
   //EditAzonosito->Text  = AnsiString( stTemp.strAzonosito );
   EditLogin->Text      = AnsiString( stTemp.strLoginNev );
   MemoMegjegyzes->Text = AnsiString( stTemp.strMegjegyzes );
   switch( stTemp.nUserLevel )
   {
      case ACCESS_ROOT:
         ComboBoxUserGroup->ItemIndex = 1;
         break;

      case ACCESS_ADMIN:
         ComboBoxUserGroup->ItemIndex = 1;
         break;

      case ACCESS_USER:
         ComboBoxUserGroup->ItemIndex = 0;
         break;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormUserKezeles::BitBtnNewClick(TObject *Sender)
{
   EditNev->Enabled = true;
   //EditAzonosito->Enabled = true;
   EditLogin->Enabled = true;
   ComboBoxUserGroup->Enabled = true;
   MemoMegjegyzes->Enabled = true;

   EditID->Text         = "0";
   EditNev->Text        = "";
   //EditAzonosito->Text  = "";
   EditLogin->Text      = "";
   MemoMegjegyzes->Text = "";

   BitBtnSaveModify->Enabled = true;
   BitBtnSaveModify->Caption = FormLanguage->LangStr(STR_BTN_SAVE);
   BitBtnCancel->Enabled = true;

   EditNev->SetFocus();

   StringGridUser->Enabled = false;
   StringGridUser->Color = clBtnFace;
   BitBtnNew->Enabled = false;
   BitBtnModify->Enabled = false;
   BitBtnDelete->Enabled = false;
   BitBtnPassword->Enabled = false;
   BitBtnOk->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormUserKezeles::BitBtnModifyClick(TObject *Sender)
{
   EditNev->Enabled = true;
   //EditAzonosito->Enabled = true;
   EditLogin->Enabled = false;
   ComboBoxUserGroup->Enabled = true;
   MemoMegjegyzes->Enabled = true;

   BitBtnSaveModify->Enabled = true;
   BitBtnSaveModify->Caption = FormLanguage->LangStr(STR_BTN_MODIFY);
   BitBtnCancel->Enabled = true;

   EditNev->SetFocus();
   StringGridUser->Enabled = false;
   StringGridUser->Color = clBtnFace;
   BitBtnNew->Enabled = false;
   BitBtnModify->Enabled = false;
   BitBtnDelete->Enabled = false;
   BitBtnPassword->Enabled = false;
   BitBtnOk->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormUserKezeles::BitBtnDeleteClick(TObject *Sender)
{
   if( Application->MessageBox( FormLanguage->LangStr(STR_USERDELETE_CONFIRM).c_str(),
                                FormLanguage->LangStr(STR_MSGBOX_QUESTION).c_str(),
                                MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 ) == IDYES )
   {
      TStrings *Items = StringGridUser->Rows[StringGridUser->Row];

      BitBtnModify->Enabled = false;
      BitBtnDelete->Enabled = false;

      pUser->strLogMsg = AnsiString( "Felhasznalo torlese: [" ) +
                         AnsiString( Items->Strings[2] ) +
                         AnsiString( "]" );
      pUser->LOG2( pUser->strLogMsg );
      pUser->DeleteUser( Items->Strings[2].c_str() );
      FillListUserek( Sender );
      StringGridUser->SetFocus();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormUserKezeles::BitBtnPasswordClick(TObject *Sender)
{
   FormPasswordChange->Caption = FormLanguage->LangStr(STR_USERPASS_MODIFY);
   FormPasswordChange->EditOldPassword->Text = EditPassword->Text;
   if( FormPasswordChange->ShowModal() == mrOk )
   {
      typ_user stTemp = pUser->GetUserLogin( EditLogin->Text.c_str() );
      strncpy( stTemp.strJelszo, FormPasswordChange->Edit2->Text.c_str(), sizeof(stTemp.strJelszo)-2 );
      pUser->strLogMsg = AnsiString( "Felhasznalo jelszovaltoztatas: [" ) +
                         AnsiString( stTemp.strLoginNev ) +
                         AnsiString( "]" );
      pUser->LOG2( pUser->strLogMsg );
      pUser->ModifyUser( stTemp );
      if( strcmp( stTemp.strLoginNev, FormLanguage->LangStr(STR_ADMINISTRATOR).c_str() ) == 0 )
      {
         pMainSettings->ModifyPassword( ACCESS_ADMIN, FormPasswordChange->Edit2->Text.c_str() );
      }
      else if( strcmp( stTemp.strLoginNev, FormLanguage->LangStr(STR_OPERATOR).c_str() ) == 0 )
      {
         pMainSettings->ModifyPassword( ACCESS_USER, FormPasswordChange->Edit2->Text.c_str() );
      }

      StringGridUserClick(Sender);
      StringGridUser->SetFocus();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormUserKezeles::BitBtnPasswordResetClick(TObject *Sender)
{
   typ_user stTemp = pUser->GetUserLogin( EditLogin->Text.c_str() );
   strcpy( stTemp.strJelszo, "" );
   pUser->ModifyUser( stTemp );
   StringGridUserClick(Sender);
   StringGridUser->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormUserKezeles::BitBtnSaveModifyClick(TObject *Sender)
{
   typ_user  stTemp;

   memset( &stTemp, 0, sizeof(stTemp) );

   if( EditNev->Text.Length() == 0 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_USERNAME_MISSING).c_str(),
                               FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                               MB_ICONEXCLAMATION );
      EditNev->SetFocus();
      return;
   }
   if( EditLogin->Text.Length() == 0 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_LOGINNAME_MISSING).c_str(),
                               FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                               MB_ICONEXCLAMATION );
      EditLogin->SetFocus();
      return;
   }
   else
   {
      stTemp = pUser->GetUserLogin( EditLogin->Text.c_str() );
      if( stTemp.dID != EditID->Text.ToDouble() && stTemp.dID )
      {
         AnsiString  strMessage;
         strMessage.sprintf( FormLanguage->LangStr(STR_MSG_LOGINNAME_INUSE).c_str(), stTemp.strNevCsalad );
         Application->MessageBox( strMessage.c_str(),
                                  FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                                  MB_ICONEXCLAMATION );
         EditLogin->SetFocus();
         return;
      }
   }

   strncpy( stTemp.strLoginNev,   EditLogin->Text.c_str(), sizeof(stTemp.strLoginNev)-2 );
   strncpy( stTemp.strNevCsalad,  EditNev->Text.c_str(), sizeof(stTemp.strNevCsalad)-2 );
   strncpy( stTemp.strMegjegyzes, MemoMegjegyzes->Text.c_str(), sizeof(stTemp.strMegjegyzes)-2 );
   strncpy( stTemp.strJelszo,     EditPassword->Text.c_str(), sizeof(stTemp.strJelszo)-2 );

   if( ComboBoxUserGroup->Text.AnsiCompare( FormLanguage->LangStr(STR_OPERATOR) ) == 0 )
      stTemp.nUserLevel = ACCESS_USER;
   else if( ComboBoxUserGroup->Text.AnsiCompare( FormLanguage->LangStr(STR_ADMINISTRATOR) ) == 0 )
      stTemp.nUserLevel = ACCESS_ADMIN;
   else
      stTemp.nUserLevel = ACCESS_USER;

   if( BitBtnSaveModify->Caption.AnsiCompare(FormLanguage->LangStr(STR_BTN_SAVE)) == 0 )
   {
      pUser->strLogMsg = AnsiString( "Uj felhasznalo felvetele: [" );
      memset( stTemp.strJelszo, 0, sizeof(stTemp.strJelszo) );
      pUser->AddUser( stTemp );
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_USERSAVED_PASSEMPTY).c_str(),
                               FormLanguage->LangStr(STR_MSGBOX_INFORMATION).c_str(),
                               MB_ICONINFORMATION );
   }
   else if( BitBtnSaveModify->Caption.AnsiCompare(FormLanguage->LangStr(STR_BTN_MODIFY)) == 0 )
   {
      pUser->strLogMsg = AnsiString( "Felhasznalo modositasa: [" );
      if( !pUser->ModifyUser( stTemp ) )
      {
         Application->MessageBox( FormLanguage->LangStr(STR_MSG_USER_NOTEXISTS).c_str(),
                                  FormLanguage->LangStr(STR_MSGBOX_ERROR).c_str(),
                                  MB_ICONSTOP );
         EditNev->SetFocus();
         return;
      }
   }
   pUser->strLogMsg += AnsiString( stTemp.strLoginNev ) +
                       AnsiString( "]" );
   pUser->LOG2( pUser->strLogMsg );

   BitBtnCancelClick(Sender);
   FillListUserek( Sender );
   StringGridUser->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormUserKezeles::BitBtnCancelClick(TObject *Sender)
{
   StringGridUser->Enabled = true;
   StringGridUser->Color = clWindow;
   StringGridUser->SetFocus();

   EditNev->Enabled = false;
   //EditAzonosito->Enabled = false;
   EditLogin->Enabled = false;
   ComboBoxUserGroup->Enabled = false;
   MemoMegjegyzes->Enabled = false;

   BitBtnSaveModify->Enabled = false;
   BitBtnCancel->Enabled = false;

   StringGridUserClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormUserKezeles::BitBtnOkClick(TObject *Sender)
{
   LabelPassword->Visible = false;
   EditPassword->Visible = false;
   BitBtnPasswordReset->Visible = false;
   BitBtnPasswordReset->Enabled = false;
   ModalResult = mrOk;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PasswordCheck.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPasswordCheck *FormPasswordCheck;
//---------------------------------------------------------------------------
__fastcall TFormPasswordCheck::TFormPasswordCheck(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormPasswordCheck::FormActivate(TObject *Sender)
{
   EditUserNev->Clear();
   for( double i=1; i<pUser->GetUserCount(); i++ )
   {
      typ_user stUser;
      stUser = pUser->GetUserItem( i );
      EditUserNev->Items->Add( AnsiString(stUser.strLoginNev) );
   }
   EditUserNev->Text = EditCurrentUser->Text;

   EditPassword->Text = "";
   EditPassword->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormPasswordCheck::BitBtnOkClick(TObject *Sender)
{
   typ_user stUser;

   memset( &stUser, 0, sizeof(typ_user) );

   stUser = pUser->GetUserLogin( EditUserNev->Text.c_str() );
   if( strlen( stUser.strLoginNev ) == 0 )
   {
      Application->MessageBox( FormLanguage->LangStr(STR_MSG_LOGINNAME_NOTEXISTS).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
      EditUserNev->SetFocus();
      ModalResult = mrNone;
   }
   else
   {
      if( strcmp(stUser.strJelszo,EditPassword->Text.c_str()) != 0 )
      {
         Application->MessageBox( FormLanguage->LangStr(STR_MSG_INVALID_PASSWORD).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONEXCLAMATION );
         EditPassword->SetFocus();
         ModalResult = mrNone;
      }
      else if( stUser.nUserLevel < AccessLevel )
      {
         Application->MessageBox( FormLanguage->LangStr(STR_MSG_ACCESS_DENIED).c_str(), FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(), MB_ICONSTOP );
         ModalResult = mrCancel;
      }
      else
      {
         ModalResult = mrOk;
      }
   }
}
//---------------------------------------------------------------------------

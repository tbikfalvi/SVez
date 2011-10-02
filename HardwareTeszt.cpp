//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HardwareTeszt.h"
#include "HW_COMMAND.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const WORD run_rel[] = { R1, R2, R3, R4, R5, R6, R7, R8,  R9, R10, R11, R12, R0 };


TFormHardverTeszt *FormHardverTeszt;
//---------------------------------------------------------------------------
__fastcall TFormHardverTeszt::TFormHardverTeszt(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormHardverTeszt::FormActivate(TObject *Sender)
{
   AnsiString  strLine;

   ListBoxLog->Items->Clear();

   pHardware->bTest = true;
   pHardware->wRelay = 0;
}
//---------------------------------------------------------------------------
void __fastcall TFormHardverTeszt::BitBtnHWTesztClick(TObject *Sender)
{
   // Megkérdezi, hogy a relay panel uC-ott vann-e a comX végén
   AnsiString  strLine;

   ListBoxLog->Items->Clear();

   if( pHardware->bSearchHardware() )
      ListBoxLog->Items->Add( FormLanguage->LangStr(STR_MSG_RELAYPANEL_OK) );
   else
      ListBoxLog->Items->Add( FormLanguage->LangStr(STR_MSG_RELAYPANEL_ERROR) );

   pHardware->EnableModulIRQ();
}
//---------------------------------------------------------------------------
void __fastcall TFormHardverTeszt::BitBtnHWInitClick(TObject *Sender)
{
   AnsiString  strLine;

   ListBoxLog->Items->Clear();

   if( pHardware->bSearchHardware() )
   {
      ListBoxLog->Items->Add( FormLanguage->LangStr(STR_MSG_RELAYPANEL_OK) );
      ListBoxLog->Items->Add( FormLanguage->LangStr(STR_MSG_LEDMODUL_SEARCH) );

      for( BYTE i=0; i<MAX_MODUL_SZAM; i++ )
      {
         pHardware->LED_Modul[ i ].bVan = false;
         pHardware->LED_Modul[ i ].bSendIras = false;
         pHardware->LED_Modul[ i ].bSendStart = false;
         pHardware->LED_Modul[ i ].bSendEnd = false;
         pHardware->LED_Modul[ i ].bStop = false;

         //Kereses max 7-szer
         BYTE j = 0;
         do
         {
            pHardware->byLedModulKeres( i );
            j++;
         }while( j<8 && !pHardware->LED_Modul[ i ].bVan );

         if( pHardware->LED_Modul[ i ].bVan )
         {
            strLine.sprintf( FormLanguage->LangStr(STR_MSG_LEDMODUL_X_OK).c_str(), i+1, j );
            ListBoxLog->Items->Add( strLine );
            Update();
         }
      }
   }
   else
      ListBoxLog->Items->Add( FormLanguage->LangStr(STR_MSG_RELAYPANEL_ERROR) );

   pHardware->EnableModulIRQ();

   ListBoxLog->Items->Add( FormLanguage->LangStr(STR_MSG_END) );
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::BitBtnLedModulKeresClick(
      TObject *Sender)
{
BYTE i;
AnsiString  strLine, strLine2;
BYTE byStatus;
char chMessage[2048];

    ListBoxLog->Items->Clear();
    pHardware->DisableModulIRQ();
    for( i=0; i<MAX_MODUL_SZAM; i++ )
    {
        strLine.sprintf( FormLanguage->LangStr(STR_MSG_LEDMODUL_X).c_str(), i+1 );
        chMessage[0] = SEND_1BYTE_TO_MODUL;
        chMessage[1] = GET_STATUS;
        if( pHardware->bSendMessageLEDModul_ReceiveStatus( chMessage, 2, i, &byStatus ) )
        {
            pHardware->LED_Modul[ i ].bVan = true;
            if( (byStatus & 0x08) == 0x08 ) strLine += "irq ";
            if( byStatus == 0x00 )      strLine += FormLanguage->LangStr(STR_MSG_OK);
            else if( (byStatus & 0x03) == 0x02 ) strLine += "Stop SW";
            else if( (byStatus & 0x03) == 0x01 ) strLine += "Start SW";
            else if( (byStatus & 0x03) == 0x03 ) strLine += "Restart";
        }
        else
        {
            strLine += "Error ";
            strLine2.sprintf( "0x%02x", byStatus );
            strLine += strLine2;
        }
        ListBoxLog->Items->Add( strLine );
        Update();
    }
    pHardware->EnableModulIRQ();
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::BitBtnLedModulTesztClick(
      TObject *Sender)
{
BYTE i, j, k;
AnsiString  strLine, strLine3, strLine2[ MAX_MODUL_SZAM ];
BYTE byStatus, byHiba[ MAX_MODUL_SZAM ];
char chMessage[2048];

    ListBoxLog->Items->Clear();

    for( j=0; j<MAX_MODUL_SZAM; j++ )
    {
        strLine2[j] = "";
        byHiba[j] = 0;
    }
    pHardware->DisableModulIRQ();
    
    /////////////////////////////////////////////////////////////////
    //Teszt
    for( j=1; j<100; j++ )
    {
        for( i=0; i<MAX_MODUL_SZAM; i++ )
        {
           if( pHardware->LED_Modul[ i ].bVan )
           {
              chMessage[0] = SEND_3BYTE_TO_MODUL;
              chMessage[1] = SEND_TIME;
              chMessage[2] = j;
              chMessage[3] = 0;
              if( pHardware->bSendMessageLEDModul_ReceiveStatus( chMessage, 4, i, &byStatus ) )
              {
                  strLine2[i].sprintf( "%02d LED modul ", i+1 );

                  if( (byStatus & 0x08) == 0x08 ) strLine2[i] += "irq ";

                  if( byStatus == 0x00 )               strLine2[i] += FormLanguage->LangStr(STR_MSG_OK);
                  else if( (byStatus & 0x03) == 0x02 ) strLine2[i] += "Stop SW";
                  else if( (byStatus & 0x03) == 0x01 ) strLine2[i] += "Start SW";
                  else if( (byStatus & 0x03) == 0x03 ) strLine2[i] += "Restart";
              }
              else
              {
                  strLine2[i].sprintf( FormLanguage->LangStr(STR_MSG_LEDMODUL_X_ERROR).c_str(), i+1 );
                  byHiba[ i ]++;
              }

              ListBoxLog->Items->Clear();
              strLine.sprintf( "%02d  Test (99)", j );
              ListBoxLog->Items->Add( strLine );
              for( k=0; k<MAX_MODUL_SZAM; k++ )
              {
                  if( pHardware->LED_Modul[ k ].bVan )
                  {
                      strLine.sprintf( "         Error = %02d", byHiba[k] );
                      strLine3 = strLine2[k] + strLine;
                      ListBoxLog->Items->Add( strLine3 );
                  }
              }
              Update();
           }
        }
    }
    pHardware->EnableModulIRQ();
    ListBoxLog->Items->Add( "...... END ......" );
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::BitBtnLedModulCimSetClick(
      TObject *Sender)
{
BYTE i;
AnsiString  strLine;
BYTE byStatus;
char chMessage[2048];

   ListBoxLog->Items->Clear();

    for( i=0; i<MAX_MODUL_SZAM; i++ )
    {
        strLine.sprintf( "LED modul %02d ", i+1 );

        chMessage[0] = SEND_3BYTE_TO_MODUL;
        chMessage[1] = SEND_SET_ADDR;
        chMessage[2] = 0xa5;
        chMessage[3] = 0x99;
        if( pHardware->bSendMessageLEDModul_ReceiveStatus( chMessage, 4, i, &byStatus ) )
        {}
        Update();
        ListBoxLog->Items->Add( strLine );
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::BitBtnRelayRunTestClick(TObject *Sender)
{
BYTE i;
    for( i=0; i<12+1; i++ )
    {
        pHardware->wRelay = run_rel[ i ];
        Sleep(100);
        pHardware->HW_Kezel();
    }
}
//---------------------------------------------------------------------------


void __fastcall TFormHardverTeszt::ChkRelay01Click(TObject *Sender)
{
    if( ChkRelay01->Checked ) pHardware->wRelay |= R1;
        else pHardware->wRelay &= ~R1;
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::ChkRelay02Click(TObject *Sender)
{
    if( ChkRelay02->Checked ) pHardware->wRelay |= R2;
        else pHardware->wRelay &= ~R2;
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::ChkRelay03Click(TObject *Sender)
{
    if( ChkRelay03->Checked ) pHardware->wRelay |= R3;
        else pHardware->wRelay &= ~R3;
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::ChkRelay04Click(TObject *Sender)
{
    if( ChkRelay04->Checked ) pHardware->wRelay |= R4;
        else pHardware->wRelay &= ~R4;
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::ChkRelay05Click(TObject *Sender)
{
    if( ChkRelay05->Checked ) pHardware->wRelay |= R5;
        else pHardware->wRelay &= ~R5;
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::ChkRelay06Click(TObject *Sender)
{
    if( ChkRelay06->Checked ) pHardware->wRelay |= R6;
        else pHardware->wRelay &= ~R6;
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::ChkRelay07Click(TObject *Sender)
{
    if( ChkRelay07->Checked ) pHardware->wRelay |= R7;
        else pHardware->wRelay &= ~R7;
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::ChkRelay08Click(TObject *Sender)
{
    if( ChkRelay08->Checked ) pHardware->wRelay |= R8;
        else pHardware->wRelay &= ~R8;
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::ChkRelay09Click(TObject *Sender)
{
    if( ChkRelay09->Checked ) pHardware->wRelay |= R9;
        else pHardware->wRelay &= ~R9;
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::ChkRelay10Click(TObject *Sender)
{
    if( ChkRelay10->Checked ) pHardware->wRelay |= R10;
        else pHardware->wRelay &= ~R10;
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::ChkRelay11Click(TObject *Sender)
{
    if( ChkRelay11->Checked ) pHardware->wRelay |= R11;
        else pHardware->wRelay &= ~R11;
}
//---------------------------------------------------------------------------

void __fastcall TFormHardverTeszt::ChkRelay12Click(TObject *Sender)
{
    if( ChkRelay12->Checked ) pHardware->wRelay |= R12;
        else pHardware->wRelay &= ~R12;
}
//---------------------------------------------------------------------------
void __fastcall TFormHardverTeszt::BitBtnOkClick(TObject *Sender)
{
/*   ChkRelay1->Checked = false;
   ChkRelay2->Checked = false;
   ChkRelay3->Checked = false;
   ChkRelay4->Checked = false;
   ChkRelay5->Checked = false;
   ChkRelay6->Checked = false;
   ChkRelay7->Checked = false;
   ChkRelay8->Checked = false;
   ChkRelay9->Checked = false;
   ChkRelay10->Checked = false;
   ChkRelay11->Checked = false;
   ChkRelay12->Checked = false;*/
   pHardware->bTest = false;
   pHardware->wRelay = 0;
}
//---------------------------------------------------------------------------
void __fastcall TFormHardverTeszt::CheckLedModulOnOffClick(TObject *Sender)
{
    if( CheckLedModulOnOff->Checked ) pHardware->bSendToModulPower_ON = true;
        else pHardware->bSendToModulPower_OFF = true;;
}
//---------------------------------------------------------------------------
void __fastcall TFormHardverTeszt::BitBtnBitBtnLedModulGombFigyelesClick(
      TObject *Sender)
{
int nTimer = 2000;
char chSerialOut[2048];
int nHossz;
BYTE i, byStatus;
char chMessage;
AnsiString  strLine, strLine2;

    ListBoxLog->Items->Clear();
    ListBoxLog->Items->Add( FormLanguage->LangStr(STR_MSG_MODULIRQ_INVESTIGATE) );
    Update();
    pHardware->EnableModulIRQ();

    do
    {
         //Szoli LED Modul IRQ figyelés
         if( pHardware->bSerialMessage( &chMessage ) )
         {
              if( chMessage == MODUL_IRQ )
              {
                  //mivel Modul IRQ akkor lekapcsolja az IRQ-üzenetet,
                  // míg le nem kérdezi a status-okat
                  pHardware->DisableModulIRQ();

                  // Modul IRQ lekezeles
                  for( i=0; i<MAX_MODUL_SZAM; i++ )
                  {
                      if( pHardware->LED_Modul[ i ].bVan )
                      {
                          chSerialOut[0] = SEND_1BYTE_TO_MODUL;
                          chSerialOut[1] = GET_STATUS;
                          if( pHardware->bSendMessageLEDModul_ReceiveStatus( chSerialOut, 2, i, &byStatus ) )
                          {
                              strLine = "";
                              ///////////////////////////////////////////
                              if( (byStatus & 0x08) == 0x08 )
                              {
                                 strLine.sprintf( "irq " );
                              }

                              ///////////////////////////////////////////
                              if( (byStatus & 0x03) == 0x01 )
                              {
                                 strLine2.sprintf( "LedModul %02d   0x%02x   Start SW", i+1, byStatus );
                              }

                              ///////////////////////////////////////////
                              if( (byStatus & 0x03) == 0x02 )
                              {
                                 strLine2.sprintf( "LedModul %02d   0x%02x  Stop SW", i+1, byStatus );
                              }

                              ///////////////////////////////////////////
                              if( (byStatus & 0x03) == 0x03 )
                              {
                                 strLine2.sprintf( "LedModul %02d   0x%02x  Restart", i+1, byStatus );
                              }

                              if( strLine != "" )
                              {
                                  ListBoxLog->Items->Add( strLine + strLine2 );
                                  Update();
                              }
                          }
                          else//if( pHardware->bSendMessageLEDModul_ReceiveStatus( chSerialOut, 2, i, &byStatus ) )
                          {
                              //nincs válasz
//                              byLedModulOlvasasiHiba++;
                          }//if( bSendMessageLEDModul_ReceiveStatus( chSerialOut, 2, i, &byStatus ) )
                      }//if( LED_Modul[ i ].bVan )
                  }
                  pHardware->EnableModulIRQ();
              }
         }// nincs LED Modul IRQ

         Sleep( 10 );
    }while( nTimer-- > 0 );
    ListBoxLog->Items->Add( "...... END ......" );
}
//---------------------------------------------------------------------------
void __fastcall TFormHardverTeszt::BitBtnWriteEEPROMClick(TObject *Sender)
{
   char chSerialOut[100];

   memset( chSerialOut, 0, sizeof(chSerialOut) );
   strncpy( chSerialOut, EditEEPROM->Text.c_str(), 98 );

   if( pHardware->bWriteEEprom( 0, chSerialOut ) )
   {
       EditEEPROM->Text = "";
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormHardverTeszt::BitBtnReadEEPROMClick(TObject *Sender)
{
   char chSerialOut[101];

   memset( chSerialOut, 0, sizeof(chSerialOut) );
   pHardware->bReedEEprom( 0, chSerialOut);

   EditEEPROM->Text = AnsiString( chSerialOut );
}
//---------------------------------------------------------------------------

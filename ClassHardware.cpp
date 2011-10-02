//---------------------------------------------------------------------------

#include <vcl.h>

#include "Classes.h"
#include "Database.h"
#include "HW_COMMAND.h"
#include "Language.h"
//---------------------------------------------------------------------------
#define WDT_TIME  6  //6*300ms
#define LED_MODUL_OLVASASI_HIBA       10
#define LED_MODUL_MAX_UJRAINDULAS     5
#define LED_MODUL_KIKAPCS_IDO_x300ms  10
//---------------------------------------------------------------------------

//12 Relay-os hardware
const WORD rel_csovek [] = {
 R2, R4, R6, R8, R10, R12, R0, R0,  R0, R0, R0, R0,  //1
 R2, R4, R6, R8, R10, R12, R0, R0,  R0, R0, R0, R0,  //2
 R2, R4, R6, R8, R10, R12, R0, R0,  R0, R0, R0, R0,  //3
 R2, R4, R6, R8, R10, R12, R0, R0,  R0, R0, R0, R0,  //4
 R2, R4, R6, R8, R10, R12, R0, R0,  R0, R0, R0, R0,  //5
 R2, R4, R6, R8, R10, R12, R0, R0,  R0, R0, R0, R0,  //6
 R2, R4, R6, R8, R10, R12, R9, R11, R0, R0, R0, R0,  //7
 R2, R4, R6, R8, R10, R12, R9, R11, R0, R0, R0, R0,  //8
 R2, R4, R6, R8, R10, R12, R9, R11, R7, R0, R0, R0,  //9
 R2, R4, R6, R8, R10, R12, R9, R11, R7, R5, R0, R0,  //10
 R2, R4, R6, R8, R10, R12, R9, R11, R7, R5, R3, R0,  //11
 R2, R4, R6, R8, R10, R12, R9, R11, R7, R5, R3, R1 };//12

const WORD rel_vent [] = {
 R1, R3, R5, R7, R9,  R11, R0, R0, R0, R0, R0, R0,  //1
 R1, R3, R5, R7, R9,  R11, R0, R0, R0, R0, R0, R0,  //2
 R1, R3, R5, R7, R9,  R11, R0, R0, R0, R0, R0, R0,  //3
 R1, R3, R5, R7, R9,  R11, R0, R0, R0, R0, R0, R0,  //4
 R1, R3, R5, R7, R9,  R11, R0, R0, R0, R0, R0, R0,  //5
 R1, R3, R5, R7, R9,  R11, R0, R0, R0, R0, R0, R0,  //6
 R1, R3, R5, R7, R0,  R0,  R0, R0, R0, R0, R0, R0,  //7
 R1, R3, R5, R7, R0,  R0,  R0, R0, R0, R0, R0, R0,  //8
 R1, R3, R5, R0, R0,  R0,  R0, R0, R0, R0, R0, R0,  //9
 R1, R3, R0, R0, R0,  R0,  R0, R0, R0, R0, R0, R0,  //10
 R1, R0, R0, R0, R0,  R0,  R0, R0, R0, R0, R0, R0,  //11
 R0, R0, R0, R0, R0,  R0,  R0, R0, R0, R0, R0, R0 };//12

//---------------------------------------------------------------------------
CS_Hardware::CS_Hardware()
{
   DEMO           = false;
   wRelay         = 0;
   wRelay_mem     = 0;
   bySerial_Error = 0;
   byHwWdtCounter = WDT_TIME;
   bTest          = false;
   bEnableIRQ_Msg = false;
   byLedModulOlvasasiHiba = 0;
   byLedModulUjraindulas = LED_MODUL_MAX_UJRAINDULAS;
   byLedModulKikapcsTimer = 0;
   bSendToModulPower_ON = false;
   bSendToModulPower_OFF = false;
   chModulMessage = 0;
   bErrorMessageDisplayed = false;
}
//---------------------------------------------------------------------------
CS_Hardware::~CS_Hardware()
{
}
//---------------------------------------------------------------------------
void CS_Hardware::HW_Kezel()
{
   //---------------------------------------------------
   // Demo esetén nem foglalkozik a hardware-al
   //---------------------------------------------------
   if( DEMO ) return;

   LOG4( "START >> CS_Hardware::HW_Kezel()" );

   int i;
   int nHossz;
   char chSerialOut[2048];
   char chSerialIn[2048];
   BYTE byStatus;
   int szoliszam =(int)pSzolarium.size();

   //---------------------------------------------------
   // Relay állapotok beállítása
   //---------------------------------------------------

   if( !bTest )
   {
       wRelay = 0;
       for( i=0; i<szoliszam; i++ )
       {
          /////////////////////////////////
          if( pSzolarium[i]->StatuszLekerdezes() == STATUS_BARNULAS )
          {
              if( !pSzolarium[i]->CsovekKikapcsolva() )
              {
                  if( !LED_Modul[ i ].bStop )  //ha nincs relay stop
                      wRelay |= rel_csovek[(szoliszam-1)*12+i];
              }
              if( !pSzolarium[i]->stAdat.bInfraSzolarium )
              {
                  wRelay |= rel_vent[(szoliszam-1)*12+i];
              }
          }
          /////////////////////////////////
          else if( pSzolarium[i]->StatuszLekerdezes() == STATUS_SZAUNAZAS )
          {
              wRelay |= rel_vent[(szoliszam-1)*12+i];
          }
          /////////////////////////////////
          else if( pSzolarium[i]->StatuszLekerdezes() == STATUS_UTOHUTES )
          {
              if( !pSzolarium[i]->stAdat.bInfraSzolarium )
              {
                  wRelay |= rel_vent[(szoliszam-1)*12+i];
              }
          }
       }
   }

   if( wRelay_mem != wRelay )
   {
       chSerialOut[0] = SET_RELAY;
       chSerialOut[1] = (BYTE) wRelay;
       chSerialOut[2] = (BYTE) (wRelay>>8);
       chSerialOut[3] = 0x5a;
       if( bSendMessageRelay_ReceiveSuccess( chSerialOut, 4  ) )
           wRelay_mem = wRelay;
   }

   //-------------------------------------------------------
   // WDT frissités, ha nem volt kikuldve semmi akkor WDT
   //-------------------------------------------------------
   if( byHwWdtCounter > 0 ) byHwWdtCounter--;
   if( byHwWdtCounter == 0 )
   {
       chSerialOut[0] = CLR_RELAY_TIMER;
       if( bSendMessageRelay_ReceiveSuccess( chSerialOut, 1  ) )
           byHwWdtCounter = WDT_TIME;
   }

   //--------------------------------------------------------------------------------------
   // Ha 10 próbálkozás után sem sikerül választ kapni az üzenetre akkor hibaüzenetet ír ki
   //--------------------------------------------------------------------------------------
//   if( bySerial_Error > 100 )
//   {
//       Sleep( 1 );
//   }


   //--------------------------------------------------------------------------------------
   // Szoli LED Modul vezérlés
   //--------------------------------------------------------------------------------------
   //Ha jó a soros komunikáció
   if( bySerial_Error == 0 )
   {
      //és fel van kapcsolva a LED táp
      if( (byLedModulKikapcsTimer == 0) && !bTest )
//      if( !bTest )
      {
         //Szoli LED Modul IRQ figyelés
         if( SComm->ReadMessage( chSerialIn, &nHossz ) )
         {
              if( chSerialIn[ nHossz-1 ] == MODUL_IRQ ||
                  chModulMessage == MODUL_IRQ )
              {
                  chModulMessage = 0;
                  //mivel Modul IRQ akkor lekapcsolja az IRQ-üzenetet,
                  // míg le nem kérdezi a status-okat
                  DisableModulIRQ();

                  // Modul IRQ lekezeles
                  for( i=0; i<szoliszam; i++ )
                  {
                      if( LED_Modul[ i ].bVan )
                      {
                          chSerialOut[0] = SEND_1BYTE_TO_MODUL;
                          chSerialOut[1] = GET_STATUS;
                          if( bSendMessageLEDModul_ReceiveStatus( chSerialOut, 2, i, &byStatus ) )
                          {
                             byLedModulOlvasasiHiba = 0;

                             ///////////////////////////////////////////
                             if( byStatus == 0 )
                             {}//Standby
                             ///////////////////////////////////////////
                             else if( (byStatus & 0x03) == 0x02 ) //Stop SW
                             {
                                 if( pSzolarium[i]->StatuszLekerdezes() == STATUS_SZAUNAZAS )
                                 {
                                     // Szauna megszakítása, következõ ciklus indítása
                                     pSzolarium[i]->StatuszSzaunaStop();
                                 }
                                 else if( pSzolarium[i]->StatuszLekerdezes() == STATUS_BARNULAS )
                                 {
                                     LED_Modul[ i ].bStop = true; //Relay kikapcsolás
                                 }
                             }
                             ///////////////////////////////////////////
                             else if( (byStatus & 0x03) == 0x01 ) //Start SW
                             {
                                 if( pSzolarium[i]->StatuszLekerdezes() == STATUS_VETKOZES )
                                 {
                                     // Vetkõzés megszakítása, következõ ciklus indítása
                                     pSzolarium[i]->StatuszVetkozesStop();
                                 }
                                 else if( pSzolarium[i]->StatuszLekerdezes() == STATUS_BARNULAS )
                                 {
                                     LED_Modul[ i ].bStop = false; //Relay bekapcsolás
                                 }
                             }

                             ///////////////////////////////////////////
                             else if( (byStatus & 0x03) == 0x03 ) // Restart, ujraindult
                             {
                                 LED_Modul[ i ].bSendIras = true;
                                 if( (pSzolarium[i]->StatuszLekerdezes() == STATUS_BARNULAS) ||
                                     (pSzolarium[i]->StatuszLekerdezes() == STATUS_SZAUNAZAS) )
                                 {
                                     LED_Modul[ i ].bSendStart = true;
                                 }
                             }
                          }
                          else//if( pHardware->bSendMessageLEDModul_ReceiveStatus( chSerialOut, 2, i, &byStatus ) )
                          {
                              //nincs válasz
                              byLedModulOlvasasiHiba++;
                          }//if( bSendMessageLEDModul_ReceiveStatus( chSerialOut, 2, i, &byStatus ) )
                      }//if( LED_Modul[ i ].bVan )
                  }//for
              }//if( chSerialIn[ nHossz-1 ] == MODUL_IRQ )
              else if( chSerialIn[ nHossz-1 ] == START_MESSAGE )
              {
                  //ujraindult a Relay panel, mindent ki kell küldeni
                  wRelay_mem = 0;
              }
         }// nincs LED Modul IRQ

         ////////////////////////////////////////////////////////////////////////
         //Szoli LED Modul vezérlés

         //Elenörzi van-e küldenivaló adat
         bool bVanKuldeniValoAdat = false;
         char chStatus;
         for( i=0; i<szoliszam; i++ )
         {
             if( LED_Modul[ i ].bVan )
             {
                 chStatus = pSzolarium[i]->StatuszLekerdezes();
                 if( chPrevStatus[i] == STATUS_ALAP && chStatus == STATUS_VETKOZES )  //vetkõzés
                 {
                    LED_Modul[ i ].bSendIras = true;
                 }
                 if( chPrevStatus[i] == STATUS_VETKOZES && chStatus == STATUS_ALAP )  //esc
                 {
                    LED_Modul[ i ].bSendIras = true;
                 }
                 if( chPrevStatus[i] == STATUS_VETKOZES && chStatus == STATUS_SZAUNAZAS )
                 {
                    LED_Modul[ i ].bSendIras = true;
                    LED_Modul[ i ].bSendStart = true;
                 }
                 if( chPrevStatus[i] == STATUS_VETKOZES && chStatus == STATUS_BARNULAS )
                 {
                    LED_Modul[ i ].bSendStart = true;
                 }
                 if( chPrevStatus[i] == STATUS_SZAUNAZAS && chStatus == STATUS_VARAKOZAS )
                 {
                    LED_Modul[ i ].bSendIras = true;
                    LED_Modul[ i ].bSendStart = true;
                 }
                 if( chPrevStatus[i] == STATUS_VARAKOZAS && chStatus == STATUS_BARNULAS )
                 {
                    LED_Modul[ i ].bSendIras = true;
                    LED_Modul[ i ].bSendStart = true;
                 }
                 if( chPrevStatus[i] == STATUS_BARNULAS  && chStatus == STATUS_UTOHUTES )
                 {
                    LED_Modul[ i ].bSendEnd = true;
                    LED_Modul[ i ].bStop = false;
                 }
                 chPrevStatus[ i ] = chStatus;
             }
         }

         bVanKuldeniValoAdat = false;
         for( i=0; i<szoliszam; i++ )
         {
             if( LED_Modul[ i ].bVan &&
                 ( LED_Modul[ i ].bSendIras  ||
                   LED_Modul[ i ].bSendStart ||
                   LED_Modul[ i ].bSendEnd    ) )
             {
                 bVanKuldeniValoAdat = true;
                 break;
             }
         }

//         if(false)
         //Adatok kiküldése a moduloknak
         if( bVanKuldeniValoAdat )
         {
             // Letiltlja az IRQ-t, hogy ne zavarja meg a komunikációt
             DisableModulIRQ();

             bool bHiba = false;
             int nIdo;
             //Kikuldi az adatokat
             for( i=0; i<szoliszam; i++ )
             {
                 if( LED_Modul[ i ].bVan )
                 {
                     /////////////////////////////////////////
                     if( LED_Modul[ i ].bSendIras )
                     {
                         chSerialOut[0] = SEND_3BYTE_TO_MODUL;
                         chSerialOut[1] = SEND_TIME;
                         nIdo = 0;
                         if( chPrevStatus[ i ] == STATUS_VETKOZES )
                             nIdo = pSzolarium[i]->GetBarnulasIdo();
                         else if( chPrevStatus[ i ] == STATUS_BARNULAS )
                             nIdo = pSzolarium[i]->GetSzoliIdo();
                         else if( chPrevStatus[ i ] == STATUS_SZAUNAZAS )
                             nIdo = pSzolarium[i]->GetSzoliIdo();
                         else if( chPrevStatus[ i ] == STATUS_VARAKOZAS )
                             nIdo = pSzolarium[i]->GetSzoliIdo();

                         chSerialOut[2] = (char)(nIdo/60);
                         chSerialOut[3] = (char)(nIdo%60);

                         if( bSendMessageLEDModul_ReceiveStatus( chSerialOut, 4, i, &byStatus ) )
                         {
                             LED_Modul[ i ].bSendIras = false;
                         }
                         else
                            bHiba = true;
                     }
                     /////////////////////////////////////////
                     if( LED_Modul[ i ].bSendStart )
                     {
                         chSerialOut[0] = SEND_1BYTE_TO_MODUL;
                         chSerialOut[1] = SEND_START;
                         if( bSendMessageLEDModul_ReceiveStatus( chSerialOut, 2, i, &byStatus ) )
                         {
                             LED_Modul[ i ].bSendStart = false;
                         }
                         else
                            bHiba = true;
                     }
                     /////////////////////////////////////////
                     if( LED_Modul[ i ].bSendEnd )
                     {
                         chSerialOut[0] = SEND_1BYTE_TO_MODUL;
                         chSerialOut[1] = SEND_END;
                         if( bSendMessageLEDModul_ReceiveStatus( chSerialOut, 2, i, &byStatus ) )
                         {
                             LED_Modul[ i ].bSendEnd = false;
                         }
                         else
                            bHiba = true;
                     }
                 }
             }
             if( bHiba )
                 byLedModulOlvasasiHiba++;
         }

         // Engedélyezi az IRQ-t, ha le volt tiltva
         EnableModulIRQ();
      }//if( byLedModulKikapcsTimer == 0 )


      // LED tápegység lekapcsolás/felkapcsolás hiba esetén próbálkozik úraindítással
      if( byLedModulOlvasasiHiba > LED_MODUL_OLVASASI_HIBA )
      {
          // LED modul tap lekapcsolas
          if( byLedModulKikapcsTimer == 0 )
          {
              byLedModulKikapcsTimer = LED_MODUL_KIKAPCS_IDO_x300ms;
              bSendToModulPower_OFF = true;
          }
          else
          {
              byLedModulKikapcsTimer--;

              // 0.9s-al korábban felkapcsolja, hogy magukhoz térjenek
              if( byLedModulKikapcsTimer == 3 )
                  bSendToModulPower_ON = true;

              if( byLedModulKikapcsTimer == 0 )
              {
                  // LED modul tap visszakapcsolás ha még nem érte el a max.számot
                  if( byLedModulUjraindulas > 0 )
                  {
                      byLedModulOlvasasiHiba = 0;
                      byLedModulUjraindulas --;
                      bSendToModulPower_ON = false;
                  }
                  else
                  {
                      //Tamás felugrik egy figyelmeztetõ ablak
                      //LED Modul komunikációs HIBA!
                      if( !bErrorMessageDisplayed )
                      {
                         bErrorMessageDisplayed = true;
                         if( Application->MessageBox( FormLanguage->LangStr(STR_MSG_LEDMODUL_COMMERR).c_str(),
                                                      FormLanguage->LangStr(STR_MSGBOX_EXCALMATION).c_str(),
                                                      MB_ICONEXCLAMATION ) == IDOK )
                         {
                            bErrorMessageDisplayed = false;
                         }
                      }
                  }
              }
          }
      }


      if( bSendToModulPower_ON )
      {
          chSerialOut[0] = MODUL_POWER_ON;
          if( bSendMessageRelay_ReceiveSuccess( chSerialOut, 1  ) )
          {
              bSendToModulPower_ON = false;
              LED_Modul_Init( (BYTE) szoliszam );
              EnableModulIRQ();
          }
      }

      if( bSendToModulPower_OFF )
      {
          chSerialOut[0] = MODUL_POWER_OFF;
          if( bSendMessageRelay_ReceiveSuccess( chSerialOut, 1  ) )
              bSendToModulPower_OFF = false;
      }
   }// if( bySerial_Error == 0 )

   LOG4( "END >> CS_Hardware::HW_Kezel()" );
}
//---------------------------------------------------------------------------
bool CS_Hardware::bReadSerialMessageTimOut( char *chMessage, int *nHossz, int nTimeOut )
{
   LOG4( "START >> CS_Hardware::bReadSerialMessageTimOut" );

   bool bRet = false;

   *nHossz = 0;
   do
   {
       if( SComm->ReadMessage( chMessage, nHossz )  )
       {
           if( (*nHossz > 0) && ((BYTE) chMessage[ (*nHossz)-1 ] != 0xff) )
           {
               bRet = true;
           }
           else
           {
               Sleep(15);
           }
       }

   }while( !bRet && (nTimeOut-- > 0) );

   Sleep( 2 ); //szükséges a hardware miatt

   if( chMessage[ (*nHossz)-1 ] == START_MESSAGE )
   {
       //ujraindult a Relay panel, mindent ki kell küldeni
       wRelay_mem = 0;
       bRet = false;
   }

   LOG4( "END >> CS_Hardware::bReadSerialMessageTimOut" );

   return bRet;
}
//---------------------------------------------------------------------------
bool CS_Hardware::bSendMessageRelay_ReceiveSuccess( char *chMessage, int nSendHossz )
{
   LOG4( "START >> CS_Hardware::bSendMessageRelay_ReceiveSuccess" );

BOOL bRes = false;
char chSerialIn[2048];
int nRecHossz;

    //buffer ürítés
    if( SComm->ReadMessage( chSerialIn, &nRecHossz ) )
        if( chSerialIn[ nRecHossz-1 ] == MODUL_IRQ )
            chModulMessage = MODUL_IRQ;

    SComm->SendMessage( chMessage, nSendHossz );  //Serial Send
    bySerial_Error++;

    if( bReadSerialMessageTimOut( chSerialIn, &nRecHossz, 5 ) )
    {
        if( chSerialIn[ nRecHossz-1 ] == HW_SUCCESS )
        {
            byHwWdtCounter = WDT_TIME;
            bySerial_Error = 0; // sikeres válasz
            bRes = true;
        }
    }

    if( chSerialIn[ nRecHossz-1 ] == START_MESSAGE )
    {
        //ujraindult a Relay panel, mindent ki kell küldeni
        wRelay_mem = 0;
    }

   LOG4( "END >> CS_Hardware::bSendMessageRelay_ReceiveSuccess" );

   return bRes;
}
//---------------------------------------------------------------------------
bool
CS_Hardware::bSendMessageLEDModul_ReceiveStatus( char *chMessage,
                                                  int nSendHossz,
                                                  BYTE byCim,
                                                  BYTE *byStatus )
{
   LOG4( "START >> CS_Hardware::bSendMessageLEDModul_ReceiveStatus" );

char chSerialIn[2048];
int nRecHossz;
bool bRes = false;
BYTE byTimeOut;

    //buffer ürítés
    if( SComm->ReadMessage( chSerialIn, &nRecHossz ) )
        if( chSerialIn[ nRecHossz-1 ] == MODUL_IRQ )
            chModulMessage = MODUL_IRQ;

    byCim++;
    chMessage[ 1 ] += byCim<<4;

    SComm->SendMessage( chMessage, nSendHossz );  //Serial Send
    *byStatus = 0;

    //2 byte-os parancsnál 35 ms szukseges (60)
    //4  byte-os parancsnál 70 ms szukseges (105)
    if( nSendHossz > 2 ) byTimeOut = 11;
       else byTimeOut = 6;

    if( bReadSerialMessageTimOut( chSerialIn, &nRecHossz, byTimeOut  ) )
    {
        *byStatus = (BYTE) chSerialIn[ nRecHossz-1 ];
        byHwWdtCounter = WDT_TIME;
        bySerial_Error = 0; // sikeres válasz
        if( (*byStatus>>4) == byCim )  //válasz ellenörzés
        {
            *byStatus &= 0x0b; //irq 0 stop start
            bRes = true;
        }
        else
            bRes = false;
    }
    else
        bRes = false;


   //Hibás válasz
   if( chSerialIn[ nRecHossz-1 ] == START_MESSAGE )
   {
       //ujraindult a Relay panel, mindent ki kell küldeni
       wRelay_mem = 0;
   }

   LOG4( "END >> CS_Hardware::bSendMessageLEDModul_ReceiveStatus" );

   return bRes;
}
//---------------------------------------------------------------------------
bool CS_Hardware::bSearchHardware( void )
{
   LOG4( "START >> CS_Hardware::bSearchHardware" );

   char  chMessage[512];
   char  chSerialIn[512];
   int   nRecHossz = 0;
   bool  bRes = false;

   memset( chMessage, 0, sizeof(chMessage) );
   memset( chSerialIn, 0, sizeof(chSerialIn) );

    if( SComm->ReadMessage( chSerialIn, &nRecHossz ) )
        if( chSerialIn[ nRecHossz-1 ] == MODUL_IRQ )
            chModulMessage = MODUL_IRQ;

    chMessage[ 0 ]= SEARCH_HW;
    chMessage[ 1 ]= 'H';

    SComm->SendMessage( chMessage, 2 );  //Serial Send

    bySerial_Error++;
    Sleep( 100 ); //var, hogy a PIC tudjon válaszolni

    if( bReadSerialMessageTimOut( chSerialIn, &nRecHossz, 5  ) )
    {
        if( (chSerialIn[ nRecHossz-2 ] == 'Y') &&
            ((BYTE) chSerialIn[ nRecHossz-1 ] == HW_SUCCESS) )
            bRes = true;
        byHwWdtCounter = WDT_TIME;
    }

   LOG4( "END >> CS_Hardware::bSearchHardware" );

   return bRes;
}
//---------------------------------------------------------------------------
void CS_Hardware::LED_Modul_Init( BYTE bySzoliszam )
{
BYTE i;
char chMessage[2048];
//BYTE byStatus;

   for( i=0; i<bySzoliszam; i++ )
   {
      LED_Modul[ i ].bVan = false;
//      LED_Modul[ i ].bSendIras = false;
//      LED_Modul[ i ].bSendStart = false;
//      LED_Modul[ i ].bSendEnd = false;

      //Kereses max 4-szer
      BYTE j = 4;
      do
      {
//         byStatus = byLedModulKeres( i );
         byLedModulKeres( i );
         j--;
      }while( j>0 && !LED_Modul[ i ].bVan );
   }
}
//---------------------------------------------------------------------------
BYTE CS_Hardware::byLedModulKeres( BYTE byCim )
{
BYTE byStatus;
char chMessage[2048];

    LED_Modul[ byCim ].bVan = false;
    LED_Modul[ byCim ].bSendIras = false;
    LED_Modul[ byCim ].bSendStart = false;
    LED_Modul[ byCim ].bSendEnd = false;

    chMessage[0] = SEND_1BYTE_TO_MODUL;
    chMessage[1] = GET_STATUS;
    if( bSendMessageLEDModul_ReceiveStatus( chMessage, 2, byCim, &byStatus ) )
    {
        LED_Modul[ byCim ].bVan = true;
        return byStatus;
    }
    else
    {
        return 0xff;
    }
}
//---------------------------------------------------------------------------
BOOL CS_Hardware::bSerialMessage( char *chMessage )
{
char chSerialIn[2048];
int nHossz;
bool bRes = false;

    if( SComm->ReadMessage( chSerialIn, &nHossz ) )
    {
        *chMessage = chSerialIn[ nHossz-1 ];
        bRes = true;
    }
    return bRes;
}
//---------------------------------------------------------------------------
void CS_Hardware::EnableModulIRQ()
{
char chSerialOut[2048];
BYTE byTemp;

   if( !bEnableIRQ_Msg )
   {
       do
       {
           chSerialOut[0] = MODUL_ENABLE;
           if( bSendMessageRelay_ReceiveSuccess( chSerialOut, 1 ) )
               bEnableIRQ_Msg = true;

       }while( !bEnableIRQ_Msg && byTemp++<10 );
   }
}
//---------------------------------------------------------------------------
void CS_Hardware::DisableModulIRQ()
{
char chSerialOut[2048];
BYTE byTemp;

   if( bEnableIRQ_Msg )
   {
       do
       {
           chSerialOut[0] = MODUL_DISABLE;
           if( bSendMessageRelay_ReceiveSuccess( chSerialOut, 1 ) )
               bEnableIRQ_Msg = false;

       }while( bEnableIRQ_Msg && byTemp++<10 );
   }
}
//---------------------------------------------------------------------------
BYTE CS_Hardware::bSendMessageRelay_Receive( char *chMessage, int nSendHossz )
{
BYTE  byRes = 0xFF;
char chSerialIn[2048];
int nRecHossz;

    //buffer ürítés
    if( SComm->ReadMessage( chSerialIn, &nRecHossz ) )
        if( chSerialIn[ nRecHossz-1 ] == MODUL_IRQ )
            chModulMessage = MODUL_IRQ;

    SComm->SendMessage( chMessage, nSendHossz );  //Serial Send
    bySerial_Error++;

    if( bReadSerialMessageTimOut( chSerialIn, &nRecHossz, 5 ) )
    {
         byHwWdtCounter = WDT_TIME;
         bySerial_Error = 0; // sikeres válasz
         byRes = chSerialIn[ nRecHossz-1 ];
    }

    if( chSerialIn[ nRecHossz-1 ] == START_MESSAGE )
    {
        //ujraindult a Relay panel, mindent ki kell küldeni
        wRelay_mem = 0;
    }
    return byRes;
}
//---------------------------------------------------------------------------
BYTE CS_Hardware::bySendMessageRelay_ReceiveData( char *chMessage, int nSendHossz )
{
//BYTE  byRes = 0xFF;
char chSerialIn[2048];
int nRecHossz;

    //buffer ürítés
    if( SComm->ReadMessage( chSerialIn, &nRecHossz ) )
        if( chSerialIn[ nRecHossz-1 ] == MODUL_IRQ )
            chModulMessage = MODUL_IRQ;

    SComm->SendMessage( chMessage, nSendHossz );  //Serial Send
    bySerial_Error++;

    if( bReadSerialMessageTimOut( chSerialIn, &nRecHossz, 5 ) )
    {
         byHwWdtCounter = WDT_TIME;
         bySerial_Error = 0; // sikeres válasz
         /*byRes = */chSerialIn[ nRecHossz-1 ];
    }

    if( chSerialIn[ nRecHossz-1 ] == START_MESSAGE )
    {
        //ujraindult a Relay panel, mindent ki kell küldeni
        wRelay_mem = 0;
        return 0;
    }

    return chSerialIn[ nRecHossz-1 ];
}
//---------------------------------------------------------------------------
BOOL CS_Hardware::bWriteEEprom( BYTE byStartAddress, char *chMessage )
{
BYTE byAddress = byStartAddress;
BYTE i = 0;
BOOL bRes = TRUE;
char chSerialOut[2048];

   while( (chMessage[i] != 0) && (i < 100) && bRes )
   {
       chSerialOut[0] = WRITE_EEPROM;
       chSerialOut[1] = byAddress++;
       chSerialOut[2] = chMessage[ i++ ];
       Sleep( 15 );
       if( !bSendMessageRelay_ReceiveSuccess( chSerialOut, 3 ) ) bRes = FALSE;
   }

   //0 a végére
   chSerialOut[0] = WRITE_EEPROM;
   chSerialOut[1] = byAddress;
   chSerialOut[2] = 0;
   Sleep( 15 );
   if( !bSendMessageRelay_ReceiveSuccess( chSerialOut, 3 ) ) bRes = FALSE;

   return bRes;
}
//---------------------------------------------------------------------------
BOOL CS_Hardware::bReedEEprom( BYTE byStartAddress, char *chMessage )
{
BYTE byAddress = byStartAddress;
BYTE i = 0;
char chSerialOut[2048];

   do
   {
       chSerialOut[0] = READ_EEPROM;
       chSerialOut[1] = byAddress++;
       chMessage[i] = bySendMessageRelay_ReceiveData( chSerialOut, 2 );

   }while( (chMessage[i++] != 0) && (i < 100) );

   //0 a végére
   chMessage[i] = 0;

   return TRUE;
}
//---------------------------------------------------------------------------

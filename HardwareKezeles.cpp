//---------------------------------------------------------------------------

#include <vcl.h>

#include "HardwareKezeles.h"
#include "HW_COMMAND.h"


/////////////////////////////////////////////////
/////////////////////////////////////////////////

//Lehessen demo verziót fordítani, ami móködik hw nélkül
bool DEMO = true;

#define WDT_TIME  4  //4*300ms

//Relay mask define
#define R0   0x0000

#define R1   0x0100
#define R2   0x0200
#define R3   0x0400
#define R4   0x0800
#define R5   0x1000
#define R6   0x2000

#define R7   0x0001
#define R8   0x0002
#define R9   0x0004
#define R10  0x0008
#define R11  0x0010
#define R12  0x0020

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
 R0, R0, R0, R0, R0,  R0,  R0, R0, R0, R0, R0, R0 };  //12

/////////////////////////////////////////////////
//Globális változók
/////////////////////////////////////////////////
WORD wRelay_mem = 0;
BYTE bySerial_Error = 0;
BYTE byHwWdtCounter = WDT_TIME;
BOOL bTest = false;
int szoliszam;

//LED Modul
typ_LED_Modul LED_Modul[ 12 ];
BOOL bEnableIRQ_Msg = true;
//---------------------------------------------------------------------------

void HW_Kezel( vector<CS_Solarium*> pSzolarium, CS_SerialComm *SComm )
{
   int i;
   int nHossz;
   WORD wRelay = 0;
   char chSerialOut[2048];
   char chSerialIn[2048];
   BYTE byStatus;

   szoliszam =(int)pSzolarium.size();

   //---------------------------------------------------
   // Demo esetén nem foglalkozik a hardware-al
   //---------------------------------------------------
   if( DEMO ) return;

   //---------------------------------------------------
   // Relay állapotok beállítása
   //---------------------------------------------------

   if( !bTest )
   {
       for( i=0; i<szoliszam; i++ )
       {
          /////////////////////////////////
          if( pSzolarium[i]->StatuszLekerdezes() == STATUS_BARNULAS )
          {
              if( !pSzolarium[i]->CsovekKikapcsolva() )
              {
                  wRelay |= rel_csovek[(szoliszam-1)*12+i];
              }
//              if( !Szauna )
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
//              if( !Szauna )
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
       if( bSendMessageRelay_ReceiveSuccess( chSerialOut, 4, SComm  ) ) wRelay_mem = wRelay;
   }

   //-------------------------------------------------------
   // WDT frissités, ha nem volt kikuldve semmi akkor WDT
   //-------------------------------------------------------
   if( (bySerial_Error == 0) && (byHwWdtCounter > 0) ) byHwWdtCounter--;
   if( byHwWdtCounter == 0 )
   {
       chSerialOut[0] = CLR_RELAY_TIMER;
       if( bSendMessageRelay_ReceiveSuccess( chSerialOut, 1, SComm  ) ) byHwWdtCounter = WDT_TIME;
   }

   //--------------------------------------------------------------------------------------
   // Ha 10 próbálkozás után sem sikerül választ kapni az üzenetre akkor hibaüzenetet ír ki
   //--------------------------------------------------------------------------------------
   if( bySerial_Error > 10 )
   {
       //Hibaablak elõugorjon
//       "Soros komunnikáciû hiba, kérem ellenõrizze e kábelt a számítûgép és a hardware között!"
// ki lehessen lépni a programból
// vagy folytatás esetén         bySerial_Error = 0;
       Sleep( 1 );
   }


   //--------------------------------------------------------------------------------------
   // Szoli LED Modul vezérlés
   //--------------------------------------------------------------------------------------

   if( bySerial_Error == 0 )
   {
       //Szoli LED Modul vezérlés
   }

   //Szoli LED Modul IRQ figyelés
   if( SComm->ReadMessage( chSerialIn, &nHossz ) )
   {
       if( chSerialIn[ nHossz-1 ] == MODUL_IRQ )
       {
           //mivel Modul IRQ akkor lekapcsolja az IRQ-üzenetet, míg le nem kérdezi a status-okat
           if( bEnableIRQ_Msg )
           {
               chSerialOut[0] = MODUL_DISABLE;
               if( bSendMessageRelay_ReceiveSuccess( chSerialOut, 1, SComm  ) ) bEnableIRQ_Msg = false;
           }

           if( !bEnableIRQ_Msg )
           {
               // Modul IRQ lekezeles
               for( i=0; i<szoliszam; i++ )
               {
                   if( LED_Modul[ i ].bVan )
                   {
                       chSerialOut[0] = (i<<4) || GET_STATUS;
                       byStatus = bySendMessageLEDModul_ReceiveStatus( chSerialOut, 1, SComm  );
                       if( byStatus == 0 )
                       {
                           //nem volt válasz, hiba
                       }
                       else
                       {
                           if( (byStatus>>4) == i )
                           {
                               //ujraindult a modul
                               if( (byStatus && 0x03) == 0x03 )
                               {
                                   LED_Modul[ i ].bIras = true;
                                   if( (pSzolarium[i]->StatuszLekerdezes() == STATUS_BARNULAS) ||
                                       (pSzolarium[i]->StatuszLekerdezes() == STATUS_SZAUNAZAS) )
                                   {
                                       LED_Modul[ i ].bSendStart = true;
                                   }
                               }
                               //Modul Start
                               else if( (byStatus && 0x03) == 0x01 )
                               {
                                   LED_Modul[ i ].bStop = false;
                                   LED_Modul[ i ].bIras = true;
                                   if( pSzolarium[i]->StatuszLekerdezes() == STATUS_VETKOZES )
                                   {
//                                       szoli[i].vetkozes:=0;
//                                       szoli[i].vetkozesmp:=1;
                                       LED_Modul[ i ].bSendStart = true;
                                   }
                               }
                               //Modul Stop
                               else if( (byStatus && 0x03) == 0x02 )
                               {
                                   if( pSzolarium[i]->StatuszLekerdezes() == STATUS_BARNULAS )
                                   {
//                                       szoli[i].stopb := true;
                                       LED_Modul[ i ].bStop = true;
                                   }

                                   if( pSzolarium[i]->StatuszLekerdezes() == STATUS_SZAUNAZAS )
                                   {
//                                       szoli[i].vetkozes:=0;
//                                       szoli[i].vetkozesmp:=1;
                                       LED_Modul[ i ].bIras = true;
                                       LED_Modul[ i ].bSendStart = true;
                                   }
                               }
                           }
                       }



/*                       bLcdhiba := false;
                       bySerIn := Send1ByteToModul( i*16+GET_STATUS, bLcdhiba );

                       if( not( bLcdhiba ) )then begin
                           {Modul Wdt Error vagy ujraindult a modul}
                           if( ((bySerIn and $01)<>0) and
                               ((bySerIn and $02)<>0) )then begin
                               led[i].iras := true;
                               if( szoli[i].barnb or szoli[i].szaunab )then begin
                                   led[i].send_start := true;
                               end;
                           end
                           { Modul START }
                           else begin
                             if( (bySerIn and $01)<>0 )then begin
                                led[i].veszjelzes:=false;
                                szoli[i].kiirb:=true;
                                if(szoli[i].barnb or szoli[i].szaunab )then begin
                                    rele_valtozott := true;
                                end;
                                szoli[i].stopb := false;
                                if (szoli[i].vetkb) then begin
                                    szoli[i].vetkozes:=0;
                                    szoli[i].vetkozesmp:=1;
                                    led[i].send_start := true;
                                end;
                             end
                             { Modul STOP/vészjelzés }
                             else begin
                               if( (bySerIn and $02)<>0 )then begin
                                   if( szoli[i].barnb or szoli[i].szaunab )then begin
                                       szoli[i].stopb := true;
                                       rele_valtozott := true;
                                   end;
                                 led[i].veszjelzes:=true;
                                   szoli[i].kiirb:=true;
                               end;
                             end;
                           end;
                       end;

                       if( (bLcdhiba) and (bySerialLedModulEnable = 0) )then begin
                           HibaFileTxt(' Led modul hiba IRQ üzenet '+strx(i)+'\n');
                           inc( napi_led_kikapcsolas );
                           bySerialLedModulEnable := LED_KIKAPCS_IDO;
                           Send_1_CommandRel( bSerialError, MODUL_POWER_OFF );
                       end;
                   end;
               end;
           end
           else if( bySerIn = START_MESSAGE )then begin
              bSendAllRelayData := true;
         end
           else begin { ismeretlen parancs/hiba eseten }
           {     bSendAllRelayData := true;}
           end;
       end;

//*  ************************************************************
       { WDT frisittes }
       if( idovaltozot ) then begin
           { LED modul táp kapcsolás}
           if( bySerialLedModulEnable > 0 )then begin
               dec( bySerialLedModulEnable );
               if( bySerialLedModulEnable = 1 )then begin
                   Send_1_CommandRel( bSerialError, MODUL_POWER_ON );
               end;
           end;
           { Relay Panel WDT timer }
           dec( byRelayWDTtimer );
         if( byRelayWDTtimer = 0 )then begin
             Send_1_CommandRel( bSerialError, CLR_RELAY_TIMER );
             byRelayWDTtimer := SERIAL_RELAY_REFRESH_TIME;
             if( bSerialError )then bSendAllRelayData := true;
         end;
 e   end;

{***************************************************************
*/



           }}}}}

}


//---------------------------------------------------------------------------
// Soros Port válaszra vár, legrosszabb esetben 0,1s után TimeOut-al kilép
//---------------------------------------------------------------------------
bool
bReadSerialMessageTimOut( char *chMessage, int *nHossz, CS_SerialComm *SComm, int nTimeOut )
{
//int nTimeOut = 100;
bool bRet = false;

   do
   {
       if( SComm->ReadMessage( chMessage, nHossz )  )
       {
           bRet = true;
       }
       else
       {
           Sleep(1);
       }

   }while( !bRet && (nTimeOut-- > 0) );

   Sleep( 2 ); //szükséges a hardware miatt

   return bRet;
}


//---------------------------------------------------------------------------
// Soros Portra Relay panelnak adatot küld Succes Választ vár
//---------------------------------------------------------------------------
bool
bSendMessageRelay_ReceiveSuccess( char *chMessage, int nSendHossz, CS_SerialComm *SComm  )
{
BOOL bRes = false;
char chSerialIn[2048];
int nRecHossz;

    SComm->SendMessage( chMessage, nSendHossz );  //Serial Send
    bySerial_Error++;

    if( bReadSerialMessageTimOut( chSerialIn, &nRecHossz, SComm, 100  ) )
    {
        if( chSerialIn[ nRecHossz-1 ] == HW_SUCCESS )
        {
            byHwWdtCounter = WDT_TIME;
            bySerial_Error = 0; // sikeres válasz
            bRes = true;
        }
    }
    return bRes;
}


//---------------------------------------------------------------------------
// Soros Portra LED Modulnak adatot küld Status Választ vár
//---------------------------------------------------------------------------
BYTE
bySendMessageLEDModul_ReceiveStatus( char *chMessage, int nSendHossz, CS_SerialComm *SComm )
{
char chSerialIn[2048];
int nRecHossz;
BYTE byStatus = 0;

    SComm->SendMessage( chMessage, nSendHossz );  //Serial Send
    bySerial_Error++;

    if( bReadSerialMessageTimOut( chSerialIn, &nRecHossz, SComm, 300  ) )
    {
        byStatus = (BYTE) chSerialIn[ nRecHossz-1 ];
        byHwWdtCounter = WDT_TIME;
        bySerial_Error = 0; // sikeres válasz
    }
    return byStatus;
}


//---------------------------------------------------------------------------
// Soros Port válaszra vár, legrosszabb esetben 0,3s után TimeOut-al kilép
//---------------------------------------------------------------------------
void
LED_Modul_Init( void  )
{
int i;

    for( i=0; i<szoliszam; i++ )
    {
        LED_Modul[ i ].bVan = true;
    }



}


/*
       SComm->SendMessage( chSerialOut, 4 );  //Serial Send

       if( bReadSerialMessageTimOut( chSerialIn, &nHossz, SComm, 300  ) )
       {
           if( chSerialIn[ nHossz-1 ] == HW_SUCCESS )
           {
               byHwWdtCounter = WDT_TIME;
               wRelay_mem = wRelay;
               bySerial_Error = 0; // sikeres válasz
           }
       }*/

//---------------------------------------------------------------------------


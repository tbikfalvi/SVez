//---------------------------------------------------------------------------

#ifndef HardwareKezelesH
#define HardwareKezelesH

#include "Classes.h"
#include "Database.h"

//---------------------------------------------------------------------------

void HW_Kezel( vector<CS_Solarium*> pSzolarium, CS_SerialComm *SComm );
bool bReadSerialMessageTimOut( char *chMessage, int *nHossz, CS_SerialComm *SComm, int nTimeOut );
bool bSendMessageRelay_ReceiveSuccess( char *chMessage, int nSendHossz, CS_SerialComm *SComm );
BYTE bySendMessageLEDModul_ReceiveStatus( char *chMessage, int nSendHossz, CS_SerialComm *SComm );



//---------------------------------------------------------------------------
#endif
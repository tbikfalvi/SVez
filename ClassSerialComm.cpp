//---------------------------------------------------------------------------

#include <vcl.h>

#include "Classes.h"
#include "Database.h"

#define EXCEPTION_OPEN_COM_PORT         0
#define EXCEPTION_GET_COM_PORT_CONFIG   1
#define EXCEPTION_SET_COM_PORT_CONFIG   2
#define EXCEPTION_CLOSE_COM_PORT        3
#define EXCEPTION_READ_COM_PORT			4
#define EXCEPTION_WRITE_COM_PORT		5
#define EXCEPTION_SET_COM_TIMEOUTS		6
#define EXCEPTION_INVALID_COM_HANDLE	7
#define EXCEPTION_GET_COM_PROP			8

//---------------------------------------------------------------------------
CS_SerialComm::CS_SerialComm()
{
   hComm = INVALID_HANDLE_VALUE;
   m_hPort = NULL;

   GetAvailableCommPorts();
}
//---------------------------------------------------------------------------
CS_SerialComm::~CS_SerialComm()
{
   ClosePort();
}
//---------------------------------------------------------------------------
void CS_SerialComm::GetAvailableCommPorts()
{
   char  channel[10];

   for(int i=0; i<32; i++)
   {
      HANDLE hcom;
      sprintf( channel, "COM%d", i+1 );

      if( (hcom = CreateFile( channel,
                              GENERIC_READ|GENERIC_WRITE,
                              0,
                              NULL,
                              OPEN_EXISTING,
                              FILE_FLAG_OVERLAPPED,
                              NULL )) != INVALID_HANDLE_VALUE )
      {
         CloseHandle( hcom );
         pComPorts.push_back(i+1);
      }
   }
}
//---------------------------------------------------------------------------
void CS_SerialComm::FillComboWithPorts( TComboBox *ComboBoxPort )
{
   char channel[10];

   ComboBoxPort->Clear();
   for( int i=0; i<(int)pComPorts.size(); i++ )
   {
      sprintf( channel, "COM%d", pComPorts[i] );
      ComboBoxPort->Items->Add( channel );
   }
}
//---------------------------------------------------------------------------
void CS_SerialComm::InitCommunication( int port, DWORD baudrate, DWORD parity )
{
   BaudRate   = baudrate;
   Parity     = parity;
   PortNumber = port;

//   if( OpenPort( false ) )
//   {
//      ClosePort();
//   }
}
//---------------------------------------------------------------------------
bool CS_SerialComm::OpenPort( bool bSync )
{
   LOG4( "START >> CS_SerialComm::OpenPort()" );

   bool bRet = false;
   char portName[20];

   memset( portName, 0, sizeof(portName) );
   sprintf( portName, "COM%d", PortNumber );

   if( bSync )
   {
      m_hPort = CreateFile( portName,                      // port name
                            GENERIC_READ | GENERIC_WRITE,  // access mode
                            0,                             // share mode
                            NULL,                          // default security attributes
                            OPEN_EXISTING,                 // creation mode
                            FILE_ATTRIBUTE_NORMAL,         // synchronous mode
                            NULL );                        // no file model
   }
   else
   {
      m_hPort = CreateFile( portName,                      // port name
                            GENERIC_READ | GENERIC_WRITE,  // access mode
                            0,                             // share mode
                            NULL,                          // default security attributes
                            OPEN_EXISTING,                 // creation mode
                            FILE_FLAG_OVERLAPPED,          // asynchronous mode
                            NULL );                        // no file model
   }

	if ( m_hPort == INVALID_HANDLE_VALUE )
   {
		m_hPort = NULL;
		throw ( EXCEPTION_OPEN_COM_PORT );
	}

	DCB dcb;

	if ( !GetCommState( m_hPort, &dcb ) )
   {
		::CloseHandle(m_hPort);
		throw ( EXCEPTION_GET_COM_PORT_CONFIG );
	}

// dcb.DCBlength;                         // sizeof(DCB)
   dcb.BaudRate = BaudRate;               // current baud rate
   dcb.fBinary = 1;                       // binary mode, no EOF check
   dcb.fParity = 1;                       // enable parity checking
   dcb.fOutxCtsFlow = 0;                  // CTS output flow control
   dcb.fOutxDsrFlow = 0;                  // DSR output flow control
// dcb.fDtrControl:2;                     // DTR flow control type
// dcb.fDsrSensitivity:1;                 // DSR sensitivity
// dcb.fTXContinueOnXoff:1;               // XOFF continues Tx
   dcb.fOutX = 0;                         // XON/XOFF out flow control
   dcb.fInX = 0;                          // XON/XOFF in flow control
// dcb.fErrorChar: 1;                     // enable error replacement
// dcb.fNull: 1;                          // enable null stripping
   dcb.fRtsControl = RTS_CONTROL_DISABLE; // RTS flow control
// dcb.fAbortOnError:1;                   // abort reads/writes on error
// dcb.fDummy2:17;                        // reserved
// dcb.wReserved;                         // not currently used
// dcb.XonLim;                            // transmit XON threshold
// dcb.XoffLim;                           // transmit XOFF threshold
   dcb.ByteSize = 8;                      // number of bits/byte, 4-8
   dcb.Parity = Parity;                   // 0-4=no,odd,even,mark,space
   dcb.StopBits = 0;                      // 0,1,2 = 1, 1.5, 2
// dcb.XonChar;                           // Tx and Rx XON character
// dcb.XoffChar;                          // Tx and Rx XOFF character
// dcb.ErrorChar;                         // error replacement character
// dcb.EofChar;                           // end of input character
// dcb.EvtChar;                           // received event character
// dcb.wReserved1;                        // reserved; do not use

  	if ( !SetCommState( m_hPort, &dcb ) )
   {
		throw ( EXCEPTION_SET_COM_PORT_CONFIG );
	}

   SetupComm( m_hPort, 512, 512 );

   COMMTIMEOUTS   timeout;

   memset( (char*)&timeout, 0, sizeof(COMMTIMEOUTS) );
   timeout.ReadIntervalTimeout = MAXDWORD;
   SetCommTimeouts( m_hPort, &timeout );

   bRet = true;

   LOG4( "END >> CS_SerialComm::OpenPort()" );

   return bRet;
}
//---------------------------------------------------------------------------
void CS_SerialComm::ClosePort()
{
	if (m_hPort != NULL && !CloseHandle(m_hPort)) {

		throw ( EXCEPTION_CLOSE_COM_PORT );
	}
   m_hPort = NULL;
/*
   if( hComm != INVALID_HANDLE_VALUE )
      CloseHandle( hComm );
   hComm = INVALID_HANDLE_VALUE;
*/
}
//---------------------------------------------------------------------------
VOID WINAPI FileIOCompletionRoutine( DWORD dwErrorCode,
                                           DWORD dwNumberOfBytesTransfered,
                                           LPOVERLAPPED lpOverlapped )
{
/*   FILE  *file = NULL;
   char  strMsg[100];

   memset( strMsg, 0, 100 );
   sprintf( strMsg, "E: %d", dwErrorCode );

   if( (file = fopen( "fsv.log", "at" )) != NULL )
   {
      fputs( FormatDateTime("yyyy/mm/dd\thh:nn:ss\t",Now()).c_str(), file );
      fputs( strMsg, file );
      fputs( "\n", file );
      fclose( file );
   }
   memset( strMsg, 0, 100 );
   sprintf( strMsg, "B: %d", dwNumberOfBytesTransfered );

   if( (file = fopen( "fsv.log", "at" )) != NULL )
   {
      fputs( FormatDateTime("yyyy/mm/dd\thh:nn:ss\t",Now()).c_str(), file );
      fputs( strMsg, file );
      fputs( "\n", file );
      fclose( file );
   }*/
}
//---------------------------------------------------------------------------
bool CS_SerialComm::SendMessage( char *Message, int nLength )
{
   LOG4( "CS_SerialComm::SendMessage" );

   bool bRet = false;

   bRet = Send( nLength, Message );
/*
   memset( (char*)(&Olpw), 0, sizeof(OVERLAPPED) );

   bRet = WriteFileEx( hComm, Message, nLength, &Olpw, FileIOCompletionRoutine );

LPVOID lpMsgBuf;

FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
               NULL,
               GetLastError(),
               MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
               (LPTSTR) &lpMsgBuf,
               0,
               NULL );
strLogMsg.sprintf( "%s", lpMsgBuf );
LOG4( strLogMsg );

   SleepEx( 1000, true );
*/
   return bRet;
}
//---------------------------------------------------------------------------
bool CS_SerialComm::ReadMessage( char *Message, int *nLength )
{
   LOG4( "CS_SerialComm::ReadMessage" );
   bool bRet = false;

   unsigned long readNumber;

   bRet = Receive ( 512, Message, &readNumber );
   *nLength = readNumber;
/*
   DWORD len,Hiba;

   memset( Puffer, 0, sizeof(Puffer) );
   bRet = ReadFile( hComm, Puffer, 512, &len, &Olpr );

LPVOID lpMsgBuf;

FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
               NULL,
               GetLastError(),
               MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
               (LPTSTR) &lpMsgBuf,
               0,
               NULL );
strLogMsg.sprintf( "%s", lpMsgBuf );
LOG4( strLogMsg );

   ClearCommError( hComm , &Hiba, NULL );
   *nLength = len;
   strncpy( Message, Puffer, len );
*/
   return bRet;
}
//---------------------------------------------------------------------------
bool CS_SerialComm :: Send ( unsigned int bytesNumber,
                      char *       bytesArray )
{
	unsigned long 	sentNumber;
	OVERLAPPED olWrite = {0};
	COMSTAT ComStat;
	DWORD lpErrors;
	DWORD dwRes;			// result of function WaitForSingleObject
	DWORD Timeout = 500; // WaitForSingleObject Timeout in ms, it can be INFINITE
	bool wRes;			// result of the write method

	if (!m_hPort) {

		return false;
	}


	// Create this write operation's OVERLAPPED structure's hEvent.
	olWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (olWrite.hEvent == NULL)
	  {
		// error creating overlapped event handle

		return false;
	  }


	if (!WriteFile ( m_hPort,           // port handle
                     bytesArray,      // read buffer
                     bytesNumber,     // bytes to read
                     &sentNumber,      // sent bytes
                     &olWrite ) )         // overlapped infos
	{
	if (GetLastError() != ERROR_IO_PENDING)
			{
			    // WriteFile failed, but isn't delayed. Report error and abort.

			  if (!CancelIo(m_hPort))
           {}

          if (!ClearCommError(m_hPort, &lpErrors , &ComStat))
           {}

			  wRes = false;
			}
	else
		  {
		     // Write is pending.

			 // The function returns if the interval elapses, even if the
			 // object's state is nonsignaled. If Timeout is zero,
			 // the function tests the object's state and returns immediately.
			 dwRes = WaitForSingleObject(olWrite.hEvent, Timeout);
			 switch(dwRes)
				 {
		        // OVERLAPPED structure's event has been signaled.
		        case WAIT_OBJECT_0:

					//If the last param is TRUE, the function does not return until the operation has been completed.
					if (!GetOverlappedResult(m_hPort, &olWrite, &sentNumber, TRUE))
						 {
							// Write fails

							if (!CancelIo(m_hPort))
                    {}

							if (!ClearCommError(m_hPort, &lpErrors , &ComStat))
                    {}

							wRes = false;
							break;
						 }
		             else
						 {

							// Write operation completed successfully.
							wRes = true;
							break;
						 }
				// 	The time-out interval elapsed, and the OVERLAPPED structure's event has NOT been signaled.
				case WAIT_TIMEOUT:

							if (!CancelIo(m_hPort))
                    {}

							if (!ClearCommError(m_hPort, &lpErrors , &ComStat))
                    {}
							wRes = false;
							break;
		        default:
							// An error has occurred in WaitForSingleObject.
					        // This usually indicates a problem with the
					        // OVERLAPPED structure's event handle.

							if (!CancelIo(m_hPort))
                     {}

							if (!ClearCommError(m_hPort, &lpErrors , &ComStat))
                     {}
							wRes = false;
							break;
				}
		  }

	return wRes;

  }


	else if ( sentNumber != bytesNumber ) {

		if (!CancelIo(m_hPort))
      {}
		if (!ClearCommError(m_hPort, &lpErrors , &ComStat))
      {}

		ShowLastWindowsError();
		return false;
	}


	return true;
}
//---------------------------------------------------------------------------
bool CS_SerialComm :: Receive ( unsigned int	bytesNumber,
                         char *			bytesArray,
						 unsigned long*	readNumber, OVERLAPPED *overLapped )
{

	if (!m_hPort) {

		return false;
	}

	if ( ! ReadFile ( m_hPort,           // port handle
					 bytesArray,      // read buffer
					 bytesNumber,     // bytes to read
					 readNumber,      // read bytes
					 overLapped ) )         // overlapped infos
	{

		ShowLastWindowsError();
		return false;
	} else if (!(*readNumber)) {

		return true;
	}

	return true;
}
//---------------------------------------------------------------------------
bool CS_SerialComm::ShowLastWindowsError(void) {
	LPVOID 		lpMsgBuf=NULL;
	char		chMsg[512];


	if (!FormatMessage(
		    FORMAT_MESSAGE_ALLOCATE_BUFFER |
		    FORMAT_MESSAGE_FROM_SYSTEM |
		    FORMAT_MESSAGE_IGNORE_INSERTS,
		    NULL,
		    ::GetLastError(),
		    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		    (LPTSTR) &lpMsgBuf,
		    0,
		    NULL ))
	{

		return false;
	} else {

	}

	// Free the buffer.
	if (lpMsgBuf) LocalFree( lpMsgBuf );

	return true;
}
//---------------------------------------------------------------------------

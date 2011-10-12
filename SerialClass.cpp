
#include <stdio.h>

#include "SerialClass.h"

Com422 :: Com422 ( char * portName,
                   int    baudRate,
                   int    parity,
                   int    dataBits,
                   int    stopBits,
				   bool   sync)
{
	DCB dcb;

	if (!sync)
	  {

			m_hPort = CreateFile ( portName,                      // port name
					              GENERIC_READ | GENERIC_WRITE,  // access mode
								  0,                             // share mode
								  NULL,                          // default security attributes
								  OPEN_EXISTING,                 // creation mode
		                          FILE_ATTRIBUTE_NORMAL,         // synchronous mode
					              NULL );                        // no file model
	  }
	else
	  {
			m_hPort = CreateFile ( portName,                      // port name
					              GENERIC_READ | GENERIC_WRITE,  // access mode
								  0,                             // share mode
								  NULL,                          // default security attributes
								  OPEN_EXISTING,                 // creation mode
		                          FILE_FLAG_OVERLAPPED,          // asynchronous mode
					              NULL );                        // no file model

	  }

	if ( m_hPort == INVALID_HANDLE_VALUE ) {
		m_hPort = NULL;

		throw ( EXCEPTION_OPEN_COM_PORT );
	}

	if ( ! GetCommState (m_hPort, &dcb) ) {

		::CloseHandle(m_hPort);
		throw ( EXCEPTION_GET_COM_PORT_CONFIG );
	}

	// Fill in the DCB

	dcb.BaudRate  = baudRate;
	dcb.fBinary   = 1;
	dcb.fParity   = 1;

	dcb.fOutxCtsFlow = 0;  // Ignore the CTS pin to send
	dcb.fOutxDsrFlow = 0;  // Ignore the DSR pin to send

	dcb.fOutX = 0;         // Don't use XON / XOFF
	dcb.fInX  = 0;         // Don't use XON / XOFF

	dcb.fRtsControl  = DTR_CONTROL_DISABLE;

	dcb.Parity    = parity;
	dcb.ByteSize  = dataBits;
	dcb.StopBits  = stopBits;

  	if ( ! SetCommState ( m_hPort, &dcb ) ) {

		throw ( EXCEPTION_SET_COM_PORT_CONFIG );
	}

}




Com422 :: ~Com422 ( )
{
	if (m_hPort != NULL && !CloseHandle(m_hPort)) {

		throw ( EXCEPTION_CLOSE_COM_PORT );
	}
}


bool Com422 :: Send ( unsigned int bytesNumber,
                      char *       bytesArray )
{
	unsigned long 	sentNumber;
	OVERLAPPED olWrite = {0};
	COMSTAT ComStat;
	DWORD lpErrors;
	DWORD dwRes;			// result of function WaitForSingleObject
	DWORD Timeout = 1000; // WaitForSingleObject Timeout in ms, it can be INFINITE
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




bool Com422 :: Receive ( unsigned int	bytesNumber,
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


bool Com422::SetTimeouts	(	unsigned int iReadIntervalTimeout,
								unsigned int iReadTotalTimeoutMultiplier,
								unsigned int iReadTotalTimeoutConstant,
								unsigned int iWriteTotalTimeoutMultiplier,
								unsigned int iWriteTotalTimeoutConstant)
{

	COMMTIMEOUTS	sCommTimeouts;


	if (!m_hPort) {

		return false;
	}

	sCommTimeouts.ReadIntervalTimeout=iReadIntervalTimeout;
	sCommTimeouts.ReadTotalTimeoutConstant=iReadTotalTimeoutConstant;
	sCommTimeouts.ReadTotalTimeoutMultiplier=iReadTotalTimeoutMultiplier;
	sCommTimeouts.WriteTotalTimeoutMultiplier=iWriteTotalTimeoutMultiplier;
	sCommTimeouts.WriteTotalTimeoutConstant=iWriteTotalTimeoutConstant;

	if (!::SetCommTimeouts(m_hPort,&sCommTimeouts)) {

		return false;
	}


	return true;
}

bool Com422::SetCommunicationState(eComState eState,DWORD value) {

	DCB dcb;


	if (!m_hPort) {

		return false;
	}

	if ( ! GetCommState ( m_hPort, &dcb ) ) {

		return false;
	}

	switch (eState) {
		case eComDTRCtrl:
			dcb.fDtrControl  = value;
			break;
		default:

			break;
	}

	if ( ! SetCommState ( m_hPort, &dcb ) ) {

		return false;
	}


	return true;

}

bool Com422::GetCommunicationProperties(COMMPROP& sProperty) {


	if (!m_hPort) {

		return false;
	}

	if (!::GetCommProperties(m_hPort,&sProperty)) {

		return false;
	}


	return true;

}

bool Com422::ShowLastWindowsError(void) {
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

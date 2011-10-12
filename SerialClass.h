
#ifndef COM422_CLASS_H
#define COM422_CLASS_H

#define EXCEPTION_OPEN_COM_PORT         0
#define EXCEPTION_GET_COM_PORT_CONFIG   1
#define EXCEPTION_SET_COM_PORT_CONFIG   2
#define EXCEPTION_CLOSE_COM_PORT        3
#define EXCEPTION_READ_COM_PORT			4
#define EXCEPTION_WRITE_COM_PORT		5
#define EXCEPTION_SET_COM_TIMEOUTS		6
#define EXCEPTION_INVALID_COM_HANDLE	7
#define EXCEPTION_GET_COM_PROP			8

#include <windows.h>

class Com422
{
public :
	//Add more desired option here if needed
	//This is used in: SetCommunicationState
	enum eComState
	{
		eComDTRCtrl=0
	};


	//Constructor & Destructor
	Com422 (char	*portName,
            int		baudRate,
            int		parity,
            int		dataBits,
            int		stopBits,
			bool	sync );

	~Com422 ( );

	//I/O commands
	bool Send (unsigned int bytesNumber,char *bytesArray);
	bool Receive ( unsigned int bytesNumber,char *bytesArray, unsigned long *readNumber, OVERLAPPED *overLapped=NULL );


	//Get Commands
	bool GetCommunicationProperties(COMMPROP&);
	bool ShowLastWindowsError(void);
	
	//Set Commands
	//Default settings: return immediately (even if nothing received)
	bool SetTimeouts	(	unsigned int iReadIntervalTimeout=MAXDWORD,
							unsigned int iReadTotalTimeoutMultiplier=0,
							unsigned int iReadTotalTimeoutConstant=0,
							unsigned int iWriteTotalTimeoutMultiplier=2,
							unsigned int iWriteTotalTimeoutConstant=0);

	bool SetCommunicationState(eComState,DWORD);
	
	HANDLE GetCommHandle() const {return m_hPort;}

private :
   HANDLE m_hPort;

};

#endif
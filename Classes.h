//---------------------------------------------------------------------------

#ifndef SzolariumClassesH
#define SzolariumClassesH

#include <vector.h>
#include <ComCtrls.hpp>
#include "Database.h"

//---------------------------------------------------------------------------
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

#define MAX_MODUL_SZAM   15
//---------------------------------------------------------------------------
class CS_FileArchive
{
   protected:

   public:

      CS_FileArchive();
      ~CS_FileArchive();
};
//---------------------------------------------------------------------------
class CS_FileManagement
{
   protected:

      AnsiString  strLogFile;

      void LOG( AnsiString strLogMessage, int nLogLevel=0 );
      int CompareFiles( AnsiString strFile1, AnsiString strFile2 );

   public:

      AnsiString  strLogMsg;
      int         nLoggingLevel;

      bool        bIsDatabaseOk;
      int         nDatabaseCode;

      CS_FileManagement();
      ~CS_FileManagement();

      void EnCode( char *str, int size );
      void DeCode( char *str, int size );

      bool CheckAndCorrectDBFiles( char *strFileOriginal, int *nErrorMsgID );

      void LOG1( AnsiString strLogMessage );
      void LOG2( AnsiString strLogMessage );
      void LOG3( AnsiString strLogMessage );
      void LOG4( AnsiString strLogMessage );

      int ReadLogLevelFromRegistry();
      void WriteLogLevelToRegistry( int nLogLevel );
};
//---------------------------------------------------------------------------
class CS_Berlet : public CS_FileManagement
{
private:

   vector<typ_berlettipus>      BerletTipus;
   vector<typ_berlet>           Berlet;
   vector<typ_berlethasznalat>  BerletHasznalat;

   bool LoadDataFromFile();

public:

   AnsiString  sBerletTipusFile;
   AnsiString  sBerletFile;
   AnsiString  sBerletHasznalatFile;

   CS_Berlet();
   ~CS_Berlet();

   /****************************************************************************
   *
   * BÉRLET TÍPUSOK KEZELESE
   *
   ****************************************************************************/
   void AddBerletTipus( typ_berlettipus stTemp );
   void ModifyBerletTipus( typ_berlettipus stTemp );
   bool DeleteBerletTipus( int nID );
   typ_berlettipus GetBerletTipus( char *strNev );
   typ_berlettipus GetBerletTipus( int nCount );
   typ_berlettipus GetBerletTipusID( int nID );
   int GetIDBerletTipusAr( int nAr );
   int GetBerletTipusCount();
   bool SaveBerlettipus( const char *strFile );
   bool CheckBerlettipus( const char *strFile );

   /****************************************************************************
   *
   * BÉRLETEK KEZELESE
   *
   ****************************************************************************/
   void AddBerlet( typ_berlet stTemp );
   bool DeleteBerlet( char *strVonalkod, bool bNeedToSave=true );
   bool IsBerletExists( char *strVonalkod );
   typ_berlet GetBerlet( char *strVonalkod );
   typ_berlet GetBerletItem( DWORD dwCount );
   DWORD GetBerletCount();
   void SetBerletEgyseg( char *strVonalkod, int nEgyseg );
   int GetBerletEgyseg( char *strVonalkod );
   void DecreaseBerletEgyseg( char *strVonalkod, int nEgyseg );
   void IncreaseBerletEgyseg( char *strVonalkod, int nEgyseg );
   bool SaveBerlet( const char *strFile );
   bool CheckBerlet( const char *strFile );
   void SetPIN( char *strVonalkod, int nPin );

   /****************************************************************************
   *
   * BÉRLET HASZNÁLAT KEZELESE
   *
   ****************************************************************************/
   void AddBerletHasznalat( char *strVonalkod, int nEgyseg );
   bool DeleteBerletHasznalat( typ_berlethasznalat stTemp, bool bNeedToSave=true );
   typ_berlethasznalat GetBerletHasznalat( double dDate, char *strVonalkod );
   typ_berlethasznalat GetBerletHasznalatItem( DWORD dwCount );
   DWORD GetBerletHasznalatCount();
   bool SaveBerlethasznalat( const char *strFile );
   bool CheckBerlethasznalat( const char *strFile );
};
//---------------------------------------------------------------------------
class CS_Konyv : public CS_FileManagement
{
   private:

      vector<typ_konyv_general>      KonyvGeneral;
      vector<typ_konyv_szolarium>    KonyvSzolarium;

      void LoadDataFromFile();
      void SaveDataToFile();

   public:

      AnsiString  sKonyvGeneralFile;
      AnsiString  sKonyvSzolariumFile;

      CS_Konyv();
      ~CS_Konyv();

      double GetGeneralKonyvCount();
      typ_konyv_general GetGeneralKonyv( double dCount );
      typ_konyv_general GetGeneralKonyvID( double dID );
      void DeleteGeneralKonyv( double dID, bool bNeedToSave=true );
      void AddGeneralKonyv( double dMuszakID,
                            double dBerletFtBevetel,
                            double dTermekFtBevetel,
                            char *strMegjegyzes );
      bool SaveGeneralKonyv( const char *strFile );
      bool CheckGeneralKonyv( const char *strFile );

      double GetSzolariumKonyvCount();
      typ_konyv_szolarium GetSzolariumKonyv( double dCount );
      typ_konyv_szolarium GetSzolariumKonyvID( double dID );
      void DeleteSzolariumKonyv( double dID, bool bNeedToSave=true );
      void AddSzolariumKonyv( double dMuszakID,
                              int nSzolariumID,
                              double dUzemeltIdo,
                              double dUzemeltBerletIdo,
                              double dUzemeltBerletEgyseg,
                              double dUzemeltFtIdo,
                              double dUzemeltFt,
                              double dUzemeltMegszakitott,
                              double dCsoUzemora,
                              char *strSzolarium );
      bool SaveSolariumKonyv( const char *strFile );
      bool CheckSolariumKonyv( const char *strFile );
};
//---------------------------------------------------------------------------
class CS_Kosar : public CS_FileManagement
{
   private:

      vector<typ_kosar>    Kosar;

      bool LoadDataFromFile();

   public:

      AnsiString           sKosarFile;

      CS_Kosar();
      ~CS_Kosar();

      void AddKosar( typ_kosar stTemp );
      bool DeleteKosar( int nID );
      bool DeleteKosar( char *strVonalkod );
      void EmptyKosar();
      typ_kosar GetKosar( int nCount );
      typ_kosar GetKosarID( int nID );
      int GetKosarCount();
      int GetKosarAr();
      bool SaveDataToFile( const char *strFile );
      bool CheckDataToFile( const char *strFile );
};
//---------------------------------------------------------------------------
class CS_MainSettings : public CS_FileManagement
{
   private:

      typ_settings         stSettingsDefault;
      typ_settings         stSettings;
      typ_szolisettings    stSoliSettingsDefault;

      bool m_bPasswordRequired;

      bool LoadSettingsFromFile( const char *strFile );

   public:

      AnsiString           sSettingsFile;

      typ_szolisettings    stSoliSettings;
      int                  nGlobalLogLevel;
      bool                 bAutoSaveOnExit;
      bool                 bCardUseWithPIN;
      AnsiString           strVersionNumber;

//      bool                 bIsDatabaseOk;

      CS_MainSettings();
      ~CS_MainSettings();

      bool SaveSettingsToFile( const char *strFile );
      bool CheckSettingsToFile( const char *strFile );

      void SetCountSolarium( int nCount );
      int GetCountSolarium();
      int GetComPort();
      DWORD GetBaudRate();
      DWORD GetParity();
      void SaveCommParameters( int Port, DWORD BaudRate, DWORD Parity );
      bool IsAccessGranted( int Level, char *Password );
      char* GetAdminPassword();
      char* GetUserPassword();
      void SetPasswordRequired( bool bPasswordRequired );
      bool IsPasswordRequired();
      void ModifyPassword( int Level, char *Password );
      void SaveApplicationParameters( int Left, int Top, int VideoResolution );
      void SaveApplicationParameters( int Left, int Top );
      void GetApplicationParameters( int *Left, int *Top, int *VideoResolution );
      double GetCurrentMuszak();
      char* GetCurrentUser();
      void SetCurrentUser( char *strLoginNev );
      void ResetMuszak();
      void MuszakZaras();
      void SetIntegerValueInRegistry( AnsiString KeyName, int nValue );
      void SetStringValueInRegistry( AnsiString KeyName, AnsiString strValue );
      void SetBoolValueInRegistry( AnsiString KeyName, bool bValue );
      int GetIntegerValueFromRegistry( AnsiString KeyName, int nDefValue=0 );
      AnsiString GetStringValueFromRegistry( AnsiString KeyName, AnsiString strDefValue="" );
      bool GetBoolValueFromRegistry( AnsiString KeyName, bool bDefValue=false );
      void GetApplicationVersionNumber();
};
//---------------------------------------------------------------------------
class CS_Penztar : public CS_FileManagement
{
   private:

      typ_penztar                   Penztar;
      vector<typ_penztar_action>    PenztarAction;

      void LoadDataFromFile();
      bool SavePenztarCashMod( typ_user stUser, char Action, int nCash, char *strMegjegyzes );

   public:

      AnsiString           sPenztarFile;
      AnsiString           sPenztarLogFile;

      CS_Penztar();
      ~CS_Penztar();

      void LoadPenztar();
      void LoadPenztarLog();

      bool SaveDataToFile( const char *strFile );
      bool CheckDataToFile( const char *strFile );

      void PenztarNyitas( typ_user stUser, int nCash );
      void PenztarBevetel(  typ_user stUser, int nCash, char *strMegjegyzes );
      void PenztarKiadas( typ_user stUser, int nCash, char *strMegjegyzes );

      int GetPenztarNyitas();
      int GetPenztarEgyenleg();

      double GetPenztarActionCount();
      typ_penztar_action GetPenztarAction( double dCount );
      void DeletePenztarAction( double dDateTime, bool bNeedToSave=true );
      bool SavePenztarActions( const char *strFile );
      bool CheckPenztarActions( const char *strFile );
};
//---------------------------------------------------------------------------
class CS_SerialComm : public CS_FileManagement
{
   private:

      HANDLE m_hPort;
   	bool Send (unsigned int bytesNumber,char *bytesArray);
	   bool Receive ( unsigned int bytesNumber,char *bytesArray, unsigned long *readNumber, OVERLAPPED *overLapped=NULL );
   	bool ShowLastWindowsError(void);

      HANDLE         hComm;
      int            PortNumber;
      DWORD          BaudRate;
      DWORD          Parity;
      OVERLAPPED     Olpw;		   // adási struktúra
      OVERLAPPED     Olpr;		   // vételi struktúra
      char           Puffer[512]; //pufferek

      vector<int>    pComPorts;

      void GetAvailableCommPorts();
//      VOID WINAPI FileIOCompletionRoutine( DWORD dwErrorCode,
//                                           DWORD dwNumberOfBytesTransfered,
//                                           LPOVERLAPPED lpOverlapped );

   public:

      CS_SerialComm();
      ~CS_SerialComm();

      void FillComboWithPorts( TComboBox *ComboBoxPort );
      void InitCommunication( int port, DWORD baudrate, DWORD parity );
      bool OpenPort( bool bSync=true );
      bool SendMessage( char *Message, int nLength );
      bool ReadMessage( char *Message, int *nLength );
      void ClosePort();
};
//---------------------------------------------------------------------------
class CS_Solarium : public CS_FileManagement
{
private:

   bool           bDebugShowAllText;

   int            nSzolariumID;
   //---------------------------------------------------------
   // Allapotok
   //---------------------------------------------------------
   char           cSolariumStatus;        // Szolarium aktualis allapota
                                          // 0 - alap allapot
                                          // 1 - vetkozes
                                          // 2 - szaunazas
                                          // 3 - barnulas
                                          // 4 - utohutes
   int            nIdoVisszaszamlalas;
   int            nIdoKovStatus;
   int            nIdoBarnulas;
   int            nIdoMegszakitott;
   int            nIdoBerlet;
   int            nForintBarnulas;
   bool           bStatusSteril;
   bool           bCsoCsereSzukseges;
   bool           bFizetniKell;
   bool           bCsovekKikapcsolva;

   //---------------------------------------------------------
   // Megjelenites
   //---------------------------------------------------------
   bool                  bPanelSelected;

   vector<typ_berlethasznalat>   BerletHasznal;
   int                           nBerletEgyseg;

   double dUzemeltBerletIdo;
   double dUzemeltFt;

   void LoadDataFromFile();

   void StatuszBeallitas( char nStatus );

public:
   //---------------------------------------------------------
   // Szolarium Adatok
   //---------------------------------------------------------

   AnsiString            DataFileName;

   typ_szoliadat  stAdat;
   typ_szolisettings    stSoliSettings;
   double         dCurrentMuszak;

   TPanel        *PanelSzolarium;
   TPanel        *Panel_Nev;
   TLabel        *Label_Status;
   TLabel        *Label_Visszaszamlalas;
   TLabel        *Label_Ido;
   TLabel        *Label_Informacio;
   TLabel        *Label_Penz;
   TProgressBar  *ProgressBarCso;

   CS_Berlet     *pBerlet;
   CS_Konyv      *pKonyv;
   CS_Penztar    *pPenztar;
   bool           bStopped;

   CS_Solarium( TObject* FormParent,
                int nID,
                int Left,
                int Top,
                int Width,
                int Height );
   ~CS_Solarium();

   bool SaveDataToFile( const char *strFile );
   bool CheckDataToFile( const char *strFile );

   void Select();
   void Deselect();
   void ShowHideUzemora( bool bVisible );

   char StatuszLekerdezes();
   void StatuszUpdate();
   void StatuszUpdateImmediate();

   void UpdateExtendedView( TPanel *pPanelSzolarium,
                            TPanel *pPanel_Nev,
                            TLabel *pLabel_Status,
                            TLabel *pLabel_Visszaszamlalas,
                            TLabel *pLabel_Ido,
                            TLabel *pLabel_Informacio,
                            TLabel *pLabel_Penz,
                            TProgressBar *pProgressBarCso );

   void StatuszVetkozesStop();
   void StatuszSzaunaStop();
   int  GetSzoliIdo();
   int  GetBarnulasIdo();

   bool CheckBarnulasIdo( int nBarnulas, int *nForint );
   bool CheckKedvezmenyIdo();

   bool StatuszSteril();
   bool StatuszCsocserekell();
   bool StatuszFizetnikell();

   void Inditas();
   void Fizetve();
   void Steril();
   void Veszleallitas( typ_user stUser );
   void CsoCserelve();

   void Resize( int Left, int Top, int Width, int Height );
   void DataRefresh( bool bNeedToSave=false );

   void StartPrepare( typ_berlet stBerlet, int nBarnulas, int nForint );
   void StartPrepare( int nBarnulas, int nForint );
   void StartReset( typ_user stUser );
   bool GetBarnulasIdo( int nEgyseg, int *nBarnulas );
   int GetMaxBarnulas();
   int GetForintBarnulas();

   bool CsovekKikapcsolva();
};
//---------------------------------------------------------------------------
class CS_Termek : public CS_FileManagement
{
   private:

      vector<typ_termek>   Termek;

      void LoadDataFromFile();

   public:

      AnsiString           sTermekFile;

      CS_Termek();
      ~CS_Termek();

      bool SaveDataToFile( const char *strFile );
      bool CheckDataToFile( const char *strFile );

      void AddTermek( typ_termek stTemp );
      bool ModifyTermek( typ_termek stTemp );
      bool DeleteTermek( DWORD nID );
      typ_termek GetTermekItem( double nCount );
      typ_termek GetTermekId( DWORD nID );
      typ_termek GetTermekKod( char *strVonalkod );
      typ_termek GetTermekNev( char *strNev );
      double GetTermekCount();
      int GetTermekDarab( DWORD nID );
      bool SetTermekDarab( DWORD nID, int nDarab );
};
//---------------------------------------------------------------------------
class CS_TermekTipus : public CS_FileManagement
{
   private:

      vector<typ_termektipus>       TermekTipus;
      vector<typ_termektipusassign> TermekTipusAsg;

      void LoadDataFromFile();

   public:

      AnsiString                    sTermekTipusFile;
      AnsiString                    sTermekTipusAsgFile;

      CS_TermekTipus();
      ~CS_TermekTipus();

      void LoadTermektipus();
      void LoadTermektipusAsg();

      bool SaveDataToFile( const char *strFile );
      bool CheckDataToFile( const char *strFile );
      bool SaveDataToFileAsg( const char *strFile );
      bool CheckDataToFileAsg( const char *strFile );

      void AddTermekTipus( typ_termektipus stTemp );
      bool ModifyTermekTipus( typ_termektipus stTemp );
      bool DeleteTermekTipus( DWORD nID );
      typ_termektipus GetTermekTipusItem( double nCount );
      typ_termektipus GetTermekTipusId( DWORD nID );
      DWORD GetTermekTipusNev( char *strNev );
      double GetTermekTipusCount();

      void AddTermekTipusAsg( typ_termektipusassign stTemp );
      bool DeleteTermekTipusAsg( typ_termektipusassign stTemp );
      typ_termektipusassign GetTermekTipusAsgItem( double nCount );
      bool CheckTermekTipusAsg( typ_termektipusassign stTemp );
      double GetTermekTipusAsgCount();
};
//---------------------------------------------------------------------------
class CS_User : public CS_FileManagement
{
   private:

      CS_MainSettings         *pMainSettings;
      vector<typ_user>         User;

      vector<typ_userlevel>    sUserLevel;

      void LoadDataFromFile();

   public:

      AnsiString               sUserFile;

      CS_User( CS_MainSettings *MainSettings );
      ~CS_User();

      bool SaveDataToFile( const char *strFile );
      bool CheckDataToFile( const char *strFile );

      void AddUser( typ_user stTemp );
      bool ModifyUser( typ_user stTemp );
      bool DeleteUser( char *strLoginNev );
      typ_user GetUserItem( double dCount );
      typ_user GetUserID( double dID );
//      typ_user GetUserAzonosito( char *strAzonosito );
      typ_user GetUserLogin( char *strLoginNev );
      double GetUserCount();
      char* GetUserNev( char *strLoginNev );
      int GetUserLevel( char *strLoginNev );
      char* GetUserLevelStr( char *strLoginNev );
};
//---------------------------------------------------------------------------
class CS_Hardware : public CS_FileManagement
{
   private:

      char chPrevStatus[ 12 ];
      BYTE byLedModulOlvasasiHiba;
      BYTE byLedModulUjraindulas;
      BYTE byLedModulKikapcsTimer;

   public:

      vector<CS_Solarium*>     pSzolarium;
      CS_SerialComm           *SComm;

      bool DEMO;
      bool  bErrorMessageDisplayed;

      WORD wRelay;
      WORD wRelay_mem;
      BYTE bySerial_Error;
      BYTE byHwWdtCounter;
      BOOL bTest;
      bool bSendToModulPower_ON;
      bool bSendToModulPower_OFF;


      BOOL bEnableIRQ_Msg;
      char chModulMessage;

      //LED Modul
      typ_LED_Modul LED_Modul[ MAX_MODUL_SZAM ];

      CS_Hardware();
      ~CS_Hardware();

      void HW_Kezel();
      bool bReadSerialMessageTimOut( char *chMessage, int *nHossz, int nTimeOut );
      bool bSendMessageRelay_ReceiveSuccess( char *chMessage, int nSendHossz );
      BYTE bSendMessageRelay_Receive( char *chMessage, int nSendHossz );
      BYTE bySendMessageRelay_ReceiveData( char *chMessage, int nSendHossz );
      bool bSendMessageLEDModul_ReceiveStatus( char *chMessage,
                                               int nSendHossz,
                                               BYTE byCim,
                                               BYTE *byStatus );
      bool CS_Hardware::bSearchHardware( void );
      void LED_Modul_Init( BYTE bySzoliszam );
      BYTE byLedModulKeres( BYTE byCim );
      BOOL bSerialMessage( char *chMessage );
      void EnableModulIRQ();
      void DisableModulIRQ();

      BOOL bWriteEEprom( BYTE byStartAddress, char *chMessage );
      BOOL bReedEEprom( BYTE byStartAddress, char *chMessage );
};
//---------------------------------------------------------------------------
#endif
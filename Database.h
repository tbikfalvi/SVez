//---------------------------------------------------------------------------

#ifndef SzolariumDatabaseH
#define SzolariumDatabaseH

//---------------------------------------------------------------------------
#define BERLET_FILE_VERSION            "000.06.00"
#define BERLETHASZNALAT_FILE_VERSION   "000.01.00"
#define BERLETTIPUS_FILE_VERSION       "000.01.00"
#define KONYV_GENERAL_FILE_VERSION     "000.01.00"
#define KONYV_SZOLARIUM_FILE_VERSION   "000.04.00"
#define KOSAR_FILE_VERSION             "000.02.00"
#define PENZTAR_FILE_VERSION           "000.01.00"
#define SETTINGS_FILE_VERSION          "000.06.00"
#define SOLARIUM_FILE_VERSION          "000.03.00"
#define TERMEK_FILE_VERSION            "000.02.00"
#define TERMEKTIPUS_FILE_VERSION       "000.01.00"
#define USER_FILE_VERSION              "000.01.00"
//---------------------------------------------------------------------------
#define BERLET_FILE                    "brltfsv.dat"
#define BERLETHASZNALAT_FILE           "brlthsznltfsv.dat"
#define BERLETTIPUS_FILE               "brlttpsfsv.dat"
#define KONYVGENERAL_FILE              "gknyvfsv.dat"
#define KONYVSZOLARIUM_FILE            "sknyvfsv.dat"
#define KOSAR_FILE                     "ksrfsv.dat"
#define PENZTAR_FILE                   "pnztrfsv.dat"
#define PENZTARLOG_FILE                "pnztrlgfsv.dat"
#define SETTINGS_FILE                  "msfsv.dat"
#define SOLARIUM_FILE                  "sdfsv"
#define TERMEK_FILE                    "trmkfsv.dat"
#define TERMEKTIPUS_FILE               "trmktpsfsv.dat"
#define TERMEKTIPUSASG_FILE            "trmktpssgfsv.dat"
#define USER_FILE                      "srfsv.dat"
//---------------------------------------------------------------------------
#define STATUS_ALAP              0
#define STATUS_VETKOZES          1
#define STATUS_SZAUNAZAS         2
#define STATUS_BARNULAS          3
#define STATUS_UTOHUTES          4
#define STATUS_VARAKOZAS         9
//---------------------------------------------------------------------------
#define ACCESS_UNDEFINED_0       0
#define ACCESS_UNDEFINED_1       1
#define ACCESS_UNDEFINED_2       2
#define ACCESS_UNDEFINED_3       3
#define ACCESS_UNDEFINED_4       4
#define ACCESS_UNDEFINED_5       5
#define ACCESS_UNDEFINED_6       6
#define ACCESS_USER              7
#define ACCESS_ADMIN             8
#define ACCESS_ROOT              9
//---------------------------------------------------------------------------
#define ACTION_PENZTAR_NYITAS    1
#define ACTION_PENZTAR_BEVET     2
#define ACTION_PENZTAR_KIADAS    3
//---------------------------------------------------------------------------
#define LISTA_BERLET             1
#define LISTA_TERMEK             2
#define LISTA_FOKONYV            3
#define LISTA_PENZTAR            4
#define LISTA_NAPIKONYV          5
#define LISTA_MUSZAK             6
#define LISTA_BERLETHASZNALAT    7
#define LISTA_BERLETOSSZ         8
//---------------------------------------------------------------------------
#define ERROR_DB_FILE_MISSING    1
//---------------------------------------------------------------------------
//
//    ERROR structure
//
//---------------------------------------------------------------------------
typedef struct _typ_error
{
   int   nErrCode;
   int   nErrType;
   char  strErrText[100];
} typ_error;
//---------------------------------------------------------------------------
//
//    BERLET structure
//
//---------------------------------------------------------------------------
typedef struct _typ_berlet
{
   char  strVonalkod[20];
   char  strMegjegyzes[50];
   int   nBerletTipus;
   int   nEgyseg;
   int   nErvEv;
   int   nErvHo;
   int   nErvNap;
   int   nPin;
} typ_berlet;
//---------------------------------------------------------------------------
//
//    BERLETHASZNALAT structure
//
//---------------------------------------------------------------------------
typedef struct _typ_berlethasznalat
{
   char  strVonalkod[20];
   int   nEv;
   int   nHo;
   int   nNap;
   int   nOra;
   int   nPerc;
   int   nEgyseg;
} typ_berlethasznalat;
//---------------------------------------------------------------------------
//
//    BERLETTIPUS structure
//
//---------------------------------------------------------------------------
typedef struct _typ_berlettipus
{
   int   nID;
   int   nAr;
   int   nEgyseg;
   char  strNev[50];
   int   nErvTolEv;
   int   nErvTolHo;
   int   nErvTolNap;
   int   nErvIgEv;
   int   nErvIgHo;
   int   nErvIgNap;
   int   nErvNapok;
   bool  bSzolariumHaszn;
   int   nEgysegIdo;
} typ_berlettipus;
//---------------------------------------------------------------------------
//
//    IDOFORINT structure
//
//---------------------------------------------------------------------------
typedef struct _typ_idoforint
{
   int   nForint;
   int   nPerc;
} typ_idoforint;
//---------------------------------------------------------------------------
//
//    KONYV_GENERAL structure
//
//---------------------------------------------------------------------------
typedef struct _typ_konyv_general
{
   double   dID;
   double   dMuszakID;
   double   dStartDateTime;
   double   dStopDateTime;
   double   dBerletFtBevetel;
   double   dTermekFtBevetel;
   char     strMegjegyzes[1000];
} typ_konyv_general;
//---------------------------------------------------------------------------
//
//    KONYV_SZOLARIUM structure
//
//---------------------------------------------------------------------------
typedef struct _typ_konyv_szolarium
{
   double   dID;
   double   dMuszakID;
   int      nSzolariumID;
   char     strSzolarium[50];
   unsigned int   dUzemeltIdo;            // Idõk másodpercben
   unsigned int   dUzemeltBerletIdo;
   unsigned int   dUzemeltBerletEgyseg;
   unsigned int   dUzemeltFtIdo;
   unsigned int   dUzemeltFt;
   unsigned int   dUzemeltMegszakitott;
   unsigned int   dCsoUzemora;
} typ_konyv_szolarium;
//---------------------------------------------------------------------------
//
//    KOSAR structure
//
//---------------------------------------------------------------------------
typedef struct _typ_kosar
{
   int   nID;
   char  strVonalkod[20];
   int   nTipus;
   char  strNev[100];
   int   nAr;
   int   nDarab;
} typ_kosar;
//---------------------------------------------------------------------------
//
//    PENZTAR structure
//
//---------------------------------------------------------------------------
typedef struct _typ_penztar
{
   int      nCurrentCash;
   int      nStartingCash;
} typ_penztar;
//---------------------------------------------------------------------------
//
//    PENZTAR_ACTION structure
//
//---------------------------------------------------------------------------
typedef struct _typ_penztar_action
{
   DWORD    dID;
   double   dDateTime;
   char     strLoginNev[20];
   char     Action;
   int      nCash;
   char     strMegjegyzes[100];
} typ_penztar_action;
//---------------------------------------------------------------------------
//
//    SETTINGS structures
//
//---------------------------------------------------------------------------
typedef struct _typ_settings
{
   int      nCountSolarium;
   char     strPasswordAdmin[20];
   char     strPasswordUser[20];
   int      Left;
   int      Top;
   int      VideoResolution;
   int      ComPort;
   DWORD    BaudRate;
   DWORD    Parity;
   double   dCurrentMuszak;
   char     strCurrentUser[20];
} typ_settings;
//---------------------------------------------------------------------------
typedef struct _typ_settings_extview
{
   int      Left;
   int      Top;
   int      Height;
   int      Width;
} typ_settings_extview;
//---------------------------------------------------------------------------
//
//    SZOLIADAT structure
//
//---------------------------------------------------------------------------
typedef struct _typ_szoliadat
{
   char           strNev[50];
   bool           bInfraSzolarium;
   int            nIdoVetkozes;
   int            nIdoUtohutes;
   int            nIdoSzauna;
   int            nKedvezmenyIdoStart;
   int            nKedvezmenyIdoStop;
   int            nCsoUzemora;         // Csõ üzemóra másodpercben
   int            nCsoUzemoraMax;      // Maximum csõ üzemóra másodpercben
   bool           bShowCsoUzemora;
   int            nMaxBarnulas;
   typ_idoforint  stIdoForint[40];
   typ_idoforint  stIdoForintKedv[40];
} typ_szoliadat;
//---------------------------------------------------------------------------
typedef struct _typ_szolisettings
{
   int            StatusTop;
   int            StatusHeight;
   int            StatusFontSize;
   int            StatusFontColorDef;
   int            StatusFontColorPre;
   int            StatusFontColorUse;
   int            StatusFontHeight;
   int            VisszaszamlalasTop;
   int            VisszaszamlalasHeight;
   int            VisszaszamlalasFontSize;
   int            VisszaszamlalasFontColorDef;
   int            VisszaszamlalasFontColorPre;
   int            VisszaszamlalasFontColorUse;
   int            VisszaszamlalasFontHeight;
   int            IdoTop;
   int            IdoHeight;
   int            IdoFontSize;
   int            IdoFontColorDef;
   int            IdoFontColorPre;
   int            IdoFontColorUse;
   int            IdoFontHeight;
   int            InformacioTop;
   int            InformacioHeight;
   int            InformacioFontSize;
   int            InformacioFontColorDef;
   int            InformacioFontColorPre;
   int            InformacioFontColorUse;
   int            InformacioFontHeight;
   int            PenzTop;
   int            PenzHeight;
   int            PenzFontSize;
   int            PenzFontColorDef;
   int            PenzFontColorPre;
   int            PenzFontColorUse;
   int            PenzFontHeight;
   int            ColorDefault;
   int            ColorPrepare;
   int            ColorUsed;
   AnsiString     StatusFontName;
   AnsiString     VisszaszamlalasFontName;
   AnsiString     IdoFontName;
   AnsiString     InformacioFontName;
   AnsiString     PenzFontName;
} typ_szolisettings;
//---------------------------------------------------------------------------
//
//    TERMEK structure
//
//---------------------------------------------------------------------------
typedef struct _typ_termek
{
   DWORD nID;
   char  strVonalkod[20];
   char  strNev[100];
   int   nAr;
   int   nDarab;
   int   nArBeszerzes;
} typ_termek;
//---------------------------------------------------------------------------
//
//    TERMEKTIPUS structure
//
//---------------------------------------------------------------------------
typedef struct _typ_termektipus
{
   DWORD nID;
   char  strNev[100];
} typ_termektipus;
//---------------------------------------------------------------------------
//
//    TERMEKTIPUSASSIGN structure
//
//---------------------------------------------------------------------------
typedef struct _typ_termektipusassign
{
   DWORD nTermekID;
   DWORD nTTipusID;
} typ_termektipusassign;
//---------------------------------------------------------------------------
//
//    USER structure
//
//---------------------------------------------------------------------------
typedef struct _typ_user
{
   DWORD    dID;
   char     strAzonosito[20];
   char     strLoginNev[20];
   char     strNevCsalad[100];
   char     strJelszo[20];
   char     strMegjegyzes[1000];
   int      nUserLevel;
} typ_user;
//---------------------------------------------------------------------------
//
//    USERLEVEL structure
//
//---------------------------------------------------------------------------
typedef struct _typ_userlevel
{
   char     strUserLevel[25];
} typ_userlevel;
//---------------------------------------------------------------------------
//
//    LED Modul structure
//
//---------------------------------------------------------------------------
typedef struct _typ_LED_Modul
{
   bool  bVan;
   bool  bStop;
   bool  bSendIras;
   bool  bSendStart;
   bool  bSendEnd;
} typ_LED_Modul;

#endif

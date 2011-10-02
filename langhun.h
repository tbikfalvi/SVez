//---------------------------------------------------------------------------

#ifndef SzolariumLangDefinesH
#define SzolariumLangDefinesH

//---------------------------------------------------------------------------
   #define  STR_APPLICATION_CAPTION       "Szol�rium vez�rl�"
   #define  STR_APPLICATION_INIT          "Alkalmaz�s inicializ�l�sa ..."
   #define  STR_APPLICATION_INIT_OK       "Alkalmaz�s inicializ�l�sa ... OK"
   #define  STR_APPLICATION_START         "Alkalmaz�s ind�t�sa."

   #define  STR_COM_INIT                  "Soros port (COM%d) inicializ�l�s ..."
   #define  STR_COM_INIT_OK               "Soros port (COM%d) inicializ�l�sa ... OK"
   #define  STR_COM_OPEN                  "Soros port (COM%d) megnyit�sa ..."
   #define  STR_COM_OPEN_OK               "Soros port (COM%d) megnyit�sa ... OK"
   #define  STR_COM_OPEN_FAILED           "Soros port (COM%d) megnyit�sa ... HIBA"

   #define  STR_MODE_DEMO                 "DEMO m�d."

   #define  STR_HARDWARE_INIT             "Hardver inicializ�l�s."
   #define  STR_HARDWARE_CONNECT          "Kapcsolatfelv�tel a hardverrel ..."
   #define  STR_HARDWARE_CONNECT_OK       "Kapcsolatfelv�tel a hardverrel ... OK"
   #define  STR_HARDWARE_CONNECT_FAILED   "Kapcsolatfelv�tel a hardverrel ... HIBA"

   #define  STR_MODUL_CHECK               "Modulok ellen�rz�se."
   #define  STR_MODUL_X_CHECK             "Modul %d ellen�rz�se ..."
   #define  STR_MODUL_X_CHECK_OK          "Modul %d ellen�rz�se ... OK"
   #define  STR_MODUL_X_CHECK_FAILED      "Modul %d ellen�rz�se ... HIBA"
   #define  STR_MODUL_CHECK_FINISHED      "Modulok ellen�rz�se befejez�d�tt."

   #define  STR_ERR_HARDWARE_COMM         "\nHiba le�r�s: Hardver kommunik�ci�s hiba.\nHiba k�d: hwe001\n\nMegold�s: Ellen�rizze a hardver �ramell�t�s�t illetve\na hardver �s a sz�m�t�g�p k�z�tti kapcsolatot"
   #define  STR_ERR_UNABLE_TO_CONTINUE    "A program tov�bbi megfelel� m�k�d�se nem lehets�ges!\n"

   #define  STR_MSGBOX_ERROR              "Hiba"
   #define  STR_MSGBOX_INFORMATION        "Inform�ci�"
   #define  STR_MSGBOX_EXCALMATION        "Figyelmeztet�s"
   #define  STR_MSGBOX_QUESTION           "K�rd�s"
   #define  STR_MSGBOX_USERERROR          "Felhaszn�l�i hiba"

   #define  STR_MSG_ACCESS_DENIED         "Hozz�f�r�s megtagadva!"

   #define  STR_MSG_LEDMODUL_COMMERR      "LED Modul komunik�ci�s HIBA!"
   #define  STR_SYSTEM_ADMINISTRATOR      "Rendszer Adminisztr�tor"
   #define  STR_DEFAULT_ADMIN_COMMENT     "Programban t�rolt alap�rtelmezett adminisztr�tor.\r\nAdatainak m�dos�t�sa a jelsz� kiv�tel�vel nem lehets�ges."
   #define  STR_DEFAULT_OPERATOR_COMMENT  "Programban t�rolt alap�rtelmezett kezel�.\r\nAdatainak m�dos�t�sa a jelsz� kiv�tel�vel nem lehets�ges."
   #define  STR_CASSA_OPEN                "P�nzt�r nyit�s"
   #define  STR_SOLARIUM_X                "Szol�rium %d"
   #define  STR_STATUS_UNDRESS            "VETK�Z�S"
   #define  STR_STATUS_SAUNA              "SZAUN�Z�S"
   #define  STR_STATUS_WAIT               "V�RAKOZ�S"
   #define  STR_STATUS_SOLARIUM_USE       "BARNUL�S"
   #define  STR_STATUS_POSTPROCESS        "UT�H�T�S"
   #define  STR_TUBECHANGE_REQUIRED       "CS�CSERE SZ�KS�GES"
   #define  STR_NOT_STERIL                "NEM STERIL"
   #define  STR_STATUS_SOLARIUM_HALTED    "BARNUL�S (STOP)"

   //***************************************************************************
   // AdatbazisKezeles ablakhoz tartoz� sz�vegek
   #define  STR_MSG_NODELETE_TODAY        "Az aktu�lis nap adatait nem lehet t�r�lni!"
   #define  STR_MSG_ACTION_INFO           "�n a k�vetkez� m�veletet akarja v�grehajtani:\n\n\"%s\"\na \"%s - %s\" id�intervallumban\na \"%s\" adatb�zison."
   #define  STR_MSG_DELETE_CONFIRM        "Biztos benne, hogy j�l adta meg az adatokat\n�s v�gre akarja hajtani a m�veletet?"
   #define  STR_MSG_DELETE_SUMMARY        "Adatb�zisb�l t�r�lt elemek sz�ma: %.0f"

   //***************************************************************************
   // AdatBeolvasas ablakhoz tartoz� sz�vegek
   #define  STR_CAPTION_DATAREAD          "Adatbeolvas�s"
   #define  STR_CAPTION_VONALKOD_READ     "B�rlet / Term�k azonos�t� beolvas�sa"
   #define  STR_CAPTION_SOLTIME           "Barnul�si id� beolvas�sa"
   #define  STR_MSG_SOLTIME_OVERFLOW      "A teljes barnul�si id� nem haladhatja meg a maximum �rt�ket!"
   #define  STR_MSG_INVALID_SOLTIME_VALUE "A barnul�si id� \"%s\" megad�sa nem helyes!"

   //***************************************************************************
   // B�rletElad�s ablakhoz tartoz� sz�vegek
   #define  STR_MSG_MISSING_BARCODE       "Nem adta meg a b�rlet sorsz�m�t / vonalk�dj�t!"
   #define  STR_MSG_BARCODE_CARD_EXISTS   "Ilyen sorsz�mmal / vonalk�ddal m�r szerepel b�rlet az adatb�zisban!\nK�rem adjon meg egy m�sik sorsz�mot / vonalk�dot."
   #define  STR_MSG_BARCODE_PROD_EXISTS   "Ilyen vonalk�d m�r l�tezik az adatb�zisban a\n%s\nterm�khez rendelve.\n\nK�rem adjon meg egy m�sik vonalk�dot!"

   //***************************************************************************
   // B�rletHasznalat ablakhoz tartoz� sz�vegek
   #define  STR_CARD_DATE_EXPIRED         "A b�rlet �rv�nyess�ge lej�rt."
   #define  STR_CARD_NOMORE_UNIT          "A b�rleten m�r nincs felhaszn�lhat� egys�g."

   //***************************************************************************
   // B�rletKezeles ablakhoz tartoz� sz�vegek
   #define  STR_NAME                      "N�v"
   #define  STR_UNIT                      "Egys�g"
   #define  STR_PRICE                     "�r"
   #define  STR_BTN_MODIFY                "&M�dos�t�s"
   #define  STR_BTN_SAVE                  "&Ment�s"
   #define  STR_CARDTYPE_DELETE_CONFIRM   "Biztosan t�r�lni akarja a b�rlett�pust az adatb�zisb�l?"
   #define  STR_ERR_CARDTYPE_NOTEXISTS    "Nincs ilyen b�rlett�pus az adatb�zisban!"
   #define  STR_ERR_CARDTYPE_NAME_MISSING "Nem adta meg a b�rlett�pus nev�t."

   //***************************************************************************
   // Fizetes ablakhoz tartoz� sz�vegek
   #define  STR_MSG_USENUMBERONLY         "K�rem csak sz�mokat haszn�ljon!"

   //***************************************************************************
   // HardwareTeszt ablakhoz tartoz� sz�vegek
   #define  STR_MSG_RELAYPANEL_OK         "Rel� panel rendben!"
   #define  STR_MSG_RELAYPANEL_ERROR      "Rel� panel hiba!"
   #define  STR_MSG_LEDMODUL_SEARCH       "LED Modul keres�s:"
   #define  STR_MSG_LEDMODUL_X_OK         "LED modul %02d rendben       %02d"
   #define  STR_MSG_END                   "...... V�GE ......"
   #define  STR_MSG_LEDMODUL_X            "LED modul %02d "
   #define  STR_MSG_OK                    "rendben"
   #define  STR_MSG_LEDMODUL_X_ERROR      "%02d LED modul HIBA"
   #define  STR_MSG_MODULIRQ_INVESTIGATE  "Modul IRQ figyel�s: (30s)"

   //***************************************************************************
   // Kosar ablakhoz tartoz� sz�vegek
   #define  STR_CARD                      "B�rlet"
   #define  STR_PRODUCT                   "Term�k"
   #define  STR_SOLARIUM                  "Szol�rium"
   #define  STR_DESIGNATION               "Megnevez�s"
   #define  STR_UNITPRICE                 "Egys�g�r"
   #define  STR_COUNTOF                   "Darabsz�m"
   #define  STR_MSG_USESOL_DELETE_DENIED  "A szol�rium haszn�latot itt nem lehet t�r�lni!\nK�rem l�pjen ki a f�ablakra �s az ESC gomb lenyom�s�val\nvonja vissza a szol�rium haszn�latot."

   //***************************************************************************
   // Lista ablakhoz tartoz� sz�vegek
   #define  STR_CAPTION_CARDS             "B�rletek"
   #define  STR_CAPTION_CARDS_OBSOLETE    "Lej�r� b�rletek"
   #define  STR_CAPTION_CARDS_USE         "B�rlethaszn�lat"
   #define  STR_CAPTION_PRODUCTS          "Term�kek"
   #define  STR_CAPTION_BOOK_MAIN         "F�k�nyv"
   #define  STR_CAPTION_BOOK_DAY          "Napi k�nyv"
   #define  STR_CAPTION_BOOK_SHIFT        "M�szak k�nyv"
   #define  STR_CAPTION_BOOK_CASH         "P�nzt�rk�nyv"
   #define  STR_CAPTION_ALLSOLDCARD       "�sszes eladott b�rlet"
   #define  STR_CAPTION_DATESOLDCARD      "Eladott b�rletek �rv�nyess�g szerint sz�rt list�ja"
   #define  STR_CAPTION_USEDSOLDCARD      "Eladott b�rletek felhaszn�l�sainak list�ja"
   #define  STR_CAPTION_PRODUCTINSTOCK    "Rakt�r k�szletnyilv�ntart�sa"
   #define  STR_CAPTION_DATEMAINBOOK      "F�k�nyv lista d�tum szerinti sz�r�ssel"
   #define  STR_CAPTION_DATEDAYBOOK       "Napi k�nyv lista d�tum szerinti sz�r�ssel"
   #define  STR_CAPTION_IDSHIFTBOOK       "M�szak lista m�szak azonos�t� szerinti sz�r�ssel"
   #define  STR_CAPTION_CASHINOUT         "P�nzt�r bev�telek �s kiad�sok"
   #define  STR_LIST_ALL_CARDS            "<�sszes b�rlet>"
   #define  STR_BARCODE                   "Vonalk�d"
   #define  STR_CARD_TYPE                 "B�rlet t�pus"
   #define  STR_COMMENT                   "Megjegyz�s"
   #define  STR_VALID                     "�rv�nyes"
   #define  STR_CURR_UNIT                 "Akt. egys�g"
   #define  STR_DATE_TIME                 "D�tum / Id�"
   #define  STR_USED_UNIT                 "Felhaszn�lt egys�g"
   #define  STR_STOCK                     "K�szlet"
   #define  STR_DATE                      "D�tum"
   #define  STR_USER                      "Felhaszn�l�"
   #define  STR_EVENT                     "Esem�ny"
   #define  STR_SUM                       "�sszeg"
   #define  STR_OPEN                      "Nyit�s"
   #define  STR_INCOME                    "Bev�tel"
   #define  STR_OUTCOME                   "Kiv�t"
   #define  STR_CASH_CURRENT_VALUE        "P�nzt�r aktu�lis egyenlege"
   #define  STR_CAPTION_SOLUSED           "                  �zemelt                                              "
   #define  STR_CAPTION_SOL_SPACES        "Szol�rium                     "
   #define  STR_CAPTION_LIST_SOLTIMES     "�ssz. id�   B�rlet id�  B�rlet egys.  Ft. id�     Megszak�tott  Cs� �zem�ra"
   #define  STR_START                     "Kezd�s"
   #define  STR_STOP                      "Befejez�s"
   #define  STR_CARD_CURRENCY             "B�rlet (Ft.)"
   #define  STR_PRODUCT_CURRENCY          "Term�k (Ft.)"
   #define  STR_SOLARIUM_CURRENCY         "Szol�rium (Ft.)"
   #define  STR_SUM_CURRENCY              "�sszesen (Ft.)"
   #define  STR_LIST_SAVEDTOFILE          "A lista elmentve a %s �llom�nyba."

   //***************************************************************************
   // PasswordChange ablakhoz tartoz� sz�vegek
   #define  STR_MSG_INVALID_OLDPASS       "Nem megfelel� a R�gi jelsz�."
   #define  STR_MSG_MISSING_NEWPASS       "Nem adta meg az �j jelsz�t."
   #define  STR_MSG_TYPOERR_NEWPASS       "Nem j�l adta meg vagy elg�pelte az �j jelsz�t.\nK�rem g�pelje be m�gegyszer."

   //***************************************************************************
   // PasswordCheck ablakhoz tartoz� sz�vegek
   #define  STR_MSG_LOGINNAME_NOTEXISTS   "Ilyen felhaszn�l�n�v nem l�tezik az adatb�zisban!"
   #define  STR_MSG_INVALID_PASSWORD      "Nem megfelel� a megadott jelsz�!"

   //***************************************************************************
   // PenztarKezeles ablakhoz tartoz� sz�vegek
   #define  STR_CAPTION_PAYTOCASSA        "Befizet�s p�nzt�rba"
   #define  STR_TOTALCASH_INCOME          "P�nzt�rbev�tel �sszege (Ft.)"
   #define  STR_INVALID_NUMBER_ENTERED    "Hib�s a be�rt �rt�k! [%s]\nK�rem csak sz�mokat haszn�ljon!"
   #define  STR_NO_COMMENT                "Nincs megjegyz�s."
   #define  STR_CAPTION_GETFROMCASSA      "K�szp�nzkiv�t p�nzt�rb�l"
   #define  STR_TOTALCASH_OUTCOME         "K�szp�nzkiv�t �sszege (Ft.)"

   //***************************************************************************
   // SzolariumMain ablakhoz tartoz� sz�vegek
   #define  STR_ERR_COMM_WITH_HARDWARE    "Kommunik�ci�s hiba l�pett fel.\nK�rem ellen�rizze a k�belt a sz�m�t�g�p �s a hardver k�z�tt!\n\nNyomja meg az Ism�t gombot, ha �jra akar pr�b�lkozni\nNyomja meg a M�gsem gombot, ha ki akar l�pni a programb�l\n"
   #define  STR_ERR_SOLINUSE_CLOSEDENIED  "Nincs mindegyik szol�rium alap �llapotban!\nA program le�ll�t�sa nem lehets�ges."
   #define  STR_HINT_MODIFY_SOLARIUM_DATA "Szol�rium adatainak m�dos�t�sa"
   #define  STR_HINT_SOLINUSE_MODDENIED   "!!! Szol�rium nincs alap�llapotban !!! Adatm�dos�t�s nem lehets�ges !!!"
   #define  STR_MSG_BARCODE_NOTEXISTS     "A be�rt azonos�t� nem tal�lhat� az adatb�zisban."
   #define  STR_MSG_SOLTIME_NOTEXISTS     "Nincs ilyen id� intervallum a szol�riumhoz rendelve.\n\nK�rem adjon meg egy m�sik id�hosszt!"
   #define  STR_MSG_TIMETABLE_EMPTY       "Nincs kit�ltve a szol�rium Id�/Forint vagy\nKedvezm�nyes Id�/Forint t�bl�zata.\n\nK�rem t�ltse fel a megfelel� t�bl�zatot adatokkal!"
   #define  STR_PIECE                     " db. "
   #define  STR_MSG_CONFIRM_EXIT          "Biztos, hogy ki akar l�pni a programb�l?"

   //***************************************************************************
   // TermekKezeles ablakhoz tartoz� sz�vegek
   #define  STR_MSG_DELPRODUCT_CONFIRM    "Biztosan t�r�lni akarja a term�ket az adatb�zisb�l?"
   #define  STR_MSG_PRODNAME_MISSING      "Nem adta meg a term�k nev�t!"
   #define  STR_MSG_PRODBARCODE_MISSING   "Nem adta meg a term�k vonalk�dj�t!"
   #define  STR_MSG_PRODBARCODE_INUSE     "Ilyen vonalk�d m�r l�tezik az adatb�zisban a\n%s\nterm�khez rendelve.\n\nK�rem adjon meg egy m�sik vonalk�dot!"
   #define  STR_MSG_BARCODE_INUSE         "Ilyen sorsz�mmal / vonalk�ddal m�r szerepel b�rlet az adatb�zisban!\nK�rem adjon meg egy m�sik sorsz�mot / vonalk�dot."
   #define  STR_MSG_PRODPRICE_MISSING     "Nem adta meg a term�k �r�t!"
   #define  STR_MSG_PROD_NOTEXISTS        "Nincs ilyen term�k az adatb�zisban!"
   #define  STR_MSG_PRODCOUNT_INCREASE    "Term�k darabsz�m n�vel�se"
   #define  STR_MSG_WITH_PIECES           "Darabsz�mmal:"
   #define  STR_MSG_PRODCOUNT_DECREASE    "Term�k darabsz�m cs�kkent�se"

   //***************************************************************************
   // UserKezeles ablakhoz tartoz� sz�vegek
   #define  STR_IDENTIFIER                "Azonos�t�"
   #define  STR_USER_NAME                 "Felhaszn�l� neve"
   #define  STR_LOGIN_NAME                "Bejelentkez�si n�v"
   #define  STR_USERDELETE_CONFIRM        "Biztosan t�r�lni akarja a felhaszn�l�t az adatb�zisb�l?"
   #define  STR_USERPASS_MODIFY           "Felhaszn�l�i jelsz� m�dos�t�sa"
   #define  STR_ADMINISTRATOR             "Adminisztr�tor"
   #define  STR_OPERATOR                  "Kezel�"
   #define  STR_MSG_USERNAME_MISSING      "Nem adta meg a felhaszn�l� val�di nev�t!"
   #define  STR_MSG_LOGINNAME_MISSING     "Nem adta meg a felhaszn�l� bejelentkez�si nev�t!"
   #define  STR_MSG_LOGINNAME_INUSE       "Ilyen bejelentkez�si n�v m�r l�tezik az adatb�zisban a\n%s\nfelhaszn�l�hoz rendelve.\n\nK�rem adjon meg egy m�sik bejelentkez�si nevet!"
   #define  STR_MSG_USERSAVED_PASSEMPTY   "A felhaszn�l�t sikeresen felvett�k az adatb�zisba.\n\nA felhaszn�l�nak jelenleg nincs jelszava.\nA program biztons�gos m�k�d�se �rdek�ben\nk�rem adjon jelsz�t az �jonnan l�trehozott felhaszn�l�nak."
   #define  STR_MSG_USER_NOTEXISTS        "Nincs ilyen felhaszn�l� az adatb�zisban!"

   #define  STR_MSG_CARD_NOTEXISTS        "A rendszerben nincs b�rlett�pus t�rolva.\nB�rlett�pus hi�ny�ban nem lehet b�rletet eladni."

   #define  STR_ERR_UNABLE_CREATE_ARCHIVE "Nem siker�lt l�trehozni az arh�v k�nyvt�rat!\nK�rem l�pjen kapcsolatba a rendszer adminisztr�torral."
   #define  STR_MSG_SESSION_CLOSE         "M�szak z�r�s"
   #define  STR_ERR_UNABLE_DATAMOD        "!!! Szol�rium nincs alap�llapotban !!! Adatm�dos�t�s nem lehets�ges !!!"
   #define  STR_MSG_PASSWORD_CHANGE       "Jelsz� m�dos�t�sa"
   #define  STR_MSG_IMPORT_FINISHED       "A %s\n�llom�ny import�l�sa befejez�d�tt.\n\nAz adatb�zisba import�lt b�rletek sz�ma: %d\n\nAz adatb�zisban l�trehozott b�rlett�pusok sz�ma: %d\n\nK�rem ne feledkezzen meg az automatikusan felvett b�rlett�pusok\nadatainak m�dos�t�s�r�l �s a hi�nyz� adatok megad�s�r�l!"
   #define  STR_MSG_BARCODE_TOOSHORT      "A vonalk�d nem lehet 4 karaktern�l r�videbb!"

   #define  STR_INF_VERSION_NUMBER        "Verzi� : "

   #define  STR_CURRENCY                  "Ft."

   #define  STR_ERR_INVALID_SOLCOUNT      "\nAz alkalmaz�s adatai nem egyeznek a hardver adataival."

   #define  STR_INF_SOLARIUM_STOPPED      "haszn�lat el�tt le�ll�tva."

//---------------------------------------------------------------------------
#endif
 
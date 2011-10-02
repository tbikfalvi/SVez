//---------------------------------------------------------------------------

#ifndef SzolariumLangDefinesH
#define SzolariumLangDefinesH

//---------------------------------------------------------------------------
   #define  STR_APPLICATION_CAPTION       "Szolárium vezérlõ"
   #define  STR_APPLICATION_INIT          "Alkalmazás inicializálása ..."
   #define  STR_APPLICATION_INIT_OK       "Alkalmazás inicializálása ... OK"
   #define  STR_APPLICATION_START         "Alkalmazás indítása."

   #define  STR_COM_INIT                  "Soros port (COM%d) inicializálás ..."
   #define  STR_COM_INIT_OK               "Soros port (COM%d) inicializálása ... OK"
   #define  STR_COM_OPEN                  "Soros port (COM%d) megnyitása ..."
   #define  STR_COM_OPEN_OK               "Soros port (COM%d) megnyitása ... OK"
   #define  STR_COM_OPEN_FAILED           "Soros port (COM%d) megnyitása ... HIBA"

   #define  STR_MODE_DEMO                 "DEMO mód."

   #define  STR_HARDWARE_INIT             "Hardver inicializálás."
   #define  STR_HARDWARE_CONNECT          "Kapcsolatfelvétel a hardverrel ..."
   #define  STR_HARDWARE_CONNECT_OK       "Kapcsolatfelvétel a hardverrel ... OK"
   #define  STR_HARDWARE_CONNECT_FAILED   "Kapcsolatfelvétel a hardverrel ... HIBA"

   #define  STR_MODUL_CHECK               "Modulok ellenõrzése."
   #define  STR_MODUL_X_CHECK             "Modul %d ellenõrzése ..."
   #define  STR_MODUL_X_CHECK_OK          "Modul %d ellenõrzése ... OK"
   #define  STR_MODUL_X_CHECK_FAILED      "Modul %d ellenõrzése ... HIBA"
   #define  STR_MODUL_CHECK_FINISHED      "Modulok ellenõrzése befejezõdött."

   #define  STR_ERR_HARDWARE_COMM         "\nHiba leírás: Hardver kommunikációs hiba.\nHiba kód: hwe001\n\nMegoldás: Ellenõrizze a hardver áramellátását illetve\na hardver és a számítógép közötti kapcsolatot"
   #define  STR_ERR_UNABLE_TO_CONTINUE    "A program további megfelelõ mûködése nem lehetséges!\n"

   #define  STR_MSGBOX_ERROR              "Hiba"
   #define  STR_MSGBOX_INFORMATION        "Információ"
   #define  STR_MSGBOX_EXCALMATION        "Figyelmeztetés"
   #define  STR_MSGBOX_QUESTION           "Kérdés"
   #define  STR_MSGBOX_USERERROR          "Felhasználói hiba"

   #define  STR_MSG_ACCESS_DENIED         "Hozzáférés megtagadva!"

   #define  STR_MSG_LEDMODUL_COMMERR      "LED Modul komunikációs HIBA!"
   #define  STR_SYSTEM_ADMINISTRATOR      "Rendszer Adminisztrátor"
   #define  STR_DEFAULT_ADMIN_COMMENT     "Programban tárolt alapértelmezett adminisztrátor.\r\nAdatainak módosítása a jelszó kivételével nem lehetséges."
   #define  STR_DEFAULT_OPERATOR_COMMENT  "Programban tárolt alapértelmezett kezelõ.\r\nAdatainak módosítása a jelszó kivételével nem lehetséges."
   #define  STR_CASSA_OPEN                "Pénztár nyitás"
   #define  STR_SOLARIUM_X                "Szolárium %d"
   #define  STR_STATUS_UNDRESS            "VETKÕZÉS"
   #define  STR_STATUS_SAUNA              "SZAUNÁZÁS"
   #define  STR_STATUS_WAIT               "VÁRAKOZÁS"
   #define  STR_STATUS_SOLARIUM_USE       "BARNULÁS"
   #define  STR_STATUS_POSTPROCESS        "UTÓHÛTÉS"
   #define  STR_TUBECHANGE_REQUIRED       "CSÕCSERE SZÜKSÉGES"
   #define  STR_NOT_STERIL                "NEM STERIL"
   #define  STR_STATUS_SOLARIUM_HALTED    "BARNULÁS (STOP)"

   //***************************************************************************
   // AdatbazisKezeles ablakhoz tartozó szövegek
   #define  STR_MSG_NODELETE_TODAY        "Az aktuális nap adatait nem lehet törölni!"
   #define  STR_MSG_ACTION_INFO           "Ön a következõ mûveletet akarja végrehajtani:\n\n\"%s\"\na \"%s - %s\" idõintervallumban\na \"%s\" adatbázison."
   #define  STR_MSG_DELETE_CONFIRM        "Biztos benne, hogy jól adta meg az adatokat\nés végre akarja hajtani a mûveletet?"
   #define  STR_MSG_DELETE_SUMMARY        "Adatbázisból törölt elemek száma: %.0f"

   //***************************************************************************
   // AdatBeolvasas ablakhoz tartozó szövegek
   #define  STR_CAPTION_DATAREAD          "Adatbeolvasás"
   #define  STR_CAPTION_VONALKOD_READ     "Bérlet / Termék azonosító beolvasása"
   #define  STR_CAPTION_SOLTIME           "Barnulási idõ beolvasása"
   #define  STR_MSG_SOLTIME_OVERFLOW      "A teljes barnulási idõ nem haladhatja meg a maximum értéket!"
   #define  STR_MSG_INVALID_SOLTIME_VALUE "A barnulási idõ \"%s\" megadása nem helyes!"

   //***************************************************************************
   // BérletEladás ablakhoz tartozó szövegek
   #define  STR_MSG_MISSING_BARCODE       "Nem adta meg a bérlet sorszámát / vonalkódját!"
   #define  STR_MSG_BARCODE_CARD_EXISTS   "Ilyen sorszámmal / vonalkóddal már szerepel bérlet az adatbázisban!\nKérem adjon meg egy másik sorszámot / vonalkódot."
   #define  STR_MSG_BARCODE_PROD_EXISTS   "Ilyen vonalkód már létezik az adatbázisban a\n%s\ntermékhez rendelve.\n\nKérem adjon meg egy másik vonalkódot!"

   //***************************************************************************
   // BérletHasznalat ablakhoz tartozó szövegek
   #define  STR_CARD_DATE_EXPIRED         "A bérlet érvényessége lejárt."
   #define  STR_CARD_NOMORE_UNIT          "A bérleten már nincs felhasználható egység."

   //***************************************************************************
   // BérletKezeles ablakhoz tartozó szövegek
   #define  STR_NAME                      "Név"
   #define  STR_UNIT                      "Egység"
   #define  STR_PRICE                     "Ár"
   #define  STR_BTN_MODIFY                "&Módosítás"
   #define  STR_BTN_SAVE                  "&Mentés"
   #define  STR_CARDTYPE_DELETE_CONFIRM   "Biztosan törölni akarja a bérlettípust az adatbázisból?"
   #define  STR_ERR_CARDTYPE_NOTEXISTS    "Nincs ilyen bérlettípus az adatbázisban!"
   #define  STR_ERR_CARDTYPE_NAME_MISSING "Nem adta meg a bérlettípus nevét."

   //***************************************************************************
   // Fizetes ablakhoz tartozó szövegek
   #define  STR_MSG_USENUMBERONLY         "Kérem csak számokat használjon!"

   //***************************************************************************
   // HardwareTeszt ablakhoz tartozó szövegek
   #define  STR_MSG_RELAYPANEL_OK         "Relé panel rendben!"
   #define  STR_MSG_RELAYPANEL_ERROR      "Relé panel hiba!"
   #define  STR_MSG_LEDMODUL_SEARCH       "LED Modul keresés:"
   #define  STR_MSG_LEDMODUL_X_OK         "LED modul %02d rendben       %02d"
   #define  STR_MSG_END                   "...... VÉGE ......"
   #define  STR_MSG_LEDMODUL_X            "LED modul %02d "
   #define  STR_MSG_OK                    "rendben"
   #define  STR_MSG_LEDMODUL_X_ERROR      "%02d LED modul HIBA"
   #define  STR_MSG_MODULIRQ_INVESTIGATE  "Modul IRQ figyelés: (30s)"

   //***************************************************************************
   // Kosar ablakhoz tartozó szövegek
   #define  STR_CARD                      "Bérlet"
   #define  STR_PRODUCT                   "Termék"
   #define  STR_SOLARIUM                  "Szolárium"
   #define  STR_DESIGNATION               "Megnevezés"
   #define  STR_UNITPRICE                 "Egységár"
   #define  STR_COUNTOF                   "Darabszám"
   #define  STR_MSG_USESOL_DELETE_DENIED  "A szolárium használatot itt nem lehet törölni!\nKérem lépjen ki a fõablakra és az ESC gomb lenyomásával\nvonja vissza a szolárium használatot."

   //***************************************************************************
   // Lista ablakhoz tartozó szövegek
   #define  STR_CAPTION_CARDS             "Bérletek"
   #define  STR_CAPTION_CARDS_OBSOLETE    "Lejáró bérletek"
   #define  STR_CAPTION_CARDS_USE         "Bérlethasználat"
   #define  STR_CAPTION_PRODUCTS          "Termékek"
   #define  STR_CAPTION_BOOK_MAIN         "Fõkönyv"
   #define  STR_CAPTION_BOOK_DAY          "Napi könyv"
   #define  STR_CAPTION_BOOK_SHIFT        "Mûszak könyv"
   #define  STR_CAPTION_BOOK_CASH         "Pénztárkönyv"
   #define  STR_CAPTION_ALLSOLDCARD       "Összes eladott bérlet"
   #define  STR_CAPTION_DATESOLDCARD      "Eladott bérletek érvényesség szerint szûrt listája"
   #define  STR_CAPTION_USEDSOLDCARD      "Eladott bérletek felhasználásainak listája"
   #define  STR_CAPTION_PRODUCTINSTOCK    "Raktár készletnyilvántartása"
   #define  STR_CAPTION_DATEMAINBOOK      "Fõkönyv lista dátum szerinti szûréssel"
   #define  STR_CAPTION_DATEDAYBOOK       "Napi könyv lista dátum szerinti szûréssel"
   #define  STR_CAPTION_IDSHIFTBOOK       "Mûszak lista mûszak azonosító szerinti szûréssel"
   #define  STR_CAPTION_CASHINOUT         "Pénztár bevételek és kiadások"
   #define  STR_LIST_ALL_CARDS            "<Összes bérlet>"
   #define  STR_BARCODE                   "Vonalkód"
   #define  STR_CARD_TYPE                 "Bérlet típus"
   #define  STR_COMMENT                   "Megjegyzés"
   #define  STR_VALID                     "Érvényes"
   #define  STR_CURR_UNIT                 "Akt. egység"
   #define  STR_DATE_TIME                 "Dátum / Idõ"
   #define  STR_USED_UNIT                 "Felhasznált egység"
   #define  STR_STOCK                     "Készlet"
   #define  STR_DATE                      "Dátum"
   #define  STR_USER                      "Felhasználó"
   #define  STR_EVENT                     "Esemény"
   #define  STR_SUM                       "Összeg"
   #define  STR_OPEN                      "Nyitás"
   #define  STR_INCOME                    "Bevétel"
   #define  STR_OUTCOME                   "Kivét"
   #define  STR_CASH_CURRENT_VALUE        "Pénztár aktuális egyenlege"
   #define  STR_CAPTION_SOLUSED           "                  Üzemelt                                              "
   #define  STR_CAPTION_SOL_SPACES        "Szolárium                     "
   #define  STR_CAPTION_LIST_SOLTIMES     "Össz. idõ   Bérlet idõ  Bérlet egys.  Ft. idõ     Megszakított  Csõ üzemóra"
   #define  STR_START                     "Kezdés"
   #define  STR_STOP                      "Befejezés"
   #define  STR_CARD_CURRENCY             "Bérlet (Ft.)"
   #define  STR_PRODUCT_CURRENCY          "Termék (Ft.)"
   #define  STR_SOLARIUM_CURRENCY         "Szolárium (Ft.)"
   #define  STR_SUM_CURRENCY              "Összesen (Ft.)"
   #define  STR_LIST_SAVEDTOFILE          "A lista elmentve a %s állományba."

   //***************************************************************************
   // PasswordChange ablakhoz tartozó szövegek
   #define  STR_MSG_INVALID_OLDPASS       "Nem megfelelõ a Régi jelszó."
   #define  STR_MSG_MISSING_NEWPASS       "Nem adta meg az Új jelszót."
   #define  STR_MSG_TYPOERR_NEWPASS       "Nem jól adta meg vagy elgépelte az új jelszót.\nKérem gépelje be mégegyszer."

   //***************************************************************************
   // PasswordCheck ablakhoz tartozó szövegek
   #define  STR_MSG_LOGINNAME_NOTEXISTS   "Ilyen felhasználónév nem létezik az adatbázisban!"
   #define  STR_MSG_INVALID_PASSWORD      "Nem megfelelõ a megadott jelszó!"

   //***************************************************************************
   // PenztarKezeles ablakhoz tartozó szövegek
   #define  STR_CAPTION_PAYTOCASSA        "Befizetés pénztárba"
   #define  STR_TOTALCASH_INCOME          "Pénztárbevétel összege (Ft.)"
   #define  STR_INVALID_NUMBER_ENTERED    "Hibás a beírt érték! [%s]\nKérem csak számokat használjon!"
   #define  STR_NO_COMMENT                "Nincs megjegyzés."
   #define  STR_CAPTION_GETFROMCASSA      "Készpénzkivét pénztárból"
   #define  STR_TOTALCASH_OUTCOME         "Készpénzkivét összege (Ft.)"

   //***************************************************************************
   // SzolariumMain ablakhoz tartozó szövegek
   #define  STR_ERR_COMM_WITH_HARDWARE    "Kommunikációs hiba lépett fel.\nKérem ellenõrizze a kábelt a számítógép és a hardver között!\n\nNyomja meg az Ismét gombot, ha újra akar próbálkozni\nNyomja meg a Mégsem gombot, ha ki akar lépni a programból\n"
   #define  STR_ERR_SOLINUSE_CLOSEDENIED  "Nincs mindegyik szolárium alap állapotban!\nA program leállítása nem lehetséges."
   #define  STR_HINT_MODIFY_SOLARIUM_DATA "Szolárium adatainak módosítása"
   #define  STR_HINT_SOLINUSE_MODDENIED   "!!! Szolárium nincs alapállapotban !!! Adatmódosítás nem lehetséges !!!"
   #define  STR_MSG_BARCODE_NOTEXISTS     "A beírt azonosító nem található az adatbázisban."
   #define  STR_MSG_SOLTIME_NOTEXISTS     "Nincs ilyen idõ intervallum a szoláriumhoz rendelve.\n\nKérem adjon meg egy másik idõhosszt!"
   #define  STR_MSG_TIMETABLE_EMPTY       "Nincs kitöltve a szolárium Idõ/Forint vagy\nKedvezményes Idõ/Forint táblázata.\n\nKérem töltse fel a megfelelõ táblázatot adatokkal!"
   #define  STR_PIECE                     " db. "
   #define  STR_MSG_CONFIRM_EXIT          "Biztos, hogy ki akar lépni a programból?"

   //***************************************************************************
   // TermekKezeles ablakhoz tartozó szövegek
   #define  STR_MSG_DELPRODUCT_CONFIRM    "Biztosan törölni akarja a terméket az adatbázisból?"
   #define  STR_MSG_PRODNAME_MISSING      "Nem adta meg a termék nevét!"
   #define  STR_MSG_PRODBARCODE_MISSING   "Nem adta meg a termék vonalkódját!"
   #define  STR_MSG_PRODBARCODE_INUSE     "Ilyen vonalkód már létezik az adatbázisban a\n%s\ntermékhez rendelve.\n\nKérem adjon meg egy másik vonalkódot!"
   #define  STR_MSG_BARCODE_INUSE         "Ilyen sorszámmal / vonalkóddal már szerepel bérlet az adatbázisban!\nKérem adjon meg egy másik sorszámot / vonalkódot."
   #define  STR_MSG_PRODPRICE_MISSING     "Nem adta meg a termék árát!"
   #define  STR_MSG_PROD_NOTEXISTS        "Nincs ilyen termék az adatbázisban!"
   #define  STR_MSG_PRODCOUNT_INCREASE    "Termék darabszám növelése"
   #define  STR_MSG_WITH_PIECES           "Darabszámmal:"
   #define  STR_MSG_PRODCOUNT_DECREASE    "Termék darabszám csökkentése"

   //***************************************************************************
   // UserKezeles ablakhoz tartozó szövegek
   #define  STR_IDENTIFIER                "Azonosító"
   #define  STR_USER_NAME                 "Felhasználó neve"
   #define  STR_LOGIN_NAME                "Bejelentkezési név"
   #define  STR_USERDELETE_CONFIRM        "Biztosan törölni akarja a felhasználót az adatbázisból?"
   #define  STR_USERPASS_MODIFY           "Felhasználói jelszó módosítása"
   #define  STR_ADMINISTRATOR             "Adminisztrátor"
   #define  STR_OPERATOR                  "Kezelõ"
   #define  STR_MSG_USERNAME_MISSING      "Nem adta meg a felhasználó valódi nevét!"
   #define  STR_MSG_LOGINNAME_MISSING     "Nem adta meg a felhasználó bejelentkezési nevét!"
   #define  STR_MSG_LOGINNAME_INUSE       "Ilyen bejelentkezési név már létezik az adatbázisban a\n%s\nfelhasználóhoz rendelve.\n\nKérem adjon meg egy másik bejelentkezési nevet!"
   #define  STR_MSG_USERSAVED_PASSEMPTY   "A felhasználót sikeresen felvettük az adatbázisba.\n\nA felhasználónak jelenleg nincs jelszava.\nA program biztonságos mûködése érdekében\nkérem adjon jelszót az újonnan létrehozott felhasználónak."
   #define  STR_MSG_USER_NOTEXISTS        "Nincs ilyen felhasználó az adatbázisban!"

   #define  STR_MSG_CARD_NOTEXISTS        "A rendszerben nincs bérlettípus tárolva.\nBérlettípus hiányában nem lehet bérletet eladni."

   #define  STR_ERR_UNABLE_CREATE_ARCHIVE "Nem sikerült létrehozni az arhív könyvtárat!\nKérem lépjen kapcsolatba a rendszer adminisztrátorral."
   #define  STR_MSG_SESSION_CLOSE         "Mûszak zárás"
   #define  STR_ERR_UNABLE_DATAMOD        "!!! Szolárium nincs alapállapotban !!! Adatmódosítás nem lehetséges !!!"
   #define  STR_MSG_PASSWORD_CHANGE       "Jelszó módosítása"
   #define  STR_MSG_IMPORT_FINISHED       "A %s\nállomány importálása befejezödött.\n\nAz adatbázisba importált bérletek száma: %d\n\nAz adatbázisban létrehozott bérlettípusok száma: %d\n\nKérem ne feledkezzen meg az automatikusan felvett bérlettípusok\nadatainak módosításáról és a hiányzó adatok megadásáról!"
   #define  STR_MSG_BARCODE_TOOSHORT      "A vonalkód nem lehet 4 karakternél rövidebb!"

   #define  STR_INF_VERSION_NUMBER        "Verzió : "

   #define  STR_CURRENCY                  "Ft."

   #define  STR_ERR_INVALID_SOLCOUNT      "\nAz alkalmazás adatai nem egyeznek a hardver adataival."

   #define  STR_INF_SOLARIUM_STOPPED      "használat elött leállítva."

//---------------------------------------------------------------------------
#endif
 
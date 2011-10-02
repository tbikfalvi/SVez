//---------------------------------------------------------------------------

#ifndef SzolariumLangDefinesH
#define SzolariumLangDefinesH

//---------------------------------------------------------------------------
   #define  STR_APPLICATION_CAPTION       "Vodic solarijuma"
   #define  STR_APPLICATION_INIT          "Osnovna upotreba ..."
   #define  STR_APPLICATION_INIT_OK       "Osnovna upotreba ... OK"
   #define  STR_APPLICATION_START         "Pokretanje upotrebe."

   #define  STR_COM_INIT                  "Upotreba rednog porta (COM%d) ..."
   #define  STR_COM_INIT_OK               "Upotreba rednog porta (COM%d) ... OK"
   #define  STR_COM_OPEN                  "Otvaranje rednog porta (COM%d) ..."
   #define  STR_COM_OPEN_OK               "Otvaranje rednog porta (COM%d) ... OK"
   #define  STR_COM_OPEN_FAILED           "Otvaranje rednog porta (COM%d) ... GRESKA"

   #define  STR_MODE_DEMO                 "DEMO mode."

   #define  STR_HARDWARE_INIT             "upotreba hardvera."
   #define  STR_HARDWARE_CONNECT          "povezivanje sa hardverom ..."
   #define  STR_HARDWARE_CONNECT_OK       "povezivanje sa hardverom ... OK"
   #define  STR_HARDWARE_CONNECT_FAILED   "povezivanje sa hardverom ... GRESKA"

   #define  STR_MODUL_CHECK               "provera modula."
   #define  STR_MODUL_X_CHECK             "provera modula %d ..."
   #define  STR_MODUL_X_CHECK_OK          "provera modula %d ... OK"
   #define  STR_MODUL_X_CHECK_FAILED      "provera modula %d ... GRESKA"
   #define  STR_MODUL_CHECK_FINISHED      "zavrsena provera modula."

   #define  STR_ERR_HARDWARE_COMM         "\nGreska: Greska u hardverskim komunikacijama\nKod greska: hwe001\n\nResenje: Proverite napon struje u \nhardveru, odnosno vezu sa kompjuterom"
   #define  STR_ERR_UNABLE_TO_CONTINUE    "Nastavak programa nije moguc!\n"

   #define  STR_MSGBOX_ERROR              "Greska"
   #define  STR_MSGBOX_INFORMATION        "Informacije"
   #define  STR_MSGBOX_EXCALMATION        "Upozorenje"
   #define  STR_MSGBOX_QUESTION           "Pitanje"
   #define  STR_MSGBOX_USERERROR          "Korisnicka greska"

   #define  STR_MSG_ACCESS_DENIED         "Pristup odbijen !"

   #define  STR_MSG_LEDMODUL_COMMERR      "Greska u led modul komunikaciji"
   #define  STR_SYSTEM_ADMINISTRATOR      "Sistem administrator"
   #define  STR_DEFAULT_ADMIN_COMMENT     "Menjane adminisztrator podataka nije moguce. Osim Lozinke\r\n"
   #define  STR_DEFAULT_OPERATOR_COMMENT  "Menjane korisnickih podataka nije moguce. Osim Lozinke\r\n"
   #define  STR_CASSA_OPEN                "Otvaranje kase"
   #define  STR_SOLARIUM_X                "Solarijum %d"
   #define  STR_STATUS_UNDRESS            "SKIDANJE"
   #define  STR_STATUS_SAUNA              "SAUNA"
   #define  STR_STATUS_WAIT               "CEKANJE"
   #define  STR_STATUS_SOLARIUM_USE       "SUNCANJE"
   #define  STR_STATUS_POSTPROCESS        "HLADJENJE"
   #define  STR_TUBECHANGE_REQUIRED       "Potrebna promena lampi"
   #define  STR_NOT_STERIL                "NIJE STERILNO"
   #define  STR_STATUS_SOLARIUM_HALTED    "SUNCANJE (STOP)"

   //***************************************************************************
   // AdatbazisKezeles ablakhoz tartozó szövegek
   #define  STR_MSG_NODELETE_TODAY        "Aktuelne dnevne podatke nije moguce brisati"
   #define  STR_MSG_ACTION_INFO           "Da li zelite da sprovedete sledeci postupak?:\n\n\"%s\"\na \"%s - %s\" vremenskom periodu\n \"%s\" na bazi podataka"
   #define  STR_MSG_DELETE_CONFIRM        "Da li ste sigurni da ste ispravno uneli podatke\ni da zelite da sprovedete postupak?"
   #define  STR_MSG_DELETE_SUMMARY        "Broj brisanih elemenata iz baze podataka: %.0f"

   //***************************************************************************
   // AdatBeolvasas ablakhoz tartozó szövegek
   #define  STR_CAPTION_DATAREAD          "Unos podataka"
   #define  STR_CAPTION_VONALKOD_READ     "Povlastica"
   #define  STR_CAPTION_SOLTIME           "Ucitavanje vremena suncanja"
   #define  STR_MSG_SOLTIME_OVERFLOW      "Ukupno vreme suncanja ne moze preci maksimalnu vrednost"
   #define  STR_MSG_INVALID_SOLTIME_VALUE "Zadato vreme suncanja \"%s\" nije moguce!"

   //***************************************************************************
   // BérletEladás ablakhoz tartozó szövegek
   #define  STR_MSG_MISSING_BARCODE       "Niste uneli broj povlastice"
   #define  STR_MSG_BARCODE_CARD_EXISTS   "Pod ovim rednim brojem vec postoji povlastica u bazi podataka!\nMolim vas unesite drugi redni broj."
   #define  STR_MSG_BARCODE_PROD_EXISTS   "Ovaj kod vec postoji u bazi podataka!\n%s Molim vas unesite drugi kod."
  
   //***************************************************************************
   // BérletHasznalat ablakhoz tartozó szövegek
   #define  STR_CARD_DATE_EXPIRED         "Upotreba povlastice istekla."
   #define  STR_CARD_NOMORE_UNIT          "Na povlastici vise ne postoje raspoloziva sredstva."

   //***************************************************************************
   // BérletKezeles ablakhoz tartozó szövegek
   #define  STR_NAME                      "Ime"
   #define  STR_UNIT                      "Jedinica"
   #define  STR_PRICE                     "Cena"
   #define  STR_BTN_MODIFY                "&Izmeniti"
   #define  STR_BTN_SAVE                  "&Sacuvati"
   #define  STR_CARDTYPE_DELETE_CONFIRM   "Da li ste sigurni da zelite da brisete ovu vrstu povlastice iz baze podataka?"
   #define  STR_ERR_CARDTYPE_NOTEXISTS    "U bazi podataka ne postoji ova vrsta povlastice."
   #define  STR_ERR_CARDTYPE_NAME_MISSING "Niste dali naziv povlastici."

   //***************************************************************************
   // Fizetes ablakhoz tartozó szövegek
   #define  STR_MSG_USENUMBERONLY         "Molim vas koristite samo brojeve!"

   //***************************************************************************
   // HardwareTeszt ablakhoz tartozó szövegek
   #define  STR_MSG_RELAYPANEL_OK         "Relay panel ok!"
   #define  STR_MSG_RELAYPANEL_ERROR      "Relay panel greska!"
   #define  STR_MSG_LEDMODUL_SEARCH       "Trazenje led modula:"
   #define  STR_MSG_LEDMODUL_X_OK         "LED modul %02d rendben       %02d"
   #define  STR_MSG_END                   "...... Kraj ......"
   #define  STR_MSG_LEDMODUL_X            "LED modul %02d "
   #define  STR_MSG_OK                    "u redu"
   #define  STR_MSG_LEDMODUL_X_ERROR      "%02d LED modul GRESKA"
   #define  STR_MSG_MODULIRQ_INVESTIGATE  "Modul IRQ: (30s)"

   //***************************************************************************
   // Kosar ablakhoz tartozó szövegek
   #define  STR_CARD                      "Povlastica"
   #define  STR_PRODUCT                   "Proizvod"
   #define  STR_SOLARIUM                  "solarijum"
   #define  STR_DESIGNATION               "Naziv"
   #define  STR_UNITPRICE                 "Jedinicna cena"
   #define  STR_COUNTOF                   "Kolicina"
   #define  STR_MSG_USESOL_DELETE_DENIED  "Koriscenje solarijuma ovde ne mozete brisati.\nMolim vas izadjite na glavnu stranu, kliknite na prozor\nzeljenog solarijuma i pritiskom na esc \ndugme ponistite koriscenje solarijuma."

   //***************************************************************************
   // Lista ablakhoz tartozó szövegek
   #define  STR_CAPTION_CARDS             "povlastica"
   #define  STR_CAPTION_CARDS_OBSOLETE    "povlastice koje isticu"
   #define  STR_CAPTION_CARDS_USE         "Koriscenje povlastice"
   #define  STR_CAPTION_PRODUCTS          "Proizvodi"
   #define  STR_CAPTION_BOOK_MAIN         "Glavna knjiga"
   #define  STR_CAPTION_BOOK_DAY          "Dnevna knjiga"
   #define  STR_CAPTION_BOOK_SHIFT        "Tehnicka knjiga"
   #define  STR_CAPTION_BOOK_CASH         "Knjiga blagajne"
   #define  STR_CAPTION_ALLSOLDCARD       "Sve prodate povlastice"
   #define  STR_CAPTION_DATESOLDCARD      "lista prodatih povlastica po datumima"
   #define  STR_CAPTION_USEDSOLDCARD      "lista prodatih povlastica po koriscenju"
   #define  STR_CAPTION_PRODUCTINSTOCK    "proizvodi na lageru"
   #define  STR_CAPTION_DATEMAINBOOK      "Glavna knjiga po datumima"
   #define  STR_CAPTION_DATEDAYBOOK       "Dnevna knjiga po datumima"
   #define  STR_CAPTION_IDSHIFTBOOK       "Technicka knjiga po datumima"
   #define  STR_CAPTION_CASHINOUT         "Rashodi i prihodi u blagajni"
   #define  STR_LIST_ALL_CARDS            "<Sve povlastice>"
   #define  STR_BARCODE                   "barkod"
   #define  STR_CARD_TYPE                 "Vrsta Povlastice"
   #define  STR_COMMENT                   "Primedba"
   #define  STR_VALID                     "Vazeci"
   #define  STR_CURR_UNIT                 "Trenutne jedinice"
   #define  STR_DATE_TIME                 "Datum\Vreme"
   #define  STR_USED_UNIT                 "Iskoriscene jedinice"
   #define  STR_STOCK                     "Lager"
   #define  STR_DATE                      "Datum"
   #define  STR_USER                      "Korisnik"
   #define  STR_EVENT                     "Dogadjaj"
   #define  STR_SUM                       "Suma"
   #define  STR_OPEN                      "Otvaranje"
   #define  STR_INCOME                    "Ulaz"
   #define  STR_OUTCOME                   "Izlaz"
   #define  STR_CASH_CURRENT_VALUE        "Aktuelno stanje u blagajni "
   #define  STR_CAPTION_SOLUSED           "                  Radio                                              "
   #define  STR_CAPTION_SOL_SPACES        "Solarium                     "
   #define  STR_CAPTION_LIST_SOLTIMES     "UkupnoVreme Vreme povl. Povlastice    Din vreme   Prekinuto koriscenje cevi"
   #define  STR_START                     "Start"
   #define  STR_STOP                      "Stop"
   #define  STR_CARD_CURRENCY             "Povlastica (Din)"
   #define  STR_PRODUCT_CURRENCY          "Proizvod (Din)"
   #define  STR_SOLARIUM_CURRENCY         "Solarium (Din)"
   #define  STR_SUM_CURRENCY              "Ukupno (Din)"
   #define  STR_LIST_SAVEDTOFILE          "List sacuvanu u %s fajl."

   //***************************************************************************
   // PasswordChange ablakhoz tartozó szövegek
   #define  STR_MSG_INVALID_OLDPASS       "Stara lozinka nije odgovarajuca."
   #define  STR_MSG_MISSING_NEWPASS       "Niste uneli novu lozinku."
   #define  STR_MSG_TYPOERR_NEWPASS       "niste dobro ukucali novu lozinku.\nMolim vas pokusajte ponovo."

   //***************************************************************************
   // PasswordCheck ablakhoz tartozó szövegek
   #define  STR_MSG_LOGINNAME_NOTEXISTS   "Ovo korisnicko ime ne postoji u bazi podataka"
   #define  STR_MSG_INVALID_PASSWORD      "Uneta lozinka nije odgovarajuca!"

   //***************************************************************************
   // PenztarKezeles ablakhoz tartozó szövegek
   #define  STR_CAPTION_PAYTOCASSA        "Uplata u blagajnu"
   #define  STR_TOTALCASH_INCOME          "Ukupan prihod u blagajni (Din)"
   #define  STR_INVALID_NUMBER_ENTERED    "Uneti iznos je pogresan! [%s]\nMolim vas koristite samo brojeve!"
   #define  STR_NO_COMMENT                "Nema primedbi"
   #define  STR_CAPTION_GETFROMCASSA      "Uzimanje para iz blagajne"
   #define  STR_TOTALCASH_OUTCOME         "kolicina uzete sume (Din)"

   //***************************************************************************
   // SzolariumMain ablakhoz tartozó szövegek
   #define  STR_ERR_COMM_WITH_HARDWARE    "Komunikacijska greska.\nMolim vas kontrolisite kabel izmedju racunara i hardvare\n\nAko opet ocete pokusati, pritisnite ponovo dugme...  \n"
   #define  STR_ERR_SOLINUSE_CLOSEDENIED  "Nije svaki solarium u osnovnom stanju\nIzkljucenje programa nije omoguceno."
   #define  STR_HINT_MODIFY_SOLARIUM_DATA "Menjanje solarium podataka"
   #define  STR_HINT_SOLINUSE_MODDENIED   "!!! Solarium nije u osnovnom stanju !!! Menjanje podatake nije moguce !!!"
   #define  STR_MSG_BARCODE_NOTEXISTS     "Unet bar kod nije u bazi podataka."
   #define  STR_MSG_SOLTIME_NOTEXISTS     "Nije dato takav vremenski interval za solarium.\n\nMolim vas unesite drugi vremenski interval!"
   #define  STR_MSG_TIMETABLE_EMPTY       "Nije ispunjen solarium Vreme/Din ili\nPopust interval Vreme/Din tabela.\n\nMolim pas popunite odgovarajucu tabelu!"
   #define  STR_PIECE                     " kol. "
   #define  STR_MSG_CONFIRM_EXIT          "Jeste li sigurni, da ocete zatvoriti program?"  

   //***************************************************************************
   // TermekKezeles ablakhoz tartozó szövegek
   #define  STR_MSG_DELPRODUCT_CONFIRM    "Da li ste sigurni da zelite da brisete proizvod iz baze podataka?"
   #define  STR_MSG_PRODNAME_MISSING      "Niste uneli naziv proizvoda!"
   #define  STR_MSG_PRODBARCODE_MISSING   "Niste uneli barkod proizvoda!"
   #define  STR_MSG_PRODBARCODE_INUSE     "Ovakav barkod vec postoji u bazi podataka. \n%s\n\n\nmolim vas unesite drugi barkod. !"
   #define  STR_MSG_BARCODE_INUSE         "Pod ovim rednim brojem/barkodom/ vec postoji povlastica u bazi podataka.\nMolim vas unesite drugi redni broj."
   #define  STR_MSG_PRODPRICE_MISSING     "Niste uneli cenu proizvoda!"
   #define  STR_MSG_PROD_NOTEXISTS        "U bazi podataka ne postoji ovakav proizvod!"
   #define  STR_MSG_PRODCOUNT_INCREASE    "Povecanje kolicine proizvoda"
   #define  STR_MSG_WITH_PIECES           "Sa kolicinom:"
   #define  STR_MSG_PRODCOUNT_DECREASE    "Smanjenje kolicine proizvoda"

   //***************************************************************************
   // UserKezeles ablakhoz tartozó szövegek
   #define  STR_IDENTIFIER                "Identifikator"
   #define  STR_USER_NAME                 "Korisnicko ime"
   #define  STR_LOGIN_NAME                "Prijavno ime"
   #define  STR_USERDELETE_CONFIRM        "Da li ste sigurni da zelite da brisete korisnika iz baze podataka?"
   #define  STR_USERPASS_MODIFY           "Promena lozinke korisnika"
   #define  STR_ADMINISTRATOR             "Administrator"
   #define  STR_OPERATOR                  "Operater"
   #define  STR_MSG_USERNAME_MISSING      "Niste uneli pravo ime korisnika!"
   #define  STR_MSG_LOGINNAME_MISSING     "Niste uneli korisnicko ime korisnika!"
   #define  STR_MSG_LOGINNAME_INUSE       "Ovo korisnicko ime vec postoji u bazi podataka.\n%s\n    \n\nMolim vas unesiti drugo!"
   #define  STR_MSG_USERSAVED_PASSEMPTY   "Korisnika smo uspesno uneli u bazu podataka.\n\nKorisnik trenutno nema lozinku.\nMolim vas a dajte lozinku korisniku!"
   #define  STR_MSG_USER_NOTEXISTS        "Ne postoji ovakav korisnik u bazi podataka"

   #define  STR_MSG_CARD_NOTEXISTS        "U bazi podataka nema tip povlastica...\n"

   #define  STR_ERR_UNABLE_CREATE_ARCHIVE "Nije uspelo da se kreiraju arhivne mape!\nMolim vas stupite u kontakt sa administratorom."
   #define  STR_MSG_SESSION_CLOSE         "Menjanje smene"
   #define  STR_ERR_UNABLE_DATAMOD        "!!! Solarium nije u osnovnom stanju !!! Menjanje podatake nije moguce !!!"
   #define  STR_MSG_PASSWORD_CHANGE       "Menjnje lozinke"
   #define  STR_MSG_IMPORT_FINISHED       " %s\n import podataka je zavrseno.\n\nU bazu podatake broj importiranih povlastica: %d\n\nBroj tipa novih povlastica: %d\n\n\n!"
   #define  STR_MSG_BARCODE_TOOSHORT      "Bar kod ne moze biti kraci od 4 karaktea!"

   #define  STR_INF_VERSION_NUMBER        "Verzija : "

   #define  STR_CURRENCY                  "Din." 

   #define  STR_ERR_INVALID_SOLCOUNT      "\nAz alkalmazás adatai nem egyeznek a hardver adataival."

   #define  STR_INF_SOLARIUM_STOPPED      "használat elött leállítva."

//---------------------------------------------------------------------------
#endif

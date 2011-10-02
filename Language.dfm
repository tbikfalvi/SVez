object FormLanguage: TFormLanguage
  Left = 308
  Top = 225
  BorderStyle = bsSingle
  Caption = 'Language'
  ClientHeight = 606
  ClientWidth = 461
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object LstLanguage: TListBox
    Left = 5
    Top = 5
    Width = 446
    Height = 596
    ItemHeight = 13
    Items.Strings = (
      'Szolárium vezérlõ'
      'Alkalmazás inicializálása ... OK'
      'Alkalmazás inicializálása ... HIBA'
      'Alkalmazás indítása.'
      'Soros port (COM%d) inicializálás ...'
      'Soros port (COM%d) inicializálása ... OK'
      'Soros port (COM%d) megnyitása ...'
      'Soros port (COM%d) megnyitása ... OK'
      'Soros port (COM%d) megnyitása ... HIBA'
      'DEMO mód.'
      'Hardver inicializálás.'
      'Kapcsolatfelvétel a hardverrel ...'
      'Kapcsolatfelvétel a hardverrel ... OK'
      'Kapcsolatfelvétel a hardverrel ... HIBA'
      'Modulok ellenõrzése.'
      'Modul %d ellenõrzése ...'
      'Modul %d ellenõrzése ... OK'
      'Modul %d ellenõrzése ... HIBA'
      'Modulok ellenõrzése befejezõdött.'
      
        '\nHiba leírás: Hardver kommunikációs hiba.\nHiba kód: hwe001\n\n' +
        'Megoldás: Ellenõrizze a hardver áramellátását illetve\na hardver' +
        ' és a számítógép közötti kapcsolatot'
      'A program további megfelelõ mûködése nem lehetséges!\n'
      'Hiba'
      'Információ'
      'Figyelmeztetés'
      'Kérdés'
      'Felhasználói hiba'
      'Hozzáférés megtagadva!'
      'LED Modul komunikációs HIBA!'
      'Rendszer Adminisztrátor'
      
        'Programban tárolt alapértelmezett adminisztrátor.\\r\\nAdatainak' +
        ' módosítása a jelszó kivételével nem lehetséges.'
      
        'Programban tárolt alapértelmezett kezelõ.\r\nAdatainak módosítás' +
        'a a jelszó kivételével nem lehetséges.'
      'Pénztár nyitás'
      'Szolárium %d'
      'VETKÕZÉS'
      'SZAUNÁZÁS'
      'VÁRAKOZÁS'
      'BARNULÁS'
      'UTÓHÛTÉS'
      'CSÕCSERE SZÜKSÉGES'
      'NEM STERIL'
      'BARNULÁS (STOP)'
      'Az aktuális nap adatait nem lehet törölni!'
      
        'Ön a következõ mûveletet akarja végrehajtani:\n\n\%s\\na \%s - %' +
        's\ idõintervallumban\na \%s\ adatbázison.'
      
        'Biztos benne, hogy jól adta meg az adatokat\nés végre akarja haj' +
        'tani a mûveletet?'
      'Adatbázisból törölt elemek száma: %.0f'
      'Adatbeolvasás'
      'Bérlet / Termék azonosító beolvasása'
      'Barnulási idõ beolvasása'
      'A teljes barnulási idõ nem haladhatja meg a maximum értéket!'
      'A barnulási idõ \%s\ megadása nem helyes!'
      'Nem adta meg a bérlet sorszámát / vonalkódját!'
      
        'Ilyen sorszámmal / vonalkóddal már szerepel bérlet az adatbázisb' +
        'an!\nKérem adjon meg egy másik sorszámot / vonalkódot.'
      
        'Ilyen vonalkód már létezik az adatbázisban a\n%s\ntermékhez rend' +
        'elve.\n\nKérem adjon meg egy másik vonalkódot!'
      'A bérlet érvényessége lejárt.'
      'A bérleten már nincs felhasználható egység.'
      'Név'
      'Egység'
      'Ár'
      '&Módosítás'
      '&Mentés'
      'Biztosan törölni akarja a bérlettípust az adatbázisból?'
      'Nincs ilyen bérlettípus az adatbázisban!'
      'Nem adta meg a bérlettípus nevét.'
      'Kérem csak számokat használjon!'
      'Relé panel rendben!'
      'Relé panel hiba!'
      'LED Modul keresés:'
      'LED modul %02d rendben %02d'
      '...... VÉGE ......'
      'LED modul %02d'
      'rendben'
      '%02d LED modul HIBA'
      'Modul IRQ figyelés: (30s)'
      'Bérlet'
      'Termék'
      'Szolárium'
      'Megnevezés'
      'Egységár'
      'Darabszám'
      
        'A szolárium használatot itt nem lehet törölni!\nKérem lépjen ki ' +
        'a fõablakra és az ESC gomb lenyomásával\nvonja vissza a szoláriu' +
        'm használatot.'
      'Bérletek'
      'Lejáró bérletek'
      'Bérlethasználat'
      'Termékek'
      'Fõkönyv'
      'Napi könyv'
      'Mûszak könyv'
      'Pénztárkönyv'
      'Összes eladott bérlet'
      'Eladott bérletek érvényesség szerint szûrt listája'
      'Eladott bérletek felhasználásainak listája'
      'Raktár készletnyilvántartása'
      'Fõkönyv lista dátum szerinti szûréssel'
      'Napi könyv lista dátum szerinti szûréssel'
      'Mûszak lista mûszak azonosító szerinti szûréssel'
      'Pénztár bevételek és kiadások'
      '<Összes bérlet>'
      'Vonalkód'
      'Bérlet típus'
      'Megjegyzés'
      'Érvényes'
      'Akt. egység'
      'Dátum / Idõ'
      'Felhasznált egység'
      'Készlet'
      'Dátum'
      'Felhasználó'
      'Esemény'
      'Összeg'
      'Nyitás'
      'Bevétel'
      'Kivét'
      'Pénztár aktuális egyenlege'
      
        '                  Üzemelt                                       ' +
        '       '
      'Szolárium                     '
      
        'Össz. idõ   Bérlet idõ  Bérlet egys.  Ft. idõ     Megszakított  ' +
        'Csõ üzemóra'
      'Kezdés'
      'Befejezés'
      'Bérlet (Ft.)'
      'Termék (Ft.)'
      'Szolárium (Ft.)'
      'Összesen (Ft.)'
      'A lista elmentve a %s állományba.'
      'Nem megfelelõ a Régi jelszó.'
      'Nem adta meg az Új jelszót.'
      
        'Nem jól adta meg vagy elgépelte az új jelszót.\nKérem gépelje be' +
        ' mégegyszer.'
      'Ilyen felhasználónév nem létezik az adatbázisban!'
      'Nem megfelelõ a megadott jelszó!'
      'Befizetés pénztárba'
      'Pénztárbevétel összege (Ft.)'
      'Hibás a beírt érték! [%s]\nKérem csak számokat használjon!'
      'Nincs megjegyzés.'
      'Készpénzkivét pénztárból'
      'Készpénzkivét összege (Ft.)'
      
        'Kommunikációs hiba lépett fel.\nKérem ellenõrizze a kábelt a szá' +
        'mítógép és a hardver között!\n\nNyomja meg az Ismét gombot, ha ú' +
        'jra akar próbálkozni\nNyomja meg a Mégsem gombot, ha ki akar lép' +
        'ni a programból\n'
      
        'Nincs mindegyik szolárium alap állapotban!\nA program leállítása' +
        ' nem lehetséges.'
      'Szolárium adatainak módosítása'
      
        '!!! Szolárium nincs alapállapotban !!! Adatmódosítás nem lehetsé' +
        'ges !!!'
      'A beírt azonosító nem található az adatbázisban.'
      
        'Nincs ilyen idõ intervallum a szoláriumhoz rendelve.\n\nKérem ad' +
        'jon meg egy másik idõhosszt!'
      
        'Nincs kitöltve a szolárium Idõ/Forint vagy\nKedvezményes Idõ/For' +
        'int táblázata.\n\nKérem töltse fel a megfelelõ táblázatot adatok' +
        'kal!'
      ' db.'
      'Biztos, hogy ki akar lépni a programból?'
      'Biztosan törölni akarja a terméket az adatbázisból?'
      'Nem adta meg a termék nevét!'
      'Nem adta meg a termék vonalkódját!'
      
        'Ilyen vonalkód már létezik az adatbázisban a\n%s\ntermékhez rend' +
        'elve.\n\nKérem adjon meg egy másik vonalkódot!'
      
        'Ilyen sorszámmal / vonalkóddal már szerepel bérlet az adatbázisb' +
        'an!\nKérem adjon meg egy másik sorszámot / vonalkódot.'
      'Nem adta meg a termék árát!'
      'Nincs ilyen termék az adatbázisban!'
      'Termék darabszám növelése'
      'Darabszámmal:'
      'Termék darabszám csökkentése'
      'Azonosító'
      'Felhasználó neve'
      'Bejelentkezési név'
      'Biztosan törölni akarja a felhasználót az adatbázisból?'
      'Felhasználói jelszó módosítása'
      'Adminisztrátor'
      'Kezelõ'
      'Nem adta meg a felhasználó valódi nevét!'
      'Nem adta meg a felhasználó bejelentkezési nevét!'
      
        'Ilyen bejelentkezési név már létezik az adatbázisban a\n%s\nfelh' +
        'asználóhoz rendelve.\n\nKérem adjon meg egy másik bejelentkezési' +
        ' nevet!'
      
        'A felhasználót sikeresen felvettük az adatbázisba.\n\nA felhaszn' +
        'álónak jelenleg nincs jelszava.\nA program biztonságos mûködése ' +
        'érdekében\nkérem adjon jelszót az újonnan létrehozott felhasznál' +
        'ónak.'
      'Nincs ilyen felhasználó az adatbázisban!'
      
        'A rendszerben nincs bérlettípus tárolva.\nBérlettípus hiányában ' +
        'nem lehet bérletet eladni.'
      
        'Nem sikerült létrehozni az arhív könyvtárat!\nKérem lépjen kapcs' +
        'olatba a rendszer adminisztrátorral.'
      'Mûszak zárás'
      
        '!!! Szolárium nincs alapállapotban !!! Adatmódosítás nem lehetsé' +
        'ges !!!'
      'Jelszó módosítása'
      
        'A %s\nállomány importálása befejezödött.\n\nAz adatbázisba impor' +
        'tált bérletek száma: %d\n\nAz adatbázisban létrehozott bérlettíp' +
        'usok száma: %d\n\nKérem ne feledkezzen meg az automatikusan felv' +
        'ett bérlettípusok\nadatainak módosításáról és a hiányzó adatok m' +
        'egadásáról!'
      'A vonalkód nem lehet 4 karakternél rövidebb!'
      'Verzió :'
      'Ft.'
      '\nAz alkalmazás adatai nem egyeznek a hardver adataival.'
      'használat elött leállítva.'
      'Biztosan törölni akarja a terméktípust az adatbázisból?'
      'Nincs ilyen terméktípus az adatbázisban!'
      'Nem adta meg a terméktípus nevét.'
      
        'Ilyen névvel már szerepel terméktípus az adatbázisban.\nKérem ad' +
        'jon meg egy másik nevet.'
      
        'Ilyen névvel már szerepel termék az adatbázisban.\nKérem adjon m' +
        'eg egy másik nevet.'
      'Besz. Ár'
      'A PIN kódnak 4 számjegyûnek kell lennie'
      'A megadott PIN kód nem egyezik a bérlethez tartozó PIN kóddal.'
      
        'A bérlethez még nincs megadva érvényes PIN kód.\nMeg akarja adni' +
        ' most az új, érvényes PIN kódot?'
      
        'Az alkalmazásban tárolt adatok nem egyeznek meg az adatbázissal.' +
        '\nAz alkalmazás automatikus mentést hajt végre.\nKérem várja meg' +
        ' a folyamat végét és próbálkozzon újra a kilépéssel.'
      
        'Az alkalmazásban tárolt adatok mentése az adatbázisba sikeresen ' +
        'befejezõdött.'
      
        'Az alkalmazásban tárolt adatok mentése az adatbázisba nem sikerü' +
        'lt.\nKérem próbálkozzon újra.'
      'Általános beállítások ... OK'
      'Általános beállítások ... HIBA'
      'Kosár adatbázis ... OK'
      'Kosár adatbázis ... HIBA'
      'Bérlettípus adatbázis ... OK'
      'Bérlettípus adatbázis ... HIBA'
      'Bérlet adatbázis ... OK'
      'Bérlet adatbázis ... HIBA'
      'Bérlethasználat adatbázis ... OK'
      'Bérlethasználat adatbázis ... HIBA')
    TabOrder = 0
  end
end

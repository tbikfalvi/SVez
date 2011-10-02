//
//command.inc
//
//*******************************************************************
//  Modul Parancsok         ( ~I2C Kommunikacio a Modulokal )
//*******************************************************************

//                                        SEND                    RECEIVE
//Command                                 Byte                     Byte
#define    SEND_TIME         0x01     // 1 command + 2 data      1 Status
#define    SEND_START        0x02     // 1 command               1 Status
#define    SEND_END          0x03     // 1 command               1 Status
#define    GET_STATUS        0x04     // 1 command               1 Status
#define    GET_TIME          0x05     // 1 command               1 Status
#define    SEND_SET_ADDR     0x06     // 0xa5 0x99   3 command               1 Status
#define    SEND_UTOHUTES_END 0x07     // 1 command               1 Status

     
//Command Byte   ---------------------------------
//               | 4bit address  |  4bit command |
//               ---------------------------------


//Response  STATUS Byte 
//            ----------------------------------------------------------
//            | 4bit address  | getint | Timer_On | ModStop | ModStart |
//            ----------------------------------------------------------

#define    ModStart     0
#define    ModStop      1
#define    Timer_On     2
#define    getint       3



//*******************************************************************
//*******************************************************************
//*******************************************************************


//Soros Vonal parancsok a SzRel-hez

//Direct relay commands:
//----------
#define SET_RELAY         '1'//, RelH,RelL, 0x5a                   4    1 ERR 


#define CLR_RELAY_TIMER   '3'//,0x09  5s-enkent torolni a PIC-ben  1    1 ERR_

#define READ_EEPROM       '4'//,ADDRESS                            2    1 Data
#define WRITE_EEPROM      '5'//,ADDRESS, DATA                      2    1 ERR


#define SEND_3BYTE_TO_MODUL '6'// Perc,  MPerc                     3    1 Status
#define SEND_1BYTE_TO_MODUL '7'//                                  1    1 Status

#define MODUL_ENABLE         0x10//                                1    1 ERR
#define MODUL_DISABLE        0x11//                                1    1 ERR

#define MODUL_POWER_ON       0x12//                                1    1 ERR
#define MODUL_POWER_OFF      0x13//                                1    1 ERR

                                                                  
#define SEARCH_HW         'S'//'H'                                 2    'Y'

#define  INIT_REQUEST  'R' // 2 |    'R'         |  4 db 'I' v laszra v r 100ms-os szunetekel
  // Ezt kovetoen a PIC -kuld 4 byte-ot (Random szamok), majd a PC visszakuldi a
  // "kisz molt ‚rt‚ket" 1Byte.
  // Pic v lasz SUCCESS / ERROR
  // Ha sikertelen volt a PC megvarja az 'RR' parancsot es lehet ismet prob lkozni.
  // 
  // A "Kisz molt ‚rt‚ket" a k”vetkez‹k‚pen kell kisz molni:
  //   Ezeket a szamokat irja ki a PIC 4db 'I' utan:
  //   Szam1, Szam2, Szam3, Szam4
  //
  // Ezt kovetoen ki kell szamolni az eredmenyt es visszakuldeni a PC-nek.
  //                        _________________________________
  //    Szam1  bitcsere     | 5 | 7 | 4 | 6 | 3 | 1 | 0 | 2 |  pl. 0x8c -> 0x49, 0xcb -> 0x5e
  //                        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //                                     Szam2                 XOR
  //                        ---------------------------------
  //               Result =
  //                                     Szam3                 ADD
  //                        ---------------------------------
  //               Result =
  //                                     Szam4                 XOR
  //                        ---------------------------------
  //         Final Result =
  //
  //
  //
  //  pl.  
  //   Szam1    Szam2    Szam3    Szam4       Final Result
  //    0x6c     0x6d     0x2c     0x74         0x67
  //    0x8b     0xa2     0xd4     0x7d         0x17
  //    0x64     0xf0     0x16     0x81         0x6f
  //



                                                                      
                                                                      
//Responses:                                                           
#define  HW_ERROR         0x00//      ERR_..
#define  HW_SUCCESS       0x01//      ERR_..
#define  HW_UNKN_COMM     0x02//      ERR_..


//Message
#define  MODUL_IRQ     'Q'//
#define  START_MESSAGE 'M'//

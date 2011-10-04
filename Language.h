//---------------------------------------------------------------------------

#ifndef LanguageH
#define LanguageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
/*
//#define LANG_SRB  "Szerb"

 //---------------------------------------------------------------------------
 //
 // Szövegek, feliratok, figyelmeztetések SZERB Nyelven
 //
 #ifdef LANG_SRB

   #include "langsrb.h"

 //---------------------------------------------------------------------------
 //
 // Szövegek, feliratok, figyelmeztetések MAGYAR Nyelven
 //
 #else
  #ifndef LANG_HUN
   #define LANG_HUN
  #endif

   #include "langhun.h"

 #endif
*/

 #define 	STR_APPLICATION_CAPTION	1
 #define 	STR_APPLICATION_INIT_OK	2
 #define 	STR_APPLICATION_INIT_HIBA	3
 #define 	STR_APPLICATION_START	4
 #define 	STR_COM_INIT	5
 #define 	STR_COM_INIT_OK	6
 #define 	STR_COM_OPEN	7
 #define 	STR_COM_OPEN_OK	8
 #define 	STR_COM_OPEN_FAILED	9
 #define 	STR_MODE_DEMO	10
 #define 	STR_HARDWARE_INIT	11
 #define 	STR_HARDWARE_CONNECT	12
 #define 	STR_HARDWARE_CONNECT_OK	13
 #define 	STR_HARDWARE_CONNECT_FAILED	14
 #define 	STR_MODUL_CHECK	15
 #define 	STR_MODUL_X_CHECK	16
 #define 	STR_MODUL_X_CHECK_OK	17
 #define 	STR_MODUL_X_CHECK_FAILED	18
 #define 	STR_MODUL_CHECK_FINISHED	19
 #define 	STR_ERR_HARDWARE_COMM	20
 #define 	STR_ERR_UNABLE_TO_CONTINUE	21
 #define 	STR_MSGBOX_ERROR	22
 #define 	STR_MSGBOX_INFORMATION	23
 #define 	STR_MSGBOX_EXCALMATION	24
 #define 	STR_MSGBOX_QUESTION	25
 #define 	STR_MSGBOX_USERERROR	26
 #define 	STR_MSG_ACCESS_DENIED	27
 #define 	STR_MSG_LEDMODUL_COMMERR	28
 #define 	STR_SYSTEM_ADMINISTRATOR	29
 #define 	STR_DEFAULT_ADMIN_COMMENT	30
 #define 	STR_DEFAULT_OPERATOR_COMMENT	31
 #define 	STR_CASSA_OPEN	32
 #define 	STR_SOLARIUM_X	33
 #define 	STR_STATUS_UNDRESS	34
 #define 	STR_STATUS_SAUNA	35
 #define 	STR_STATUS_WAIT	36
 #define 	STR_STATUS_SOLARIUM_USE	37
 #define 	STR_STATUS_POSTPROCESS	38
 #define 	STR_TUBECHANGE_REQUIRED	39
 #define 	STR_NOT_STERIL	40
 #define 	STR_STATUS_SOLARIUM_HALTED	41
 #define 	STR_MSG_NODELETE_TODAY	42
 #define 	STR_MSG_ACTION_INFO	43
 #define 	STR_MSG_DELETE_CONFIRM	44
 #define 	STR_MSG_DELETE_SUMMARY	45
 #define 	STR_CAPTION_DATAREAD	46
 #define 	STR_CAPTION_VONALKOD_READ	47
 #define 	STR_CAPTION_SOLTIME	48
 #define 	STR_MSG_SOLTIME_OVERFLOW	49
 #define 	STR_MSG_INVALID_SOLTIME_VALUE	50
 #define 	STR_MSG_MISSING_BARCODE	51
 #define 	STR_MSG_BARCODE_CARD_EXISTS	52
 #define 	STR_MSG_BARCODE_PROD_EXISTS	53
 #define 	STR_CARD_DATE_EXPIRED	54
 #define 	STR_CARD_NOMORE_UNIT	55
 #define 	STR_NAME	56
 #define 	STR_UNIT	57
 #define 	STR_PRICE	58
 #define 	STR_BTN_MODIFY	59
 #define 	STR_BTN_SAVE	60
 #define 	STR_CARDTYPE_DELETE_CONFIRM	61
 #define 	STR_ERR_CARDTYPE_NOTEXISTS	62
 #define 	STR_ERR_CARDTYPE_NAME_MISSING	63
 #define 	STR_MSG_USENUMBERONLY	64
 #define 	STR_MSG_RELAYPANEL_OK	65
 #define 	STR_MSG_RELAYPANEL_ERROR	66
 #define 	STR_MSG_LEDMODUL_SEARCH	67
 #define 	STR_MSG_LEDMODUL_X_OK	68
 #define 	STR_MSG_END	69
 #define 	STR_MSG_LEDMODUL_X	70
 #define 	STR_MSG_OK	71
 #define 	STR_MSG_LEDMODUL_X_ERROR	72
 #define 	STR_MSG_MODULIRQ_INVESTIGATE	73
 #define 	STR_CARD	74
 #define 	STR_PRODUCT	75
 #define 	STR_SOLARIUM	76
 #define 	STR_DESIGNATION	77
 #define 	STR_UNITPRICE	78
 #define 	STR_COUNTOF	79
 #define 	STR_MSG_USESOL_DELETE_DENIED	80
 #define 	STR_CAPTION_CARDS	81
 #define 	STR_CAPTION_CARDS_OBSOLETE	82
 #define 	STR_CAPTION_CARDS_USE	83
 #define 	STR_CAPTION_PRODUCTS	84
 #define 	STR_CAPTION_BOOK_MAIN	85
 #define 	STR_CAPTION_BOOK_DAY	86
 #define 	STR_CAPTION_BOOK_SHIFT	87
 #define 	STR_CAPTION_BOOK_CASH	88
 #define 	STR_CAPTION_ALLSOLDCARD	89
 #define 	STR_CAPTION_DATESOLDCARD	90
 #define 	STR_CAPTION_USEDSOLDCARD	91
 #define 	STR_CAPTION_PRODUCTINSTOCK	92
 #define 	STR_CAPTION_DATEMAINBOOK	93
 #define 	STR_CAPTION_DATEDAYBOOK	94
 #define 	STR_CAPTION_IDSHIFTBOOK	95
 #define 	STR_CAPTION_CASHINOUT	96
 #define 	STR_LIST_ALL_CARDS	97
 #define 	STR_BARCODE	98
 #define 	STR_CARD_TYPE	99
 #define 	STR_COMMENT	100
 #define 	STR_VALID	101
 #define 	STR_CURR_UNIT	102
 #define 	STR_DATE_TIME	103
 #define 	STR_USED_UNIT	104
 #define 	STR_STOCK	105
 #define 	STR_DATE	106
 #define 	STR_USER	107
 #define 	STR_EVENT	108
 #define 	STR_SUM	109
 #define 	STR_OPEN	110
 #define 	STR_INCOME	111
 #define 	STR_OUTCOME	112
 #define 	STR_CASH_CURRENT_VALUE	113
 #define 	STR_CAPTION_SOLUSED	114
 #define 	STR_CAPTION_SOL_SPACES	115
 #define 	STR_CAPTION_LIST_SOLTIMES	116
 #define 	STR_START	117
 #define 	STR_STOP	118
 #define 	STR_CARD_CURRENCY	119
 #define 	STR_PRODUCT_CURRENCY	120
 #define 	STR_SOLARIUM_CURRENCY	121
 #define 	STR_SUM_CURRENCY	122
 #define 	STR_LIST_SAVEDTOFILE	123
 #define 	STR_MSG_INVALID_OLDPASS	124
 #define 	STR_MSG_MISSING_NEWPASS	125
 #define 	STR_MSG_TYPOERR_NEWPASS	126
 #define 	STR_MSG_LOGINNAME_NOTEXISTS	127
 #define 	STR_MSG_INVALID_PASSWORD	128
 #define 	STR_CAPTION_PAYTOCASSA	129
 #define 	STR_TOTALCASH_INCOME	130
 #define 	STR_INVALID_NUMBER_ENTERED	131
 #define 	STR_NO_COMMENT	132
 #define 	STR_CAPTION_GETFROMCASSA	133
 #define 	STR_TOTALCASH_OUTCOME	134
 #define 	STR_ERR_COMM_WITH_HARDWARE	135
 #define 	STR_ERR_SOLINUSE_CLOSEDENIED	136
 #define 	STR_HINT_MODIFY_SOLARIUM_DATA	137
 #define 	STR_HINT_SOLINUSE_MODDENIED	138
 #define 	STR_MSG_BARCODE_NOTEXISTS	139
 #define 	STR_MSG_SOLTIME_NOTEXISTS	140
 #define 	STR_MSG_TIMETABLE_EMPTY	141
 #define 	STR_PIECE	142
 #define 	STR_MSG_CONFIRM_EXIT	143
 #define 	STR_MSG_DELPRODUCT_CONFIRM	144
 #define 	STR_MSG_PRODNAME_MISSING	145
 #define 	STR_MSG_PRODBARCODE_MISSING	146
 #define 	STR_MSG_PRODBARCODE_INUSE	147
 #define 	STR_MSG_BARCODE_INUSE	148
 #define 	STR_MSG_PRODPRICE_MISSING	149
 #define 	STR_MSG_PROD_NOTEXISTS	150
 #define 	STR_MSG_PRODCOUNT_INCREASE	151
 #define 	STR_MSG_WITH_PIECES	152
 #define 	STR_MSG_PRODCOUNT_DECREASE	153
 #define 	STR_IDENTIFIER	154
 #define 	STR_USER_NAME	155
 #define 	STR_LOGIN_NAME	156
 #define 	STR_USERDELETE_CONFIRM	157
 #define 	STR_USERPASS_MODIFY	158
 #define 	STR_ADMINISTRATOR	159
 #define 	STR_OPERATOR	160
 #define 	STR_MSG_USERNAME_MISSING	161
 #define 	STR_MSG_LOGINNAME_MISSING	162
 #define 	STR_MSG_LOGINNAME_INUSE	163
 #define 	STR_MSG_USERSAVED_PASSEMPTY	164
 #define 	STR_MSG_USER_NOTEXISTS	165
 #define 	STR_MSG_CARD_NOTEXISTS	166
 #define 	STR_ERR_UNABLE_CREATE_ARCHIVE	167
 #define 	STR_MSG_SESSION_CLOSE	168
 #define 	STR_ERR_UNABLE_DATAMOD	169
 #define 	STR_MSG_PASSWORD_CHANGE	170
 #define 	STR_MSG_IMPORT_FINISHED	171
 #define 	STR_MSG_BARCODE_TOOSHORT	172
 #define 	STR_INF_VERSION_NUMBER	173
 #define 	STR_CURRENCY	174
 #define 	STR_ERR_INVALID_SOLCOUNT	175
 #define 	STR_INF_SOLARIUM_STOPPED	176
 #define    STR_PRODUCTTYPE_DELETE_CONFIRM 177
 #define 	STR_ERR_PRODUCTTYPE_NOTEXISTS	178
 #define    STR_ERR_PRODUCTTYPE_NAME_MISSING 179
 #define    STR_ERR_PRODUCTTYPE_NAME_EXISTS 180
 #define    STR_MSG_PRODNAME_INUSE 181
 #define    STR_UNITPRICE_BUY 182
 #define    STR_PIN_MUST_4_DIGIT 183
 #define    STR_PIN_INVALID 184
 #define    STR_NO_VALID_PIN 185
 #define    STR_ERR_DATABASE_INCONSISTENCY 186
 #define    STR_ERR_DATABASE_SAVE_OK 187
 #define    STR_ERR_DATABASE_SAVE_ERROR 188
 #define    STR_ERR_GENERAL_SETTINGS_OK 189
 #define    STR_ERR_GENERAL_SETTINGS_HIBA 190
 #define    STR_ERR_KOSAR_OK 191
 #define    STR_ERR_KOSAR_HIBA 192
 #define    STR_ERR_BERLET_TIPUS_OK 193
 #define    STR_ERR_BERLET_TIPUS_HIBA 194
 #define    STR_ERR_BERLET_OK 195
 #define    STR_ERR_BERLET_HIBA 196
 #define    STR_ERR_BERLET_HASZNALAT_OK 197
 #define    STR_ERR_BERLET_HASZNALAT_HIBA 198

//---------------------------------------------------------------------------
class TFormLanguage : public TForm
{
__published:	// IDE-managed Components
   TListBox *LstLanguage;
private:	// User declarations
public:		// User declarations
   __fastcall TFormLanguage(TComponent* Owner);

   AnsiString LangStr( int LangId );
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLanguage *FormLanguage;
//---------------------------------------------------------------------------
#endif

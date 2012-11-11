//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "Classes.h"
#include "Database.h"
#include "SzolariumAdat.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSzolariumAdat *FormSzolariumAdat;
//---------------------------------------------------------------------------
__fastcall TFormSzolariumAdat::TFormSzolariumAdat(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSzolariumAdat::FormActivate(TObject *Sender)
{
   EditNev->SetFocus();
   CheckBoxInfraClick(Sender);
   TabControlTablazatChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormSzolariumAdat::FormShortCut(TWMKey &Msg, bool &Handled)
{
   if (Msg.CharCode == VK_RETURN)
   {
      Handled = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormSzolariumAdat::CheckBoxInfraClick(TObject *Sender)
{
   if( CheckBoxInfra->Checked )
   {
      EditIdoSzauna->Enabled = true;
   }
   else
   {
      EditIdoSzauna->Enabled = false;
   }
}
//---------------------------------------------------------------------------
void TFormSzolariumAdat::FillControlsWithData( typ_szoliadat stAdat )
{
   unsigned short nHour, nMin, nSec, nMSec;

   Now().DecodeTime( &nHour, &nMin, &nSec, &nMSec );
   if( stAdat.nKedvezmenyIdoStart <= (nHour*60+nMin) &&
       (nHour*60+nMin) <= stAdat.nKedvezmenyIdoStop )
   {
      TabControlTablazat->TabIndex = 1;
   }
   else
   {
      TabControlTablazat->TabIndex = 0;
   }

   EditNev->Text = AnsiString( stAdat.strNev );
   EditIdoVetkozes->Text = AnsiString( stAdat.nIdoVetkozes );
   EditIdoUtohutes->Text = AnsiString( stAdat.nIdoUtohutes );
   CheckBoxInfra->Checked = stAdat.bInfraSzolarium;
   EditIdoSzauna->Text = AnsiString( stAdat.nIdoSzauna );
   CheckBoxCsoVisible->Checked = stAdat.bShowCsoUzemora;
   UpDownCsoUzemoraOra->Position = stAdat.nCsoUzemora/3600;
   UpDownCsoUzemoraOra->Max = stAdat.nCsoUzemoraMax/3600;
   UpDownCsoUzemoraPerc->Position = (stAdat.nCsoUzemora%3600)/60;
   UpDownCsoUzemoraMp->Position = stAdat.nCsoUzemora%60;
   EditCsoUzemoraMax->Text = AnsiString( stAdat.nCsoUzemoraMax/3600 );
   EditIdoHasznalatMax->Text = AnsiString( stAdat.nMaxBarnulas );
   EditKedvStartO->Text = AnsiString( stAdat.nKedvezmenyIdoStart/60 );
   UpDownKedvOraStart->Position = stAdat.nKedvezmenyIdoStart/60;
   EditKedvStartP->Text = AnsiString( stAdat.nKedvezmenyIdoStart%60 );
   UpDownKedvPercStart->Position = stAdat.nKedvezmenyIdoStart%60;
   EditKedvStopO->Text = AnsiString( stAdat.nKedvezmenyIdoStop/60 );
   UpDownKedvOraStop->Position = stAdat.nKedvezmenyIdoStop/60;
   EditKedvStopP->Text = AnsiString( stAdat.nKedvezmenyIdoStop%60 );
   UpDownKedvPercStop->Position = stAdat.nKedvezmenyIdoStop%60;

   EditPerc0->Text = AnsiString( stAdat.stIdoForint[0].nPerc );
   EditPerc1->Text = AnsiString( stAdat.stIdoForint[1].nPerc );
   EditPerc2->Text = AnsiString( stAdat.stIdoForint[2].nPerc );
   EditPerc3->Text = AnsiString( stAdat.stIdoForint[3].nPerc );
   EditPerc4->Text = AnsiString( stAdat.stIdoForint[4].nPerc );
   EditPerc5->Text = AnsiString( stAdat.stIdoForint[5].nPerc );
   EditPerc6->Text = AnsiString( stAdat.stIdoForint[6].nPerc );
   EditPerc7->Text = AnsiString( stAdat.stIdoForint[7].nPerc );
   EditPerc8->Text = AnsiString( stAdat.stIdoForint[8].nPerc );
   EditPerc9->Text = AnsiString( stAdat.stIdoForint[9].nPerc );
   EditPerc10->Text = AnsiString( stAdat.stIdoForint[10].nPerc );
   EditPerc11->Text = AnsiString( stAdat.stIdoForint[11].nPerc );
   EditPerc12->Text = AnsiString( stAdat.stIdoForint[12].nPerc );
   EditPerc13->Text = AnsiString( stAdat.stIdoForint[13].nPerc );
   EditPerc14->Text = AnsiString( stAdat.stIdoForint[14].nPerc );
   EditPerc15->Text = AnsiString( stAdat.stIdoForint[15].nPerc );
   EditPerc16->Text = AnsiString( stAdat.stIdoForint[16].nPerc );
   EditPerc17->Text = AnsiString( stAdat.stIdoForint[17].nPerc );
   EditPerc18->Text = AnsiString( stAdat.stIdoForint[18].nPerc );
   EditPerc19->Text = AnsiString( stAdat.stIdoForint[19].nPerc );
   EditPerc20->Text = AnsiString( stAdat.stIdoForint[20].nPerc );
   EditPerc21->Text = AnsiString( stAdat.stIdoForint[21].nPerc );
   EditPerc22->Text = AnsiString( stAdat.stIdoForint[22].nPerc );
   EditPerc23->Text = AnsiString( stAdat.stIdoForint[23].nPerc );
   EditPerc24->Text = AnsiString( stAdat.stIdoForint[24].nPerc );
   EditPerc25->Text = AnsiString( stAdat.stIdoForint[25].nPerc );
   EditPerc26->Text = AnsiString( stAdat.stIdoForint[26].nPerc );
   EditPerc27->Text = AnsiString( stAdat.stIdoForint[27].nPerc );
   EditPerc28->Text = AnsiString( stAdat.stIdoForint[28].nPerc );
   EditPerc29->Text = AnsiString( stAdat.stIdoForint[29].nPerc );
   EditPerc30->Text = AnsiString( stAdat.stIdoForint[30].nPerc );
   EditPerc31->Text = AnsiString( stAdat.stIdoForint[31].nPerc );
   EditPerc32->Text = AnsiString( stAdat.stIdoForint[32].nPerc );
   EditPerc33->Text = AnsiString( stAdat.stIdoForint[33].nPerc );
   EditPerc34->Text = AnsiString( stAdat.stIdoForint[34].nPerc );
   EditPerc35->Text = AnsiString( stAdat.stIdoForint[35].nPerc );
   EditPerc36->Text = AnsiString( stAdat.stIdoForint[36].nPerc );
   EditPerc37->Text = AnsiString( stAdat.stIdoForint[37].nPerc );
   EditPerc38->Text = AnsiString( stAdat.stIdoForint[38].nPerc );
   EditPerc39->Text = AnsiString( stAdat.stIdoForint[39].nPerc );
   EditKPerc0->Text = AnsiString( stAdat.stIdoForintKedv[0].nPerc );
   EditKPerc1->Text = AnsiString( stAdat.stIdoForintKedv[1].nPerc );
   EditKPerc2->Text = AnsiString( stAdat.stIdoForintKedv[2].nPerc );
   EditKPerc3->Text = AnsiString( stAdat.stIdoForintKedv[3].nPerc );
   EditKPerc4->Text = AnsiString( stAdat.stIdoForintKedv[4].nPerc );
   EditKPerc5->Text = AnsiString( stAdat.stIdoForintKedv[5].nPerc );
   EditKPerc6->Text = AnsiString( stAdat.stIdoForintKedv[6].nPerc );
   EditKPerc7->Text = AnsiString( stAdat.stIdoForintKedv[7].nPerc );
   EditKPerc8->Text = AnsiString( stAdat.stIdoForintKedv[8].nPerc );
   EditKPerc9->Text = AnsiString( stAdat.stIdoForintKedv[9].nPerc );
   EditKPerc10->Text = AnsiString( stAdat.stIdoForintKedv[10].nPerc );
   EditKPerc11->Text = AnsiString( stAdat.stIdoForintKedv[11].nPerc );
   EditKPerc12->Text = AnsiString( stAdat.stIdoForintKedv[12].nPerc );
   EditKPerc13->Text = AnsiString( stAdat.stIdoForintKedv[13].nPerc );
   EditKPerc14->Text = AnsiString( stAdat.stIdoForintKedv[14].nPerc );
   EditKPerc15->Text = AnsiString( stAdat.stIdoForintKedv[15].nPerc );
   EditKPerc16->Text = AnsiString( stAdat.stIdoForintKedv[16].nPerc );
   EditKPerc17->Text = AnsiString( stAdat.stIdoForintKedv[17].nPerc );
   EditKPerc18->Text = AnsiString( stAdat.stIdoForintKedv[18].nPerc );
   EditKPerc19->Text = AnsiString( stAdat.stIdoForintKedv[19].nPerc );
   EditKPerc20->Text = AnsiString( stAdat.stIdoForintKedv[20].nPerc );
   EditKPerc21->Text = AnsiString( stAdat.stIdoForintKedv[21].nPerc );
   EditKPerc22->Text = AnsiString( stAdat.stIdoForintKedv[22].nPerc );
   EditKPerc23->Text = AnsiString( stAdat.stIdoForintKedv[23].nPerc );
   EditKPerc24->Text = AnsiString( stAdat.stIdoForintKedv[24].nPerc );
   EditKPerc25->Text = AnsiString( stAdat.stIdoForintKedv[25].nPerc );
   EditKPerc26->Text = AnsiString( stAdat.stIdoForintKedv[26].nPerc );
   EditKPerc27->Text = AnsiString( stAdat.stIdoForintKedv[27].nPerc );
   EditKPerc28->Text = AnsiString( stAdat.stIdoForintKedv[28].nPerc );
   EditKPerc29->Text = AnsiString( stAdat.stIdoForintKedv[29].nPerc );
   EditKPerc30->Text = AnsiString( stAdat.stIdoForintKedv[30].nPerc );
   EditKPerc31->Text = AnsiString( stAdat.stIdoForintKedv[31].nPerc );
   EditKPerc32->Text = AnsiString( stAdat.stIdoForintKedv[32].nPerc );
   EditKPerc33->Text = AnsiString( stAdat.stIdoForintKedv[33].nPerc );
   EditKPerc34->Text = AnsiString( stAdat.stIdoForintKedv[34].nPerc );
   EditKPerc35->Text = AnsiString( stAdat.stIdoForintKedv[35].nPerc );
   EditKPerc36->Text = AnsiString( stAdat.stIdoForintKedv[36].nPerc );
   EditKPerc37->Text = AnsiString( stAdat.stIdoForintKedv[37].nPerc );
   EditKPerc38->Text = AnsiString( stAdat.stIdoForintKedv[38].nPerc );
   EditKPerc39->Text = AnsiString( stAdat.stIdoForintKedv[39].nPerc );
   EditForint0->Text = convertToCurrencyString( stAdat.stIdoForint[0].nForint );
   EditForint1->Text = convertToCurrencyString( stAdat.stIdoForint[1].nForint );
   EditForint2->Text = convertToCurrencyString( stAdat.stIdoForint[2].nForint );
   EditForint3->Text = convertToCurrencyString( stAdat.stIdoForint[3].nForint );
   EditForint4->Text = convertToCurrencyString( stAdat.stIdoForint[4].nForint );
   EditForint5->Text = convertToCurrencyString( stAdat.stIdoForint[5].nForint );
   EditForint6->Text = convertToCurrencyString( stAdat.stIdoForint[6].nForint );
   EditForint7->Text = convertToCurrencyString( stAdat.stIdoForint[7].nForint );
   EditForint8->Text = convertToCurrencyString( stAdat.stIdoForint[8].nForint );
   EditForint9->Text = convertToCurrencyString( stAdat.stIdoForint[9].nForint );
   EditForint10->Text = convertToCurrencyString( stAdat.stIdoForint[10].nForint );
   EditForint11->Text = convertToCurrencyString( stAdat.stIdoForint[11].nForint );
   EditForint12->Text = convertToCurrencyString( stAdat.stIdoForint[12].nForint );
   EditForint13->Text = convertToCurrencyString( stAdat.stIdoForint[13].nForint );
   EditForint14->Text = convertToCurrencyString( stAdat.stIdoForint[14].nForint );
   EditForint15->Text = convertToCurrencyString( stAdat.stIdoForint[15].nForint );
   EditForint16->Text = convertToCurrencyString( stAdat.stIdoForint[16].nForint );
   EditForint17->Text = convertToCurrencyString( stAdat.stIdoForint[17].nForint );
   EditForint18->Text = convertToCurrencyString( stAdat.stIdoForint[18].nForint );
   EditForint19->Text = convertToCurrencyString( stAdat.stIdoForint[19].nForint );
   EditForint20->Text = convertToCurrencyString( stAdat.stIdoForint[20].nForint );
   EditForint21->Text = convertToCurrencyString( stAdat.stIdoForint[21].nForint );
   EditForint22->Text = convertToCurrencyString( stAdat.stIdoForint[22].nForint );
   EditForint23->Text = convertToCurrencyString( stAdat.stIdoForint[23].nForint );
   EditForint24->Text = convertToCurrencyString( stAdat.stIdoForint[24].nForint );
   EditForint25->Text = convertToCurrencyString( stAdat.stIdoForint[25].nForint );
   EditForint26->Text = convertToCurrencyString( stAdat.stIdoForint[26].nForint );
   EditForint27->Text = convertToCurrencyString( stAdat.stIdoForint[27].nForint );
   EditForint28->Text = convertToCurrencyString( stAdat.stIdoForint[28].nForint );
   EditForint29->Text = convertToCurrencyString( stAdat.stIdoForint[29].nForint );
   EditForint30->Text = convertToCurrencyString( stAdat.stIdoForint[30].nForint );
   EditForint31->Text = convertToCurrencyString( stAdat.stIdoForint[31].nForint );
   EditForint32->Text = convertToCurrencyString( stAdat.stIdoForint[32].nForint );
   EditForint33->Text = convertToCurrencyString( stAdat.stIdoForint[33].nForint );
   EditForint34->Text = convertToCurrencyString( stAdat.stIdoForint[34].nForint );
   EditForint35->Text = convertToCurrencyString( stAdat.stIdoForint[35].nForint );
   EditForint36->Text = convertToCurrencyString( stAdat.stIdoForint[36].nForint );
   EditForint37->Text = convertToCurrencyString( stAdat.stIdoForint[37].nForint );
   EditForint38->Text = convertToCurrencyString( stAdat.stIdoForint[38].nForint );
   EditForint39->Text = convertToCurrencyString( stAdat.stIdoForint[39].nForint );
   EditKForint0->Text = convertToCurrencyString( stAdat.stIdoForintKedv[0].nForint );
   EditKForint1->Text = convertToCurrencyString( stAdat.stIdoForintKedv[1].nForint );
   EditKForint2->Text = convertToCurrencyString( stAdat.stIdoForintKedv[2].nForint );
   EditKForint3->Text = convertToCurrencyString( stAdat.stIdoForintKedv[3].nForint );
   EditKForint4->Text = convertToCurrencyString( stAdat.stIdoForintKedv[4].nForint );
   EditKForint5->Text = convertToCurrencyString( stAdat.stIdoForintKedv[5].nForint );
   EditKForint6->Text = convertToCurrencyString( stAdat.stIdoForintKedv[6].nForint );
   EditKForint7->Text = convertToCurrencyString( stAdat.stIdoForintKedv[7].nForint );
   EditKForint8->Text = convertToCurrencyString( stAdat.stIdoForintKedv[8].nForint );
   EditKForint9->Text = convertToCurrencyString( stAdat.stIdoForintKedv[9].nForint );
   EditKForint10->Text = convertToCurrencyString( stAdat.stIdoForintKedv[10].nForint );
   EditKForint11->Text = convertToCurrencyString( stAdat.stIdoForintKedv[11].nForint );
   EditKForint12->Text = convertToCurrencyString( stAdat.stIdoForintKedv[12].nForint );
   EditKForint13->Text = convertToCurrencyString( stAdat.stIdoForintKedv[13].nForint );
   EditKForint14->Text = convertToCurrencyString( stAdat.stIdoForintKedv[14].nForint );
   EditKForint15->Text = convertToCurrencyString( stAdat.stIdoForintKedv[15].nForint );
   EditKForint16->Text = convertToCurrencyString( stAdat.stIdoForintKedv[16].nForint );
   EditKForint17->Text = convertToCurrencyString( stAdat.stIdoForintKedv[17].nForint );
   EditKForint18->Text = convertToCurrencyString( stAdat.stIdoForintKedv[18].nForint );
   EditKForint19->Text = convertToCurrencyString( stAdat.stIdoForintKedv[19].nForint );
   EditKForint20->Text = convertToCurrencyString( stAdat.stIdoForintKedv[20].nForint );
   EditKForint21->Text = convertToCurrencyString( stAdat.stIdoForintKedv[21].nForint );
   EditKForint22->Text = convertToCurrencyString( stAdat.stIdoForintKedv[22].nForint );
   EditKForint23->Text = convertToCurrencyString( stAdat.stIdoForintKedv[23].nForint );
   EditKForint24->Text = convertToCurrencyString( stAdat.stIdoForintKedv[24].nForint );
   EditKForint25->Text = convertToCurrencyString( stAdat.stIdoForintKedv[25].nForint );
   EditKForint26->Text = convertToCurrencyString( stAdat.stIdoForintKedv[26].nForint );
   EditKForint27->Text = convertToCurrencyString( stAdat.stIdoForintKedv[27].nForint );
   EditKForint28->Text = convertToCurrencyString( stAdat.stIdoForintKedv[28].nForint );
   EditKForint29->Text = convertToCurrencyString( stAdat.stIdoForintKedv[29].nForint );
   EditKForint30->Text = convertToCurrencyString( stAdat.stIdoForintKedv[30].nForint );
   EditKForint31->Text = convertToCurrencyString( stAdat.stIdoForintKedv[31].nForint );
   EditKForint32->Text = convertToCurrencyString( stAdat.stIdoForintKedv[32].nForint );
   EditKForint33->Text = convertToCurrencyString( stAdat.stIdoForintKedv[33].nForint );
   EditKForint34->Text = convertToCurrencyString( stAdat.stIdoForintKedv[34].nForint );
   EditKForint35->Text = convertToCurrencyString( stAdat.stIdoForintKedv[35].nForint );
   EditKForint36->Text = convertToCurrencyString( stAdat.stIdoForintKedv[36].nForint );
   EditKForint37->Text = convertToCurrencyString( stAdat.stIdoForintKedv[37].nForint );
   EditKForint38->Text = convertToCurrencyString( stAdat.stIdoForintKedv[38].nForint );
   EditKForint39->Text = convertToCurrencyString( stAdat.stIdoForintKedv[39].nForint );
}
//---------------------------------------------------------------------------
void TFormSzolariumAdat::SaveDataFromControls( typ_szoliadat *stAdat )
{
   memset( stAdat->strNev, 0, sizeof(stAdat->strNev) );
   strncpy( stAdat->strNev, EditNev->Text.c_str(), sizeof(stAdat->strNev)-2 );
   stAdat->nIdoVetkozes = EditIdoVetkozes->Text.ToInt();
   stAdat->nIdoUtohutes = EditIdoUtohutes->Text.ToInt();
   stAdat->bInfraSzolarium = CheckBoxInfra->Checked;
   stAdat->nIdoSzauna = EditIdoSzauna->Text.ToInt();
   stAdat->bShowCsoUzemora = CheckBoxCsoVisible->Checked;
   stAdat->nCsoUzemora = UpDownCsoUzemoraOra->Position*3600 +
                         UpDownCsoUzemoraPerc->Position*60 +
                         UpDownCsoUzemoraMp->Position;
   stAdat->nCsoUzemoraMax = EditCsoUzemoraMax->Text.ToInt()*3600;
   stAdat->nMaxBarnulas = EditIdoHasznalatMax->Text.ToInt();
   stAdat->nKedvezmenyIdoStart = EditKedvStartO->Text.ToInt()*60+EditKedvStartP->Text.ToInt();
   stAdat->nKedvezmenyIdoStop = EditKedvStopO->Text.ToInt()*60+EditKedvStopP->Text.ToInt();

   stAdat->stIdoForint[0].nPerc = EditPerc0->Text.ToInt();
   stAdat->stIdoForint[1].nPerc = EditPerc1->Text.ToInt();
   stAdat->stIdoForint[2].nPerc = EditPerc2->Text.ToInt();
   stAdat->stIdoForint[3].nPerc = EditPerc3->Text.ToInt();
   stAdat->stIdoForint[4].nPerc = EditPerc4->Text.ToInt();
   stAdat->stIdoForint[5].nPerc = EditPerc5->Text.ToInt();
   stAdat->stIdoForint[6].nPerc = EditPerc6->Text.ToInt();
   stAdat->stIdoForint[7].nPerc = EditPerc7->Text.ToInt();
   stAdat->stIdoForint[8].nPerc = EditPerc8->Text.ToInt();
   stAdat->stIdoForint[9].nPerc = EditPerc9->Text.ToInt();
   stAdat->stIdoForint[10].nPerc = EditPerc10->Text.ToInt();
   stAdat->stIdoForint[11].nPerc = EditPerc11->Text.ToInt();
   stAdat->stIdoForint[12].nPerc = EditPerc12->Text.ToInt();
   stAdat->stIdoForint[13].nPerc = EditPerc13->Text.ToInt();
   stAdat->stIdoForint[14].nPerc = EditPerc14->Text.ToInt();
   stAdat->stIdoForint[15].nPerc = EditPerc15->Text.ToInt();
   stAdat->stIdoForint[16].nPerc = EditPerc16->Text.ToInt();
   stAdat->stIdoForint[17].nPerc = EditPerc17->Text.ToInt();
   stAdat->stIdoForint[18].nPerc = EditPerc18->Text.ToInt();
   stAdat->stIdoForint[19].nPerc = EditPerc19->Text.ToInt();
   stAdat->stIdoForint[20].nPerc = EditPerc20->Text.ToInt();
   stAdat->stIdoForint[21].nPerc = EditPerc21->Text.ToInt();
   stAdat->stIdoForint[22].nPerc = EditPerc22->Text.ToInt();
   stAdat->stIdoForint[23].nPerc = EditPerc23->Text.ToInt();
   stAdat->stIdoForint[24].nPerc = EditPerc24->Text.ToInt();
   stAdat->stIdoForint[25].nPerc = EditPerc25->Text.ToInt();
   stAdat->stIdoForint[26].nPerc = EditPerc26->Text.ToInt();
   stAdat->stIdoForint[27].nPerc = EditPerc27->Text.ToInt();
   stAdat->stIdoForint[28].nPerc = EditPerc28->Text.ToInt();
   stAdat->stIdoForint[29].nPerc = EditPerc29->Text.ToInt();
   stAdat->stIdoForint[30].nPerc = EditPerc30->Text.ToInt();
   stAdat->stIdoForint[31].nPerc = EditPerc31->Text.ToInt();
   stAdat->stIdoForint[32].nPerc = EditPerc32->Text.ToInt();
   stAdat->stIdoForint[33].nPerc = EditPerc33->Text.ToInt();
   stAdat->stIdoForint[34].nPerc = EditPerc34->Text.ToInt();
   stAdat->stIdoForint[35].nPerc = EditPerc35->Text.ToInt();
   stAdat->stIdoForint[36].nPerc = EditPerc36->Text.ToInt();
   stAdat->stIdoForint[37].nPerc = EditPerc37->Text.ToInt();
   stAdat->stIdoForint[38].nPerc = EditPerc38->Text.ToInt();
   stAdat->stIdoForint[39].nPerc = EditPerc39->Text.ToInt();
   stAdat->stIdoForint[0].nForint = convertCurrency(EditForint0->Text.ToDouble());
   stAdat->stIdoForint[1].nForint = convertCurrency(EditForint1->Text.ToDouble());
   stAdat->stIdoForint[2].nForint = convertCurrency(EditForint2->Text.ToDouble());
   stAdat->stIdoForint[3].nForint = convertCurrency(EditForint3->Text.ToDouble());
   stAdat->stIdoForint[4].nForint = convertCurrency(EditForint4->Text.ToDouble());
   stAdat->stIdoForint[5].nForint = convertCurrency(EditForint5->Text.ToDouble());
   stAdat->stIdoForint[6].nForint = convertCurrency(EditForint6->Text.ToDouble());
   stAdat->stIdoForint[7].nForint = convertCurrency(EditForint7->Text.ToDouble());
   stAdat->stIdoForint[8].nForint = convertCurrency(EditForint8->Text.ToDouble());
   stAdat->stIdoForint[9].nForint = convertCurrency(EditForint9->Text.ToDouble());
   stAdat->stIdoForint[10].nForint = convertCurrency(EditForint10->Text.ToDouble());
   stAdat->stIdoForint[11].nForint = convertCurrency(EditForint11->Text.ToDouble());
   stAdat->stIdoForint[12].nForint = convertCurrency(EditForint12->Text.ToDouble());
   stAdat->stIdoForint[13].nForint = convertCurrency(EditForint13->Text.ToDouble());
   stAdat->stIdoForint[14].nForint = convertCurrency(EditForint14->Text.ToDouble());
   stAdat->stIdoForint[15].nForint = convertCurrency(EditForint15->Text.ToDouble());
   stAdat->stIdoForint[16].nForint = convertCurrency(EditForint16->Text.ToDouble());
   stAdat->stIdoForint[17].nForint = convertCurrency(EditForint17->Text.ToDouble());
   stAdat->stIdoForint[18].nForint = convertCurrency(EditForint18->Text.ToDouble());
   stAdat->stIdoForint[19].nForint = convertCurrency(EditForint19->Text.ToDouble());
   stAdat->stIdoForint[20].nForint = convertCurrency(EditForint20->Text.ToDouble());
   stAdat->stIdoForint[21].nForint = convertCurrency(EditForint21->Text.ToDouble());
   stAdat->stIdoForint[22].nForint = convertCurrency(EditForint22->Text.ToDouble());
   stAdat->stIdoForint[23].nForint = convertCurrency(EditForint23->Text.ToDouble());
   stAdat->stIdoForint[24].nForint = convertCurrency(EditForint24->Text.ToDouble());
   stAdat->stIdoForint[25].nForint = convertCurrency(EditForint25->Text.ToDouble());
   stAdat->stIdoForint[26].nForint = convertCurrency(EditForint26->Text.ToDouble());
   stAdat->stIdoForint[27].nForint = convertCurrency(EditForint27->Text.ToDouble());
   stAdat->stIdoForint[28].nForint = convertCurrency(EditForint28->Text.ToDouble());
   stAdat->stIdoForint[29].nForint = convertCurrency(EditForint29->Text.ToDouble());
   stAdat->stIdoForint[30].nForint = convertCurrency(EditForint30->Text.ToDouble());
   stAdat->stIdoForint[31].nForint = convertCurrency(EditForint31->Text.ToDouble());
   stAdat->stIdoForint[32].nForint = convertCurrency(EditForint32->Text.ToDouble());
   stAdat->stIdoForint[33].nForint = convertCurrency(EditForint33->Text.ToDouble());
   stAdat->stIdoForint[34].nForint = convertCurrency(EditForint34->Text.ToDouble());
   stAdat->stIdoForint[35].nForint = convertCurrency(EditForint35->Text.ToDouble());
   stAdat->stIdoForint[36].nForint = convertCurrency(EditForint36->Text.ToDouble());
   stAdat->stIdoForint[37].nForint = convertCurrency(EditForint37->Text.ToDouble());
   stAdat->stIdoForint[38].nForint = convertCurrency(EditForint38->Text.ToDouble());
   stAdat->stIdoForint[39].nForint = convertCurrency(EditForint39->Text.ToDouble());
   stAdat->stIdoForintKedv[0].nPerc = EditKPerc0->Text.ToInt();
   stAdat->stIdoForintKedv[1].nPerc = EditKPerc1->Text.ToInt();
   stAdat->stIdoForintKedv[2].nPerc = EditKPerc2->Text.ToInt();
   stAdat->stIdoForintKedv[3].nPerc = EditKPerc3->Text.ToInt();
   stAdat->stIdoForintKedv[4].nPerc = EditKPerc4->Text.ToInt();
   stAdat->stIdoForintKedv[5].nPerc = EditKPerc5->Text.ToInt();
   stAdat->stIdoForintKedv[6].nPerc = EditKPerc6->Text.ToInt();
   stAdat->stIdoForintKedv[7].nPerc = EditKPerc7->Text.ToInt();
   stAdat->stIdoForintKedv[8].nPerc = EditKPerc8->Text.ToInt();
   stAdat->stIdoForintKedv[9].nPerc = EditKPerc9->Text.ToInt();
   stAdat->stIdoForintKedv[10].nPerc = EditKPerc10->Text.ToInt();
   stAdat->stIdoForintKedv[11].nPerc = EditKPerc11->Text.ToInt();
   stAdat->stIdoForintKedv[12].nPerc = EditKPerc12->Text.ToInt();
   stAdat->stIdoForintKedv[13].nPerc = EditKPerc13->Text.ToInt();
   stAdat->stIdoForintKedv[14].nPerc = EditKPerc14->Text.ToInt();
   stAdat->stIdoForintKedv[15].nPerc = EditKPerc15->Text.ToInt();
   stAdat->stIdoForintKedv[16].nPerc = EditKPerc16->Text.ToInt();
   stAdat->stIdoForintKedv[17].nPerc = EditKPerc17->Text.ToInt();
   stAdat->stIdoForintKedv[18].nPerc = EditKPerc18->Text.ToInt();
   stAdat->stIdoForintKedv[19].nPerc = EditKPerc19->Text.ToInt();
   stAdat->stIdoForintKedv[20].nPerc = EditKPerc20->Text.ToInt();
   stAdat->stIdoForintKedv[21].nPerc = EditKPerc21->Text.ToInt();
   stAdat->stIdoForintKedv[22].nPerc = EditKPerc22->Text.ToInt();
   stAdat->stIdoForintKedv[23].nPerc = EditKPerc23->Text.ToInt();
   stAdat->stIdoForintKedv[24].nPerc = EditKPerc24->Text.ToInt();
   stAdat->stIdoForintKedv[25].nPerc = EditKPerc25->Text.ToInt();
   stAdat->stIdoForintKedv[26].nPerc = EditKPerc26->Text.ToInt();
   stAdat->stIdoForintKedv[27].nPerc = EditKPerc27->Text.ToInt();
   stAdat->stIdoForintKedv[28].nPerc = EditKPerc28->Text.ToInt();
   stAdat->stIdoForintKedv[29].nPerc = EditKPerc29->Text.ToInt();
   stAdat->stIdoForintKedv[30].nPerc = EditKPerc30->Text.ToInt();
   stAdat->stIdoForintKedv[31].nPerc = EditKPerc31->Text.ToInt();
   stAdat->stIdoForintKedv[32].nPerc = EditKPerc32->Text.ToInt();
   stAdat->stIdoForintKedv[33].nPerc = EditKPerc33->Text.ToInt();
   stAdat->stIdoForintKedv[34].nPerc = EditKPerc34->Text.ToInt();
   stAdat->stIdoForintKedv[35].nPerc = EditKPerc35->Text.ToInt();
   stAdat->stIdoForintKedv[36].nPerc = EditKPerc36->Text.ToInt();
   stAdat->stIdoForintKedv[37].nPerc = EditKPerc37->Text.ToInt();
   stAdat->stIdoForintKedv[38].nPerc = EditKPerc38->Text.ToInt();
   stAdat->stIdoForintKedv[39].nPerc = EditKPerc39->Text.ToInt();
   stAdat->stIdoForintKedv[0].nForint = convertCurrency(EditKForint0->Text.ToDouble());
   stAdat->stIdoForintKedv[1].nForint = convertCurrency(EditKForint1->Text.ToDouble());
   stAdat->stIdoForintKedv[2].nForint = convertCurrency(EditKForint2->Text.ToDouble());
   stAdat->stIdoForintKedv[3].nForint = convertCurrency(EditKForint3->Text.ToDouble());
   stAdat->stIdoForintKedv[4].nForint = convertCurrency(EditKForint4->Text.ToDouble());
   stAdat->stIdoForintKedv[5].nForint = convertCurrency(EditKForint5->Text.ToDouble());
   stAdat->stIdoForintKedv[6].nForint = convertCurrency(EditKForint6->Text.ToDouble());
   stAdat->stIdoForintKedv[7].nForint = convertCurrency(EditKForint7->Text.ToDouble());
   stAdat->stIdoForintKedv[8].nForint = convertCurrency(EditKForint8->Text.ToDouble());
   stAdat->stIdoForintKedv[9].nForint = convertCurrency(EditKForint9->Text.ToDouble());
   stAdat->stIdoForintKedv[10].nForint = convertCurrency(EditKForint10->Text.ToDouble());
   stAdat->stIdoForintKedv[11].nForint = convertCurrency(EditKForint11->Text.ToDouble());
   stAdat->stIdoForintKedv[12].nForint = convertCurrency(EditKForint12->Text.ToDouble());
   stAdat->stIdoForintKedv[13].nForint = convertCurrency(EditKForint13->Text.ToDouble());
   stAdat->stIdoForintKedv[14].nForint = convertCurrency(EditKForint14->Text.ToDouble());
   stAdat->stIdoForintKedv[15].nForint = convertCurrency(EditKForint15->Text.ToDouble());
   stAdat->stIdoForintKedv[16].nForint = convertCurrency(EditKForint16->Text.ToDouble());
   stAdat->stIdoForintKedv[17].nForint = convertCurrency(EditKForint17->Text.ToDouble());
   stAdat->stIdoForintKedv[18].nForint = convertCurrency(EditKForint18->Text.ToDouble());
   stAdat->stIdoForintKedv[19].nForint = convertCurrency(EditKForint19->Text.ToDouble());
   stAdat->stIdoForintKedv[20].nForint = convertCurrency(EditKForint20->Text.ToDouble());
   stAdat->stIdoForintKedv[21].nForint = convertCurrency(EditKForint21->Text.ToDouble());
   stAdat->stIdoForintKedv[22].nForint = convertCurrency(EditKForint22->Text.ToDouble());
   stAdat->stIdoForintKedv[23].nForint = convertCurrency(EditKForint23->Text.ToDouble());
   stAdat->stIdoForintKedv[24].nForint = convertCurrency(EditKForint24->Text.ToDouble());
   stAdat->stIdoForintKedv[25].nForint = convertCurrency(EditKForint25->Text.ToDouble());
   stAdat->stIdoForintKedv[26].nForint = convertCurrency(EditKForint26->Text.ToDouble());
   stAdat->stIdoForintKedv[27].nForint = convertCurrency(EditKForint27->Text.ToDouble());
   stAdat->stIdoForintKedv[28].nForint = convertCurrency(EditKForint28->Text.ToDouble());
   stAdat->stIdoForintKedv[29].nForint = convertCurrency(EditKForint29->Text.ToDouble());
   stAdat->stIdoForintKedv[30].nForint = convertCurrency(EditKForint30->Text.ToDouble());
   stAdat->stIdoForintKedv[31].nForint = convertCurrency(EditKForint31->Text.ToDouble());
   stAdat->stIdoForintKedv[32].nForint = convertCurrency(EditKForint32->Text.ToDouble());
   stAdat->stIdoForintKedv[33].nForint = convertCurrency(EditKForint33->Text.ToDouble());
   stAdat->stIdoForintKedv[34].nForint = convertCurrency(EditKForint34->Text.ToDouble());
   stAdat->stIdoForintKedv[35].nForint = convertCurrency(EditKForint35->Text.ToDouble());
   stAdat->stIdoForintKedv[36].nForint = convertCurrency(EditKForint36->Text.ToDouble());
   stAdat->stIdoForintKedv[37].nForint = convertCurrency(EditKForint37->Text.ToDouble());
   stAdat->stIdoForintKedv[38].nForint = convertCurrency(EditKForint38->Text.ToDouble());
   stAdat->stIdoForintKedv[39].nForint = convertCurrency(EditKForint39->Text.ToDouble());
}
//---------------------------------------------------------------------------
void __fastcall TFormSzolariumAdat::TabControlTablazatChange(TObject *Sender)
{
   switch( TabControlTablazat->TabIndex )
   {
      case 0:
         GroupBoxTablazatNorm->Enabled = true;
         GroupBoxTablazatNorm->Visible = true;
         GroupBoxTablazatKedv->Enabled = false;
         GroupBoxTablazatKedv->Visible = false;
         break;
      case 1:
         GroupBoxTablazatNorm->Enabled = false;
         GroupBoxTablazatNorm->Visible = false;
         GroupBoxTablazatKedv->Enabled = true;
         GroupBoxTablazatKedv->Visible = true;
         break;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormSzolariumAdat::BtnResetClick(TObject *Sender)
{
   UpDownCsoUzemoraOra->Position = 0;
   UpDownCsoUzemoraPerc->Position = 0;
   UpDownCsoUzemoraMp->Position = 0;
}
//---------------------------------------------------------------------------


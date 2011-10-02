object FormAdatbazisKezeles: TFormAdatbazisKezeles
  Left = 397
  Top = 125
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Adatbázis kezelés'
  ClientHeight = 452
  ClientWidth = 388
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 20
  object BitBtnOk: TBitBtn
    Left = 285
    Top = 415
    Width = 96
    Height = 30
    Caption = '&Bezárás'
    Default = True
    TabOrder = 4
    OnClick = BitBtnOkClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00330000000000
      03333377777777777F333301BBBBBBBB033333773F3333337F3333011BBBBBBB
      0333337F73F333337F33330111BBBBBB0333337F373F33337F333301110BBBBB
      0333337F337F33337F333301110BBBBB0333337F337F33337F333301110BBBBB
      0333337F337F33337F333301110BBBBB0333337F337F33337F333301110BBBBB
      0333337F337F33337F333301110BBBBB0333337F337FF3337F33330111B0BBBB
      0333337F337733337F333301110BBBBB0333337F337F33337F333301110BBBBB
      0333337F3F7F33337F333301E10BBBBB0333337F7F7F33337F333301EE0BBBBB
      0333337F777FFFFF7F3333000000000003333377777777777333}
    Margin = 5
    NumGlyphs = 2
  end
  object GB_FilterDatum: TGroupBox
    Left = 5
    Top = 5
    Width = 376
    Height = 101
    Caption = ' 1. Idõintervallum kiválasztása '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 10
      Top = 30
      Width = 106
      Height = 20
      Caption = 'Kezdõ dátum :'
    end
    object Label2: TLabel
      Left = 10
      Top = 65
      Width = 88
      Height = 20
      Caption = 'Vég dátum :'
    end
    object DTPickerStart: TDateTimePicker
      Left = 190
      Top = 27
      Width = 111
      Height = 28
      CalAlignment = dtaLeft
      Date = 39512
      Time = 39512
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 2
    end
    object BtnStartPrevWeek: TButton
      Left = 125
      Top = 27
      Width = 30
      Height = 30
      Caption = '<<'
      TabOrder = 0
      OnClick = BtnStartPrevWeekClick
    end
    object BtnStartPrevDay: TButton
      Left = 156
      Top = 27
      Width = 30
      Height = 30
      Caption = '<'
      TabOrder = 1
      OnClick = BtnStartPrevDayClick
    end
    object BtnStartNextDay: TButton
      Left = 305
      Top = 27
      Width = 30
      Height = 30
      Caption = '>'
      TabOrder = 3
      OnClick = BtnStartNextDayClick
    end
    object BtnStartNextWeek: TButton
      Left = 336
      Top = 27
      Width = 30
      Height = 30
      Caption = '>>'
      TabOrder = 4
      OnClick = BtnStartNextWeekClick
    end
    object BtnStopPrevWeek: TButton
      Left = 124
      Top = 62
      Width = 30
      Height = 30
      Caption = '<<'
      TabOrder = 5
      OnClick = BtnStopPrevWeekClick
    end
    object BtnStopPrevDay: TButton
      Left = 156
      Top = 62
      Width = 30
      Height = 30
      Caption = '<'
      TabOrder = 6
      OnClick = BtnStopPrevDayClick
    end
    object DTPickerStop: TDateTimePicker
      Left = 190
      Top = 63
      Width = 111
      Height = 28
      CalAlignment = dtaLeft
      Date = 39512.9999884259
      Time = 39512.9999884259
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 7
    end
    object BtnStopNextDay: TButton
      Left = 305
      Top = 62
      Width = 30
      Height = 30
      Caption = '>'
      TabOrder = 8
      OnClick = BtnStopNextDayClick
    end
    object BtnStopNextWeek: TButton
      Left = 336
      Top = 62
      Width = 30
      Height = 30
      Caption = '>>'
      TabOrder = 9
      OnClick = BtnStopNextWeekClick
    end
  end
  object GroupBox1: TGroupBox
    Left = 5
    Top = 110
    Width = 376
    Height = 166
    Caption = ' 2. Adatcsoport kiválasztása '
    TabOrder = 1
    object Label3: TLabel
      Left = 9
      Top = 59
      Width = 351
      Height = 20
      Caption = '_______________________________________'
    end
    object Label4: TLabel
      Left = 9
      Top = 115
      Width = 351
      Height = 20
      Caption = '_______________________________________'
    end
    object RadioBerlet: TRadioButton
      Left = 10
      Top = 30
      Width = 351
      Height = 17
      Caption = 'Bérletek (lejárat dátuma szerint)'
      TabOrder = 0
      TabStop = True
      OnClick = RadioBerletClick
    end
    object RadioBerlethasznalat: TRadioButton
      Left = 10
      Top = 55
      Width = 351
      Height = 17
      Caption = 'Bérlet használat'
      TabOrder = 1
      OnClick = RadioBerlethasznalatClick
    end
    object RadioFokonyv: TRadioButton
      Left = 10
      Top = 85
      Width = 351
      Height = 17
      Caption = 'Fõkönyv'
      TabOrder = 2
      OnClick = RadioFokonyvClick
    end
    object RadioSzolariumkonyv: TRadioButton
      Left = 10
      Top = 110
      Width = 351
      Height = 17
      Caption = 'Szolárium könyv'
      TabOrder = 3
      OnClick = RadioSzolariumkonyvClick
    end
    object RadioPenztar: TRadioButton
      Left = 10
      Top = 140
      Width = 351
      Height = 17
      Caption = 'Pénztárkönyv'
      TabOrder = 4
      OnClick = RadioPenztarClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 5
    Top = 280
    Width = 376
    Height = 61
    Caption = ' 3. Adatbázis mûvelet kiválasztása '
    TabOrder = 2
    object RadioDBDelete: TRadioButton
      Left = 10
      Top = 30
      Width = 351
      Height = 17
      Caption = 'Adatok törlése a megadott idõintervallumban'
      Enabled = False
      TabOrder = 0
      TabStop = True
      OnClick = RadioDBDeleteClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 5
    Top = 345
    Width = 376
    Height = 61
    TabOrder = 3
    object BitBtnExecute: TBitBtn
      Left = 10
      Top = 20
      Width = 356
      Height = 30
      Caption = 'Adatbázis mûvelet végrehajtása'
      Default = True
      Enabled = False
      TabOrder = 0
      OnClick = BitBtnExecuteClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555550FF0559
        1950555FF75F7557F7F757000FF055591903557775F75557F77570FFFF055559
        1933575FF57F5557F7FF0F00FF05555919337F775F7F5557F7F700550F055559
        193577557F7F55F7577F07550F0555999995755575755F7FFF7F5570F0755011
        11155557F755F777777555000755033305555577755F75F77F55555555503335
        0555555FF5F75F757F5555005503335505555577FF75F7557F55505050333555
        05555757F75F75557F5505000333555505557F777FF755557F55000000355557
        07557777777F55557F5555000005555707555577777FF5557F55553000075557
        0755557F7777FFF5755555335000005555555577577777555555}
      NumGlyphs = 2
    end
  end
end

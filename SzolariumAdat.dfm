object FormSzolariumAdat: TFormSzolariumAdat
  Left = 286
  Top = 112
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Szolárium adatok'
  ClientHeight = 594
  ClientWidth = 747
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  OnShortCut = FormShortCut
  PixelsPerInch = 96
  TextHeight = 20
  object GroupBoxNevIdo: TGroupBox
    Left = 5
    Top = 5
    Width = 431
    Height = 91
    TabOrder = 0
    object Label1: TLabel
      Left = 10
      Top = 20
      Width = 182
      Height = 20
      Caption = 'Szolárium megnevezés: '
    end
    object Label3: TLabel
      Left = 10
      Top = 55
      Width = 151
      Height = 20
      Caption = 'Vetkõzési idõ (mp) : '
    end
    object Label4: TLabel
      Left = 210
      Top = 55
      Width = 149
      Height = 20
      Caption = 'Utóhûtési idõ (mp) : '
    end
    object EditNev: TEdit
      Left = 195
      Top = 17
      Width = 226
      Height = 28
      MaxLength = 49
      TabOrder = 0
    end
    object EditIdoVetkozes: TEdit
      Left = 165
      Top = 52
      Width = 35
      Height = 28
      TabOrder = 1
    end
    object EditIdoUtohutes: TEdit
      Left = 360
      Top = 52
      Width = 35
      Height = 28
      TabOrder = 2
    end
  end
  object GroupBoxInfra: TGroupBox
    Left = 440
    Top = 5
    Width = 301
    Height = 91
    TabOrder = 1
    object Label2: TLabel
      Left = 10
      Top = 55
      Width = 200
      Height = 20
      Caption = 'Szauna idõ (max 240 mp) : '
    end
    object CheckBoxInfra: TCheckBox
      Left = 10
      Top = 23
      Width = 153
      Height = 17
      Caption = 'Infra szolárium'
      TabOrder = 0
      OnClick = CheckBoxInfraClick
    end
    object EditIdoSzauna: TEdit
      Left = 210
      Top = 52
      Width = 44
      Height = 28
      Enabled = False
      TabOrder = 1
    end
  end
  object BitBtnOk: TBitBtn
    Left = 265
    Top = 556
    Width = 106
    Height = 30
    Caption = 'Mentés'
    TabOrder = 6
    Kind = bkOK
    Margin = 5
  end
  object BitBtnCancel: TBitBtn
    Left = 380
    Top = 556
    Width = 101
    Height = 30
    Caption = 'Mégsem'
    TabOrder = 7
    Kind = bkCancel
    Margin = 5
  end
  object TabControlTablazat: TTabControl
    Left = 5
    Top = 237
    Width = 736
    Height = 312
    TabOrder = 5
    Tabs.Strings = (
      'Normál idõszak'
      'Kedvezményes idõszak')
    TabIndex = 0
    OnChange = TabControlTablazatChange
    object GroupBoxTablazatNorm: TGroupBox
      Left = 6
      Top = 30
      Width = 723
      Height = 275
      Color = clBtnFace
      ParentColor = False
      TabOrder = 0
      object Panel1: TPanel
        Left = 1
        Top = 10
        Width = 180
        Height = 263
        BevelOuter = bvNone
        Color = 13041663
        TabOrder = 0
        object Label5: TLabel
          Left = 52
          Top = 8
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label6: TLabel
          Left = 138
          Top = 8
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label7: TLabel
          Left = 52
          Top = 33
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label8: TLabel
          Left = 138
          Top = 33
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label9: TLabel
          Left = 52
          Top = 58
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label10: TLabel
          Left = 138
          Top = 58
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label12: TLabel
          Left = 52
          Top = 83
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label11: TLabel
          Left = 138
          Top = 83
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label13: TLabel
          Left = 52
          Top = 108
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label14: TLabel
          Left = 138
          Top = 108
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label15: TLabel
          Left = 52
          Top = 133
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label16: TLabel
          Left = 138
          Top = 133
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label18: TLabel
          Left = 52
          Top = 158
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label17: TLabel
          Left = 138
          Top = 158
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label19: TLabel
          Left = 52
          Top = 183
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label20: TLabel
          Left = 138
          Top = 183
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label21: TLabel
          Left = 52
          Top = 208
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label22: TLabel
          Left = 138
          Top = 208
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label23: TLabel
          Left = 52
          Top = 233
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label24: TLabel
          Left = 138
          Top = 233
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object EditPerc0: TEdit
          Left = 5
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 0
        end
        object EditForint0: TEdit
          Left = 90
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 1
        end
        object EditPerc1: TEdit
          Left = 5
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 2
        end
        object EditForint1: TEdit
          Left = 90
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 3
        end
        object EditPerc2: TEdit
          Left = 5
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 4
        end
        object EditForint2: TEdit
          Left = 90
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 5
        end
        object EditPerc3: TEdit
          Left = 5
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 6
        end
        object EditForint3: TEdit
          Left = 90
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 7
        end
        object EditPerc4: TEdit
          Left = 5
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 8
        end
        object EditForint4: TEdit
          Left = 90
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 9
        end
        object EditPerc5: TEdit
          Left = 5
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 10
        end
        object EditForint5: TEdit
          Left = 90
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 11
        end
        object EditPerc6: TEdit
          Left = 5
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 12
        end
        object EditForint6: TEdit
          Left = 90
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 13
        end
        object EditPerc7: TEdit
          Left = 5
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 14
        end
        object EditForint7: TEdit
          Left = 90
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 15
        end
        object EditPerc8: TEdit
          Left = 5
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 16
        end
        object EditForint8: TEdit
          Left = 90
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 17
        end
        object EditPerc9: TEdit
          Left = 5
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 18
        end
        object EditForint9: TEdit
          Left = 90
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 19
        end
      end
      object Panel2: TPanel
        Left = 181
        Top = 10
        Width = 180
        Height = 263
        BevelOuter = bvNone
        Color = clWhite
        TabOrder = 1
        object Label44: TLabel
          Left = 52
          Top = 8
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label34: TLabel
          Left = 138
          Top = 8
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label43: TLabel
          Left = 52
          Top = 33
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label33: TLabel
          Left = 138
          Top = 33
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label42: TLabel
          Left = 52
          Top = 58
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label32: TLabel
          Left = 138
          Top = 58
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label41: TLabel
          Left = 52
          Top = 83
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label31: TLabel
          Left = 138
          Top = 83
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label40: TLabel
          Left = 52
          Top = 108
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label30: TLabel
          Left = 138
          Top = 108
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label39: TLabel
          Left = 52
          Top = 133
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label29: TLabel
          Left = 138
          Top = 133
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label38: TLabel
          Left = 52
          Top = 158
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label28: TLabel
          Left = 138
          Top = 158
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label37: TLabel
          Left = 52
          Top = 183
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label27: TLabel
          Left = 138
          Top = 183
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label36: TLabel
          Left = 52
          Top = 208
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label26: TLabel
          Left = 138
          Top = 208
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label35: TLabel
          Left = 52
          Top = 233
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label25: TLabel
          Left = 138
          Top = 233
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object EditPerc10: TEdit
          Left = 5
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 0
        end
        object EditForint10: TEdit
          Left = 90
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 1
        end
        object EditPerc11: TEdit
          Left = 5
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 2
        end
        object EditForint11: TEdit
          Left = 90
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 3
        end
        object EditPerc12: TEdit
          Left = 5
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 4
        end
        object EditForint12: TEdit
          Left = 90
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 5
        end
        object EditPerc13: TEdit
          Left = 5
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 6
        end
        object EditForint13: TEdit
          Left = 90
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 7
        end
        object EditPerc14: TEdit
          Left = 5
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 8
        end
        object EditForint14: TEdit
          Left = 90
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 9
        end
        object EditPerc15: TEdit
          Left = 5
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 10
        end
        object EditForint15: TEdit
          Left = 90
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 11
        end
        object EditPerc16: TEdit
          Left = 5
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 12
        end
        object EditForint16: TEdit
          Left = 90
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 13
        end
        object EditPerc17: TEdit
          Left = 5
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 14
        end
        object EditForint17: TEdit
          Left = 90
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 15
        end
        object EditPerc18: TEdit
          Left = 5
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 16
        end
        object EditForint18: TEdit
          Left = 90
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 17
        end
        object EditPerc19: TEdit
          Left = 5
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 18
        end
        object EditForint19: TEdit
          Left = 90
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 19
        end
      end
      object Panel3: TPanel
        Left = 361
        Top = 10
        Width = 180
        Height = 263
        BevelOuter = bvNone
        Color = 13041663
        TabOrder = 2
        object Label64: TLabel
          Left = 52
          Top = 8
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label54: TLabel
          Left = 138
          Top = 8
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label63: TLabel
          Left = 52
          Top = 33
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label53: TLabel
          Left = 138
          Top = 33
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label62: TLabel
          Left = 52
          Top = 58
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label52: TLabel
          Left = 138
          Top = 58
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label61: TLabel
          Left = 52
          Top = 83
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label51: TLabel
          Left = 138
          Top = 83
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label60: TLabel
          Left = 52
          Top = 108
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label50: TLabel
          Left = 138
          Top = 108
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label59: TLabel
          Left = 52
          Top = 133
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label49: TLabel
          Left = 138
          Top = 133
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label58: TLabel
          Left = 52
          Top = 158
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label48: TLabel
          Left = 138
          Top = 158
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label57: TLabel
          Left = 52
          Top = 183
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label47: TLabel
          Left = 138
          Top = 183
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label56: TLabel
          Left = 52
          Top = 208
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label46: TLabel
          Left = 138
          Top = 208
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label55: TLabel
          Left = 52
          Top = 233
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label45: TLabel
          Left = 138
          Top = 233
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object EditPerc20: TEdit
          Left = 5
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 0
        end
        object EditForint20: TEdit
          Left = 90
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 1
        end
        object EditPerc21: TEdit
          Left = 5
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 2
        end
        object EditForint21: TEdit
          Left = 90
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 3
        end
        object EditPerc22: TEdit
          Left = 5
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 4
        end
        object EditForint22: TEdit
          Left = 90
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 5
        end
        object EditPerc23: TEdit
          Left = 5
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 6
        end
        object EditForint23: TEdit
          Left = 90
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 7
        end
        object EditPerc24: TEdit
          Left = 5
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 8
        end
        object EditForint24: TEdit
          Left = 90
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 9
        end
        object EditPerc25: TEdit
          Left = 5
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 10
        end
        object EditForint25: TEdit
          Left = 90
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 11
        end
        object EditPerc26: TEdit
          Left = 5
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 12
        end
        object EditForint26: TEdit
          Left = 90
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 13
        end
        object EditPerc27: TEdit
          Left = 5
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 14
        end
        object EditForint27: TEdit
          Left = 90
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 15
        end
        object EditPerc28: TEdit
          Left = 5
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 16
        end
        object EditForint28: TEdit
          Left = 90
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 17
        end
        object EditPerc29: TEdit
          Left = 5
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 18
        end
        object EditForint29: TEdit
          Left = 90
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 19
        end
      end
      object Panel4: TPanel
        Left = 541
        Top = 10
        Width = 180
        Height = 263
        BevelOuter = bvNone
        Color = clWhite
        TabOrder = 3
        object Label84: TLabel
          Left = 52
          Top = 8
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label74: TLabel
          Left = 138
          Top = 8
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label83: TLabel
          Left = 52
          Top = 33
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label73: TLabel
          Left = 138
          Top = 33
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label82: TLabel
          Left = 52
          Top = 58
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label72: TLabel
          Left = 138
          Top = 58
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label81: TLabel
          Left = 52
          Top = 83
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label71: TLabel
          Left = 138
          Top = 83
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label80: TLabel
          Left = 52
          Top = 108
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label70: TLabel
          Left = 138
          Top = 108
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label79: TLabel
          Left = 52
          Top = 133
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label69: TLabel
          Left = 138
          Top = 133
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label78: TLabel
          Left = 52
          Top = 158
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label68: TLabel
          Left = 138
          Top = 158
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label77: TLabel
          Left = 52
          Top = 183
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label67: TLabel
          Left = 138
          Top = 183
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label76: TLabel
          Left = 52
          Top = 208
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label66: TLabel
          Left = 138
          Top = 208
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label75: TLabel
          Left = 52
          Top = 233
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label65: TLabel
          Left = 138
          Top = 233
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object EditPerc30: TEdit
          Left = 5
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 0
        end
        object EditForint30: TEdit
          Left = 90
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 1
        end
        object EditPerc31: TEdit
          Left = 5
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 2
        end
        object EditForint31: TEdit
          Left = 90
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 3
        end
        object EditPerc32: TEdit
          Left = 5
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 4
        end
        object EditForint32: TEdit
          Left = 90
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 5
        end
        object EditPerc33: TEdit
          Left = 5
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 6
        end
        object EditForint33: TEdit
          Left = 90
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 7
        end
        object EditPerc34: TEdit
          Left = 5
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 8
        end
        object EditForint34: TEdit
          Left = 90
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 9
        end
        object EditPerc35: TEdit
          Left = 5
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 10
        end
        object EditForint35: TEdit
          Left = 90
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 11
        end
        object EditPerc36: TEdit
          Left = 5
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 12
        end
        object EditForint36: TEdit
          Left = 90
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 13
        end
        object EditPerc37: TEdit
          Left = 5
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 14
        end
        object EditForint37: TEdit
          Left = 90
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 15
        end
        object EditPerc38: TEdit
          Left = 5
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 16
        end
        object EditForint38: TEdit
          Left = 90
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 17
        end
        object EditPerc39: TEdit
          Left = 5
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 18
        end
        object EditForint39: TEdit
          Left = 90
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 19
        end
      end
    end
    object GroupBoxTablazatKedv: TGroupBox
      Left = 6
      Top = 30
      Width = 723
      Height = 275
      Color = clBtnFace
      Enabled = False
      ParentColor = False
      TabOrder = 1
      Visible = False
      object Panel5: TPanel
        Left = 1
        Top = 10
        Width = 180
        Height = 263
        BevelOuter = bvNone
        Color = clWhite
        TabOrder = 0
        object Label87: TLabel
          Left = 52
          Top = 8
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label88: TLabel
          Left = 138
          Top = 8
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label89: TLabel
          Left = 52
          Top = 33
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label90: TLabel
          Left = 138
          Top = 33
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label91: TLabel
          Left = 52
          Top = 58
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label92: TLabel
          Left = 138
          Top = 58
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label93: TLabel
          Left = 52
          Top = 83
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label94: TLabel
          Left = 138
          Top = 83
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label95: TLabel
          Left = 52
          Top = 108
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label96: TLabel
          Left = 138
          Top = 108
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label97: TLabel
          Left = 52
          Top = 133
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label98: TLabel
          Left = 138
          Top = 133
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label99: TLabel
          Left = 52
          Top = 158
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label100: TLabel
          Left = 138
          Top = 158
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label101: TLabel
          Left = 52
          Top = 183
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label102: TLabel
          Left = 138
          Top = 183
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label103: TLabel
          Left = 52
          Top = 208
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label104: TLabel
          Left = 138
          Top = 208
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label105: TLabel
          Left = 52
          Top = 233
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label106: TLabel
          Left = 138
          Top = 233
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object EditKPerc0: TEdit
          Left = 5
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 0
        end
        object EditKForint0: TEdit
          Left = 90
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 1
        end
        object EditKPerc1: TEdit
          Left = 5
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 2
        end
        object EditKForint1: TEdit
          Left = 90
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 3
        end
        object EditKPerc2: TEdit
          Left = 5
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 4
        end
        object EditKForint2: TEdit
          Left = 90
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 5
        end
        object EditKPerc3: TEdit
          Left = 5
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 6
        end
        object EditKForint3: TEdit
          Left = 90
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 7
        end
        object EditKPerc4: TEdit
          Left = 5
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 8
        end
        object EditKForint4: TEdit
          Left = 90
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 9
        end
        object EditKPerc5: TEdit
          Left = 5
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 10
        end
        object EditKForint5: TEdit
          Left = 90
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 11
        end
        object EditKPerc6: TEdit
          Left = 5
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 12
        end
        object EditKForint6: TEdit
          Left = 90
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 13
        end
        object EditKPerc7: TEdit
          Left = 5
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 14
        end
        object EditKForint7: TEdit
          Left = 90
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 15
        end
        object EditKPerc8: TEdit
          Left = 5
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 16
        end
        object EditKForint8: TEdit
          Left = 90
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 17
        end
        object EditKPerc9: TEdit
          Left = 5
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 18
        end
        object EditKForint9: TEdit
          Left = 90
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 19
        end
      end
      object Panel6: TPanel
        Left = 181
        Top = 10
        Width = 180
        Height = 263
        BevelOuter = bvNone
        Color = 13041663
        TabOrder = 1
        object Label107: TLabel
          Left = 52
          Top = 8
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label108: TLabel
          Left = 138
          Top = 8
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label109: TLabel
          Left = 52
          Top = 33
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label110: TLabel
          Left = 138
          Top = 33
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label111: TLabel
          Left = 52
          Top = 58
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label112: TLabel
          Left = 138
          Top = 58
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label113: TLabel
          Left = 52
          Top = 83
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label114: TLabel
          Left = 138
          Top = 83
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label115: TLabel
          Left = 52
          Top = 108
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label116: TLabel
          Left = 138
          Top = 108
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label117: TLabel
          Left = 52
          Top = 133
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label118: TLabel
          Left = 138
          Top = 133
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label119: TLabel
          Left = 52
          Top = 158
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label120: TLabel
          Left = 138
          Top = 158
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label121: TLabel
          Left = 52
          Top = 183
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label122: TLabel
          Left = 138
          Top = 183
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label123: TLabel
          Left = 52
          Top = 208
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label124: TLabel
          Left = 138
          Top = 208
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label125: TLabel
          Left = 52
          Top = 233
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label126: TLabel
          Left = 138
          Top = 233
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object EditKPerc10: TEdit
          Left = 5
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 0
        end
        object EditKForint10: TEdit
          Left = 90
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 1
        end
        object EditKPerc11: TEdit
          Left = 5
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 2
        end
        object EditKForint11: TEdit
          Left = 90
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 3
        end
        object EditKPerc12: TEdit
          Left = 5
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 4
        end
        object EditKForint12: TEdit
          Left = 90
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 5
        end
        object EditKPerc13: TEdit
          Left = 5
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 6
        end
        object EditKForint13: TEdit
          Left = 90
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 7
        end
        object EditKPerc14: TEdit
          Left = 5
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 8
        end
        object EditKForint14: TEdit
          Left = 90
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 9
        end
        object EditKPerc15: TEdit
          Left = 5
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 10
        end
        object EditKForint15: TEdit
          Left = 90
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 11
        end
        object EditKPerc16: TEdit
          Left = 5
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 12
        end
        object EditKForint16: TEdit
          Left = 90
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 13
        end
        object EditKPerc17: TEdit
          Left = 5
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 14
        end
        object EditKForint17: TEdit
          Left = 90
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 15
        end
        object EditKPerc18: TEdit
          Left = 5
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 16
        end
        object EditKForint18: TEdit
          Left = 90
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 17
        end
        object EditKPerc19: TEdit
          Left = 5
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 18
        end
        object EditKForint19: TEdit
          Left = 90
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 19
        end
      end
      object Panel7: TPanel
        Left = 361
        Top = 10
        Width = 180
        Height = 263
        BevelOuter = bvNone
        Color = clWhite
        TabOrder = 2
        object Label127: TLabel
          Left = 52
          Top = 8
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label128: TLabel
          Left = 138
          Top = 8
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label129: TLabel
          Left = 52
          Top = 33
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label130: TLabel
          Left = 138
          Top = 33
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label131: TLabel
          Left = 52
          Top = 58
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label132: TLabel
          Left = 138
          Top = 58
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label133: TLabel
          Left = 52
          Top = 83
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label134: TLabel
          Left = 138
          Top = 83
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label135: TLabel
          Left = 52
          Top = 108
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label136: TLabel
          Left = 138
          Top = 108
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label137: TLabel
          Left = 52
          Top = 133
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label138: TLabel
          Left = 138
          Top = 133
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label139: TLabel
          Left = 52
          Top = 158
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label140: TLabel
          Left = 138
          Top = 158
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label141: TLabel
          Left = 52
          Top = 183
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label142: TLabel
          Left = 138
          Top = 183
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label143: TLabel
          Left = 52
          Top = 208
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label144: TLabel
          Left = 138
          Top = 208
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label145: TLabel
          Left = 52
          Top = 233
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label146: TLabel
          Left = 138
          Top = 233
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object EditKPerc20: TEdit
          Left = 5
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 0
        end
        object EditKForint20: TEdit
          Left = 90
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 1
        end
        object EditKPerc21: TEdit
          Left = 5
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 2
        end
        object EditKForint21: TEdit
          Left = 90
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 3
        end
        object EditKPerc22: TEdit
          Left = 5
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 4
        end
        object EditKForint22: TEdit
          Left = 90
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 5
        end
        object EditKPerc23: TEdit
          Left = 5
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 6
        end
        object EditKForint23: TEdit
          Left = 90
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 7
        end
        object EditKPerc24: TEdit
          Left = 5
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 8
        end
        object EditKForint24: TEdit
          Left = 90
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 9
        end
        object EditKPerc25: TEdit
          Left = 5
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 10
        end
        object EditKForint25: TEdit
          Left = 90
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 11
        end
        object EditKPerc26: TEdit
          Left = 5
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 12
        end
        object EditKForint26: TEdit
          Left = 90
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 13
        end
        object EditKPerc27: TEdit
          Left = 5
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 14
        end
        object EditKForint27: TEdit
          Left = 90
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 15
        end
        object EditKPerc28: TEdit
          Left = 5
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 16
        end
        object EditKForint28: TEdit
          Left = 90
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 17
        end
        object EditKPerc29: TEdit
          Left = 5
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 18
        end
        object EditKForint29: TEdit
          Left = 90
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 19
        end
      end
      object Panel8: TPanel
        Left = 541
        Top = 10
        Width = 180
        Height = 263
        BevelOuter = bvNone
        Color = 13041663
        TabOrder = 3
        object Label147: TLabel
          Left = 52
          Top = 8
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label148: TLabel
          Left = 138
          Top = 8
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label149: TLabel
          Left = 52
          Top = 33
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label150: TLabel
          Left = 138
          Top = 33
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label151: TLabel
          Left = 52
          Top = 58
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label152: TLabel
          Left = 138
          Top = 58
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label153: TLabel
          Left = 52
          Top = 83
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label154: TLabel
          Left = 138
          Top = 83
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label155: TLabel
          Left = 52
          Top = 108
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label156: TLabel
          Left = 138
          Top = 108
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label157: TLabel
          Left = 52
          Top = 133
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label158: TLabel
          Left = 138
          Top = 133
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label159: TLabel
          Left = 52
          Top = 158
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label160: TLabel
          Left = 138
          Top = 158
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label161: TLabel
          Left = 52
          Top = 183
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label162: TLabel
          Left = 138
          Top = 183
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label163: TLabel
          Left = 52
          Top = 208
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label164: TLabel
          Left = 138
          Top = 208
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object Label165: TLabel
          Left = 52
          Top = 233
          Width = 33
          Height = 20
          Caption = 'perc'
        end
        object Label166: TLabel
          Left = 138
          Top = 233
          Width = 38
          Height = 20
          Caption = 'forint'
        end
        object EditKPerc30: TEdit
          Left = 5
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 0
        end
        object EditKForint30: TEdit
          Left = 90
          Top = 5
          Width = 44
          Height = 28
          TabOrder = 1
        end
        object EditKPerc31: TEdit
          Left = 5
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 2
        end
        object EditKForint31: TEdit
          Left = 90
          Top = 30
          Width = 44
          Height = 28
          TabOrder = 3
        end
        object EditKPerc32: TEdit
          Left = 5
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 4
        end
        object EditKForint32: TEdit
          Left = 90
          Top = 55
          Width = 44
          Height = 28
          TabOrder = 5
        end
        object EditKPerc33: TEdit
          Left = 5
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 6
        end
        object EditKForint33: TEdit
          Left = 90
          Top = 80
          Width = 44
          Height = 28
          TabOrder = 7
        end
        object EditKPerc34: TEdit
          Left = 5
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 8
        end
        object EditKForint34: TEdit
          Left = 90
          Top = 105
          Width = 44
          Height = 28
          TabOrder = 9
        end
        object EditKPerc35: TEdit
          Left = 5
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 10
        end
        object EditKForint35: TEdit
          Left = 90
          Top = 130
          Width = 44
          Height = 28
          TabOrder = 11
        end
        object EditKPerc36: TEdit
          Left = 5
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 12
        end
        object EditKForint36: TEdit
          Left = 90
          Top = 155
          Width = 44
          Height = 28
          TabOrder = 13
        end
        object EditKPerc37: TEdit
          Left = 5
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 14
        end
        object EditKForint37: TEdit
          Left = 90
          Top = 180
          Width = 44
          Height = 28
          TabOrder = 15
        end
        object EditKPerc38: TEdit
          Left = 5
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 16
        end
        object EditKForint38: TEdit
          Left = 90
          Top = 205
          Width = 44
          Height = 28
          TabOrder = 17
        end
        object EditKPerc39: TEdit
          Left = 5
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 18
        end
        object EditKForint39: TEdit
          Left = 90
          Top = 230
          Width = 44
          Height = 28
          TabOrder = 19
        end
      end
    end
  end
  object GroupBoxKedvezmenyesIdo: TGroupBox
    Left = 365
    Top = 170
    Width = 376
    Height = 66
    Caption = ' Kedvezményes idõszak '
    TabOrder = 4
    object Label85: TLabel
      Left = 10
      Top = 30
      Width = 70
      Height = 20
      Caption = 'Kezdete :'
    end
    object Label86: TLabel
      Left = 205
      Top = 30
      Width = 47
      Height = 20
      Caption = 'Vége :'
    end
    object Label167: TLabel
      Left = 134
      Top = 30
      Width = 13
      Height = 20
      Caption = ' : '
    end
    object Label168: TLabel
      Left = 306
      Top = 30
      Width = 13
      Height = 20
      Caption = ' : '
    end
    object EditKedvStartO: TEdit
      Left = 90
      Top = 27
      Width = 24
      Height = 28
      MaxLength = 2
      TabOrder = 0
      Text = '0'
    end
    object EditKedvStartP: TEdit
      Left = 150
      Top = 27
      Width = 24
      Height = 28
      MaxLength = 2
      TabOrder = 2
      Text = '0'
    end
    object EditKedvStopO: TEdit
      Left = 260
      Top = 27
      Width = 24
      Height = 28
      MaxLength = 2
      TabOrder = 4
      Text = '0'
    end
    object EditKedvStopP: TEdit
      Left = 325
      Top = 27
      Width = 24
      Height = 28
      MaxLength = 2
      TabOrder = 6
      Text = '0'
    end
    object UpDownKedvOraStart: TUpDown
      Left = 114
      Top = 27
      Width = 16
      Height = 28
      Associate = EditKedvStartO
      Min = 0
      Max = 23
      Position = 0
      TabOrder = 1
      Thousands = False
      Wrap = False
    end
    object UpDownKedvPercStart: TUpDown
      Left = 174
      Top = 27
      Width = 16
      Height = 28
      Associate = EditKedvStartP
      Min = 0
      Max = 59
      Position = 0
      TabOrder = 3
      Thousands = False
      Wrap = False
    end
    object UpDownKedvOraStop: TUpDown
      Left = 284
      Top = 27
      Width = 16
      Height = 28
      Associate = EditKedvStopO
      Min = 0
      Max = 23
      Position = 0
      TabOrder = 5
      Thousands = False
      Wrap = False
    end
    object UpDownKedvPercStop: TUpDown
      Left = 349
      Top = 27
      Width = 16
      Height = 28
      Associate = EditKedvStopP
      Min = 0
      Max = 59
      Position = 0
      TabOrder = 7
      Thousands = False
      Wrap = False
    end
  end
  object GroupBoxCsoUzemora: TGroupBox
    Left = 5
    Top = 100
    Width = 736
    Height = 66
    Caption = ' Csõ üzemóra '
    TabOrder = 2
    object Label169: TLabel
      Left = 115
      Top = 30
      Width = 61
      Height = 20
      Caption = 'Értéke : '
    end
    object Label170: TLabel
      Left = 459
      Top = 30
      Width = 160
      Height = 20
      Caption = 'Csõcsere szükséges '
    end
    object Label171: TLabel
      Left = 227
      Top = 30
      Width = 13
      Height = 20
      Caption = ' : '
    end
    object Label172: TLabel
      Left = 282
      Top = 30
      Width = 13
      Height = 20
      Caption = ' : '
    end
    object Label174: TLabel
      Left = 660
      Top = 30
      Width = 64
      Height = 20
      Caption = 'óra után.'
    end
    object EditCsoUzemoraOra: TEdit
      Left = 175
      Top = 27
      Width = 34
      Height = 28
      ReadOnly = True
      TabOrder = 1
      Text = '0'
    end
    object EditCsoUzemoraMax: TEdit
      Left = 613
      Top = 27
      Width = 44
      Height = 28
      TabOrder = 8
    end
    object UpDownCsoUzemoraPerc: TUpDown
      Left = 267
      Top = 27
      Width = 16
      Height = 28
      Associate = EditCsoUzemoraPerc
      Min = 0
      Max = 59
      Position = 0
      TabOrder = 4
      Thousands = False
      Wrap = False
    end
    object EditCsoUzemoraPerc: TEdit
      Left = 242
      Top = 27
      Width = 25
      Height = 28
      ReadOnly = True
      TabOrder = 3
      Text = '0'
    end
    object UpDownCsoUzemoraOra: TUpDown
      Left = 209
      Top = 27
      Width = 16
      Height = 28
      Associate = EditCsoUzemoraOra
      Min = 0
      Max = 999
      Position = 0
      TabOrder = 2
      Thousands = False
      Wrap = False
    end
    object UpDownCsoUzemoraMp: TUpDown
      Left = 322
      Top = 27
      Width = 16
      Height = 28
      Associate = EditCsoUzemoraMp
      Min = 0
      Max = 59
      Position = 0
      TabOrder = 6
      Thousands = False
      Wrap = False
    end
    object EditCsoUzemoraMp: TEdit
      Left = 297
      Top = 27
      Width = 25
      Height = 28
      ReadOnly = True
      TabOrder = 5
      Text = '0'
    end
    object CheckBoxCsoVisible: TCheckBox
      Left = 10
      Top = 32
      Width = 97
      Height = 17
      Caption = 'látható'
      TabOrder = 0
    end
    object BtnReset: TButton
      Left = 345
      Top = 28
      Width = 96
      Height = 25
      Caption = 'Nullázás'
      TabOrder = 7
      OnClick = BtnResetClick
    end
  end
  object GroupBoxIdoHasznalat: TGroupBox
    Left = 5
    Top = 170
    Width = 356
    Height = 66
    Caption = ' Folyamatos használat '
    TabOrder = 3
    object Label173: TLabel
      Left = 10
      Top = 30
      Width = 251
      Height = 20
      Caption = 'Maximális beírható értéke (perc) : '
    end
    object EditIdoHasznalatMax: TEdit
      Left = 267
      Top = 27
      Width = 44
      Height = 28
      TabOrder = 0
    end
  end
end

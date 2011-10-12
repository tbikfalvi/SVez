object FormInstallMain: TFormInstallMain
  Left = 304
  Top = 175
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Szolárium Telepítõ'
  ClientHeight = 464
  ClientWidth = 760
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
  object LabelPageCaption: TLabel
    Left = 5
    Top = 5
    Width = 751
    Height = 20
    AutoSize = False
    Caption = 'Fejléc - NEM KELL LEFORDÍTANI :-)'
  end
  object PanelTablazat: TPanel
    Left = 5
    Top = 30
    Width = 751
    Height = 396
    Hint = 'Szolárium adatok II.'
    TabOrder = 0
    object TabControlTablazat: TTabControl
      Left = 5
      Top = 77
      Width = 736
      Height = 312
      TabOrder = 2
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
        object Panel2: TPanel
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
        object Panel3: TPanel
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
        object Panel4: TPanel
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
        object Panel5: TPanel
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
        object Panel6: TPanel
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
        object Panel7: TPanel
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
        object Panel8: TPanel
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
        object Panel9: TPanel
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
      Top = 5
      Width = 376
      Height = 66
      Caption = ' Kedvezményes idõszak '
      TabOrder = 1
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
    object GroupBoxIdoHasznalat: TGroupBox
      Left = 5
      Top = 5
      Width = 356
      Height = 66
      Caption = ' Folyamatos használat '
      TabOrder = 0
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
        Text = '100'
      end
    end
  end
  object PanelSzolarium: TPanel
    Left = 5
    Top = 30
    Width = 751
    Height = 396
    Hint = 'Szolárium adatok I.'
    TabOrder = 1
    object GroupBoxInfra: TGroupBox
      Left = 5
      Top = 5
      Width = 741
      Height = 56
      TabOrder = 0
      object Label2: TLabel
        Left = 10
        Top = 20
        Width = 374
        Height = 20
        Caption = 'Infraszauna esetében a szauna idõ (max 240 mp) : '
      end
      object EditIdoSzauna: TEdit
        Left = 391
        Top = 17
        Width = 44
        Height = 28
        TabOrder = 0
        Text = '120'
      end
    end
    object GroupBoxNevIdo: TGroupBox
      Left = 5
      Top = 60
      Width = 741
      Height = 56
      TabOrder = 1
      object Label3: TLabel
        Left = 10
        Top = 20
        Width = 151
        Height = 20
        Caption = 'Vetkõzési idõ (mp) : '
      end
      object Label4: TLabel
        Left = 260
        Top = 20
        Width = 149
        Height = 20
        Caption = 'Utóhûtési idõ (mp) : '
      end
      object EditIdoVetkozes: TEdit
        Left = 175
        Top = 17
        Width = 56
        Height = 28
        TabOrder = 0
        Text = '60'
      end
      object EditIdoUtohutes: TEdit
        Left = 415
        Top = 17
        Width = 56
        Height = 28
        TabOrder = 1
        Text = '60'
      end
    end
    object GroupBoxCsoUzemora: TGroupBox
      Left = 5
      Top = 115
      Width = 741
      Height = 56
      TabOrder = 2
      object Label170: TLabel
        Left = 284
        Top = 20
        Width = 160
        Height = 20
        Caption = 'Csõcsere szükséges '
      end
      object Label174: TLabel
        Left = 505
        Top = 20
        Width = 64
        Height = 20
        Caption = 'óra után.'
      end
      object EditCsoUzemoraMax: TEdit
        Left = 453
        Top = 17
        Width = 44
        Height = 28
        TabOrder = 1
        Text = '600'
      end
      object CheckBoxCsoVisible: TCheckBox
        Left = 10
        Top = 20
        Width = 241
        Height = 17
        Alignment = taLeftJustify
        Caption = 'Csõ üzemóra kijelzés látható'
        TabOrder = 0
      end
    end
  end
  object PanelDirectory: TPanel
    Left = 5
    Top = 30
    Width = 751
    Height = 396
    Hint = 'Telepítési adatok'
    TabOrder = 7
    object GroupBox3: TGroupBox
      Left = 5
      Top = 5
      Width = 741
      Height = 381
      Caption = ' Telepítés célkönyvtára '
      TabOrder = 0
      object Label171: TLabel
        Left = 10
        Top = 30
        Width = 118
        Height = 20
        Caption = 'Elérési útvonal :'
      end
      object EditDirectory: TEdit
        Left = 10
        Top = 50
        Width = 601
        Height = 28
        Color = clBtnFace
        ReadOnly = True
        TabOrder = 0
      end
      object BitBtnChangeDir: TBitBtn
        Left = 615
        Top = 48
        Width = 115
        Height = 30
        Caption = 'Változtatás'
        TabOrder = 1
        OnClick = BitBtnChangeDirClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000130B0000130B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          3333333333FFFFF3333333333222223333333333F77777FFF333333222222222
          3333333777333777FF3333222333332223333377333333777FF3322233333332
          223337733333333377F3322333333333223337733333333337FF223333333333
          322377F333333333377F223333333333322377F3333333333373223333333333
          333377F3333333333333223333333333333377F33333333FFFFF223333333322
          222377FF33333377777F3223333333322223373FF3333337777F322233333333
          22233773FF333FFF777F332223333322222333773FFFFF77777F333222222222
          3323333777333777337333333222223333333333377777333333}
        Margin = 5
        NumGlyphs = 2
      end
    end
  end
  object PanelSummary: TPanel
    Left = 5
    Top = 30
    Width = 751
    Height = 396
    Hint = 'Összefoglalás'
    TabOrder = 9
    OnEnter = PanelSummaryEnter
    object GroupBox5: TGroupBox
      Left = 5
      Top = 5
      Width = 741
      Height = 386
      TabOrder = 0
      object ListBoxSummary: TListBox
        Left = 10
        Top = 20
        Width = 721
        Height = 356
        Color = clBtnFace
        ItemHeight = 20
        TabOrder = 0
      end
      object MemoProgress: TMemo
        Left = 10
        Top = 20
        Width = 721
        Height = 355
        Color = clBtnFace
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 1
        Visible = False
      end
    end
  end
  object BitBtnCancel: TBitBtn
    Left = 5
    Top = 430
    Width = 115
    Height = 30
    Caption = '&Mégsem'
    TabOrder = 3
    OnClick = BitBtnCancelClick
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      333333333333333333333333000033338833333333333333333F333333333333
      0000333911833333983333333388F333333F3333000033391118333911833333
      38F38F333F88F33300003339111183911118333338F338F3F8338F3300003333
      911118111118333338F3338F833338F3000033333911111111833333338F3338
      3333F8330000333333911111183333333338F333333F83330000333333311111
      8333333333338F3333383333000033333339111183333333333338F333833333
      00003333339111118333333333333833338F3333000033333911181118333333
      33338333338F333300003333911183911183333333383338F338F33300003333
      9118333911183333338F33838F338F33000033333913333391113333338FF833
      38F338F300003333333333333919333333388333338FFF830000333333333333
      3333333333333333333888330000333333333333333333333333333333333333
      0000}
    Margin = 5
    NumGlyphs = 2
  end
  object BitBtnPrev: TBitBtn
    Left = 262
    Top = 430
    Width = 115
    Height = 30
    Caption = '&Elõzõ'
    Enabled = False
    TabOrder = 4
    OnClick = BitBtnPrevClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      33333333333333333333333333333333333333333333333333FF333333333333
      3000333333FFFFF3F77733333000003000B033333777773777F733330BFBFB00
      E00033337FFF3377F7773333000FBFB0E000333377733337F7773330FBFBFBF0
      E00033F7FFFF3337F7773000000FBFB0E000377777733337F7770BFBFBFBFBF0
      E00073FFFFFFFF37F777300000000FB0E000377777777337F7773333330BFB00
      000033333373FF77777733333330003333333333333777333333333333333333
      3333333333333333333333333333333333333333333333333333333333333333
      3333333333333333333333333333333333333333333333333333}
    Margin = 5
    NumGlyphs = 2
  end
  object BitBtnNext: TBitBtn
    Left = 382
    Top = 430
    Width = 115
    Height = 30
    Caption = '&Következõ'
    TabOrder = 5
    OnClick = BitBtnNextClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333333333333333333FFF333333333333000333333333
      3333777FFF3FFFFF33330B000300000333337F777F777773F333000E00BFBFB0
      3333777F773333F7F333000E0BFBF0003333777F7F3337773F33000E0FBFBFBF
      0333777F7F3333FF7FFF000E0BFBF0000003777F7F3337777773000E0FBFBFBF
      BFB0777F7F33FFFFFFF7000E0BF000000003777F7FF777777773000000BFB033
      33337777773FF733333333333300033333333333337773333333333333333333
      3333333333333333333333333333333333333333333333333333333333333333
      3333333333333333333333333333333333333333333333333333}
    Margin = 5
    NumGlyphs = 2
  end
  object BitBtnExit: TBitBtn
    Left = 640
    Top = 430
    Width = 115
    Height = 30
    Caption = '&Befejezés'
    Enabled = False
    TabOrder = 6
    OnClick = BitBtnExitClick
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333330000333333333333333333333333F33333333333
      00003333344333333333333333388F3333333333000033334224333333333333
      338338F3333333330000333422224333333333333833338F3333333300003342
      222224333333333383333338F3333333000034222A22224333333338F338F333
      8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
      33333338F83338F338F33333000033A33333A222433333338333338F338F3333
      0000333333333A222433333333333338F338F33300003333333333A222433333
      333333338F338F33000033333333333A222433333333333338F338F300003333
      33333333A222433333333333338F338F00003333333333333A22433333333333
      3338F38F000033333333333333A223333333333333338F830000333333333333
      333A333333333333333338330000333333333333333333333333333333333333
      0000}
    Margin = 5
    NumGlyphs = 2
  end
  object LanguageStrings: TListBox
    Left = 125
    Top = 430
    Width = 141
    Height = 26
    Enabled = False
    ItemHeight = 20
    Items.Strings = (
      'A program további mûködése nem lehetséges.'
      'COM port megnyitása.'
      'COM port megnyitása sikeres.'
      'A hardver elérhetõ.'
      'A hardver nem elérhetõ.'
      'COM port lezárása.'
      'Szolarium Vezérlõ alkalmazás telepítése'
      'Szolarium Vezérlõ alkalmazás eltávolítása'
      'Szolarium Vezérlõ alkalmazás frissítése'
      'Telepítés könyvtára:'
      'Szoláriumok száma:'
      'Frissítés verziólépése:'
      'Figyelmeztetés'
      'Nem sikerült a következõ állomány telepítése/frissítése:'
      'Nem sikerült a következõ állomány törlése:'
      'Információ'
      'sikeresen befejezõdött.'
      'Kérdés'
      'Biztos benne, hogy megszakítja a telepítést?'
      'COM port megnyitása sikertelen.'
      
        'A hardvereszköz a következõ adatokkal van inicializálva\nSzolári' +
        'umok száma: %s\nFejléc szöveg: %s\n\nFel akarja használni ezeket' +
        ' az adatokat?'
      'Nem adta meg a szoláriumok számát.'
      'Hardvereszköz beállítása, feltöltése adatokkal ...'
      'Hardvereszköz beállítása, feltöltése adatokkal ... RENDBEN'
      'Hardvereszköz beállítása, feltöltése adatokkal ... SIKERTELEN'
      'Alkalmazás környezeti beállítások létrehozása ...'
      'Alkalmazás környezeti beállítások létrehozása ... RENDBEN'
      'Alkalmazás környezeti beállítások létrehozása ... SIKERTELEN'
      'Adatbázis állomány [%s] létrehozása ...'
      'Adatbázis állomány [%s] létrehozása ... RENDBEN'
      'Adatbázis állomány [%s] létrehozása ... SIKERTELEN'
      'Alkalmazás állomány [%s] másolása ...'
      'Alkalmazás állomány [%s] másolása ... RENDBEN'
      'Alkalmazás állomány [%s] másolása ... SIKERTELEN'
      'Bérletek adatait tartalmazó adatbázis frissítése ...'
      'Bérletek adatait tartalmazó adatbázis frissítése ... RENDBEN'
      'Bérletek adatait tartalmazó adatbázis frissítése ... SIKERTELEN'
      'Termékek adatait tartalmazó adatbázis frissítése ...'
      'Termékek adatait tartalmazó adatbázis frissítése ... RENDBEN'
      'Termékek adatait tartalmazó adatbázis frissítése ... SIKERTELEN'
      'Alkalmazás környezeti beállítások törlése ...'
      'Alkalmazás környezeti beállítások törlése ... RENDBEN'
      'Alkalmazás környezeti beállítások törlése ... SIKERTELEN'
      'Állomány [%s] törlése ...'
      'Állomány [%s] törlése ... RENDBEN'
      'Állomány [%s] törlése ... SIKERTELEN'
      'Könyvtár [%s] törlése ... '
      'Könyvtár [%s] törlése ... RENDBEN'
      'Könyvtár [%s] törlése ... SIKERTELEN')
    TabOrder = 10
    Visible = False
  end
  object BitBtnExitApp: TBitBtn
    Left = 323
    Top = 429
    Width = 115
    Height = 30
    Caption = '&Bezárás'
    Enabled = False
    TabOrder = 11
    Visible = False
    OnClick = BitBtnExitAppClick
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
  object PanelSetupType: TPanel
    Left = 5
    Top = 30
    Width = 751
    Height = 396
    Hint = 'Telepítés módja'
    TabOrder = 8
    object GroupBox4: TGroupBox
      Left = 5
      Top = 5
      Width = 741
      Height = 116
      TabOrder = 0
      object RB_Setup: TRadioButton
        Left = 15
        Top = 25
        Width = 296
        Height = 17
        Caption = 'Program telepítése'
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = RB_SetupClick
      end
      object RB_Update: TRadioButton
        Left = 15
        Top = 55
        Width = 296
        Height = 17
        Caption = 'Program frissítése'
        Enabled = False
        TabOrder = 1
        OnClick = RB_UpdateClick
      end
      object RB_Remove: TRadioButton
        Left = 15
        Top = 85
        Width = 296
        Height = 17
        Caption = 'Program eltávolítása'
        Enabled = False
        TabOrder = 2
        OnClick = RB_RemoveClick
      end
    end
  end
  object PanelHadver: TPanel
    Left = 5
    Top = 30
    Width = 751
    Height = 396
    Hint = 'Hardver és kommunikációs adatok'
    TabOrder = 2
    object GroupBox1: TGroupBox
      Left = 5
      Top = 140
      Width = 231
      Height = 246
      Caption = ' Kommunikáció '
      TabOrder = 0
      object Label1: TLabel
        Left = 10
        Top = 30
        Width = 81
        Height = 20
        Caption = 'COM port :'
      end
      object Label169: TLabel
        Left = 10
        Top = 65
        Width = 91
        Height = 20
        Caption = 'Baud Rate : '
      end
      object Label176: TLabel
        Left = 10
        Top = 100
        Width = 62
        Height = 20
        Caption = 'Paritás :'
      end
      object ComboBoxPort: TComboBox
        Left = 120
        Top = 27
        Width = 96
        Height = 28
        Style = csDropDownList
        ItemHeight = 20
        TabOrder = 1
        OnChange = ComboBoxPortChange
      end
      object ComboBoxBaudRate: TComboBox
        Left = 120
        Top = 62
        Width = 96
        Height = 28
        Style = csDropDownList
        Enabled = False
        ItemHeight = 20
        TabOrder = 2
        Items.Strings = (
          '1200'
          '2400'
          '4800'
          '9600'
          '19200'
          '38400'
          '76800'
          '115200'
          '230400')
      end
      object ComboBoxParity: TComboBox
        Left = 120
        Top = 97
        Width = 96
        Height = 28
        Style = csDropDownList
        Enabled = False
        ItemHeight = 20
        TabOrder = 3
        Items.Strings = (
          'Nincs'
          'Páratlan'
          'Páros')
      end
      object BitBtnTeszt: TBitBtn
        Left = 115
        Top = 135
        Width = 101
        Height = 30
        Caption = '&Teszt'
        TabOrder = 4
        OnClick = BitBtnTesztClick
        Glyph.Data = {
          DE010000424DDE01000000000000760000002800000024000000120000000100
          0400000000006801000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          3333333333333333333333330000333333333333333333333333F33333333333
          00003333344333333333333333388F3333333333000033334224333333333333
          338338F3333333330000333422224333333333333833338F3333333300003342
          222224333333333383333338F3333333000034222A22224333333338F338F333
          8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
          33333338F83338F338F33333000033A33333A222433333338333338F338F3333
          0000333333333A222433333333333338F338F33300003333333333A222433333
          333333338F338F33000033333333333A222433333333333338F338F300003333
          33333333A222433333333333338F338F00003333333333333A22433333333333
          3338F38F000033333333333333A223333333333333338F830000333333333333
          333A333333333333333338330000333333333333333333333333333333333333
          0000}
        Margin = 5
        NumGlyphs = 2
      end
      object BitBtnRefresh: TBitBtn
        Left = 10
        Top = 135
        Width = 101
        Height = 30
        Caption = '&Frissít'
        TabOrder = 0
        OnClick = BitBtnRefreshClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000130B0000130B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          3333333333FFFFF3333333333222223333333333F77777FFF333333222222222
          3333333777333777FF3333222333332223333377333333777FF3322233333332
          223337733333333377F3322333333333223337733333333337FF223333333333
          322377F333333333377F223333333333322377F3333333333373223333333333
          333377F3333333333333223333333333333377F33333333FFFFF223333333322
          222377FF33333377777F3223333333322223373FF3333337777F322233333333
          22233773FF333FFF777F332223333322222333773FFFFF77777F333222222222
          3323333777333777337333333222223333333333377777333333}
        Margin = 5
        NumGlyphs = 2
      end
    end
    object GroupBox2: TGroupBox
      Left = 245
      Top = 140
      Width = 501
      Height = 246
      TabOrder = 1
      object ListBoxLog: TListBox
        Left = 10
        Top = 27
        Width = 481
        Height = 204
        ItemHeight = 20
        TabOrder = 0
      end
    end
    object GroupBoxSzolariumSzam: TGroupBox
      Left = 5
      Top = 5
      Width = 741
      Height = 51
      TabOrder = 2
      object Label175: TLabel
        Left = 10
        Top = 20
        Width = 159
        Height = 20
        Caption = 'Szoláriumok száma : '
      end
      object EditSzolariumCount: TEdit
        Left = 175
        Top = 17
        Width = 56
        Height = 28
        TabOrder = 0
      end
    end
    object GroupBox6: TGroupBox
      Left = 5
      Top = 55
      Width = 741
      Height = 81
      TabOrder = 3
      object Label172: TLabel
        Left = 10
        Top = 20
        Width = 312
        Height = 20
        Caption = 'Alkalmazás fejlécében megjelenõ szöveg :'
      end
      object EditApplicationCaption: TEdit
        Left = 10
        Top = 45
        Width = 721
        Height = 28
        TabOrder = 0
      end
    end
  end
end

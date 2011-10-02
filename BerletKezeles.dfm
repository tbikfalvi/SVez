object FormBerlet: TFormBerlet
  Left = 306
  Top = 175
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Bérlettípusok kezelése'
  ClientHeight = 539
  ClientWidth = 508
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
  object GroupBoxBerletTipus: TGroupBox
    Left = 5
    Top = 260
    Width = 496
    Height = 236
    Caption = ' Bérlet típus adatok '
    TabOrder = 1
    object Label1: TLabel
      Left = 10
      Top = 30
      Width = 86
      Height = 20
      Caption = 'Elnevezés :'
    end
    object Label2: TLabel
      Left = 10
      Top = 65
      Width = 70
      Height = 20
      Caption = 'Ára (Ft) : '
    end
    object Label3: TLabel
      Left = 10
      Top = 100
      Width = 85
      Height = 20
      Caption = 'Egységek : '
    end
    object Label4: TLabel
      Left = 10
      Top = 135
      Width = 82
      Height = 20
      Caption = 'Érvényes : '
    end
    object Label5: TLabel
      Left = 148
      Top = 135
      Width = 13
      Height = 20
      Caption = ' / '
    end
    object Label6: TLabel
      Left = 190
      Top = 135
      Width = 13
      Height = 20
      Caption = ' / '
    end
    object Label7: TLabel
      Left = 148
      Top = 165
      Width = 13
      Height = 20
      Caption = ' / '
    end
    object Label8: TLabel
      Left = 190
      Top = 165
      Width = 13
      Height = 20
      Caption = ' / '
    end
    object Label9: TLabel
      Left = 235
      Top = 135
      Width = 28
      Height = 20
      Caption = '- tól'
    end
    object Label10: TLabel
      Left = 235
      Top = 165
      Width = 23
      Height = 20
      Caption = '- ig'
    end
    object Label11: TLabel
      Left = 283
      Top = 151
      Width = 34
      Height = 20
      Caption = 'vagy'
    end
    object Label12: TLabel
      Left = 376
      Top = 150
      Width = 40
      Height = 20
      Caption = 'napig'
    end
    object Label13: TLabel
      Left = 10
      Top = 200
      Width = 203
      Height = 20
      Caption = 'Egy egységhez tartozó idõ: '
    end
    object EditBTNev: TEdit
      Left = 103
      Top = 27
      Width = 263
      Height = 28
      Enabled = False
      TabOrder = 1
    end
    object EditBTAr: TEdit
      Left = 103
      Top = 62
      Width = 88
      Height = 28
      Enabled = False
      TabOrder = 2
    end
    object EditBTEgyseg: TEdit
      Left = 103
      Top = 97
      Width = 43
      Height = 28
      Enabled = False
      TabOrder = 3
    end
    object EditBTErvTolEv: TEdit
      Left = 103
      Top = 132
      Width = 43
      Height = 28
      Enabled = False
      MaxLength = 4
      TabOrder = 4
    end
    object EditBTErvTolHo: TEdit
      Left = 163
      Top = 132
      Width = 28
      Height = 28
      Enabled = False
      MaxLength = 2
      TabOrder = 5
    end
    object EditBTErvTolNap: TEdit
      Left = 205
      Top = 132
      Width = 28
      Height = 28
      Enabled = False
      MaxLength = 2
      TabOrder = 6
    end
    object EditBTErvIgEv: TEdit
      Left = 103
      Top = 162
      Width = 43
      Height = 28
      Enabled = False
      MaxLength = 4
      TabOrder = 7
    end
    object EditBTErvIgHo: TEdit
      Left = 163
      Top = 162
      Width = 28
      Height = 28
      Enabled = False
      MaxLength = 2
      TabOrder = 8
    end
    object EditBTErvIgNap: TEdit
      Left = 205
      Top = 162
      Width = 28
      Height = 28
      Enabled = False
      MaxLength = 2
      TabOrder = 9
    end
    object EditBTErvNapok: TEdit
      Left = 328
      Top = 147
      Width = 43
      Height = 28
      Enabled = False
      MaxLength = 4
      TabOrder = 10
    end
    object ButtonBTSave: TBitBtn
      Left = 375
      Top = 26
      Width = 110
      Height = 30
      Caption = 'Mentés'
      Default = True
      Enabled = False
      TabOrder = 11
      OnClick = ButtonBTSaveClick
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
    object EditBTID: TEdit
      Left = -7
      Top = 7
      Width = 33
      Height = 28
      Enabled = False
      TabOrder = 0
      Visible = False
    end
    object ButtonBTCancel: TBitBtn
      Left = 375
      Top = 61
      Width = 110
      Height = 30
      Caption = 'Mégsem'
      Default = True
      Enabled = False
      TabOrder = 12
      OnClick = ButtonBTCancelClick
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
    object EditBTEgysegido: TEdit
      Left = 215
      Top = 198
      Width = 56
      Height = 28
      TabOrder = 13
    end
  end
  object GroupBoxBerletTipusok: TGroupBox
    Left = 5
    Top = 5
    Width = 496
    Height = 251
    Caption = ' Bérlet típusok '
    TabOrder = 0
    object ButtonBTNew: TBitBtn
      Left = 375
      Top = 26
      Width = 110
      Height = 30
      Caption = 'Új'
      Default = True
      TabOrder = 1
      OnClick = ButtonBTNewClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333333B333
        333B33FF33337F3333F73BB3777BB7777BB3377FFFF77FFFF77333B000000000
        0B3333777777777777333330FFFFFFFF07333337F33333337F333330FFFFFFFF
        07333337F33333337F333330FFFFFFFF07333337F33333337F333330FFFFFFFF
        07333FF7F33333337FFFBBB0FFFFFFFF0BB37777F3333333777F3BB0FFFFFFFF
        0BBB3777F3333FFF77773330FFFF000003333337F333777773333330FFFF0FF0
        33333337F3337F37F3333330FFFF0F0B33333337F3337F77FF333330FFFF003B
        B3333337FFFF77377FF333B000000333BB33337777777F3377FF3BB3333BB333
        3BB33773333773333773B333333B3333333B7333333733333337}
      Margin = 5
      NumGlyphs = 2
    end
    object ButtonBTDelete: TBitBtn
      Left = 375
      Top = 96
      Width = 110
      Height = 30
      Caption = 'Törlés'
      Default = True
      Enabled = False
      TabOrder = 3
      OnClick = ButtonBTDeleteClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333000000000
        3333333777777777F3333330F777777033333337F3F3F3F7F3333330F0808070
        33333337F7F7F7F7F3333330F080707033333337F7F7F7F7F3333330F0808070
        33333337F7F7F7F7F3333330F080707033333337F7F7F7F7F3333330F0808070
        333333F7F7F7F7F7F3F33030F080707030333737F7F7F7F7F7333300F0808070
        03333377F7F7F7F773333330F080707033333337F7F7F7F7F333333070707070
        33333337F7F7F7F7FF3333000000000003333377777777777F33330F88877777
        0333337FFFFFFFFF7F3333000000000003333377777777777333333330777033
        3333333337FFF7F3333333333000003333333333377777333333}
      Margin = 5
      NumGlyphs = 2
    end
    object StringGridBerletTipus: TStringGrid
      Left = 10
      Top = 25
      Width = 356
      Height = 216
      ColCount = 4
      DefaultColWidth = 84
      DefaultRowHeight = 20
      FixedCols = 0
      RowCount = 2
      GridLineWidth = 0
      Options = [goRowSelect]
      ScrollBars = ssVertical
      TabOrder = 0
      OnClick = ListBoxBerletTipusokClick
    end
    object ButtonBTModify: TBitBtn
      Left = 375
      Top = 61
      Width = 110
      Height = 30
      Caption = 'Módosítás'
      Default = True
      Enabled = False
      TabOrder = 2
      OnClick = ButtonBTModifyClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333300000000
        0000333377777777777733330FFFFFFFFFF033337F3FFF3F3FF733330F000F0F
        00F033337F777373773733330FFFFFFFFFF033337F3FF3FF3FF733330F00F00F
        00F033337F773773773733330FFFFFFFFFF033337FF3333FF3F7333300FFFF00
        F0F03333773FF377F7373330FB00F0F0FFF0333733773737F3F7330FB0BF0FB0
        F0F0337337337337373730FBFBF0FB0FFFF037F333373373333730BFBF0FB0FF
        FFF037F3337337333FF700FBFBFB0FFF000077F333337FF37777E0BFBFB000FF
        0FF077FF3337773F7F37EE0BFB0BFB0F0F03777FF3733F737F73EEE0BFBF00FF
        00337777FFFF77FF7733EEEE0000000003337777777777777333}
      Margin = 5
      NumGlyphs = 2
    end
  end
  object BitBtnOk: TBitBtn
    Left = 405
    Top = 500
    Width = 96
    Height = 30
    Caption = '&Bezárás'
    Default = True
    TabOrder = 2
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
end

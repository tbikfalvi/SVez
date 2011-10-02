object FormLista: TFormLista
  Left = 254
  Top = 174
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Bérlet lista'
  ClientHeight = 734
  ClientWidth = 1016
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
  object GB_FilterMuszak: TGroupBox
    Left = 5
    Top = 5
    Width = 1006
    Height = 66
    Caption = ' Szûrés mûszak azonosító szerint '
    TabOrder = 1
    object Label3: TLabel
      Left = 10
      Top = 30
      Width = 71
      Height = 20
      Caption = 'Mûszak : '
    end
    object BtnPrevMuszak: TButton
      Left = 102
      Top = 27
      Width = 30
      Height = 30
      Caption = '<'
      TabOrder = 0
      OnClick = BtnPrevMuszakClick
    end
    object EditMuszakID: TEdit
      Left = 133
      Top = 28
      Width = 69
      Height = 28
      ReadOnly = True
      TabOrder = 1
    end
    object BtnNextMuszak: TButton
      Left = 204
      Top = 27
      Width = 30
      Height = 30
      Caption = '>'
      TabOrder = 2
      OnClick = BtnNextMuszakClick
    end
  end
  object GB_FilterDatum: TGroupBox
    Left = 5
    Top = 5
    Width = 1006
    Height = 66
    Caption = ' Szûrés dátum szerint '
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
      Left = 380
      Top = 30
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
      OnChange = DTPickerStartChange
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
      Left = 474
      Top = 27
      Width = 30
      Height = 30
      Caption = '<<'
      TabOrder = 5
      OnClick = BtnStopPrevWeekClick
    end
    object BtnStopPrevDay: TButton
      Left = 506
      Top = 27
      Width = 30
      Height = 30
      Caption = '<'
      TabOrder = 6
      OnClick = BtnStopPrevDayClick
    end
    object DTPickerStop: TDateTimePicker
      Left = 539
      Top = 28
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
      OnChange = DTPickerStopChange
    end
    object BtnStopNextDay: TButton
      Left = 652
      Top = 27
      Width = 30
      Height = 30
      Caption = '>'
      TabOrder = 8
      OnClick = BtnStopNextDayClick
    end
    object BtnStopNextWeek: TButton
      Left = 683
      Top = 27
      Width = 30
      Height = 30
      Caption = '>>'
      TabOrder = 9
      OnClick = BtnStopNextWeekClick
    end
  end
  object GB_FilterBerlet: TGroupBox
    Left = 5
    Top = 5
    Width = 1006
    Height = 66
    Caption = ' Szûrés bérlet szerint  '
    TabOrder = 2
    object Label4: TLabel
      Left = 10
      Top = 30
      Width = 143
      Height = 20
      Caption = 'Bérlet azonosítója :'
    end
    object EditBerlet: TEdit
      Left = 160
      Top = 26
      Width = 121
      Height = 28
      TabOrder = 0
      OnChange = EditBerletChange
    end
  end
  object BitBtnOk: TBitBtn
    Left = 916
    Top = 700
    Width = 96
    Height = 30
    Caption = '&Bezárás'
    Default = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ModalResult = 1
    ParentFont = False
    TabOrder = 6
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
  object BitBtnPrint: TBitBtn
    Left = 795
    Top = 700
    Width = 117
    Height = 30
    Caption = '&Nyomtatás'
    Default = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    OnClick = BitBtnPrintClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000130B0000130B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00300000000000
      00033FFFFFFFFFFFFFFF0888888888888880777777777777777F088888888888
      8880777777777777777F0000000000000000FFFFFFFFFFFFFFFF0F8F8F8F8F8F
      8F80777777777777777F08F8F8F8F8F8F9F0777777777777777F0F8F8F8F8F8F
      8F807777777777777F7F0000000000000000777777777777777F3330FFFFFFFF
      03333337F3FFFF3F7F333330F0000F0F03333337F77773737F333330FFFFFFFF
      03333337F3FF3FFF7F333330F00F000003333337F773777773333330FFFF0FF0
      33333337F3FF7F3733333330F08F0F0333333337F7737F7333333330FFFF0033
      33333337FFFF7733333333300000033333333337777773333333}
    Margin = 5
    NumGlyphs = 2
  end
  object BitBtnSave: TBitBtn
    Left = 610
    Top = 700
    Width = 180
    Height = 30
    Caption = '&Mentés állományba'
    Default = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = BitBtnSaveClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      333333FFFFFFFFFFFFF33000077777770033377777777777773F000007888888
      00037F3337F3FF37F37F00000780088800037F3337F77F37F37F000007800888
      00037F3337F77FF7F37F00000788888800037F3337777777337F000000000000
      00037F3FFFFFFFFFFF7F00000000000000037F77777777777F7F000FFFFFFFFF
      00037F7F333333337F7F000FFFFFFFFF00037F7F333333337F7F000FFFFFFFFF
      00037F7F333333337F7F000FFFFFFFFF00037F7F333333337F7F000FFFFFFFFF
      00037F7F333333337F7F000FFFFFFFFF07037F7F33333333777F000FFFFFFFFF
      0003737FFFFFFFFF7F7330099999999900333777777777777733}
    Margin = 5
    NumGlyphs = 2
  end
  object TabControlLista: TTabControl
    Left = 5
    Top = 75
    Width = 1006
    Height = 621
    TabOrder = 3
    Tabs.Strings = (
      'Lista')
    TabIndex = 0
    OnChange = TabControlListaChange
    object RichEditLista: TRichEdit
      Left = 10
      Top = 35
      Width = 986
      Height = 576
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
      WantTabs = True
    end
  end
  object PrintDialog: TPrintDialog
    Options = [poPageNums]
    Left = 795
    Top = 680
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'txt'
    Filter = 'Szöveges állományok|*.txt'
    Options = [ofHideReadOnly, ofNoChangeDir, ofEnableSizing]
    Left = 610
    Top = 680
  end
end

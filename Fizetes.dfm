object FormFizetes: TFormFizetes
  Left = 305
  Top = 169
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Fizetés'
  ClientHeight = 151
  ClientWidth = 308
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
  object Label2: TLabel
    Left = 10
    Top = 20
    Width = 86
    Height = 20
    Caption = 'Fizetendõ : '
  end
  object Label4: TLabel
    Left = 100
    Top = 20
    Width = 111
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
    Caption = '.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 215
    Top = 20
    Width = 19
    Height = 20
    Caption = 'Ft.'
  end
  object GroupBox1: TGroupBox
    Left = 5
    Top = 0
    Width = 296
    Height = 111
    TabOrder = 0
    object Label1: TLabel
      Left = 10
      Top = 20
      Width = 86
      Height = 20
      Caption = 'Fizetendõ : '
    end
    object LabelFizetendo: TLabel
      Left = 100
      Top = 20
      Width = 156
      Height = 20
      Alignment = taRightJustify
      AutoSize = False
      Caption = '.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 260
      Top = 20
      Width = 19
      Height = 20
      Caption = 'Ft.'
    end
    object Label6: TLabel
      Left = 10
      Top = 80
      Width = 83
      Height = 20
      Caption = 'Visszajár : '
    end
    object LabelVisszajaro: TLabel
      Left = 100
      Top = 80
      Width = 156
      Height = 20
      Alignment = taRightJustify
      AutoSize = False
      Caption = '.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 260
      Top = 80
      Width = 19
      Height = 20
      Caption = 'Ft.'
    end
    object Label7: TLabel
      Left = 10
      Top = 50
      Width = 61
      Height = 20
      Caption = 'Fizetett:'
    end
    object Label9: TLabel
      Left = 260
      Top = 50
      Width = 19
      Height = 20
      Caption = 'Ft.'
    end
    object EditFizetett: TEdit
      Left = 170
      Top = 48
      Width = 86
      Height = 23
      AutoSize = False
      TabOrder = 0
      OnChange = EditFizetettChange
    end
  end
  object BitBtnOk: TBitBtn
    Left = 5
    Top = 115
    Width = 96
    Height = 30
    Caption = 'Fizetve'
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = BitBtnOkClick
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
  object BitBtnKosar: TBitBtn
    Left = 105
    Top = 115
    Width = 96
    Height = 30
    Caption = 'Kosárba'
    Default = True
    ModalResult = 6
    TabOrder = 2
    OnClick = BitBtnKosarClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDD77DDDDDDD
      DDDDDDD77DDDDDDDDDDDD7778DDDDDDDDDDDD7778DDDDDDDDDDDD78888888DDD
      D7DDD78888888DDDD7DDD7888888878887DDD7888888878887DDDDD87788788F
      F8DDDDD87788788FF8DDDDDDD888788FF8DDDDDDD888788FF8DDDDDDD88D8888
      88DDDDDDD88D888888DDDDD8877778877DDDDDD8877778877DDD888887777787
      8DDD8888877777878DDD88888888888788DD88888888888788DD888888888888
      88DD88888888888888DD88888888888788DD88888888888788DD888888877777
      788D888888877777788DD88888F87877788DD88888F87877788DDDDDD8887877
      888DDDDDD8887877888DDDDDDDD88888888DDDDDDDD88888888D}
    Margin = 5
    NumGlyphs = 2
  end
  object BitBtnCancel: TBitBtn
    Left = 205
    Top = 115
    Width = 96
    Height = 30
    Caption = 'Mégsem'
    TabOrder = 3
    Kind = bkCancel
  end
end

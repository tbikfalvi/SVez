object FormPasswordChange: TFormPasswordChange
  Left = 305
  Top = 178
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Jelsz� v�ltoztat�s'
  ClientHeight = 167
  ClientWidth = 279
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
  object GroupBox1: TGroupBox
    Left = 5
    Top = 0
    Width = 266
    Height = 126
    TabOrder = 0
    object Label1: TLabel
      Left = 10
      Top = 20
      Width = 95
      Height = 20
      Caption = 'R�gi jelsz� : '
    end
    object Label2: TLabel
      Left = 10
      Top = 55
      Width = 77
      Height = 20
      Caption = '�j jelsz� : '
    end
    object Label3: TLabel
      Left = 10
      Top = 90
      Width = 103
      Height = 20
      Caption = '(m�gegyszer)'
    end
    object Edit1: TEdit
      Left = 120
      Top = 17
      Width = 135
      Height = 28
      PasswordChar = '*'
      TabOrder = 1
    end
    object Edit2: TEdit
      Left = 120
      Top = 52
      Width = 135
      Height = 28
      MaxLength = 18
      PasswordChar = '*'
      TabOrder = 2
    end
    object Edit3: TEdit
      Left = 120
      Top = 87
      Width = 135
      Height = 28
      MaxLength = 18
      PasswordChar = '*'
      TabOrder = 3
    end
    object EditOldPassword: TEdit
      Left = 0
      Top = 0
      Width = 26
      Height = 28
      Enabled = False
      TabOrder = 0
      Visible = False
    end
  end
  object BitBtnCancel: TBitBtn
    Left = 142
    Top = 130
    Width = 100
    Height = 30
    Caption = 'M�gsem'
    TabOrder = 2
    Kind = bkCancel
    Margin = 5
  end
  object BitBtnOk: TBitBtn
    Left = 37
    Top = 130
    Width = 100
    Height = 30
    Caption = 'Ment�s'
    Default = True
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
end

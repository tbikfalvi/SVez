object FormBerletHasznalat: TFormBerletHasznalat
  Left = 304
  Top = 170
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Bérlet használat'
  ClientHeight = 286
  ClientWidth = 274
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
    Left = 35
    Top = 250
    Width = 100
    Height = 30
    Caption = 'Rendben'
    Default = True
    ModalResult = 1
    TabOrder = 2
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
  object BitBtnCancel: TBitBtn
    Left = 140
    Top = 250
    Width = 100
    Height = 30
    Caption = 'Mégsem'
    TabOrder = 3
    Kind = bkCancel
    Margin = 5
  end
  object GroupBox1: TGroupBox
    Left = 5
    Top = 5
    Width = 261
    Height = 171
    Caption = ' Bérlet információk '
    TabOrder = 0
    object Label1: TLabel
      Left = 10
      Top = 65
      Width = 63
      Height = 20
      Caption = 'Típusa : '
    end
    object Label2: TLabel
      Left = 10
      Top = 100
      Width = 200
      Height = 20
      Caption = 'Felhasználható egységek : '
    end
    object Label3: TLabel
      Left = 10
      Top = 135
      Width = 82
      Height = 20
      Caption = 'Érvényes : '
    end
    object EditTipus: TEdit
      Left = 75
      Top = 62
      Width = 176
      Height = 28
      Enabled = False
      TabOrder = 0
    end
    object EditEgyseg: TEdit
      Left = 215
      Top = 97
      Width = 36
      Height = 28
      Enabled = False
      TabOrder = 1
    end
    object EditErvenyes: TEdit
      Left = 100
      Top = 132
      Width = 91
      Height = 28
      Enabled = False
      TabOrder = 2
    end
    object EditMegjegyzes: TEdit
      Left = 10
      Top = 27
      Width = 241
      Height = 28
      Enabled = False
      TabOrder = 3
    end
  end
  object GroupBox2: TGroupBox
    Left = 5
    Top = 180
    Width = 261
    Height = 66
    Caption = ' Felhasználandó bérlet ... '
    TabOrder = 1
    object Label4: TLabel
      Left = 10
      Top = 30
      Width = 137
      Height = 20
      Caption = 'egységek száma : '
    end
    object ComboBoxHasznalat: TComboBox
      Left = 155
      Top = 27
      Width = 56
      Height = 28
      Style = csDropDownList
      Enabled = False
      ItemHeight = 20
      TabOrder = 0
    end
  end
end

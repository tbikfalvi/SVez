object FormDialogSelectDir: TFormDialogSelectDir
  Left = 302
  Top = 144
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'K�nyvt�r v�laszt�s'
  ClientHeight = 364
  ClientWidth = 292
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 16
  object GroupBox1: TGroupBox
    Left = 5
    Top = 45
    Width = 281
    Height = 271
    TabOrder = 0
    object DriveComboBox: TDriveComboBox
      Left = 10
      Top = 20
      Width = 261
      Height = 22
      DirList = DirectoryListBox
      TabOrder = 0
    end
    object DirectoryListBox: TDirectoryListBox
      Left = 10
      Top = 50
      Width = 261
      Height = 211
      DirLabel = LabelDir
      ItemHeight = 16
      TabOrder = 1
    end
  end
  object BitBtnOk: TBitBtn
    Left = 44
    Top = 325
    Width = 100
    Height = 30
    Caption = 'Rendben'
    Default = True
    ModalResult = 1
    TabOrder = 1
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
    Left = 149
    Top = 325
    Width = 100
    Height = 30
    Cancel = True
    Caption = 'M�gsem'
    ModalResult = 2
    TabOrder = 2
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
  object GroupBox2: TGroupBox
    Left = 5
    Top = 0
    Width = 281
    Height = 46
    TabOrder = 3
    object LabelDir: TLabel
      Left = 10
      Top = 20
      Width = 129
      Height = 16
      Caption = 'D:\Development\szoli'
    end
  end
end

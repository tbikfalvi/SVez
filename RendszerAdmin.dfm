object SystemAdmin: TSystemAdmin
  Left = 277
  Top = 174
  Width = 1000
  Height = 740
  Caption = 'Rendszer Adminisztr�tori vez�rl�pult'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 5
    Top = 5
    Width = 141
    Height = 391
    Caption = ' Adatb�zis '
    TabOrder = 0
    object RB_Berlet: TRadioButton
      Left = 10
      Top = 20
      Width = 113
      Height = 17
      Caption = 'B�rlet'
      TabOrder = 0
    end
    object RB_Berlettipus: TRadioButton
      Left = 10
      Top = 40
      Width = 113
      Height = 17
      Caption = 'B�rlett�pus'
      Enabled = False
      TabOrder = 1
    end
    object RB_Berlethasznalat: TRadioButton
      Left = 10
      Top = 60
      Width = 113
      Height = 17
      Caption = 'B�rlethaszn�lat'
      Enabled = False
      TabOrder = 2
    end
    object RB_Konyv: TRadioButton
      Left = 10
      Top = 80
      Width = 113
      Height = 17
      Caption = 'K�nyv'
      Enabled = False
      TabOrder = 3
    end
    object RB_Solkonyv: TRadioButton
      Left = 10
      Top = 100
      Width = 113
      Height = 17
      Caption = 'Szol�riumk�nyv'
      Enabled = False
      TabOrder = 4
    end
    object RB_Penztarkonyv: TRadioButton
      Left = 10
      Top = 120
      Width = 113
      Height = 17
      Caption = 'P�nzt�rk�nyv'
      TabOrder = 5
    end
    object RB_Szolarium: TRadioButton
      Left = 10
      Top = 140
      Width = 113
      Height = 17
      Caption = 'Szol�rium'
      TabOrder = 6
    end
  end
  object GroupBox2: TGroupBox
    Left = 150
    Top = 5
    Width = 836
    Height = 391
    Caption = ' Adat rekordok '
    TabOrder = 1
    object RekordLista: TStringGrid
      Left = 10
      Top = 20
      Width = 816
      Height = 361
      FixedCols = 0
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
      TabOrder = 0
    end
  end
  object GroupBox3: TGroupBox
    Left = 5
    Top = 505
    Width = 586
    Height = 51
    Caption = ' Adat k�dol�s / dek�dol�s '
    TabOrder = 2
    object EditKod: TEdit
      Left = 10
      Top = 20
      Width = 446
      Height = 21
      TabOrder = 0
    end
    object BtnCode: TButton
      Left = 460
      Top = 20
      Width = 116
      Height = 22
      Caption = 'K�dol�s / Dek�dol�s'
      TabOrder = 1
      OnClick = BtnCodeClick
    end
  end
end

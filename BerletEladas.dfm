object FormBerletEladas: TFormBerletEladas
  Left = 306
  Top = 171
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Bérlet eladás'
  ClientHeight = 320
  ClientWidth = 446
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
  object BitBtnOk: TBitBtn
    Left = 38
    Top = 285
    Width = 151
    Height = 30
    Caption = 'Fizetés azonnal'
    Default = True
    TabOrder = 1
    OnClick = BitBtnOkClick
    Glyph.Data = {
      36060000424D3606000000000000360000002800000020000000100000000100
      18000000000000060000C40E0000C40E00000000000000000000FF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFABD5E076C4DA69B5CB87C9
      D9CFE3E8FF00FFFF00FFFF00FFFF00FFFF00FFFCFCFCF5F5F5FDFDFDFF00FFFF
      00FFFBFBFBD3D3D3C2C2C2B3B3B3C6C6C6E1E1E1FF00FFFF00FFFF00FFFF00FF
      8ECADA58B5CF50ADC862B5CBABD3DCFF00FF87C2D14FADC554B5CD4EA7BF4CA4
      BC4BA4BAB4D2D9FF00FFFF00FFF6F6F6C8C8C8B3B3B3AAAAAAB3B3B3D0D0D0F8
      F8F8BFBFBFA9A9A9B2B2B2A4A4A4A1A1A1A1A1A1D0D0D0FF00FFFF00FF75BACC
      51AAC254B9D250A5BC4EA9C14BA5BC79B2C353A5BE4BA7C151C0DB5FADBF4BBA
      D44EAFC65099ACEBEFF1FF00FFB8B8B8A7A7A7B6B6B6A2A2A2A6A6A6A2A2A2B0
      B0B0A3A3A3A5A5A5BCBCBCA9A9A9B7B7B7ACACAC969696EDEDEDBEDAE255A6BF
      4CA3BC4DB8D35BA9BB49B3CC4DADC364A7BC4EA3BD52AAC157AABF4F9EB44BA0
      B64BACC352A9BFAFCED6D8D8D8A4A4A4A0A0A0B4B4B4A5A5A5B0B0B0A9A9A9A5
      A5A5A1A1A1A7A7A7A7A7A79C9C9C9D9D9DA9A9A9A5A5A5CCCCCC91BFCF4CA0B9
      50AFC858ADC355A6BD4EA5BC4AADC560AAC14CA5BF55ABC350ABC456A8BF4BA9
      C14DA9C053A9BE9DC3CEBEBEBE9E9E9EACACACAAAAAAA4A4A4A2A2A2A9A9A9A8
      A8A8A3A3A3A9A9A9A8A8A8A6A6A6A6A6A6A5A5A5A5A5A5C1C1C188B8C84EA7BF
      58AAC151AAC155AAC14DA9BF50A9BF68ABBF56A7BC50A5BC50A3B959B1C54BA4
      B952A8BD4B94A7B8D2D9B6B6B6A4A4A4A8A8A8A7A7A7A8A8A8A5A5A5A5A5A5A9
      A9A9A4A4A4A2A2A2A0A0A0ADADADA1A1A1A5A5A5919191D1D1D1A6CBD654A3B9
      50A7BE4EA4BA59B0C34BA3B850A6BC66A6B750A8C14EA1B653AABF55A9BD479F
      B4469CB259A3B6F5F9F9C9C9C9A1A1A1A4A4A4A1A1A1ACACACA0A0A0A2A2A2A3
      A3A3A6A6A69E9E9EA6A6A6A6A6A69C9C9C999999A0A0A0F7F7F7FF00FF56ADC5
      50A5BA52A9BE56AABE479DB2459AAF57A6B967B2C557B5CA50A7BC4B9EB54C9F
      B159A2B5FF00FFFF00FFEDEDEDAAAAAAA2A2A2A5A5A5A7A7A79A9A9A979797A3
      A3A3AFAFAFB1B1B1A3A3A39C9C9C9B9B9B9F9F9FE7E7E7FF00FFFF00FFFF00FF
      63B8CA50ACC34CA1B84AA0B35CA6B95EBFD861B1C459B6CC61BBD15BA7BB89BA
      C7FF00FFFF00FFFF00FFFF00FFEAEAEAB4B4B4A9A9A99F9F9F9D9D9DA3A3A3BB
      BBBBAEAEAEB3B3B3B8B8B8A4A4A4B8B8B8ECECECFF00FFFF00FFFF00FFFF00FF
      FF00FFC2E2EA80B8C959A0B55EAFC455A9BF4F9FB54C9FB54BA9C051ACC29FC5
      CFFF00FFFF00FFFF00FFFF00FFFF00FFFBFBFBE0E0E0B6B6B69E9E9EACACACA6
      A6A69C9C9C9C9C9CA5A5A5A9A9A9C3C3C3FF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FF91BECE4BA2BB55ADC550ACC553A6BD4EAAC04DAAC052ABC08CB9
      C6FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFBCBCBC9F9F9FAAAAAAA9
      A9A9A3A3A3A6A6A6A6A6A6A7A7A7B8B8B8FF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFA5C9D554A3B954A9C04FA3B95AB1C54CA4BA51A9BF4D96A9A4C6
      CFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFC7C7C7A1A1A1A6A6A6A0
      A0A0ADADADA1A1A1A5A5A5939393C4C4C4FF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FF52A8C14FA2B84FA5BB59ADC1489FB4459CB1519FB3FF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFEAEAEAA6A6A69F9F9FA2
      A2A2AAAAAA9C9C9C9898989C9C9CEFEFEFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFC0E0E959B6CB50A8BC4DA0B64B9EB1539EB3FF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFDEDEDEB3B3B3A4
      A4A49D9D9D9B9B9B9C9C9CE0E0E0FF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFA2D7E490C8D698C6D2FF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFF0F0F0D4
      D4D4C6C6C6C3C3C3E5E5E5FF00FFFF00FFFF00FFFF00FFFF00FF}
    Margin = 5
    NumGlyphs = 2
  end
  object BitBtnCancel: TBitBtn
    Left = 303
    Top = 285
    Width = 105
    Height = 30
    Caption = 'Mégsem'
    TabOrder = 3
    Kind = bkCancel
    Margin = 5
  end
  object GroupBox1: TGroupBox
    Left = 5
    Top = 5
    Width = 436
    Height = 276
    Caption = ' Új bérlet adatai '
    TabOrder = 0
    object Label2: TLabel
      Left = 10
      Top = 100
      Width = 54
      Height = 20
      Caption = 'Típus : '
    end
    object Label3: TLabel
      Left = 10
      Top = 135
      Width = 68
      Height = 20
      Caption = 'Egység : '
    end
    object Label4: TLabel
      Left = 10
      Top = 170
      Width = 82
      Height = 20
      Caption = 'Érvényes : '
    end
    object Label6: TLabel
      Left = 165
      Top = 170
      Width = 13
      Height = 20
      Caption = ' / '
    end
    object Label7: TLabel
      Left = 207
      Top = 170
      Width = 13
      Height = 20
      Caption = ' / '
    end
    object Label9: TLabel
      Left = 250
      Top = 170
      Width = 28
      Height = 20
      Caption = '- tól'
    end
    object Label8: TLabel
      Left = 165
      Top = 205
      Width = 13
      Height = 20
      Caption = ' / '
    end
    object Label10: TLabel
      Left = 207
      Top = 205
      Width = 13
      Height = 20
      Caption = ' / '
    end
    object Label11: TLabel
      Left = 250
      Top = 205
      Width = 23
      Height = 20
      Caption = '- ig'
    end
    object Label12: TLabel
      Left = 10
      Top = 240
      Width = 70
      Height = 20
      Caption = 'Ára (Ft) : '
    end
    object Label13: TLabel
      Left = 10
      Top = 30
      Width = 77
      Height = 20
      Caption = 'Vonalkód :'
    end
    object Label1: TLabel
      Left = 10
      Top = 65
      Width = 102
      Height = 20
      Caption = 'Megjegyzés : '
    end
    object ComboBoxTipus: TComboBox
      Left = 115
      Top = 97
      Width = 211
      Height = 28
      Style = csDropDownList
      ItemHeight = 20
      TabOrder = 3
      OnChange = ComboBoxTipusChange
    end
    object EditBTEgyseg: TEdit
      Left = 115
      Top = 132
      Width = 36
      Height = 28
      Enabled = False
      TabOrder = 4
    end
    object EditBTErvTolEv: TEdit
      Left = 115
      Top = 167
      Width = 45
      Height = 28
      Enabled = False
      MaxLength = 4
      TabOrder = 5
    end
    object EditBTErvTolHo: TEdit
      Left = 180
      Top = 167
      Width = 25
      Height = 28
      Enabled = False
      MaxLength = 2
      TabOrder = 6
    end
    object EditBTErvTolNap: TEdit
      Left = 222
      Top = 167
      Width = 25
      Height = 28
      Enabled = False
      MaxLength = 2
      TabOrder = 7
    end
    object EditBTErvIgEv: TEdit
      Left = 115
      Top = 202
      Width = 45
      Height = 28
      Enabled = False
      MaxLength = 4
      TabOrder = 8
    end
    object EditBTErvIgHo: TEdit
      Left = 180
      Top = 202
      Width = 25
      Height = 28
      Enabled = False
      MaxLength = 2
      TabOrder = 9
    end
    object EditBTErvIgNap: TEdit
      Left = 222
      Top = 202
      Width = 25
      Height = 28
      Enabled = False
      MaxLength = 2
      TabOrder = 10
    end
    object EditBTAr: TEdit
      Left = 115
      Top = 237
      Width = 66
      Height = 28
      Enabled = False
      TabOrder = 11
    end
    object EditBTID: TEdit
      Left = 0
      Top = 10
      Width = 21
      Height = 28
      Enabled = False
      TabOrder = 0
      Visible = False
    end
    object EditVonalkod: TEdit
      Left = 115
      Top = 27
      Width = 136
      Height = 28
      TabOrder = 1
      OnExit = EditVonalkodExit
    end
    object EditMegjegyzes: TEdit
      Left = 115
      Top = 62
      Width = 311
      Height = 28
      TabOrder = 2
    end
  end
  object BitBtnKosar: TBitBtn
    Left = 193
    Top = 285
    Width = 105
    Height = 30
    Caption = 'Kosárba'
    Default = True
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
end

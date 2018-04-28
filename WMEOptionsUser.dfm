object frmOptionsUser: TfrmOptionsUser
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMaximize]
  BorderStyle = bsToolWindow
  Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
  ClientHeight = 240
  ClientWidth = 336
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Segoe UI'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 21
  object Bevel: TBevel
    Left = 16
    Top = 176
    Width = 304
    Height = 4
    Shape = bsTopLine
  end
  object btnCancel: TButton
    Left = 224
    Top = 192
    Width = 96
    Height = 32
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 6
  end
  object btnOk: TButton
    Left = 112
    Top = 192
    Width = 96
    Height = 32
    Caption = 'OK'
    Default = True
    TabOrder = 5
    OnClick = btnOkClick
  end
  object eName: TLabeledEdit
    Left = 16
    Top = 40
    Width = 168
    Height = 29
    EditLabel.Width = 36
    EditLabel.Height = 21
    EditLabel.Caption = #1060#1048#1054
    MaxLength = 24
    TabOrder = 0
  end
  object ePass: TLabeledEdit
    Left = 200
    Top = 40
    Width = 120
    Height = 29
    EditLabel.Width = 53
    EditLabel.Height = 21
    EditLabel.Caption = #1055#1072#1088#1086#1083#1100
    PasswordChar = '#'
    TabOrder = 1
  end
  object eTabNum: TLabeledEdit
    Left = 16
    Top = 96
    Width = 136
    Height = 29
    EditLabel.Width = 128
    EditLabel.Height = 21
    EditLabel.Caption = #1058#1072#1073#1077#1083#1100#1085#1099#1081' '#1085#1086#1084#1077#1088
    MaxLength = 8
    TabOrder = 2
  end
  object eShiftNum: TLabeledEdit
    Left = 200
    Top = 96
    Width = 120
    Height = 29
    EditLabel.Width = 46
    EditLabel.Height = 21
    EditLabel.Caption = #1057#1084#1077#1085#1072
    MaxLength = 4
    TabOrder = 3
  end
  object cboxAdmin: TCheckBox
    Left = 16
    Top = 144
    Width = 304
    Height = 18
    Caption = #1040#1076#1084#1080#1085#1080#1089#1090#1088#1072#1090#1086#1088
    TabOrder = 4
  end
end

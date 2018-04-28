object frmOptionsVanType: TfrmOptionsVanType
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMaximize]
  BorderStyle = bsToolWindow
  Caption = 'VanType'
  ClientHeight = 206
  ClientWidth = 328
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
    Top = 141
    Width = 296
    Height = 4
    Shape = bsTopLine
  end
  object btnCancel: TButton
    Left = 216
    Top = 158
    Width = 96
    Height = 32
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 3
  end
  object btnOk: TButton
    Left = 104
    Top = 158
    Width = 96
    Height = 32
    Caption = 'OK'
    Default = True
    TabOrder = 2
    OnClick = btnOkClick
  end
  object eCode: TLabeledEdit
    Left = 16
    Top = 40
    Width = 80
    Height = 29
    EditLabel.Width = 27
    EditLabel.Height = 21
    EditLabel.Caption = #1050#1086#1076
    MaxLength = 24
    NumbersOnly = True
    TabOrder = 0
  end
  object eName: TLabeledEdit
    Left = 112
    Top = 40
    Width = 200
    Height = 29
    EditLabel.Width = 107
    EditLabel.Height = 21
    EditLabel.Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
    TabOrder = 1
  end
  object eAxisCount: TLabeledEdit
    Left = 16
    Top = 96
    Width = 80
    Height = 29
    EditLabel.Width = 86
    EditLabel.Height = 21
    EditLabel.Caption = #1050#1086#1083'-'#1074#1086' '#1086#1089#1077#1081
    NumbersOnly = True
    TabOrder = 4
  end
end

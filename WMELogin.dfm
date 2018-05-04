object frmLogin: TfrmLogin
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1042#1093#1086#1076
  ClientHeight = 238
  ClientWidth = 352
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Segoe UI'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 21
  object lblPass: TLabel
    Left = 16
    Top = 96
    Width = 53
    Height = 21
    Caption = #1055#1072#1088#1086#1083#1100
    FocusControl = ePass
  end
  object lblUser: TLabel
    Left = 16
    Top = 16
    Width = 99
    Height = 21
    Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
    FocusControl = cboxUser
  end
  object Bevel: TBevel
    Left = 16
    Top = 174
    Width = 320
    Height = 4
    Shape = bsTopLine
  end
  object btnOk: TButton
    Left = 128
    Top = 190
    Width = 96
    Height = 32
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 2
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 240
    Top = 190
    Width = 96
    Height = 32
    Cancel = True
    Caption = #1047#1072#1082#1088#1099#1090#1100
    ModalResult = 2
    TabOrder = 3
  end
  object ePass: TEdit
    Left = 16
    Top = 128
    Width = 320
    Height = 29
    PasswordChar = '#'
    TabOrder = 1
  end
  object cboxUser: TComboBox
    Left = 16
    Top = 48
    Width = 320
    Height = 29
    Style = csDropDownList
    DropDownCount = 10
    TabOrder = 0
  end
end

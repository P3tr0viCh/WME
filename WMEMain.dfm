object Main: TMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1055'3'#1090#1088'0'#1074#1080#1063#1098
  ClientHeight = 228
  ClientWidth = 560
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
  object btnAbout: TButton
    Left = 16
    Top = 144
    Width = 248
    Height = 48
    Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
    TabOrder = 2
    OnClick = btnAboutClick
  end
  object btnClose: TButton
    Left = 296
    Top = 144
    Width = 248
    Height = 48
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 5
    OnClick = btnCloseClick
  end
  object btnOptions: TButton
    Left = 296
    Top = 80
    Width = 248
    Height = 48
    Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
    TabOrder = 4
    OnClick = btnOptionsClick
  end
  object btnManual: TButton
    Left = 16
    Top = 16
    Width = 248
    Height = 48
    Caption = #1042#1074#1086#1076' '#1076#1072#1085#1085#1099#1093
    TabOrder = 0
    OnClick = btnManualClick
  end
  object btnDatabase: TButton
    Left = 16
    Top = 80
    Width = 248
    Height = 48
    Caption = #1057#1087#1080#1089#1086#1082' '#1074#1079#1074#1077#1096#1080#1074#1072#1085#1080#1081
    TabOrder = 1
    OnClick = btnDatabaseClick
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 208
    Width = 560
    Height = 20
    Panels = <
      item
        Width = 200
      end
      item
        Width = 50
      end>
  end
  object btnOperator: TButton
    Left = 296
    Top = 16
    Width = 248
    Height = 48
    Caption = #1054#1087#1077#1088#1072#1090#1086#1088
    TabOrder = 3
    OnClick = btnOperatorClick
  end
  object ADOConnection: TADOConnection
    LoginPrompt = False
    Mode = cmShareDenyNone
    Left = 224
    Top = 32
  end
  object ADOQuery: TADOQuery
    Parameters = <>
    Left = 224
    Top = 88
  end
end

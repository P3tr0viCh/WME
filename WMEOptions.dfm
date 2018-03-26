object frmOptions: TfrmOptions
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 448
  ClientWidth = 640
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Segoe UI'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    640
    448)
  PixelsPerInch = 96
  TextHeight = 21
  object btnOk: TButton
    Left = 416
    Top = 400
    Width = 96
    Height = 32
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object btnCancel: TButton
    Left = 528
    Top = 400
    Width = 96
    Height = 32
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 2
  end
  object PageControl: TPageControl
    Left = 152
    Top = 16
    Width = 472
    Height = 368
    ActivePage = tsDatabase
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 0
    StyleElements = [seFont, seClient]
    object tsDatabase: TTabSheet
      Caption = 'tsDatabase'
      TabVisible = False
      DesignSize = (
        464
        358)
      object Label2: TLabel
        Left = 16
        Top = 8
        Width = 286
        Height = 24
        Caption = #1055#1086#1076#1082#1083#1102#1095#1077#1085#1080#1077' '#1082' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1073#1072#1079#1077' '#1076#1072#1085#1085#1099#1093
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentFont = False
      end
      object bvlDB: TBevel
        Left = 16
        Top = 168
        Width = 432
        Height = 1
        Anchors = [akLeft, akTop, akRight]
        Shape = bsTopLine
      end
      object eDBUser: TLabeledEdit
        Left = 16
        Top = 122
        Width = 120
        Height = 29
        EditLabel.Width = 44
        EditLabel.Height = 21
        EditLabel.Caption = #1051#1086#1075#1080#1085
        TabOrder = 2
      end
      object eDBPass: TLabeledEdit
        Left = 152
        Top = 122
        Width = 136
        Height = 29
        EditLabel.Width = 53
        EditLabel.Height = 21
        EditLabel.Caption = #1055#1072#1088#1086#1083#1100
        PasswordChar = '#'
        TabOrder = 3
      end
      object btnDBConnectionCheck: TButton
        Left = 312
        Top = 119
        Width = 128
        Height = 32
        Anchors = [akLeft, akTop, akRight]
        Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100
        TabOrder = 5
        OnClick = btnDBConnectionCheckClick
      end
      object eDBServer: TLabeledEdit
        Left = 16
        Top = 66
        Width = 120
        Height = 29
        EditLabel.Width = 32
        EditLabel.Height = 21
        EditLabel.Caption = #1061#1086#1089#1090
        TabOrder = 0
      end
      object eDBPort: TLabeledEdit
        Left = 152
        Top = 66
        Width = 64
        Height = 29
        EditLabel.Width = 36
        EditLabel.Height = 21
        EditLabel.Caption = #1055#1086#1088#1090
        TabOrder = 1
      end
      object btnDBConnectionDefault: TButton
        Left = 312
        Top = 63
        Width = 128
        Height = 32
        Anchors = [akLeft, akTop, akRight]
        Caption = #1055#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
        TabOrder = 4
        OnClick = btnDBConnectionDefaultClick
      end
      object btnDBCreate: TButton
        Left = 16
        Top = 184
        Width = 176
        Height = 32
        Anchors = [akLeft, akTop, akRight]
        Caption = #1057#1086#1079#1076#1072#1090#1100' '#1073#1072#1079#1091' '#1076#1072#1085#1085#1099#1093
        TabOrder = 6
        OnClick = btnDBConnectionDefaultClick
      end
      object btnDBDelete: TButton
        Left = 208
        Top = 184
        Width = 176
        Height = 32
        Anchors = [akLeft, akTop, akRight]
        Caption = #1059#1076#1072#1083#1080#1090#1100' '#1073#1072#1079#1091' '#1076#1072#1085#1085#1099#1093
        TabOrder = 7
        OnClick = btnDBConnectionDefaultClick
      end
    end
    object tsUsers: TTabSheet
      Caption = 'tsUsers'
      ImageIndex = 1
      TabVisible = False
      ExplicitTop = 32
      ExplicitWidth = 281
      ExplicitHeight = 157
      object Label1: TLabel
        Left = 16
        Top = 16
        Width = 88
        Height = 21
        Caption = 'TODO: Users'
      end
    end
  end
  object pnlButtons: TPanel
    Left = 0
    Top = 0
    Width = 152
    Height = 448
    Anchors = [akLeft, akTop, akBottom]
    BevelOuter = bvNone
    TabOrder = 3
    DesignSize = (
      152
      448)
    object btnDatabase: TButton
      Left = 16
      Top = 16
      Width = 120
      Height = 32
      Anchors = [akLeft, akTop, akRight]
      Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
      TabOrder = 0
      OnClick = btnPageSelectClick
    end
    object btnUsers: TButton
      Left = 16
      Top = 56
      Width = 120
      Height = 32
      Anchors = [akLeft, akTop, akRight]
      Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1080
      TabOrder = 1
      OnClick = btnPageSelectClick
    end
  end
end

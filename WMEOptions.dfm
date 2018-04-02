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
  Padding.Left = 16
  Padding.Top = 16
  Padding.Right = 16
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 21
  object PanelMain: TPanel
    Left = 16
    Top = 16
    Width = 608
    Height = 368
    Align = alClient
    BevelOuter = bvLowered
    TabOrder = 0
    object PageControl: TPageControl
      Left = 1
      Top = 1
      Width = 606
      Height = 366
      ActivePage = tsDatabase
      Align = alClient
      MultiLine = True
      TabOrder = 0
      StyleElements = [seFont, seClient]
      object tsDatabase: TTabSheet
        Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
        DesignSize = (
          598
          330)
        object lblDBConnection: TLabel
          Left = 16
          Top = 8
          Width = 286
          Height = 21
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
          Width = 566
          Height = 1
          Anchors = [akLeft, akTop, akRight]
          Shape = bsTopLine
          ExplicitWidth = 432
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
          Width = 152
          Height = 29
          EditLabel.Width = 53
          EditLabel.Height = 21
          EditLabel.Caption = #1055#1072#1088#1086#1083#1100
          PasswordChar = '#'
          TabOrder = 3
        end
        object btnDBConnectionCheck: TButton
          Left = 320
          Top = 119
          Width = 120
          Height = 32
          Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100
          TabOrder = 5
          OnClick = btnDBConnectionCheckClick
        end
        object eDBHost: TLabeledEdit
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
          Left = 320
          Top = 63
          Width = 120
          Height = 32
          Caption = #1055#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
          TabOrder = 4
          OnClick = btnDBConnectionDefaultClick
        end
        object btnDBCreate: TButton
          Left = 16
          Top = 184
          Width = 168
          Height = 32
          Caption = #1057#1086#1079#1076#1072#1090#1100' '#1073#1072#1079#1091' '#1076#1072#1085#1085#1099#1093
          TabOrder = 6
          OnClick = btnDBCreateClick
        end
        object btnDBDelete: TButton
          Left = 196
          Top = 184
          Width = 168
          Height = 32
          Caption = #1059#1076#1072#1083#1080#1090#1100' '#1073#1072#1079#1091' '#1076#1072#1085#1085#1099#1093
          TabOrder = 7
          OnClick = btnDBDeleteClick
        end
      end
      object tsUsers: TTabSheet
        Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1080
        ImageIndex = 1
        object sgUsers: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goFixedColClick]
          TabOrder = 0
          OnDblClick = sgUsersDblClick
          OnFixedCellClick = sgUsersFixedCellClick
        end
        object btnUsersAdd: TButton
          Left = 16
          Top = 282
          Width = 96
          Height = 32
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnUsersChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnUsersDelete: TButton
          Left = 240
          Top = 282
          Width = 96
          Height = 32
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
    end
  end
  object PanelButtons: TPanel
    Left = 16
    Top = 384
    Width = 608
    Height = 64
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      608
      64)
    object btnOk: TButton
      Left = 400
      Top = 16
      Width = 96
      Height = 32
      Anchors = [akTop, akRight]
      Caption = 'OK'
      Default = True
      ModalResult = 1
      TabOrder = 0
      OnClick = btnOkClick
    end
    object btnCancel: TButton
      Left = 512
      Top = 16
      Width = 96
      Height = 32
      Anchors = [akTop, akRight]
      Cancel = True
      Caption = #1054#1090#1084#1077#1085#1072
      ModalResult = 2
      TabOrder = 1
    end
  end
end

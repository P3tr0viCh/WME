object frmOptions: TfrmOptions
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 472
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
  Padding.Bottom = 16
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
    Height = 392
    Align = alClient
    BevelOuter = bvLowered
    TabOrder = 0
    object PageControl: TPageControl
      Left = 1
      Top = 1
      Width = 606
      Height = 390
      ActivePage = tsInvoiceSuppliers
      Align = alClient
      MultiLine = True
      TabOrder = 0
      StyleElements = [seFont, seClient]
      object tsDatabase: TTabSheet
        Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
        DesignSize = (
          598
          328)
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
          NumbersOnly = True
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
          ColCount = 2
          DefaultDrawing = False
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goFixedColClick]
          TabOrder = 0
          OnDblClick = sgUsersDblClick
          OnDrawCell = sgUsersDrawCell
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
      object tsVanTypes: TTabSheet
        Caption = #1056#1086#1076' '#1074#1072#1075#1086#1085#1072
        ImageIndex = 2
        object sgVanTypes: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          ColCount = 2
          DefaultDrawing = False
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goFixedColClick]
          TabOrder = 0
          OnDblClick = sgUsersDblClick
          OnDrawCell = sgVanTypesDrawCell
          OnFixedCellClick = sgUsersFixedCellClick
        end
        object btnVanTypesAdd: TButton
          Left = 16
          Top = 282
          Width = 96
          Height = 32
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnVanTypesChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnVanTypesDelete: TButton
          Left = 240
          Top = 282
          Width = 96
          Height = 32
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
      object tsCargoTypes: TTabSheet
        Caption = #1056#1086#1076' '#1075#1088#1091#1079#1072
        ImageIndex = 3
        object sgCargoTypes: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          ColCount = 2
          DefaultDrawing = False
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goFixedColClick]
          TabOrder = 0
          OnDblClick = sgUsersDblClick
          OnDrawCell = sgVanCatalogDrawCell
          OnFixedCellClick = sgUsersFixedCellClick
        end
        object btnCargoTypesAdd: TButton
          Left = 16
          Top = 282
          Width = 96
          Height = 32
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnCargoTypesChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnCargoTypesDelete: TButton
          Left = 240
          Top = 282
          Width = 96
          Height = 32
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
      object tsDepartStations: TTabSheet
        Caption = #1057#1090#1072#1085#1094#1080#1103' '#1086#1090#1087#1088#1072#1074#1083#1077#1085#1080#1103
        ImageIndex = 4
        object sgDepartStations: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          ColCount = 2
          DefaultDrawing = False
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goFixedColClick]
          TabOrder = 0
          OnDblClick = sgUsersDblClick
          OnDrawCell = sgVanCatalogDrawCell
          OnFixedCellClick = sgUsersFixedCellClick
        end
        object btnDepartStationsAdd: TButton
          Left = 16
          Top = 282
          Width = 96
          Height = 32
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnDepartStationsChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnDepartStationsDelete: TButton
          Left = 240
          Top = 282
          Width = 96
          Height = 32
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
      object tsPurposeStations: TTabSheet
        Caption = #1057#1090#1072#1085#1094#1080#1103' '#1085#1072#1079#1085#1072#1095#1077#1085#1080#1103
        ImageIndex = 5
        object sgPurposeStations: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          ColCount = 2
          DefaultDrawing = False
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goFixedColClick]
          TabOrder = 0
          OnDblClick = sgUsersDblClick
          OnDrawCell = sgVanCatalogDrawCell
          OnFixedCellClick = sgUsersFixedCellClick
        end
        object btnPurposeStationsAdd: TButton
          Left = 16
          Top = 282
          Width = 96
          Height = 32
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnPurposeStationsChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnPurposeStationsDelete: TButton
          Left = 240
          Top = 282
          Width = 96
          Height = 32
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
      object tsInvoiceSuppliers: TTabSheet
        Caption = #1043#1088#1091#1079#1086#1086#1090#1087#1088#1072#1074#1080#1090#1077#1083#1100
        ImageIndex = 6
        object sgInvoiceSuppliers: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          ColCount = 2
          DefaultDrawing = False
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goFixedColClick]
          TabOrder = 0
          OnDblClick = sgUsersDblClick
          OnDrawCell = sgVanCatalogDrawCell
          OnFixedCellClick = sgUsersFixedCellClick
        end
        object btnInvoiceSuppliersAdd: TButton
          Left = 16
          Top = 282
          Width = 96
          Height = 32
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnInvoiceSuppliersChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnInvoiceSuppliersDelete: TButton
          Left = 240
          Top = 282
          Width = 96
          Height = 32
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
      object tsInvoiceRecipients: TTabSheet
        Caption = #1043#1088#1091#1079#1086#1087#1086#1083#1091#1095#1072#1090#1077#1083#1100
        ImageIndex = 7
        object sgInvoiceRecipients: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          ColCount = 2
          DefaultDrawing = False
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goFixedColClick]
          TabOrder = 0
          OnDblClick = sgUsersDblClick
          OnDrawCell = sgVanCatalogDrawCell
          OnFixedCellClick = sgUsersFixedCellClick
        end
        object btnInvoiceRecipientsAdd: TButton
          Left = 16
          Top = 282
          Width = 96
          Height = 32
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnInvoiceRecipientsChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnInvoiceRecipientsDelete: TButton
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
    Top = 408
    Width = 608
    Height = 48
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      608
      48)
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

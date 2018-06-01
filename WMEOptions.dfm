object frmOptions: TfrmOptions
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 500
  ClientWidth = 638
  Color = clBtnFace
  Constraints.MinHeight = 500
  Constraints.MinWidth = 640
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
    Width = 606
    Height = 420
    Align = alClient
    BevelOuter = bvLowered
    TabOrder = 0
    object PageControl: TPageControl
      Left = 1
      Top = 1
      Width = 604
      Height = 418
      ActivePage = tsLocalDatabase
      Align = alClient
      MultiLine = True
      TabOrder = 0
      StyleElements = [seFont, seClient]
      object tsLocalDatabase: TTabSheet
        Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
        DesignSize = (
          596
          330)
        object lblLocalConnection: TLabel
          Left = 16
          Top = 16
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
        object bvlLocalDB: TBevel
          Left = 16
          Top = 176
          Width = 564
          Height = 4
          Anchors = [akLeft, akTop, akRight]
          Shape = bsTopLine
          ExplicitWidth = 566
        end
        object eLocalDBUser: TLabeledEdit
          Left = 16
          Top = 130
          Width = 120
          Height = 29
          EditLabel.Width = 44
          EditLabel.Height = 21
          EditLabel.Caption = #1051#1086#1075#1080#1085
          TabOrder = 2
        end
        object eLocalDBPass: TLabeledEdit
          Left = 152
          Top = 130
          Width = 152
          Height = 29
          EditLabel.Width = 53
          EditLabel.Height = 21
          EditLabel.Caption = #1055#1072#1088#1086#1083#1100
          PasswordChar = '#'
          TabOrder = 3
        end
        object btnLocalDBConnectionCheck: TButton
          Left = 320
          Top = 127
          Width = 120
          Height = 32
          Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100
          TabOrder = 5
          OnClick = btnLocalDBConnectionCheckClick
        end
        object eLocalDBHost: TLabeledEdit
          Left = 16
          Top = 74
          Width = 120
          Height = 29
          EditLabel.Width = 32
          EditLabel.Height = 21
          EditLabel.Caption = #1061#1086#1089#1090
          TabOrder = 0
        end
        object eLocalDBPort: TLabeledEdit
          Left = 152
          Top = 74
          Width = 64
          Height = 29
          EditLabel.Width = 36
          EditLabel.Height = 21
          EditLabel.Caption = #1055#1086#1088#1090
          NumbersOnly = True
          TabOrder = 1
        end
        object btnLocalDBConnectionDefault: TButton
          Left = 320
          Top = 71
          Width = 120
          Height = 32
          Caption = #1055#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
          TabOrder = 4
          OnClick = btnLocalDBConnectionDefaultClick
        end
        object btnLocalDBCreate: TButton
          Left = 16
          Top = 194
          Width = 168
          Height = 32
          Caption = #1057#1086#1079#1076#1072#1090#1100' '#1073#1072#1079#1091' '#1076#1072#1085#1085#1099#1093
          TabOrder = 6
          OnClick = btnLocalDBCreateClick
        end
        object btnLocalDBDelete: TButton
          Left = 196
          Top = 194
          Width = 168
          Height = 32
          Caption = #1059#1076#1072#1083#1080#1090#1100' '#1073#1072#1079#1091' '#1076#1072#1085#1085#1099#1093
          TabOrder = 7
          OnClick = btnLocalDBDeleteClick
        end
      end
      object tsServerDatabase: TTabSheet
        Caption = #1057#1077#1088#1074#1077#1088
        ImageIndex = 8
        object eServerDBHost: TLabeledEdit
          Left = 16
          Top = 74
          Width = 120
          Height = 29
          EditLabel.Width = 32
          EditLabel.Height = 21
          EditLabel.Caption = #1061#1086#1089#1090
          TabOrder = 1
        end
        object eServerDBPort: TLabeledEdit
          Left = 152
          Top = 74
          Width = 64
          Height = 29
          EditLabel.Width = 36
          EditLabel.Height = 21
          EditLabel.Caption = #1055#1086#1088#1090
          NumbersOnly = True
          TabOrder = 2
        end
        object eServerDBUser: TLabeledEdit
          Left = 16
          Top = 130
          Width = 120
          Height = 29
          EditLabel.Width = 44
          EditLabel.Height = 21
          EditLabel.Caption = #1051#1086#1075#1080#1085
          TabOrder = 3
        end
        object eServerDBPass: TLabeledEdit
          Left = 152
          Top = 130
          Width = 152
          Height = 29
          EditLabel.Width = 53
          EditLabel.Height = 21
          EditLabel.Caption = #1055#1072#1088#1086#1083#1100
          PasswordChar = '#'
          TabOrder = 4
        end
        object btnServerDBConnectionCheck: TButton
          Left = 320
          Top = 127
          Width = 120
          Height = 32
          Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100
          TabOrder = 5
          OnClick = btnServerDBConnectionCheckClick
        end
        object cboxServerDBConnection: TCheckBox
          Left = 16
          Top = 16
          Width = 400
          Height = 21
          Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1073#1072#1079#1091' '#1076#1072#1085#1085#1099#1093' '#1089#1077#1088#1074#1077#1088#1072
          TabOrder = 0
        end
      end
      object tsUsers: TTabSheet
        Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1080
        ImageIndex = 1
        DesignSize = (
          596
          330)
        object sgUsers: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 256
          Anchors = [akLeft, akTop, akRight, akBottom]
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
          Top = 288
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnUsersChange: TButton
          Left = 128
          Top = 288
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnUsersDelete: TButton
          Left = 240
          Top = 288
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
      object tsVanTypes: TTabSheet
        Caption = #1056#1086#1076' '#1074#1072#1075#1086#1085#1072
        ImageIndex = 2
        DesignSize = (
          596
          330)
        object sgVanTypes: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          Anchors = [akLeft, akTop, akRight, akBottom]
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
          Anchors = [akLeft, akBottom]
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnVanTypesChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnVanTypesDelete: TButton
          Left = 240
          Top = 282
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
      object tsCargoTypes: TTabSheet
        Caption = #1056#1086#1076' '#1075#1088#1091#1079#1072
        ImageIndex = 3
        DesignSize = (
          596
          330)
        object sgCargoTypes: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          Anchors = [akLeft, akTop, akRight, akBottom]
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
          Anchors = [akLeft, akBottom]
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnCargoTypesChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnCargoTypesDelete: TButton
          Left = 240
          Top = 282
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
      object tsDepartStations: TTabSheet
        Caption = #1057#1090#1072#1085#1094#1080#1103' '#1086#1090#1087#1088#1072#1074#1083#1077#1085#1080#1103
        ImageIndex = 4
        DesignSize = (
          596
          330)
        object sgDepartStations: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          Anchors = [akLeft, akTop, akRight, akBottom]
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
          Anchors = [akLeft, akBottom]
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnDepartStationsChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnDepartStationsDelete: TButton
          Left = 240
          Top = 282
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
      object tsPurposeStations: TTabSheet
        Caption = #1057#1090#1072#1085#1094#1080#1103' '#1085#1072#1079#1085#1072#1095#1077#1085#1080#1103
        ImageIndex = 5
        DesignSize = (
          596
          330)
        object sgPurposeStations: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          Anchors = [akLeft, akTop, akRight, akBottom]
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
          Anchors = [akLeft, akBottom]
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnPurposeStationsChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnPurposeStationsDelete: TButton
          Left = 240
          Top = 282
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
      object tsInvoiceSuppliers: TTabSheet
        Caption = #1043#1088#1091#1079#1086#1086#1090#1087#1088#1072#1074#1080#1090#1077#1083#1100
        ImageIndex = 6
        DesignSize = (
          596
          330)
        object sgInvoiceSuppliers: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          Anchors = [akLeft, akTop, akRight, akBottom]
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
          Anchors = [akLeft, akBottom]
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnInvoiceSuppliersChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnInvoiceSuppliersDelete: TButton
          Left = 240
          Top = 282
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
      object tsInvoiceRecipients: TTabSheet
        Caption = #1043#1088#1091#1079#1086#1087#1086#1083#1091#1095#1072#1090#1077#1083#1100
        ImageIndex = 7
        DesignSize = (
          596
          330)
        object sgInvoiceRecipients: TStringGrid
          Left = 16
          Top = 16
          Width = 566
          Height = 250
          Anchors = [akLeft, akTop, akRight, akBottom]
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
          Anchors = [akLeft, akBottom]
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = btnUsersAddClick
        end
        object btnInvoiceRecipientsChange: TButton
          Left = 128
          Top = 282
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
          OnClick = btnUsersChangeClick
        end
        object btnInvoiceRecipientsDelete: TButton
          Left = 240
          Top = 282
          Width = 96
          Height = 32
          Anchors = [akLeft, akBottom]
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 3
          OnClick = btnUsersDeleteClick
        end
      end
    end
  end
  object PanelButtons: TPanel
    Left = 16
    Top = 436
    Width = 606
    Height = 48
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      606
      48)
    object btnOk: TButton
      Left = 398
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
      Left = 510
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

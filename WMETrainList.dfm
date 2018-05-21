object frmTrainList: TfrmTrainList
  Left = 0
  Top = 0
  Caption = #1057#1087#1080#1089#1086#1082' '#1074#1079#1074#1077#1096#1080#1074#1072#1085#1080#1081
  ClientHeight = 419
  ClientWidth = 683
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Segoe UI'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 21
  object PanelMain: TPanel
    Left = 0
    Top = 0
    Width = 683
    Height = 395
    Align = alClient
    BevelOuter = bvNone
    Padding.Left = 8
    Padding.Top = 8
    Padding.Right = 8
    Padding.Bottom = 8
    TabOrder = 0
    ExplicitHeight = 399
    object Splitter: TSplitter
      Left = 8
      Top = 205
      Width = 667
      Height = 8
      Cursor = crSizeNS
      Align = alTop
      MinSize = 120
      ResizeStyle = rsUpdate
      ExplicitTop = 210
    end
    object sgTrains: TStringGrid
      Left = 8
      Top = 45
      Width = 667
      Height = 160
      Align = alTop
      ColCount = 2
      Constraints.MinHeight = 100
      DefaultDrawing = False
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goFixedColClick]
      TabOrder = 1
      OnDblClick = sgTrainsDblClick
      OnDrawCell = sgTrainsDrawCell
      OnFixedCellClick = sgTrainsFixedCellClick
      OnSelectCell = sgTrainsSelectCell
    end
    object PanelTop: TPanel
      Left = 8
      Top = 37
      Width = 667
      Height = 8
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
    end
    object sgVans: TStringGrid
      Left = 8
      Top = 213
      Width = 667
      Height = 174
      Align = alClient
      ColCount = 2
      Constraints.MinHeight = 100
      DefaultDrawing = False
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goFixedColClick]
      TabOrder = 2
      OnDblClick = sgTrainsDblClick
      OnDrawCell = sgVansDrawCell
      OnFixedCellClick = sgTrainsFixedCellClick
      ExplicitHeight = 178
    end
    object ToolBar: TToolBar
      Left = 8
      Top = 8
      Width = 667
      Height = 29
      ButtonHeight = 29
      ButtonWidth = 78
      Caption = 'ToolBar'
      ShowCaptions = True
      TabOrder = 3
      object tbtnPrevPage: TToolButton
        Left = 0
        Top = 0
        Caption = #1053#1072#1079#1072#1076
        Enabled = False
        ImageIndex = 1
        OnClick = tbtnPrevPageClick
      end
      object tbtnNextPage: TToolButton
        Left = 78
        Top = 0
        Caption = #1042#1087#1077#1088#1105#1076
        ImageIndex = 2
        OnClick = tbtnNextPageClick
      end
      object tbtnSeparator01: TToolButton
        Left = 156
        Top = 0
        Width = 4
        Caption = 'tbtnSeparator01'
        ImageIndex = 1
        Style = tbsSeparator
      end
      object tbtnOpen: TToolButton
        Left = 160
        Top = 0
        Caption = #1048#1079#1084#1077#1085#1080#1090#1100
        ImageIndex = 2
        OnClick = tbtnOpenClick
      end
      object tbtnSeparator02: TToolButton
        Left = 238
        Top = 0
        Width = 4
        ImageIndex = 1
        Style = tbsSeparator
      end
      object tbtnClose: TToolButton
        Left = 242
        Top = 0
        Caption = #1047#1072#1082#1088#1099#1090#1100
        ImageIndex = 0
        OnClick = tbtnCloseClick
      end
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 395
    Width = 683
    Height = 24
    Panels = <
      item
        Width = 50
      end>
    ParentFont = True
    UseSystemFont = False
    ExplicitTop = 399
  end
end

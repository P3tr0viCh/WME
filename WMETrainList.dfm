object frmTrainList: TfrmTrainList
  Left = 0
  Top = 0
  Caption = #1057#1087#1080#1089#1086#1082' '#1074#1079#1074#1077#1096#1080#1074#1072#1085#1080#1081
  ClientHeight = 381
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
    Height = 361
    Align = alClient
    BevelOuter = bvNone
    Padding.Left = 8
    Padding.Top = 8
    Padding.Right = 8
    Padding.Bottom = 8
    TabOrder = 0
    object Splitter: TSplitter
      Left = 8
      Top = 205
      Width = 667
      Height = 8
      Cursor = crSizeNS
      Align = alTop
      MinSize = 120
      ResizeStyle = rsUpdate
      ExplicitTop = 290
    end
    object ToolBar: TToolBar
      Left = 8
      Top = 8
      Width = 667
      Height = 29
      AutoSize = True
      ButtonHeight = 29
      ButtonWidth = 69
      Caption = 'ToolBar'
      ShowCaptions = True
      TabOrder = 0
      object tbtnOpen: TToolButton
        Left = 0
        Top = 0
        Caption = #1054#1090#1082#1088#1099#1090#1100
        ImageIndex = 2
        OnClick = tbtnOpenClick
      end
      object tbtnSeparator02: TToolButton
        Left = 69
        Top = 0
        Width = 4
        ImageIndex = 1
        Style = tbsSeparator
      end
      object tbtnClose: TToolButton
        Left = 73
        Top = 0
        Caption = #1047#1072#1082#1088#1099#1090#1100
        ImageIndex = 0
        OnClick = tbtnCloseClick
      end
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
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goFixedColClick]
      TabOrder = 2
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
      TabOrder = 1
    end
    object sgVans: TStringGrid
      Left = 8
      Top = 213
      Width = 667
      Height = 140
      Align = alClient
      ColCount = 2
      Constraints.MinHeight = 100
      DefaultDrawing = False
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goFixedColClick]
      TabOrder = 3
      OnDblClick = sgTrainsDblClick
      OnDrawCell = sgVansDrawCell
      OnFixedCellClick = sgTrainsFixedCellClick
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 361
    Width = 683
    Height = 20
    Panels = <>
  end
end

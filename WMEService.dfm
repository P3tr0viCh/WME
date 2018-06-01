object frmService: TfrmService
  Left = 0
  Top = 0
  Caption = #1057#1077#1088#1074#1080#1089
  ClientHeight = 354
  ClientWidth = 656
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
    Width = 656
    Height = 330
    Align = alClient
    BevelOuter = bvNone
    Padding.Left = 8
    Padding.Top = 8
    Padding.Right = 8
    Padding.Bottom = 8
    TabOrder = 0
    ExplicitWidth = 480
    ExplicitHeight = 254
    object ToolBar: TToolBar
      Left = 8
      Top = 8
      Width = 640
      Height = 29
      AutoSize = True
      ButtonHeight = 29
      ButtonWidth = 92
      Caption = 'ToolBar'
      ShowCaptions = True
      TabOrder = 0
      ExplicitWidth = 464
      ExplicitHeight = 62
      object tbtnLocal: TToolButton
        Left = 0
        Top = 0
        Caption = #1042#1077#1089#1099
        Grouped = True
        ImageIndex = 1
        Style = tbsCheck
        OnClick = tbtnLocalClick
      end
      object tbtnServer: TToolButton
        Left = 92
        Top = 0
        Caption = #1057#1077#1088#1074#1077#1088
        Grouped = True
        ImageIndex = 1
        Style = tbsCheck
        OnClick = tbtnServerClick
      end
      object tbtnSeparator01: TToolButton
        Left = 184
        Top = 0
        Width = 4
        Caption = 'tbtnSeparator01'
        ImageIndex = 1
        Style = tbsSeparator
      end
      object tbtnSearch: TToolButton
        Left = 188
        Top = 0
        Caption = #1055#1086#1080#1089#1082
        ImageIndex = 1
        OnClick = tbtnSearchClick
      end
      object tbtnSave: TToolButton
        Left = 280
        Top = 0
        Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
        ImageIndex = 1
      end
      object tbtnSeparator03: TToolButton
        Left = 372
        Top = 0
        Width = 4
        ImageIndex = 1
        Style = tbsSeparator
      end
      object tbtnClose: TToolButton
        Left = 376
        Top = 0
        Caption = #1047#1072#1082#1088#1099#1090#1100
        ImageIndex = 0
        OnClick = tbtnCloseClick
      end
    end
    object sgVansLocal: TStringGrid
      Left = 8
      Top = 45
      Width = 640
      Height = 277
      Align = alClient
      ColCount = 2
      DefaultDrawing = False
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goTabs, goFixedColClick]
      TabOrder = 2
      OnDrawCell = sgVansLocalDrawCell
      OnFixedCellClick = sgVansServerFixedCellClick
      ExplicitWidth = 464
      ExplicitHeight = 201
    end
    object PanelTop: TPanel
      Left = 8
      Top = 37
      Width = 640
      Height = 8
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      ExplicitWidth = 464
    end
    object sgVansServer: TStringGrid
      Left = 8
      Top = 45
      Width = 640
      Height = 277
      Align = alClient
      ColCount = 2
      DefaultDrawing = False
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goTabs, goFixedColClick]
      TabOrder = 3
      OnDrawCell = sgVansServerDrawCell
      OnFixedCellClick = sgVansServerFixedCellClick
      ExplicitLeft = 16
      ExplicitTop = 53
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 330
    Width = 656
    Height = 24
    Panels = <>
    ParentFont = True
    UseSystemFont = False
    ExplicitTop = 230
    ExplicitWidth = 609
  end
end

object frmService: TfrmService
  Left = 0
  Top = 0
  Caption = #1057#1077#1088#1074#1080#1089
  ClientHeight = 254
  ClientWidth = 480
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
    Width = 480
    Height = 254
    Align = alClient
    BevelOuter = bvNone
    Padding.Left = 8
    Padding.Top = 8
    Padding.Right = 8
    Padding.Bottom = 8
    TabOrder = 0
    ExplicitLeft = -129
    ExplicitTop = -84
    ExplicitWidth = 609
    ExplicitHeight = 338
    object ToolBar: TToolBar
      Left = 8
      Top = 8
      Width = 464
      Height = 29
      AutoSize = True
      ButtonHeight = 29
      ButtonWidth = 92
      Caption = 'ToolBar'
      ShowCaptions = True
      TabOrder = 0
      object tbtnSave: TToolButton
        Left = 0
        Top = 0
        Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
        ImageIndex = 1
      end
      object tbtnSeparator03: TToolButton
        Left = 92
        Top = 0
        Width = 4
        ImageIndex = 1
        Style = tbsSeparator
      end
      object tbtnClose: TToolButton
        Left = 96
        Top = 0
        Caption = #1047#1072#1082#1088#1099#1090#1100
        ImageIndex = 0
        OnClick = tbtnCloseClick
      end
    end
    object sgVans: TStringGrid
      Left = 8
      Top = 45
      Width = 464
      Height = 201
      Align = alClient
      ColCount = 2
      DefaultDrawing = False
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goTabs]
      TabOrder = 2
      OnDrawCell = sgVansDrawCell
    end
    object PanelTop: TPanel
      Left = 8
      Top = 37
      Width = 464
      Height = 8
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
    end
  end
end

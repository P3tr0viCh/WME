object frmTrain: TfrmTrain
  Left = 0
  Top = 0
  Caption = 'C'#1086#1089#1090#1072#1074
  ClientHeight = 362
  ClientWidth = 609
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
  object StatusBar: TStatusBar
    Left = 0
    Top = 342
    Width = 609
    Height = 20
    Panels = <>
  end
  object PanelMain: TPanel
    Left = 0
    Top = 0
    Width = 609
    Height = 342
    Align = alClient
    BevelOuter = bvNone
    Padding.Left = 8
    Padding.Top = 8
    Padding.Right = 8
    Padding.Bottom = 8
    TabOrder = 1
    object ToolBar: TToolBar
      Left = 8
      Top = 8
      Width = 593
      Height = 29
      AutoSize = True
      ButtonHeight = 29
      ButtonWidth = 76
      Caption = 'ToolBar'
      ShowCaptions = True
      TabOrder = 0
      object tbtnAdd: TToolButton
        Left = 0
        Top = 0
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        ImageIndex = 2
        OnClick = tbtnAddClick
      end
      object tbtnDelete: TToolButton
        Left = 76
        Top = 0
        Caption = #1059#1076#1072#1083#1080#1090#1100
        ImageIndex = 1
        OnClick = tbtnDeleteClick
      end
      object ToolButton3: TToolButton
        Left = 152
        Top = 0
        Width = 4
        Caption = 'ToolButton3'
        ImageIndex = 1
        Style = tbsSeparator
      end
      object tbtnClose: TToolButton
        Left = 156
        Top = 0
        Caption = #1047#1072#1082#1088#1099#1090#1100
        ImageIndex = 0
        OnClick = tbtnCloseClick
      end
    end
    object sgVans: TStringGrid
      Left = 8
      Top = 45
      Width = 593
      Height = 201
      Align = alClient
      ColCount = 2
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
      TabOrder = 1
      OnSelectCell = sgVansSelectCell
      OnSetEditText = sgVansSetEditText
    end
    object PanelTop: TPanel
      Left = 8
      Top = 37
      Width = 593
      Height = 8
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 2
    end
    object sgTrain: TStringGrid
      Left = 8
      Top = 254
      Width = 593
      Height = 80
      Align = alBottom
      ColCount = 2
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
      ScrollBars = ssHorizontal
      TabOrder = 3
    end
    object PanelBottom: TPanel
      Left = 8
      Top = 246
      Width = 593
      Height = 8
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 4
    end
  end
end

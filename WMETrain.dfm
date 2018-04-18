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
  OnCloseQuery = FormCloseQuery
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
      ButtonWidth = 83
      Caption = 'ToolBar'
      ShowCaptions = True
      TabOrder = 0
      OnMouseActivate = ToolBarMouseActivate
      object tbtnAdd: TToolButton
        Left = 0
        Top = 0
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        ImageIndex = 2
        OnClick = tbtnAddClick
      end
      object tbtnDelete: TToolButton
        Left = 83
        Top = 0
        Caption = #1059#1076#1072#1083#1080#1090#1100
        ImageIndex = 1
        OnClick = tbtnDeleteClick
      end
      object tbtnSeparator01: TToolButton
        Left = 166
        Top = 0
        Width = 4
        ImageIndex = 1
        Style = tbsSeparator
      end
      object tbtnSave: TToolButton
        Left = 170
        Top = 0
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        ImageIndex = 1
        OnClick = tbtnSaveClick
      end
      object tbtnSeparator02: TToolButton
        Left = 253
        Top = 0
        Width = 4
        ImageIndex = 1
        Style = tbsSeparator
      end
      object tbtnClose: TToolButton
        Left = 257
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
      DefaultDrawing = False
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goTabs]
      TabOrder = 2
      OnDblClick = sgVansDblClick
      OnDrawCell = sgVansDrawCell
      OnExit = sgVansExit
      OnGetEditMask = sgVansGetEditMask
      OnGetEditText = sgVansGetEditText
      OnKeyDown = sgVansKeyDown
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
      TabOrder = 1
    end
    object sgTrain: TStringGrid
      Left = 8
      Top = 254
      Width = 593
      Height = 80
      Align = alBottom
      ColCount = 2
      DefaultDrawing = False
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
      ScrollBars = ssHorizontal
      TabOrder = 4
      OnDrawCell = sgTrainDrawCell
    end
    object PanelBottom: TPanel
      Left = 8
      Top = 246
      Width = 593
      Height = 8
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 3
    end
    object ComboBox: TComboBox
      Left = 296
      Top = 136
      Width = 145
      Height = 29
      TabOrder = 5
      Text = 'ComboBox'
      Visible = False
      OnEnter = ComboBoxEnter
      OnExit = ComboBoxExit
      OnKeyDown = ComboBoxKeyDown
      OnKeyPress = ComboBoxKeyPress
      Items.Strings = (
        'VanType 1'
        'VanType 2'
        'VanType 3')
    end
  end
end

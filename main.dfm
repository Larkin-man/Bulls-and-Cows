object Form1: TForm1
  Left = 575
  Top = 156
  Width = 372
  Height = 375
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 20
  object Label1: TLabel
    Left = 8
    Top = 192
    Width = 104
    Height = 20
    Caption = #1042#1089#1077#1075#1086' : '#1041#1099#1082#1086#1074
  end
  object Grid: TStringGrid
    Left = 188
    Top = 0
    Width = 176
    Height = 337
    Align = alRight
    ColCount = 7
    DefaultColWidth = 18
    DefaultRowHeight = 18
    FixedCols = 0
    RowCount = 1440
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    ParentFont = False
    TabOrder = 0
  end
  object MaskEdit1: TMaskEdit
    Left = 8
    Top = 40
    Width = 49
    Height = 28
    EditMask = '0000'
    MaxLength = 4
    TabOrder = 1
    Text = '1234'
  end
  object MaskEdit2: TMaskEdit
    Left = 64
    Top = 40
    Width = 33
    Height = 28
    EditMask = '0:0'
    MaxLength = 3
    TabOrder = 2
    Text = '3:0'
  end
  object Search: TBitBtn
    Left = 104
    Top = 40
    Width = 75
    Height = 25
    Caption = 'Search'
    TabOrder = 3
    OnClick = SearchClick
  end
  object Edit1: TEdit
    Left = 8
    Top = 120
    Width = 121
    Height = 28
    TabOrder = 4
    Text = 'Edit1'
  end
  object Button1: TButton
    Left = 8
    Top = 160
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 5
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 24
    Top = 216
    Width = 75
    Height = 25
    Caption = 'Button2'
    TabOrder = 6
    OnClick = Button2Click
  end
  object SearchNext: TButton
    Left = 8
    Top = 72
    Width = 105
    Height = 25
    Caption = 'SearchNext'
    TabOrder = 7
    OnClick = SearchNextClick
  end
  object New: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 25
    Caption = 'New'
    TabOrder = 8
    OnClick = NewClick
  end
end

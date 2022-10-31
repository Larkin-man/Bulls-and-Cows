object MainForm: TMainForm
  Left = 327
  Top = 136
  Caption = #1041#1099#1082#1080' '#1080' '#1082#1086#1088#1086#1074#1099
  ClientHeight = 371
  ClientWidth = 464
  Color = clBtnFace
  Constraints.MinHeight = 409
  Constraints.MinWidth = 472
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Book Antiqua'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    464
    371)
  PixelsPerInch = 96
  TextHeight = 20
  object Label1: TLabel
    Left = 8
    Top = 256
    Width = 98
    Height = 20
    Anchors = [akLeft, akBottom]
    Caption = #1042#1072#1096' '#1074#1072#1088#1080#1072#1085#1090
  end
  object Label2: TLabel
    Left = 232
    Top = 256
    Width = 26
    Height = 20
    Anchors = [akLeft, akBottom]
    Caption = #1045#1075#1086
  end
  object Label3: TLabel
    Left = 152
    Top = 0
    Width = 94
    Height = 20
    Caption = #1053#1072#1095#1072#1090#1100' '#1080#1075#1088#1091
  end
  object Bevel1: TBevel
    Left = 144
    Top = 8
    Width = 105
    Height = 17
    Shape = bsBottomLine
  end
  object LLoses: TLabel
    Left = 165
    Top = 240
    Width = 57
    Height = 20
    Caption = 'Loses: 0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -16
    Font.Name = 'Book Antiqua'
    Font.Style = []
    ParentFont = False
  end
  object LWins: TLabel
    Left = 169
    Top = 216
    Width = 53
    Height = 20
    Caption = 'Wins: 0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -16
    Font.Name = 'Book Antiqua'
    Font.Style = []
    ParentFont = False
  end
  object LStage: TLabel
    Left = 160
    Top = 192
    Width = 62
    Height = 20
    Caption = #1061#1086#1076#1086#1074': 0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -16
    Font.Name = 'Book Antiqua'
    Font.Style = []
    ParentFont = False
  end
  object You: TMaskEdit
    Left = 8
    Top = 280
    Width = 57
    Height = 31
    Anchors = [akLeft, akBottom]
    EditMask = '0000'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Century'
    Font.Style = []
    MaxLength = 4
    ParentFont = False
    TabOrder = 0
    Text = '1234'
  end
  object His: TMaskEdit
    Left = 232
    Top = 280
    Width = 56
    Height = 31
    Anchors = [akLeft, akBottom]
    EditMask = '0000'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Century'
    Font.Style = []
    MaxLength = 4
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
    Text = '5678'
  end
  object Edit1: TEdit
    Left = 8
    Top = 344
    Width = 449
    Height = 28
    Anchors = [akLeft, akBottom]
    Color = cl3DLight
    TabOrder = 2
    Text = 'Edit1'
  end
  object MaskBC: TMaskEdit
    Left = 304
    Top = 280
    Width = 41
    Height = 31
    Anchors = [akLeft, akBottom]
    EditMask = '0:0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Century'
    Font.Style = []
    MaxLength = 3
    ParentFont = False
    TabOrder = 3
    Text = '3:1'
  end
  object Go: TButton
    Left = 96
    Top = 283
    Width = 113
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1057#1076#1077#1083#1072#1090#1100' '#1093#1086#1076
    TabOrder = 4
    OnClick = GoClick
  end
  object StartRazgBtn: TButton
    Left = 152
    Top = 32
    Width = 89
    Height = 25
    Caption = #1056#1072#1079#1075#1072#1076#1072#1090#1100
    TabOrder = 5
    OnClick = StartRazgBtnClick
  end
  object HisTable: TValueListEditor
    Left = 256
    Top = 23
    Width = 137
    Height = 234
    Anchors = [akLeft, akTop, akBottom]
    DefaultRowHeight = 22
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goAlwaysShowEditor, goThumbTracking]
    TabOrder = 7
    TitleCaptions.Strings = (
      #1063#1080#1089#1083#1086
      #1054#1090#1074#1077#1090)
    ColWidths = (
      74
      57)
  end
  object YourTable: TValueListEditor
    Left = 0
    Top = 23
    Width = 137
    Height = 234
    Anchors = [akLeft, akTop, akBottom]
    DefaultRowHeight = 22
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goAlwaysShowEditor, goThumbTracking]
    TabOrder = 6
    TitleCaptions.Strings = (
      #1063#1080#1089#1083#1086
      #1054#1090#1074#1077#1090)
    ColWidths = (
      76
      55)
  end
  object StaticText1: TStaticText
    Left = 0
    Top = 0
    Width = 137
    Height = 24
    AutoSize = False
    BevelInner = bvLowered
    BevelKind = bkTile
    BevelOuter = bvNone
    BorderStyle = sbsSunken
    Caption = #1042#1072#1096#1080' '#1074#1072#1088#1080#1072#1085#1090#1099
    TabOrder = 8
  end
  object StaticText2: TStaticText
    Left = 256
    Top = 0
    Width = 137
    Height = 24
    AutoSize = False
    BevelInner = bvLowered
    BevelKind = bkTile
    BevelOuter = bvNone
    BorderStyle = sbsSunken
    Caption = #1045#1075#1086' '#1074#1072#1088#1080#1072#1085#1090#1099
    TabOrder = 9
  end
  object CalcCB: TButton
    Left = 352
    Top = 296
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = 'CalcCB'
    TabOrder = 10
    OnClick = CalcCBClick
  end
  object SetReal: TButton
    Left = 352
    Top = 320
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = 'SetReal'
    TabOrder = 11
    OnClick = SetRealClick
  end
  object StartZagBtn: TButton
    Left = 152
    Top = 128
    Width = 89
    Height = 25
    Caption = #1047#1072#1075#1072#1076#1072#1090#1100
    TabOrder = 12
    OnClick = StartZagBtnClick
  end
  object StartpvpBTN: TButton
    Left = 152
    Top = 160
    Width = 89
    Height = 25
    Caption = #1055#1074#1050
    TabOrder = 13
    OnClick = StartpvpBTNClick
  end
  object Secret: TMaskEdit
    Left = 352
    Top = 264
    Width = 57
    Height = 31
    Hint = #1042#1072#1096#1077' '#1079#1072#1075#1072#1076#1072#1085#1085#1086#1077' '#1095#1080#1089#1083#1086
    Anchors = [akLeft, akBottom]
    EditMask = '0000'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBackground
    Font.Height = -19
    Font.Name = 'Century'
    Font.Style = []
    MaxLength = 4
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 14
    Text = '1234'
  end
  object F1: TStaticText
    Left = 9
    Top = 316
    Width = 21
    Height = 24
    Anchors = [akLeft, akBottom]
    AutoSize = False
    BorderStyle = sbsSingle
    Caption = ' 1'
    Color = clCaptionText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 15
    OnClick = FigureLClick
    OnContextPopup = F1ContextPopup
  end
  object F2: TStaticText
    Left = 33
    Top = 316
    Width = 21
    Height = 24
    Anchors = [akLeft, akBottom]
    AutoSize = False
    BorderStyle = sbsSingle
    Caption = ' 2'
    Color = clCaptionText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 16
    OnClick = FigureLClick
    OnContextPopup = F1ContextPopup
  end
  object F3: TStaticText
    Left = 57
    Top = 316
    Width = 21
    Height = 24
    Anchors = [akLeft, akBottom]
    AutoSize = False
    BorderStyle = sbsSingle
    Caption = ' 3'
    Color = clCaptionText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 17
    OnClick = FigureLClick
    OnContextPopup = F1ContextPopup
  end
  object F4: TStaticText
    Left = 81
    Top = 316
    Width = 21
    Height = 24
    Anchors = [akLeft, akBottom]
    AutoSize = False
    BorderStyle = sbsSingle
    Caption = ' 4'
    Color = clCaptionText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 18
    OnClick = FigureLClick
    OnContextPopup = F1ContextPopup
  end
  object F5: TStaticText
    Left = 105
    Top = 316
    Width = 21
    Height = 24
    Anchors = [akLeft, akBottom]
    AutoSize = False
    BorderStyle = sbsSingle
    Caption = ' 5'
    Color = clCaptionText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 19
    OnClick = FigureLClick
    OnContextPopup = F1ContextPopup
  end
  object F6: TStaticText
    Left = 129
    Top = 316
    Width = 21
    Height = 24
    Anchors = [akLeft, akBottom]
    AutoSize = False
    BorderStyle = sbsSingle
    Caption = ' 6'
    Color = clCaptionText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 20
    OnClick = FigureLClick
    OnContextPopup = F1ContextPopup
  end
  object F7: TStaticText
    Left = 153
    Top = 316
    Width = 21
    Height = 24
    Anchors = [akLeft, akBottom]
    AutoSize = False
    BorderStyle = sbsSingle
    Caption = ' 7'
    Color = clCaptionText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 21
    OnClick = FigureLClick
    OnContextPopup = F1ContextPopup
  end
  object F8: TStaticText
    Left = 177
    Top = 316
    Width = 21
    Height = 24
    Anchors = [akLeft, akBottom]
    AutoSize = False
    BorderStyle = sbsSingle
    Caption = ' 8'
    Color = clCaptionText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 22
    OnClick = FigureLClick
    OnContextPopup = F1ContextPopup
  end
  object F9: TStaticText
    Left = 201
    Top = 316
    Width = 21
    Height = 24
    Anchors = [akLeft, akBottom]
    AutoSize = False
    BorderStyle = sbsSingle
    Caption = ' 9'
    Color = clCaptionText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 23
    OnClick = FigureLClick
    OnContextPopup = F1ContextPopup
  end
  object F0: TStaticText
    Left = 225
    Top = 316
    Width = 21
    Height = 24
    Anchors = [akLeft, akBottom]
    AutoSize = False
    BorderStyle = sbsSingle
    Caption = ' 0'
    Color = clCaptionText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 24
    OnClick = FigureLClick
    OnContextPopup = F1ContextPopup
  end
  object Hired: TButton
    Left = 256
    Top = 316
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1057#1076#1072#1102#1089#1100'!'
    TabOrder = 25
    OnClick = HiredClick
  end
  object Style: TRadioGroup
    Left = 144
    Top = 56
    Width = 105
    Height = 65
    Caption = #1057#1083#1086#1078#1085#1086#1089#1090#1100
    ItemIndex = 0
    Items.Strings = (
      #1051#1077#1075#1082#1080#1081
      #1058#1088#1091#1076#1085#1080#1081)
    TabOrder = 26
  end
  object Button1: TButton
    Left = 400
    Top = 24
    Width = 59
    Height = 25
    Caption = 'Button1'
    TabOrder = 27
    OnClick = Button1Click
  end
end

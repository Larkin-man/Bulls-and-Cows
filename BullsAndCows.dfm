object Form1: TForm1
  Left = 285
  Top = 146
  Width = 696
  Height = 375
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 20
  object StaticText1: TStaticText
    Left = 88
    Top = 56
    Width = 19
    Height = 24
    BorderStyle = sbsSingle
    Caption = ' '#1040
    Color = clWhite
    ParentColor = False
    TabOrder = 0
    OnClick = StaticText1Click
    OnContextPopup = StaticText1ContextPopup
  end
  object Memo1: TMemo
    Left = 503
    Top = 0
    Width = 185
    Height = 341
    Align = alRight
    Lines.Strings = (
      'Memo1')
    TabOrder = 1
  end
  object StaticText2: TStaticText
    Left = 112
    Top = 56
    Width = 19
    Height = 24
    BorderStyle = sbsSingle
    Caption = ' '#1041
    Color = clWhite
    ParentColor = False
    TabOrder = 2
    OnClick = StaticText1Click
    OnContextPopup = StaticText1ContextPopup
  end
end

//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>    
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <ExtCtrls.hpp>
#include "TheBullsAndCow.cpp"
//---------------------------------------------------------------------------
enum TStatus { None = 0, Yes = 1, No = -1 };
TFontStyles Bold, Norm;
class TStaticFigure
{
private:
   TStatus Status;
protected:

public:
   char Letter;
   __fastcall TStaticFigure()
   {
      Status = None;
      Window = NULL;
   }
   __fastcall ~TStaticFigure()
   {
   }
   TStaticText *Window;
   void SetStatus(TStatus status)
   {
      Status = status;
      switch (Status)
      {
         case Yes:
         {
            Window->Font->Style = Bold;
            Window->Color = clSkyBlue;
            Window->Font->Color = clWindowText;
            break;
         }
         case No:
         {
            Window->Font->Style = Norm;
            Window->Color = cl3DLight;
            Window->Font->Color = clBtnShadow;
            break;
         }
         case None:
         {
            Window->Font->Style = Norm;
            Window->Color = clCaptionText;
            Window->Font->Color = clWindowText;
            break;
         }
      }
   }
   void StatusUp()
   {
      switch (Status)
      {
         case None: SetStatus(Yes); break;
         case Yes: SetStatus(No); break;
         case No: SetStatus(None); break;
      }
   }
   void StatusDown()
   {
      switch (Status)
      {
         case None: SetStatus(No); break;
         case Yes: SetStatus(None); break;
         case No: SetStatus(Yes); break;
      }
   }

} Ten[10];
class TMainForm : public TForm
{
__published:	// IDE-managed Components
   TMaskEdit *You;
   TLabel *Label1;
   TMaskEdit *His;
   TLabel *Label2;
   TEdit *Edit1;
   TMaskEdit *MaskBC;
   TButton *Go;
   TButton *StartRazgBtn;
   TValueListEditor *YourTable;
   TValueListEditor *HisTable;
   TStaticText *StaticText1;
   TStaticText *StaticText2;
   TButton *CalcCB;
   TButton *SetReal;
   TLabel *Label3;
   TButton *StartZagBtn;
   TBevel *Bevel1;
   TLabel *LLoses;
   TLabel *LWins;
   TLabel *LStage;
   TButton *StartpvpBTN;
   TMaskEdit *Secret;
   TStaticText *F1;
   TStaticText *F2;
   TStaticText *F3;
   TStaticText *F4;
   TStaticText *F5;
   TStaticText *F6;
   TStaticText *F7;
   TStaticText *F8;
   TStaticText *F9;
   TStaticText *F0;
   TButton *Hired;
   TRadioGroup *Style;
   TButton *Button1;
   void __fastcall StartRazgBtnClick(TObject *Sender);
   void __fastcall GoClick(TObject *Sender);
   void __fastcall CalcCBClick(TObject *Sender);
   void __fastcall SetRealClick(TObject *Sender);
   void __fastcall StartZagBtnClick(TObject *Sender);
   void __fastcall StartpvpBTNClick(TObject *Sender);
   void __fastcall FigureLClick(TObject *Sender);
   void __fastcall F1ContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled);
   void __fastcall HiredClick(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TMainForm(TComponent* Owner);
   BullsAndCow BC;
   AnsiString Numb; //Отправленное число
   bool CompZagad, CompOtgad;
   void GameOverFunction(bool Result, int Stage);
   void ErrorFunction(AnsiString Message);
   void BaseStart();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef WordsCowsH
#define WordsCowsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Mask.hpp>
#include <ComCtrls.hpp>
#include "CSPIN.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
const int CIPHER = 5;
const int CIP = CIPHER + 1;
const int BKV = 33;
const int UGA = 8;
enum TStatus { None = 0, Yes = 1, No = -1 };
TFontStyles Bold, Norm;
//Set <unsigned char, 'À','ß'> F[CIP], Full;
typedef unsigned char uchar;
const uchar END = 'ß'+1;
Set <unsigned char, (unsigned char) 'À', (unsigned char) 'ß'> F[CIP], Full, Player;

struct Quest
{
private:
protected:
public:
   AnsiString Str;
   int Bulls;
   int Cows;
   int All;
   Set <unsigned char, (unsigned char) 'À', (unsigned char) 'ß'> M;
  __fastcall Quest()
  {
  }
  __fastcall ~Quest()
  {
  }

} Questions;

class TStaticLetter
{
private:
protected:
   TStatus FStatus;
   bool FPos[CIP];
   inline bool GetPos(int i) { return FPos[i]; }
   inline void SetPos(int i, bool value)
   {
      FPos[i] = value;
      if (value)
         F[i] << Letter;
      else
         F[i] >> Letter;
   }

   void SetStatus(TStatus status)
   {
      FStatus = status;
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
public:
   char Letter;
   __property TStatus Status = {read=FStatus, write=SetStatus};
   __property bool Pos[int i] = {read=GetPos, write=SetPos};
   __fastcall TStaticLetter()
   {
      FStatus = None;
      Window = NULL;
      for (int i=0; i<CIP; i++)
         FPos[i] = true;
   }
   __fastcall ~TStaticLetter()
   {
   }
   TStaticText *Window;

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

} Alphabet[33];

class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TStaticText *A0;
   TStaticText *B1;
   TStaticText *V2;
   TStaticText *G3;
   TStaticText *d4;
   TStaticText *e5;
   TStaticText *e6;
   TStaticText *i9;
   TStaticText *j7;
   TStaticText *z8;
   TStaticText *i10;
   TStaticText *k11;
   TStaticText *l12;
   TStaticText *m13;
   TStaticText *n14;
   TStaticText *o15;
   TStaticText *p16;
   TStaticText *r17;
   TStaticText *s18;
   TStaticText *t19;
   TStaticText *u20;
   TStaticText *f21;
   TStaticText *h22;
   TStaticText *c23;
   TStaticText *ch24;
   TStaticText *sh25;
   TStaticText *sch26;
   TStaticText *q27;
   TStaticText *Y28;
   TStaticText *q29;
   TStaticText *e30;
   TStaticText *u31;
   TStaticText *ya32;
   TValueListEditor *List;
   TMaskEdit *NewWord;
   TMaskEdit *MaskEdit2;
   TButton *New;
   TButton *Go;
   TRichEdit *Rich;
   TButton *Refresh;
   TButton *Where;
   TListBox *L1;
   TListBox *L2;
   TListBox *L3;
   TListBox *L4;
   TListBox *L5;
   TButton *WhereBlue;
   TButton *FULL;
   TGroupBox *GroupBox1;
   TCSpinEdit *CSpinEdit1;
   TMaskEdit *Secr;
   TBitBtn *BringPos;
   TButton *Button1;
   void __fastcall StaticText1Click(TObject *Sender);
   void __fastcall StaticText1ContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
   void __fastcall GoClick(TObject *Sender);
   void __fastcall testrichClick(TObject *Sender);
   void __fastcall NewWordChange(TObject *Sender);
   void __fastcall RefreshClick(TObject *Sender);
   void __fastcall WhereClick(TObject *Sender);
   void __fastcall ListKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall WhereBlueClick(TObject *Sender);
   void __fastcall FULLClick(TObject *Sender);
   void __fastcall BringPosClick(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
   int Cow, Bull;
   DoublyConnectedList <Quest> QList;
   bool SetCowAndBull(const AnsiString &Text);
   TStaticLetter* __fastcall GetLetter(char Symb);
   bool Lister(const AnsiString &Curr, bool del);
   TListBox* LP[6];
   void AddWordPos(const AnsiString &Word);
   void RemoveWordPos(const AnsiString &Word);
   void Kill(char Letter);
   inline int LContain(int L, char Symb);
   void LAdd(int L, char Symb);
   void RemoveL(char Symb);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

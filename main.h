//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#define VARIANTSMEM
//---------------------------------------------------------------------------
const int CIPHER = 4;
const int COUNT = 10;
const int COUN = COUNT - 1;
const int CIP = CIPHER + 1;
typedef Set< int, 0, COUN> NUMB;

struct Variant
{
   //Bitset tt;
   unsigned  int F1 : 4;
   unsigned  int F2 : 4;
   unsigned  int F3 : 4;
   unsigned  int F4 : 4;
   bool Correct : 1;
    int Next : 13;
   unsigned int __fastcall GetNumb(int i)
   {
      switch (i)
      {
         case 1 : return F1;
         case 2 : return F2;
         case 3 : return F3;
         case 4 : return F4;
         default : return -1;
      }
   }
   void __fastcall SetNumb(int i, unsigned int value)
   {
      switch (i)
      {
         case 1 : F1 = value; return;
         case 2 : F2 = value; return;
         case 3 : F3 = value; return;
         case 4 : F4 = value; return;
         default : return ;
      }
   }
   __property unsigned int Numb [int i] = { read=GetNumb, write=SetNumb};
   void SetNumber(int number[4])
   {
      Correct = true;
      F1 = number[0];
      F2 = number[1];
      F3 = number[2];
      F4 = number[3];
   }
   void CalcCowAndBull(const NUMB &Test, int &Cow, int &Bull)
   {
      //Vari.->RCS(); //Œœ≈–¿“Œ– HELL
      Cow = 0; Bull = 0;
      if (Test.Contains(F1)) Cow++;
      if (Test.Contains(F2)) Cow++;
      if (Test.Contains(F3)) Cow++;
      if (Test.Contains(F4)) Cow++;
   }
   bool CheckCorrect(const unsigned int* TestMas, const NUMB &TestM, int Cow, int Bull )
   {
      if (TestM.Contains(F1)) Cow--;
      if (TestM.Contains(F2)) Cow--;
      if (TestM.Contains(F3)) Cow--;
      if (TestM.Contains(F4)) Cow--;
      if (TestMas[0] == F1)  Bull--;
      if (TestMas[1] == F2)  Bull--;
      if (TestMas[2] == F3)  Bull--;
      if (TestMas[3] == F4)  Bull--;
      if ( (Cow == 0)&&(Bull == 0) )
         return true;
      else
         return false;
   }
};


class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TStringGrid *Grid;
   TMaskEdit *MaskEdit1;
   TMaskEdit *MaskEdit2;
   TBitBtn *Search;
   TEdit *Edit1;
   TButton *Button1;
   TButton *Button2;
   TButton *SearchNext;
   TButton *New;
   TLabel *Label1;
   void __fastcall SearchClick(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall Button2Click(TObject *Sender);
   void __fastcall SearchNextClick(TObject *Sender);
   void __fastcall NewClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
   //bool __fastcall Nin
   unsigned  int Numb[5];
   NUMB Number, CurrNo, N[5], Full;
   //bitset<4> Bitt;
   ::Variant *Store;
   int Cows, Bulls;
   int CurrCows, CurrBulls;
   void SetNumber(AnsiString number, bool IndexFromOne = true)
   {
      Number.Clear();
      if (IndexFromOne)
         for (int i=1; i<CIP; i++)
         {
            Numb[i] = StrToInt(number[i]);
            Number << Numb[i];
         }
      else
         for (int i=0; i<CIPHER; i++)
         {
            Numb[i] = StrToInt(number[i+1]);
            Number << Numb[i];
         }
   }
   bool CalcCows, CalcBulls;
   inline bool __fastcall CheckPar(unsigned int num,  int pos);

   inline  int CalcCow( int n1,  int n2,  int n3,  int n4)
   {
      int C=0;
      if (Number.Contains(n1))  C++;
      if (Number.Contains(n2))  C++;
      if (Number.Contains(n3))  C++;
      if (Number.Contains(n4))  C++;
      return C;
   }
   inline  int CalcBull(unsigned  int n1, unsigned  int n2, unsigned  int n3, unsigned  int n4)
   {
      int B=0;
      if (Numb[1] == n1)   B++;
      if (Numb[2] == n2)   B++;
      if (Numb[3] == n3)   B++;
      if (Numb[4] == n4)   B++;
      return B;
   }
   int MaxRow;
   inline void __fastcall CyclerStart(int Numb);

   int StoreCount, StoreFirst;
   int VariantCount(const int Cow, const int Bull)
   {
      //if (Cow < Bull) ÚÛÚ ÔÓ‚ÂÓ˜Í‡
      switch (Cow)
      {
         case 0 : switch (Bull)
            {
               case 0 : return 360;
               default: return 0;
            }
         case 1 : switch (Bull)
            {
               case 0 : return 1440;
               case 1 : return 480;
               default: return 0;
            }
         case 2 : switch (Bull)
            {
               case 0 : return 1260;
               case 1 : return 720;
               case 2 : return 180;
               default: return 0;
            }
         case 3 : switch (Bull)
            {
               case 0 : return 264;
               case 1 : return 216;
               case 2 : return 72;
               case 3 : return 24;
               default: return 0;
            }
         case 4 : switch (Bull)
            {
               case 0 : return 9;
               case 1 : return 8;
               case 2 : return 6;
               case 4 : return 1;
               default: return 0;
            }
         default: return 0;
      }
   }
   bool SetCowAndBull(int Cow, int Bull);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

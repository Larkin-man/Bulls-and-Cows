//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
   for (int i=0; i<10; i++)
      Full << i;
   MaxRow = 0;
   Store = NULL;
   StoreFirst = 0;
}
//---------------------------------------------------------------------------
inline void __fastcall TForm1::CyclerStart(int Numb)
{
   N[Numb] -= CurrNo;
}
void __fastcall TForm1::SearchClick(TObject *Sender)
{
   if (SetCowAndBull(StrToInt(MaskEdit2->Text[1]), StrToInt(MaskEdit2->Text[3])) == false)
      return;
#ifdef VARIANTSMEM
   if (Store == NULL)
   {  //Первый раз - выделяем память
      StoreCount = VariantCount(Cows, Bulls);
      Store = new ::Variant[StoreCount];
   }
#endif
   SetNumber(MaskEdit1->Text);
   NUMB Base = Full;
   CalcCows = true; CalcBulls = true;
   int Row = 0;
   CurrCows = 0; CurrBulls = 0;
   if (Cows == CIPHER)
   {
      Base.Clear();
      for (int i=1; i<CIP; i++)
         Base << Numb[i];
      CalcCows = false;
   } else
   if (Cows == 0)
   {
      for (int i=1; i<CIP; i++)
         Base >> Numb[i];
      CalcCows = false;
   }
   /////////////////////////
   //Цикл по первой цифре
   N[1] = Base;
   if (Bulls == 0)
   {
      N[1] >> Numb[1];
      CalcBulls = false;
   }
   unsigned int n[5];
   for (n[1]=0; n[1]<10; n[1]++)
   {
      if ( !N[1].Contains(n[1]) )  continue;
      //Базовая инициальзация в начале каждого числа
         CurrNo.Clear();
         CalcCows = false; //возм лишн
         CurrCows = 0; CurrBulls = 0;
         if ( (Cows > 0)&&(Cows < CIPHER) )
         {  CalcCows = true;      }
         N[2] = Base; N[3] = Base; N[4] = Base;
         CalcBulls = true;
         if (Bulls == 0)
         {   CalcBulls = false; N[2] >> Numb[2]; N[3] >> Numb[3]; N[4] >> Numb[4]; }

      //--------------------------------------------
      //if ( CheckPar(n1, 1) )  continue;
      //Цикл по второй цифре
      //Уже были
      NUMB N2 = N[2];
      N2 >> n[1]; //да
      N2 -= CurrNo;
      if (Bulls == 0)
         N2 >> Numb[2];
      for (n[2]=0; n[2]<10; n[2]++)
      {
         if ( !N2.Contains(n[2]) )  continue;
         //if ( CheckPar(n2, 2) )  continue;
         //Цикл по третьей цифре
         //CurrNo << n2; //Эта уже была
         NUMB N3 = N[3];
         N3 >> n[1]>>n[2];
         N3 -= CurrNo;
         if (Bulls == 0)
            N3 >> Numb[3];
         for (n[3]=0; n[3]<10; n[3]++)
         {
            if ( !N3.Contains(n[3]) )  continue;
            //if ( CheckPar(n3, 3) )  continue;
            //Цикл по четвертой цифре
            //CurrNo << n3; //Эта уже была
            NUMB N4 = N[4];
            N4 >> n[1]>>n[2]>>n[3];
            N4 -= CurrNo;
            if (Bulls == 0)
               N4 >> Numb[4];
            for (n[4]=0; n[4]<10; n[4]++)
            {
               if ( !N4.Contains(n[4]) )  continue;
               //if ( CheckPar(n4, 4) )  continue;
               CurrCows = 0; CurrBulls = 0;
               for (int i=1; i<CIP; i++)
               {
                  if (Number.Contains(n[i]))
                     CurrCows++;
                  if (Numb[i] == n[i])
                     CurrBulls++;
               }
               if ( (CurrCows != Cows)||(CurrBulls != Bulls) )
                  continue;
               //Главный
               #ifdef VARIANTSMEM
               if (Row >= StoreCount)
                  ShowMessage(IntToStr(Row));
               Store[Row].F1 = n[1];
               Store[Row].F2 = n[2];
               Store[Row].F3 = n[3];
               Store[Row].F4 = n[4];
               Store[Row].Next = Row+1;
               #endif
               Row++;
               for (int i=0; i<CIPHER; i++)
               {
                  Grid->Cells[i][Row] = n[i+1];
               }
               Grid->Cells[5][Row] = CurrCows;
               Grid->Cells[6][Row] = CurrBulls;
            }
         }
      }
   }
   Edit1->Text = "Цифр "+IntToStr(Row);
   Row++;
   for (int i=Row; i<MaxRow; i++)
      for (int j=0; j<7; j++)
         Grid->Cells[j][i] = "";
   MaxRow = Row;
}
//---------------------------------------------------------------------------
inline bool __fastcall TForm1::CheckPar(unsigned int num,  int pos)
{
   if (CalcCows)
      if (Number.Contains(num))
         if (CurrCows+1 > Cows)
            return true;
         else
            CurrCows++;
   if (CalcBulls)
      if (Numb[pos] == num)
         CurrBulls++;
   if     ( (CurrCows > Cows)||(CurrBulls > Bulls) )
      return true;
   if (CalcCows)
      if(CurrCows == Cows)  //Уже все коровы на месте
         for (int i=pos+1; i<CIP; i++) //По остальным цифрам сгенерированного
            CurrNo << Numb[i];
   if (CalcBulls)
      if(CurrBulls == Bulls)//Все быки на месте
      {
         for (int i=pos+1; i<CIP; i++)
            N[i] >> Numb[i];
      }
   return false;
}
//-----------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   Store = new ::Variant[100];
   for (int i=0; i<100; i++)
   {
      Store[i].F1 = i;
      Store[i].Next = i+1;
   }
   Store[99].Next = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
   delete [] Store;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
   /*int idx = 0;
   while (Store[idx].Next != 0)
   {
      Grid->Cells[0][idx] = Store[idx].F1;
      idx = Store[idx].Next;
   }   */
   for (int idx=0; idx < StoreCount; idx = Store[idx].Next)
   {
      Grid->Cells[0][idx+1] = Store[idx].F1;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SearchNextClick(TObject *Sender)
{
   if (SetCowAndBull(StrToInt(MaskEdit2->Text[1]), StrToInt(MaskEdit2->Text[3])) == false)
      return;
   if (Store == NULL)
      return;
   SetNumber(MaskEdit1->Text, false);
   for (int i=1; i<MaxRow; i++)
      for (int j=0; j<7; j++)
         Grid->Cells[j][i] = "";
   int Row = 0, Last = -1;;
   for (int idx=StoreFirst; idx < StoreCount; idx = Store[idx].Next)
   {
      if (Store[idx].CheckCorrect(Numb, Number, Cows, Bulls))
      {
         if (Last > -1)
         {
            Store[Last].Next = idx;
         }
         else if (Last == -1)
         {
            StoreFirst = idx;
         }
         Last = idx;
         Row++;
         Grid->Cells[0][Row] = Store[idx].F1;
         Grid->Cells[1][Row] = Store[idx].F2;
         Grid->Cells[2][Row] = Store[idx].F3;
         Grid->Cells[3][Row] = Store[idx].F4;  
      }
   }
   Store[Last].Next = StoreCount;
   Edit1->Text = "Цифр "+IntToStr(Row);
   Row++;
   for (int i=Row; i<MaxRow; i++)
      for (int j=0; j<7; j++)
         Grid->Cells[j][i] = "";
   MaxRow = Row;
}
//---------------------------------------------------------------------------
bool TForm1::SetCowAndBull(int Cow, int Bull)
{
   if ( (Cow < 0)||(Cow > CIPHER) )
   {
      ShowMessage("Ошибка: Коров="+IntToStr(Cows));
      return false;
   }
   if ( (Bull < 0)||(Bull > CIPHER) )
   {
      ShowMessage("Ошибка: Быков="+IntToStr(Bulls));
      return false;
   }
   Cows = Cow;
   Bulls = Bull;
   return true;
}

void __fastcall TForm1::NewClick(TObject *Sender)
{
   delete [] Store;
   Store = NULL;
   MaxRow = 0;
   StoreFirst = 0;
   StoreCount = 0;
}
//---------------------------------------------------------------------------


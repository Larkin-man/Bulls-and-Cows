//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "DoublyConnectedList.cpp"
#include "CodeWords.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
   Alphabet[0].Window = A0;
   Alphabet[1].Window = B1;
   Alphabet[2].Window = V2;
   Alphabet[3].Window = G3;
   Alphabet[4].Window = d4;
   Alphabet[5].Window = e5;
   Alphabet[6].Window = e6;
   Alphabet[7].Window = j7;
   Alphabet[8].Window = z8;
   Alphabet[9].Window = i9;
   Alphabet[10].Window = i10;
   Alphabet[11].Window = k11;
   Alphabet[12].Window = l12;
   Alphabet[13].Window = m13;
   Alphabet[14].Window = n14;
   Alphabet[15].Window = o15;
   Alphabet[16].Window = p16;
   Alphabet[17].Window = r17;
   Alphabet[18].Window = s18;
   Alphabet[19].Window = t19;
   Alphabet[20].Window = u20;
   Alphabet[21].Window = f21;
   Alphabet[22].Window = h22;
   Alphabet[23].Window = c23;
   Alphabet[24].Window = ch24;
   Alphabet[25].Window = sh25;
   Alphabet[26].Window = sch26;
   Alphabet[27].Window = q27;
   Alphabet[28].Window = Y28;
   Alphabet[29].Window = q29;
   Alphabet[30].Window = e30;
   Alphabet[31].Window = u31;
   Alphabet[32].Window = ya32;
   LP[1] = L1;
   LP[2] = L2;
   LP[3] = L3;
   LP[4] = L4;
   LP[5] = L5;
   Bold << fsBold, Norm.Clear();
   List->RowHeights[0] = 24;
   //List->InsertRow()
   for (int i=0; i<33; i++)
   {
      Alphabet[i].Letter = Alphabet[i].Window->Caption[2];
      Full << Alphabet[i].Letter;
   }
   for (int i=1; i<CIP; i++)
   {
      LP[i]->Items->Clear();
      F[i] = Full;
   }
   F[1] >> 'Ъ'>>'Ь'>>'Ы';
   Kill('Ё');
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StaticText1Click(TObject *Sender)
{
   TStaticText *Let = ((TStaticText*)Sender);
   for (int i=0; i<33; i++)
   {
      if (Alphabet[i].Window == Let)
      {
         Alphabet[i].StatusUp();
         //Let->Caption = Let->Caption;
         break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StaticText1ContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
   TStaticText *Let = ((TStaticText*)Sender);
   for (int i=0; i<33; i++)
   {
      if (Alphabet[i].Window == Let)
      {
         Alphabet[i].StatusDown();
         //Let->Refresh();
         break;
      }
   }
}
//---------------------------------------------------------------------------
bool TForm1::SetCowAndBull(const AnsiString &Text)
{
   Cow = StrToInt(Text[3]);
   Bull =StrToInt(Text[1]);
   if ( (Bull<0)||(Bull>CIPHER) )
      return true;
   if ( (Cow<0)||(Cow>CIPHER) )
      return true;
   return false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GoClick(TObject *Sender)
{
   SetCowAndBull(MaskEdit2->Text);
   AnsiString Word = NewWord->Text;
   Word = Word.UpperCase();
   Quest Q;
   Q.Str = Word;
   Q.Bulls = Bull;
   Q.Cows = Cow;
   Q.All = Cow+Bull;
   for (int i=1; i<CIP; i++)
      Q.M << Word[i];
   QList.Add(Q);
   List->InsertRow(Word, MaskEdit2->Text+"   ("+IntToStr(Q.All)+")", true);
   if ((Cow == 0)&&(Bull == 0))
   {
      for (int j=1; j<CIP; j++)
      {
         char C = Word[j];
         for (int i=0; i<BKV; i++)
         {
            if (Alphabet[i].Letter == C)
            {
               Alphabet[i].Status = No;
               break;
            }
         }
      }
      Lister(Word, true);
   }else if (Cow == 0)
   {
      AddWordPos(Word);
   } 
   if (Bull == 0)
      RemoveWordPos(Word);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::testrichClick(TObject *Sender)
{
   Rich->SelStart = 2;
   Rich->SelLength = 1;
   Rich->SelAttributes->Color = clRed;
   //Rich->Lines->Add(Rich->Lines->Count);
   Rich->SelAttributes->Color = clBlue;
   //Rich->Lines[0].Text.Insert("R",2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NewWordChange(TObject *Sender)
{
   AnsiString Word = NewWord->Text.UpperCase();
   Rich->Text = Word;
   Rich->SelStart = 0;
   Rich->SelLength = 5;
   Rich->SelAttributes->Color = clBlack;
   if (Word[1] == ' ')
      return;
   for (int i=1; i<CIP; i++) //По позициям буквы
   {
      char C = Word[i];
      if (C == ' ')
         return;
      TStaticLetter *Let = GetLetter(C);
      if (Let->Status == No)
      {
         Rich->SelStart = i-1;
         Rich->SelLength = 1;
         Rich->SelAttributes->Color = clRed;
      }
      else
      {  //Смотрим если она не на месте i
         if (Let->Pos[i] == false)
         {
            Rich->SelStart = i-1;
            Rich->SelLength = 1;
            Rich->SelAttributes->Color = clTeal;
         }
         /*if (List->RowCount < 3)
            return;
         for (int s=1; s<List->RowCount; s++)
         {
            if (List->Cells[1][s][1] != '0') //коров
               continue;
            AnsiString Word = List->Keys[s];
            if (Word[i] == Let->Letter)
            {
               Rich->SelStart = i-1;
               Rich->SelLength = 1;
               Rich->SelAttributes->Color = clTeal;
            }
         }  */
      }
   }
}
//---------------------------------------------------------------------------

TStaticLetter* __fastcall TForm1::GetLetter(char Symb)
{
   for (int i=0; i<BKV; i++)
      if (Alphabet[i].Letter == Symb)
         return &Alphabet[i];
   return NULL;
}
//---------------------------------------------------------------------------
bool TForm1::Lister(const AnsiString &Curr, bool del)
{
   //Цикл по листу
   if (del == false)
      return true;
   for (int s=1; s<List->RowCount; s++)
   {
      AnsiString Word = List->Keys[s];
      if (Word == "")
         return true;
      if (List->Cells[1][s][UGA] == '0')
         continue;
      for (int i=1; i<CIP; i++)
         for (int j=1; j<CIP; j++)
            if (Curr[i] == Word[j])
               Word[j] = '_';
      List->Keys[s] = Word;
   }
   return false;   
}

//---------------------------------------------------------------------------
void __fastcall TForm1::RefreshClick(TObject *Sender)
{
   for (int s=1; s<List->RowCount; s++)
   {
      if (List->Cells[1][s][UGA] == '0')
         continue;
      AnsiString Word = List->Keys[s];
      for (int i=1; i<CIP; i++)
      {
         if (Word[i] != '_')
            if (GetLetter(Word[i])->Status == No)
               Word[i] = '_';
      }
      List->Keys[s] = Word;
   }
   for (int i=0; i<BKV; i++)
      if (Alphabet[i].Status == No)
         RemoveL(Alphabet[i].Letter);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::WhereClick(TObject *Sender)
{
   //Memo1->Text = "";
   for (int i=0; i<BKV; i++)
   {
      if (Alphabet[i].Status == Yes)
      {
         char yep = Alphabet[i].Letter;
         AnsiString Bkv = "_____";
         for (int s=1; s<List->RowCount; s++)
         {
            AnsiString Word = List->Keys[s];
            AnsiString Value = List->Cells[1][s];
            if (List->Cells[1][s][1] == '0')
            {
            }
            for (int j=1; j<CIP; j++)
            {
               if (Word[j] == yep)
               {
                  //int B = StrToInt(Value[1]);
                  //int A = StrToInt(Value[UGA]);
                  Word[j] = '_';
                  //Value[1] = B-1;
                  //Value[UGA] = (A-1);
               }
            }
            List->Cells[1][s] = Value;
         }
      }
   }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
   if (Key == VK_DELETE)
      List->DeleteRow(List->Row);
}
//---------------------------------------------------------------------------
//0 Коров
void TForm1::AddWordPos(const AnsiString &Word)
{
   for (int j=1; j<CIP; j++) //По символам слова
   {
      TStaticLetter* Let = GetLetter(Word[j]);
      if (Let->Pos[j] == false)
         Kill(Word[j]);
      for (int p=1; p<CIP; p++)
         Let->Pos[p] = false;
      if (Let->Status == No)
         continue;
      else
         Let->Pos[j] = true;
      //Искать в листах и добавить
      int i = 0;
      for (; i<LP[j]->Items->Count; i++)
         if (LP[j]->Items->Strings[i] == Word[j])
            break;
      if (i == LP[j]->Items->Count)
         LP[j]->Items->Add(Word[j]);
   }
}
//---------------------------------------------------------------------------
void TForm1::RemoveWordPos(const AnsiString &Word) //0 Быков
{
   for (int j=1; j<CIP; j++) //По символам слова
   {
      TStaticLetter* Let = GetLetter(Word[j]);
      Let->Pos[j] = false;
      int i = 0;
      for (; i<LP[j]->Items->Count; i++)
      {
         if (LP[j]->Items->Strings[i] == Word[j])
            break;
      }
      if (i != LP[j]->Items->Count) //она там есть
         LP[j]->Items->Delete(i);
      //Посчиаем где она не может
      i = 0;
      for (int p=1; p<CIP; p++)
         if (Let->Pos[p] == true)
            i++;
      if (i == 0)
      {
         if (Let->Status != No)
            Rich->Lines->Add("Kill "+AnsiString(Word[j]));
         Kill(Word[j]);
      }
      //---------------------------- Осталась только на одном месте
      else if (i == 1)
      {
         for (int b=1; b<CIP; b++) //По Листбоксам
         {
            i = 0;
            for (; i<LP[b]->Items->Count; i++)
               if (LP[b]->Items->Strings[i] == Word[j])
                  break;
            if (i != LP[b]->Items->Count) //она там есть
            {
               if (Let->Pos[b] == false)
                  LP[b]->Items->Delete(i);
            } else //её там нет
               if (Let->Pos[b] == true)
                  LP[b]->Items->Add(Word[j]);
         }
      }
   }
}
//---------------------------------------------------------------------------
void TForm1::Kill(char Letter)
{
   TStaticLetter* Let = GetLetter(Letter);
   Let->Status = No;
   for (int i=0; i<CIP; i++)
      Let->Pos[i] = false;
   for (int i=1; i<CIP; i++)
      if (LContain(i, Letter) != -1)
         LP[i]->Items->Delete(i);
   RemoveL(Letter);
   Full >> Letter;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WhereBlueClick(TObject *Sender)
{
   for (int i=0; i<BKV ;i++)
      if (Alphabet[i].Status == Yes)
         for (int j=1; j<CIP ;j++) //По позициям Pos
            if (LContain(j,Alphabet[i].Letter) == -1) //Её нет в листе
            {
               if (Alphabet[i].Pos[j] == true)
                  LP[j]->Items->Add(Alphabet[i].Letter);
            } else //Она есть в листе
            {
               if (Alphabet[i].Pos[j] == false)
                  LP[j]->Items->Delete(LContain(j,Alphabet[i].Letter));
            }
}
//---------------------------------------------------------------------------
inline int TForm1::LContain(int L, char Symb)
{
   for (int i=0; i<LP[L]->Count ;i++)
      if (LP[L]->Items->Strings[i] == Symb)
         return i;
   return -1;
}
//---------------------------------------------------------------------------
void TForm1::RemoveL(char Symb)
{
   for (int i=1; i<CIP ;i++) //По листбоксам
      for (int j=0; j<LP[i]->Count ;j++)
         if (LP[i]->Items->Strings[j] == Symb)
         {
            LP[i]->Items->Delete(j);
            break;
         }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FULLClick(TObject *Sender)
{
   //Тест----------------------------------------------
   //Full.Clear();
   //Full << 'А' <<'Г'<< 'О'<<'Н'<<'Ы'<<'Х';
   //F[1] >> 'Ы';
   //F[3].Clear();  F[3] << 'Й'<<'Ь';
   //--------------------------------------------------
   Player.Clear();
   for (int i=0; i<BKV; i++)
      if (Alphabet[i].Status == No)
         Player << Alphabet[i].Letter;
   Full -= Player;
   int Count = 0;
   //Box->Items->Capacity = 1000;
   for (int i=1; i<CIP; i++)
   {
      F[i] *= Full;
   }
   AnsiString word = "12345";
   uchar N[CIP];
   for (N[1]='А'; N[1]<END; N[1]++)
   {
      if (!F[1].Contains(N[1])) continue;
      for (N[2]='А'; N[2]<END; N[2]++)
      {
         if (!F[2].Contains(N[2])) continue;
         if (N[2] == N[1]) continue;
         for (N[3]='А'; N[3]<END; N[3]++)
         {
            if (!F[3].Contains(N[3])) continue;
            if ( (N[3] == N[1])||(N[3] == N[2]) ) continue;
            for (N[4]='А'; N[4]<END; N[4]++)
            {
               if (!F[4].Contains(N[4])) continue;
               if ( (N[4] == N[1])||(N[4] == N[2])||(N[4] == N[3]) ) continue;
               for (N[5]='А'; N[5]<END; N[5]++)
               {
                  if (!F[5].Contains(N[5])) continue;
                  if ( (N[5] == N[1])||(N[5] == N[2])||(N[5] == N[3])||(N[5] == N[4]) ) continue;
                  //Главный код
                  Count++;
                  if (Count > 9999) { Rich->Lines->Add(Count); return; }
                  int i=0;
                  for (; i<QList.Count; i++)
                  {
                     int B = QList[i].Bulls;
                     int A = QList[i].All;
                     for (int j=1; j<CIP; j++)
                        if (QList[i].Str[j] == N[j])
                           B--;
                     if (B != 0)
                        break;
                     for (int j=1; j<CIP; j++)
                        if (QList[i].M.Contains(N[j]))
                           A--;
                     if (A != 0)
                        break;  
                  }
                  if (i < QList.Count)
                     continue;
                  for (int i=1; i<CIP; i++)
                     word[i] = N[i];
                  //Box->Items->Add(word);
               }
            }
         }
      }
   }
   Rich->Lines->Add(Count);
   //uchar n = END;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BringPosClick(TObject *Sender)
{
   char Letter = Secr->Text.UpperCase()[1];
   int P = CSpinEdit1->Value;
   Rich->Lines->Add(Letter);
   TStaticLetter* Let;
   for (int i=0; i<BKV; i++)
   {
      Alphabet[i].Pos[P] = false;
      if (Alphabet[i].Letter == Letter)
         Let = &Alphabet[i];
   }
   for (int i=1; i<CIP; i++)
   {
      Let->Pos[i] = false;
      int Cont = LContain(i, Letter);
      if (Cont > -1)
         LP[i]->Items->Delete(Cont);
   }
   Let->Pos[P] = true;
   Let->Status = Yes;
   LP[P]->Items->Clear();
   LP[P]->Items->Add(Letter);
   F[P].Clear();
   F[P] << Letter;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
   for (int i=0; i<QList.Count; i++)
   {
      //Box->Items->Add(QList[i].Str+IntToStr(QList[i].Bulls));
   }

}
//---------------------------------------------------------------------------



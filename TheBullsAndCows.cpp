//---------------------------------------------------------------------------
//#include <Classes.hpp>
//#include <dstring.h> //нельзя
#include <Classes.hpp>
//#include <SysUtils.hpp> //это хуже чем систм
//#include <sysclass.H>
#include <time.h>
#include <stdlib.h>
#pragma hdrstop
#include "TheBullsAndCows.h"

//---------------------------------------------------------------------------
//Конструктор быков с коровами
__fastcall BullsAndCow::BullsAndCow()
{
   //srand(time(0));   //рандомизация называется. Типа зерно задаем
   for (int i=0; i<10; i++)
      Full << i;
   Store = NULL;
   Win = 0;
   Lose = 0;
   FStage = 0;
   //BaseStart
   randomize();
   StoreFirst = 0;
   StoreCount = 0;
   CompZagad = false;
   CompOtgad = false;
   GameOver = false;
}
//-------------------------------------------------
//Деструктор быков с коровами
__fastcall BullsAndCow::~BullsAndCow()
{
   delete [] Store;
}
//-------------------------------------------------
//Подготовить новую игру. Автоматическое поражение, если игра уже идет.
void BullsAndCow::BaseStart()
{
   if (GameOver == false)
   {
      if (FStage > 0)
      {
         Lose++;
         //if (GameOver)
         //   GameOver(false, FStage); 
      }
   }
   randomize();
   StoreFirst = 0;
   StoreCount = 0;
   FStage = 0;
   if (Store)
   {
      delete [] Store;
      Store = NULL;
   }
   Confidential.Clear();
   if (CompZagad)   //Загадываем число Confident
   {
      RandomNumber(Confident);
      for (int i=1; i<CIP; i++)
         Confidential << Confident[i];
   }
   for (int i=1; i<CIP; i++)
      No[i].Clear();
   GameOver = false;
}
//-------------------------------------------------
//Игра на загадывание игроком
AnsiString BullsAndCow::Start(Difficult difficult)
{
   CompZagad = false;
   CompOtgad = true;
   Diff = difficult;
   BaseStart();
   RandomNumber(Quest);
   AnsiQuest = NumbToAnsi(Quest);
   Vect.reserve(16);
   Vect.push_back(Quest);
   return AnsiQuest;
}
//-------------------------------------------------
//Игра на отгадывание игроком
void BullsAndCow::NewGame()
{
   CompZagad = true;
   CompOtgad = false;
   BaseStart();
}
//-------------------------------------------------

AnsiString BullsAndCow::NumbToAnsi(NUMB &numb)
{
   AnsiString Res ;//= AnsiString::StringOfChar('*',CIP);
   for (int i=1; i<CIP; ++i)
      //Res[i] = char(numb[i]-'0');
      Res.Insert(numb[i], i);
   return Res;
}
//-------------------------------------------------
//Игра на отгадывание и загадывание
AnsiString BullsAndCow::NewGame(Difficult difficult)
{
   CompZagad = true;
   CompOtgad = true;
   Diff = difficult;
   BaseStart();
   RandomNumber(Quest);
   AnsiQuest = NumbToAnsi(Quest);
   Vect.reserve(16);
   Vect.push_back(Quest);
   return AnsiQuest;
}
//-------------------------------------------------
//Игра на отгадывание и загадывание ИЛИ просто отгадывание
//Numb - игрок пытается отгадать, возвращает комп пытается отгадать. bull cow это ответ игрока на quest. Возращаются ответ на numb при отгадывании 
bool BullsAndCow::Play(AnsiString &Numb, int &bull, int &cow) //на отгадывание тоже эта
{
   //Проверка корректности
   if (CompOtgad)
   {
      if ( cow < 0 )
         return ThrowError("Коров не может быть меньше нуля.");
      if ( bull < 0 )
         return ThrowError("Быков не может быть меньше нуля.");
      if ( (bull + cow) > CIPHER)
         return ThrowError("Не верное число быков и коров.");
      Vect.back().SetCowAndBull(bull, cow);
      //Quests ti(Quest);//(Quest, bull, cow);
      //ti.SetNumb(Quest);
   }
   if (CompZagad)
   {
      if (Numb.Length() < CIPHER)
         return ThrowError("Количество цифр в числе меньше требуемого.");
      for (int i=1; i<CIP; i++)
      {
         char c = Numb[i];
         if ( (c < '0') || (c > '9') )
            return ThrowError("Недопустимый символ.");
         for (int j=1; j<i; j++)
            if (Numb[j] == c)
               return ThrowError("Символы не должны повторяться.");
         //Quest[i] = StrToInt(Numb[i]);
      }
   }
   //ИГРА
   FStage++;
   if (CompOtgad) //Загадывание игроком, принимает cow и bull и Quest, возвр NUmb(Quest)
   {
      //Нужно сформировать Quest
      if (bull == CIPHER)
      {
         if (GameOver == false)
         {
            Lose++;
            GameOver = true;
            if (GameOverEvent)
            GameOverEvent(false, FStage);
         }
      }
      if (Diff == bcEasy)
      {
         if (bull == 0)
         {  //добавить все в No
            for (int i=1; i<CIP; i++)
               No[i] << Quest[i];
            KillerClean();
         }
         if (cow == 0)
         {
            if (bull > 0)
            {
               for (int i=1; i<CIP; i++)
               {
                  if (No[i].Contains(Quest[i]))
                     Kill(Quest[i]);
                  else
                  {
                     for (int j=1; j<CIP; j++)
                        No[j] << Quest[i];
                     No[i] >> Quest[i];
                  }
               }                   
            }
            else //bull = 0 cow=0
            {
               for (int i=1; i<CIP; i++)
                  Kill(Quest[i]);
            }
            KillerClean();
         } else
         if (cow + bull == 4)
         {
            NoCow.Clear(); YesCow.Clear();
            for (int i=0; i<10; i++)
               NoCow << i;
            for (int i=1; i<CIP; i++)
            {
               YesCow << Quest[i];
               NoCow >> Quest[i];
            }
            KillerClean();
            //return RandomAll();
         }
         CreateQuest();
         AnsiQuest = NumbToAnsi(Quest);
         Vect.push_back(Quest);
         //Numb = NumbToAnsi(Quest);
      } //bcEasy ------------------------------
      else //Отгадывание на сложном
      {
         if (FStage == 1)
            CreateVariants(Quest, bull, cow);
         else
         {
            SearchVariants(Quest, bull, cow);
         }
         if (StoreCount <= 0)
         {
            Lose++;
            GameOver = true;
            return ThrowError("Вы мухлюете! Игра окончена."); 
         }
         int R = (rand() % Row);
         int ToR = 0;
         for (int idx=StoreFirst; idx < StoreCount; idx = Store[idx].Next)
         {
            if (ToR == R)
            {
               Store[R].GetNumb(Quest);
               AnsiQuest = NumbToAnsi(Quest);
               break;
            }
            ++ToR;
         }
         //Numb = Quest; //Пытаемся отгадать это в конце         
      } //bcHard

   }
   if (CompZagad) //Загадывание компом, принимает Numb, Confident возвр bull и cow
   {       
      //Подсчитаем быков и коров
      bull = 0; cow = 0;
      for (int i=1; i<CIP; i++)
      {
         if (Confident[i] == Numb[i]-'0')
            bull++;
         if (Confidential.Contains(Numb[i]-'0'))
            cow++; 
      }
      cow -= bull;
      if (bull == CIPHER)
      {
         if (GameOver == false)
         {
            Win++;
            GameOver = true;
            if (GameOverEvent)
            GameOverEvent(true, FStage);
         }
      }
   }
   if (CompOtgad)
   {
      Numb = AnsiQuest;
   }
   return false;
}                                                 
//-------------------------------------------------
inline bool BullsAndCow::ThrowError(AnsiString str)
{
   if (ErrorFunction)
      ErrorFunction(str);
   return true;
}
//-------------------------------------------------
//CreateQuest - случайное число для отгадывания компом на Easy
AnsiString BullsAndCow::CreateQuest()
{
   int Wrong = 0;
   //randomize();
   //AnsiString Str = "";     
   strt:          
   No[0] = NoCow;
   for (int i=1; i<CIP; ++i)
      Quest[i] = 10;
   unsigned int Temp[10];
   if (YesCow.Empty() == false)
   {
      int Count = 0;
      for (int figure=0; figure<10; ++figure)
      {
         if (YesCow.Contains(figure))
         {
            Count = 0;
            for (int j=1; j<CIP; ++j)
            {
               if (No[j].Contains(figure) == false)
               {
                  Temp[Count] = j;
                  Count++;
               }
            }
            if (Count == 0)
            {
               return "У вас есть цифра "+IntToStr(figure)+"но не на одной из позиций! Мухлевщик!";
            }
            else
               Quest[Temp[rand() % Count]];
            
         }
      }
   }
   for (int i=1; i<5; i++)
   {
      int gen = AIRndFromSet(No[i]);
      if (gen == -1)
      {
         Wrong++;
         if (Wrong < 20)
            goto strt;
         else
            return "WRONG";
      }

      No[0] << gen;
      //Numb[i+1] = (gen);
      //Str.Insert(gen, i);
   }
   //tabl->Add(Numb);
   //Quest = Numb;
   return NumbToAnsi(Quest);
}
//-------------------------------------------------
int BullsAndCow::AIRndFromSet(NUMBERSET &N)
{
   int FMas[10];
   int Pos = 0;
   for (int i=0; i<10; i++)
   {
      if (!((N.Contains(i))||(No[0].Contains(i))))
      {
         FMas[Pos] = i;
         Pos++;
      }
   }
   //int Count = Pos + 1;
   if (Pos == 0)
      return -1;
   int RandPos = (rand() % (Pos));
   return FMas[RandPos];
}

//-------------------------------------------------
//Игра на Зашадывание игроком, принимает cow и bull как ответ на quest
AnsiString BullsAndCow::Answer(int Cow, int Bull)
{
   //if (tabl == NULL)
   //   return "Ещё не начали";
   if ((Cow < 0)||(Bull < 0))
      return "Че ты пишешь?";
   if ((Cow > CIPHER)||(Bull > CIPHER))
      return "Че так много?";
   FStage++;
   //if (Bull == 4)
   //   return "Я победил за "+IntToStr(Stage)+" попыток";
   //ОТГАДЫВАНИЕ
   //Занести в QC[] цифры запроса

   return CreateQuest();
}
//-------------------------------------------------

int BullsAndCow::Count(NUMBERSET &N)
{
   int Count = 0;
   for (int i=0; i<10; i++)
      if (N.Contains(i))
         Count++;
   return Count;
}
//-------------------------------------------------
void BullsAndCow::Kill(int Cow)
{
   for (int i=1; i<CIP; i++)
      No[i] << Cow;
   NoCow << Cow;
}

void BullsAndCow::KillerClean()
{  /*
   for (int i=0; i<10; i++)
      if ( (No[1].Contains(i))&&(No[2].Contains(i))&&(No[3].Contains(i))&&(No[4].Contains(i))  )
      {   NoCow << i;  }//ShowMessage("Отсекаитса "+IntToStr(i));  }*/
}

//-------------------------------------------------
void BullsAndCow::Push(int pos, int num)
{
   YesCow << num;
   for (int p=1; p<CIP; p++)
   {
      if (p != pos)
         No[p] << num;
   }
}    
//-------------------------------------------------
inline int BullsAndCow::CalcCow( int n1,  int n2,  int n3,  int n4)
   {
      int C=0;
      if (Confidential.Contains(n1))  C++;
      if (Confidential.Contains(n2))  C++;
      if (Confidential.Contains(n3))  C++;
      if (Confidential.Contains(n4))  C++;
      return C;
   }
//-------------------------------------------------
inline int BullsAndCow::CalcBull(UINT n1, UINT n2, UINT n3, UINT n4)
   {
      int B=0;
      if (Confident[1] == n1)   B++;
      if (Confident[2] == n2)   B++;
      if (Confident[3] == n3)   B++;
      if (Confident[4] == n4)   B++;
      return B;
   }
//-------------------------------------------------
int BullsAndCow::VariantCount(const int &Bull, const int &Cow)
{
   switch (Bull)
   {  case 4 : switch (Cow)         {
              case 0 : return 1;
              default: return 0;       }
      case 3 : switch (Cow)         {
            case 0 : return 24;
            default: return 0;         }
      case 2 : switch (Cow)         {
            case 0 : return 180;
            case 1 : return 72;
            case 2 : return 6;
            default: return 0;         }
      case 1 : switch (Cow)         {
            case 0 : return 480;
            case 1 : return 720;
            case 2 : return 216;
            case 3 : return 8;
            default: return 0;         }
      case 0 : switch (Cow)         {
            case 0 : return 360;
            case 1 : return 1440;
            case 2 : return 1260;
            case 3 : return 264;
            case 4 : return 9;
            default: return 0;         }
      default: return 0;
   }
}
//-------------------------------------------------
inline bool __fastcall BullsAndCow::CheckParj(unsigned int num,  int pos)
{
   if (CalcCows)
      if (Confidential.Contains(num))
         if (CurrCows+1 > Cows)
            return true;
         else
            CurrCows++;
   if (CalcBulls)
      if (Confident[pos] == num)
         CurrBulls++;
   if     ( (CurrCows > Cows)||(CurrBulls > Bulls) )
      return true;
   if (CalcCows)
      if(CurrCows == Cows)  //Уже все коровы на месте
         for (int i=pos+1; i<CIP; i++) //По остальным цифрам сгенерированного
            CurrNo << Confident[i];
   if (CalcBulls)
      if(CurrBulls == Bulls)//Все быки на месте
      {
         for (int i=pos+1; i<CIP; i++)
            N[i] >> Confident[i];
      }
   return false;
}
//-------------------------------------------------
void BullsAndCow::SearchVariants(NUMB Number, int Bull, int Cow)
{
   if (Store == NULL)
      return;
   NUMBERSET QuestM;
   QuestM.Clear();
   for (int i=1; i<CIP; i++)
      QuestM << Number[i];
   Row = 0;
   int Last = -1;
   for (int idx=StoreFirst; idx < StoreCount; idx = Store[idx].Next)
   {
      if (Store[idx].CheckCorrect(Number, QuestM, Cow, Bull))
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
      }
   }
   //ShowMessage("Row="+IntToStr(Row)+"\nCount="+IntToStr(StoreCount)+"\nFirst="+IntToStr(StoreFirst));
   //Row++;
   out->InsertRow(Row, StoreCount, true);
   if (Last > -1)
      Store[Last].Next = StoreCount;
   /*Edit1->Text = "Цифр "+IntToStr(Row);
   Row++;
   for (int i=Row; i<MaxRow; i++)
      for (int j=0; j<7; j++)
         Grid->Cells[j][i] = "";
   MaxRow = Row;      */
}

//------------------------------------------------- НОРМ

AnsiString BullsAndCow::End()
{
   if ( (FStage > 0)&&(GameOver == false) )
   {

      Lose++;
      GameOver = true;
      AnsiString str;
      for (int i=1; i<CIP; i++)
         str.Insert(Confident[i],i);
      str.Insert("Я загадывал ",1);
      return str;
   }
   return "Нет игры.";
}
//-------------------------------------------------
//vRandomNumber - возвращает случайное число для игры в быки и коровы
void BullsAndCow::RandomNumber(NUMB Numb)
{
   NUMBERSET RandBox;
   RandBox.Clear();
   int i = 1;
   do
   {
      int R = rand() % 10;
      if (!RandBox.Contains(R))
      {
         Numb[i] = R;
         RandBox << R;
         i++;
      }
   } while (i < CIP);
}
//-------------------------------------------------
//SetReal - Запоминает число, загаданное компом
inline void BullsAndCow::SetReal(AnsiString NewReal, bool IndexFromOne)
{
   Confidential.Clear();
   if (IndexFromOne)
      for (int i=1; i<CIP; i++)
      {
         Confident[i] = ToInt(NewReal[i]);
         Confidential << Confident[i];
      }
   else
      for (int i=0; i<CIPHER; i++)
      {
         Confident[i] = ToInt(Confident[i+1]);
         Confidential << Confident[i];
      }
}
//-------------------------------------------------
//CalcCowAndBull - Считает кол-во быков и коров в числе 
void BullsAndCow::CalcCowAndBull(AnsiString Numb, AnsiString Real, int &Bull, int &Cow)
{
   Cow = 0; Bull = 0;
   int Max = Real.Length() >= Numb.Length() ? Numb.Length() : Real.Length();
   Max++;
   for (int i=1; i<Max; i++)
   {
      if (Real[i] == Numb[i])
         Bull++;
      for (int j=1; j<Max; j++)
         if (Real[i] == Numb[j])
         {
            Cow++;
            break;
         }
   }
   Cow -= Bull;
}
//-------------------------------------------------
//-------------------------------------------------
//CreateVariants() - отгадывание компом, создание всех возм вариантов. Устанавлив Quest
void BullsAndCow::CreateVariants(NUMB Number, int Bull, int Cow)
{
#ifdef VARIANTSMEM
   if (Store != NULL)
   {  //Первый раз - выделяем память
      delete [] Store;
   }
      StoreCount = VariantCount(Bull, Cow);
      Store = new ::Variant[StoreCount];

   //ShowMessage("Создано "+IntToStr(StoreCount));
#endif
   //Дальше 100 пудов правильно
   Cow += Bull;
   //Base - это посланное игроку число
   NUMBERSET Quester;   Quester.Clear();
   for (int i=1; i<CIP; i++)
      Quester << Number[i];
   NUMBERSET Base = Full;
   CalcCows = true; CalcBulls = true;
   Row = 0;
   CurrCows = 0; CurrBulls = 0;
   if (Cow == CIPHER)
   {
      Base.Clear();
      for (int i=1; i<CIP; i++)
         Base << Number[i];
      CalcCows = false;
   } else
   if (Cow == 0)
   {
      for (int i=1; i<CIP; i++)
         Base >> Number[i];
      CalcCows = false;
   }
   /////////////////////////
   //Цикл по первой цифре
   N[1] = Base;
   if (Bull == 0)
   {
      N[1] >> Number[1];
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
         if ( (Cow > 0)&&(Cow < CIPHER) )
         {  CalcCows = true;      }
         N[2] = Base; N[3] = Base; N[4] = Base;
         CalcBulls = true;
         if (Bull == 0)
         {   CalcBulls = false; N[2] >> Number[2]; N[3] >> Number[3]; N[4] >> Number[4]; }

      //--------------------------------------------
      NUMBERSET N2 = N[2];
      N2 >> n[1]; //да
      N2 -= CurrNo;
      if (Bull == 0)
         N2 >> Number[2];
      for (n[2]=0; n[2]<10; n[2]++)
      {
         if ( !N2.Contains(n[2]) )  continue;
         NUMBERSET N3 = N[3];
         N3 >> n[1]>>n[2];
         N3 -= CurrNo;
         if (Bull == 0)
            N3 >> Number[3];
         for (n[3]=0; n[3]<10; n[3]++)
         {
            if ( !N3.Contains(n[3]) )  continue;
            NUMBERSET N4 = N[4];
            N4 >> n[1]>>n[2]>>n[3];
            N4 -= CurrNo;
            if (Bull == 0)
               N4 >> Number[4];
            for (n[4]=0; n[4]<10; n[4]++)
            {
               if ( !N4.Contains(n[4]) )  continue;
               //if ( CheckPar(n4, 4) )  continue;
               CurrCows = 0; CurrBulls = 0;
               for (int i=1; i<CIP; i++)
               {
                  if (Quester.Contains(n[i]))
                     CurrCows++;
                  if (Number[i] == n[i])
                     CurrBulls++;
               }
               if ( (CurrCows != Cow)||(CurrBulls != Bull) )
                  continue;
               //Главный
               #ifdef VARIANTSMEM
               Store[Row].F1 = n[1];
               Store[Row].F2 = n[2];
               Store[Row].F3 = n[3];
               Store[Row].F4 = n[4];
               Store[Row].Next = Row+1;
               #endif
               Row++;
               /*for (int i=0; i<CIPHER; i++)
                  Grid->Cells[i][Row] = n[i+1];
               Grid->Cells[5][Row] = CurrCows;
               Grid->Cells[6][Row] = CurrBulls;  */
            }
         }
      }
   }
   //Edit1->Text = "Цифр "+IntToStr(Row);
   //ShowMessage("Цифр "+IntToStr(Row));
   //Row++;
   //for (int i=0; i<StoreCount; i++)
   //   out->InsertRow(Store[i].Ansi, i, true);
   //MaxRow = Row;
   //Cow -= Bull;
}
#pragma package(smart_init)

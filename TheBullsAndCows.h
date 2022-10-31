/*************************************************************\
* Игра быки и коровы : отгадывающий алгоритм                  *
\*************************************************************/
#ifndef TheBullsAndCowH
#define TheBullsAndCowH
//#include <Dialogs.hpp>
#include <ValEdit.hpp>
#include <vector>
//tabl >> "1234 3:1"
//КОНСТАНТЫ
const int CIPHER = 4;         //Количество цифр в числе. Для циклов 0123
const int CIP = CIPHER + 1;   //Используется для циклов 1234
const int PCOW = CIPHER + 2;
const int PBULL = CIPHER + 4;
const int SYMB0 = 48;   const int SYMB9 = 57;
//БАЗОВЫЕ ТИПЫ
typedef Set <short int, 0, 9> NUMBERSET;
typedef unsigned int UINT;
typedef unsigned int NUMB[CIP]; //[0]-temp
#define VARIANTSMEM

enum Difficult { bcEasy, bcHard };
//"Быки" - это те цифры вашего числа, расположение которых поразрядно совпадает с цифрами загаданного числа;
//"Коровы" - это те цифры вашего числа, которые присутствуют в загаданном числе, но находятся в другом месте, (в другом разряде, на другой позиции).
//---------------------------------------------------------------------------
//Variant - Структура всех возможных вариантов
//---------------------------------------------------------------------------
class Vars
{
   protected:
   unsigned int __fastcall GetF(int i)
   {
      switch (i)
      {
         case 1 : return F1;
         case 2 : return F2;
         case 3 : return F3;
         case 4 : return F4;
         default : return 10;
      }
   }
   void __fastcall SetF(int i, unsigned int value)
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
   AnsiString GetAnsi()
   {
      AnsiString str;
      str.Insert(F1,1);
      str.Insert(F2,2);
      str.Insert(F3,3);
      str.Insert(F4,4);
      return str;
   }
   void SetAnsi(AnsiString& rhs)
   {
      if (rhs.Length() < CIPHER)
         return;
      F1 = rhs[1];
      F2 = rhs[2];
      F3 = rhs[3];
      F4 = rhs[4];
   }

public:
   Vars() { F1=0; F2=0; F3=0; F4=0; }
   Vars(AnsiString &src) { SetAnsi(src); }
   unsigned  int F1 : 4;
   unsigned  int F2 : 4;
   unsigned  int F3 : 4;
   unsigned  int F4 : 4;
   __property unsigned int F [int i] = { read=GetF, write=SetF };
   __property AnsiString Ansi = {read = GetAnsi, write=SetAnsi};
   //__property unsigned int* const Numb = { write=SetNumb };
   void GetNumb(NUMB &numb)
   {
      numb[1] = F1;
      numb[2] = F2;
      numb[3] = F3;
      numb[4] = F4;
   }

   void SetNumb(NUMB numb)
   {
      F1 = numb[1];
      F2 = numb[2];
      F3 = numb[3];
      F4 = numb[4];
   }

   void CalcCowAndBull(const NUMBERSET &Test, int &Cow, int &Bull)
   {
      //Vari.->RCS(); //ОПЕРАТОР HELL
      Cow = 0; Bull = 0;
      if (Test.Contains(F1)) Cow++;
      if (Test.Contains(F2)) Cow++;
      if (Test.Contains(F3)) Cow++;
      if (Test.Contains(F4)) Cow++;
   }
   bool CheckCorrect(NUMB TestMas, const NUMBERSET &TestM, int Cow, int Bull)
   {
      Cow += Bull;
      if (TestM.Contains(F1)) Cow--;
      if (TestM.Contains(F2)) Cow--;
      if (TestM.Contains(F3)) Cow--;
      if (TestM.Contains(F4)) Cow--;
      if (TestMas[1] == F1)  Bull--;
      if (TestMas[2] == F2)  Bull--;
      if (TestMas[3] == F3)  Bull--;
      if (TestMas[4] == F4)  Bull--;
      if ( (Cow == 0)&&(Bull == 0) )
         return true;
      else
         return false;
   }
};

class Variant : public Vars
{
public:
   int Next : 13;
};

class Quests : public Vars
{
public:
   int Bull;
   int Sum;
   Quests() { F1=0; F2=0; F3=0; F4=0; }
   Quests(AnsiString &src, int bull, int cow)
   {
      SetAnsi(src);
      Bull = bull;
      Sum = bull + cow;
   }
   Quests(NUMB numb)
   {
      F1 = numb[1];
      F2 = numb[2];
      F3 = numb[3];
      F4 = numb[4];
      Bull = -1; Sum = -1;
   }
   Quests(NUMB &numb, int bull, int cow)
   {
      SetNumb(numb);
      Bull = bull;
      Sum = bull + cow;
   }
   void SetCowAndBull(int bull, int cow)
   {
      Bull = bull;
      Sum = bull + cow;
   }
};
//---------------------------------------------------------------------------
//Figure
//---------------------------------------------------------------------------
class Numberic
{
private:
   int FCount;
   NUMBERSET Store;
   NUMBERSET BanList[CIP];
   //NUMBERSET YesList[CIP];
   short int FReal;
   //unsigned int FNumber[CIPHER];
   void SetReal(short int AReal)
   {
      for (int i=0; i<10; i++)
         Store << i;
      Store >> AReal;
      FReal = AReal;
      FCount = 9;
   }
public:  
   Numberic()
   {
      FCount = 0;
      Store.Clear();
      Real = -1;
   }
   __property short int Real = {read=FReal, write=SetReal};
   __property int Count = {read=FCount};
   bool Add(const short int Figure)
   {
      if (Store.Contains(Figure))
         return false;
      else
      {
         Store << Figure;
         FCount++;
      }
      return true;
   }
   bool Remove(const short int Figure)
   {
      if ( !(Store.Contains(Figure)) )
         return false;
      else
      {
         Store >> Figure;
         FCount--;
      }
      return true;
   }
   void Ban(int Figure, int Position)
   {
      
   }
   bool Contain(short int num)   {      return Store.Contains(num);   }
};



//---------------------------------------------------------------------------
//BullsAndCow - Класс для игры в быки и коровы
//---------------------------------------------------------------------------
class BullsAndCow
{
private:
   //Общее
   int Count(NUMBERSET &N);
   void Push(int pos, int num);
   unsigned int Win, Lose;
   unsigned int FStage;
   void BaseStart();
   bool GameOver;
   //Игра на загадывание игроком
      int Cows, Bulls;
      //Тактика - легкий

      NUMB Quest; //Это последнее отправленное игроку число
      AnsiString AnsiQuest; //Это последнее отправленное игроку число
      AnsiString CreateQuest();          
   //Игра на отгадывание игроком
   //Игра на отгадывание и загадывание
   NUMB Confident;  //Загаданное компом число
   NUMBERSET Confidential; //Загаданное компом множество
   Difficult Diff;
   NUMBERSET No[CIP]; //Забаненные цифры, по позициям, [0] это temp. AI
   NUMBERSET NoCow, YesCow;
   NUMBERSET CurrNo, N[5], Full;
   int CurrCows, CurrBulls;
   bool CalcCows, CalcBulls;
   void Kill(int Cow);
   int AIRndFromSet(NUMBERSET &N);
   void KillerClean();
   inline bool __fastcall CheckParj(unsigned int num,  int pos);   //Проверка может ли число быть на позиции
   inline void __fastcall CyclerStart(int NUMBERSET);
   //Тактика - трудный
   ::Variant *Store;
   void CreateVariants(NUMB Number, int Bull, int Cow);
   void SearchVariants(NUMB Number, int Bull, int Cow);
   int StoreCount, StoreFirst;
   int Row;
   inline int CalcCow(  int n1,  int n2,  int n3,  int n4);
   inline int CalcBull(UINT n1, UINT n2, UINT n3, UINT n4);
   bool CompZagad, CompOtgad;
   inline bool ThrowError(AnsiString str);
public:
   __fastcall BullsAndCow();
   __fastcall ~BullsAndCow();
   //Общее
   std::vector<Quests> Vect;
   typedef void (__closure *GameOverFunction)(bool Result, int Stage); //
   GameOverFunction GameOverEvent;
   typedef void (__closure *TMessageFunction)(AnsiString Message); //
   TMessageFunction ErrorFunction;
   //Игра на загадывание игроком
   AnsiString Start(Difficult difficult); //Начать новую игру, авт поражение
   AnsiString Answer(int Cow, int Bull);
   //Игра на отгадывание игроком
   void NewGame();
   //Игра на отгадывание и загадывание
   AnsiString NewGame(Difficult difficult);
   bool Play(AnsiString &Numb, int &bull, int &cow); //на отгадывание тоже эта
   __property UINT Stage = {read=FStage};
   __property UINT Wins = {read=Win};
   __property UINT Loses = {read=Lose};
   AnsiString End();
   __property AnsiString LastWord = { read=AnsiQuest };
   //Вспомогательные
   void RandomNumber(NUMB Numb); //Возвращает случайное число для игры в быки и коровы
   unsigned int ToInt(char symb)
   {
      if ( (symb >= '0')&&(symb <= '9') )
         return symb-SYMB0;
      return symb;
   }
   int VariantCount(const int &Bull, const int &Cow);
   void CalcCowAndBull (AnsiString Numb, AnsiString Real, int &Bull, int &Cow); //Считает кол-во быков и коров
   inline void SetReal(AnsiString NewReal, bool IndexFromOne = true);   //Запоминает число, загаданное компом
   AnsiString NumbToAnsi(NUMB &numb);
   TValueListEditor *out;
};

#endif

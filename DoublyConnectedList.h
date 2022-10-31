// Copyright 2022 Larkin
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// See the License for the specific language governing permissions and
// limitations under the License.
/*************************************************************\
*   Двусвязный список с возможностью сортировки и создания коллекций                                         *
\*************************************************************/
#ifndef DoublyConnectedListH
#define DoublyConnectedListH
#define PATTN
#ifdef PATTN
 #define TEMPLT template <class T>
 #define IST <T>
#else
 #define TEMPLT
 #define IST
 #define T int
#endif
//---------------------------------------------------------------------------
#ifndef ClassesHPP   
enum TDuplicates { dupIgnore, dupAccept, dupError };
#endif

TEMPLT class DoublyConnectedList
{
private:
   int FCount;
   int Mid;
   struct Data
   {
      T Store;
      Data *next;
      Data *prev;
   }
   *Begin, *End, *Linker, *FIterator;
   TDuplicates FDuplicates;

protected:
   Data* Get(int Index);         //Получить элемент списка по индексу
   Data* CreateItem(const T& Item);
   Data* Find(const T& Item);    //Ищет элемент списка по объекту. NULL если нету.
   void Erase(Data *ExcludedItem);
   void SetCount(int NewCount)    { FCount = NewCount; Mid = FCount/2;   }
   void Concatenate(Data *parent, Data *Item);
   void Push(Data* Position, Data* Item); //Вставляет объект на мето Position, сдвигая тот и все последующие. Count++
   void SetIterator(T Value);
   inline Data* GoForvard(Data* Item, int Pos);
   inline Data* GoBack(Data* Item, int Pos);
   bool FSorted;
   void SetSorted(bool Value);
   void QuickSort(Data *pLeft, Data *pRight);

public:
   typedef bool __fastcall (*TTCLSortCompare)(const T & Item1, const T & Item2); //Параметры для сортирующей функции
   DoublyConnectedList(); //Конструктор
   __property int Count = { read=FCount, write=SetCount };
   int Add(const T& Item); //Добавляет объект в конец списка или если Sorted то в позицию. Возвращает индекс. Индекс первого - 0
   int AddVector(T* Mas, int Count);   //AddVector - добавить массив в конец. Sorted = false
   void Insert(int Index, const T& Item); //Вставляет объект на мето Index, сдвигая тот и все последующие
   T& operator[](int Index);    //Вернуть объект на позиции Index. [0..Count-1]
   //__property T Iterator = { read=GetIterator, write=SetIterator} ;
   void InitIterator();
   T& Iterator(void);
   TTCLSortCompare CompareFunction;
   __property bool Sorted = { read=FSorted, write=SetSorted } ;
   //void __fastcall Sort(TTCLSortCompare Compare);
   int IndexOf(const T& Item);   //Возвращает индекс первого появление объекта. -1 если нет
   __property TDuplicates Duplicates = {read=FDuplicates, write=FDuplicates};
   void Exchange(int Index1, int Index2); //Меняет местами элементы и устанавливает Sorted в false
   T& First(void);
	T& Last(void);
   void Delete(int Index);       //Удаляет с нуля. уменьшает countf на 1 по идее память не очищает . очистка памяти это уменьшение Capacity
   void Remove(const T& Item);   //Удаляет первую копию, возвращает индекс перред удалением, уменьшает Count
   void Clear(void);
   ~DoublyConnectedList(void)  {  Clear(); } 
};
#endif


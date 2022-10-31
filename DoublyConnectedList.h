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
*   ���������� ������ � ������������ ���������� � �������� ���������                                         *
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
   Data* Get(int Index);         //�������� ������� ������ �� �������
   Data* CreateItem(const T& Item);
   Data* Find(const T& Item);    //���� ������� ������ �� �������. NULL ���� ����.
   void Erase(Data *ExcludedItem);
   void SetCount(int NewCount)    { FCount = NewCount; Mid = FCount/2;   }
   void Concatenate(Data *parent, Data *Item);
   void Push(Data* Position, Data* Item); //��������� ������ �� ���� Position, ������� ��� � ��� �����������. Count++
   void SetIterator(T Value);
   inline Data* GoForvard(Data* Item, int Pos);
   inline Data* GoBack(Data* Item, int Pos);
   bool FSorted;
   void SetSorted(bool Value);
   void QuickSort(Data *pLeft, Data *pRight);

public:
   typedef bool __fastcall (*TTCLSortCompare)(const T & Item1, const T & Item2); //��������� ��� ����������� �������
   DoublyConnectedList(); //�����������
   __property int Count = { read=FCount, write=SetCount };
   int Add(const T& Item); //��������� ������ � ����� ������ ��� ���� Sorted �� � �������. ���������� ������. ������ ������� - 0
   int AddVector(T* Mas, int Count);   //AddVector - �������� ������ � �����. Sorted = false
   void Insert(int Index, const T& Item); //��������� ������ �� ���� Index, ������� ��� � ��� �����������
   T& operator[](int Index);    //������� ������ �� ������� Index. [0..Count-1]
   //__property T Iterator = { read=GetIterator, write=SetIterator} ;
   void InitIterator();
   T& Iterator(void);
   TTCLSortCompare CompareFunction;
   __property bool Sorted = { read=FSorted, write=SetSorted } ;
   //void __fastcall Sort(TTCLSortCompare Compare);
   int IndexOf(const T& Item);   //���������� ������ ������� ��������� �������. -1 ���� ���
   __property TDuplicates Duplicates = {read=FDuplicates, write=FDuplicates};
   void Exchange(int Index1, int Index2); //������ ������� �������� � ������������� Sorted � false
   T& First(void);
	T& Last(void);
   void Delete(int Index);       //������� � ����. ��������� countf �� 1 �� ���� ������ �� ������� . ������� ������ ��� ���������� Capacity
   void Remove(const T& Item);   //������� ������ �����, ���������� ������ ������ ���������, ��������� Count
   void Clear(void);
   ~DoublyConnectedList(void)  {  Clear(); } 
};
#endif


// Copyright 2022 Larkin.
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
* ���������� ������                                           *
\*************************************************************/
#include <_null.h>
//#include <stdio.h>
//#include <system.hpp>
//#include <Dialogs.hpp>     //��� ShowMessage
//#include <dstring.h>
//#include <Classes.hpp>  //��� �����������
//#include <conio.h>  //*/
#pragma hdrstop       
#include "DoublyConnectedList.h"

//---------------------------------------------------------------------------
//�����������
TEMPLT DoublyConnectedList IST::DoublyConnectedList()
{
   FCount = 0;
   Mid = 0;
   Begin = NULL;
   End = NULL;
   FSorted = false;
   FDuplicates = dupAccept;
   CompareFunction = NULL;
   FIterator = NULL;
   //SortAccordingIncrease = true;
}
//---------------------------------------------------------------------------
//Get - �������� ������ �� �������
TEMPLT DoublyConnectedList IST::Data* DoublyConnectedList IST::Get(int Index)
{
   if (Index < 0)
      Index = 0;
   else if (Index >= FCount)
      Index = FCount-1;
   if ( Index > Mid )
   {  //C �����
      Linker = End;
      for (int i=FCount-1; i>Index; i--)
         Linker = Linker->prev;
   }
   else
   {  //C ������
      Linker = Begin;
      for (int i=0; i<Index; i++)
         Linker = Linker->next;
   }
   return Linker;
}
//---------------------------------------------------------------------------
//Find - ���� ������� ������ �� �������. NULL ���� ����.
TEMPLT DoublyConnectedList IST::Data* DoublyConnectedList IST::Find(const T& Item)
{
   for (Linker = Begin; Linker != NULL; Linker=Linker->next)
      if (&Linker->Store == &Item)
         return Linker;
   return NULL;
}
//---------------------------------------------------------------------------
//Push - //��������� ������� ����� Position, ������� ��� � ��� �����������. Count++
TEMPLT void DoublyConnectedList IST::Push(Data* Position, Data* Item)
{
   //������� ������� � ������
   if (Position == Begin) //��� ��������� ����� begin=NULL � Pos=NULL
   {  //� ������
      Item->next = Begin;
      Item->prev = NULL;
      if (Begin != NULL)
         Begin->prev = Item;
      Begin = Item;
      if (End == NULL)
         End = Item;
   }
   else if (Position == NULL)
   {   //� ����� ����� ����� ����������
      Item->next = NULL;
      Item->prev = End;
      if (Begin == NULL)
         Begin = Item;
      else
         End->next = Item;
      End = Item;
   }
   else
   {  //��������� ������� ����� Position
      Item->next = Position;
      Item->prev = Position->prev;
      Position->prev->next = Item;
      Position->prev = Item;
   }
}
//---------------------------------------------------------------------------
//CreateItem - ������� ������� ������
TEMPLT inline DoublyConnectedList IST::Data* DoublyConnectedList IST::CreateItem(const T& Item)
{
   Data *NewItem = new Data;
   NewItem->Store = Item;
   FCount++;
   Mid = FCount / 2;
   return NewItem;
}
//---------------------------------------------------------------------------
//Add - ��������  ��� ����������� �� ���������
TEMPLT int DoublyConnectedList IST::Add(const T& Item)
{
   if (FDuplicates == dupIgnore)
      if (Find(Item) != NULL)
         return -1;
   Data *NewItem = CreateItem(Item);
   int pos = 0;
   if (Sorted)
      for (Linker = Begin; Linker != NULL; Linker=Linker->next , pos++)
         //if (Item < Linker->Store)
         if (CompareFunction(Item, Linker->Store))
         { //�������� ����� ��������
            Push(Linker, NewItem);
            return pos;
         }
   Push(NULL, NewItem); //������� � �����
   return FCount-1;
}
//---------------------------------------------------------------------------
//AddVector - �������� ������
TEMPLT int DoublyConnectedList IST::AddVector(T* Mas, int count)
{
   if (FDuplicates == dupIgnore)
   {
      for (int i=0; i<count; i++)
         if (Find(Mas[i]) != NULL)
         {
            T temp = Mas[i];
            count--;
            Mas[i] = Mas[count];
            Mas[count] = temp;
            i--;
            continue;
         }
      if (count == 0)
         return -1;
   }
   Data **NewMas = new Data*[count];
   for (int i=0; i<count; i++)
   {
      NewMas[i] = new Data;
      NewMas[i]->Store = Mas[i];
      if (i != 0)
      {
         NewMas[i]->prev = NewMas[i-1];
         NewMas[i-1]->next = NewMas[i];
      }    
   }
   NewMas[0]->prev = End;
   if (End != NULL)
      End->next = NewMas[0];
   if (Begin == NULL)
      Begin = NewMas[0];
   NewMas[count-1]->next = NULL;
   End = NewMas[count-1];
   FCount += count;
   Mid = FCount / 2;
   Sorted = false;
   return FCount-count;
}
//---------------------------------------------------------------------------
//������� ������ �� ������� Index. [0..Count-1]
TEMPLT inline T& DoublyConnectedList IST::operator[](int Index)
//template <class T> T& DoublyConnectedList<T>::operator[](int Index)
{
   return Get(Index)->Store;
}
//---------------------------------------------------------------------------
//IndexOf - ���������� ������ ������� ��������� �������
TEMPLT int DoublyConnectedList IST::IndexOf(const T& Item)
{
   int Idx = 0;
   for (Linker = Begin; Linker != NULL; Linker=Linker->next , Idx++)
      if (Linker->Store == Item)
         return Idx;
   return -1;
}
//---------------------------------------------------------------------------
//Insert - //��������� ������ �� ���� Index, ������� ��� � ��� �����������
TEMPLT void DoublyConnectedList IST::Insert(int Index, const T& Item)
{
   Push(Get(Index), CreateItem(Item));
   Sorted = false;
}
//---------------------------------------------------------------------------
//Serted = Value : SetSorted
TEMPLT void DoublyConnectedList IST::SetSorted(bool Value)
{
   if (Value)
   {
      if (CompareFunction == NULL)
      {
         FSorted = false;
         return;
      }
      if (FCount > 1)
      {
         QuickSort(Begin, End);
         Begin = GoBack(Begin, FCount);
      }
   }
   FSorted = Value;
}
/*/---------------------------------------------------------------------------
TEMPLT bool DoublyConnectedList IST::GetSorted(void)
{
   return FSorted;
}
//--------------------------------------------------------------------------- */
/*/������� ����������
TEMPLT bool DoublyConnectedList IST::SortCompare(const T & Item1, const T & Item2)
{
   if (CompareFunction == NULL)
      if (SortAccordingIncrease)
         return (Item1 < Item2);
      else
         return (Item1 > Item2);
   return CompareFunction(Item1, Item2);
}       */

TEMPLT void DoublyConnectedList IST::QuickSort(Data *pLeft, Data *pRight)
{
   if (CompareFunction == NULL)
      return;
	Data *pStart;
	Data *pCurrent;
	T nCopyInteger;
	// ���������� �������� - �����
	if (pLeft == pRight) return;
	// ��������� ���� ������� ���������� - Start � Current
	pStart = pLeft;
	pCurrent = pStart->next;
	// �������� �� ������ ����� �������
	while (1)
	{
		//if (pStart->Store < pCurrent->Store)
      if (CompareFunction(pStart->Store, pCurrent->Store))
		{
			nCopyInteger = pCurrent->Store;
			pCurrent->Store = pStart->Store;
			pStart->Store = nCopyInteger;
		}	
		
		if (pCurrent == pRight) break;
		pCurrent = pCurrent->next;
	}
	// ������������ First � Current - �������� �������� � ������ ����� ������
   //ShowMessage(IntToStr(pLeft->Store) + " � "+IntToStr(pCurrent->Store));
	nCopyInteger = pLeft->Store;
	pLeft->Store = pCurrent->Store;
	pCurrent->Store = nCopyInteger;
	// ���������� Current
	Data *pOldCurrent = pCurrent;
	// ��������
	pCurrent = pCurrent->prev;
	if (pCurrent != NULL)
	{
		if ((pLeft->prev != pCurrent) && (pCurrent->next != pLeft))
			QuickSort(pLeft, pCurrent);
	}
	pCurrent = pOldCurrent;
	pCurrent = pCurrent->next;
	if (pCurrent != NULL)
	{
		if ((pCurrent->prev != pRight) && (pRight->next != pCurrent))
			QuickSort(pCurrent, pRight);
	}
}
//---------------------------------------------------------------------------
//Clear - ������� ��
TEMPLT void DoublyConnectedList IST::Clear(void)
{
   Data *DelItem, *Item = Begin;
	while (Item != NULL)
	{
		DelItem = Item;
		Item = Item->next;
		delete DelItem;
	}
	Begin = NULL; End = NULL;
   FCount = 0;   Mid = 0;
}
//---------------------------------------------------------------------------
//�oncatenate - ��������� ��� �������� //REMARKABLE!
TEMPLT void DoublyConnectedList IST::Concatenate(Data *parent, Data *Item)
{
   if (parent != NULL)
       parent->next = Item;
   if (Item != NULL)
       Item->prev = parent;
}
//---------------------------------------------------------------------------
//Erase - ������� ������� ������
TEMPLT void DoublyConnectedList IST::Erase(Data *ExcludedItem)
{
   if (ExcludedItem == NULL)
      return;
   if (ExcludedItem == Begin)
      Begin = Begin->next;
   if (ExcludedItem == End)
      End = End->prev;
   Concatenate(ExcludedItem->prev, ExcludedItem->next);
   delete ExcludedItem;
   Count--;
}
//---------------------------------------------------------------------------
//Delete
TEMPLT void DoublyConnectedList IST::Delete(int Index)
{
   if ( FCount == 0 )
      return;
   if ( FCount == 1 )
   {
      Clear();
      return;
   }   
   Erase(Get(Index));
}
//---------------------------------------------------------------------------
//Remove - ������� ������ �����, ���������� ������ ������ ���������, ��������� Count
TEMPLT void DoublyConnectedList IST::Remove(const T& Item)
{
   Erase(Find(Item));
}
//---------------------------------------------------------------------------
//GetIterator -
TEMPLT void DoublyConnectedList IST::InitIterator()
{

}
TEMPLT T &DoublyConnectedList IST::Iterator(void)
{
   if (FIterator == NULL)
   {
      DoublyConnectedList::Data h;
      return h.Store;
   }
   T &Curr = FIterator->Store;
   FIterator = FIterator->next;
   return Curr;
}  
//---------------------------------------------------------------------------
//SetIterator - ���������� � NULL ����� ������
TEMPLT void DoublyConnectedList IST::SetIterator(T Value)
{
   if (Value == NULL)
      FIterator = Begin;
   else
      FIterator = Find(Value);
}
//---------------------------------------------------------------------------
//Exchange - �������� ������� ��������
TEMPLT void DoublyConnectedList IST::Exchange(int Index1, int Index2)
{
   if (Index1 == Index2)
      return;
   if ((Index1 >= FCount) || (Index2 >= FCount))
      return;
   Data *A = Get(Index1);
   Data *B = Get(Index2);
   T One = A->Store;
   A->Store = B->Store;
   B->Store = One;
   Sorted = false;
}
//---------------------------------------------------------------------------
//First - ��������� �� ������
TEMPLT T& DoublyConnectedList IST::First(void)
{
   return operator[](0);
}
//---------------------------------------------------------------------------
//First - ��������� �� ���������
TEMPLT T& DoublyConnectedList IST::Last(void)
{
   return operator[](FCount-1);
}
//---------------------------------------------------------------------------
//GoForvard - ������� ��������� ������
TEMPLT inline DoublyConnectedList IST::Data* DoublyConnectedList IST::GoForvard(Data* Item, int Pos)
{
   Data *Link = Item;
   for (int i=0 ; i<Pos; i++)
      if (Link->next != NULL)
         Link = Link->next;
      else
         break;
   return Link;
}
//---------------------------------------------------------------------------
//GoBack - ������� ��������� �����
TEMPLT inline DoublyConnectedList IST::Data* DoublyConnectedList IST::GoBack(Data* Item, int Pos)
{
   Data *Link = Item;
   for (int i=0 ; i<Pos; i++)
      if (Link->prev != NULL)
         Link = Link->prev;
      else
         break;
   return Link;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#pragma package(smart_init)

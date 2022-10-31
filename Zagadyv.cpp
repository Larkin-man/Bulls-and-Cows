//---------------------------------------------------------------------------
#include <vector>
#include <vcl.h>
#pragma hdrstop

#include "Zagadyv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	file = new TStringList;
	file->LoadFromFile("Data\\BASE.txt");
	Out->Lines->Add("Слов в базе: "+IntToStr(file->Count));
	srand(time(NULL));
	for (int i = file->Count-1; i > 0; --i)
		file->Exchange(i, rand()%(i+1)); //лучайнамаперетасофка
	WC = file->Count;
	Words = new RusSet[WC];
	for (int i = 0; i < WC; ++i)
		for (int b = 1; b <= LEN; ++b)
			Words[i] << file->Strings[i][b];
	Strong->Max = WC-1;
	//Тест
	Word = "йцуке";
	Out->Lines->Add(file->Strings[0]);
	if (Words[0].Contains(Word[1]))		Out->Lines->Add(Word[1]);
	if (Words[0].Contains(Word[2]))		Out->Lines->Add(Word[2]);
	if (Words[0].Contains(Word[3]))		Out->Lines->Add(Word[3]);
	if (Words[0].Contains(Word[4]))		Out->Lines->Add(Word[4]);
	if (Words[0].Contains(Word[5]))		Out->Lines->Add(Word[5]);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	delete file;
	delete Words;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Word = file->Strings[rand()%file->Count];
	Out->Clear();
	Pos = 0;
	/*Buk.Clear();    	
	for (int i = 1; i < LEN1; ++i)
	{
		Buk << (wchar_t)Word[i];
		if (Buk.Contains(Word[i]))
			Out->Lines->Add(Word[i]);
	}
	if (Buk.Empty())
		Out->Lines->Add("empty");
	else
		Out->Lines->Add(Buk.ToInt());  */
	In->Text = file->Strings[Pos];
	Answers.clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::InKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN)
	{
		UnicodeString Curr = In->Text;
		int Cow=0, Bull=0;
		for (int i = 1; i < LEN1; ++i)
		{
			if (Curr[i] == Word[i])
				Bull++;
			for (int j = 1; j < LEN1; ++j)
				if (Curr[i] == Word[j])
					Cow++;
		}
		Cow -= Bull;
		Out->Lines->Add(Curr + " "+IntToStr(Bull)+":"+IntToStr(Cow));
		HisTable->InsertRow(Curr, IntToStr(Bull)+":"+IntToStr(Cow), true );
		ANSWERS A;
		for (int i = 1; i < LEN1; ++i)
      {
			A.Word[i-1] = Curr[i];
			A.M << Curr[i];
		}
		A.Bull = Bull;
		A.CowiBull = Cow + Bull;
		Answers.push_back(A);
	}
	if (Key == VK_END)
	{
		Out->Lines->Add(Word);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	//int Rand = rand() % WC;
	//int Curr = Rand;
	int Stop = Pos + Strong->Position;
	if (Stop > WC)
		Stop = WC;
	for (; Pos < Stop; ++Pos)
   {
		if (CheckCorrect(Pos))
		{
			Out->Lines->Add("true");
			break;
		}
		else
		{
			Out->Lines->Add("false");
			//Curr = Words[Curr].Next;
      }
	}
	//HisTable->InsertRow(file->Strings[Curr], Curr, true );
	Out->Lines->Add(IntToStr(Pos)+file->Strings[Pos]);

}
//---------------------------------------------------------------------------
//Проверяет коррекнтонсть всех слов и помечает next
bool TForm1::CheckCorrect(int Str)
{
	Out->Lines->Add("Check "+IntToStr(Str)+file->Strings[Str]);
	int Cow, Bull;
	wchar_t WordI[LEN];
	for (int i = 1; i < LEN1; ++i)
		WordI[i-1] = file->Strings[Str][i];
   CorrMaxIdx = -1;
	for (std::vector<ANSWERS>::iterator el = Answers.begin(); el != Answers.end(); ++el)
	{
		Bull = el->Bull;
		Cow = el->CowiBull;
		//Out->Lines->Add(file->Strings[Str]+IntToStr(Bull)+IntToStr(Cow));
		if (el->M.Contains(WordI[0])) Cow--;
		if (el->M.Contains(WordI[1])) Cow--;
		if (el->M.Contains(WordI[2])) Cow--;
		if (el->M.Contains(WordI[3])) Cow--;
		if (el->M.Contains(WordI[4])) Cow--;
		if (WordI[0] == el->Word[0])  Bull--;
		if (WordI[1] == el->Word[1])  Bull--;
		if (WordI[2] == el->Word[2])  Bull--;
		if (WordI[3] == el->Word[3])  Bull--;
		if (WordI[4] == el->Word[4])  Bull--;
		Out->Lines->Add(el->Word+IntToStr(Bull)+IntToStr(Cow));
      if ( (Cow == 0)&&(Bull == 0) )
			continue;
		else
			return false;
	}
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::AnswwrBtnClick(TObject *Sender)
{
	//Сохранение ответа игрока на его слово
	Out->Lines->Add(ANSW->Text);
	int Bull = StrToInt(ANSW->Text[1]);
	int Cow =  StrToInt(ANSW->Text[3]);
	HisTable->InsertRow(In->Text, IntToStr(Bull)+":"+IntToStr(Cow), true );
	ANSWERS A;
	for (int i = 1; i < LEN1; ++i)
	{
		A.Word[i-1] = In->Text[i];
		A.M << In->Text[i];
	}
	A.Bull = Bull;
	A.CowiBull = Cow + Bull;
	Answers.push_back(A);
	//Просчет
	Pos++;
	if (Pos >= WC)
	{
		Out->Lines->Add("ОЙ ВСЁ");
		return;
	}
	int Stop = Pos + Strong->Position;
	if (Stop > WC)
		Stop = WC;
	for (; Pos < Stop; ++Pos)
	{
		Out->Lines->Add(file->Strings[Pos]+IntToStr(Pos));
		for (std::vector<ANSWERS>::iterator el = Answers.begin(); el != Answers.end(); ++el)
		{
			Bull = el->Bull;
         if (file->Strings[Pos][1] == el->Word[0])  Bull--;
			if (file->Strings[Pos][2] == el->Word[1])  Bull--;
			if (file->Strings[Pos][3] == el->Word[2])  Bull--;
			if (file->Strings[Pos][4] == el->Word[3])  Bull--;
			if (file->Strings[Pos][5] == el->Word[4])  Bull--;
			if (Bull != 0)
				break;
			Cow = el->CowiBull;
			if (el->M.Contains(file->Strings[Pos][1])) Cow--;
			if (el->M.Contains(file->Strings[Pos][2])) Cow--;
			if (el->M.Contains(file->Strings[Pos][3])) Cow--;
			if (el->M.Contains(file->Strings[Pos][4])) Cow--;
			if (el->M.Contains(file->Strings[Pos][5])) Cow--;
			if (Cow != 0)
				break;
			//Out->Lines->Add(el->Word+IntToStr(Bull)+IntToStr(Cow));
		}
		if ( (Cow == 0)&&(Bull == 0) )
			break;
	}
   if (Pos >= WC)
	{
		Out->Lines->Add("СДАЮСЬ");
		return;
	}
	In->Text = file->Strings[Pos];

}
//---------------------------------------------------------------------------


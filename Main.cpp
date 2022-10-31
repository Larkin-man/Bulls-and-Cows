//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
   : TForm(Owner)
{
   YourTable->RowHeights[0] = 24;
   HisTable->RowHeights[0] = 24;
   //BC.ErrorFunction = &TMainForm::ErrorFunction;
   BC.ErrorFunction = ErrorFunction;
   BC.GameOverEvent = GameOverFunction;
   CompZagad = false;
   CompOtgad = false;
   Ten[0].Window = F0;
   Ten[1].Window = F1;
   Ten[2].Window = F2;
   Ten[3].Window = F3;
   Ten[4].Window = F4;
   Ten[5].Window = F5;
   Ten[6].Window = F6;
   Ten[7].Window = F7;
   Ten[8].Window = F8;
   Ten[9].Window = F9;
   YourTable->Height = 234;
   HisTable->Height = 234;
   Vars del;
   //Variant del2;
   Edit1->Text = sizeof (del);
   AnsiString str = "7654";
   Vars ti(str);
   ti.F1 = 8;
   Edit1->Text = ti.Ansi;
   BC.out = HisTable;

}
//---------------------------------------------------------------------------
void TMainForm::BaseStart()
{
   for (int i=1; i<YourTable->RowCount; i++)
   {
      YourTable->Cells[0][i] = "";
      YourTable->Cells[1][i] = "";
   }
   for (int i=1; i<HisTable->RowCount; i++)
   {
      HisTable->Cells[0][i] = "";
      HisTable->Cells[1][i] = "";
   }   
   LLoses->Caption = "Loses: "+IntToStr(BC.Loses);
   for (int i=0; i<10; i++)
      Ten[i].SetStatus(None);
   LStage->Caption = "Ходов: 0";

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StartRazgBtnClick(TObject *Sender)
{
   Edit1->Text = "Игра на разгадывание игроком.";
   BC.NewGame();
   CompZagad = true;
   CompOtgad = false;
   His->Text = "0000";
   MaskBC->Text = "0:0";
   BaseStart();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GoClick(TObject *Sender)
{
   //ShowMessage(MaskEdit1->Text);
   int B = MaskBC->Text[1] - 48;
   int C = MaskBC->Text[3] - 48;
   if (CompOtgad)
   {
      HisTable->InsertRow(Numb, MaskBC->Text, true );
   }
   Numb = You->Text;
   //Edit1->Text = BC.Answer(C, B);
   if (BC.Play(Numb, B, C))
      return;
   if (CompZagad)
   {
      YourTable->InsertRow(You->Text, IntToStr(B)+":"+IntToStr(C), true );
   }
   if (CompOtgad)
   {
      //HisTable->InsertRow(Numb, MaskBC->Text, true );
      His->Text = Numb;
      BC.CalcCowAndBull(His->Text, Secret->Text, B, C);
      MaskBC->Text = IntToStr(B)+":"+IntToStr(C);
   }   
   LStage->Caption = "Ходов: "+IntToStr(BC.Stage);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CalcCBClick(TObject *Sender)
{
   int c,b;
   BC.CalcCowAndBull(Edit1->Text, His->Text, c,b);
   MaskBC->Text = IntToStr(c)+":"+IntToStr(b);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::SetRealClick(TObject *Sender)
{
   BC.SetReal(His->Text, true);
}
//---------------------------------------------------------------------------
void TMainForm::GameOverFunction(bool Result, int Stage)
{
   if (Result)
      ShowMessage("Вы отгадали число за "+IntToStr(Stage)+" ходов!");
   else
      ShowMessage("Компьютер отгадал число за "+IntToStr(Stage)+" попыток.");
   LWins->Caption = "Wins: "+IntToStr(BC.Wins);
   LLoses->Caption = "Loses: "+IntToStr(BC.Loses);
}

//   GameOverFunction GameOver;
void TMainForm::ErrorFunction(AnsiString Message)
{
   Application->MessageBox(Message.c_str(), "Ошибка", MB_ICONSTOP);
}
void __fastcall TMainForm::StartZagBtnClick(TObject *Sender)
{
   CompZagad = false;
   CompOtgad = true;
   Edit1->Text = "Игра на загадывание игроком.";
   BaseStart();
   if (Style->ItemIndex == 0)
      Numb = BC.Start(bcEasy);
   else
      Numb = BC.Start(bcHard);
   His->Text = Numb;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StartpvpBTNClick(TObject *Sender)
{
   Edit1->Text = "Игра против компа.";
   CompZagad = true;
   CompOtgad = true;
   BaseStart();
   if (Style->ItemIndex == 0)
      His->Text = BC.Start(bcEasy);
   else
      His->Text = BC.Start(bcHard);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FigureLClick(TObject *Sender)
{
   TStaticText *Fig = ((TStaticText*)Sender);
   for (int i=0; i<10; i++)
   {
      if (Ten[i].Window == Fig)
      {
         Ten[i].StatusUp();
         break;
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::F1ContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
   TStaticText *Fig = ((TStaticText*)Sender);
   for (int i=0; i<10; i++)
   {
      if (Ten[i].Window == Fig)
      {
         Ten[i].StatusDown();
         break;
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HiredClick(TObject *Sender)
{
   Edit1->Text = BC.End();
   LLoses->Caption = "Loses: "+IntToStr(BC.Loses);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Button1Click(TObject *Sender)
{
   int S = BC.Vect.size();
   for (int i=0; i<S; ++i)
   {
      HisTable->InsertRow(BC.Vect[i].Ansi, BC.Vect[i].Sum, true );
   }

}
//---------------------------------------------------------------------------



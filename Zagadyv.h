//---------------------------------------------------------------------------

#ifndef ZagadyvH
#define ZagadyvH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <time.h>
#include <stdlib.h>
#include <Mask.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
int const LEN = 5;
int const LEN1 = LEN + 1;
typedef Set <wchar_t, L'à', L'ÿ'> RusSet;
typedef struct BASEWORD
{
	String* Word;
	RusSet Set;
} BCWORD;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TMemo *Out;
	TMaskEdit *In;
	TButton *Button2;
	TValueListEditor *HisTable;
	TImageList *ImageList1;
	TScrollBar *Strong;
	TMaskEdit *ANSW;
	TButton *AnswwrBtn;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall InKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall AnswwrBtnClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	TStringList *file;
	UnicodeString Word;
	//Set<wchar_t,L'à',L'ÿ'>Buk;
	//Set<wchar_t,-127,127>Buk;
	RusSet *Words;
	int WC;
	int Pos;
	int CorrMaxIdx;
	//UnicodeString &Str(int i) { return (file->Strings[i]); }
	bool CheckCorrect(int Str);
	int ToInt(wchar_t symb)
	{
		if ( (symb >= L'0')&&(symb <= L'9') )
         return symb-L'0';
      return symb;
	}
	struct ANSWERS
	{
		wchar_t Word[LEN];
		RusSet M;
		int Bull;
		int CowiBull;
	} ;
	std::vector <ANSWERS> Answers;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

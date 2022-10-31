//---------------------------------------------------------------------------

#ifndef WordsCowsH
#define WordsCowsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
enum TStatus { None = 0, Yes = 1, No = -1 };
class TStaticLetter
{
private:
   TStatus Status;
protected:

public:
   __fastcall TStaticLetter()
   {
      Status = None;
      Window = NULL;
   }
   __fastcall ~TStaticLetter()
   {
   }
   TStaticText *Window;

} Alphabet[33];

class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TStaticText *StaticText1;
   TMemo *Memo1;
   TStaticText *StaticText2;
   void __fastcall StaticText1Click(TObject *Sender);
   void __fastcall StaticText1ContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
private:	// User declarations
public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

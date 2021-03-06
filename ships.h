//---------------------------------------------------------------------------

#ifndef SeaBattleH
#define SeaBattleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TStringGrid *StringGrid1;
        TStringGrid *StringGrid2;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TTimer *Timer1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall StartGame(void);
        void __fastcall ManualPlacing(TObject * Sender, int ACol, int ARow);
        void __fastcall SelectGrid1(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
        void __fastcall Draw1(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall RandomPlace();
        void __fastcall Doom();
        void __fastcall Imshooting(TObject * Sender, int ACol, int ARow);
        void __fastcall Draw2(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
        void __fastcall SelectGrid2(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
        void __fastcall  CompShoots();
        void __fastcall CheckWin();
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall StartGame2();




private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
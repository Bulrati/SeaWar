//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <dos.h>

#include "SeaBattle.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

bool firstpoint;

int popal1=0,popal2=0;

bool pcopponent;

bool disposition = FALSE;

int currentship = 1;

int compmoove = 0;

int lastrow, lastcol;

int leftField[10][10], rightField[10][10];

int leftVisible[10][10], rightVisible[10][10];

int ships[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

int shipsize;

bool ranil=FALSE;

int saveco,savero,gdechetvertiy=0;

bool leftshoots = TRUE;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
      //раставить корабли
void __fastcall TForm1::Button1Click(TObject *Sender)
{
disposition = TRUE;
RadioButton1->Visible=TRUE;
RadioButton2->Visible=TRUE;
Button1->Visible=FALSE;
Button2->Visible=TRUE;
Button3->Visible=TRUE;
StringGrid1->Enabled=TRUE;

// нарисуем координаты
 char c;
for (int i = 1; i <= 10; i++) {

    StringGrid1->Cells[i][0] = i;

    StringGrid2->Cells[i][0] = i;

    c = i + 96;

    StringGrid1->Cells[0][i] = c;

    StringGrid2->Cells[0][i] = c;


                /*
    srand(time(0));
    for (int i=1;i<StringGrid1->ColCount;i++)
    for (int j=1;j<StringGrid1->RowCount;j++)
        {
        int a=rand()%26;
        StringGrid1->Cells[i][j] = a;
        }              */

}
for (int i=0;i<10;i++)
{for(int j=0;j<10;j++)
{
leftField[i][j]=0;
rightField[i][j]=0;
}
}
//StartGame();
}
//---------------------------------------------------------------------------


 void __fastcall TForm1::StartGame(void)
{
for (int i=0;i<10;i++)
{for(int j=0;j<10;j++)
{
      if (StringGrid1->Enabled==FALSE)
      {
       if ( leftField[i][j]==12)
         {
                StringGrid1->Cells[j+1][i+1]=' ';
         }
      }
   if (StringGrid2->Enabled==FALSE)
      {
 if ( rightField[i][j]==12)
 {
StringGrid2->Cells[j+1][i+1]=' ';
  }
  }
}
}
 StringGrid2->Refresh();
 StringGrid1->Refresh();       //TODO: Add your source code here
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SelectGrid1(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
 if(disposition == TRUE)
 {
        ManualPlacing(Sender, ACol, ARow);
 }
 if (leftshoots == FALSE)
 {
 Imshooting(Sender,ACol,ARow);
 }
 StringGrid1->Refresh();
}
//---------------------------------------------------------------------------
  void __fastcall TForm1::ManualPlacing(TObject * Sender, int ACol, int ARow)
{
     TStringGrid* currentGrid = (TStringGrid*)Sender;

int (*playerField)[10];

if (((TStringGrid*)Sender)->Name == "StringGrid1") {

    playerField = leftField;

} else if (((TStringGrid*)Sender)->Name == "StringGrid2") {

    playerField = rightField;

}

  shipsize = ships[currentship - 1];

int direction = -1; // всего четыре направления

int currentrow, currentcol;

int i;

    // продолжаем расставлять корабли только в том случае, если есть ещё

    if (currentship <= 10) {

         //Application->MessageBox("Vxod!","Жеребьевка",MB_OK);
        // расставляем кораблики
        if(firstpoint==TRUE)
                {
                 //Application->MessageBox("firstpoint==TRUE!","Жеребьевка",MB_OK);
                }
                if(firstpoint==FALSE)
                {
                //Application->MessageBox("firspoint==FALSE!","Жеребьевка",MB_OK);
                }

       /* if ((firstpoint == FALSE || shipsize == 1)) {
             Application->MessageBox("if1!","Жеребьевка",MB_OK);
        if((playerField[ARow-1][ACol-1] == 0)&&(playerField[ARow-1-1][ACol+1-1] == 0)&&(playerField[ARow-1-1][ACol-1] == 0)&&(playerField[ARow-1-1][ACol-1-1] ==0)&&(playerField[ARow-1][ACol-1-1] ==0)&&(playerField[ARow+1-1][ACol-1-1] ==0)&&(playerField[ARow+1-1][ACol-1] ==0)&&(playerField[ARow+1-1][ACol+1-1] ==0)&&(playerField[ARow-1][ACol+1-1] ==0)) { //значит это будет первая точка
         */
         if ((firstpoint == FALSE || shipsize == 1)&&(currentGrid->Cells[ACol][ARow] != 12)&&(currentGrid->Cells[ACol+1][ARow-1] != 12)&&(currentGrid->Cells[ACol][ARow-1] != 12)&&(currentGrid->Cells[ACol-1][ARow-1] != 12)&&(currentGrid->Cells[ACol-1][ARow] != 12)&&(currentGrid->Cells[ACol-1][ARow+1] != 12)&&(currentGrid->Cells[ACol][ARow+1] != 12)&&(currentGrid->Cells[ACol+1][ARow+1] != 12)&&(currentGrid->Cells[ACol+1][ARow] != 12)) {

            playerField[ARow - 1][ACol - 1] = 12;//Application->MessageBox("fp111!","Жеребьевка",MB_OK);

            currentGrid->Cells[ACol][ARow] = playerField[ARow - 1][ACol - 1];

            lastrow = ARow;

            lastcol = ACol;

            if (shipsize == 1)

                currentship++;

            else if ( shipsize != 1)

            {//Application->MessageBox("fp!","Жеребьевка",MB_OK);
                firstpoint = TRUE;}

            currentGrid->Refresh();


        } else if (firstpoint==TRUE) { // тогда ставим хвост корабля

            // определим конкретное на-правление

            if (ARow - lastrow == shipsize-1 && lastcol == ACol) // вверх

               { direction = 0;//Application->MessageBox("verx!","Жеребьевка",MB_OK);
               }

            else if (lastrow - ARow == shipsize-1 && lastcol == ACol) // вниз

                {direction = 1;//Application->MessageBox("vniz!","Жеребьевка",MB_OK);
                }

            else if (lastcol - ACol == shipsize-1 && lastrow == ARow) // вправо

                {direction = 2; //Application->MessageBox("vpravo!","Жеребьевка",MB_OK);
                }

            else if (ACol - lastcol == shipsize-1 && lastrow == ARow) // влево

               { direction = 3; //Application->MessageBox("vlevo!","Жеребьевка",MB_OK);
               }

            // если направление удовлетво-ряет

           // if (((direction == 0)&&(playerField[ARow-1][ACol-1] != 12)&&(playerField[ARow-1-1][ACol+1-1] != 12)/*&&(StringGrid1->Cells[ACol][ARow-1] != 12)*/&&(playerField[ARow-1-1][ACol-1-1] != 12)&&(playerField[ARow-1][ACol-1-1] != 12)&&(playerField[ARow+1-1][ACol-1-1] != 12)&&(playerField[ARow+1-1][ACol-1] != 12)&&(playerField[ARow+1-1][ACol+1-1] != 12)&&(playerField[ARow-1][ACol+1-1] != 12))||((direction == 1)&&(playerField[ARow-1][ACol-1] != 12)&&(playerField[ARow-1-1][ACol+1-1] != 12)&&(playerField[ARow-1-1][ACol-1] != 12)&&(playerField[ARow-1-1][ACol-1-1] != 12)&&(playerField[ARow-1][ACol-1-1] != 12)&&(playerField[ARow+1-1][ACol-1-1] != 12)/*&&(StringGrid1->Cells[ACol][ARow+1] != 12)*/&&(playerField[ARow+1-1][ACol+1-1] != 12)&&(playerField[ARow-1][ACol+1-1] != 12))||
//((direction == 2)&&(playerField[ARow-1][ACol-1] != 12)&&(playerField[ARow-1-1][ACol+1-1] != 12)&&(playerField[ARow-1-1][ACol-1] != 12)&&(playerField[ARow-1-1][ACol-1-1] != 12)&&(playerField[ARow-1][ACol-1-1] != 12)&&(playerField[ARow+1-1][ACol-1-1] != 12)&&(playerField[ARow+1-1][ACol-1] != 12)&&(playerField[ARow+1-1][ACol+1-1] != 12)/*&&(StringGrid1->Cells[ACol+1][ARow] != 12)*/)||((direction == 3)&&(playerField[ARow-1][ACol-1] != 12)&&(playerField[ARow-1-1][ACol+1-1] != 12)&&(playerField[ARow-1-1][ACol-1] != 12)&&(playerField[ARow-1-1][ACol-1-1] != 12)/*&&(StringGrid1->Cells[ACol-1][ARow] != 12)*/&&(playerField[ARow+1-1][ACol-1-1] != 12)&&(playerField[ARow+1-1][ACol-1] != 12)&&(playerField[ARow+1-1][ACol+1-1] != 12)&&(playerField[ARow-1][ACol+1-1] != 12))) {


          if (((direction == 0)&&(currentGrid->Cells[ACol][ARow] != 12)&&(currentGrid->Cells[ACol+1][ARow-1] != 12)/*&&(StringGrid1->Cells[ACol][ARow-1] != 12)*/&&(currentGrid->Cells[ACol-1][ARow-1] != 12)&&(currentGrid->Cells[ACol-1][ARow] != 12)&&(currentGrid->Cells[ACol-1][ARow+1] != 12)&&(currentGrid->Cells[ACol][ARow+1] != 12)&&(currentGrid->Cells[ACol+1][ARow+1] != 12)&&(currentGrid->Cells[ACol+1][ARow] != 12))||((direction == 1)&&(currentGrid->Cells[ACol][ARow] != 12)&&(currentGrid->Cells[ACol+1][ARow-1] != 12)&&(currentGrid->Cells[ACol][ARow-1] != 12)&&(currentGrid->Cells[ACol-1][ARow-1] != 12)&&(currentGrid->Cells[ACol-1][ARow] != 12)&&(currentGrid->Cells[ACol-1][ARow+1] != 12)/*&&(StringGrid1->Cells[ACol][ARow+1] != 12)*/&&(currentGrid->Cells[ACol+1][ARow+1] != 12)&&(currentGrid->Cells[ACol+1][ARow] != 12))||
((direction == 2)&&(currentGrid->Cells[ACol][ARow] != 12)&&(currentGrid->Cells[ACol+1][ARow-1] != 12)&&(currentGrid->Cells[ACol][ARow-1] != 12)&&(currentGrid->Cells[ACol-1][ARow-1] != 12)&&(currentGrid->Cells[ACol-1][ARow] != 12)&&(currentGrid->Cells[ACol-1][ARow+1] != 12)&&(currentGrid->Cells[ACol][ARow+1] != 12)&&(currentGrid->Cells[ACol+1][ARow+1] != 12)/*&&(StringGrid1->Cells[ACol+1][ARow] != 12)*/)||((direction == 3)&&(currentGrid->Cells[ACol][ARow] != 12)&&(currentGrid->Cells[ACol+1][ARow-1] != 12)&&(currentGrid->Cells[ACol][ARow-1] != 12)&&(currentGrid->Cells[ACol-1][ARow-1] != 12)/*&&(StringGrid1->Cells[ACol-1][ARow] != 12)*/&&(currentGrid->Cells[ACol-1][ARow+1] != 12)&&(currentGrid->Cells[ACol][ARow+1] != 12)&&(currentGrid->Cells[ACol+1][ARow+1] != 12)&&(currentGrid->Cells[ACol+1][ARow] != 12))) {


                currentrow = ARow - 1;
               // Application->MessageBox("Proshlo uslovie!","Жеребьевка",MB_OK);
                currentcol = ACol - 1;

                shipsize = 0;

                // заполним всё пространство между концом и началом

                while (shipsize!= ships[currentship -  1] - 1) {//Application->MessageBox("Procrutka!","Жеребьевка",MB_OK);

                   playerField[currentrow][currentcol] = 12;

                   currentGrid->Cells[currentcol+1][currentrow+1] = playerField[currentrow][currentcol];

                    if (direction == 0) // вверх

                        currentrow--;

                    else if (direction == 1) // вниз

                        currentrow++;

                    else if (direction == 2) // вправо

                        currentcol++;

                    else // влево

                        currentcol--;

                    shipsize++;

                }

                currentship++;
                //Application->MessageBox("Zopa!","Жеребьевка",MB_OK);
                firstpoint = FALSE;
                //Application->MessageBox("Zopa111!","Жеребьевка",MB_OK);
                currentGrid->Refresh();
                if(firstpoint==TRUE)
                {
                 //Application->MessageBox("firstpoint==TRUE!","Жеребьевка",MB_OK);
                }
                if(firstpoint==FALSE)
                {
                //Application->MessageBox("firspoint==FALSE!","Жеребьевка",MB_OK);
                }

            }

        }
        if(currentship>10)
        {
        disposition=FALSE;
         Application->MessageBox("disposition=FALSE;!","Жеребьевка",MB_OK);
         }
       // if (currentship > 10 && leftshoots == TRUE)

            //NextPlayerSetsCoordinates();

        //if (currentship > 10 && leftshoots == FALSE)

            //WhoIsFirst();

    } // if (currentship <= 10)

}
//---------------------------------------------------------------------------




void __fastcall TForm1::Draw1(TObject *Sender, int ACol, int ARow,
      TRect &Rect, TGridDrawState State)
{
 //CellColorer(Sender,ACol,ARow,Rect);

 if(StringGrid1->Cells[ACol][ARow]==12 )
 {
        StringGrid1->Canvas->Brush->Color=clBlue;
        StringGrid1->Canvas->FillRect(Rect);
        StringGrid1->Canvas->Pen->Color = clGreen;
        StringGrid1->Canvas->Rectangle(Rect);


 }
 if(StringGrid1->Cells[ACol][ARow]==14)
       {
       StringGrid1->Canvas->Brush->Color=clGreen;
        StringGrid1->Canvas->FillRect(Rect);
        StringGrid1->Canvas->Pen->Color = clGreen;
        StringGrid1->Canvas->Rectangle(Rect);
        }
 if(StringGrid1->Cells[ACol][ARow]==15)
        {
         StringGrid1->Canvas->Brush->Color=clBlack;
        StringGrid1->Canvas->FillRect(Rect);
        StringGrid1->Canvas->Pen->Color = clGreen;
        StringGrid1->Canvas->Rectangle(Rect);

         }
 if(StringGrid1->Cells[ACol][ARow]==16)
       {
       StringGrid1->Canvas->Brush->Color=clGreen;
        StringGrid1->Canvas->FillRect(Rect);
        StringGrid1->Canvas->Pen->Color = clGreen;
        StringGrid1->Canvas->Rectangle(Rect);
        }
        if(StringGrid1->Cells[ACol][ARow]==17)
        {
         StringGrid1->Canvas->Brush->Color=clBlack;
        StringGrid1->Canvas->FillRect(Rect);
        StringGrid1->Canvas->Pen->Color = clGreen;
        StringGrid1->Canvas->Rectangle(Rect);

         }



}
//---------------------------------------------------------------------------

//----Отмена установки корабля------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
if (StringGrid1->Enabled==TRUE)
{
if (firstpoint == TRUE)
{
     leftField[lastrow-1][lastcol-1]=0;
     StringGrid1->Cells[lastcol][lastrow] = ' ' ;
     firstpoint = FALSE;
}
if (shipsize == 1)
{       disposition=TRUE;
        currentship--;
        leftField[lastrow-1][lastcol-1]=0;
        StringGrid1->Cells[lastcol][lastrow] = ' ' ;
}
}
 if (StringGrid2->Enabled==TRUE)
{
if (firstpoint == TRUE)
{
     rightField[lastrow-1][lastcol-1]=0;
     StringGrid2->Cells[lastcol][lastrow] = ' ' ;
     firstpoint = FALSE;
}
if (shipsize == 1)
{       disposition=TRUE;
        currentship--;
        rightField[lastrow-1][lastcol-1]=0;
        StringGrid2->Cells[lastcol][lastrow] = ' ' ;
}
}
}
//---------------------------------------------------------------------------


//---------Кнопка Старта--------------------------------------------------------------




void __fastcall TForm1::Button2Click(TObject *Sender)
{

if ((RadioButton1->Checked==TRUE)&&(disposition == FALSE))
{
StringGrid1->Enabled=FALSE;
Button3->Visible=FALSE;
Button2->Visible=FALSE;
RadioButton1->Visible=FALSE;
RadioButton2->Visible=FALSE;
StringGrid2->Visible=TRUE;
  pcopponent=TRUE;
  RandomPlace();
  

}
if ((RadioButton2->Checked==TRUE)&&(disposition == FALSE))
{
  pcopponent=FALSE;
  StringGrid2->Visible=TRUE;
  Button2->Visible=FALSE;
  RadioButton1->Visible=FALSE;
  RadioButton2->Visible=FALSE;
  StringGrid1->Enabled=FALSE;
  StringGrid2->Enabled=TRUE;
  disposition=TRUE;
  leftshoots=FALSE;
  currentship=1;
  StartGame();
  //firstpoint=FALSE;
  Button4->Visible=TRUE;
 // StartGame();
}
        StringGrid2->Refresh();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::RandomPlace()
{      /* srand(time(0));
      for(int i=0;i<100;i++)

         {
        int stolbez = rand()%10;
        int stroka = rand()%10;
        if(rightField[stroka][stolbez]==0)
        {
         rightField[stroka][stolbez]=13  ;
        StringGrid2->Cells[stolbez+1][stroka+1] = rightField[stroka][stolbez];
        }
        else
        {
        continue;
        }
        } */
        //TODO: Add your source code here
        int i, j, s;

int shipsize; // нужен при переборе

int direction; // направление, 0 – горизонталь, 1 – вертикаль

int goodpositions[100];

int goodposcounter = 0;

int currentline, currentrow;

bool good;

currentship = 1;

// десять кораблей

for (s = 0; s < 10; s++) {

    shipsize = ships[s];

    goodposcounter = 0;

    // выбираем направление

    randomize();

    direction = random(2); // 0 или 1

    // собираем места, куда можем поставить

    // для этого обходим каждую клетку поля

    for (i = 0; i < 10; i++) {

        for (j = 0; j < 10; j++) {

            // и проверяем, помещается ли там корабль или нет

            currentline = i;

            currentrow = j;

            good = TRUE;

            shipsize = ships[s];

            // обходим каждую палубу ко-рабля

            while (shipsize > 0) {

                if (currentrow > 9 || currentline > 9) {

                    good = FALSE;

                }

                // придётся проверить все 8 сторон

                if (currentline!= 0) { // верхний средний

                    if (rightField[currentline - 1][currentrow]!= 0) {

                        good = FALSE;

                    }

                }

                if (currentline!= 0 && currentrow!= 9) { // верхний правый

                    if (rightField[currentline - 1][currentrow + 1]!= 0) {

                        good = FALSE;

                    }

                }

                if (currentrow!= 9) { // средний правый

                    if (rightField[currentline][currentrow + 1]!= 0) {

                        good = FALSE;

                    }

                }

                if (currentline!= 9 && currentrow!= 9) { // нижний правый

                    if (rightField[currentline + 1][currentrow + 1]!= 0) {

                        good = FALSE;

                    }

                }

                if (currentline!= 9) { // нижний средний

                    if (rightField[currentline + 1][currentrow]!= 0) {

                        good = FALSE;

                    }

                }

                if (currentline!= 9 && currentrow!= 0) { // нижний левый

                    if (rightField[currentline + 1][currentrow - 1]!= 0) {

                        good = FALSE;

                    }

                }

                if (currentrow!= 0) { // средний левый

                    if (rightField[currentline][currentrow - 1]!= 0) {

                        good = FALSE;

                    }

                }

                if (currentline!= 0 && currentrow!= 0) { // верхний левый

                    if (rightField[currentline - 1][currentrow - 1]!= 0) {

                        good = FALSE;

                    }

                }

                if (good == FALSE)

                    break;

                if (direction == 0)

                    currentrow++;

                else

                    currentline++;

                shipsize--;

            } // while (sizecounter > 0)

            if (good == TRUE) {

                goodpositions[goodposcounter] = i*10 + j;

                goodposcounter++;

            }

        } // for j

    } // for i

    // выбираем из них одно
     do {
    randomize();

    int place = random(goodposcounter); // выбрали место старта

    // теперь поставим корабль

    shipsize = ships[s];

    currentline = (goodpositions[place] - goodpositions[place]%10)/10;

    currentrow = goodpositions[place]%10;
    }while (rightField[currentline][currentrow] == 12);

    while (shipsize > 0) {

        rightField[currentline][currentrow] = 12;
        //StringGrid2->Cells[currentline+1][currentrow+1] = rightField[currentline][currentrow];

        if (direction == 0)

            currentrow++;

        else

            currentline++;

        shipsize--;

    }

    currentship++;

}
Doom();
}

void __fastcall TForm1::Doom()
{
int doom;
srand(time(0));
doom=rand()%2;
if(doom==0)
{
 Application->MessageBox("Вы ходите первый!","Жеребьевка",MB_OK);
 leftshoots=TRUE;
 StringGrid2->Enabled=TRUE;
 StartGame2();
}
if(doom==1)
{

 if (pcopponent == TRUE)
 {
 Application->MessageBox("Соперник ходит первый!","Жеребьевка",MB_OK);
 leftshoots=FALSE;
 //CompShoots();
 Timer1->Enabled=TRUE;
 }
 else if (pcopponent == FALSE)
 {
 Application->MessageBox("Игрок №2 ходит первый!","Жеребьевка",MB_OK);
  leftshoots=FALSE;
  StringGrid1->Enabled=TRUE;
  StartGame2();
 }
}
        //TODO: Add your source code here
}



void __fastcall TForm1::Imshooting(TObject * Sender, int ACol, int ARow)
{
  int (*opponentField)[10], (*opponentVisible)[10];
  TStringGrid* currentGrid = (TStringGrid*)Sender;

      if (((TStringGrid*)Sender)->Name == "StringGrid1") {

    opponentField = leftField;

    //opponentVisible = leftVisible;

} else {

    opponentField = rightField;

    //opponentVisible = rightVisible;


}

 if (opponentField[ARow-1][ACol-1]==12)
 {
     opponentField[ARow-1][ACol-1]=14;
     currentGrid->Cells[ACol][ARow]=opponentField[ARow-1][ACol-1];
     if (currentGrid->Name == "StringGrid1")
    {
    popal2++;
    }
    if (currentGrid->Name == "StringGrid2")
    {
    popal1++;
    }

     if((opponentField[ARow-1][(ACol-1)+1]==12)||(opponentField[ARow-1][(ACol-1)-1]==12)||(opponentField[(ARow-1)+1][ACol-1]==12)||(opponentField[(ARow-1)-1][ACol-1]==12)||((opponentField[ARow-1][(ACol-1)+1]==14)&&(opponentField[ARow-1][(ACol-1)+2]==12))||((opponentField[ARow-1][(ACol-1)-1]==14)&&(opponentField[ARow-1][(ACol-1)-2]==12))||((opponentField[(ARow-1)+1][ACol-1]==14)&&(opponentField[(ARow-1)+2][ACol-1]==12))||((opponentField[(ARow-1)-1][ACol-1]==14)&&(opponentField[(ARow-1)-2][ACol-1]==12))||((opponentField[ARow-1][(ACol-1)+1]==14)&&(opponentField[ARow-1][(ACol-1)+2]==14)&&(opponentField[ARow-1][(ACol-1)+3]==12))||((opponentField[ARow-1][(ACol-1)-1]==14)&&(opponentField[ARow-1][(ACol-1)-2]==14)&&(opponentField[ARow-1][(ACol-1)-3]==12))||((opponentField[(ARow-1)+1][ACol-1]==14)&&(opponentField[(ARow-1)+2][ACol-1]==14)&&(opponentField[(ARow-1)+3][ACol-1]==12))||((opponentField[(ARow-1)-1][ACol-1]==14)&&(opponentField[(ARow-1)-2][ACol-1]==14)&&(opponentField[(ARow-1)-3][ACol-1]==12)))
     {
     Application->MessageBox("Ранил!","Результат выстрела",MB_OK);
     }
     else
     {
     Application->MessageBox("Убил!","Результат выстрела",MB_OK);
     }
     CheckWin();
 }
 if(opponentField[ARow-1][ACol-1]!=12&&opponentField[ARow-1][ACol-1]!=14&&opponentField[ARow-1][ACol-1]!=15)
 {
   opponentField[ARow-1][ACol-1]=15;
   currentGrid->Cells[ACol][ARow]=opponentField[ARow-1][ACol-1];
   if (pcopponent == TRUE)
   {
   leftshoots=FALSE;
   currentGrid->Enabled=FALSE;
  // CompShoots();
   Timer1->Enabled=TRUE;
   }
   if (pcopponent == FALSE)
   {
    if (currentGrid->Name == "StringGrid1")
    {
    leftshoots=TRUE;
    StartGame();
    Application->MessageBox("Переход хода!","Результат выстрела",MB_OK);
    currentGrid->Enabled=FALSE;
    StringGrid2->Enabled = TRUE;
    StartGame2();
    }
    if (currentGrid->Name == "StringGrid2")
    {
    leftshoots=FALSE;
    StartGame();
    Application->MessageBox("Переход хода!","Результат выстрела",MB_OK);
    currentGrid->Enabled=FALSE;
    StringGrid1->Enabled = TRUE;
     StartGame2();
    }
   }
 }


 StringGrid1->Refresh();
 StringGrid2->Refresh();

        //TODO: Add your source code here
}
void __fastcall TForm1::Draw2(TObject *Sender, int ACol, int ARow,
      TRect &Rect, TGridDrawState State)
{
   if(StringGrid2->Cells[ACol][ARow]==12 )
 {
        StringGrid2->Canvas->Brush->Color=clRed;
        StringGrid2->Canvas->FillRect(Rect);
        StringGrid2->Canvas->Pen->Color = clGreen;
        StringGrid2->Canvas->Rectangle(Rect);
        }
   if (StringGrid2->Cells[ACol][ARow]==13)
 {
        StringGrid2->Canvas->Brush->Color=clRed;
        StringGrid2->Canvas->FillRect(Rect);
        StringGrid2->Canvas->Pen->Color = clGreen;
        StringGrid2->Canvas->Rectangle(Rect);

 }
 if(StringGrid2->Cells[ACol][ARow]==14)
       {
       StringGrid2->Canvas->Brush->Color=clGreen;
        StringGrid2->Canvas->FillRect(Rect);
        StringGrid2->Canvas->Pen->Color = clGreen;
        StringGrid2->Canvas->Rectangle(Rect);
        }
 if(StringGrid2->Cells[ACol][ARow]==15)
        {
         StringGrid2->Canvas->Brush->Color=clBlack;
        StringGrid2->Canvas->FillRect(Rect);
        StringGrid2->Canvas->Pen->Color = clGreen;
        StringGrid2->Canvas->Rectangle(Rect);

         }
 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SelectGrid2(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
 if (leftshoots == TRUE)
 {
 Imshooting(Sender,ACol,ARow);
 }
 if(disposition == TRUE)
 {
        ManualPlacing(Sender, ACol, ARow);
 }
 StringGrid2->Refresh();       
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CompShoots()
{
        
        //TODO: Add your source code here
        srand(time(0));
        int co,ro,viborvistrela;

       do{

         co = rand()%10+1;
         ro = rand()%10+1;

        if(ranil==TRUE)
        {

          viborvistrela=rand()%4;
         // Application->MessageBox("Проверка2!","Результат выстрела",MB_OK);
          if(viborvistrela == 0)
          {co=saveco+1;
          ro=savero;
          //Application->MessageBox("0!","Результат выстрела",MB_OK);
          }
          if(viborvistrela == 1)
          {co=saveco-1;
          ro=savero;
          //Application->MessageBox("1!","Результат выстрела",MB_OK);
          }
          if(viborvistrela == 2)
          {ro=savero+1;
          co=saveco;
          //Application->MessageBox("2!","Результат выстрела",MB_OK);
          }
          if(viborvistrela == 3)
          {ro=savero-1;
          co=saveco;
          //Application->MessageBox("3!","Результат выстрела",MB_OK);
          }
        }
        if(gdechetvertiy==1)
     {
     StringGrid1->Cells[saveco+3][savero]=16;
     gdechetvertiy=0;
     }
     if(gdechetvertiy==2)
     {
     StringGrid1->Cells[saveco-3][savero]=16;
     gdechetvertiy=0;
     }
     if(gdechetvertiy==3)
     {
     StringGrid1->Cells[saveco][savero+3]=16;
     gdechetvertiy=0;
     }
     if(gdechetvertiy==4)
     {
     StringGrid1->Cells[saveco][savero-3]=16;
     gdechetvertiy=0;
     }
        if (StringGrid1->Cells[co][ro]==12)
 {

     StringGrid1->Cells[co][ro]=16;
     compmoove++;
     popal2++;
     CheckWin();
     //Timer1->Enabled=TRUE;
     if((StringGrid1->Cells[co+1][ro]==12)||(StringGrid1->Cells[co-1][ro]==12)||(StringGrid1->Cells[co][ro+1]==12)||(StringGrid1->Cells[co][ro-1]==12))
     {
     //Application->MessageBox("Проверка1!","Результат выстрела",MB_OK);
             ranil=TRUE;
              saveco=co;
              savero=ro;
              Application->MessageBox("Ваш корабль подбили!","Результат выстрела",MB_OK);
              continue;
     }
     if (((StringGrid1->Cells[co+1][ro]==16)&&(StringGrid1->Cells[co+2][ro]==12))||((StringGrid1->Cells[co-1][ro]==16)&&(StringGrid1->Cells[co-2][ro]==12))||((StringGrid1->Cells[co][ro+1]==16)&&(StringGrid1->Cells[co][ro+2]==12))||((StringGrid1->Cells[co][ro-1]==16)&&(StringGrid1->Cells[co][ro-2]==12)))
     {
    //Application->MessageBox("Через клетку враг!","Результат выстрела",MB_OK);
     ranil=TRUE;
     continue;
     }
     if(((StringGrid1->Cells[co+1][ro]==16)&&(StringGrid1->Cells[co+2][ro]==16)&&(StringGrid1->Cells[co+3][ro]==12)))
     {
     gdechetvertiy=1;
     ranil=FALSE;
     saveco=co;
     savero=ro;
     //Application->MessageBox("Враг через 2 справа!","Результат выстрела",MB_OK);
     continue;
     }
     if(((StringGrid1->Cells[co-1][ro]==16)&&(StringGrid1->Cells[co-2][ro]==16)&&(StringGrid1->Cells[co-3][ro]==12)))
     {
     gdechetvertiy=2;
     ranil=FALSE;
     saveco=co;
     savero=ro;
     //Application->MessageBox("Враг через 2 слева!","Результат выстрела",MB_OK);
     continue;
     }
     if(((StringGrid1->Cells[co][ro+1]==16)&&(StringGrid1->Cells[co][ro+2]==16)&&(StringGrid1->Cells[co][ro+3]==12)))
     {
     gdechetvertiy=3;
     ranil=FALSE;
     saveco=co;
     savero=ro;
    // Application->MessageBox("Враг через 2 снизу!","Результат выстрела",MB_OK);
     continue;
     }
     if(((StringGrid1->Cells[co][ro-1]==16)&&(StringGrid1->Cells[co][ro-2]==16)&&(StringGrid1->Cells[co][ro-3]==12)))
     {
     gdechetvertiy=4;
     ranil=FALSE;
     saveco=co;
     savero=ro;
    // Application->MessageBox("Враг через 2 сверху!","Результат выстрела",MB_OK);
     continue;
     }

     ranil=FALSE;
     Application->MessageBox("Ваш корабль потопили!","Результат выстрела",MB_OK);


 }
 if(StringGrid1->Cells[co][ro]!=12&&StringGrid1->Cells[co][ro]!=16&&StringGrid1->Cells[co][ro]!=17)
 {
   StringGrid1->Cells[co][ro]=17;
   StringGrid2->Enabled=TRUE;
   leftshoots=TRUE;
   //ranil=FALSE;
   compmoove++;
   }
   if(compmoove==100)
   {break;
   }

   }while(leftshoots==FALSE);

}

void __fastcall TForm1::CheckWin()
{
        //TODO: Add your source code here


        if(popal2==20)
        {
        Application->MessageBox("You loose!","End",MB_OK);
        StringGrid1->Enabled=FALSE;
        StringGrid2->Enabled=FALSE;
        }
        if(popal1==20)
        {
        Application->MessageBox("You win!","End",MB_OK);
        StringGrid1->Enabled=FALSE;
        StringGrid2->Enabled=FALSE;
        }
}
void __fastcall TForm1::Button4Click(TObject *Sender)
{
  Button4->Visible=FALSE;
  Button3->Visible=FALSE;
  StringGrid1->Enabled=FALSE;
  StringGrid2->Enabled=FALSE;
  StartGame();
  Doom();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{

CompShoots();
Timer1->Enabled=FALSE;

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TForm1::StartGame2()
{
      for (int i=0;i<10;i++)
{for(int j=0;j<10;j++)
{
      if (StringGrid1->Enabled==TRUE)
      {
       if ( leftField[i][j]==12)
         {
                StringGrid1->Cells[j+1][i+1]=' ';
         }
      }
   if (StringGrid2->Enabled==TRUE)
      {
 if ( rightField[i][j]==12)
 {
StringGrid2->Cells[j+1][i+1]=' ';
  }
  }
  if (StringGrid1->Enabled==FALSE)
      {
       if ( leftField[i][j]!=0)
         {
                StringGrid1->Cells[j+1][i+1]= leftField[i][j];
         }
      }
   if (StringGrid2->Enabled==FALSE)
      {
 if ( rightField[i][j]!=0)
 {
StringGrid2->Cells[j+1][i+1]=rightField[i][j];
  }
  }
}
}
 StringGrid2->Refresh();
 StringGrid1->Refresh();  //TODO: Add your source code here
}
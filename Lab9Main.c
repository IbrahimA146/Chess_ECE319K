// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// Your name
// Last Modified: 12/26/2024


#include "../inc/ADC.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "../inc/DAC5.h"
#include "../inc/Arabic.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"
#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "Chess_Sprites.h"

// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

Arabic_t ArabicAlphabet[]={
alif,ayh,baa,daad,daal,dhaa,dhaal,faa,ghayh,haa,ha,jeem,kaaf,khaa,laam,meem,noon,qaaf,raa,saad,seen,sheen,ta,thaa,twe,waaw,yaa,zaa,space,dot,null
};
Arabic_t Hello[]={alif,baa,ha,raa,meem,null}; // hello
Arabic_t WeAreHonoredByYourPresence[]={alif,noon,waaw,ta,faa,raa,sheen,null}; // we are honored by your presence

uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}



uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};



/* 



This is the section where we do all of our initializations and declare out handlers....

- - - - - ()()() - - - - - - - - - - - - - - - () ()() - - - - - - - -






*/






const uint8_t whiteOrBlack[8][8] = {
  {1,0,1,0,1,0,1,0},
  {0,1,0,1,0,1,0,1},
  {1,0,1,0,1,0,1,0},
  {0,1,0,1,0,1,0,1},
  {1,0,1,0,1,0,1,0},
  {0,1,0,1,0,1,0,1},
  {1,0,1,0,1,0,1,0},
  {0,1,0,1,0,1,0,1}    
};

#include <stdio.h> 
#define NUM 8


bool bot = false;
bool actMiniMax = true;
bool player1Mode;
bool isplacing = false;
bool needtoCheck = false;


static uint8_t toggle = 0;
uint8_t screen0 = 0; // used to cahnge screens 
uint8_t currentFrame = 0;
uint8_t updateFrame = 0;
uint8_t getSwitch = 0;
uint8_t chosenLanguage = 0; // 5 = spanish, 10 = english
#define NUM_FRAMES 4


 uint16_t whitehex = 0xFFFF;
 uint16_t blackhex = 0000;
uint16_t chosenhexcolor;
unsigned short backgroundcolor = 0x0000;

uint8_t xin1;
  uint8_t yin1; 
  uint8_t xf1; 
  uint8_t yf1;  

uint32_t soundpause = 4;

uint8_t chessturn = 1; // 1 = white; 0 = black
uint8_t doubleclick = 0;
uint8_t futureIDGlobal;
uint8_t currentIDGlobal;
uint32_t x;
uint32_t y;
uint32_t xplot = 48;
uint32_t yplot = 60;
uint32_t xarr = 4;
uint32_t yarr = 4;
uint8_t x0to7pre;
uint8_t y0to7pre;
int xprevious = -1;
int yprevious = -1;
uint32_t vol;
uint32_t Time = 0;
bool turn = true; //true = white: false = black
uint32_t click = 0; // 0 is just recived turn 1 is has selected init pos and 2 is selected final posion
uint32_t datas;
uint32_t flag;
uint32_t TimerG0counts = 0;
uint8_t whitewantsdraw = 0;
uint8_t blackwantsdraw = 0;
uint8_t agreeddraw = 0;
uint8_t blackwon = 0;
uint8_t whitewon = 0;
uint8_t whitescore = 0;
uint8_t blackscore = 0;
int selectedBoxColor = ST7735_YELLOW;
int yellowColor = ST7735_YELLOW;
int cyanColor = ST7735_CYAN;



void buttonInit_LEDInit()
{
 IOMUX->SECCFG.PINCM[PA24INDEX] = (uint32_t) 0x00040081;
 IOMUX->SECCFG.PINCM[PA25INDEX] = (uint32_t) 0x00040081;
 IOMUX->SECCFG.PINCM[PA26INDEX] = (uint32_t) 0x00040081;
 IOMUX->SECCFG.PINCM[PA27INDEX] = (uint32_t) 0x00040081;
 IOMUX->SECCFG.PINCM[PA28INDEX] = (uint32_t) 0x00040081;


 //output init
 IOMUX->SECCFG.PINCM[PA15INDEX] = (uint32_t) 0x00000081;
 IOMUX->SECCFG.PINCM[PA16INDEX] = (uint32_t) 0x00000081;
 IOMUX->SECCFG.PINCM[PA17INDEX] = (uint32_t) 0x00000081;

 
 //DOE init
 GPIOA->DOE31_0 |= 0x00038000;  
}

uint32_t ButtonIn(void){
uint32_t res;
 
  res = (GPIOA->DIN31_0  & (0x1F000000)) >> 24;
    return res; // write this
}





/*


    DRAW HOLLOW BOX FUNCTION


    Purpose; Draws a hollow box around selected chess square

    How? Highlights the current square at (xplot, yplot) using a hollow box and re draws the previously
    selected square using its original color based on what it was previously. Then it stores new pos. 
    Functionality:
      - If its not a double click, redraw the old square using its original color
      - If the old square and current square match, clear the selection
      - Always draw hollow box around the currently selected square
      - Store current position

    Variables used?
      - xplot, yplot
      - xprev, yprev
      - WhiteOrBlack[][]
      - Doubleclick
      - Selectedboxcolor

    Inputs: None

    Outputs: Draws pixels to the screen





*/


void drawHollowBox(){

  // Color Definitions
  uint16_t lightBrown = ST7735_Color565(210, 190, 140);
  uint16_t darkGreen = ST7735_Color565(34, 85, 34);

  int i, j; // For loop variables


  // Get the index of the previously selected square (chessboard drawn in 16x20 blocks)
  int x_index = xprevious / 16;
  int y_index = yprevious / 20;

  // Make sure double clock not happening
  if (doubleclick != 2) {



    if (xprevious != -1 && whiteOrBlack[y_index][x_index] == 1) {
      for (i = 0; i < 12; i++) {
        ST7735_DrawPixel(xprevious + 2 + i, yprevious, lightBrown);
        ST7735_DrawPixel(xprevious + 2 + i, yprevious + 18, lightBrown);
      }
      for (j = 0; j < 17; j++) {
        ST7735_DrawPixel(xprevious, yprevious + 1 + j, lightBrown);
        ST7735_DrawPixel(xprevious + 14, yprevious + 1 + j, lightBrown);
      }
    } else {
      for (i = 0; i < 12; i++) {
        ST7735_DrawPixel(xprevious + 2 + i, yprevious, darkGreen);
        ST7735_DrawPixel(xprevious + 2 + i, yprevious + 18, darkGreen);
      }
      for (j = 0; j < 17; j++) {
        ST7735_DrawPixel(xprevious, yprevious + 1 + j, darkGreen);
        ST7735_DrawPixel(xprevious + 14, yprevious + 1 + j, darkGreen);
      }
    }

    if (xplot == xprevious && yplot == yprevious) {
      xprevious = -1;
      yprevious = -1;
    }

    for (i = 0; i < 12; i++) {
      ST7735_DrawPixel(xplot + 2 + i, yplot, selectedBoxColor);
      ST7735_DrawPixel(xplot + 2 + i, yplot + 18, selectedBoxColor);
    }

    for (j = 0; j < 17; j++) {
      ST7735_DrawPixel(xplot, yplot + 1 + j, selectedBoxColor);
      ST7735_DrawPixel(xplot + 14, yplot + 1 + j, selectedBoxColor);
    }

    xprevious = xplot;
    yprevious = yplot;
  }
}

void TIMG12_IRQHandler(void){
  
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    Time++;
    ADC_InTriple(ADC1, &y, &vol, &x);
    flag = 1;
    uint32_t res = ButtonIn() - 16;

    if(res == 1)
  {

    if(doubleclick == 0)
    {

      if((player1Mode) && (chessturn == 1))
      {

        bot = true;

        actMiniMax = true;

      }
      else {

        bot = false;

      xin1 = xarr-1;
      yin1 = yarr-1;
      doubleclick = 1;
      selectedBoxColor = ST7735_CYAN;
      while(res != 0){res = ButtonIn() - 16;};
      
      }
      
    }
  }

  if(res == 1)
  {

    if(doubleclick == 1)
    {
      xf1 = xarr-1;
      yf1 = yarr-1;
      doubleclick = 2;
      selectedBoxColor = ST7735_YELLOW;
      while(res != 0){res = ButtonIn() - 16;};
    }

  }

  if(res == 8) // white draw
  {
    uint32_t localcount = 0;
    uint32_t res = 0;

      GPIOA->DOUTCLR31_0 = (1 << 15);
      GPIOA->DOUTSET31_0 = (1 << 16);
      GPIOA->DOUTCLR31_0 = (1 << 17);
      whitewantsdraw = 1;
      while((localcount != 5000000) && (res != 4) && (res != 1))
      {
        res = ButtonIn() - 16;
        localcount++;
        if((5000000 - localcount) < 1000000 )
        {
          if((localcount %100000) == 0)
          {

            GPIOA->DOUTTGL31_0 = (1 << 16);

          }
          
          
        }
        
      }
      {

      }
      if((whitewantsdraw == 1) && (res == 4))
      {
        agreeddraw = 1;
      }
      else {
      blackwantsdraw = 0;
      whitewantsdraw = 0;
      GPIOA->DOUTCLR31_0 = (1 << 16);
      }



    
  }

  if(res == 4) // black draw
  {

      uint32_t localcount = 0;
    uint32_t res = 0;

      GPIOA->DOUTCLR31_0 = (1 << 15);
      GPIOA->DOUTSET31_0 = (1 << 16);
      GPIOA->DOUTCLR31_0 = (1 << 17);
      whitewantsdraw = 1;
      while((localcount != 5000000) && (res != 8) && (res != 1))
      {
        res = ButtonIn() - 16;
        localcount++;
        if((5000000 - localcount) < 500000 )
        {
          if((localcount %100000) == 0)
          {

            GPIOA->DOUTTGL31_0 = (1 << 16);

          }
          
          
        }
        
      }
      {

      }
      if((whitewantsdraw == 1) && (res == 8))
      {
        agreeddraw = 1;
      }
      else {
      blackwantsdraw = 0;
      whitewantsdraw = 0;
      GPIOA->DOUTCLR31_0 = (1 << 16);
      }


    
  }

  if(res == 2) // resign
  {

    if(chessturn == 1)
    {

      blackwon = 1;

      

    }
    if(chessturn == 0)
    {

      whitewon = 1;

    }
    

   
    


    
  }

  if(res == 16) // undo
  {


    
  }


    // sample 12-bit ADC0 channel 5, slidepot
    // store data into mailbox
    // set the semaphore
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}




/*




  Draw Board FUNCTION! :)

  Purpose?!? Draws the entire chess board :O

  Initializes the LCD screen and renders an 8x8 chessboard pattern using alternating light/dark
  rectangles

  Input - > (Variables used?)
    - Num defines the board size
  Outputs - > 
    - Sends graphical data using the ST7735_FillRect()
    - Produces 8x8 alternating pattern of light brown and dark green tiles
  Return? None :(

  How does it work...

    - Loops over each row and column to determine the (x,y) screen position for each square
    - Uses a checkboard pattern
      a) k tracks row offset to alternate the light/dark starting square each row
      b) Uses a checkerboard pattern: `k` tracks row offset to alternate the light/dark starting square each row
      c) If the condition `j % 2 != k` is true, it draws a dark square. Otherwise, it draws a light one
      d) After finishing each row, it toggles `k` between 0 and 1 to ensure alternating pattern per row




*/


void drawBoard() {


  // Define tile colors

  uint16_t lightBrown = ST7735_Color565(210, 190, 140);
  uint16_t darkGreen = ST7735_Color565(34, 85, 34);

  ST7735_InitR(INITR_REDTAB);

  int i, j;
  int k = 0;

  for (i = 0; i < NUM; i++) { // each iteration is a row
    for (j = 0; j < NUM; j++) { // each iteration is a column
      int x = i * 16; // left corner of square
      int y = j * 20; // top corner of square

      uint16_t squareColor;

      if ((j % 2 == 0 && k == 0) || (j % 2 != 0 && k == 1)) { // alternating logic
        squareColor = lightBrown; // even row : light square
      } else {
        squareColor = darkGreen; // odd row : dark square
      }

      ST7735_FillRect(x, y, 16, 20, squareColor); // File the rectangle
    }

    // Flip `k` to alternate starting color for the next row
    if (k == 0) {
      k = 1;
    } else {
      k = 0;
    }
  }
  
}


//START OF ACTUAL CHESS GAME
//WILL BE PRINTED OUT IN THE CIO: HARDWARE IMEPLENTAION STILL A WIP
//GLOBAL VARIABLES

uint8_t xpos; //Keeps important x positions
uint8_t ypos; //Keeps important y positions
uint8_t playerKing = 20; //Keeps what opposing kings turn it is (10 for white and 20 for black) P.S (for now it is defaulted at 20 for testing)
bool check = false;
bool printcheck = true; // is the code currently checking for a chess "check"
bool invalidMove = false;
uint8_t currentx;
uint8_t currenty;
uint8_t futurex;
uint8_t futurey;



/*


Piece Definitions (Symbolic Constants)

NA 0     // No piece
WP 11    // White pawn
WH 12    // White knight
WB 13    // White bishop
WR 15    // White rook
WQ 19    // White queen
WK 20    // White king

BP 1     // Black pawn
BH 2     // Black knight
BB 3     // Black bishop
BR 5     // Black rook
BQ 9     // Black queen
BK 10    // Black king




*/

#define NA 0

#define WP 11
#define WH 12
#define WB 13
#define WR 15
#define WQ 19
#define WK 20

#define BP 1
#define BH 2
#define BB 3
#define BR 5
#define BQ 9
#define BK 10


/*


CHESS BOARD SATE VARIABLES


*/


/*

ChessboardNum: Current Live Game State

What for? Contains the position of every piece during actual gameplay. 

*/

uint8_t chessboardNum[8][8] = {
  {WR,WH,WB,WK,WQ,WB,WH,WR},
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {BR,BH,BB,BK,BQ,BB,BH,BR}


  
    
};


/*

ChessboardNumCheck

What for? Used to store the state before a move to check for things like check/checkmate

*/
uint8_t chessboardNumCheck[8][8] = {
  {WR,WH,WB,WK,WQ,WB,WH,WR},
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {BR,BH,BB,BK,BQ,BB,BH,BR}
    
};


/*

Used to save the game state before a player makes a move. Check if a move is found to be ILLEGAL :OO

*/

uint8_t chessboardNumSave[8][8] = {
  {WR,WH,WB,WK,WQ,WB,WH,WR},
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {BR,BH,BB,BK,BQ,BB,BH,BR}
    
};

/*

Another snapshot.... (more specific checks)

*/

uint8_t chessboardNumSpecialSave[8][8] = {
  {WR,WH,WB,WK,WQ,WB,WH,WR},
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {BR,BH,BB,BK,BQ,BB,BH,BR}
    
};

uint8_t chessboardNumbot[8][8] = {
  {WR,WH,WB,WK,WQ,WB,WH,WR},
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {BR,BH,BB,BK,BQ,BB,BH,BR}


  
    
};

uint8_t chessboardNumSaveBot[8][8] = {
  {WR,WH,WB,WK,WQ,WB,WH,WR},
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {BR,BH,BB,BK,BQ,BB,BH,BR}
    
};


/*

Original state configurations 

*/

const uint8_t chessboardinit[8][8] = {
  {WR,WH,WB,WK,WQ,WB,WH,WR},
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {BR,BH,BB,BK,BQ,BB,BH,BR}
    
};


/*

What this guy do? 

- Saves the current board state (chessboardNum[][]) into chessboardNumSave[][]

*/


void saveChessboardNum()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNumSave[i][j] = chessboardNum[i][j]; // puts chessboardNum into chessboardNumSave
        }
    }

}

/*

What this guy do?

- Saves the current board state into chessboardNumSpecialSave[][].

*/

void SpecialsaveChessboardNum()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNumSpecialSave[i][j] = chessboardNum[i][j]; // puts chessboardNum into chessboardNumSave
        }
    }

}


/*

What this guy do?

- Restores chessboardNum[][] from chessboardNumSave[][].

*/
void restoreChessboardNum()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNum[i][j] = chessboardNumSave[i][j]; // puts chessboardNumSave[][] into chessboardNum[][]
        }
    }

}

/*

What this guy do?

  - Restores chessboardNum[][] from chessboardNumSpecialSave[][].

*/

void SpecialRestoreChessboardNum()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNum[i][j] = chessboardNumSpecialSave[i][j]; // puts chessboardNumSave[][] into chessboardNum[][]
        }
    }

}

/*

What this guy do?

  - It loops through all 64 squares of the board and copies 
    the initial board layout from chessboardinit[][] into the three main board tracking arrays:

*/


void resetBoards()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNum[i][j] = chessboardinit[i][j];
            chessboardNumSave[i][j] = chessboardinit[i][j];
            chessboardNumCheck[i][j] = chessboardinit[i][j]; // puts chessboardNum into chessboardNumSave
        }
    }

}


/*

Find Piece Function

Input? Piece Number

Purpose? Searches the current board (`chessboardNum`) for the first match of the given piece number.

 - How? Loops through all squares on 8x8 board
 - When it finds target piece, it stores (row, column) in global var ypos and xpos


*/


void findPiece(uint8_t pieceNum)
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if(chessboardNum[i][j] == pieceNum) // finds the piece (king or queen (only when there is 1 queen))
      {
        ypos = i; // puts x corrdinate of piece
        xpos = j; // puts y corrdicate of piece
      }
    }
  }
}



/*

PIECE ID Functionality

Purpose?

 - To retrieve the piece ID (number) located at a specific square (yin, xin) on the current board (chessboardNum).

Input? 

 - Row Index (0-7) (yin)
 - Column Index (0-7) (xin)

Output?

  - Returns numeric ID of piece of that square 



*/

uint8_t PieceID(int yin, int xin)
{
  uint8_t num = (uint8_t)chessboardNum[yin][xin]; // finds id of the given square and returns it
  return num;

}



/*

PLACE PIECE Functionality

 - Purpose? 

  Moves a piece from one square to another on the board. [Pretty simple, right? RIGHT?!?!?!]

  Inputs: 

    - yin, xin, Starting square 
    - yf, xf, Destination square
    - Current ID: ID of piece being moved

  Outpts:

    - Modifies the board array 
    - Returns 1 to indicate success

*/

uint8_t placePiece(int yin, int xin, int yf, int xf, uint8_t currentID)
{
    if (!check) // If not simulating a check, do an actual move
    {
        chessboardNum[yin][xin] = 0;         // Clear the original square
        chessboardNum[yf][xf] = currentID;   // Place the piece at the new square
    }

    return 1; // Always return 1 to indicate the operation executed
}

/*


PAWN TAKES Function 

What does it do ?!?!

 - Handles the case where the pawn captures an opponents piece diagonally 

What are the inputs?

 - xin, yin is starting row and column of the pawn
 - yf, xf which is the target row/column of opponent piece 

What does it return?

 - 1 if valid ; 0 otherwise 

How does it work? Well, it's relatively simple :)

 - Retrieves the current piece at (yin, xin) and the piece at (yf, xf)
 - Checks if the move involves a white pawn capturing black or
   black pawn capturing white
 - Verifies that the move is a diagonal forward capture 
 - If valid, moves the piece using `placePiece()` and sets `res = 1`; otherwise res = 0


*/

uint8_t pawnTakes(int yin, int xin, int yf, int xf) {
    uint8_t currentID = PieceID(yin, xin);   // Piece trying to move
    uint8_t targetID  = PieceID(yf, xf);     // Piece being captured
    uint8_t result = 0;

    // Check if it’s a white pawn capturing black
    if ((currentID != 0) && (currentID < 11) && (targetID > 10))
    {
        if ((yin - yf == 1) && ((xin - xf == 1) || (xf - xin == 1)))
        {
            result = placePiece(yin, xin, yf, xf, currentID);
        }
    }

    // Check if it’s a black pawn capturing white
    if ((currentID > 10) && (targetID < 11) && (targetID != 0))
    {
        if ((yf - yin == 1) && ((xin - xf == 1) || (xf - xin == 1)))
        {
            result = placePiece(yin, xin, yf, xf, currentID);
        }
    }

    return result;
}


/*

MAKE PAWN MOVE FUNCITONALITY -->> super duper

 What parameters are we using here?

  - xin, yin are starting position of the pawn
  - yf, xf are target row and column index

  What do we return?

   - 1 if success -> 0 if fail :(

  Purpose?! To process ALL POSSIBLE PAWN MOVES woahh (Single step forward, double step forward, diagonal captures)

  Outputs?

   - Updates chessboardNum if the move is valid by calling the placepiece function

*/

uint8_t makePawnMove(int yin, int xin, int yf, int xf) {
    uint8_t piece = PieceID(yin, xin);     // Current piece to move
    uint8_t target = PieceID(yf, xf);      // Target square piece
    uint8_t result = 0;
    uint8_t midCheck;

    
    result = pawnTakes(yin, xin, yf, xf);


    if (piece == 1 && (yin - yf == 1) && (xin == xf) && target == 0) // Black pawn
    {
        result = placePiece(yin, xin, yf, xf, piece);
    }

    if (piece == 11 && (yf - yin == 1) && (xin == xf) && target == 0) // White pawn
    {
        result = placePiece(yin, xin, yf, xf, piece);
    }

  
    if (piece == 1 && yin == 6 && (yin - yf == 2) && (xin == xf) && target == 0)
    {
        midCheck = PieceID(yf + 1, xf);
        if (midCheck == 0)
        {
            result = placePiece(yin, xin, yf, xf, piece);
        }
    }

    if (piece == 11 && yin == 1 && (yf - yin == 2) && (xin == xf) && target == 0)
    {
        midCheck = PieceID(yf - 1, xf);
        if (midCheck == 0)
        {
            result = placePiece(yin, xin, yf, xf, piece);
        }
    }

    return result;
}

/*


MAKING KNIGHT MOVE - this is a long one...

  Purpose: ...

   Fucntion checks whether a knight move is valid (including capturing opponent or moving to empty square)

  What are our INPUT PARAMETERS..

   - xin, yin : starting row and column of the index
   - yf, xf : target row and column of the index 

  Outputs??

    - If move is valid, it moves by calling place piece
    - If move is not valid, nothing. is. changed. 

  But how does all this WORKKKK

   - First checks that the target square is either:
     - Empty, OR
     - Contains an enemy piece 
   - Then checks for each of the 8 possible knight L-shaped move patterns
   - If any of the move patterns match, calls placePiece to perform the move and sets res = 1; otherwise res = 0


*/

uint8_t makeKnightMove(int yin, int xin,int yf, int xf) {
    uint8_t currentPiece = PieceID(yin, xin);   // Piece at the starting position
    uint8_t targetPiece = PieceID(yf, xf);      // Piece at the target position
    uint8_t result = 0;

    // Check if destination is empty OR it’s a valid capture (opposite color)
    uint8_t isWhite = (currentPiece < 11 && currentPiece != 0);
    uint8_t isBlack = (currentPiece > 10);
    uint8_t targetIsEnemy = ((isWhite && targetPiece > 10) || (isBlack && (targetPiece < 11 && targetPiece != 0)));

    if (targetPiece == 0 || targetIsEnemy)
    {
        int rowDiff = yf - yin;
        int colDiff = xf - xin;

        // Check all 8 possible knight movement patterns
        if ((rowDiff == 2  && (colDiff == 1 || colDiff == -1)) ||
            (rowDiff == -2 && (colDiff == 1 || colDiff == -1)) ||
            (rowDiff == 1  && (colDiff == 2 || colDiff == -2)) ||
            (rowDiff == -1 && (colDiff == 2 || colDiff == -2)))
        {
            result = placePiece(yin, xin, yf, xf, currentPiece);
        }
    }

    return result;
}

/*


Now for the EASIEST one so far... (jk!) pls help..

 - What is the PURPOSE ?!?! 

  a) Handles ALL ALL ALL bishop moves (diagonal and captures)

- What are out input parameters...

  - xin, yin : starting row and column 
  - yf, xf : destination row and column 

- What do we output ....

 - If move is legal - > place piece using placepiece function (look at that modularity!! :O)
 - res based off of legality (1 is yay ; 0 is boo)


- How are we planning on making this work

 1. The function creates four separate temporary coordinate pairs (xtemp/ytemp) to simulate the bishop moving in
    each of its four diagonal directions
 2.  For each direction:
     - It iteratively steps one square at a time until either:
       - It reaches the target square and confirms the path is valid
       - Or, it hits a blocking piece, which disables further checking in that direction
 3. If any direction allows a valid path to the target square, the master `flag` is set to true
 4. If `flag` is true at the end of the loop, `placePiece()` is called to execute the move and `res` is set to 1.
 5. If no valid path was found, the function returns 0.


*/

uint8_t makeBishopMove(int yin, int xin,int yf, int xf) {


    uint8_t currentID = PieceID(yin, xin);
    uint8_t futureID = PieceID(yf, xf);
    uint8_t res = 0;
    bool validMove = false;

    // Define bishop movement directions: 
    int dx[4] = {1, -1, 1, -1};
    int dy[4] = {1, 1, -1, -1};

    for (int dir = 0; dir < 4; dir++)
    {
        int x = xin;
        int y = yin;
        bool blocked = false;

        for (int step = 1; step < 8; step++)
        {
            x += dx[dir];
            y += dy[dir];

            // Stop if we go off board
            if (x < 0 || x >= 8 || y < 0 || y >= 8)
                break;

            uint8_t squareID = PieceID(y, x);

            if (x == xf && y == yf)
            {
                if (squareID == 0 || (currentID < 11 && squareID > 10) || (currentID > 10 && squareID < 11 && squareID != 0))
                {
                    validMove = true;
                }
                break;
            }

            if (squareID != 0)
            {
                blocked = true;
                break;
            }
        }

        if (validMove) break; // No need to keep scanning other directions
    }

    if (validMove)
    {
        res = placePiece(yin, xin, yf, xf, currentID);
    }

    return res;
}

/*

MAKING THE ROOK MOVE.....

  - What is it for

    a) Handles all legal work for the rook

  - What are input parameters:

    - xin, yin ; xf, yf
  
  - What are we outputting? 

   - 1 if legal and we also execute it 
   - 0 if not legal

  - How are we planning on making it work

    - The function checks all four  directions (right, left, up, down) from the rooks position
    - For each direction, it walks one square at a time:
      - If it reaches the destination and it's either empty or has an opponent's piece, the move is valid
      - If any piece blocks the path before reaching the destination, that direction is canceled
    - A set of flags keeps track of whether the path in each direction is still clear
    - If any of the four directions reach the destination legally, the move is executed

*/


uint8_t makeRookMove(int yin, int xin,int yf, int xf) {
    uint8_t currentID = PieceID(yin, xin);
    uint8_t futureID  = PieceID(yf, xf);
    uint8_t res = 0;
    bool validMove = false;

    // Rook can move in 4 straight directions: 
    int dx[4] = {1, -1, 0, 0}; // change in x for each direction
    int dy[4] = {0, 0, 1, -1}; // change in y for each direction

    // Check each direction
    for (int dir = 0; dir < 4; dir++)
    {
        int x = xin;
        int y = yin;

        // Step one square at a time in the current direction
        for (int step = 1; step < 8; step++)
        {
            x += dx[dir];
            y += dy[dir];

            // If we're off the board, stop
            if (x < 0 || x >= 8 || y < 0 || y >= 8)
                break;

            uint8_t squareID = PieceID(y, x);

            // If we reached the destination square
            if (x == xf && y == yf)
            {
                // Destination must be empty or contain enemy piece
                if (squareID == 0 ||
                    (currentID < 11 && squareID > 10) ||
                    (currentID > 10 && squareID < 11 && squareID != 0))
                {
                    validMove = true;
                }
                break;
            }

            // If path is blocked, this direction is done
            if (squareID != 0)
                break;
        }

        // No need to check other directions if valid move already found
        if (validMove) break;
    }

    // If a valid path to the destination was found, make the move
    if (validMove)
    {
        res = placePiece(yin, xin, yf, xf, currentID);
    }

    return res;
}

/*

Making queen move FUNCTION

 - Purpose?!?!

  - Handles all queen moving functionality/legality

Input parameters: xin, yin, xf, yf

Return? 1 if success ; 0 if fail -> make the move?

How does it work??!?!

  Call makebishop move
  Call makerook move
  If either function is a 1 - > it is LEGAL !!


*/

uint8_t makeQueenMove(int yin, int xin,int yf, int xf) {
  uint8_t res = 0;

  res += makeBishopMove(yin, xin, yf, xf); 
  res += makeRookMove(yin, xin, yf, xf);

  return res;
  
}

/*

MAKING KING MOVE FUNCTION....

 - What's the purpose -> handle all moves for the king

 Input parameters ; yin, xin, xf, yf 
 Output ; 1 if success -> 0 if fail ... if success, also make the move


 - How does the whole thing work??

  1. Retrieves the current piece at the starting position and the piece at the target square
  2. Verifies that the destination is either empty or occupied by an enemy piece.
  3. Checks all 8 possible directions a king can move one square:
 4. If the movement matches any of those one-square directions, the function calls `placePiece()` and returns `1`.
 5. Otherwise, it returns `0`.

*/

uint8_t makeKingMove(int yin, int xin,int yf, int xf) {

    uint8_t currentID = PieceID(yin, xin);     // Current piece at origin
    uint8_t futureID  = PieceID(yf, xf);       // Target square contents
    uint8_t res = 0;

    // Valid if target is empty OR contains enemy piece
    bool whitePiece = (currentID < 11 && currentID != 0);
    bool blackPiece = (currentID > 10);
    bool isEnemyTarget = (whitePiece && futureID > 10) || (blackPiece && futureID < 11 && futureID != 0);

    if (futureID == 0 || isEnemyTarget)
    {
        int dx = xf - xin;
        int dy = yf - yin;

        // King can move one square in any direction: horizontal, vertical, diagonal
        if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1))
        {
            // Must exclude 0,0 which means "no movement"
            if (dx != 0 || dy != 0)
            {
                res = placePiece(yin, xin, yf, xf, currentID);
            }
        }
    }

    return res;
}

/**
 * Function: isInCheck
 * -------------------
 * This function checks if a given king (either white or black) is in check.
 * It iterates through all board positions to determine if any opposing piece 
 * can legally move to the king's position.
 * 
 * Parameters:
 *   - pieceNum: The piece number representing the king to check (10 for white, 20 for black).
 * 
 * Returns:
 *   - true if the king is in check, false otherwise.
 * 
 * How it works:
 *   1. Identifies the position of the given king using findPiece(pieceNum).
 *   2. Iterates through every position on the board to check for potential attacks.
 *   3. Checks if any opponent piece (pawn, knight, bishop, rook, queen, or king) 
 *      has a valid move to the king's position.
 *   4. If a valid attacking move is found, sets res to true and prints "Check".
 *   5. Resets the check flag before returning the result.
 */

bool isInCheck(){
    check = true;
    bool res = false;
    uint8_t xin = 0, yin = 0;
    uint8_t yf = 0, xf = 0;
    uint8_t resNum = 0;

    if (bot && !needtoCheck) return false;

    if (needtoCheck)
    {
        findPiece(20);
        playerKing = 20;
    }

    findPiece(playerKing);
    xin = xpos;
    yin = ypos;

    int attackerIDs[6] = {0}; // Will be filled based on king color

    if (playerKing == 10) // white king
    {
        attackerIDs[0] = 11; // pawn
        attackerIDs[1] = 12; // knight
        attackerIDs[2] = 13; // bishop
        attackerIDs[3] = 15; // rook
        attackerIDs[4] = 19; // queen
        attackerIDs[5] = 20; // king
    }
    else // black king
    {
        attackerIDs[0] = 1;
        attackerIDs[1] = 2;
        attackerIDs[2] = 3;
        attackerIDs[3] = 5;
        attackerIDs[4] = 9;
        attackerIDs[5] = 10;
    }

    for (int i = 0; i < 8 && !res; i++)
    {
        for (int j = 0; j < 8 && !res; j++)
        {
            yf = i;
            xf = j;

            if (chessboardNum[yf][xf] == attackerIDs[0]) // pawn
            {
                if (pawnTakes(yin, xin, yf, xf))
                    return true;
            }

            if (chessboardNum[yf][xf] == attackerIDs[1]) // knight
            {
                if (makeKnightMove(yin, xin, yf, xf))
                    return true;
            }

            if (chessboardNum[yf][xf] == attackerIDs[2]) // bishop
            {
                if (makeBishopMove(yin, xin, yf, xf))
                    return true;
            }

            if (chessboardNum[yf][xf] == attackerIDs[3]) // rook
            {
                if (makeRookMove(yin, xin, yf, xf))
                    return true;
            }

            if (chessboardNum[yf][xf] == attackerIDs[4]) // queen
            {
                if (makeQueenMove(yin, xin, yf, xf))
                    return true;
            }

            if (chessboardNum[yf][xf] == attackerIDs[5]) // enemy king
            {
                if (makeKingMove(yin, xin, yf, xf))
                {
                    invalidMove = true;
                    break;
                }
            }
        }
    }

    check = false;
    return res;
}

/*


Stalemate functionality 

  - Purpose
    * Checks if the player is in a stalemate position

  - Inputs? None. But uses the following global variables

    a) playerKing: the king being evaluated (10 = white, 20 = black)
    b) currentx, currenty, futurex, futurey: current/future move tracking
  
  - Outputs 

    Doesn't modify the board
  
  - Return

    - True if stalemate
    - False if not stalemate


*/
bool isStalemate() {
    uint8_t xin = currentx;
    uint8_t yin = currenty;
    uint8_t xf = futurex;
    uint8_t yf = futurey;
    uint8_t res = 0;
    uint8_t moveCount = 0;
    uint8_t currentID = PieceID(yin, xin);
    uint8_t futureID = PieceID(yf, xf);
    uint8_t currentIDs;

    bool pieceCanMove = false;
    bool canKingMove = false;
    bool isStale = false;
    bool notValid = false;

    check = true;

    if (bot) return false;

    // Pawn move simulation
    if (currentID == 1 || currentID == 11)
    {
        if (makePawnMove(yin, xin, yf, xf)) moveCount = 0;
    }

    // If pawn is being captured or involved
    if (futureID == 1 || futureID == 11)
    {
        if (currentID == 1 || currentID == 11) res = makePawnMove(yin, xin, yf, xf);
        else if (currentID == 2 || currentID == 12) res = makeKnightMove(yin, xin, yf, xf);
        else if (currentID == 3 || currentID == 13) res = makeBishopMove(yin, xin, yf, xf);
        else if (currentID == 5 || currentID == 15) res = makeRookMove(yin, xin, yf, xf);
        else if (currentID == 9 || currentID == 19) res = makeQueenMove(yin, xin, yf, xf);
        else if (currentID == 10 || currentID == 20) res = makeKingMove(yin, xin, yf, xf);
        else res = 0;

        if (res == 1) moveCount = 0;
    }

    if (moveCount == 50) isStale = true;
    moveCount++;

    // Get position of the king based on current player
    findPiece(playerKing);
    uint8_t kx = xpos;
    uint8_t ky = ypos;

    // First check if the king has ANY valid move (that doesn't lead to check)
    for (int row = 0; row < 8 && !canKingMove; row++)
    {
        for (int col = 0; col < 8 && !canKingMove; col++)
        {
            saveChessboardNum();
            if (makeKingMove(ky, kx, row, col))
            {
                if (!isInCheck()) canKingMove = true;
            }
            restoreChessboardNum();
        }
    }

    // Now test if ANY other piece can legally move
    for (int fromY = 0; fromY < 8 && !pieceCanMove; fromY++)
    {
        for (int fromX = 0; fromX < 8 && !pieceCanMove; fromX++)
        {
            currentIDs = PieceID(fromY, fromX);
            if ((playerKing == 20 && currentIDs > 10) || (playerKing == 10 && currentIDs < 11 && currentIDs != 0))
            {
                for (int toY = 0; toY < 8 && !pieceCanMove; toY++)
                {
                    for (int toX = 0; toX < 8 && !pieceCanMove; toX++)
                    {
                        check = true;

                        if (currentIDs == 1 || currentIDs == 11) res = makePawnMove(fromY, fromX, toY, toX);
                        else if (currentIDs == 2 || currentIDs == 12) res = makeKnightMove(fromY, fromX, toY, toX);
                        else if (currentIDs == 3 || currentIDs == 13) res = makeBishopMove(fromY, fromX, toY, toX);
                        else if (currentIDs == 5 || currentIDs == 15) res = makeRookMove(fromY, fromX, toY, toX);
                        else if (currentIDs == 9 || currentIDs == 19) res = makeQueenMove(fromY, fromX, toY, toX);
                        else if (currentIDs == 10 || currentIDs == 20) res = makeKingMove(fromY, fromX, toY, toX);
                        else res = 0;

                        if (res == 1 && !invalidMove)
                        {
                            pieceCanMove = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    check = false;

    // Final condition: no king move and no legal piece move
    if (!canKingMove && !pieceCanMove && !notValid)
    {
        isStale = true;
    }

    return isStale;
}

// Sets the chessboardNum to the previous move stored by chessboardNumCheck
// Inputs yin, xin, yf, xf, are all the propesed corrdiantes
// Output none
void undoMove(int yin, int xin, int yf, int xf)
{
  uint32_t prevInit = chessboardNumCheck[yin][xin];
  uint32_t prevFinal = chessboardNumCheck[yf][xf];

  chessboardNum[yin][xin] = prevInit;
  chessboardNum[yf][xf] = prevFinal;

}


/*

IsInCheckMate FUNCTION : 

 - Purpose 

  - Tells you whether or not a function is in checkmate 

Inputs; None, but global variables are used

  - playerKing: the king being evaluated (10 for white, 20 for black)
  - chessboardNum[][]: the current game board
  - xpos, ypos, and other move-related globals
  - check: whether we're in a state of evaluating check

Outputs:


  - True if in checmate ; false otherwise



*/


bool isInCheckmate() 
{
    saveChessboardNum(); // Save current board state

    bool checkmate = true;   // Assume checkmate until disproven
    uint8_t res = 255;       // Result of move attempts
    uint8_t xin, yin, xf, yf;
    uint8_t debug_xin, debug_yin, debug_xf, debug_yf;

    for (int fromY = 0; fromY < 8 && checkmate; fromY++)
    {
        for (int fromX = 0; fromX < 8 && checkmate; fromX++)
        {
            for (int toY = 0; toY < 8 && checkmate; toY++)
            {
                for (int toX = 0; toX < 8 && checkmate; toX++)
                {
                    yin = fromY;
                    xin = fromX;
                    yf = toY;
                    xf = toX;

                    uint8_t currentID = PieceID(yin, xin);

                    // Only evaluate pieces that belong to the current player
                    if ((playerKing == 20 && currentID > 10) || (playerKing == 10 && currentID < 11 && currentID != 0))
                    {
                        saveChessboardNum(); // Save before simulating move

                        // Try all legal move types
                        if ((currentID == 1) || (currentID == 11)) res = makePawnMove(yin, xin, yf, xf);
                        else if ((currentID == 2) || (currentID == 12)) res = makeKnightMove(yin, xin, yf, xf);
                        else if ((currentID == 3) || (currentID == 13)) res = makeBishopMove(yin, xin, yf, xf);
                        else if ((currentID == 5) || (currentID == 15)) res = makeRookMove(yin, xin, yf, xf);
                        else if ((currentID == 9) || (currentID == 19)) res = makeQueenMove(yin, xin, yf, xf);
                        else if ((currentID == 10) || (currentID == 20)) res = makeKingMove(yin, xin, yf, xf);
                        else res = 0;

                        if (res == 1)
                        {
                            // Simulate the move and check if king is still in check
                            if (!isInCheck())
                            {
                                checkmate = false;
                                debug_yin = yin;
                                debug_xin = xin;
                                debug_yf = yf;
                                debug_xf = xf;
                                restoreChessboardNum(); // Return board to original state
                                break;
                            }
                        }

                        restoreChessboardNum(); // Always restore after sim
                    }
                }
            }
        }
    }

    // Final check: if king is not even in check to begin with
    if (!isInCheck()) checkmate = false;

    printcheck = true; // not functionally relevant
    restoreChessboardNum(); // Restore one last time in case of lingering sim state

    return checkmate;
}





/*


MAKE MOVE FUNCTION : 

  - Executes a chess move from one coordinate to another and updates the game state 

  - Furthermore, the function attempts to make a move in the `chessboardNum` array and evaluates the validity of 
    that move.
    It checks legality, executes the move, updates whose turn it is, and evaluates game-ending conditions
    like checkmate and stalemate. If the move exposes the player's king to check (i.e., a discovered check),
    the move is undone.

 - Inputs: 

    yin, xin, xf, yf

  - Outputs

  chessboardNum[][]: board state is updated with the new piece positions
  playerKing: toggled to reflect the current player's king
  invalidMove: flag set to true if move results in discovered check
  whitewon / blackwon: set to 1 if a checkmate is detected after the move



*/

uint8_t makeMove(int yin, int xin,int yf, int xf)
{
  currenty = yin;
  currentx = xin;
  futurey = yf;
  futurex = xf;
  uint8_t currentID = PieceID(yin,xin);
  currentIDGlobal = PieceID(yin,xin); // sets currentID to the initial position selected
  futureIDGlobal = PieceID(yf,xf);
  uint8_t res = 255; // initally set to 255 (for debugging purposes)
  
  
  invalidMove = false; // set the gloabl var to false

  if((currentID == 1) || (currentID == 11)) // if currentID is a pawn
  {
    res = makePawnMove(yin,xin,yf,xf); // move the pawn if possible
    
  }

  if((currentID == 2) || (currentID == 12)) // if currentID is a knight
  {

    res = makeKnightMove(yin,xin,yf,xf); // move the knight if possible

  }

  if((currentID == 3) || (currentID == 13)) // if currentID is a bishop
  {

    res = makeBishopMove(yin,xin,yf,xf); // move the bishop if possible

  }

  if((currentID == 5) || (currentID == 15)) // if currentID is a rook
  {

    res = makeRookMove(yin,xin,yf,xf); // move the rook if possible

  }

  if((currentID == 9) || (currentID == 19)) // if currentID is a queen
  {

    res = makeQueenMove(yin,xin,yf,xf); // move the queen if possible

  }

  if((currentID == 10) || (currentID == 20)) // if currentID is a king
  {

    res = makeKingMove(yin,xin,yf,xf); // move the king if possible

  }

  if(currentID == 0) // if selected piece doesn't exist
  {
    res = 0; // result is automatically 0 since selected piece is nothing
  }

 
 if(playerKing == 20)
 {
  playerKing = 10;
 }
 else {
 playerKing = 20;
 }



if((isInCheck()) && ((((playerKing == 10)) && (chessboardNum[yf][xf] < 11)) || (((playerKing == 20)) && (chessboardNum[yf][xf] < 11)))) // cehces for discovered check once the move is made
{
  undoMove(yin,xin,yf,xf);
  res = 0; // move has to be undone if the move results in a check which is bad since the king is exposed
  invalidMove = true;
}

if(playerKing == 20)
 {
  playerKing = 10;
 }
 else {
 playerKing = 20;
 }





if(!invalidMove && !needtoCheck) // if discovered check is false
{
  chessboardNumCheck[yin][xin] = chessboardNum[yin][xin]; // move the chess piece
  chessboardNumCheck[yf][xf] = chessboardNum[yf][xf]; //move the chess piece
}

if(res == 0)
{
  invalidMove = true;
}

  isInCheckmate(); // checks for mate

  if(isInCheckmate())
  {

    if(chessturn == 1)
      {
        whitewon = 1;
      }
      if(chessturn == 0)
      {
        blackwon = 1;
      }
    
    
  }

  isStalemate(); // checks for stalemate

  isInCheck(); //checks for check

  

  

  //printmyArray(); // prints out the current chessboard
  
  //statusOfBoard(); // prints out teh status of teh board if it is in check , mate or an invalid move has been made

  //printf("\n");

  //printf("\n");

    return res; // returns if a move was made or not

  

  
}





//Have fun creating your own chess games
//Only need to use makeMove(x1,y1,x2,y2) and everything else will be done for you :)
//Happy chessing :)


void TIMG0_IRQHandler(void){
  if((TIMG0->CPU_INT.IIDX) == 1){ // this will acknowledge
    TimerG0counts += 1;
    if(TimerG0counts == 7256)
    {
      TimerG0counts = TimerG0counts;
    }
    
  }
}

void mySysTick_IntArm(uint32_t period, uint32_t priority){
  uint32_t value;
  SysTick->CTRL = 0x00;
  SysTick ->LOAD = period-1;
  value = priority << 30;
  SCB ->SHP[1] = SCB->SHP[1]&(~0xC0000000);
  SysTick->VAL = 0;
  SysTick->CTRL = 0x00000007;
}


/*


Function: JOYSTICK READINGS

 - Purpose

  - Handles cursor movement using joystick input and performs piece movement on button press 

 - Inputs

  - Uses global variables

    x,y as joystick readings 
    double click for slecting/deselecting 
    yin1, xin1, yf1, xf1 for propossed start and end position 
    player1mode for if human input is active 
    flag and datas from ADC 

 - Outputs

   Pretty much affects everyhting (no direct output)




*/
void joyStickReadings()
{
  uint32_t res;
  res = ButtonIn() - 16; // reads initial button state 
  ADC_InitTriple(ADC1, 4, 5, 6, ADCVREF_VDDA);
  uint32_t temp;
  uint32_t Position;
  
  

    

  // initialize semaphore

  Time = 0;
  __enable_irq();
  while(1){ // waits for a timed semaphore flag 
      // write this

      if(flag)
      {
        flag = 0;
       Position = Convert(datas); // convert to a meaningful position
       GPIOB->DOUTTGL31_0 = RED; // toggle PB26 (minimally intrusive debugging)
    // toggle red LED2 on Port B, PB26
     // convert Data to Position
     // move cursor to top
    // display distance in top row OutFix

    Time++;
    if((Time%15)==0){
      //OutFix(Position);
     
      break;
    }
    }
      }

 uint32_t xtemp;
uint32_t ytemp;
TimerG0counts = 0;



  drawHollowBox();
   while(TimerG0counts != 40000)
 {

 
  xtemp = 4096 - x;
  ytemp = y;

  if(xtemp > 3700)
  {
    if(xarr < 8)
    {

    xarr++;
    xplot+=16;
    

    }

    break;
    
    

  }

  if(xtemp < 300)
  {
    if(xarr > 1)
    {

    xarr--;
    xplot-=16;
    

    }

    break;
    
    

  }

  if(ytemp > 3700)
  {
    if(yarr < 8)
    {

    yarr++;
    yplot+=20;
    

    }

    break;
    
    

  }

  if(ytemp < 300)
  {
    if(yarr > 1)
    {

    yarr--;
    yplot-=20;
    

    }

    break;
    

  }
  if(doubleclick == 2 || player1Mode)
  {
    break;
  }

  if(isInCheckmate())
    {
      if(chessturn == 1)
      {
        whitewon = 1;
      }
      if(chessturn == 0)
      {
        blackwon = 1;
      }
    }
 }

    if((doubleclick == 2) && (agreeddraw != 1) && !isInCheckmate())
  {

    doubleclick = 0;


    if((chessturn == 1) && (chessboardNum[yin1][xin1] > 10))
    {
      
      if(makeMove(yin1, xin1, yf1, xf1) == 1)
      {
        chessturn = 0;
        playerKing = 20;

        if(chessboardNum[yf1][xf1] == 11)
        {

          ST7735_DrawBitmap(xf1*16, yf1*20+17, WhitePawn, 16, 16);

        }

        if(chessboardNum[yf1][xf1] == 12)
        {

          ST7735_DrawBitmap(xf1*16, yf1*20+17, WhiteKnight, 16, 16);

        }

        if(chessboardNum[yf1][xf1] == 13)
        {

          ST7735_DrawBitmap(xf1*16, yf1*20+17, WhiteBishop, 16, 16);

        }

        if(chessboardNum[yf1][xf1] == 15)
        {

          ST7735_DrawBitmap(xf1*16, yf1*20+17, WhiteRook, 16, 16);

        }

        if(chessboardNum[yf1][xf1] == 19)
        {

          ST7735_DrawBitmap(xf1*16, yf1*20+17, WhiteQueen, 16, 16);

        }

        if(chessboardNum[yf1][xf1] == 20)
        {

          ST7735_DrawBitmap(xf1*16, yf1*20+17, WhiteKing, 16, 16);

        }

        
        if(!invalidMove)
        {

          if(whiteOrBlack[yin1][xin1] == 1)
          {
            ST7735_FillRect(xin1*16, yin1*20, 16, 20, ST7735_Color565(210, 180, 140));
          }
          else {
          ST7735_FillRect(xin1*16, yin1*20, 16, 20, ST7735_Color565(34, 85, 34));
          }

        }
        else {
        playerKing = 10;
        chessturn = 1;
        }

        if(chessturn == 0 && !invalidMove)
    {
      GPIOA->DOUTSET31_0 = (1 << 15);
      GPIOA->DOUTCLR31_0 = (1 << 16);
      GPIOA->DOUTCLR31_0 = (1 << 17);
    }
    if(chessturn == 1 && !invalidMove){
      GPIOA->DOUTCLR31_0 = (1 << 15);
      GPIOA->DOUTCLR31_0 = (1 << 16);
      GPIOA->DOUTSET31_0 = (1 << 17);
      
    }

    invalidMove = false;
        

        



      }
    }

    if((chessturn == 0) && (chessboardNum[yin1][xin1] < 11) && (chessboardNum[yin1][xin1] != 0))
    {
      
      if(makeMove(yin1, xin1, yf1, xf1) == 1)
      {
        chessturn = 1;
        playerKing = 10;

         if(chessboardNum[yf1][xf1] == 1)
        {

          ST7735_DrawBitmap(xf1*16, yf1*20+17, BlackPawn, 16, 16);

        }

        if(chessboardNum[yf1][xf1] == 2)
        {

          ST7735_DrawBitmap(xf1*16, yf1*20+17, BlackKnight, 16, 16);

        }

        if(chessboardNum[yf1][xf1] == 3)
        {

          ST7735_DrawBitmap(xf1*16, yf1*20+17, BlackBishop, 16, 16);

        }

        if(chessboardNum[yf1][xf1] == 5)
        {

          ST7735_DrawBitmap(xf1*16, yf1*20+17, BlackRook, 16, 16);

        }

        if(chessboardNum[yf1][xf1] == 9)
        {

          ST7735_DrawBitmap(xf1*16, yf1*20+17, BlackQueen, 16, 16);

        }

        if(chessboardNum[yf1][xf1] == 10)
        {

          ST7735_DrawBitmap(xf1*16, yf1*20+17, BlackKing, 16, 16);

        }

        
        
        if(!invalidMove)
        {

          if(whiteOrBlack[yin1][xin1] == 1)
          {
            ST7735_FillRect(xin1*16, yin1*20, 16, 20, ST7735_Color565(210, 180, 140));
          }
          else {
          ST7735_FillRect(xin1*16, yin1*20, 16, 20, ST7735_Color565(34, 85, 34));
          }

        }
        else {
        playerKing = 20;
        chessturn = 0;
        }

        if(chessturn == 0 && !invalidMove)
    {
      GPIOA->DOUTSET31_0 = (1 << 15);
      GPIOA->DOUTCLR31_0 = (1 << 16);
      GPIOA->DOUTCLR31_0 = (1 << 17);
      
    }
     if(chessturn == 1 && !invalidMove){
      GPIOA->DOUTCLR31_0 = (1 << 15);
      GPIOA->DOUTCLR31_0 = (1 << 16);
      GPIOA->DOUTSET31_0 = (1 << 17);

      
      
    }

    

    
        

        invalidMove = false;



      }
    }
    
    if(!invalidMove)
    {
      TimerG0counts = 0;
      mySysTick_IntArm(7256, 0);
        TimerG0_IntArm(7256, 0, 0);
        if(chessboardNum[yf1][xf1] == 12 || chessboardNum[yf1][xf1] == 2)
        {
          Sound_Start(2, vol);
          soundpause = 40;
        }
        else if (chessboardNum[yf1][xf1] == 13 || chessboardNum[yf1][xf1] == 3 || chessboardNum[yf1][xf1] == 15 || chessboardNum[yf1][xf1] == 5 || chessboardNum[yf1][xf1] == 19 || chessboardNum[yf1][xf1] == 9) {
          Sound_Start(1, vol);
          soundpause = 20;
        }
        else {
        Sound_Start(0, vol);
        soundpause = 4;
        }
        Sound_Init();
      while(TimerG0counts != soundpause)
      {

        
        
      }
      mySysTick_IntArm(0, 0);
        TimerG0_IntArm(0, 1, 0);
      TimerG0counts = 0;
    }
  }
}



  

  

    


void setup(void)
{
   uint16_t lightBrown = ST7735_Color565(210, 190, 140);   // Example Tan
uint16_t darkgreen = ST7735_Color565(34, 85, 34);
  
  uint32_t buttonclicked = 0;
  __enable_irq();
  ADC_InitTriple(ADC1, 4, 5, 6, ADCVREF_VDDA);
  resetBoards();
  ST7735_FillScreen(ST7735_WHITE);
   doubleclick = 2;
  selectedBoxColor = ST7735_YELLOW;
  chessturn = 1;
  TimerG12_IntArm(1333333,0);










ST7735_FillScreen(ST7735_BLACK);  // Clear the screen
  ST7735_SetTextColor(ST7735_YELLOW);
    
  while (!screen0){

    getSwitch = ButtonIn() - 16;
    
      
      if (vol > 2048){
        ST7735_DrawSmallCircle(64, 30, ST7735_WHITE);
        ST7735_DrawSmallCircle(64, 60, ST7735_BLACK);
        ST7735_DrawSmallCircle(64, 90, ST7735_BLACK);  
        ST7735_DrawSmallCircle(64, 120, ST7735_BLACK);    
      }
       

       if (vol <= 2048 ){
        ST7735_DrawSmallCircle(64, 30, ST7735_BLACK);
        ST7735_DrawSmallCircle(64, 60, ST7735_BLACK);
        ST7735_DrawSmallCircle(64, 90, ST7735_BLACK);  
        ST7735_DrawSmallCircle(64, 120, ST7735_WHITE); 
      }
      
    

    if (vol > 2048 && (getSwitch == 1)){

      screen0 = 1;
      chosenLanguage = 5; //E
      

    }

     

     if (vol <= 2048 && (getSwitch == 1)){

      screen0 = 1;
      chosenLanguage = 10; //S
      

    }

    ST7735_SetCursor(3, 3);
    ST7735_OutString("English 2 Players");
    
    ST7735_SetCursor(3, 12);
    ST7735_OutString("Espa\xA4ol 2 jugadores");

  }

  TimerG0counts = 0;
  while(getSwitch != 0)
  {
    getSwitch = ButtonIn() - 16;

  }


  
  __enable_irq();

  ST7735_FillScreen(ST7735_BLACK);
  
  //getSwitch = Switch_In();

  while(getSwitch == 0){

     getSwitch = ButtonIn() - 16;

    if(updateFrame){
      updateFrame = 0;
    
    if (toggle == 0) {
      ST7735_SetTextColor(ST7735_YELLOW);  // Text is visible
    } else {
      ST7735_SetTextColor(ST7735_BLACK);   // Text is invisible (black background)
    }}

    if (chosenLanguage == 5){

      toggle = !toggle; // Flip the toggle for the next frame
      ST7735_SetCursor(3, 2); 
      ST7735_OutString("WELCOME TO CHESS");
      ST7735_SetCursor(3, 12);
      ST7735_OutString("PRESS ANY BUTTON");
      ST7735_SetCursor(6, 14); 
      ST7735_OutString("TO START");
      
      switch(currentFrame){
        case 0:
          ST7735_DrawBitmap(32, 105, rot1, 64, 64);
          if(TimerG0counts > 250)
          {
            currentFrame = 1;
            TimerG0counts = 0;
          }
          break;
        case 1:
          ST7735_DrawBitmap(32, 105, rot3, 64, 64);
          if(TimerG0counts > 250)
          {
            currentFrame = 2;
            TimerG0counts = 0;
          }
          break;
        case 2:
          ST7735_DrawBitmap(32, 105, rot5, 64, 64);
          if(TimerG0counts > 250)
          {
            currentFrame = 3;
            TimerG0counts = 0;
          }
          break;
        case 3:
          ST7735_DrawBitmap(32, 105, rot3, 64, 64);
          if(TimerG0counts > 250)
          {
            currentFrame = 0;
            TimerG0counts = 0;
          }
          break;
      }
      }
      else if (chosenLanguage == 10){

      toggle = !toggle; // Flip the toggle for the next frame
      ST7735_SetCursor(4, 1); 
      ST7735_OutString("BIENVENIDO AL");
      ST7735_SetCursor(8, 3); 
      ST7735_OutString("AJEDREZ");
      ST7735_SetCursor(2, 12);
      ST7735_OutString("PRESIONE CUALQUIER");
      ST7735_SetCursor(8, 13);
      ST7735_OutString("BOT\xA2N");
      ST7735_SetCursor(6, 15); 
      ST7735_OutString("PARA EMPEZAR");
      switch(currentFrame){
        case 0:
          ST7735_DrawBitmap(32, 105, rot1, 64, 64);
          if(TimerG0counts > 250)
          {
            currentFrame = 1;
            TimerG0counts = 0;
          }
          break;
        case 1:
          ST7735_DrawBitmap(32, 105, rot3, 64, 64);
          if(TimerG0counts > 250)
          {
            currentFrame = 2;
            TimerG0counts = 0;
          }
          break;
        case 2:
          ST7735_DrawBitmap(32, 105, rot5, 64, 64);
          if(TimerG0counts > 250)
          {
            currentFrame = 3;
            TimerG0counts = 0;
          }
          break;
        case 3:
          ST7735_DrawBitmap(32, 105, rot3, 64, 64);
          if(TimerG0counts > 250)
          {
            currentFrame = 0;
            TimerG0counts = 0;
          }
          break;
      }
      }
           
  }
    
    

















  



      GPIOA->DOUTCLR31_0 = (1 << 15);
      GPIOA->DOUTCLR31_0 = (1 << 16);
      GPIOA->DOUTSET31_0 = (1 << 17);
  
  while(buttonclicked < 1)
  {

    buttonclicked = ButtonIn() - 16;
    
    

  }

  



 
  GPIOA->DOUTSET31_0 = (1 << 17);
  screen0 = 0;





  drawBoard();
  if(whiteOrBlack[0][7] == 1)
  {

    backgroundcolor = lightBrown;



  }
  else {
  backgroundcolor = darkgreen;
  }
  ST7735_DrawBitmap(0, 157, BlackRook, 16,16);
  
  ST7735_DrawBitmap(16, 157, BlackKnight, 16, 16);

  ST7735_DrawBitmap(32, 157, BlackBishop, 16,16);
  
  ST7735_DrawBitmap(64, 157, BlackQueen, 16, 16);

  ST7735_DrawBitmap(48, 157, BlackKing, 16,16);
  
  ST7735_DrawBitmap(80, 157, BlackBishop, 16, 16);

  ST7735_DrawBitmap(96, 157, BlackKnight, 16,16);
  
  ST7735_DrawBitmap(112, 157, BlackRook, 16, 16);

  for(int i = 0; i < 128; i = i +16)
  {
    ST7735_DrawBitmap(i, 137, BlackPawn, 16, 16);
  }


  ST7735_DrawBitmap(0, 17, WhiteRook, 16,16);
  
  ST7735_DrawBitmap(16, 17, WhiteKnight, 16, 16);

  ST7735_DrawBitmap(32, 17, WhiteBishop, 16,16);
  
  ST7735_DrawBitmap(64, 17, WhiteQueen, 16, 16);

  ST7735_DrawBitmap(48, 17, WhiteKing, 16,16);
  
  ST7735_DrawBitmap(80, 17, WhiteBishop, 16, 16);

  ST7735_DrawBitmap(96, 17, WhiteKnight, 16,16);
  
  ST7735_DrawBitmap(112, 17, WhiteRook, 16, 16);

  for(int i = 0; i < 128; i = i +16)
  {
    ST7735_DrawBitmap(i, 37, WhitePawn, 16, 16);
  }
}

void score(void)
{
  uint32_t whitehexscore;
    uint32_t blackhexscore;
    uint32_t count = 0;
    char newline[] = "\n";
    char whiteString[] = " White Score\n";
    char blackString[] = " Black Score\n";
    char whiteStringS[] = " Puntuación blanca\n";
    char blackStringS[] = " Puntuación negra\n";


if(chosenLanguage == 5)
{

  ST7735_FillScreen(ST7735_BLACK);
  whitescore += (2*whitewon + agreeddraw);
  ST7735_SetCursor(50, 50);
  whitehexscore = whitescore + 0x30;
  ST7735_OutChar(whitehexscore);
  ST7735_OutStringTransparent(whiteString);
  blackscore += (2*blackwon + agreeddraw);
  ST7735_SetCursor(100, 100);
  blackhexscore = blackscore + 0x30;
  ST7735_OutChar(blackhexscore);
  ST7735_OutStringTransparent(blackString);

}

else {

  ST7735_FillScreen(ST7735_BLACK);
  whitescore += (2*whitewon + agreeddraw);
  ST7735_SetCursor(50, 50);
  whitehexscore = whitescore + 0x30;
  ST7735_OutChar(whitehexscore);
  ST7735_OutStringTransparent(whiteStringS);
  blackscore += (2*blackwon + agreeddraw);
  ST7735_SetCursor(100, 100);
  blackhexscore = blackscore + 0x30;
  ST7735_OutChar(blackhexscore);
  ST7735_OutStringTransparent(blackStringS);

}
  
 
  agreeddraw = 0;
  blackwon = 0;
  whitewon = 0;

  TimerG0counts = 0;

  while(TimerG0counts != 2000)
  {

  }
}









int main(void) 
{

  

  
GPIOA->DOUT31_0 |= 0x10000000;

  __disable_irq();
  Clock_Init80MHz(0);
  LaunchPad_Init();
   TimerG12_IntArm(1333333,0);
   TimerG0_IntArm(0, 1, 0);
  ST7735_InitR(INITR_REDTAB);
  buttonInit_LEDInit();
  DAC5_Init();
  LED_Init();
  
  
  setup();
 
 
 
 




while(1)
{
  
  if(agreeddraw == 1) {
  ST7735_FillScreen(ST7735_BLUE);
  }
  if(blackwon == 1)
  {

    ST7735_FillScreen(ST7735_BLACK);

  }
  if(whitewon == 1)
  {

    ST7735_FillScreen(ST7735_WHITE);

  }
  if((agreeddraw != 1) && (blackwon != 1) && (whitewon != 1))
  {
    joyStickReadings();
  }
  
  else {

    score();
    

  

  setup();
  }
  
  }
  
  


return 0;

}

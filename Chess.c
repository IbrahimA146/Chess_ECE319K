/**

Hello my name is Ibrahim Aksoy and I'm an absoulte god at coding in c.
Since he would never say that I though I might as well say it and btw my name is Aarav Lakdawala 
Ibrahim Aksoy, Aarav Lakdawala, Sharaf Zaman, and blank (IDK his name Ibrahim) have wrote this equally and fairly (THATS SOO CAP)
Just as a warning I'm an awful speller which is why I love prorgamming so beware of spelling mistakes
We would like to present you the game of chess remastered in its beta fucntionality
Our team is working tirelessly to produce the best chess exprience and we would love your feedback


IbrahimA146 is the gitbub


WITHOUT FURTHER ADO CHESS 

♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖
♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙





♟︎ ♟︎ ♟︎ ♟︎ ♟︎ ♟︎ ♟︎ ♟︎ 
♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜


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

 uint16_t whitehex = 0xFFFF;
 uint16_t blackhex = 0000;
uint16_t chosenhexcolor;
unsigned short backgroundcolor = 0x0000;

uint8_t xin1;
  uint8_t yin1; 
  uint8_t xf1; 
  uint8_t yf1;  

uint8_t chessturn = 1; // 1 = white; 0 = black
uint8_t doubleclick = 0;
uint8_t futureIDGlobal;
uint8_t currentIDGlobal;
uint32_t x;
uint32_t y;
uint32_t xplot;
uint32_t yplot;
uint32_t xarr;
uint32_t yarr;
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

void drawHollowBox()
{
  uint16_t lightBrown = ST7735_Color565(210, 180, 140);   // Example Tan
uint16_t darkBrown = ST7735_Color565(101, 67, 33);  
  ST7735_DrawPixel(xplot, yplot, ST7735_YELLOW);
int i;
int j;

x0to7pre = xprevious / 16;
y0to7pre = yprevious / 20;


 

  if(((whiteOrBlack[y0to7pre][x0to7pre]) == 1) && xprevious != -1) //white
  {

       for(i = xprevious +2; i < xprevious+14; i++)
  {

     ST7735_DrawPixel(i, yprevious, lightBrown);

  }

  for(i = xprevious +2; i < xprevious+14; i++)
  {

     ST7735_DrawPixel(i, yprevious+18, lightBrown);

  }

  for(j = yprevious +1; j < yprevious+18; j++)
  {

     ST7735_DrawPixel(xprevious, j, lightBrown);

  }

  for(j = yprevious+1; j < yprevious+18; j++)
  {

     ST7735_DrawPixel(xprevious +14, j, lightBrown);

  }

  }
  else
  {

  for(i = xprevious +2; i < xprevious+14; i++)
  {

     ST7735_DrawPixel(i, yprevious, darkBrown);

  }

  for(i = xprevious +2; i < xprevious+14; i++)
  {

     ST7735_DrawPixel(i, yprevious+18, darkBrown);

  }

  for(j = yprevious +1; j < yprevious+18; j++)
  {

     ST7735_DrawPixel(xprevious, j, darkBrown);

  }

  for(j = yprevious+1; j < yprevious+18; j++)
  {

     ST7735_DrawPixel(xprevious +14, j, darkBrown);

  }
  
  }

   if((xprevious == xplot) && (yprevious == yplot))
  {

    xprevious = -1;
    yprevious = -1;

  }

   for(i = xplot +2; i < xplot+14; i++)
  {

     ST7735_DrawPixel(i, yplot, ST7735_YELLOW);

  }

  for(i = xplot +2; i < xplot+14; i++)
  {

     ST7735_DrawPixel(i, yplot+18, ST7735_YELLOW);

  }

  for(j = yplot +1; j < yplot+18; j++)
  {

     ST7735_DrawPixel(xplot, j, ST7735_YELLOW);

  }

  for(j = yplot+1; j < yplot+18; j++)
  {

     ST7735_DrawPixel(xplot +14, j, ST7735_YELLOW);

  }
  

 

  xprevious = xplot;
  yprevious = yplot;



  

}

void TIMG12_IRQHandler(void){
  
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    Time++;
    ADC_InTriple(ADC1, &y, &vol, &x);
    flag = 1;
    uint32_t res = ButtonIn();

    if(res >= 16)
  {

    if(doubleclick == 0)
    {
      xin1 = xarr;
      yin1 = yarr;
      doubleclick = 1;
      while(res != 0){res = ButtonIn();};
    }
  }

  if(res >= 16)
  {

    if(doubleclick == 1)
    {
      xf1 = xarr;
      yf1 = yarr;
      doubleclick = 2;
      while(res != 0){res = ButtonIn();};
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
      while((localcount != 5000000) && (res != 4) && (res != 16))
      {
        res = ButtonIn();
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
      while((localcount != 5000000) && (res != 8) && (res != 16))
      {
        res = ButtonIn();
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

  if(res == 1) // undo
  {


    
  }


    // sample 12-bit ADC0 channel 5, slidepot
    // store data into mailbox
    // set the semaphore
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}






void drawBoard()
{

uint16_t lightBrown = ST7735_Color565(210, 180, 140);   // Example Tan
uint16_t darkBrown = ST7735_Color565(101, 67, 33); 


  ST7735_InitR(INITR_REDTAB);
  int i,j;
  int k = 0;
  
  for (i = 0; i< NUM; i++)
  {

    for(j = 0; j < NUM; j++)
    {
      int x = 16*i;
      int y = 20*j;
       if(j%2 != k)
        {
          ST7735_FillRect(x,y,16,20,darkBrown);
        }

    else {
  

        ST7735_FillRect(x,y,16,20,lightBrown);
      
      }
   
    
    
  }

  if(i%2 == 0)
  {
    k = 1;
  }
  else
  {
  k = 0;
  }
 
}
printf("\n");
}
  
// Driver Code 
// Initizizing display and showing the checkered board on hardware screen



/************************************************\

               Mailbox Chess Engine
                      (0x88)

                        by

                 Code Monkey King // NOT BY ME :)

\************************************************/

// headers
#include <stdio.h>

// piece encoding
enum {e, P, N, B, R, Q, K, p, n, b, r, q, k, o};

// ascii pieces
char ascii_pieces[] = ".PNBRQKpnbrqk";

// unicode pieces
char *unicode_pieces[] = {".", "♙", "♘", "♗", "♖", "♕", "♔", "♟︎", "♞", "♝", "♜", "♛", "♚"};

// chess board representation
int board[128] = {
    r, n, b, q, k, b, n, r,  o, o, o, o, o, o, o, o,
    p, p, p, p, p, p, p, p,  o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,  o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,  o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,  o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,  o, o, o, o, o, o, o, o,
    P, P, P, P, P, P, P, P,  o, o, o, o, o, o, o, o,
    R, N, B, Q, K, B, N, R,  o, o, o, o, o, o, o, o
};

// print board
void print_board()
{
    // print new line
    printf("\n");

    // loop over board ranks
    for (int rank = 0; rank < 8; rank++)
    {
        for (int file = 0; file < 16; file++)
        {
            // init square
            int square = rank * 16 + file;
            
            // print ranks
            if (file == 0)
                printf(" %d  ", 8 - rank);
            
            // if square is on board
            if (!(square & 0x88))
                printf("%c ", ascii_pieces[board[square]]);
                //printf("%s ", unicode_pieces[board[square]]);
        }
        
        // print new line every time new rank is encountered
        printf("\n");
    }
    
    // print files
    printf("\n    a b c d e f g h\n\n");
}

// main driver
// Will print out the board with actual text pieces
int main9(void)
{
    print_board();
    printf("♔");
    return 0;
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



//Change 0 to 1 at y = 6 x = 3 once testing is complete for check
/**
 0 = no pieces
 1 = white pawn
 2 = white horse
 3 = white bishop
 5 = white rook
 9 = white queen
 10 = white king
 11 = black pawn
 12 = black horse
 13 = black bishop
 15 = black rook
 19 = black queen
 20 = black king

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


// GOD CHESS BOARD ALL UPDATES ARE KEPT IN HERE

uint8_t chessboardNum[8][8] = {
  {WR,WH,WB,WQ,WK,WB,WH,WR},
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {BR,BH,BB,BQ,BK,BB,BH,BR}


  
    
};


/**uint8_t chessboardNum[8][8] = {
  {WR,WH,WB,WQ,WK,WB,WH,WR},
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {BR,BH,BB,BQ,BK,BB,BH,BR}
    
};
*/

// KEEPS THE PREVIOUS POSITION OF THE BOARD
uint8_t chessboardNumCheck[8][8] = {
  {WR,WH,WB,WQ,WK,WB,WH,WR},
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {BR,BH,BB,BQ,BK,BB,BH,BR}
    
};

//Array in which saveChessboardNum uses()
uint8_t chessboardNumSave[8][8] = {
  {WR,WH,WB,WQ,WK,WB,WH,WR},
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {BR,BH,BB,BQ,BK,BB,BH,BR}
    
};


//SAVES THE CHESS BOARD TO WHAT WAS INPUTED IN chessboardNum[][] into chessboardSave[][]
void saveChessboardNum()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNumSave[i][j] = chessboardNum[i][j]; // puts chessboardNum into chessboardNumSave
        }
    }

}

//RESORES THE CHESS BOARD TO WHAT WAS INPUTED IN chessboardSave[][] into chessboardNum[][]
void restoreChessboardNum()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNum[i][j] = chessboardNumSave[i][j]; // puts chessboardNumSave[][] into chessboardNum[][]
        }
    }

}

//Will print out the array in CIO (aka the software output for strings w/o using serial console)
void printmyArray()
{
  for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%3u ", chessboardNum[i][j]); // %3u to format as unsigned int with width 3
        }
        printf("\n"); // Newline after each row
    }

    
}

//Will find the coordiates of any piece and will store this value in the global variables xpos and ypos
//Input pieceNum
//Output None

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










//Will find the PieceID based on given xin and yin corrdiantes
//Inputs xin yin
//Output ID value stored as num

uint8_t PieceID(int yin, int xin)
{
  uint8_t num = (uint8_t)chessboardNum[yin][xin]; // finds id of the given square and returns it
  return num;

}

//This fucntion will Place a Piece in its new location
//Inputs yin, xin, yf, xf, are all the corrdiantes used to move the piece from its orginal location to its new location. currentID tells us what the piece is
//Output return 1 for traversing fxn (important for isItCheck())

uint8_t placePiece(int yin, int xin, int yf, int xf, uint8_t currentID)
{

  if(!check) // gets the gloabl value of check and sees whether the function is propsing a check search or an actual palcement
  {
    chessboardNum[yin][xin] = 0; // puts 0 in the current value
    chessboardNum[yf][xf] = currentID; // updates the future corrdiante to the current piece id (moving the piece)
    

  }
  return 1;  //still ran even in check or not

  
    

  

    

}

//This fucntion explicaly highlights the niche case of a pawn taking material 
//This function is seperate from makePawnMove() because isItCheck() is only concerned about the king being attackd and a pawn can't attack when directly facing a piece
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output returns res: 1 meaning the move was executed 0 meaning its an invalid move

uint8_t pawnTakes(int yin, int xin, int yf, int xf)
{

  uint8_t currentID = PieceID(yin,xin); // finds current ID value of the position
  uint8_t futureID = PieceID(yf,xf); // finds future ID value of the position
  uint8_t res = 0; // returns 0 if pawnTakes doesnt take any conditionals

  if(((currentID != 0) && ((currentID != 0) && (currentID < 11)) && (futureID > 10)) || (((currentID > 10) && (((futureID < 11)) && (futureID !=0))))) // is it a valid move? THIS FUNCTION DOESNT WEED OUT IF CURRENTID IS A PAWN
  {

     if(((yin - yf)==1) && (((xin - xf) == 1) || ((xf - xin) == 1))) // checks if the direction is a pawn taking 
    {

    
      res = placePiece( yin, xin, yf, xf, currentID);

    }

    if(((yf - yin)==1) && (((xin - xf) == 1) || ((xf - xin) == 1))) // checks if the direction is a pawn taking 
      {

        res = placePiece( yin, xin, yf, xf, currentID); 

      }

  }

 

  return res;
}

//inputs corrdiates of chosen piece and its desitnation. This function accounts all pawn moves execpt en pesant
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output returns res: 1 meaning the move was executed 0 meaning its an invalid move

uint8_t makePawnMove(int yin, int xin, int yf, int xf)
{

  uint8_t currentID = PieceID(yin,xin); // finds current ID value of the position
  uint8_t futureID = PieceID(yf,xf); // finds future ID value of the position
  uint8_t res = 0; // returns 0 if makePawnMove doesnt take any conditionals
  uint8_t temp;

  res = pawnTakes(yin, xin, yf, xf); // calls pawnTakes() and returns result since it is a legal move

  if((currentID == 1) && ((yin - yf)==1) && (futureID == 0) && ((xin - xf)==0)) // Single foward move and checks valildity if currentID is a pawn
  {

    res = placePiece( yin, xin, yf, xf, currentID);

  }


  if((currentID == 11) && ((yf - yin)==1) && (futureID == 0) && ((xin - xf)==0)) // Single foward move and checks valildity if currentID is a pawn
  {

    res = placePiece( yin, xin, yf, xf, currentID);

  }

  if((currentID == 11) && ((yf - yin)==2) && (yin == 1) && (futureID == 0) && ((xin - xf)==0)) // Double foward move at begining and checks valildity if currentID is a pawn
  {
    temp = yf -1;
    temp = PieceID(temp, xf);
    if(temp == 0)
    {

      res = placePiece( yin, xin, yf, xf, currentID);

    }
    


    

  }

  if((currentID == 1) && ((yin - yf)==2) && (yin == 6) && (futureID == 0)&& ((xin - xf)==0)) // Double foward move at begining and checks valildity if currentID is a pawn
  {

    temp = yf +1;
    temp = PieceID(temp, xf);
    if(temp == 0)
    {

      res = placePiece( yin, xin, yf, xf, currentID);

    }

  }

  return res;

  
  
}

//This function accounts for all knight moves
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output returns res: 1 meaning the move was executed 0 meaning its an invalid move

uint8_t makeKnightMove(int yin, int xin,int yf, int xf)
{
  uint8_t currentID = PieceID(yin,xin); // finds current ID value of the position
  uint8_t futureID = PieceID(yf,xf); // finds future ID value of the position
  uint8_t res = 0; // returns 0 if makeKnightMove doesnt take any conditionals

  if((futureID == 0) || (((currentID != 0) && ((currentID < 11)) && (futureID > 10)) || (((currentID > 10) && ((futureID != 0) && (futureID < 11)))))) // is it a valid move? THIS FUNCTION DOESNT WEED OUT IF CURRENTID IS A KNIGHT
  {
    
      if((yf-yin) == 2 && (((xf - xin) == 1) || ((xin - xf) == 1))) // 2 knight moves
      {
        res = placePiece( yin, xin, yf, xf, currentID);

      }

      if((yf-yin) == -2 && (((xf - xin) == 1) || ((xin - xf) == 1))) // 2 knight moves
      {
        res = placePiece( yin, xin, yf, xf, currentID);

      }

      if((yf-yin) == 1 && (((xf - xin) == 2) || ((xin - xf) == 2))) // 2 knight moves
      {
        res = placePiece( yin, xin, yf, xf, currentID);

      }

      if((yf-yin) == -1 && (((xf - xin) == 2) || ((xin - xf) == 2))) // 2 knight moves
      {
        res = placePiece( yin, xin, yf, xf, currentID);

      }

    

  }

  return res;
  




}

//This function accounts for all bishop moves
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output returns res: 1 meaning the move was executed 0 meaning its an invalid move

uint8_t makeBishopMove(int yin, int xin,int yf, int xf)
{

  uint8_t currentID = PieceID(yin,xin); // finds current ID value of the position
  uint8_t futureID = PieceID(yf,xf); // finds future ID value of the position
  uint8_t res = 0; // returns 0 if makeBishopMove doesnt take any conditionals
  uint8_t xtemp1 = xin; // tempVar for initial x val
  uint8_t ytemp1 = yin; //tempVar for initial y val
  uint8_t xtemp2 = xin; // tempVar for initial x val
  uint8_t ytemp2 = yin; //tempVar for initial y val
  uint8_t xtemp3 = xin; // tempVar for initial x val
  uint8_t ytemp3 = yin; //tempVar for initial y val
  uint8_t xtemp4 = xin; // tempVar for initial x val
  uint8_t ytemp4 = yin; //tempVar for initial y val
  uint8_t tempID = currentID; //tempId is initalized to currentID
  bool flag = false; //overall flag if the function hits a conditional
  bool flag1 = true; // flag for when pathway is not empty
  bool flag2 = true; // flag for when pathway is not empty
  bool flag3 = true; // flag for when pathway is not empty
  bool flag4 = true; // flag for when pathway is not empty



  for(int i = 0; i < 8; i++)
  {
    xtemp1 += 1; //checking one possible pathway
    ytemp1 += 1; //checking one possible pathway

    tempID = PieceID(ytemp1,xtemp1); // tempID = to xtemp1 and ytemp1

    if(flag1 && ((xtemp1 == xf) && (ytemp1 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11)))))) // conditional checking whether bisop has made it to its destination
    {
      flag = true; //is a valid move
      break;
    }

    if(tempID != 0) // something is in the way and therefore the bishop can no longer continue on this path
    {

      flag1 = false;
      

    }

    xtemp2 -= 1; // checking one possible pathway
    ytemp2 += 1; // checking one possible pathway

    tempID = PieceID(ytemp2,xtemp2); // tempID = to xtemp2 and ytemp2

    if(flag2 && ((xtemp2 == xf) && (ytemp2 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11)))))) // conditional checking whether bisop has made it to its destination
    {
      flag = true;
      break;
    }

    if(tempID != 0)
    {

      flag2 = false;
      

    }

    

    xtemp3 += 1; // checking one possible pathway
    ytemp3 -= 1; // checking one possible pathway

    tempID = PieceID(ytemp3,xtemp3); // tempID = to xtemp3 and ytemp3

    if(flag3 && ((xtemp3 == xf) && (ytemp3 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11)))))) // conditional checking whether bisop has made it to its destination
    {
      flag = true; //is a valid move
      break;
    }

    if(tempID != 0) // something is in the way and therefore the bishop can no longer continue on this path
    {

      flag3 = false;
      

    }

    

    xtemp4 -= 1; // checking one possible pathway
    ytemp4 -= 1; // checking one possible pathway

    tempID = PieceID(ytemp4,xtemp4); // tempID = to xtemp4 and ytemp4

    if(flag4 && ((xtemp4 == xf) && (ytemp4 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11)))))) // conditional checking whether bisop has made it to its destination
    {
      flag = true; //is a valid move
      break;
    }

    if(tempID != 0) // something is in the way and therefore the bishop can no longer continue on this path
    {

      flag4 = false;
      

    }

  }

  if(flag)
  {

        res = placePiece( yin, xin, yf, xf, currentID); // places bishop if flag is true


  }

  return res;
}

//This function accounts for all rook moves
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output returns res: 1 meaning the move was executed 0 meaning its an invalid move


uint8_t makeRookMove(int yin, int xin,int yf, int xf)
{

  uint8_t currentID = PieceID(yin,xin); // finds current ID value of the position
  uint8_t futureID = PieceID(yf,xf); // finds future ID value of the position
  uint8_t res = 0; // returns 0 if makeBishopMove doesnt take any conditionals
  uint8_t xtemp1 = xin; // tempVar for initial x val
  uint8_t ytemp1 = yin; //tempVar for initial y val
  uint8_t xtemp2 = xin; // tempVar for initial x val
  uint8_t ytemp2 = yin; //tempVar for initial y val
  uint8_t xtemp3 = xin; // tempVar for initial x val
  uint8_t ytemp3 = yin; //tempVar for initial y val
  uint8_t xtemp4 = xin; // tempVar for initial x val
  uint8_t ytemp4 = yin; //tempVar for initial y val
  uint8_t tempID = currentID; //tempId is initalized to currentID
  bool flag = false; //overall flag if the function hits a conditional
  bool flag1 = true; // flag for when pathway is not empty
  bool flag2 = true; // flag for when pathway is not empty
  bool flag3 = true; // flag for when pathway is not empty
  bool flag4 = true; // flag for when pathway is not empty



  for(int i = 0; i < 8; i++)
  {
    xtemp1 += 1; // checking one possible pathway
    ytemp1 += 0; // checking one possible pathway

    tempID = PieceID(ytemp1,xtemp1); // tempID = to xtemp1 and ytemp1

    if(flag1 && ((xtemp1 == xf) && (ytemp1 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11)))))) // conditional checking whether rook has made it to its destination
    {
      flag = true; //is a valid move
      break;
    }

    if(tempID != 0) // something is in the way and therefore the rook can no longer continue on this path
    {

      flag1 = false;
      

    }

    xtemp2 -= 1; // checking one possible pathway
    ytemp2 += 0; // checking one possible pathway

    tempID = PieceID(ytemp2,xtemp2); // tempID = to xtemp2 and ytemp2

    if(flag2 && ((xtemp2 == xf) && (ytemp2 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11)))))) // conditional checking whether rook has made it to its destination
    {
      flag = true; //is a valid move
      break;
    }

    if(tempID != 0) // something is in the way and therefore the rook can no longer continue on this path
    {

      flag2 = false;
      

    }

    

    xtemp3 += 0; // checking one possible pathway
    ytemp3 += 1; // checking one possible pathway

    tempID = PieceID(ytemp3,xtemp3); // tempID = to xtemp3 and ytemp3

    if(flag3 && ((xtemp3 == xf) && (ytemp3 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11)))))) // conditional checking whether rook has made it to its destination
    {
      flag = true; //is a valid move
      break;
    }

    if(tempID != 0) // something is in the way and therefore the rook can no longer continue on this path
    {

      flag3 = false;
      

    }

    

    xtemp4 += 0; // checking one possible pathway
    ytemp4 -= 1; // checking one possible pathway

    tempID = PieceID(ytemp4,xtemp4); // tempID = to xtemp4 and ytemp4

    if(flag4 && ((xtemp4 == xf) && (ytemp4 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11)))))) // conditional checking whether rook has made it to its destination
    {
      flag = true; //is a valid move
      break;
    }

    if(tempID != 0) // something is in the way and therefore the rook can no longer continue on this path
    {

      flag4 = false;
      

    }

  }

  if(flag)
  {

        res = placePiece( yin, xin, yf, xf, currentID); //places rook on future spot if flag is true


  }

  return res;
}

//This function accounts for all queen moves
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output returns res: 1 meaning the move was executed 0 meaning its an invalid move

uint8_t makeQueenMove(int yin, int xin,int yf, int xf)
{
  uint8_t res = 0;

  res += makeBishopMove(yin, xin, yf, xf); // A queen is really a bishop and a rook combined so just call both fxns :)
  res += makeRookMove(yin, xin, yf, xf);

  return res;
  
}

//This function accounts for all king moves execpt casting which will be implemented soon
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output returns res: 1 meaning the move was executed 0 meaning its an invalid move

uint8_t makeKingMove(int yin, int xin,int yf, int xf)
{

  uint8_t currentID = PieceID(yin,xin); // finds current ID value of the position
  uint8_t futureID = PieceID(yf,xf); // finds future ID value of the position
  uint8_t res = 0; // returns 0 if makeBishopMove doesnt take any conditionals



if((futureID == 0) || (((currentID < 11) && (futureID > 10)) || (((currentID > 10) && (futureID < 11))))) //is it a valid move? THIS FUNCTION DOESNT WEED OUT IF CURRENTID IS A KING
{

  // diagional moves

  if(((xf - xin) == 1) && ((yf - yin) ==1))
  {

      res = placePiece( yin, xin, yf, xf, currentID);
  }

  if(((xf - xin) == 1) && ((yin - yf) ==1))
  {
      
      res = placePiece( yin, xin, yf, xf, currentID);    
  }

  if(((xin - xf) == 1) && ((yf - yin) ==1))
  {
      
      res = placePiece( yin, xin, yf, xf, currentID);
  }

  if(((xin - xf) == 1) && ((yin - yf) ==1))
  {
      
      res = placePiece( yin, xin, yf, xf, currentID);
  }

  // straight moves

  if(((xf - xin) == 1) && ((yf - yin) ==0))
  {
      
      res = placePiece( yin, xin, yf, xf, currentID);
  }

  if(((xf - xin) == 0) && ((yin - yf) ==1))
  {
      
      res = placePiece( yin, xin, yf, xf, currentID);    
  }

  if(((xin - xf) == 0) && ((yf - yin) ==1))
  {
      
      res = placePiece( yin, xin, yf, xf, currentID);
  }

  if(((xin - xf) == 1) && ((yin - yf) ==0))
  {
      
      res = placePiece( yin, xin, yf, xf, currentID);
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

bool isInCheck()
{
  check = true; // global variable check is true since the function is in checking for a possible "check"
  bool res = false; //result is flase if a "check" dosen't exsist
  uint8_t xin = 0; // initial position setup
  uint8_t yin = 0; // initial position setup
  uint8_t yf = 0; // initial position setup
  uint8_t xf = 0; // initial position setup
  uint8_t resNum = 0; //temporary variable that will store whatever moving piece fxn is called
  findPiece(playerKing); // will find where opposing king is and store it in global var xpos and ypos

  xin = xpos; // sets xin = xpos (locally storing a global var)
  yin = ypos; // sets yin = ypos (locally storing a global var)


  if(playerKing == 10) //opposing king is white
  {
    for(int i = 0; i < 8; i++)
    {
      if(res) //break if check is true
      {
        break;
      }

      for(int j = 0; j < 8; j++) // finding all future moves
      {
        yf = i; // sets yf to val of i
        xf = j; // sets xf to val of j

        resNum = pawnTakes(ypos, xpos, yf, xf); // the king is pretending to traverse in a pawnTakes pathway (diagolly one square)
        if((chessboardNum[yf][xf] == 11) && (resNum == 1)) // if there is a pawn attacking the king like the fxn pawnTakes implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          break;
        }

        resNum = makeKnightMove(ypos, xpos,  yf,  xf); // the king is pretending to traverse in a makeKnightMove pathway
        if((chessboardNum[yf][xf] == 12) && (resNum == 1)) // if there is a knight attacking the king like the fxn makeKnightMove implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          break;
        }

        resNum = makeBishopMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeBishopMove pathway
        if((chessboardNum[yf][xf] == 13) && (resNum == 1)) // if there is a bishop attacking the king like the fxn makeBishopMove implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          break;
        }

        resNum = makeRookMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeRookMove pathway
        if((chessboardNum[yf][xf] == 15) && (resNum == 1)) // if there is a rook attacking the king like the fxn makeRookMove implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          break;
        }

        resNum = makeQueenMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeQueenMove pathway
        if((chessboardNum[yf][xf] == 19) && (resNum == 1)) // if there is a queen attacking the king like the fxn makeQueenMove implements the conditional is true
        {
        {
          res = true; // "check" is true and break out of the fxn
          break;
        }

        resNum = makeKingMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeKingMove pathway
        if((chessboardNum[yf][xf] == 20) && (resNum == 1)) // if there is a king attacking the king like the fxn makeKingMove implements the conditional is true
        {
          invalidMove = true; // a global variable is set to true that a discovered check happens which indicates an invalid move
          break;
        }
      }
    }
  }
}

  if(playerKing == 20)
  {
    for(int i = 0; i < 8; i++)
    {
      if(res) //break if check is true
      {
        break;
      }

      for(int j = 0; j < 8; j++) // finding all future moves
      {
        yf = i; // sets yf to val of i
        xf = j; // sets xf to val of j

        resNum = pawnTakes(ypos, xpos, yf, xf); // the king is pretending to traverse in a pawnTakes pathway (diagolly one square)
        if((chessboardNum[yf][xf] == 1) && (resNum == 1)) // if there is a pawn attacking the king like the fxn pawnTakes implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          break;
        }

        resNum = makeKnightMove(ypos, xpos,  yf,  xf); // the king is pretending to traverse in a makeKnightMove pathway
        if((chessboardNum[yf][xf] == 2) && (resNum == 1)) // if there is a knight attacking the king like the fxn makeKnightMove implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          break;
        }

        resNum = makeBishopMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeBishopMove pathway
        if((chessboardNum[yf][xf] == 3) && (resNum == 1)) // if there is a bishop attacking the king like the fxn makeBishopMove implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          break;
        }

        resNum = makeRookMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeRookMove pathway
        if((chessboardNum[yf][xf] == 5) && (resNum == 1)) // if there is a rook attacking the king like the fxn makeRookMove implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          break;
        }

        resNum = makeQueenMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeQueenMove pathway
        if((chessboardNum[yf][xf] == 9) && (resNum == 1)) // if there is a queen attacking the king like the fxn makeQueenMove implements the conditional is true
        {
        {
          res = true; // "check" is true and break out of the fxn
          break;
        }

        resNum = makeKingMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeKingMove pathway
        if((chessboardNum[yf][xf] == 10) && (resNum == 1)) // if there is a king attacking the king like the fxn makeKingMove implements the conditional is true
        {
          invalidMove = true; // a global variable is set to true that a discovered check happens which indicates an invalid move
          break;
        }
      }
    }
  }
}

 
  check = false; // check fxn is done

  return res;

}

bool isStalemate()
{
  uint8_t xin = currentx;
  uint8_t yin = currenty;
  uint8_t xf = futurex;
  uint8_t yf = futurey;
  uint8_t movecount50 = 0;
  uint8_t currentIDs;
  uint8_t futureIDs;
  uint8_t currentID = PieceID(yin,xin);
  uint8_t futureID = PieceID(yf,xf);
  uint8_t res = 0;
  bool isStalemate = false;
  bool pieceCanMove = false;
  bool notValid = false;
  check = true;

  if((currentID == 1) || (currentID == 11)) // if currentID is a pawn
  {
    res = makePawnMove(yin,xin,yf,xf); // move the pawn if possible
    if(res == 1)
    {
      movecount50 = 0;
    } 
  }

  if((futureID == 1) || (futureID == 11))
  {

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

    if(res == 1)
    {
      movecount50 = 0;
    }
  }
  
  if(movecount50 == 50)
  {
    isStalemate = true;
  }
  movecount50++;

  if(playerKing == 20)
  {
    uint8_t xking;
    uint8_t yking;
    uint8_t pieceId;
    findPiece(20);

    xking = xpos;
    yking = ypos;
    bool checking = true;
    bool canKingMoveBeMade = false;

     for(int i = 0; i < 7; i++)
     {
      if(canKingMoveBeMade)
      {
        break;
      }
      for(int j = 0; j < 7; j++)
      {
       
        saveChessboardNum();

        

        res = makeKingMove(yking,xking,i,j);
        
        if(res == 1)
        {
          checking = isInCheck();
        }
          restoreChessboardNum();

        

        if(!checking)
        {
          canKingMoveBeMade = true;
          break;
        }

      }
     }

     for(int i = 0; i < 7; i++)
     {
      if(pieceCanMove)
      {
        break;
      }
      for(int j = 0; j < 7; j++)
      {
        if(pieceCanMove)
        {
          break;
        }
        for(int k = 0; k < 7; k++)
        {
          if(pieceCanMove)
          {
            break;
          }
          for(int l = 0; l < 7; l++)
          {
            yin = i; // sets temp var to a value
            xin = j; // sets temp var to a value
            yf = k; // sets temp var to a value
            xf = l; // sets temp var to a value
            currentIDs = PieceID(yin, xin);
            check = true;

            if(currentIDs > 10)
            {
              if((currentIDs == 1) || (currentIDs == 11)) // if currentID is a pawn
              {
                res = makePawnMove(yin,xin,yf,xf); // move the pawn if possible
    
              }

              if((currentIDs == 2) || (currentIDs == 12)) // if currentID is a knight
              {

                res = makeKnightMove(yin,xin,yf,xf); // move the knight if possible

              }

              if((currentIDs == 3) || (currentIDs == 13)) // if currentID is a bishop
              {

                res = makeBishopMove(yin,xin,yf,xf); // move the bishop if possible

              }

              if((currentIDs == 5) || (currentIDs == 15)) // if currentID is a rook
              {

                res = makeRookMove(yin,xin,yf,xf); // move the rook if possible

              }

              if((currentIDs == 9) || (currentIDs == 19)) // if currentID is a queen
              {

                res = makeQueenMove(yin,xin,yf,xf); // move the queen if possible

              }

              if((currentIDs == 10) || (currentIDs == 20)) // if currentID is a king
              {

                res = makeKingMove(yin,xin,yf,xf); // move the king if possible

              }

              if(currentIDs == 0) // if selected piece doesn't exist
              {
                res = 0; // result is automatically 0 since selected piece is nothing
              }

              if((res == 1) && !invalidMove)
              {
                pieceCanMove = true;
                break;

              }



            }
            else {
            //notValid = true;
            }

          }
        }
      }
     }





     check = false;



     if(!canKingMoveBeMade && !pieceCanMove)
     {
      isStalemate = true;
     } 


  }




  if(playerKing == 10)
  {
    uint8_t xking;
    uint8_t yking;
    uint8_t pieceId;
     findPiece(10);
     check = false;

     xking = xpos;
     yking = ypos;
     bool checking = true;
     bool canKingMoveBeMade = false;

     for(int i = 0; i < 7; i++)
     {
      if(canKingMoveBeMade)
      {
        break;
      }
      for(int j = 0; j < 7; j++)
      {
        saveChessboardNum();

          

        res = makeKingMove(yking,xking,i,j);
        if(res == 1)
        {
          checking = isInCheck();
        }
          restoreChessboardNum();

           

        if(!checking)
        {
          canKingMoveBeMade = true;
          break;
        }

      }
     }

     for(int i = 0; i < 7; i++)
     {
      if(pieceCanMove)
      {
        break;
      }
      for(int j = 0; j < 7; j++)
      {
        if(pieceCanMove)
        {
          break;
        }
        for(int k = 0; k < 7; k++)
        {
          if(pieceCanMove)
          {
            break;
          }
          if(pieceCanMove)
          {
            break;
          }
          for(int l = 0; l < 7; l++)
          {
            yin = i; // sets temp var to a value
            xin = j; // sets temp var to a value
            yf = k; // sets temp var to a value
            xf = l; // sets temp var to a value
            currentIDs = PieceID(yin, xin);
            check = true;

            if(currentIDs < 11)
            {
              if((currentIDs == 1) || (currentIDs == 11)) // if currentID is a pawn
              {
                res = makePawnMove(yin,xin,yf,xf); // move the pawn if possible
    
              }

              if((currentIDs == 2) || (currentIDs == 12)) // if currentID is a knight
              {

                res = makeKnightMove(yin,xin,yf,xf); // move the knight if possible

              }

              if((currentIDs == 3) || (currentIDs == 13)) // if currentID is a bishop
              {

                res = makeBishopMove(yin,xin,yf,xf); // move the bishop if possible

              }

              if((currentIDs == 5) || (currentIDs == 15)) // if currentID is a rook
              {

                res = makeRookMove(yin,xin,yf,xf); // move the rook if possible

              }

              if((currentIDs == 9) || (currentIDs == 19)) // if currentID is a queen
              {

                res = makeQueenMove(yin,xin,yf,xf); // move the queen if possible

              }

              if((currentIDs == 10) || (currentIDs == 20)) // if currentID is a king
              {

                res = makeKingMove(yin,xin,yf,xf); // move the king if possible

              }

              if(currentIDs == 0) // if selected piece doesn't exist
              {
                res = 0; // result is automatically 0 since selected piece is nothing
              }

              if((res == 1) && !invalidMove)
              {
                pieceCanMove = true;
                break;

              }
            }
            else {
            //notValid = true;
            }
          }
        }
      }
     }





     check = false;



     if(!canKingMoveBeMade && !pieceCanMove && !notValid)
     {
      isStalemate = true;
     } 


  }



  return isStalemate;
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


// Will check every possible input move and output move and see whether check becomes false in any case
// Inputs none
// Output true if checkmate is true and false if checkmate isnt true


bool isInCheckmate()
{

  saveChessboardNum(); // Saves chessboard (not needed but used for testing)
  uint8_t res = 255; // initial value set to 255 (debugging purposes to see if the code ever reaches a conditional and sets it to 0 or 1)
  bool checkmate = true; // checkmate is true until proven false
  printcheck = false; // useless line
  bool iteratteloop = false; //useless line
  

  uint8_t xin; // initial setup for temp var
  uint8_t yin; // initial setup for temp var
  uint8_t yf; // initial setup for temp var
  uint8_t xf; // initial setup for temp var

  uint8_t xin_1; // initial setup for temp var (debugging purposes)
  uint8_t yin_1; // initial setup for temp var (debugging purposes)
  uint8_t yf_1; // initial setup for temp var (debugging purposes)
  uint8_t xf_1; // initial setup for temp var (debugging purposes)



  for(int i = 0; i < 8; i++)
  {
    if(!checkmate) // breaks if checkmate is false
              {
                break;
              }
    for(int j = 0; j < 8; j++) 
    {
      if(!checkmate) // breaks if checkmate is false
              {

                break;
              }
      for(int k = 0; k < 8; k++)
      {
        if(!checkmate) // breaks if checkmate is false
              {
                break;
              }
        for(int l = 0; l < 8; l++) // check all 4096 differnt possibilites of moves that could be made for initial moves and final moves (most are illegal :( )
        {

          yin = i; // sets temp var to a value
          xin = j; // sets temp var to a value
          yf = k; // sets temp var to a value
          xf = l; // sets temp var to a value

          uint8_t currentID = PieceID(yin,xin); // currentID = corrdiates of yin and xin

          if(((currentID >10) && (playerKing == 20)) || ((currentID <11) && (playerKing == 10))) // checks if attacked king can be saved by moving one of its own pieces (essentally looking 1 move ahead)
          {

            if((currentID == 1) || (currentID == 11)) // is it a pawn
            {
              saveChessboardNum(); // saves chessboard in this state
              res = makePawnMove(yin,xin,yf,xf); // makes a pawn move and checks validity
              if(res == 1) // conditional checking validty of the move
              {
                checkmate = isInCheck(); // checkmate = chceck + one addional move made
                restoreChessboardNum(); // restore chessboard to its orginal state
                if(!checkmate) // breaks if checkmate is false
                  {

                    yin_1 = yin;
                    xin_1 = xin;
                    yf_1 = yf;
                    xf_1 = xf;
                    break;
                  }
              }
              
    
            }

          if((currentID == 2) || (currentID == 12)) // is it a knight
            {
              saveChessboardNum(); // saves chessboard in this state
              res = makeKnightMove(yin,xin,yf,xf); // makes a knight move and checks validity
              if(res == 1) // conditional checking validty of the move
              {
                checkmate = isInCheck(); // checkmate = chceck + one addional move made
                restoreChessboardNum(); // restore chessboard to its orginal state
                if(!checkmate) // breaks if checkmate is false
                  {
                    yin_1 = yin;
                    xin_1 = xin;
                    yf_1 = yf;
                    xf_1 = xf;
                    break;
                  }
              }

            }

          if((currentID == 3) || (currentID == 13))
            {
              saveChessboardNum(); // saves chessboard in this state
              res = makeBishopMove(yin,xin,yf,xf); // makes a bishop move and checks validity
              if(res == 1) // conditional checking validty of the move
              {
                checkmate = isInCheck(); // checkmate = chceck + one addional move made
                restoreChessboardNum(); // restore chessboard to its orginal state
                if(!checkmate) // breaks if checkmate is false
                  {
                    yin_1 = yin;
                    xin_1 = xin;
                    yf_1 = yf;
                    xf_1 = xf;
                    break;
                  }
              }

            }

          if((currentID == 5) || (currentID == 15))
            {
              saveChessboardNum(); // saves chessboard in this state
              res = makeRookMove(yin,xin,yf,xf); // makes a rook move and checks validity
              if(res == 1) // conditional checking validty of the move
              {
                checkmate = isInCheck(); // checkmate = chceck + one addional move made
                restoreChessboardNum(); // restore chessboard to its orginal state
                if(!checkmate) // breaks if checkmate is false
                  {
                    yin_1 = yin;
                    xin_1 = xin;
                    yf_1 = yf;
                    xf_1 = xf;
                    break;
                  }
              }

            }

          if((currentID == 9) || (currentID == 19))
            {
              saveChessboardNum(); // saves chessboard in this state
              res = makeQueenMove(yin,xin,yf,xf); // makes a queen move and checks validity
              if(res == 1) // conditional checking validty of the move
              {
                checkmate = isInCheck(); // checkmate = chceck + one addional move made
                restoreChessboardNum(); // restore chessboard to its orginal state
                if(!checkmate) // breaks if checkmate is false
                  {
                    yin_1 = yin;
                    xin_1 = xin;
                    yf_1 = yf;
                    xf_1 = xf;
                    break;
                  }
              }

            }

          if((currentID == 10) || (currentID == 20))
            {
              saveChessboardNum(); // saves chessboard in this state
              res = makeKingMove(yin,xin,yf,xf); // makes a king move and checks validity
              if(res == 1) // conditional checking validty of the move
              {
                checkmate = isInCheck(); // checkmate = chceck + one addional move made
                restoreChessboardNum(); // restore chessboard to its orginal state
                if(!checkmate) // breaks if checkmate is false
                  {
                    yin_1 = yin;
                    xin_1 = xin;
                    yf_1 = yf;
                    xf_1 = xf;
                    break;
                  }
              }
            }
          }
        }
      }
    }
  }

  if(!isInCheck())
  {
    checkmate = false;
  }


  printcheck = true; // not needed

  //check = false;
  restoreChessboardNum(); // not needed but used for debugging
  return checkmate;
  

}

// Prints the state of the board whether its in check, checkmate, or an invalid move has been made
// Input none
// Output none

void statusOfBoard()
{
  bool checkprint = false; // sets checkprint false until proven true
  for(int i = 0; i < 4; i++) // looping to make sure it works (not needed but more testing needs to happen)
  {
    
    if(isInCheckmate()) // runs checkmate and sees result
    {

      printf("Checkmate");
      printf("\n");
      break;

    }

    if(isStalemate())
    {

      printf("Stalemate");
      printf("\n");
      break;

    }

    if(isInCheck() && !invalidMove && !isInCheckmate()) // determines wheter a "true check" has occured meaning its a clean check and no otehr invalid moves created this check
    {
      checkprint = true;
      
    }

  }

  if(!isInCheckmate() && checkprint) // if check is true and checkmate is false then check is true
  {
    printf("Check");
    printf("\n");

  }

  if(invalidMove) // if an invalid move is made it will show up here
  {
    printf("Invalid Move");
    printf("\n");
  }

  
}





//This function will make a move stored in chessboardNum
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output returns res: 1 meaning the move was executed 255 meaning its an invalid move 0 meaning that piece was found but couldnt be moved
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


if((isInCheck()) && ((((playerKing == 10)) && (chessboardNum[yf][xf] < 11)) || (((playerKing == 20)) && (chessboardNum[yf][xf] > 10)))) // cehces for discovered check once the move is made
{
  undoMove(yin,xin,yf,xf); // move has to be undone if the move results in a check which is bad since the king is exposed
  invalidMove = true;
}

 if(playerKing == 20)
 {
  playerKing = 10;
 }
 else {
 playerKing = 20;
 }


if(!invalidMove) // if discovered check is false
{
  chessboardNumCheck[yin][xin] = chessboardNum[yin][xin]; // move the chess piece
  chessboardNumCheck[yf][xf] = chessboardNum[yf][xf]; //move the chess piece
}

if(res == 0)
{
  invalidMove = true;
}

  isInCheckmate(); // checks for mate

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

int main10(void)
{
    /*
    makeMove(6,0,4,0);
    
    makeMove(7,0,5,0);
    
    //makeMove(1,3,3,3);
    
    makeMove(7,1,5,2);
    
    makeMove(7,2,5,3);
    
    makeMove(5,0,5,7);
    
    makeMove(5,0,5,1);
    
    makeMove(6,3,4,3);
    
    makeMove(7,3,5,3);
    
    makeMove(5,3,2,0);
    
    makeMove(2,0,2,4);
    
    makeMove(2,4,1,4);
    
    makeMove(6,7,6,5);
    */
    

    /**
    makeMove(7,3,6,3);
    
    makeMove(6,3,3,0);
    
    makeMove(6,3,3,0);
    
    makeMove(3,0,4,0);
    
    makeMove(1,3,3,3);
    
    makeMove(4,0,1,3);
    
    makeMove(0,3,1,3);
    
    */
    
    
   
    printmyArray();
    statusOfBoard();
    
    

}

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




void joyStickReadings()
{
  uint32_t res;
  res = ButtonIn();
  ADC_InitTriple(ADC1, 4, 5, 6, ADCVREF_VDDA);
  uint32_t temp;
  uint32_t Position;
  
  

    

  // initialize semaphore

  Time = 0;
  __enable_irq();
  while(1){
      // write this

      if(flag)
      {
        flag = 0;
       Position = Convert(datas);
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

  
 
  xplot = (x / 32);
  yplot = (y / 25.6);

  xplot = xplot - xplot%16;
  xplot = 128 -16 - xplot;
  yplot = yplot - yplot%20;

  xarr = xplot/16;
  yarr = yplot/20;
  drawHollowBox();

    if((doubleclick == 2) && (agreeddraw != 1))
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
          ST7735_FillRect(xin1*16, yin1*20, 16, 20, ST7735_Color565(101, 67, 33));
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
          ST7735_FillRect(xin1*16, yin1*20, 16, 20, ST7735_Color565(101, 67, 33));
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
        

        



      }
    }
    
    if(!invalidMove)
    {
      TimerG0counts = 0;
      mySysTick_IntArm(7256, 0);
        TimerG0_IntArm(7256, 0, 0);
        Sound_Init();
      while(TimerG0counts != 4)
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
   uint16_t lightBrown = ST7735_Color565(210, 180, 140);   // Example Tan
uint16_t darkBrown = ST7735_Color565(101, 67, 33);  
  uint32_t buttonclicked = 0;
  __enable_irq();
  ST7735_FillScreen(ST7735_WHITE);

  ST7735_DrawBitmap(16, 160 - 30, WelcomeScreen, 100, 100);
  
  while(buttonclicked < 16)
  {

    buttonclicked = ButtonIn();
    

  }

  while(buttonclicked < 16)
  {

    buttonclicked = ButtonIn();
    

  }

 
  GPIOA->DOUTSET31_0 = (1 << 17);





  drawBoard();
  if(whiteOrBlack[0][7] == 1)
  {

    backgroundcolor = lightBrown;



  }
  else {
  backgroundcolor = darkBrown;
  }
  ST7735_DrawBitmap(0, 157, BlackRook, 16,16);
  
  ST7735_DrawBitmap(16, 157, BlackKnight, 16, 16);

  ST7735_DrawBitmap(32, 157, BlackBishop, 16,16);
  
  ST7735_DrawBitmap(48, 157, BlackQueen, 16, 16);

  ST7735_DrawBitmap(64, 157, BlackKing, 16,16);
  
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
  
  ST7735_DrawBitmap(48, 17, WhiteQueen, 16, 16);

  ST7735_DrawBitmap(64, 17, WhiteKing, 16,16);
  
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
  doubleclick = 0;
 
 
 




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

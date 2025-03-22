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

#include <stdio.h> 
#define NUM 8
  
// Driver Code 
// Initizizing display and showing the checkered board on hardware screen
int main8(void)
{
  Clock_Init80MHz(0);
  LaunchPad_Init();
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
      
      ST7735_FillRect(x,y,16,20,ST7735_WHITE);
    }

    else {
  

      ST7735_FillRect(x,y,16,20,ST7735_BLACK);
      
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

return 0;

}

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
uint8_t playerKing = 20; //Keeps what kings turn it is (10 for white and 20 for black) P.S (for now it is defaulted at 20 for testing)
bool check = false;
bool printcheck = true; // is the code currently checking for a chess "check"
bool discoveredCheck = false;


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

#define WP 1
#define WH 2
#define WB 3
#define WR 5
#define WQ 9
#define WK 10

#define BP 11
#define BH 12
#define BB 13
#define BR 15
#define BQ 19
#define BK 20


// GOD CHESS BOARD ALL UPDATES ARE KEPT IN HERE

uint8_t chessboardNum[8][8] = {
  {BR,BH,BB,BQ,BK,BB,BH,BR},
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {WR,WH,WB,WQ,WK,WB,WH,WR}
    
};

/**uint8_t chessboardNum[8][8] = {
  {BR,BH,BB,BQ,BK,BB,BH,BR},
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {WR,WH,WB,WQ,WK,WB,WH,WR}
    
};
*/

// KEEPS THE PREVIOUS POSITION OF THE BOARD
uint8_t chessboardNumCheck[8][8] = {
  {BR,BH,BB,BQ,BK,BB,BH,BR},
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {WR,WH,WB,WQ,WK,WB,WH,WR}
    
};

//Array in which saveChessboardNum uses()
uint8_t chessboardNumSave[8][8] = {
  {BR,BH,BB,BQ,BK,BB,BH,BR},
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {WR,WH,WB,WQ,WK,WB,WH,WR}
    
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

  if(((currentID != 0) && (currentID < 11) && (futureID > 10)) || (((currentID > 10) && (futureID < 11)))) // is it a valid move? THIS FUNCTION DOESNT WEED OUT IF CURRENTID IS A PAWN
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

    res = placePiece( yin, xin, yf, xf, currentID);

  }

  if((currentID == 1) && ((yin - yf)==2) && (yin == 6) && (futureID == 0)&& ((xin - xf)==0)) // Double foward move at begining and checks valildity if currentID is a pawn
  {

    res = placePiece( yin, xin, yf, xf, currentID);

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

  if((futureID == 0) || (((currentID < 11) && (futureID > 10)) || (((currentID > 10) && (futureID < 11))))) // is it a valid move? THIS FUNCTION DOESNT WEED OUT IF CURRENTID IS A KNIGHT
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
          discoveredCheck = true; // a global variable is set to true that a discovered check happens which indicates an invalid move
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
          discoveredCheck = true; // a global variable is set to true that a discovered check happens which indicates an invalid move
          break;
        }
      }
    }
  }
}

 
  check = false; // check fxn is done

  return res;

}

// Sets the chessboardNum to the previous move stored by chessboardNumCheck
// Inputs yin, xin, yf, xf, are all the propesed corrdiantes
// Output none
void undoMove(int yin, int xin, int yf, int xf)
{
  chessboardNum[yin][xin] = chessboardNumCheck[yin][xin];
  chessboardNum[yf][xf] = chessboardNumCheck[yf][xf];

}


// Will check every possible input move and output move and see whether check becomes false in any case
// Inputs none
// Output true if checkmate is true and false if checkmate isnt true


bool isCheckMate()
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
    if(isCheckMate()) // runs checkmate and sees result
    {

      printf("Checkmate");
      printf("\n");
      break;

    }
    if(isInCheck() && !discoveredCheck) // determines wheter a "true check" has occured meaning its a clean check and no otehr invalid moves created this check
    {
      checkprint = true;
      
    }

  }

  if(!isCheckMate() && checkprint) // if check is true and checkmate is false then check is true
  {
    printf("Check");
    printf("\n");

  }

  if(discoveredCheck) // if an invalid move is made it will show up here
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
  uint8_t currentID = PieceID(yin,xin); // sets currentID to the initial position selected
  uint8_t res = 255; // initally set to 255 (for debugging purposes)
  
  discoveredCheck = false; // set the gloabl var to false

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


if((isInCheck()) && ((((playerKing == 10)) && (chessboardNum[yf][xf] < 11)) || (((playerKing == 20)) && (chessboardNum[yf][xf] > 10)))) // cehces for discovered check once the move is made
{
  undoMove(yin,xin,yf,xf); // move has to be undone if the move results in a check which is bad since the king is exposed
  discoveredCheck = true;
}


if(!discoveredCheck) // if discovered check is false
{
  chessboardNumCheck[yin][xin] = 0; // move the chess piece
  chessboardNumCheck[yf][xf] = currentID; //move the chess piece
}

  isInCheck(); //checks for check

  isCheckMate(); // checks for mate

  printmyArray(); // prints out the current chessboard
  
  statusOfBoard(); // prints out teh status of teh board if it is in check , mate or an invalid move has been made

  printf("\n");

  printf("\n");

    return res; // returns if a move was made or not

  
}



//Have fun creating your own chess games
//Only need to use makeMove(x1,y1,x2,y2) and printmyArray() to move pieces
//Happy chessing :)

int main(void)
{
    /*printmyArray();
    makeMove(6,0,4,0);
    printmyArray();
    makeMove(7,0,5,0);
    printmyArray();
    //makeMove(1,3,3,3);
    //printmyArray();
    makeMove(7,1,5,2);
    printmyArray();
    makeMove(7,2,5,3);
    printmyArray();
    makeMove(5,0,5,7);
    printmyArray();
    makeMove(5,0,5,1);
    printmyArray();
    makeMove(6,3,4,3);
    printmyArray();
    makeMove(7,3,5,3);
    printmyArray();
    makeMove(5,3,2,0);
    printmyArray();
    makeMove(2,0,2,4);
    printmyArray();
    makeMove(2,4,1,4);
    printmyArray();
    makeMove(6,7,6,5);
    printmyArray();
    */

    /**
    makeMove(7,3,6,3);
    printmyArray();
    makeMove(6,3,3,0);
    printmyArray();
    makeMove(6,3,3,0);
    printmyArray();
    makeMove(3,0,4,0);
    printmyArray();
    makeMove(1,3,3,3);
    printmyArray();
    makeMove(4,0,1,3);
    printmyArray();
    makeMove(0,3,1,3);
    printmyArray();
    */
    
    //printmyArray();
    makeMove(6,4,4,4);
    //makeMove(7,5,4,2);
    makeMove(7,3,3,7);
    makeMove(3,7,1,5);
    makeMove(0,6,2,5);
    
    makeMove(0,4,1,5);

    makeMove(1,5,4,5);
    
    

}

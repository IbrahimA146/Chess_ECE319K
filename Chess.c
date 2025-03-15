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

/**uint8_t chessboardNum[8][8] = {
  {BR,BH,BB,BQ,BK,BB,BH,BR},
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {BR,BH,BB,BQ,BK,BB,BH,BR}
    
};
*/

uint8_t chessboardNum[8][8] = {
  {BK,BR,0,0,0,0,0,0},
  {BR,BR,0,0,0,0,0,0},
  {0, WH, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {WP,WP,WP,WP,WP,WP,WB,WP},
  {WR,WH,WB,WQ,WK,WB,WH,WR}
    
};





// KEEPS THE PREVIOUS POSITION OF THE BOARD
uint8_t chessboardNumCheck[8][8] = {
  {BK,BR,0,0,0,0,0,0},
  {BR,BR,0,0,0,0,0,0},
  {0, WH, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {WP,WP,WP,WP,WP,WP,WB,WP},
  {WR,WH,WB,WQ,WK,WB,WH,WR}
    
};

uint8_t chessboardNumSave[8][8] = {
  {15,12,13,19,20,13,12,15},
  {11,11,11,11,11,11,11,11},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {1, 1, 1, 1, 1, 1, 1, 1 },
  {5, 2, 3, 9, 10,3 ,2, 5 }
    
};

void saveChessboardNum()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNumSave[i][j] = chessboardNum[i][j]; // %3u to format as unsigned int with width 3
        }
    }

}

void restoreChessboardNum()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNum[i][j] = chessboardNumSave[i][j]; // %3u to format as unsigned int with width 3
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

    printf("\n");

    printf("\n");
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
      if(chessboardNum[i][j] == pieceNum)
      {
        ypos = i;
        xpos = j;
      }
    }
  }
}










//Will find the PieceID based on given xin and yin corrdiantes
//Inputs xin yin
//Output ID value stored as num

uint8_t PieceID(int yin, int xin)
{
  uint8_t num = (uint8_t)chessboardNum[yin][xin];
  return num;

}

//This fucntion will Place a Piece in its new location
//Inputs yin, xin, yf, xf, are all the corrdiantes used to move the piece from its orginal location to its new location. currentID tells us what the piece is
//Output return 1 for traversing fxn (important for isItCheck())

uint8_t placePiece(int yin, int xin, int yf, int xf, uint8_t currentID)
{

  if(!check)
  {
    chessboardNum[yin][xin] = 0;
    chessboardNum[yf][xf] = currentID;
    

  }
  return 1;  //still ran even in check or not

  
    

  

    

}

//This fucntion explicaly highlights the niche case of a pawn taking material 
//This function is seperate from makePawnMove() because isItCheck() is only concerned about the king being attackd and a pawn can't attack when directly facing a piece
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output returns res: 1 meaning the move was executed 0 meaning its an invalid move

uint8_t pawnTakes(int yin, int xin, int yf, int xf)
{
  uint8_t currentID = PieceID(yin,xin);
  uint8_t futureID = PieceID(yf,xf);
  uint8_t res = 0;
  if((currentID == 1) && ((yin - yf)==1) && (futureID > 10) && (((xin - xf) == 1) || ((xf - xin) == 1)))
  {

    
    res = placePiece( yin, xin, yf, xf, currentID);

  }

  if((currentID == 11) && ((yf - yin)==1) && (futureID < 11) && (((xin - xf) == 1) || ((xf - xin) == 1)))
  {

    res = placePiece( yin, xin, yf, xf, currentID);

  }

  return res;
}

//inputs corrdiates of chosen piece and its desitnation. This function accounts all pawn moves execpt en pesant
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output returns res: 1 meaning the move was executed 0 meaning its an invalid move

uint8_t makePawnMove(int yin, int xin, int yf, int xf)
{

  

  uint8_t currentID = PieceID(yin,xin);
  uint8_t futureID = PieceID(yf,xf);
  uint8_t res = 0;

  res = pawnTakes(yin, xin, yf, xf);

  if((currentID == 1) && ((yin - yf)==1) && (futureID == 0) && ((xin - xf)==0))
  {

    res = placePiece( yin, xin, yf, xf, currentID);

  }


  if((currentID == 11) && ((yf - yin)==1) && (futureID == 0) && ((xin - xf)==0))
  {

    res = placePiece( yin, xin, yf, xf, currentID);

  }

  if((currentID == 11) && ((yf - yin)==2) && (yin == 1) && (futureID == 0) && ((xin - xf)==0))
  {

    res = placePiece( yin, xin, yf, xf, currentID);

  }

  if((currentID == 1) && ((yin - yf)==2) && (yin == 6) && (futureID == 0)&& ((xin - xf)==0))
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
  uint8_t currentID = PieceID(yin,xin);
  uint8_t futureID = PieceID(yf,xf);
  uint8_t res = 0;
  if((futureID == 0) || (((currentID < 11) && (futureID > 10)) || (((currentID > 10) && (futureID < 11)))))
  {
    
      if((yf-yin) == 2 && (((xf - xin) == 1) || ((xin - xf) == 1)))
      {
        res = placePiece( yin, xin, yf, xf, currentID);

      }

      if((yf-yin) == -2 && (((xf - xin) == 1) || ((xin - xf) == 1)))
      {
        res = placePiece( yin, xin, yf, xf, currentID);

      }

      if((yf-yin) == 1 && (((xf - xin) == 2) || ((xin - xf) == 2)))
      {
        res = placePiece( yin, xin, yf, xf, currentID);

      }

      if((yf-yin) == -1 && (((xf - xin) == 2) || ((xin - xf) == 2)))
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

  uint8_t currentID = PieceID(yin,xin);
  uint8_t futureID = PieceID(yf,xf);
  uint8_t res = 0;
  uint8_t xtemp1 = xin;
  uint8_t ytemp1 = yin;
  uint8_t xtemp2 = xin;
  uint8_t ytemp2 = yin;
  uint8_t xtemp3 = xin;
  uint8_t ytemp3 = yin;
  uint8_t xtemp4 = xin;
  uint8_t ytemp4 = yin;
  uint8_t tempID = currentID;
  bool flag = false;
  bool flag1 = true;
  bool flag2 = true;
  bool flag3 = true;
  bool flag4 = true;



  for(int i = 0; i < 8; i++)
  {
    xtemp1 += 1;
    ytemp1 += 1;

    tempID = PieceID(ytemp1,xtemp1);

    if(flag1 && ((xtemp1 == xf) && (ytemp1 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11))))))
    {
      flag = true;
      break;
    }

    if(tempID != 0)
    {

      flag1 = false;
      

    }

    xtemp2 -= 1;
    ytemp2 += 1;

    tempID = PieceID(ytemp2,xtemp2);

    if(flag2 && ((xtemp2 == xf) && (ytemp2 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11))))))
    {
      flag = true;
      break;
    }

    if(tempID != 0)
    {

      flag2 = false;
      

    }

    

    xtemp3 += 1;
    ytemp3 -= 1;

    tempID = PieceID(ytemp3,xtemp3);

    if(flag3 && ((xtemp3 == xf) && (ytemp3 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11))))))
    {
      flag = true;
      break;
    }

    if(tempID != 0)
    {

      flag3 = false;
      

    }

    

    xtemp4 -= 1;
    ytemp4 -= 1;

    tempID = PieceID(ytemp4,xtemp4);

    if(flag4 && ((xtemp4 == xf) && (ytemp4 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11))))))
    {
      flag = true;
      break;
    }

    if(tempID != 0)
    {

      flag4 = false;
      

    }

  }

  if(flag)
  {

        res = placePiece( yin, xin, yf, xf, currentID);


  }

  return res;
}

//This function accounts for all rook moves
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output returns res: 1 meaning the move was executed 0 meaning its an invalid move


uint8_t makeRookMove(int yin, int xin,int yf, int xf)
{

  uint8_t currentID = PieceID(yin,xin);
  uint8_t futureID = PieceID(yf,xf);
  uint8_t res = 0;
  uint8_t xtemp1 = xin;
  uint8_t ytemp1 = yin;
  uint8_t xtemp2 = xin;
  uint8_t ytemp2 = yin;
  uint8_t xtemp3 = xin;
  uint8_t ytemp3 = yin;
  uint8_t xtemp4 = xin;
  uint8_t ytemp4 = yin;
  uint8_t tempID = currentID;
  bool flag = false;
  bool flag1 = true;
  bool flag2 = true;
  bool flag3 = true;
  bool flag4 = true;



  for(int i = 0; i < 8; i++)
  {
    xtemp1 += 1;
    ytemp1 += 0;

    tempID = PieceID(ytemp1,xtemp1);

    if(flag1 && ((xtemp1 == xf) && (ytemp1 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11))))))
    {
      flag = true;
      break;
    }

    if(tempID != 0)
    {

      flag1 = false;
      

    }

    xtemp2 -= 1;
    ytemp2 += 0;

    tempID = PieceID(ytemp2,xtemp2);

    if(flag2 && ((xtemp2 == xf) && (ytemp2 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11))))))
    {
      flag = true;
      break;
    }

    if(tempID != 0)
    {

      flag2 = false;
      

    }

    

    xtemp3 += 0;
    ytemp3 += 1;

    tempID = PieceID(ytemp3,xtemp3);

    if(flag3 && ((xtemp3 == xf) && (ytemp3 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11))))))
    {
      flag = true;
      break;
    }

    if(tempID != 0)
    {

      flag3 = false;
      

    }

    

    xtemp4 += 0;
    ytemp4 -= 1;

    tempID = PieceID(ytemp4,xtemp4);

    if(flag4 && ((xtemp4 == xf) && (ytemp4 == yf) && (futureID == 0 || (((currentID < 11) && (tempID > 10)) || ((currentID > 10) && (tempID < 11))))))
    {
      flag = true;
      break;
    }

    if(tempID != 0)
    {

      flag4 = false;
      

    }

  }

  if(flag)
  {

        res = placePiece( yin, xin, yf, xf, currentID);


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

  uint8_t currentID = PieceID(yin,xin);
  uint8_t futureID = PieceID(yf,xf);
  uint8_t res = 0;

  //diagional moves

if((futureID == 0) || (((currentID < 11) && (futureID > 10)) || (((currentID > 10) && (futureID < 11)))))
{
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
  check = true;
  bool res = false;
  uint8_t xin = 0;
  uint8_t yin = 0;
  uint8_t yf = 0;
  uint8_t xf = 0;
  uint8_t resNum = 0;
  findPiece(playerKing);

  xin = xpos;
  yin = ypos;


  if(playerKing == 10)
  {
    for(int i = 0; i < 8; i++)
    {
      for(int j = 0; j < 8; j++)
      {
        yf = i;
        xf = j;

        resNum = pawnTakes(ypos, xpos, yf, xf);
        if((chessboardNum[yf][xf] == 11) && (resNum == 1))
        {
          res = true;
          break;
        }

        resNum = makeKnightMove(ypos, xpos,  yf,  xf);
        if((chessboardNum[yf][xf] == 12) && (resNum == 1))
        {
          res = true;
          break;
        }

        resNum = makeBishopMove(ypos, xpos, yf, xf);
        if((chessboardNum[yf][xf] == 13) && (resNum == 1))
        {
          res = true;
          break;
        }

        resNum = makeRookMove(ypos, xpos, yf, xf);
        if((chessboardNum[yf][xf] == 15) && (resNum == 1))
        {
          res = true;
          break;
        }

        resNum = makeQueenMove(ypos, xpos, yf, xf);
        if((chessboardNum[yf][xf] == 19) && (resNum == 1))
        {
          res = true;
          break;
        }

        resNum = makeKingMove(ypos, xpos, yf, xf);
        if((chessboardNum[yf][xf] == 20) && (resNum == 1))
        {
          res = true;
          break;
        }
      }
    }

  }

  if(playerKing == 20)
  {
    for(int i = 0; i < 8; i++)
    {
      for(int j = 0; j < 8; j++)
      {
        yf = i;
        xf = j;

        resNum = pawnTakes(ypos, xpos, yf, xf);
        if((chessboardNum[yf][xf] == 1) && (resNum == 1))
        {
          res = true;
          break;
        }

        resNum = makeKnightMove(ypos, xpos, yf, xf);
        if((chessboardNum[yf][xf] == 2) && (resNum == 1))
        {
          res = true;
          break;
        }

        resNum = makeBishopMove(ypos, xpos, yf, xf);
        if((chessboardNum[yf][xf] == 3) && (resNum == 1))
        {
          res = true;
          break;
        }

        resNum = makeRookMove(ypos, xpos, yf, xf);
        if((chessboardNum[yf][xf] == 5) && (resNum == 1))
        {
          res = true;
          break;
        }

        resNum = makeQueenMove(ypos, xpos, yf, xf);
        if((chessboardNum[yf][xf] == 9) && (resNum >= 1))
        {
          res = true;
          break;
        }

        resNum = makeKingMove(ypos, xpos, yf, xf);
        if((chessboardNum[yf][xf] == 10) && (resNum == 1))
        {
          res = true;
          break;
        }



      
      }
    }
  }

  if(res && printcheck)
  {
    printf("Check");
    printf("\n");
  }

  check = false;

  return res;

}

//Sets the chessboardNum to the previous move stored by chessboardNumCheck
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output none
void undoMove(int yin, int xin, int yf, int xf)
{
  chessboardNum[yin][xin] = chessboardNumCheck[yin][xin];
  chessboardNum[yf][xf] = chessboardNumCheck[yf][xf];

}

bool isCheckMate()
{

  saveChessboardNum();
  uint8_t res = 255;
  bool checkmate = true;
  //check = true;
  printcheck = false;
  bool iteratteloop = false;

  uint8_t xin;
  uint8_t yin;
  uint8_t yf;
  uint8_t xf;

  uint8_t xin_1;
  uint8_t yin_1;
  uint8_t yf_1;
  uint8_t xf_1;



  for(int i = 0; i < 8; i++)
  {
    if(!checkmate)
              {
                break;
              }
    for(int j = 0; j < 8; j++) 
    {
      if(!checkmate)
              {

                break;
              }
      for(int k = 0; k < 8; k++)
      {
        if(!checkmate)
              {
                break;
              }
        for(int l = 0; l < 8; l++)
        {

          yin = i;
          xin = j;
          yf = k;
          xf = l;

          uint8_t currentID = PieceID(yin,xin);

          if(((currentID >10) && (playerKing == 20)) || ((currentID <11) && (playerKing == 10)))
          {

            if((currentID == 1) || currentID == 11)
            {
              saveChessboardNum();
              res = makePawnMove(yin,xin,yf,xf);
              if(res == 1)
              {
                checkmate = isInCheck();
                restoreChessboardNum();
                if(!checkmate)
                  {

                    yin_1 = yin;
                    xin_1 = xin;
                    yf_1 = yf;
                    xf_1 = xf;
                    break;
                  }
              }
              
    
            }

          if((currentID == 2) || currentID == 12)
            {
              saveChessboardNum();
              res = makeKnightMove(yin,xin,yf,xf);
              if(res == 1)
              {
                checkmate = isInCheck();
                restoreChessboardNum();
                if(!checkmate)
                  {
                    yin_1 = yin;
                    xin_1 = xin;
                    yf_1 = yf;
                    xf_1 = xf;
                    break;
                  }
              }

            }

          if((currentID == 3) || currentID == 13)
            {
              saveChessboardNum();
              res = makeBishopMove(yin,xin,yf,xf);
              if(res == 1)
              {
                checkmate = isInCheck();
                restoreChessboardNum();
                if(!checkmate)
                  {
                    yin_1 = yin;
                    xin_1 = xin;
                    yf_1 = yf;
                    xf_1 = xf;
                    break;
                  }
              }

            }

          if((currentID == 5) || currentID == 15)
            {
              saveChessboardNum();
              res = makeRookMove(yin,xin,yf,xf);
              if(res == 1)
              {
                checkmate = isInCheck();
                restoreChessboardNum();
                if(!checkmate)
                  {
                    yin_1 = yin;
                    xin_1 = xin;
                    yf_1 = yf;
                    xf_1 = xf;
                    break;
                  }
              }

            }

          if((currentID == 9) || currentID == 19)
            {
              saveChessboardNum();
              res = makeQueenMove(yin,xin,yf,xf);
              if(res == 1)
              {
                checkmate = isInCheck();
                restoreChessboardNum();
                if(!checkmate)
                  {
                    yin_1 = yin;
                    xin_1 = xin;
                    yf_1 = yf;
                    xf_1 = xf;
                    break;
                  }
              }

            }

          if((currentID == 10) || currentID == 20)
            {
              saveChessboardNum();
              res = makeKingMove(yin,xin,yf,xf);
              if(res == 1)
              {
                checkmate = isInCheck();
                restoreChessboardNum();
                if(!checkmate)
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



  if(checkmate)
  {
    printf("Checkmate");

    printf("\n");
  }

  printcheck = true;

  //check = false;
  restoreChessboardNum();
  return checkmate;
  

}

  

  


  












//This function will make a move stored in chessboardNum
//Inputs yin, xin, yf, xf, are all the propesed corrdiantes
//Output returns res: 1 meaning the move was executed 255 meaning its an invalid move 0 meaning that piece was found but couldnt be moved
uint8_t makeMove(int yin, int xin,int yf, int xf)
{
  uint8_t currentID = PieceID(yin,xin);
  uint8_t res = 255;
  bool discoveredCheck = false;

do
{
  discoveredCheck = false;
  if((currentID == 1) || currentID == 11)
  {
    res = makePawnMove(yin,xin,yf,xf);
    
  }

  if((currentID == 2) || currentID == 12)
  {

    res = makeKnightMove(yin,xin,yf,xf);

  }

  if((currentID == 3) || currentID == 13)
  {

    res = makeBishopMove(yin,xin,yf,xf);

  }

  if((currentID == 5) || currentID == 15)
  {

    res = makeRookMove(yin,xin,yf,xf);

  }

  if((currentID == 9) || currentID == 19)
  {

    res = makeQueenMove(yin,xin,yf,xf);

  }

  if((currentID == 10) || currentID == 20)
  {

    res = makeKingMove(yin,xin,yf,xf);

  }

if((isInCheck()) && ((((playerKing == 10)) && (chessboardNum[yf][xf] < 11)) || (((playerKing == 20)) && (chessboardNum[yf][xf] > 10)))) //discovered check
{
  undoMove(yin,xin,yf,xf);
  discoveredCheck = true;
}

if(isCheckMate())
{
  break;
}


}
while((isInCheck()) && (discoveredCheck)); //discovered check

    chessboardNumCheck[yin][xin] = 0;
    chessboardNumCheck[yf][xf] = currentID;


  

  



    return res;

  
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
    printmyArray();
    makeMove(1,3,6,3);
    printmyArray();
    makeMove(2,2,5,2);
    printmyArray();
    makeMove(6,6,2,2);
    printmyArray();
    makeMove(1,1,2,1);
    printmyArray();
    
    

}

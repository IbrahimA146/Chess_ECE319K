// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// Your name
// Last Modified: 12/26/2024


#include "../inc/ADC.h"
#include <chess_sprites.h>
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
int main0(void){ // main 0, demonstrate Arabic output
  Clock_Init80MHz(0);
  LaunchPad_Init();
  ST7735_InitR(INITR_REDTAB);
  ST7735_FillScreen(ST7735_WHITE);
  Arabic_SetCursor(0,15);
  Arabic_OutString(Hello);
  Arabic_SetCursor(0,31);
  Arabic_OutString(WeAreHonoredByYourPresence);
  Arabic_SetCursor(0,63);
  Arabic_OutString(ArabicAlphabet);
  while(1){
  }
}
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
// use main1 to observe special characters
int main1(void){ // main1
    char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  ST7735_FillScreen(0x0000);            // set screen to black
  for(phrase_t myPhrase=HELLO; myPhrase<= GOODBYE; myPhrase++){
    for(Language_t myL=English; myL<= French; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// use main2 to observe graphics
int main2(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_DrawBitmap(22, 159, PlayerShip0, 18,8); // player ship bottom
  ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
  ST7735_DrawBitmap(42, 159, PlayerShip1, 18,8); // player ship bottom
  ST7735_DrawBitmap(62, 159, PlayerShip2, 18,8); // player ship bottom
  ST7735_DrawBitmap(82, 159, PlayerShip3, 18,8); // player ship bottom
  ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
  ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
  ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
  ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
  ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);

  for(uint32_t t=500;t>0;t=t-5){
    SmallFont_OutVertical(t,104,6); // top left
    Clock_Delay1ms(50);              // delay 50 msec
  }
  ST7735_FillScreen(0x0000);   // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString("GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString("Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString("Earthling!");
  ST7735_SetCursor(2, 4);
  ST7735_OutUDec(1234);
  while(1){
  }
}

// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  while(1){
    // write code to test switches and LEDs
    
  }
}
// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    now = Switch_In(); // one of your buttons
    if((last == 0)&&(now == 1)){
      Sound_Shoot(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_Killed(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_Explosion(); // call one of your sounds
    }
    if((last == 0)&&(now == 8)){
      Sound_Fastinvader1(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}

// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main5(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  //ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  TimerG12_IntArm(80000000/30,2);
  // initialize all data structures
  __enable_irq();

  while(1){
    // wait for semaphore
       // clear semaphore
       // update ST7735R
    // check for end game or level switch
  }
}


void main7(void)
{
  Clock_Init80MHz(0);
  LaunchPad_Init();
  ST7735_InitR(INITR_REDTAB);
  ST7735_FillScreen(ST7735_WHITE);
}

// C program to create a chess board 
//#include <conio.h> 
//#include <dos.h> 
//#include <graphics.h> 















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

uint8_t allPossMovesWhite [2250][4];
uint8_t allPossMovesBlack [2250][4];
uint8_t firstWhiteMoves [500][4];
uint8_t undoBotMovesBot [10][4];
uint8_t undoBotMovesBotCount = 0;
uint8_t botYin;
uint8_t botXin;
uint8_t botYf;
uint8_t botXf;
uint8_t botYinFin;
uint8_t botXinFin;
uint8_t botYfFin;
uint8_t botXfFin;
bool bot = false;
uint32_t Searchcount = 0;
bool actMiniMax = true;
bool player1Mode;
bool isplacing = false;
bool needtoCheck = false;
bool needtoCheckmate = false;
bool canBotDeflectCheck = false;
uint8_t yinFirst;
uint8_t xinFirst;
uint8_t yfFirst;
uint8_t xfFirst;
int TheFirstMaxValue;
bool bothasran = false;

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

void drawHollowBox()
{
  uint16_t lightBrown = ST7735_Color565(210, 180, 140);   // Example Tan
uint16_t darkBrown = ST7735_Color565(101, 67, 33);  
  //ST7735_DrawPixel(xplot, yplot, ST7735_YELLOW);


int i;
int j;

x0to7pre = xprevious / 16;
y0to7pre = yprevious / 20;


 
 if(doubleclick == 2)
 {

 }
 else {

 

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

     ST7735_DrawPixel(i, yplot, selectedBoxColor);

  }

  for(i = xplot +2; i < xplot+14; i++)
  {

     ST7735_DrawPixel(i, yplot+18, selectedBoxColor);

  }

  for(j = yplot +1; j < yplot+18; j++)
  {

     ST7735_DrawPixel(xplot, j, selectedBoxColor);

  }

  for(j = yplot+1; j < yplot+18; j++)
  {

     ST7735_DrawPixel(xplot +14, j, selectedBoxColor);

  }
  

 

  xprevious = xplot;
  yprevious = yplot;

 }

  

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

void mySysTick_Stop(void){
 
  SysTick->VAL = 5;
  
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
      while(res != 0){res = ButtonIn();};
      
      }
      
    }
  }

  if(res >= 16)
  {

    if(doubleclick == 1)
    {
      xf1 = xarr-1;
      yf1 = yarr-1;
      doubleclick = 2;
      selectedBoxColor = ST7735_YELLOW;
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
  {WR,WH,WB,WK,WQ,WB,WH,WR},
  {WP,WP,WP,WP,WP,WP,WP,WP},
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0, 0, 0, 0 },
  {BP,BP,BP,BP,BP,BP,BP,BP},
  {BR,BH,BB,BK,BQ,BB,BH,BR}
    
};

//Array in which saveChessboardNum uses()
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


//SAVES THE CHESS BOARD TO WHAT WAS INPUTED IN chessboardNum[][] into chessboardSave[][]
void saveChessboardNum()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNumSave[i][j] = chessboardNum[i][j]; // puts chessboardNum into chessboardNumSave
        }
    }

}

void SpecialsaveChessboardNum()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNumSpecialSave[i][j] = chessboardNum[i][j]; // puts chessboardNum into chessboardNumSave
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

void SpecialRestoreChessboardNum()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNum[i][j] = chessboardNumSpecialSave[i][j]; // puts chessboardNumSave[][] into chessboardNum[][]
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

uint8_t PieceIDBot(int yin, int xin)
{
  uint8_t num = (uint8_t)chessboardNumbot[yin][xin]; // finds id of the given square and returns it
  return num;

}

//This fucntion will Place a Piece in its new location
//Inputs yin, xin, 
//yf, xf, are all the corrdiantes used to move the piece from its orginal location to its new location. currentID tells us what the piece is
//Output return 1 for traversing fxn (important for isItCheck())

uint8_t placePiece(int yin, int xin, int yf, int xf, uint8_t currentID)
{
  if(bot && !check && isplacing)
  {

    chessboardNumbot[yin][xin] = 0; // puts 0 in the current value
    chessboardNumbot[yf][xf] = currentID;
    chessboardNum[yin][xin] = 0; // puts 0 in the current value
    chessboardNum[yf][xf] = currentID;

    return 1;

  }

  if(bot )
  {



    chessboardNumbot[yin][xin] = 0; // puts 0 in the current value
    chessboardNumbot[yf][xf] = currentID;
    return 1;

  }
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

     if((((yin - yf)==1) && (((xin - xf) == 1) || ((xf - xin) == 1))) && currentID < 11) // checks if the direction is a pawn taking 
    {

    
      res = placePiece( yin, xin, yf, xf, currentID);

    }

    if((((yf - yin)==1) && (((xin - xf) == 1) || ((xf - xin) == 1))) && currentID > 10) // checks if the direction is a pawn taking 
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
  if(bot && !needtoCheck)
  {
  return 0;
  }

  if(needtoCheck)
  {
    findPiece(20);
    playerKing = 20;
    xin = xpos; // sets xin = xpos (locally storing a global var)
    yin = ypos; // sets yin = ypos (locally storing a global var)

  }

  


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
          return res;
          break;
        }

        resNum = makeKnightMove(ypos, xpos,  yf,  xf); // the king is pretending to traverse in a makeKnightMove pathway
        if((chessboardNum[yf][xf] == 12) && (resNum == 1)) // if there is a knight attacking the king like the fxn makeKnightMove implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          return res;
          break;
        }

        resNum = makeBishopMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeBishopMove pathway
        if((chessboardNum[yf][xf] == 13) && (resNum == 1)) // if there is a bishop attacking the king like the fxn makeBishopMove implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          return res;
          break;
        }

        resNum = makeRookMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeRookMove pathway
        if((chessboardNum[yf][xf] == 15) && (resNum == 1)) // if there is a rook attacking the king like the fxn makeRookMove implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          return res;
          break;
        }

        resNum = makeQueenMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeQueenMove pathway
        if((chessboardNum[yf][xf] == 19) && (resNum == 1)) // if there is a queen attacking the king like the fxn makeQueenMove implements the conditional is true
        {
        {
          res = true; // "check" is true and break out of the fxn
          return res;
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
          return res;
          break;
        }

        resNum = makeKnightMove(ypos, xpos,  yf,  xf); // the king is pretending to traverse in a makeKnightMove pathway
        if((chessboardNum[yf][xf] == 2) && (resNum == 1)) // if there is a knight attacking the king like the fxn makeKnightMove implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          return res;
          break;
        }

        resNum = makeBishopMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeBishopMove pathway
        if((chessboardNum[yf][xf] == 3) && (resNum == 1)) // if there is a bishop attacking the king like the fxn makeBishopMove implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          return res;
          break;
        }

        resNum = makeRookMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeRookMove pathway
        if((chessboardNum[yf][xf] == 5) && (resNum == 1)) // if there is a rook attacking the king like the fxn makeRookMove implements the conditional is true
        {
          res = true; // "check" is true and break out of the fxn
          return res;
          break;
        }

        resNum = makeQueenMove(ypos, xpos, yf, xf); // the king is pretending to traverse in a makeQueenMove pathway
        if((chessboardNum[yf][xf] == 9) && (resNum == 1)) // if there is a queen attacking the king like the fxn makeQueenMove implements the conditional is true
        {
        {
          res = true; // "check" is true and break out of the fxn
          return res;
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

  if(bot == true)
  {
  return 0;
  }

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

  if(bot && !needtoCheckmate)
  {
  return 0;
  }



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

  if(isInCheck())
  {

    if(chessturn == 1)
      {
        whitewon = 0;
        blackwon = 0;
      }
      if(chessturn == 0)
      {
        whitewon = 0;
        blackwon = 0;
      }

  }

  

  

  //printmyArray(); // prints out the current chessboard
  
  //statusOfBoard(); // prints out teh status of teh board if it is in check , mate or an invalid move has been made

  //printf("\n");

  //printf("\n");

    return res; // returns if a move was made or not

  

  
}


void saveChessboardNumBot()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNumSaveBot[i][j] = chessboardNumbot[i][j]; // puts chessboardNum into chessboardNumSave
        }
    }

}

void saveChessboardNumBotReset()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNumSaveBot[i][j] = chessboardNumSave[i][j]; // puts chessboardNum into chessboardNumSave
        }
    }

}

void restoreChessboardBot()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNumbot[i][j] = chessboardNum[i][j]; // puts chessboardNumSave[][] into chessboardNum[][]
        }
    }

}

void botFromBotSave()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNumbot[i][j] = chessboardNumSaveBot[i][j]; // puts chessboardNumSave[][] into chessboardNum[][]
        }
    }

}

void restoreChessboardBotReset()
{

   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNumbot[i][j] = chessboardNum[i][j]; // puts chessboardNumSave[][] into chessboardNum[][]
        }
    }

}



//CHESS BOT
const int pawnValue = 100;
const int knightValue = 300;
const int bishopValue = 300;
const int rookValue = 500;
const int queenValue = 900;
const int kingValue = 2000;
uint32_t countofBigArray = 0;

int pawnWhiteValues[8][8] = {
       
        {5, 10, 10, -20, -20, 10, 10, 5},
        {5, -5, -10, 0, 0, -10, -5, 5},
        {-5, 0, 0, 5, 20, 0, 0, -5},
        {0, 5, 5, 20, 5, 5, 5, 0},
        {0, 10, 5, 5, 5, 5, 10, 0},
        {5, 5, 5, 5, 5, 5, 5, 5},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int knightWhiteValues[8][8] = {
        {-50, -40, -30, -30, -30, -30, -40, -50},
        {-40, -20, 0, 0, 0, 0, -20, -40},
        {-30, 0, 10, 15, 15, 10, 0, -100},
        {-30, 5, 15, 20, 20, 15, 5, -100},
        {-30, 0, 15, 20, 20, 15, 0, -100},
        {-30, 5, 100, 15, 15, 10, 5, -100},
        {-40, -20, 0, 5, 5, 0, -20, -40},
        {-50, -40, -30, -30, -30, -30, -40, -50}
    };

    int bishopWhiteValues[8][8] = {

        {-20, -10, -10, -10, -10, -10, -10, -20},
        {-10, 5, 0, 0, 0, 0, 5, -10},
        {-10, 10, 10, 10, 10, 10, 10, -10},
        {-10, 0, 10, 10, 10, 10, 0, -10},
        {-10, 5, 5, 10, 10, 5, 5, -10},
        {-10, 0, 5, 10, 10, 5, 0, -10},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-20, -10, -10, -10, -10, -10, -10, -20},
    };

    int rookWhiteValues[8][8] = {

        {0, 0, 0, 5, 5, 0, 0, 0},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {5, 10, 10, 10, 10, 10, 10, 5},
        {0, 0, 0, 0, 0, 0, 0, 0},

    };

    int queenWhiteValues[8][8] = {

        {-20, -10, -10, -5, -5, -10, -10, -20},
        {-10, 0, 5, 0, 0, 0, 0, -10},
        {-10, 5, 5, 5, 5, 5, 5, -10},
        {0, 0, 5, 5, 5, 5, 0, -5},
        {-5, 0, 5, 5, 5, 5, 0, -5},
        {-10, 0, 5, 5, 5, 5, 0, -10},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-20, -10, -10, -5, -5, -10, -10, -20},
    };

    int kingWhiteValues[8][8] = {

        {20, 30, 10, 0, 0, 10, 30, 20},
        {20, 20, 0, 0, 0, 0, 20, 20},
        {-10, -20, -20, -20, -20, -20, -20, -10},
        {-20, -30, -30, -40, -40, -30, -30, -20},
        {-30, -40, -40, -50, -50, -40, -40, -100},
        {-30, -40, -40, -50, -50, -40, -40, -100},
        {-30, -40, -40, -50, -50, -40, -40, -100},
        {-30, -40, -40, -50, -50, -40, -40, -100},

    };


    int pawnBlackValues[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {5, 5, 5, 5, 5, 5, 5, 5},
        {5, 10, 20, 5, 5, 20, 10, 5},
        {0, 0, 0, 25, 25, 5, 5, 5},
        {0, 0, 0, 20, 20, 0, 0, 0},
        {5, -5, -10, 0, 0, -10, -5, 5},
        {5, 0, 0, -20, -20, 0, 0, 5},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };


    int knightBlackValues[8][8] = {
        {-50, -40, -30, -30, -30, -30, -40, -50},
        {-40, -20, 0, 0, 0, 0, -20, -40},
        {-30, 0, 10, 15, 15, 10, 0, -30},
        {-30, 5, 15, 20, 20, 15, 5, -30},
        {-30, 0, 15, 20, 20, 15, 0, -30},
        {-30, 5, 100, 15, 15, 10, 5, -30},
        {-40, -20, 0, 5, 5, 0, -20, -40},
        {-50, -40, -30, -30, -30, -30, -40, -50}
    };

    int bishopBlackValues[8][8] = {
        {-20, -10, -10, -10, -10, -10, -10, -20},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-10, 0, 5, 10, 10, 5, 0, -10},
        {-10, 5, 5, 10, 10, 5, 5, -10},
        {-10, 0, 10, 10, 10, 10, 0, -10},
        {-10, 10, 10, 10, 10, 10, 10, -10},
        {-10, 5, 0, 0, 0, 0, 5, -10},
        {-20, -10, -10, -10, -10, -10, -10, -20}
    };

    int rookBlackValues[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {5, 10, 10, 10, 10, 10, 10, 5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {0, 0, 0, 5, 5, 0, 0, 0}
    };

    int queenBlackValues[8][8] = {
        {-20, -10, -10, -5, -5, -10, -10, -20},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-10, 0, 5, 5, 5, 5, 0, -10},
        {-5, 0, 5, 5, 5, 5, 0, -5},
        {0, 0, 5, 5, 5, 5, 0, -5},
        {-10, 5, 5, 5, 5, 5, 5, -10},
        {-10, 0, 5, 0, 0, 0, 0, -10},
        {-20, -10, -10, -5, -5, -10, -10, -20}
    };

    int kingBlackValues[8][8] = {
        {-30, -40, -40, -50, -50, -40, -40, -30},
        {-30, -40, -40, -50, -50, -40, -40, -30},
        {-30, -40, -40, -50, -50, -40, -40, -30},
        {-30, -40, -40, -50, -50, -40, -40, -30},
        {-20, -30, -30, -40, -40, -30, -30, -20},
        {-10, -20, -20, -20, -20, -20, -20, -10},
        {20, 20, 0, 0, 0, 0, 20, 20},
        {20, 30, 10, 0, 0, 10, 30, 20}
    };







int32_t countWhiteMaterial(uint8_t yin, uint8_t xin, uint8_t yf, uint8_t xf)
{
  int32_t material = 0;
  int32_t temVal;

  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if(PieceIDBot(i, j) > 10)
      {
        temVal = PieceIDBot(i, j);
        if(temVal == 11)
        {
          material += 1000;

        }

        if(temVal == 12)
        {
          material += 3000;
        } 

        if(temVal == 13)
        {
          material += 3000;
        } 

        if(temVal == 15)
        {
          material += 5000;
        } 

        if(temVal == 19)
        {
          material += 9000;
        }

        if(temVal == 20)
        {
          material += 20000;
        }    

      }
      
    }
  }

  return material;

}


int32_t countBlackMaterial(uint8_t yin, uint8_t xin, uint8_t yf, uint8_t xf)
{
  int32_t material = 0;
  int32_t temVal;

  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if(PieceIDBot(i, j) < 11 && PieceIDBot(i, j) !=0)
      {
        temVal = PieceIDBot(i, j);
        if(temVal == 1)
        {
          material -= 1000;
        }

        if(temVal == 2)
        {
          material -= 3000;
        } 

        if(temVal == 3)
        {
          material -= 3000;
        } 

        if(temVal == 5)
        {
          material -= 5000;
        } 

        if(temVal == 9)
        {
          material -= 9000;
        }

        if(temVal == 10)
        {
          material -= 20000;
        }    

      }
      
    }
  }

  return material;

}



uint32_t Evaluate(uint8_t yin, uint8_t xin, uint8_t yf,  uint8_t xf)
{
  int Evaluation;
  int32_t whiteEval = countWhiteMaterial(yin, xin, yf, xf);
  int32_t blackEval = countBlackMaterial(yin, xin, yf, xf);

   Evaluation = whiteEval + blackEval;

  return Evaluation;


}

void clearGenerateLegalMoves()
{
  for(int i = 0; i < 2500; i++)
  {
    for(int j = 0; j < 3; j++)
    {

      allPossMovesWhite[i][j] = 0;
      allPossMovesBlack[i][j] = 0;

    }
  }
}

void GenerateLegalWhiteMoves()
{
  uint32_t count = 0;
  uint8_t yin;
  uint8_t xin;
  uint8_t yf;
  uint8_t xf;
  uint8_t res;


for(int i = 0; i < 8; i++)
{
for(int j = 0; j < 8; j++) 
{

for(int k = 0; k < 8; k++)
{

for(int l = 0; l < 8; l++) // check all 4096 differnt possibilites of moves that could be made for initial moves and final moves (most are illegal :( )
{
   yin = i;
  xin = j;
  yf = k;
  xf = l;
  uint8_t currentID = PieceIDBot(yin,xin);
  uint8_t futureID = PieceIDBot(yf,xf);

  check = true;
  bot = false;

  if(currentID > 10)
  {


  if(currentID == 11) // if currentID is a pawn
  {
    res = makePawnMove(yin,xin,yf,xf); // move the pawn if possible
    
  }

  if(currentID == 12) // if currentID is a knight
  {

    res = makeKnightMove(yin,xin,yf,xf); // move the knight if possible

  }

  if(currentID == 13) // if currentID is a bishop
  {

    res = makeBishopMove(yin,xin,yf,xf); // move the bishop if possible

  }

  if(currentID == 15) // if currentID is a rook
  {

    res = makeRookMove(yin,xin,yf,xf); // move the rook if possible

  }

  if(currentID == 19) // if currentID is a queen
  {

    res = makeQueenMove(yin,xin,yf,xf); // move the queen if possible

  }

  if(currentID == 20) // if currentID is a king
  {

    res = makeKingMove(yin,xin,yf,xf); // move the king if possible

  }

  if(currentID == 0) // if selected piece doesn't exist
  {
    res = 0; // result is automatically 0 since selected piece is nothing
  }

  if(res == 1)
  {

    allPossMovesWhite[count][0] = yin;
    allPossMovesWhite[count][1] = xin;
    allPossMovesWhite[count][2] = yf;
    allPossMovesWhite[count][3] = xf;
    count++;
    
  }

}
}
}
}
    
}

allPossMovesWhite[count][0] = 10;
    allPossMovesWhite[count][1] = 10;
    allPossMovesWhite[count][2] = 10;
    allPossMovesWhite[count][3] = 10;
    check = false;
    bot = true;
    countofBigArray = count;
}


void GenerateLegalBlackMoves()
{
  uint32_t count = 0;
  uint8_t yin;
  uint8_t xin;
  uint8_t yf;
  uint8_t xf;
  uint8_t res;


for(int i = 0; i < 8; i++)
{
for(int j = 0; j < 8; j++) 
{

for(int k = 0; k < 8; k++)
{

for(int l = 0; l < 8; l++) // check all 4096 differnt possibilites of moves that could be made for initial moves and final moves (most are illegal :( )
{
   yin = i;
  xin = j;
  yf = k;
  xf = l;
  uint8_t currentID = PieceIDBot(yin,xin);
  uint8_t futureID = PieceIDBot(yf,xf);

  check = true;
  bot = false;

  if((currentID < 11) && (currentID != 0))
  {


  if(currentID == 1) // if currentID is a pawn
  {
    res = makePawnMove(yin,xin,yf,xf); // move the pawn if possible
    
  }

  if(currentID == 2) // if currentID is a knight
  {

    res = makeKnightMove(yin,xin,yf,xf); // move the knight if possible

  }

  if(currentID == 3) // if currentID is a bishop
  {

    res = makeBishopMove(yin,xin,yf,xf); // move the bishop if possible

  }

  if(currentID == 4) // if currentID is a rook
  {

    res = makeRookMove(yin,xin,yf,xf); // move the rook if possible

  }

  if(currentID == 5) // if currentID is a queen
  {

    res = makeQueenMove(yin,xin,yf,xf); // move the queen if possible

  }

  if(currentID == 6) // if currentID is a king
  {

    res = makeKingMove(yin,xin,yf,xf); // move the king if possible

  }

  if(currentID == 0) // if selected piece doesn't exist
  {
    res = 0; // result is automatically 0 since selected piece is nothing
  }

  if(res == 1)
  {

    allPossMovesBlack[count][0] = yin;
    allPossMovesBlack[count][1] = xin;
    allPossMovesBlack[count][2] = yf;
    allPossMovesBlack[count][3] = xf;
    count++;
    
  }

}
}
}
}
    
}

allPossMovesBlack[count][0] = 10;
    allPossMovesBlack[count][1] = 10;
    allPossMovesBlack[count][2] = 10;
    allPossMovesBlack[count][3] = 10;
    check = false;
    bot = true;
    countofBigArray = count;
}

void createFirstArr()
{
  int i = -1;
  do {
  i++;
  firstWhiteMoves[i][0] = allPossMovesWhite[i][0];
  firstWhiteMoves[i][1] = allPossMovesWhite[i][1];
  firstWhiteMoves[i][2] = allPossMovesWhite[i][2];
  firstWhiteMoves[i][3] = allPossMovesWhite[i][3];
  
  }while (allPossMovesWhite[i][0] != 10);
}

int PieceValMoved(uint8_t yin, uint8_t xin, uint8_t yf, uint8_t xf)
{

  int res;
  uint8_t currentID = PieceIDBot(yin,xin);
  uint8_t futureID = PieceIDBot(yf,xf);
  

  if(futureID == 11) // if currentID is a pawn
  {
    res = pawnWhiteValues[yf][xf]; // move the pawn if possible
    
  }

  if(futureID == 12) // if currentID is a knight
  {

    res = knightWhiteValues[yf][xf]; // move the knight if possible

  }

  if(futureID == 13) // if currentID is a bishop
  {

    res = bishopWhiteValues[yf][xf]; // move the bishop if possible

  }

  if(futureID == 15) // if currentID is a rook
  {

    res = rookWhiteValues[yf][xf]; // move the rook if possible

  }

  if(futureID == 19) // if currentID is a queen
  {

    res = queenWhiteValues[yf][xf]; // move the queen if possible

  }

  if(futureID == 20) // if currentID is a king
  {

    res = kingWhiteValues[yf][xf]; // move the king if possible

  }

  if(futureID == 1) // if currentID is a pawn
  {
    res = -1*pawnBlackValues[yf][xf]; // move the pawn if possible
    
  }

  if(futureID == 2) // if currentID is a knight
  {

    res = -1*knightBlackValues[yf][xf]; // move the knight if possible

  }

  if(futureID == 3) // if currentID is a bishop
  {

    res = -1*bishopBlackValues[yf][xf]; // move the bishop if possible

  }

  if(futureID == 5) // if currentID is a rook
  {

    res = -1*rookBlackValues[yf][xf]; // move the rook if possible

  }

  if(futureID == 9) // if currentID is a queen
  {

    res = -1*queenBlackValues[yf][xf]; // move the queen if possible

  }

  if(futureID == 10) // if currentID is a king
  {

    res = -1*kingBlackValues[yf][xf]; // move the king if possible

  }

  if(futureID == 0) // if selected piece doesn't exist
  {
    res = 0; // result is automatically 0 since selected piece is nothing
  }

  if(isInCheckmate())
  {
    if(futureID > 10)
    {
      res -= 2000;
    }
    else {
    res += 2000;
    }
    
  }

  return res;

}



int Max(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int Min(int a, int b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}




// Alpha-Beta Pruning with Cleaned-Up Logic


uint8_t yin = 0;
  uint8_t xin = 0;
  uint8_t yf = 0;
  uint8_t xf = 0;
  uint8_t currentID;
  bool isRecivingdata = false;
  int MyMaxValue = -100000;
int miniMax(int evaluation, int depth, int alpha, int beta, bool isWhite, uint8_t yin, uint8_t xin, uint8_t yf, uint8_t xf)
{
  
  GPIOA->DOUTTGL31_0 = (1 << 16);
  uint8_t arrcounts = 0;
  bot = true;
  Searchcount++;
  
  int maxEval;
  
  int minEval;
  int eval;
  int tempEval;
  int temp;
  int temp1;
  
  if(depth == 0)
  {
    
    temp = Evaluate(yin, xin, yf, xf);
    temp1 = PieceValMoved(yin, xin, yf, xf);
    temp = temp + temp1;
    tempEval = temp;

    if ((tempEval > MyMaxValue)) {
                

                // Save best move
                botYin = yin;
                botXin = xin;
                botYf = yf;
                botXf = xf;
            }
        MyMaxValue = Max(MyMaxValue, tempEval);
    restoreChessboardBot();
    return temp;
  }

  if(isWhite)
  {
    maxEval = -100000;
    arrcounts = 0;
    GenerateLegalWhiteMoves();
    while(allPossMovesWhite[arrcounts][0] != 10)
    {
    yin = allPossMovesWhite[arrcounts][0];
    xin = allPossMovesWhite[arrcounts][1];
    yf = allPossMovesWhite[arrcounts][2];
    xf = allPossMovesWhite[arrcounts][3];
    arrcounts++;
    if(PieceID(yin, xin) > 10)
    {
      saveChessboardNumBot();  
      makeMove(yin, xin, yf, xf);
      
      //tempEval = Evaluate(yin, xin, yf, xf) + PieceValMoved(yin, xin, yf, xf);
      
      
      

      eval = miniMax(tempEval, (depth -1) , alpha, beta, false, yin, xin, yf, xf);
      
     

      

      maxEval = Max(maxEval, eval);
      alpha = Max(alpha, eval);

      

      if(beta <= alpha)
      {
        break;
      }

    }
    }

    
    return maxEval;
    

  }
  else 
  {

    minEval = 100000;
    arrcounts = 0;
    GenerateLegalBlackMoves();
    while(allPossMovesBlack[arrcounts][0] != 10)
    {
    yin = allPossMovesBlack[arrcounts][0] ;
    xin = allPossMovesBlack[arrcounts][1];
    yf = allPossMovesBlack[arrcounts][2];
    xf = allPossMovesBlack[arrcounts][3];
    arrcounts++;
    if(PieceID(yin, xin) < 11)
    {
      saveChessboardNumBot();  
      makeMove(yin, xin, yf, xf);
      
      //tempEval = Evaluate(yin, xin, yf, xf) + PieceValMoved(yin, xin, yf, xf);
      tempEval = tempEval;
      

      eval = miniMax(tempEval, depth -1 , alpha, beta, true, yin, xin, yf, xf);
      minEval = Min(minEval, eval);
      beta = Min(beta, eval);
      if(beta <= alpha)
      {
        break;
      }

     

      

    }
    }

    
    return minEval;
  
  }
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
    makeMove(6,2,4,2);
    
    makeMove(7,3,4,0);
    
    makeMove(6,3,3,0);
    
    makeMove(3,0,4,0);
    
    makeMove(1,3,3,3);
    
    makeMove(4,0,1,3);
    
    makeMove(0,3,1,3);
    
    */

    makeMove(6,2,4,2);
    makeMove(1,3, 3,3);
    
    makeMove(7,3,4,0);
    
    
   
    printmyArray();
    statusOfBoard();
    
    

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

    

    
        

        invalidMove = false;



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

void joyStickReadingsBot()
{

  uint32_t res;
  res = ButtonIn();
  ADC_InitTriple(ADC1, 4, 5, 6, ADCVREF_VDDA);
  uint32_t temp;
  uint32_t Position;
  mySysTick_IntArm(0, 0);
  
  

    

  // initialize semaphore

  Time = 0;
  __enable_irq();
  while(1){
    mySysTick_IntArm(0, 0);
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

 uint32_t xtemp;
uint32_t ytemp;
TimerG0counts = 0;



  drawHollowBox();

 
   while(TimerG0counts != 4000)
 {

 
  xtemp = 4096 - x;
  ytemp = y;

  if(xtemp > 3700)
  {
    if(xarr < 8)
    {

    xarr++;
    xplot+=16;
    mySysTick_Stop();
    

    }

    break;
    
    

  }

  if(xtemp < 300)
  {
    if(xarr > 1)
    {

    xarr--;
    xplot-=16;
    mySysTick_Stop();
    

    }

    break;
    
    

  }

  if(ytemp > 3700)
  {
    if(yarr < 8)
    {

    yarr++;
    yplot+=20;
    mySysTick_Stop();
    

    }

    break;
    
    

  }

  if(ytemp < 300)
  {
    if(yarr > 1)
    {

    yarr--;
    yplot-=20;
    mySysTick_Stop();
    

    }

    break;
    

  }

  if(doubleclick == 2)
  {
    break;
  }
  
 }

  

  if((agreeddraw != 1) || actMiniMax)
  {

    

    if(actMiniMax)
  {

    bothasran = true;

      needtoCheck = true;
      needtoCheckmate = true;
      bool breakoutofloop = false;


      if(isInCheck())
      {
        for(int i = 0; i < 8; i++)
        {
          if(breakoutofloop)
          {
            break;
          }
          for(int j = 0; j < 8; j++)
          {
            if(breakoutofloop)
            {
              break;
            }
            for(int k = 0; k < 8; k++)
            {
              if(breakoutofloop)
              {
                break;
              }
              for(int l = 0; l < 8; l++)
              {

                isplacing = true;
                check = false;
                SpecialsaveChessboardNum();
                restoreChessboardBotReset();
                GPIOA->DOUTTGL31_0 = (1 << 16);
                if(PieceID(i, j) > 10)
                {

                  makeMove(i, j, k, l);

                }
                
                if(!isInCheck())
                {
                  yin1 = i;
                  xin1 = j;
                  yf1 = k;
                  xf1 = l;
                  breakoutofloop = true;
                  canBotDeflectCheck = true;
                  whitewon = 0;
                  blackwon = 0;
                  SpecialRestoreChessboardNum();
                restoreChessboardBotReset();
                  
                }
                SpecialRestoreChessboardNum();
                restoreChessboardBotReset();
                isplacing = false;
                check = true;
                if(breakoutofloop)
                {
                  break;
                }

              }
            }
          }
        }

        if(isInCheckmate())
        {

        }

        needtoCheck = false;
        needtoCheckmate = false;

        
      }

      else {

        needtoCheck = false;
        needtoCheckmate = false;

        
      
      

      

      int32_t temp;

      restoreChessboardBotReset();
      SpecialRestoreChessboardNum();
      restoreChessboardNum();
      restoreChessboardBot();

      temp = Evaluate(0, 0, 0, 0);
      clearGenerateLegalMoves();
      saveChessboardNum();
      saveChessboardNumBot();
      SpecialsaveChessboardNum();
      //GenerateLegalMoves();
      TimerG0counts = 0;


      miniMax(0,3, -100000, 100000, true, 0, 0, 0, 0);
      player1Mode = true;
      MyMaxValue = -100000;

      yin1 = botYin;
      xin1 = botXin;
      yf1 = botYf;
      xf1 = botXf;

    
      
      

      restoreChessboardBotReset();
      SpecialRestoreChessboardNum();
      restoreChessboardNum();
      restoreChessboardBot();
      

      bot = false;
      check = false;

      restoreChessboardBotReset();
      



      

      
      
    }

      
     
      isplacing = true;
      bot = true;
      check = false;

      
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

    invalidMove = false;
        

        



      }
    }

    isplacing = false;
      bot = false;
      check = true;





  }

    actMiniMax = false;
  if(doubleclick == 2)
  {
    doubleclick = 0;

  
    isplacing = true;
      bot = true;
      check = false;
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

    

    
        

        invalidMove = false;



      }

      
    }
    bothasran = true;
  }

  isplacing = false;
      bot = false;
      check = true;
    if(!invalidMove && bothasran)
    {
      TimerG0counts = 0;
      mySysTick_IntArm(7256, 0);
        TimerG0_IntArm(7256, 0, 0);
        TimerG12_IntArm(0,0);
        Sound_Init();
      while(TimerG0counts != 4)
      {

        
        
      }
      mySysTick_IntArm(0, 0);
        TimerG0_IntArm(1, 0, 0);
        TimerG12_IntArm(1333333,0);
      TimerG0counts = 0;
    }

    bothasran = false;

    
  }

}  

  

  

    

  




void setup(void)
{
   uint16_t lightBrown = ST7735_Color565(210, 180, 140);   // Example Tan
uint16_t darkBrown = ST7735_Color565(101, 67, 33);  
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

    getSwitch = ButtonIn();
    
      
      if (vol > 3072){
        ST7735_DrawSmallCircle(64, 30, ST7735_WHITE);
        ST7735_DrawSmallCircle(64, 60, ST7735_BLACK);
        ST7735_DrawSmallCircle(64, 90, ST7735_BLACK);  
        ST7735_DrawSmallCircle(64, 120, ST7735_BLACK);    
      }
       if (vol <= 3072 && vol > 2048 )
      {

        ST7735_DrawSmallCircle(64, 30, ST7735_BLACK);
        ST7735_DrawSmallCircle(64, 60, ST7735_WHITE);
        ST7735_DrawSmallCircle(64, 90, ST7735_BLACK);  
        ST7735_DrawSmallCircle(64, 120, ST7735_BLACK); 

      }
       if (vol <= 2048 && vol > 1024){
        ST7735_DrawSmallCircle(64, 30, ST7735_BLACK);
        ST7735_DrawSmallCircle(64, 60, ST7735_BLACK);
        ST7735_DrawSmallCircle(64, 90, ST7735_WHITE);  
        ST7735_DrawSmallCircle(64, 120, ST7735_BLACK); 
      }

       if (vol <= 1024 ){
        ST7735_DrawSmallCircle(64, 30, ST7735_BLACK);
        ST7735_DrawSmallCircle(64, 60, ST7735_BLACK);
        ST7735_DrawSmallCircle(64, 90, ST7735_BLACK);  
        ST7735_DrawSmallCircle(64, 120, ST7735_WHITE); 
      }
      
    

    if (vol > 3072 && (getSwitch == 16)){

      screen0 = 1;
      chosenLanguage = 5; //E
      player1Mode = false;
      actMiniMax = false;
      bot = false;

    }

     if(vol <= 3072 && vol > 2048 && (getSwitch == 16))
    {

      screen0 = 1;
      chosenLanguage = 5; //E
      player1Mode = true;
      actMiniMax = true;
      bot = true;

    }

     if(vol <= 2048 && vol > 1024 && (getSwitch == 16))
    {

      screen0 = 1;
      chosenLanguage = 10; //E
      player1Mode = false;
      actMiniMax = false;
      bot = false;

    }

     if (vol <= 1024 && (getSwitch == 16)){

      screen0 = 1;
      chosenLanguage = 10; //S
      player1Mode = true;
      actMiniMax = true;
      bot = true;

    }

    ST7735_SetCursor(3, 3);
    ST7735_OutString("English 2 Players");
    ST7735_SetCursor(3, 6);
    ST7735_OutString("English 1 Player");
    ST7735_SetCursor(3, 9);
    ST7735_OutString("Espa\xA4ol 2 jugadores");
    ST7735_SetCursor(3, 12);
    ST7735_OutString("Espa\xA4ol 1 jugador");

  }

  TimerG0counts = 0;
  while(getSwitch != 0)
  {
    getSwitch = ButtonIn();

  }


  
  __enable_irq();

  ST7735_FillScreen(ST7735_BLACK);
  
  //getSwitch = Switch_In();

  while(getSwitch == 0){

     getSwitch = ButtonIn();

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

    buttonclicked = ButtonIn();
    
    

  }

  



 
  GPIOA->DOUTSET31_0 = (1 << 17);
  screen0 = 0;





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

  TimerG0_IntArm(7256, 0, 0);

  TimerG0counts = 0;

  while(TimerG0counts != 110)
  {



  }
}






int main11(void) //driver Code
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

int main12(void) //testing bot
{

  TimerG0_IntArm(7256, 0, 0);



while(1)
{
  

}
}






int main(void) //driver Code 13
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
  if((agreeddraw != 1) && (blackwon != 1) && (whitewon != 1) && !player1Mode)
  {
    joyStickReadings();
  }
  

  else if((agreeddraw != 1) && (blackwon != 1) && (whitewon != 1) && player1Mode)
  {
    joyStickReadingsBot();
  }
  else {

    score();
    

  

  setup();
  }
  
  }
  
  


return 0;

}

int main14(void)
{ int temp;
while(1)
{

  PieceValMoved(0, 1, 2, 0);
  temp = PieceValMoved(0, 1, 2, 2);
  temp = temp;

}
  
}

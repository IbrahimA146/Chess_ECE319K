// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// Your name
// Last Modified: 12/26/2024

#include <stdio.h>
#include <stdint.h>
#include <string.h>
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
#include "sounds.h"
#include "chess_sprites.h"
#include "images/images.h"
// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
static uint8_t toggle = 0;
uint8_t screen0 = 0; // used to cahnge screens 
uint8_t currentFrame = 0;
uint8_t updateFrame = 0;
uint8_t getSwitch = 0;
uint8_t chosenLanguage = 0; // 5 = spanish, 10 = english
#define NUM_FRAMES 4


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


// games  engine runs at 30Hz
void TIMG0_IRQHandler(void){uint32_t pos,msg;
  if((TIMG0->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
// game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    // 4) start sounds
    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)


    updateFrame = 1; 
    currentFrame = (currentFrame + 1) % NUM_FRAMES;


  }
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
int main(void){ // main2

  __disable_irq();
  PLL_Init(); // set bus speed
  Switch_Init(); 
  LaunchPad_Init();
  ST7735_InitPrintf();


    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()


  ST7735_FillScreen(ST7735_BLACK);  // Clear the screen
  ST7735_SetTextColor(ST7735_YELLOW);
    
  while (!screen0){

    getSwitch = Switch_In();
    if (getSwitch == 1){

      screen0 = 1;
      chosenLanguage = 5;

    }

    else if (getSwitch == 2){

      screen0 = 1;
      chosenLanguage = 10;

    }

    ST7735_SetCursor(1, 1);
    ST7735_OutString("Press 1 for English");
    ST7735_SetCursor(1, 3);
    ST7735_OutString("Press 2 for Spanish\n\n ....................");
    ST7735_SetCursor(3, 7);
    ST7735_OutString("Presione 1 para");
    ST7735_SetCursor(7, 9);
    ST7735_OutString("Ingl\x82s");
    ST7735_SetCursor(3, 11);
    ST7735_OutString("Presione 2 para");
    ST7735_SetCursor(7, 13);
    ST7735_OutString(" Espa\xA4ol");


  }

  
    TimerG0_IntArm(40000000, 4999, 0);
  
  __enable_irq();

  ST7735_FillScreen(ST7735_BLACK);
  
  //getSwitch = Switch_In();

  while(1){

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
          break;
        case 1:
          ST7735_DrawBitmap(32, 105, rot3, 64, 64);
          break;
        case 2:
          ST7735_DrawBitmap(32, 105, rot5, 64, 64);
          break;
        case 3:
          ST7735_DrawBitmap(32, 105, rot3, 64, 64);
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
          break;
        case 1:
          ST7735_DrawBitmap(32, 105, rot3, 64, 64);
          break;
        case 2:
          ST7735_DrawBitmap(32, 105, rot5, 64, 64);
          break;
        case 3:
          ST7735_DrawBitmap(32, 105, rot3, 64, 64);
          break;
      }
      }
           
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
        Sound_Tick(); // call one of your sounds
      }

      /*
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

      */

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
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
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

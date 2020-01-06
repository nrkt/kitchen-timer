#include "enpitshield.h"

static boolean bCurLed1;

void Led1_Init(){ //初期化
  bCurLed1 = LED_OFF; //消灯
  digitalWrite(LED1, LED_OFF);

  return;
}

void Led1_Light(){
  if (bCurLed1 == LED_OFF){ //前回消灯なら
    bCurLed1 = LED_ON; //点灯
  }
  else{ //前回点灯なら
    bCurLed1 = LED_OFF; //消灯
  }

  digitalWrite(LED1, bCurLed1);

  return;
}

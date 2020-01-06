#include "enpitshield.h"

static boolean bCurLed0;

void Led0_Init(){ //初期化
  bCurLed0 = LED_OFF; //消灯
  digitalWrite(LED0, LED_OFF);

  return;
}

void Led0_Tick05(){ //call by 0.5s
  if (bCurLed0 == LED_OFF){ //前回消灯なら
    bCurLed0 = LED_ON; //点灯
  }
  else{ //前回点灯なら
    bCurLed0 = LED_OFF; //消灯
  }

  digitalWrite(LED0, bCurLed0);

  return;
}

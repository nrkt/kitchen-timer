#include "enpitshield.h"


static boolean bCurLed3;
static int count;

void Led3_Init(){ //初期化
  bCurLed3 = LED_OFF; //消灯
  count = 0; //回数0
  digitalWrite(LED3, LED_OFF);

  return;
}

void Led3_Tick025(){ //call by 0.25s
  if (count < 4 && bCurLed3 == LED_OFF){ //1s以下　かつ　消灯なら
    bCurLed3 = LED_ON; //点灯
  }
  else if (count < 4 && bCurLed3 == LED_ON){ //1s以下　かつ　点灯なら
    bCurLed3 = LED_OFF; //消灯
  }
  digitalWrite(LED3, bCurLed3);
  CountBlink();
  return;
}


void CountBlink(){ //呼び出された回数カウント(0.25sごとに+1)
  count++;
  if (count == 20){ //5sなら0sに戻す
    count = 0;
  }
}

void EndBlink(){
  if(bCurLed3 == LED_ON){
    bCurLed3 = LED_OFF;
  }
  else{
    bCurLed3 = LED_ON;
  }
  digitalWrite(LED3, bCurLed3);
  return;
}

void Led3_Off(){
}

#include "enpitshield.h"

static boolean bCurSw1;
static boolean sw1_1;
static boolean sw1_2;
static boolean sw1_3;

void Sw1_Init(){ //初期化
  bCurSw1 = false; //押されていない
  sw1_1 = false;
  sw1_2 = false;
  sw1_3 = false;
  return;
}

boolean IsSw1(void){ //call by 0.01s
  boolean CurSw1;
  sw1_3 = sw1_2; //2つ前のスイッチ1の状態
  sw1_2 = sw1_1; //1つ前のスイッチ1の状態
  sw1_1 = digitalRead(TACTSW1); //現在のスイッチ1の状態
  if ( sw1_1 & sw1_2 & sw1_3 ){ //3回のスイッチ1状態が全てONなら
    CurSw1 = true;
  }
  else{
    CurSw1 = false;
  }
  if (CurSw1){ //押されているなら
    if (bCurSw1 == CurSw1){ //前回とスイッチ1の状態が一致するなら
      return SW_OFF; //押されていないを返す
    }
    else{ //前回とスイッチ1の状態が一致しないなら
      bCurSw1 = CurSw1; //前回の状態を更新
      return SW_PUSHED; //押されたを返す
    }
  }
  else{ //押されていないなら
    bCurSw1 = CurSw1;
    return SW_OFF; //押されていないを返す
  }
}

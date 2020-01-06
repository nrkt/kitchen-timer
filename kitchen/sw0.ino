#include "enpitshield.h"

static boolean bCurSw0;
static boolean sw0_1;
static boolean sw0_2;
static boolean sw0_3;

void Sw0_Init(){ //初期化
  bCurSw0 = false; //押されていない
  sw0_1 = false;
  sw0_2 = false;
  sw0_3 = false;
  
  return;
}

boolean IsSw0(void){ //call by 0.01s
  boolean CurSw0;
  sw0_3 = sw0_2; //2つ前のスイッチ0の状態
  sw0_2 = sw0_1; //1つ前のスイッチ0の状態
  sw0_1 = digitalRead(TACTSW0); //現在のスイッチ0の状態
  if (sw0_1 & sw0_2 & sw0_3){ //3回のスイッチ0の状態が全てONなら
    CurSw0 = true;
  }
  else{
    CurSw0 = false;
  }
  if (CurSw0){ //押されているなら
    if (bCurSw0 == CurSw0){ //前回とスイッチ0の状態が一致するなら
      return SW_OFF; //押されていないを返す
    }
    else{ //前回とスイッチ0の状態が一致しないなら
      bCurSw0 = CurSw0; //前回の状態を更新
      return SW_PUSHED; //押されたを返す
    }
  }
  else{ //押されていないなら
    bCurSw0 = CurSw0;
    return SW_OFF; //押されていないを返す
  }
}

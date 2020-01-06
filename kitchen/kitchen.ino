#include "enpitshield.h"
#include <MsTimer2.h>

#define TIMER_CYCLE 10
#define _15SEC 1500
#define _30SEC 3000
#define _60SEC 6000
#define BEAT 300

enum State { STATE_STOP, STATE_MOVE, STATE_FINISH };
static int TimeUp;
static int FinishTime;
static int Led0Count;
static int Led3Count;
static int CurState;
static int SongCount;
static int Sound[8] = {262, 294, 330, 349, 392, 440, 494, 523};
static int Song[15] = {392,440,494,494,440,392,0,392,440,494,440,392,440,440,0};

void setup() {
  // put your setup code here, to run once:
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(TACTSW0,INPUT);
  pinMode(TACTSW1,INPUT);
  pinMode(SPEAKER,OUTPUT);
  
  Led0_Init();
  Led1_Init();
  Sw0_Init();
  Sw1_Init();
  enum State CurState;
  CurState = STATE_STOP;
  TimeUp = _30SEC;
  FinishTime = _15SEC;
  Led0Count = 0;
  Led3Count = 0;
  SongCount = 0;
  
  //Serial.begin(9600);
  MsTimer2::set(TIMER_CYCLE, TimerDrv);
  MsTimer2::start();

}

void TimerDrv(){  //call by 0.01s
  //Serial.println(TimeUp, DEC);
  //Serial.println(Led3Count, DEC);
   if(Led0Count % 50 == 0){ //0.01s*50 = 0.5s
    Led0Count = 0; //0sに戻す
    Led0_Tick05(); //LED0点滅
   }
   Led0Count++; //+0.01s
   switch(CurState){
    case STATE_STOP:
      //停止中の処理
      noTone(SPEAKER);
      SongCount = 0;
      if(IsSw0()){ //sw0押下
        Led3_Init(); //LED3初期化
        CurState = STATE_MOVE; //動作中に遷移
        Led3Count = 0; //0sに初期化
        break;
      }
      if(IsSw1()){ //sw1押下
        //時間変更、LED1制御
        Led1_Light();
        if(TimeUp == _30SEC){ //30sモードなら60sモードに
          TimeUp = _60SEC;
        }
        else{ //60sモードなら30sモードに
          TimeUp = _30SEC;
        }
      }
      break;
      
    case STATE_MOVE:
      //動作中の処理
      if(Led3Count % 25 == 0){ //0.01s * 25 = 0.25s
        Led3_Tick025(); //LED3点滅
      }
      if(IsSw0()){ //sw0押下
        if(TimeUp == _60SEC){ //60sモードなら30sモードに
          Led1_Light();
          TimeUp = _30SEC;
        }
        Led3_Init(); //LED3初期化
        CurState = STATE_STOP; //停止中に遷移
        break;
      }
      if(Led3Count == TimeUp){ //timeupなら
        CurState = STATE_FINISH; //終了通知中に遷移
        Led3Count = 0; //0sに初期化
        break;
      }
      Led3Count++; //0.01s追加
      break;
      
    case STATE_FINISH:
      //終了通知中の処理
      if(Led3Count % 25 == 0){ //0.01s * 25 = 0.25s
        EndBlink(); //終了点滅
      }
      if(IsSw0() || Led3Count == FinishTime){ //sw0押下 または 15sカウント終了
        if(TimeUp == _60SEC){ //60sモードなら
          Led1_Light(); //LED1消灯
          TimeUp = _30SEC; //30sモードにする
        }
        CurState = STATE_STOP; //停止中に遷移
        Led3_Init(); //LED3初期化
        break;
      }
      Led3Count++; //0.01s追加
      if(Led3Count % 30 == 0){
        tone(SPEAKER,Song[SongCount%15]);
        SongCount++;
        if(SongCount == 15){
          SongCount = 0;
        }
      }
      break;
  }

  return;
}

void loop(){
  
}

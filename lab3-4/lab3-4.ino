#include <FreeRTOS_AVR.h>
#define MS2TICKS(ms) (ms/portTICK_PERIOD_MS)
#define FND_SIZE 6

const int Keypad[4]={2,3,21,20};
const int FndSelectPin[6]={22,23,24,25,26,27};
const int FndPin[8]={30,31,32,33,34,35,36,37};
const int FndFont[10]={0x3F,0x06,0x5B,0x4F,0x66,0x60,0x7D,0x07,0x7F,0x67};

SemaphoreHandle_t Sem;

int SendValue=0;
int Fnd[FND_SIZE]={0,};

void ShiftInsert(int data){
  int i;
  for(i=0;i<FND_SIZE;i++){
    Fnd[FND_SIZE-i]=Fnd[FND_SIZE-i-1];
    }
  Fnd[0]=data;
  }

void KeypadControl1(){
  delay(50);
  SendValue=1;
  xSemaphoreGive(Sem);
  }
void KeypadControl2(){
  delay(50);
  SendValue=2;
  xSemaphoreGive(Sem);
  }
void KeypadControl3(){
  delay(50);
  SendValue=3;
  xSemaphoreGive(Sem);
  }
void KeypadControl4(){
  delay(50);
  SendValue=4;
  xSemaphoreGive(Sem);
  }
void KeypadTask(void* arg){
  int i;
  int keypad;
  while(1){
    if(xSemaphoreTake(Sem,portMAX_DELAY)){
      keypad=SendValue;
      ShiftInsert(keypad);
      }
    }
  }
void FndSelect(int pos){
    int i;
    for(i=0;i<6;i++){
      if(i==pos){
          digitalWrite(FndSelectPin[i],LOW);
        }
      else{
          digitalWrite(FndSelectPin[i],HIGH);
        }
      }
  }

void FndDisplay(int pos,int num){
  int i;
  int flag=0;
  int shift=0x01;
  FndSelect(pos);
  for (i=0;i<8;i++){
    flag=(FndFont[num]&shift);
    digitalWrite(FndPin[i],flag);
    shift<<=1;
    }
  }
void FndTask(void* arg){
  int i;
  while(1){
    for(i=0;i<FND_SIZE;i++){
      delay(3);
      FndDisplay(i,Fnd[i]);
      }
    }
  }
void setup() {
  // put your setup code here, to run once:
  int i;
  for(i=0;i<6;i++){
    pinMode(FndSelectPin[i],OUTPUT);
    }
  for(i=0;i<8;i++){
    pinMode(FndPin[i],OUTPUT);
    }
  for(i=0;i<4;i++){
    pinMode(Keypad[i],INPUT);
    }
  attachInterrupt(0,KeypadControl1,RISING);
  attachInterrupt(1,KeypadControl2,RISING);
  attachInterrupt(2,KeypadControl3,RISING);
  attachInterrupt(3,KeypadControl4,RISING);

  vSemaphoreCreateBinary(Sem);
  
  xTaskCreate(KeypadTask,NULL,200,NULL,2,NULL);
  xTaskCreate(KeypadTask,NULL,200,NULL,1,NULL);
  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:

}

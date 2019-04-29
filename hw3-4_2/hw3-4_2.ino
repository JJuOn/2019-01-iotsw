#include <FreeRTOS_AVR.h>

const int MT_P=10;
const int MT_N=9;

const int LeftKey=2;
const int StopKey=3;
const int RightKey=21;

SemaphoreHandle_t Sem1,Empty, Full;
int in=0;
int out=0;
int N=3;
uint16_t sendValue;
uint16_t CQueue[3]={};
  void LeftKeyControl(){
      sendValue=1;
      //Serial.println("sendValue : ");
      //Serial.println(sendValue);
  }
  void StopKeyControl(){
      sendValue=2;
      //Serial.println("sendValue : ");
      //Serial.println(sendValue);
  }
  void RightKeyControl(){
      sendValue=3;
      //Serial.println("sendValue : ");
      //Serial.println(sendValue);
  }

  void MotorTask(void* arg){
    while(1){
      if(xSemaphoreTake(Full,portMAX_DELAY)<=N){
        if(xSemaphoreTake(Sem1,portMAX_DELAY)){
          uint16_t receiveValue=CQueue[out];
          out=(out+1)%N;
          //Serial.println("recieveValue : ");
          //Serial.println(receiveValue);
          if(receiveValue==1){
            digitalWrite(MT_P,LOW);
            digitalWrite(MT_N,HIGH);
            }
          else if(receiveValue==2){
            digitalWrite(MT_P,LOW);
            digitalWrite(MT_N,LOW);
          }
          else if(receiveValue==3){
            digitalWrite(MT_P,HIGH);
            digitalWrite(MT_N,LOW);
          }
        xSemaphoreGive(Sem1);
        xSemaphoreGive(Empty);
        }
      }
     }
   }

  void KeypadTask(void* arg){
    while(1){
      if(xSemaphoreTake(Empty,portMAX_DELAY)>=0){
        if(xSemaphoreTake(Sem1,portMAX_DELAY)){
           CQueue[in]=sendValue;
           in=(in+1)%N;
           xSemaphoreGive(Sem1);
           xSemaphoreGive(Full);
          }
        }
      }
    }
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(MT_P,OUTPUT);
  pinMode(MT_N,OUTPUT);

  pinMode(LeftKey,INPUT);
  pinMode(StopKey,INPUT);
  pinMode(RightKey,INPUT);
  
  attachInterrupt(0,LeftKeyControl,RISING);
  attachInterrupt(1,StopKeyControl,RISING);
  attachInterrupt(2,RightKeyControl,RISING);

  Empty=xSemaphoreCreateCounting(N,N);
  Full=xSemaphoreCreateCounting(N,0);
  Sem1=xSemaphoreCreateMutex();
  
  xTaskCreate(MotorTask,NULL,200,NULL,2,NULL);
  xTaskCreate(KeypadTask,NULL,200,NULL,1,NULL);
  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:

}

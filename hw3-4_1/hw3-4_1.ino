#include <FreeRTOS_AVR.h>

const int MT_P=10;
const int MT_N=9;

const int LeftKey=2;
const int StopKey=3;
const int RightKey=21;

SemaphoreHandle_t Sem;
uint16_t sendValue=0;
  void LeftKeyControl(){
    sendValue=1;
    xSemaphoreGive(Sem);
  }
  void StopKeyControl(){
    sendValue=2;
    xSemaphoreGive(Sem);
  }
  void RightKeyControl(){
    sendValue=3;
    xSemaphoreGive(Sem); 
  }

  void MotorTask(void* arg){
    while(1){
      if(xSemaphoreTake(Sem,portMAX_DELAY)){
        uint16_t receiveValue=sendValue;
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
        }
      }
   }
  

void setup() {
  // put your setup code here, to run once:
  pinMode(MT_P,OUTPUT);
  pinMode(MT_N,OUTPUT);

  pinMode(LeftKey,INPUT);
  pinMode(StopKey,INPUT);
  pinMode(RightKey,INPUT);

  attachInterrupt(0,LeftKeyControl,RISING);
  attachInterrupt(1,StopKeyControl,RISING);
  attachInterrupt(2,RightKeyControl,RISING);

  vSemaphoreCreateBinary(Sem);
  xTaskCreate(MotorTask,NULL,200,NULL,1,NULL);
  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:

}

#include <FreeRTOS_AVR.h>

const int MT_P=10;
const int MT_N=9;

const int LeftKey=2;
const int StopKey=3;
const int RightKey=21;

const int LeftAccel=20;
const int RightAccel=19;

int i=0;
int j=0;

QueueHandle_t xQueue;

  void LeftKeyControl(){
    uint16_t sendValue=1;
    xQueueSendFromISR(xQueue,&sendValue,0);
  }
  void StopKeyControl(){
    uint16_t sendValue=2;
    xQueueSendFromISR(xQueue,&sendValue,0);
  }
  void RightKeyControl(){
    uint16_t sendValue=3;
    xQueueSendFromISR(xQueue,&sendValue,0);  
  }
  void LeftAccelControl(){
    uint16_t sendValue=4;
    xQueueSendFromISR(xQueue,&sendValue,0);
    }
  void RightAccelControl(){
    uint16_t sendValue=5;
    xQueueSendFromISR(xQueue,&sendValue,0);
    }

  void MotorTask(void* arg){
    uint16_t receiveValue=0;

    while(1){
      if(xQueueReceive(xQueue,&receiveValue,0)){
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
          else if(receiveValue==4){
            if (i==3)
              i=0;
            analogWrite(MT_P,127+64*i);
            analogWrite(MT_N,0);
            i++;
          }
          else if(receiveValue==5){
            if (j==3)
              j=0;
            analogWrite(MT_P,0);
            analogWrite(MT_N,127+64*j);
            j++;
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

  pinMode(LeftAccel,INPUT);
  pinMode(RightAccel,INPUT);

  attachInterrupt(0,LeftKeyControl,RISING);
  attachInterrupt(1,StopKeyControl,RISING);
  attachInterrupt(2,RightKeyControl,RISING);
  attachInterrupt(3,LeftAccelControl,RISING);
  attachInterrupt(4,RightAccelControl,RISING);
  
  xQueue=xQueueCreate(5,sizeof(uint16_t));
  if(xQueue!=NULL){
    xTaskCreate(MotorTask,NULL,200,NULL,1,NULL);
    vTaskStartScheduler();
    }
}

void loop() {
  // put your main code here, to run repeatedly:

}

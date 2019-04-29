#include <FreeRTOS_AVR.h>

#define MS2TICKS(ms) (ms / portTICK_PERIOD_MS )
#define LED1 5
#define LED2 6
void LedTask(int* pParam){
  int led,turn,param=*pParam;
  if(param==1){
    led=LED1;
    turn=HIGH;
    }
  else{
    led=LED2;
    turn=LOW;
    }
   while(1){
      digitalWrite(led,turn);
      vTaskDelay(MS2TICKS(500));
      turn=(turn==HIGH)?LOW:HIGH;
    }
  }
void setup() {
  // put your setup code here, to run once:
  int param[2] = { 1, 2 };
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  xTaskCreate(LedTask, NULL, 200, &param[0], 1, NULL);
  xTaskCreate(LedTask, NULL, 200, &param[1], 2, NULL);

  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:

}

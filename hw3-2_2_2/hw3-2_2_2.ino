#include <FreeRTOS_AVR.h>

#define MS2TICKS(ms) (ms/portTICK_PERIOD_MS)

#define LED 5
#define BUZZER 9

enum { REST=0, DO=262, RE=294, MI=330, FA=349, SOL=392, LA=440, SHI=494, DO2=523 };

int Num = 9;
int Frequency[] = { DO, RE, MI, REST, FA, SOL, LA, SHI, DO2 };
int Delay[] = { 500, 0, 500, 500, 500, 500, 1000, 0, 500 };

void LedTask(void* arg){
  while(1){
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);
    }
  }
void BuzzerTask(void* arg){
  int i;
  while(1){
    for(i=0;i<Num;i++){
      tone(BUZZER,Frequency[i]);
      vTaskDelay(MS2TICKS(Delay[i]));
      }
    }
  }

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  xTaskCreate(LedTask,NULL,200,NULL,1,NULL);
  xTaskCreate(BuzzerTask,NULL,200,NULL,2,NULL);

  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:

}

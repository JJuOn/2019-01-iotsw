#include<MsTimer2.h>

int Button=2;
int Led[3]={5,6,7};

void LedControl(){
  static int counter=0;
  static byte output=HIGH;
  digitalWrite(Led[counter++],output);
  if(counter>1){
    counter=0;
    output=!output;
  }
}

void ButtonLedControl(){
  static byte output=HIGH;
  digitalWrite(Led[2],output);
  output=!output;
}

void setup() {
  // put your setup code here, to run once:
  int i;
  pinMode(Button,INPUT_PULLUP);
  for(i=0;i<3;i++)
    pinMode(Led[i],OUTPUT);
  attachInterrupt(0,ButtonLedControl,RISING);
  MsTimer2::set(500,LedControl);
  MsTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:

}

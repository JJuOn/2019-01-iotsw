#include<MsTimer2.h>

int Button[2]={2,3};
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

void ButtonOn(){
  digitalWrite(Led[2],HIGH);
}
void ButtonOff(){
  digitalWrite(Led[2],LOW);
}
void setup() {
  // put your setup code here, to run once:
  int i;
  pinMode(Button[0],INPUT_PULLUP);
  pinMode(Button[1],INPUT_PULLUP);
  for(i=0;i<3;i++)
    pinMode(Led[i],OUTPUT);
  attachInterrupt(0,ButtonOn,FALLING);
  attachInterrupt(1,ButtonOff,RISING);
  MsTimer2::set(500,LedControl);
  MsTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:

}

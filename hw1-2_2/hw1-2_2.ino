int Led[4]={5,6,7,8};

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<4;i++){
    pinMode(Led[i],OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<4;i+=2){
    digitalWrite(Led[i],HIGH);
    digitalWrite(Led[i+1],HIGH);
    delay(500);
    digitalWrite(Led[i],LOW);
    digitalWrite(Led[i+1],LOW);
    delay(500);
  }
}

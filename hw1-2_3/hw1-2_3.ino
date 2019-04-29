int Led[4]={5,6,7,8};

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<4;i++){
    pinMode(Led[i],OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  static int count=0;
  for(int i=0;i<4;i++){
    digitalWrite(Led[i],HIGH);
    delay(500+count*500);
    digitalWrite(Led[i],LOW);
    delay(500+count*500);
  }
  count++;
  if(count>4){
    count=0;
  }
}

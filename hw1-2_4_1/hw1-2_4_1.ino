#define LED16 9
int Led[4]={5,6,7,8};

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<4;i++)
    pinMode(Led[i],OUTPUT);
  pinMode(LED16,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  static byte output= HIGH;
  for(int i=0;i<4;i++){
    digitalWrite(Led[i],HIGH);
    delay(500);
    digitalWrite(Led[i],LOW);
    delay(500);
    digitalWrite(LED16,output);
    output=!output;
  }
  
}

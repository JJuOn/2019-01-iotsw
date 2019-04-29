#define LED 5
#define BUZZER 6
enum { REST=0, DO=262, RE=294, MI=330, FA=349, SOL=392, LA=440, SHI=494, DO2=523 };
int Num = 9;
int Frequency[] = { DO, RE, MI, REST, FA, SOL, LA, SHI, DO2 };
int Delay[] = { 500, 0, 500, 500, 500, 500, 1000, 0, 500 };

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  pinMode(BUZZER,OUTPUT);
}

void loop() {
  digitalWrite(LED,HIGH);
  tone(BUZZER, Frequency[0]);
  delay(500);
  digitalWrite(LED,LOW);
  tone(BUZZER, Frequency[1]);
  delay(0);
  tone(BUZZER, Frequency[2]);
  delay(500);
  tone(BUZZER, Frequency[3]);
  digitalWrite(LED,HIGH);
  delay(500);
  tone(BUZZER, Frequency[4]);
  digitalWrite(LED,LOW);
  delay(500);
  digitalWrite(LED,HIGH);
  tone(BUZZER, Frequency[5]);
  delay(500);
  digitalWrite(LED,LOW);
  tone(BUZZER, Frequency[6]);
  delay(500);
  digitalWrite(LED,HIGH);
  delay(500);
  tone(BUZZER, Frequency[7]);
  delay(0);
  digitalWrite(LED,LOW);
  tone(BUZZER, Frequency[8]);
  delay(500);
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  noTone(BUZZER);
  delay(500);
}

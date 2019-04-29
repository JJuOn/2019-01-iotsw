void setup() {
  // put your setup code here, to run once:
  DDRB = 0x80;
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTB=0x80;
  delay(1000);
  PORTB=0x00;
  delay(1000);
}

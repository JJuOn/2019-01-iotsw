void setup() {
  // put your setup code here, to run once:
  DDRE=0x08;
  DDRH=0x38;//00111000
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTE=0x08;
  delay(500);
  PORTE=0x00;
  delay(500);
  PORTH=0x08;
  delay(500);
  PORTH=0x00;
  delay(500);
  PORTH=0x10;
  delay(500);
  PORTH=0x00;
  delay(500);
  PORTH=0x20;
  delay(500);
  PORTH=0x00;
  delay(500);
}

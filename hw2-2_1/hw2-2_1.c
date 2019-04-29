#include <stdio.h>
#include <wiringPi.h>
#define LED_ON 1
#define LED_OFF 0

const int Led[16]={4,17,18,27,22,23,24,25,6,12,13,16,19,20,26,21};
const int LedOdd[8]={4,18,22,24,6,13,19,26};
const int LedEven[8]={17,27,23,25,12,16,20,21};

int main()
{
	int i;
	if(wiringPiSetupGpio()==-1)
		return 1;
	for(i=0;i<16;i++)
	{
		pinMode(Led[i],OUTPUT);
		digitalWrite(Led[i],LED_OFF);
	}
	while(1)
	{
		for(i=0;i<8;i++){
			digitalWrite(LedOdd[i],LED_ON);
			delay(500);
			digitalWrite(LedOdd[i],LED_OFF);
			delay(500);
		}
		for(i=0;i<8;i++){
                        digitalWrite(LedEven[i],LED_ON);
                        delay(500);
                        digitalWrite(LedEven[i],LED_OFF);
                        delay(500);
                }

	}
	return 0;
}

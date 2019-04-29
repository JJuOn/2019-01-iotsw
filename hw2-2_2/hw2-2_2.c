#include <stdio.h>
#include <wiringPi.h>
#define LED_ON 1
#define LED_OFF 0

const int Led[16]={4,17,18,27,22,23,24,25,6,12,13,16,19,20,26,21};

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
		for(i=0;i<15;i+=2)
		{
			digitalWrite(Led[i],LED_ON);
			digitalWrite(Led[i+1],LED_ON);
			delay(250);
			digitalWrite(Led[i],LED_OFF);
                        digitalWrite(Led[i+1],LED_OFF);
                        delay(250);

		}
	}
	return 0;
}

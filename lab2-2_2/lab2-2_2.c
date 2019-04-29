#include <stdio.h>
#include <wiringPi.h>
#define LED_ON 1
#define LED_OFF 0
#define LED_GREEN 2
#define LED_RED 3

const int LedRed[8]={4,17,18,27,22,23,24,25};
const int LedGreen[8]={6,12,13,16,19,20,26,21};

void LEDControl(int color)
{
	int i;
	if(color==LED_RED)
	{
		for(i=0;i<8;i++)
		{
			digitalWrite(LedRed[i],LED_ON);
			digitalWrite(LedGreen[i],LED_OFF);
		}
	}
	else if(color==LED_GREEN)
	{
                for(i=0;i<8;i++)
                {
                        digitalWrite(LedRed[i],LED_OFF);
                        digitalWrite(LedGreen[i],LED_ON);
                }
        }
}


int main()
{
	int i;
	if(wiringPiSetupGpio()==-1)
		return 1;
	for(i=0;i<8;i++)
	{
		pinMode(LedRed[i],OUTPUT);
		pinMode(LedGreen[i],OUTPUT);
		digitalWrite(LedRed[i],LED_OFF);
		digitalWrite(LedGreen[i],LED_OFF);

	}
	while(1)
	{
		LEDControl(LED_RED);
		delay(500);
		LEDControl(LED_GREEN);
		delay(500);
	}
	return 0;
}

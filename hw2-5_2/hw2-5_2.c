#include <wiringPi.h>
#include <softPwm.h>

const int led[8]={4,17,18,27,22,23,24,25};

int main(){

	if(wiringPiSetupGpio()==-1){
		return 1;
	}
	int i;
	for(i=0;i<8;i++){
		pinMode(led[i],OUTPUT);
		softPwmWrite(led[i],0);
	}
	softPwmCreate(4,0,128);
	
	while(1){
		int i;
		for(i=1;i<=128;i++){
			softPwmWrite(4,i);
			delay(100);
		}
		for(i=128;i>0;i--){
			softPwmWrite(4,i);
			delay(100);
		}
	}
	return 0;
}

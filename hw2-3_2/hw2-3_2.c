#include <wiringPi.h>
const int LedRed[8]={4,17,18,27,22,23,24,25};
const int Keypad[3]={6,12,13};
int status=2;

int KeypadRead(){
	int i,keypadnum=-1;
	for(i=0;i<3;i++){
		if(!digitalRead(Keypad[i])){
			status=i;
			break;
		}
	}
	return status;
}

void LedControl(int keypadnum){
	int i;
	for(i=0;i<8;i++){
		if(i==keypadnum)
			digitalWrite(LedRed[i],HIGH);
		else
			digitalWrite(LedRed[i],LOW);
	}
}

int main(){
	int i;
	int keypadnum=-1;
	if(wiringPiSetupGpio()==-1)
		return 1;

	for(i=0;i<8;i++){
		pinMode(LedRed[i],OUTPUT);
		digitalWrite(LedRed[i],LOW);
	}
	for(i=0;i<3;i++)
		pinMode(Keypad[i],INPUT);
	while(1){
		keypadnum=KeypadRead();
		if(status==0){
			for(i=0;i<8;i++){
				LedControl(i);
				delay(500);
			}
			digitalWrite(LedRed[i-1],LOW);
		}if(status==1){
			for(i=7;i>=0;i--){
				LedControl(i);
				delay(500);
			}
			digitalWrite(LedRed[i+1],LOW);
		}if(status==2){
			for(i=0;i<8;i++){
				digitalWrite(LedRed[i],LOW);
			}
		}
	}
	return 0;
}

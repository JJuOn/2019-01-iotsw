#include <wiringPi.h>
#include <softPwm.h>

#define MOTOR_MT_N_PIN 17
#define MOTOR_MT_P_PIN 4

#define LEFT_ROTATE 1
#define RIGHT_ROTATE 2

void MotorStop(){
	softPwmWrite(MOTOR_MT_N_PIN,0);
	softPwmWrite(MOTOR_MT_P_PIN,0);
}

void MotorControl(int rotate){
	if(rotate==LEFT_ROTATE){
		digitalWrite(MOTOR_MT_P_PIN,LOW);
		softPwmWrite(MOTOR_MT_N_PIN,50);
	}
	else if(rotate==RIGHT_ROTATE){
		digitalWrite(MOTOR_MT_N_PIN,LOW);
		softPwmWrite(MOTOR_MT_P_PIN,50);
	}
}
int main(){
	if(wiringPiSetupGpio()==-1){
		return 1;
	}
	pinMode(MOTOR_MT_N_PIN,OUTPUT);
	pinMode(MOTOR_MT_P_PIN,OUTPUT);
	softPwmCreate(MOTOR_MT_N_PIN,0,100);
	softPwmCreate(MOTOR_MT_P_PIN,0,100);
	while(1){
		MotorControl(LEFT_ROTATE);
		delay(2000);
		MotorStop();
		delay(1000);
		MotorControl(RIGHT_ROTATE);
		delay(2000);
		MotorStop();
		delay(1000);
	}
	return 0;
}

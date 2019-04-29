#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
const int FndSelectPin[6]={4,17,18,27,22,23};
const int FndPin[8]={6,12,13,16,19,20,26,21};
const int FndFont[10]={0x3F, 0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0X7F,0x67};

void Init(){
	int i;
	if(wiringPiSetupGpio()==-1){
		printf("wiringPiSetpuGpio() error\n");
		exit(-1);
	}
	for(i=0;i<6;i++){
		pinMode(FndSelectPin[i],OUTPUT);
		digitalWrite(FndSelectPin[i],HIGH);
	}
	for(i=0;i<8;i++){
		pinMode(FndPin[i],OUTPUT);
		digitalWrite(FndPin[i],LOW);
	}
}
void FndSelect(int position){
	int i;
	for(i=0;i<6;i++){
		if(i==position){
			digitalWrite(FndSelectPin[i],LOW);
		}
		else{
			digitalWrite(FndSelectPin[i],HIGH);
		}
	}
}
void FndDisplay(int position, int num){
	int i;
	int flag=0;
	int shift=0x01;
	FndSelect(position);
	for(i=0;i<8;i++){
		flag=(FndFont[num]&shift);
		digitalWrite(FndPin[i],flag);
		shift<<=1;
	}
}

int main(){
	int pos;
	int data[6]={0,1,2,3,4,5};
	Init();
	while(1){
		for(pos=0;pos<6;pos++){
			FndDisplay(pos,data[pos]);
			delay(1);
		}
	}
	return 0;
}

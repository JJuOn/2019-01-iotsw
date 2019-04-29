#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
const int FndSelectPin[6]={4,17,18,27,22,23};
const int FndPin[8]={6,12,13,16,19,20,26,21};
const int FndFont[10]={0x3F, 0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0X7F,0x67};
const int dot=0x80;
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
	int i,font;
	int flag=0;
	int shift=0x01;
	FndSelect(position);
	for(i=0;i<8;i++){
		font=FndFont[num];
		if(position==2){
			font |=dot;
		}
		flag=(font&shift);
		digitalWrite(FndPin[i],flag);
		shift<<=1;
	}
}

void dataCheck(int data[]){
	int i;
	for(i=0;i<5;i++){
		if(data[i]>=10){
			data[i]=0;
			data[i+1]++;
		}
	}
	if(data[5]>=10){
		data[5]=0;
	}
}

int main(){
	int pos,i,cnt;
	int data[6]={0,0,0,0,0,0};
	Init();
	for(i=0;i<6;i++){
		FndDisplay(i,0);
	}

	while(1){
		for(pos=0;pos<6;pos++){
			FndDisplay(pos,data[pos]);
			delay(1);
			cnt++;
		}
		if(cnt>=10){
			data[0]++;
			cnt=0;
		}
		dataCheck(data);
	}
	return 0;
}

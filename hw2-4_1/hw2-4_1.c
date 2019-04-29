#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
const int FndSelectPin[6]={4,17,18,27,22,23};
const int FndPin[8]={6,12,13,16,19,20,26,21};
const int FndFont[10]={0x3F, 0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0X7F,0x67};
const int FndHello[6]={0x00,0x76,0x79,0x38,0x38,0x3F};
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
                else
                	digitalWrite(FndSelectPin[i],HIGH);
        }
}
                                                                               
void FndDisplay(int position, int num){
	int i;
	int flag=0;
	int shift=0x01;
	for(i=0;i<8;i++){
		flag=(FndHello[num]&shift);
		digitalWrite(FndPin[i],flag);
		shift<<=1;
	}
	FndSelect(position);
}

int main(){
	int i,j=0,temp;
	Init();
	int data[6]={5,4,3,2,1,0};
	while(1){
		for(i=0;i<6;i++){
			FndDisplay(i,data[i]);
			delay(1);
			j++;
		}
		if(j>=500){
			for(i=0;i<6;i++){
			temp=data[i];
			data[i]=data[0];
			data[0]=temp;
			}
			j=0;
		}
	}
	return 0;
}

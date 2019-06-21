#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#define MAX_FIFO_NAME 32
#define SERV_FIFO "./.fifo"

const int FndSelect[6]={4,17,18,27,22,23};
const int FndPin[8]={6,12,13,16,19,20,26,21};
const int FndFont[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};

int status;

void Setup(){
	int i;
	if(wiringPiSetupGpio()==-1){
		exit(-1);
	}
	for(i=0;i<6;i++){
		pinMode(FndSelect[i],OUTPUT);
		digitalWrite(FndSelect[i],HIGH);
	}
	for(i=0;i<8;i++){
		pinMode(FndPin[i],OUTPUT);
		digitalWrite(FndPin[i],LOW);
	}

}
void Select(int position){
	int i;
	for(i=0;i<6;i++){
		if(i==position){
			digitalWrite(FndSelect[i],LOW);	
		}
		else{
			digitalWrite(FndSelect[i],HIGH);
		}
	}	
}
void FndDisplay(int position, int num){
	int i;
	int flag=0;
	int shift=0x01;
	for(i=0;i<8;i++){
		int font=FndFont[num];
		if(position==2){
			flag|=0x80;
		}
		flag=(font  & shift);
		digitalWrite(FndPin[i],flag);
		shift<<=1;
	}
	Select(position);
}

void* DoStopWatch(void* dummy){
	int data[6]={0,0,0,0,0,0};
	while(1){
		if(status==0){
			int i;
			data[5]++;
			for(i=5;i>=0;i--){
				if (data[i]==10){
					data[i-1]++;
					data[i]=0;
				}
			}
			if (data[0]==10){
				data[0]=0;
			}
			sleep(0.01);			
		}
		else if(status==1){
			continue;
		}
		else{
			int i;
			for(i=5;i>=0;i--){
				data[i]=0;
			}	
		}
		int j;
		for(j=0;j<6;j++){
			FndDisplay(j,data[j]);
		}
	}
}

void* DoIPC(void* dummy){
	while(1){
		char buf[1024];
		int fd;
		if((fd=open(SERV_FIFO, O_RDWR))<0){
			perror("open\n");
			exit(1);	
		}
		int n;
		if((n=read(fd,(char*)buf, 1024))<0){
			perror("read\n");
			exit(1);
		}
		status=atoi(&buf[0]);
		char* subbuff;
		memcpy(subbuff,&buf[1],n);
		subbuff[n-1]='\0';
		write(fd,subbuff,n);
		close(fd);
	}
}
void StartStopWatch(){
        mkfifo(SERV_FIFO,0666);
        pthread_t p_thread[2];
        pthread_create(&p_thread[0],NULL,DoStopWatch,NULL);
        pthread_create(&p_thread[1],NULL,DoIPC,NULL);
        pthread_join(p_thread[0],NULL);
	pthread_join(p_thread[1],NULL);
}

int main(){
	printf("Content-type:text/html\n");
	printf("\n");
	printf("<html>\n");
	printf("<head>\n");
	printf("<title>START</title>\n");
	printf("</head>\n");
	printf("<body>\n");
	printf("<p>Start StopWatch</p>\n");
	Setup();
	int pid;
	if((pid=fork())==0){
		StartStopWatch();
		exit(0);	
	}
	printf("</body>\n");
	printf("</html>\n");
	return 0;	
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#define MAX_FIFO_NAME 32
#define SERV_FIFO "./.fifo"

int main(){
	char buff[2];
	printf("Content-type:text/html\n\n");
	printf("<html>\n");
	printf("<head>\n");
	printf("<title>START</title>\n");
	printf("</head>\n");
	printf("<body>\n");
	printf("<p>Stop StopWatch</p>\n");
	int fd;
	if((fd=open(SERV_FIFO,O_RDWR))<0){
		perror("open");
		exit(1);
	}
	buff[0]='1';
	buff[1]='\0';
	write(fd,buff,strlen(buff));
	close(fd);
	printf("</body>\n");
	printf("</html>\n");
	return 0;
}

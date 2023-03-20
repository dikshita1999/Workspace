#include <stdio.h>
#include <string.h>
#include <fcntl.h> 
#include <errno.h> 
#include <termios.h> 
#include <unistd.h> 

int main() {
       	
  char data[20];
  int fd;
  fd = open("/dev/ttyUSB2", O_RDWR );
	if(fd == -1)
	{
		printf("unable to create file");
	}
	else
	{
		printf("file created successfully");
	}



  struct termios tr;

  tcgetattr(fd,&tr);

  tr.c_iflag &= ~(IXON | IXOFF | IXANY);
  tr.c_oflag &= ~OPOST;
  tr.c_lflag &= ~(ICANON |ECHO | ECHOE | ECHONL  | ISIG ); 
  tr.c_cflag &= ~(CSIZE | PARENB);
  tr.c_cflag &= ~CRTSCTS;
  tr.c_cflag |= CS8;
  tr.c_cflag |= (CREAD | CLOCAL);
  tr.c_cflag |= B9600;
  tr.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); 
  tr.c_cc[VMIN] = 0;
  tr.c_cc[VTIME] = 0;
  tr.c_cflag &= ~CSTOPB;
  tcsetattr(fd,TCSANOW, &tr);
  
  while(1){

    printf("\n Waiting for message...\n");
    sleep(3);
    read(fd,data,sizeof(data));
    if(data > 0)
    {

            for(int i=0;i<20;i++)
	        {
                 printf("%c",data[i]);
            }
     
    }
    else
    {
      printf("Data not read");
    }

    memset(data,0,sizeof(data));
    
    sleep(1);
 
   
  }
  
  close(fd);
  return 0; 
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
 
#define RD_VALUE _IOR('a','b',int32_t*)
 
int main()
{
        int fd;
        int32_t data, number;
        printf("This is Read Functionality\n");
 
        printf("\nOpening the Driver\n");
        fd = open("/dev/etx_device", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file\n");
                return 0;
        }
 
        printf("Reading the data from Driver\n");
        ioctl(fd, RD_VALUE, (int32_t*) &data);
        printf("Value is %d\n", data);
 
        printf("Closing Driver\n");
        close(fd);
}

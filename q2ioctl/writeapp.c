#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
 
#define WR_VALUE _IOW('a','a',int32_t*)
 
int main()
{
        int fd;
        int32_t data, number;
        printf("This is Write functionality\n");
        printf("\nOpening the Driver\n");
        fd = open("/dev/etx_device", O_RDWR);
        if(fd < 0) {
                printf("Cannot open the device file\n");
                return 0;
        }
 
        printf("Enter the data to send\n");
        scanf("%d",&number);
        printf("Writing the data to Driver\n");
        ioctl(fd, WR_VALUE, (int32_t*) &number); 
 
        printf("Closing Driver\n");
        close(fd);
}

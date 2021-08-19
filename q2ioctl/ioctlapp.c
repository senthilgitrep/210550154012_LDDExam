#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>

#define MY_IOCTL_IN _IOC(_IOC_WRITE, 'k', 1, sizeof(my_ioctl_data))

static long my_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
    struct my_device_data *my_data = (struct my_device_data*) file->private_data;
    my_ioctl_data mid;

    switch(cmd) {
    case MY_IOCTL_IN:
        if( copy_from_user(&mid, (my_ioctl_data *) arg, sizeof(my_ioctl_data)) )
            return -EFAULT;

        break;
    	default:
        return -ENOTTY;
    }

    return 0;
}

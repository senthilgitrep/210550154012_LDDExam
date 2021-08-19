// *** Program for character device with open, read, write, close and ioctl functionality ***//

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>

#define mychardevice

static int mychardev_open(struct inode *inode, struct file *file);
static int mychardev_release(struct inode *inode, struct file *file);
static long mychardev_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t mychardev_read(struct file *file, char __user *buf, size_t count, loff_t *offset);
static ssize_t mychardev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset);

struct file_operations fops = {
	.open       	= mychardev_open,
	.release    	= mychardev_release,
    	.unlocked_ioctl = mychardev_ioctl,
    	.read       	= mychardev_read,
    	.write       	= mychardev_write,
   	.owner		= THIS_MODULE
};

struct cdev *my_cdev 

static int __init mychardev_init(void)
{
    	int result, MAJOR, MINOR;
    	Mydev_t dev;
    	Mydev = MKDEV(255,0);
	MAJOR = MAJOR(dev);
	MINOR = MINOR(dev);
	printk("The major number is %d and the minor number is %d\n", MAJOR, MINOR);
	result = register_chrdev_region(Mydev, 1, "mychardevice");
	if(result<0)
	{
		printk("Not accessible\n");
		return(-1);
    }
	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;
	result = cdev_add(cdev, Mydev, 1);
	return(-1);
    }
    return 0;
}

static void __exit mychardev_exit(void)
{
	dev_t Mydev;
	int MAJOR, MINOR;
	Mydev=MKDEV(255,0);
	MAJOR = MAJOR(dev);
	MINOR = MINOR(dev);
	printk("The major number is %d and the minor number is %d\n", MAJOR, MINOR);
	unregister_chrdev_region(Mydev, 1);
	cdev_del(my_cdev);
	printk("Unregistered the char device, Goodbye");
	return;
}

static int mychardev_open(struct inode *inode, struct file *file)
{
    	printk("MYCHARDEV: Device open\n");
    	return 0;
}

static int mychardev_release(struct inode *inode, struct file *file)
{
    	printk("MYCHARDEV: Device close\n");
    	return 0;
}

static long mychardev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    	printk("MYCHARDEV: Device ioctl\n");
    	return 0;
}

static ssize_t mychardev_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    	uint8_t *data = "It is kernel\n";
    	size_t datalen = strlen(data);
    	printk("Read mode: %d\n", MINOR(file->f_path.dentry->d_inode->i_rdev));
    	if (count > datalen) {
        count = datalen;
    }
    	if (copy_to_user(buf, data, count)) {
        return -EFAULT;
    }
    return count;
}

static ssize_t mychardev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    size_t maxdatalen = 30, ncopied;
    uint8_t databuf[maxdatalen];
    printk("Write mode: %d\n", MINOR(file->f_path.dentry->d_inode->i_rdev));
    if (count < maxdatalen) {
        maxdatalen = count;
    }

    ncopied = copy_from_user(databuf, buf, maxdatalen);
    if (ncopied == 0) {
        printk("Copied %zd bytes from the user\n", maxdatalen);
    } else {
        printk("Could not copy %zd bytes from the user\n", ncopied);
    }

    databuf[maxdatalen] = 0;
    printk("User data is: %s\n", databuf);
    return count;
}

module_init(mychardev_init);
module_exit(mychardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SENTHILMURUGAN");
MODULE_DESCRIPTION("Program for Character device with Open, Read, Write, Close and ioctl functionality");

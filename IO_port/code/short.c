/*************************************************************************
	> File Name: short.c
	> Author: 
	> Mail: 
	> Created Time: 2017年04月19日 星期三 01时07分49秒
 ************************************************************************/

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/sched.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/delay.h>	/* udelay */
#include <linux/kdev_t.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/poll.h>
#include <linux/wait.h>

#include <asm/io.h>

#define SHORT_NR_PORTS	8	/* use 8 ports by default */
/*
 * all of the parameters have no "short_" prefix, to save typing when
 * specifying them at load time
 */
int major = 0;	/* dynamic by default */


static unsigned long base = 0x378;
unsigned long short_base = 0;






MODULE_LICENSE("Dual BSD/GPL");



int short_open (struct inode *inode, struct file *filp)
{
	
	return 0;
}


int short_release (struct inode *inode, struct file *filp)
{
	return 0;
}


/* first, the port-oriented device */

enum short_modes {SHORT_DEFAULT=0, SHORT_PAUSE, SHORT_STRING, SHORT_MEMORY};

ssize_t do_short_read (struct inode *inode, struct file *filp, char __user *buf,
		size_t count, loff_t *f_pos)
{
	int retval = count, minor = iminor (inode);
	unsigned long port = short_base + (minor&0x0f);
	void *address = (void *) short_base + (minor&0x0f);
	int mode = (minor&0x70) >> 4;
	unsigned char *kbuf = kmalloc(count, GFP_KERNEL), *ptr;
    
	if (!kbuf)
		return -ENOMEM;
	ptr = kbuf;
	
	
	while(count--){
	    *(ptr++) = inb(port);
	    rmb();
    }
	
	
	if ((retval > 0) && copy_to_user(buf, kbuf, retval))
		retval = -EFAULT;
   	//printk("\nread kbuf %s\n",kbuf);
   	//printk("\nread buf %s\n",buf);
	kfree(kbuf);
	return retval;
}


/*
 * Version-specific methods for the fops structure.  FIXME don't need anymore.
 */
ssize_t short_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	return do_short_read(filp->f_path.dentry->d_inode, filp, buf, count, f_pos);
}



ssize_t do_short_write (struct inode *inode, struct file *filp, const char __user *buf,
		size_t count, loff_t *f_pos)
{
	int retval = count, minor = iminor(inode);
	unsigned long port = short_base + (minor&0x0f);
	void *address = (void *) short_base + (minor&0x0f);
	int mode = (minor&0x70) >> 4;
	unsigned char *kbuf = kmalloc(count, GFP_KERNEL), *ptr;
	char temp;
	if (!kbuf)
		return -ENOMEM;
	if (copy_from_user(kbuf, buf, count))
		return -EFAULT;
	ptr = kbuf;


	printk("write : %c\n",*ptr);
	outb(*(ptr), 0x70);
	
	
		
	
	temp = inb(0x71);
	printk("read : %c\n",temp);
	
	kfree(kbuf);
	return retval;
}


ssize_t short_write(struct file *filp, const char __user *buf, size_t count,
		loff_t *f_pos)
{
	return do_short_write(filp->f_path.dentry->d_inode, filp, buf, count, f_pos);
}




unsigned int short_poll(struct file *filp, poll_table *wait)
{
	return POLLIN | POLLRDNORM | POLLOUT | POLLWRNORM;
}






struct file_operations short_fops = {
	.owner	 = THIS_MODULE,
	.read	 = short_read,
	.write	 = short_write,
	.poll	 = short_poll,
	.open	 = short_open,
	.release = short_release,
};


int short_init(void)
{
	int result;

	short_base = base;
	


	request_region(base, SHORT_NR_PORTS, "short");
	
	result = register_chrdev(major, "short", &short_fops);
	if (result < 0) {
		printk(KERN_INFO "short: can't get major number\n");
		return result;
	}
    major = result;	
	
    printk("the major :%d\n",result);
	


	return 0;
}

void short_cleanup(void)
{

    	printk("i want remove %d short\n",major);
	unregister_chrdev(major, "short");

	release_region(base,SHORT_NR_PORTS);
    	printk("short :%0xd\n",short_base);

	
}



module_init(short_init);
module_exit(short_cleanup);


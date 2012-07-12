#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/cdev.h>
#include<linux/delay.h>
#include<linux/device.h>
#include<linux/jiffies.h>
#include<linux/uaccess.h>
#include<linux/vmalloc.h>
#include<linux/mutex.h>
#include<linux/workqueue.h>
#include<linux/mm.h>
#include"lcd.h"
#include"s1d13700_fb.h"

#define S1D13700_NAME "s1d13700d"


static unsigned int s1d13700_rate = 14;
static unsigned char* s1d13700_cache;
extern unsigned char* s1d13700_buffer;
extern unsigned char  s1d13700fb_inited;
static DEFINE_MUTEX(s1d13700_mutex);
static unsigned char s1d13700_updating;
static void s1d13700_update(struct work_struct* delayed_work);
static struct workqueue_struct* s1d13700_workqueue;
static DECLARE_DELAYED_WORK(s1d13700_work, s1d13700_update);


static void s1d13700_queue(void){
    queue_delayed_work(s1d13700_workqueue, &s1d13700_work, HZ);//s1d13700_rate);
}

static void s1d13700_update(struct work_struct* work)
{
    if(memcmp(s1d13700_cache, s1d13700_buffer, S1D13700_BUFFER_SIZE)) {
        printk(KERN_ALERT "Updating Screen \n");
        s1d13700_set_cursor_addr(S1D13700_GRAPHICSTART); //set curosr to begining of screen
        
        memcpy(s1d13700_cache, s1d13700_buffer, S1D13700_BUFFER_SIZE);
        s1d13700_write_buffer(s1d13700_cache, S1D13700_BUFFER_SIZE);
    }
    if(s1d13700_updating)
        s1d13700_queue();
}

static char s1d13700_enable(void)
{
    char ret;

    mutex_lock(&s1d13700_mutex);

    if(!s1d13700_updating){
        s1d13700_updating = 1;
        s1d13700_queue();
        ret = 0;
    }else{
        ret = 1;
    }

    mutex_unlock(&s1d13700_mutex);
    return ret;
}


static int __init s1d13700_driver_init(void)
{
    int ret = -EINVAL;
    if(!s1d13700fb_inited){
        printk(KERN_ALERT "S1D13700FB Not initialized. \n");
        goto none;
    }
    printk(KERN_ALERT "Buffer address = %p \n", s1d13700_buffer);
    //BUILD_BUG_ON(PAGE_SIZE < S1D13700_BUFFER_SIZE);

    if(s1d13700_buffer == NULL){
        printk(KERN_ERR "invalid buffer \n");
        goto none;
    }

    s1d13700_cache = vmalloc_32(PAGE_ALIGN(S1D13700_BUFFER_SIZE));
    if(s1d13700_cache == NULL){
        printk(KERN_ERR "Can't allocate cache buffer (%i buffer) \n", S1D13700_BUFFER_SIZE);
        ret = -ENOMEM;
        goto none;
    }

    s1d13700_workqueue = create_singlethread_workqueue(S1D13700_NAME);
    if(s1d13700_workqueue == NULL){
        goto cache_alloc;
    }
    
    s1d13700_init();
    s1d13700_clear();
    
    s1d13700_enable();

    return 0;

cache_alloc:
    kfree(s1d13700_cache);

none:
    return ret;
}

static void __exit s1d13700_driver_exit(void){
    //s1d13700_disable();
    destroy_workqueue(s1d13700_workqueue);
    kfree(s1d13700_cache);
}

module_init(s1d13700_driver_init);
module_exit(s1d13700_driver_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Yannick Roberts");


#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/delay.h>
#include<linux/errno.h>
#include<linux/fb.h>
#include<linux/mm.h>
#include<linux/platform_device.h>
#include<linux/string.h>
#include<linux/uaccess.h>
#include<linux/vmalloc.h>
#include"s1d13700_fb.h"

#define DEBUG

#define S1D13700FB_NAME "s1d13700fb"

unsigned char * s1d13700_buffer;
unsigned char s1d13700fb_inited;

static struct fb_fix_screeninfo s1d13700fb_fix __devinitdata = {
    .id = "s1d13700",
    .type = FB_TYPE_PACKED_PIXELS,
    .visual = FB_VISUAL_MONO10,
    .xpanstep = 0,
    .ypanstep = 0,
    .ywrapstep = 0,
    .line_length = S1D13700_WIDTH / 8,
    .accel = FB_ACCEL_NONE,
};

static struct fb_var_screeninfo s1d13700fb_var __devinitdata = {
    .xres = S1D13700_WIDTH,
    .yres = S1D13700_HEIGHT,
    .xres_virtual = S1D13700_WIDTH,
    .yres_virtual = S1D13700_HEIGHT,
    .bits_per_pixel = S1D13700_BPP,
    .red = { 0, 1, 0 },
    .blue = { 0, 1, 0 },
    .green = { 0, 1, 0},
    .left_margin = 0,
    .right_margin = 0,
    .lower_margin = 0,
    .vmode = FB_VMODE_NONINTERLACED,
};
/*

static int s1d13700fb_mmap_(struct fb_info* info, struct vm_area_struct* vma)
{
    return vm_insert_page(vma, vma->vm_start, virt_to_page(cfag12864b_buffer));

}
*/

static int s1d13700fb_mmap(struct fb_info *info,
                     struct vm_area_struct *vma)
 {
    printk(KERN_ALERT "Remapping framebuffer: \n");
     unsigned long start = vma->vm_start;
     unsigned long size = vma->vm_end - vma->vm_start;
     unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
     unsigned long page, pos;

     if (offset + size > info->fix.smem_len) {
         printk(KERN_ALERT "Offset failed \n Offset size = %i \t buffer size=%i",
                 offset+size, info->fix.smem_len);
         return -EINVAL;
     }

     pos = (unsigned long)info->screen_base + offset;

     while (size > 0) {
         page = vmalloc_to_pfn((void *)pos);
         if (remap_pfn_range(vma, start, page, PAGE_SIZE, PAGE_SHARED)) {
             printk(KERN_ALERT "ERROR:Failed to remap pfn \n");
             return -EAGAIN;
         }
         start += PAGE_SIZE;
         pos += PAGE_SIZE;
         if (size > PAGE_SIZE)
             size -= PAGE_SIZE;
         else
             size = 0;
     }

     vma->vm_flags |= VM_RESERVED;   /* avoid to swap out this VMA */
     return 0;

 }


static struct fb_ops s1d13700fb_ops = {
    .owner = THIS_MODULE,
    .fb_read = fb_sys_read,
    .fb_write = fb_sys_write,
    .fb_fillrect  = sys_fillrect,
    .fb_copyarea = sys_copyarea,
    .fb_imageblit = sys_imageblit,
    .fb_mmap = s1d13700fb_mmap
};

static void* s1d13700fb_alloc_videomemory(void)
{
    void* mem;
    unsigned long adr;
    int size;

    printk(KERN_ALERT "Buffer Size = %i \n", S1D13700_BUFFER_SIZE);
    size = PAGE_ALIGN(S1D13700_BUFFER_SIZE);
    printk(KERN_ALERT "Page aligned buffer size = %i \n", size);
    mem = vmalloc_32(size);
    printk(KERN_ALERT "Buffer allocated at %p \n", mem);

    if(!mem){
        printk(KERN_ALERT "Failed to allocate memory: %p \n", mem);
        return NULL;
    }
    memset(mem, 0xff, size);/* Clear the ram out, no junk to the user */
    adr = (unsigned long) mem;
    while (size > 0) {
        SetPageReserved(vmalloc_to_page((void *)adr));
        adr += PAGE_SIZE;
        size -= PAGE_SIZE;
    }

    return mem;
}


static void s1d13700fb_free_videomemory(void *mem, unsigned long size)
{
    unsigned long adr;

    if (!mem)
      return;

    adr = (unsigned long) mem;
    while ((long) size > 0) {
        ClearPageReserved(vmalloc_to_page((void *)adr));
        adr += PAGE_SIZE;
        size -= PAGE_SIZE;
    }
    vfree(mem);
}


static int __devinit s1d13700fb_probe(struct platform_device* device)
{
    int ret = -EINVAL;
    printk(KERN_ALERT "Allocating fb_info \n");
    struct fb_info* info = framebuffer_alloc(0, &device->dev);
    if(!info)
        goto none;

    printk(KERN_ALERT "Allocating video memory \n");
    s1d13700_buffer = (char *) s1d13700fb_alloc_videomemory();
    if(s1d13700_buffer == NULL)
        goto vballoced;
    info->screen_base = (char __iomem *)s1d13700_buffer;
    info->fbops = &s1d13700fb_ops;
    s1d13700fb_fix.smem_start = s1d13700_buffer;
    s1d13700fb_fix.smem_len = PAGE_ALIGN(S1D13700_BUFFER_SIZE);
    info->fix = s1d13700fb_fix;
    info->var = s1d13700fb_var;
    info->pseudo_palette = NULL;
    info->par = NULL;
    info->flags = FBINFO_FLAG_DEFAULT;

    if(register_framebuffer(info) < 0){
        printk(KERN_ALERT "Failed to register framebuffer info \n");
        goto vballoced;
    }

    platform_set_drvdata(device, info);
    return 0;
vballoced:
    s1d13700fb_free_videomemory(info->screen_base, S1D13700_BUFFER_SIZE);
fballoced:
printk(KERN_ALERT "Probe failed \n");
    framebuffer_release(info);
none:
    return ret;
}

static int __devexit s1d13700fb_remove(struct platform_device* device)
{
    struct fb_info* info = platform_get_drvdata(device);

    if(info){
        unregister_framebuffer(info);
        framebuffer_release(info);
    }
    return 0;
}

static struct platform_driver s1d13700fb_driver ={
    .probe = s1d13700fb_probe,
    .remove = s1d13700fb_remove,
    .driver = {
        .name = S1D13700FB_NAME,
    },
};

static struct platform_device* s1d13700fb_device;

static int __init s1d13700fb_init(void)
{
    int ret = -EINVAL;
    s1d13700fb_inited = 0;
    printk(KERN_ALERT "Registering Platform Driver at address %p \n", &s1d13700fb_driver);

    ret = platform_driver_register(&s1d13700fb_driver);

    if(!ret){
        printk(KERN_ALERT "Allocating Platform Device \n");
        s1d13700fb_device = platform_device_alloc(S1D13700FB_NAME, 0);
        if(s1d13700fb_device)
        {
            printk(KERN_ALERT "Registering platform device \n");
            ret = platform_device_add(s1d13700fb_device);
            s1d13700fb_inited = 1;
            goto none;
        }
        else
        {
            printk(KERN_ALERT "Failed to allocate platform device memory \n");
            platform_driver_unregister(&s1d13700fb_driver);
            ret = -EINVAL;
        }

        if(ret){
            platform_device_put(s1d13700fb_device);
            platform_driver_unregister(&s1d13700fb_driver);
            goto failed;
        }
    }
    else
        goto failed;
    none:
    printk(KERN_ALERT "Initialization Successfully \n");
    return ret;
failed:
    printk(KERN_ALERT "Initializing platform device failed. \n");
    return ret;
}

static void __exit s1d13700fb_exit(void)
{
    platform_device_unregister(s1d13700fb_device);
    platform_driver_unregister(&s1d13700fb_driver);

}

EXPORT_SYMBOL_GPL(s1d13700_buffer);
EXPORT_SYMBOL_GPL(s1d13700fb_inited);

module_init(s1d13700fb_init);
module_exit(s1d13700fb_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Yannick Roberts");
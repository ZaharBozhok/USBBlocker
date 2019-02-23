#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");


static int usbblocker_prode(struct usb_interface *usbInterface, const struct usb_device_id *usbDeviceId)
{
    printk(KERN_INFO "usbblocker_prode\n");
    return 0;
}

static void usbblocker_disconnect(struct usb_interface *usbInterface)
{
    printk(KERN_INFO "usbblocker_disconnect\n");
}

static struct usb_device_id usbblocker_id_table[] = {
    {.driver_info = 42, .bDeviceClass = USB_CLASS_MASS_STORAGE},
    {}};

static struct usb_driver usbblocker_driver = {
    .name = "usbblocker",
    .probe = usbblocker_prode,
    .disconnect = usbblocker_disconnect,
    .id_table = usbblocker_id_table
    };

static int __init usbblocker_init(void)
{
    printk(KERN_INFO "usbblocker_init\n");
    int usbblockerRegister = usb_register(&usbblocker_driver);
    if (usbblockerRegister)
    {
        printk(KERN_INFO "Registering usb driver failed, error : %d\n", usbblockerRegister);
    }
    printk(KERN_INFO "usbblocker_loaded\n");
    return usbblockerRegister;
}
static void __exit usbblocker_exit(void)
{
    printk(KERN_INFO "usbblocker_exit\n");
    usb_deregister(&usbblocker_driver);
    printk(KERN_INFO "usbblocker_unloaded\n");
}
module_init(usbblocker_init);
module_exit(usbblocker_exit);

#include <linux/module.h>
#include <linux/usb.h>

static int toy_usb_probe(struct usb_interface *interface, 
					const struct usb_device_id *id)
{
	return 0;

}

static void toy_usb_disconnect(struct usb_interface *interface)
{

}


static const struct usb_device_id id_table[] = {
	{USB_DEVICE(0x6666,0x6666)},
	{}
};

MODULE_DEVICE_TABLE(usb, id_table);

static struct usb_driver toy_usb_driver = {
	.name = "toy_usb",
	.probe = toy_usb_probe,
	.disconnect = toy_usb_disconnect,
//	.suspend = udl_usb_suspend,
//	.resume = udl_usb_resume,
	.id_table = id_table,
};
module_usb_driver(toy_usb_driver);
MODULE_LICENSE("GPL");

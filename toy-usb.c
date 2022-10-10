
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/slab.h>

struct toy_usb_device
{
	struct usb_device*		usb_dev;
	struct usb_interface*	usb_if;

	struct usb_endpoint_descriptor *ep_in;
	struct usb_endpoint_descriptor *ep_out;
	struct usb_endpoint_descriptor *ep_intr;
};

static int toy_usb_probe(struct usb_interface *interface,
					const struct usb_device_id *id)
{
	struct usb_device* usb_dev = usb_get_dev(interface_to_usbdev(interface));
	struct usb_endpoint_descriptor *epd;
	struct usb_host_interface *settings;
	struct toy_usb_device *toy_usb_dev;
	int i;

	if(!(toy_usb_dev = kzalloc(sizeof(struct toy_usb_device),GFP_KERNEL)))
	{
		dev_dbg(&interface->dev,"could not allocate device memor");		
		usb_put_dev(toy_usb_dev->usb_dev);
		return -ENOMEM;
	}

	//save USB device data
	toy_usb_dev->usb_dev = usb_dev;
	toy_usb_dev->usb_if = interface;
	
	//find endpoints
	settings = interface->cur_altsetting;
	dev_dbg(&interface->dev, "bNumEndpoints=%d", settings->desc.bNumEndpoints);

	for(i = 0; i < settings->desc.bNumEndpoints; i++)
	{
       epd = &settings->endpoint[i].desc;                                 
                                                                          
       dev_dbg(&interface->dev, "  endpoint=%d type=%d dir=%d addr=%0x", i,
                usb_endpoint_type(epd), usb_endpoint_dir_in(epd),         
                usb_endpoint_num(epd));                                   
                                                                          
       if (usb_endpoint_is_bulk_in (epd)) toy_usb_dev->ep_in   = epd; else  
       if (usb_endpoint_is_bulk_out(epd)) toy_usb_dev->ep_out  = epd; else  
       if (usb_endpoint_xfer_int   (epd)) toy_usb_dev->ep_intr = epd; 	
	}
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

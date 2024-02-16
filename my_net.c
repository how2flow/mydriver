// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) Steve Jeong <steve@how2flow.net>
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>

#define DRIVER_NAME "my_net"
#define MAC_ADDR_LEN ETH_ALEN

static struct net_device *my_net_device;

static int my_net_open(struct net_device *dev)
{
	printk(KERN_INFO "Network device opened\n");
	netif_start_queue(dev);

	return 0;
}

static int my_net_stop(struct net_device *dev)
{
	printk(KERN_INFO "Network device closed\n");
	netif_stop_queue(dev);

	return 0;
}

static netdev_tx_t my_net_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct sk_buff *new_skb;

	printk(KERN_INFO "Transmit\n");

	new_skb = skb_copy(skb, GFP_ATOMIC);
	if (!new_skb) {
		printk(KERN_ERR "skb_copy failed\n");
		return NETDEV_TX_OK;
	}

	netif_rx(new_skb);

	dev_kfree_skb_any(skb);

	return NETDEV_TX_OK;
}

static struct net_device_ops my_net_device_ops = {
	.ndo_open = my_net_open,
	.ndo_stop = my_net_stop,
	.ndo_start_xmit = my_net_xmit,
};

static int __init my_net_init(void)
{
	my_net_device = alloc_netdev(0, DRIVER_NAME, NET_NAME_UNKNOWN, ether_setup);
	if (!my_net_device) {
		printk(KERN_ERR "Failed to allocate net device\n");
		return -ENOMEM;
	}

	my_net_device->netdev_ops = &my_net_device_ops;
	my_net_device->type = ETH_P_LOOPBACK;
	my_net_device->mtu = 1500;
	my_net_device->flags |= IFF_LOOPBACK;

	if (register_netdev(my_net_device)) {
		printk(KERN_ERR "Failed to register net device\n");
		free_netdev(my_net_device);
		return -ENODEV;
	}

	printk(KERN_INFO "Network device registered\n");

	return 0;
}

static void __exit my_net_exit(void)
{
	unregister_netdev(my_net_device);
	free_netdev(my_net_device);
	printk(KERN_INFO "Network device unregistered\n");
}

module_init(my_net_init);
module_exit(my_net_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Steve Jeong");
MODULE_DESCRIPTION("A simple network device driver example");

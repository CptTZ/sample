#ifndef __KERNEL__
#define __KERNEL__
#endif

#ifndef MODULE
#define MODULE
#endif

#include <linux/netfilter.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/netfilter_ipv4.h>
#include <linux/inet.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/netlink.h>
#include <linux/spinlock.h>
#include <net/sock.h>
#include <net/ip.h>
#include <linux/net.h>
#include "easylink.h"

MODULE_LICENSE("Dual BSD/GPL");
#define IMP2_K_MY "imp2_k_my:"
//#define printk(arg) //printkk(KERN_ALERT IMP2_K_MY arg)

DECLARE_MUTEX(receive_sem);
static struct sock *mysock;
struct
{
    __u32 pid;
    rwlock_t lock;
} user_proc;

static int send_to_user(struct packet_info *info)
{
    int ret = 0;
    int size;
    unsigned char *old_tail;

    struct sk_buff *skb;
    struct nlmsghdr *nlh;
    struct packet_info *packet;

//    printk("%s, begin !!! \n", __func__);

    size = NLMSG_SPACE(sizeof(struct packet_info));
    
    skb = alloc_skb(size, GFP_ATOMIC);
    old_tail = skb->tail;

    nlh = NLMSG_PUT(skb, 0, 0, IMP2_K_MSG, size - sizeof(*nlh));
    packet = NLMSG_DATA(nlh);
    memset(packet, 0, sizeof(struct packet_info));

    packet->src = info->src;
    packet->dest = info->dest;
    packet->len =  info->len;
    packet->eth_hdrr = info->eth_hdrr;

    nlh->nlmsg_len = skb->tail - old_tail;
    NETLINK_CB(skb).dst_group = 0;

    read_lock_bh(&user_proc.lock);
    ret = netlink_unicast(mysock, skb, user_proc.pid, MSG_DONTWAIT);
    read_unlock_bh(&user_proc.lock);
    
//    printk("%s, end !!! \n", __func__);

    return ret;
    
nlmsg_failure: 
    if(skb)
        kfree_skb(skb);
    return -1;
}

static unsigned int icmp_hook_func(unsigned int hooknum,
             struct sk_buff **skb,
             const struct net_device *in,
             const struct net_device *out,
             int (*okfn)(struct sk_buff *))
{
//    struct iphdr *iph = ip_hdr(skb);
	struct iphdr *iph = (*skb)->nh.iph;
    struct packet_info info;
	struct ethhdr *eth_hdr1=(struct ethhdr *)((*skb)->mac.raw);
    //printk("%s, begin !!! \n", __func__);

//    if (iph->protocol == IPPROTO_ICMP) {
//	if ((*skb)->pkt_type == PACKET_MULTICAST ){
	if((eth_hdr1->h_dest[0] == 0x01) &&
		(eth_hdr1->h_dest[1] == 0x00) && 
		(eth_hdr1->h_dest[2] == 0x5e) && 
		((eth_hdr1->h_dest[3] == 0x76) ||(eth_hdr1->h_dest[3] == 0x7e))){
       		read_lock_bh(&user_proc.lock);
        
        	if (user_proc.pid != 0) {
            		info.src = iph->saddr;
            		info.dest = iph->daddr;
//            		printk("%s, src=%u.%u.%u.%u, dst=%u.%u.%u.%u\n", __func__,NIPQUAD(info.src), NIPQUAD(info.dest));
            		info.eth_hdrr=*eth_hdr1;
	    		info.len=(*skb)->len;
	    		send_to_user(&info);
       	 	} else {
         		printk("%s, no user process running..!\n", __func__);
      		}
        
        	read_unlock_bh(&user_proc.lock);
    	} 
    //printk("%s, end !!! \n", __func__);
    
    return NF_ACCEPT;
}

#define NF_IP_PRE_ROUTING    0

static struct nf_hook_ops my_icmp_hook = {
    .hook = icmp_hook_func,
    .pf = PF_INET,
    .hooknum = NF_IP_PRE_ROUTING,
    .owner = THIS_MODULE,
    .priority = NF_IP_PRI_FILTER - 1,
};

static void my_receive(struct sock *sk,int len)
{
    struct sk_buff *skb;
//    struct nlmsghdr *nlh=NULL;
    
    printk("%s, begin !!!!!\n", __func__);
    
    while((skb=skb_dequeue(&sk->sk_receive_queue))!=NULL)
    {
        {
              struct nlmsghdr *nlh = NULL;
        if(skb->len <= sizeof(struct nlmsghdr))
              {
                nlh = (struct nlmsghdr *)skb->data;


/*    		printk("skb len:%d !!!!!\n", len);
    		printk("len:%d !!!!!\n", nlh->nlmsg_len);
   		printk("type:%d !!!!!\n", nlh->nlmsg_type);
   		printk("flags:%d !!!!!\n", nlh->nlmsg_flags);
 		printk("seq:%d !!!!!\n", nlh->nlmsg_seq);
   		printk("pid:%d !!!!!\n", nlh->nlmsg_pid);
*/

                if((nlh->nlmsg_len <= sizeof(struct nlmsghdr))
                   && (skb->len <= nlh->nlmsg_len))
                  {
                    if(nlh->nlmsg_type == IMP2_U_PID)
                      {
                        user_proc.pid = nlh->nlmsg_pid;
                      }
                    else if(nlh->nlmsg_type == IMP2_CLOSE)
                      {
               if(nlh->nlmsg_pid == user_proc.pid) user_proc.pid = 0;
                      }
                  }
              }
          }


/*	nlh=(struct nlmsghdr *)skb-data;
        if (nlh->nlmsg_type == IMP2_U_PID) {
            user_proc.pid = nlh->nlmsg_pid;
        } else if (nlh->nlmsg_type == IMP2_CLOSE &&
                nlh->nlmsg_pid == user_proc.pid) {
            user_proc.pid = 0;
        }
*/


 	kfree_skb(skb);
    }







//    nlh = nlmsg_hdr(skb);
/*	nlh = (struct nlmsghdr *)skb->data;
    len = skb->len;

    printk("skb len:%d !!!!!\n", len);
    printk("len:%d !!!!!\n", nlh->nlmsg_len);
    printk("type:%d !!!!!\n", nlh->nlmsg_type);
    printk("flags:%d !!!!!\n", nlh->nlmsg_flags);
    printk("seq:%d !!!!!\n", nlh->nlmsg_seq);
    printk("pid:%d !!!!!\n", nlh->nlmsg_pid);

    while (NLMSG_OK(nlh, len)) {

        printk("%s, skb_len = %d!!!!!\n", __func__, len);

        if (nlh->nlmsg_type == IMP2_U_PID) {
            user_proc.pid = nlh->nlmsg_pid;
        } else if (nlh->nlmsg_type == IMP2_CLOSE &&
                nlh->nlmsg_pid == user_proc.pid) {
            user_proc.pid = 0;
        } 
        
        netlink_ack(skb, nlh, 0);
        nlh = NLMSG_NEXT(nlh, len);
    } 
  */
    printk("%s, end !!!!!\n", __func__);
}
/*
static void my_receive(struct sk_buff *skb)
{
    struct nlmsghdr *nlh;
    int len;
    
    printk("%s, begin !!!!!\n", __func__);

//    nlh = nlmsg_hdr(skb);
	nlh = (struct nlmsghdr *)skb->data;
    len = skb->len;

    printk("skb len:%d !!!!!\n", len);
    printk("len:%d !!!!!\n", nlh->nlmsg_len);
    printk("type:%d !!!!!\n", nlh->nlmsg_type);
    printk("flags:%d !!!!!\n", nlh->nlmsg_flags);
    printk("seq:%d !!!!!\n", nlh->nlmsg_seq);
    printk("pid:%d !!!!!\n", nlh->nlmsg_pid);

    while (NLMSG_OK(nlh, len)) {

        printk("%s, skb_len = %d!!!!!\n", __func__, len);

//        write_lock_bh(&user_proc.pid);
        if (nlh->nlmsg_type == IMP2_U_PID) {
            user_proc.pid = nlh->nlmsg_pid;
        } else if (nlh->nlmsg_type == IMP2_CLOSE &&
                nlh->nlmsg_pid == user_proc.pid) {
            user_proc.pid = 0;
        } 
//        write_unlock_bh(&user_proc.pid);
        
        netlink_ack(skb, nlh, 0);
        nlh = NLMSG_NEXT(nlh, len);
    } 
  
    printk("%s, end !!!!!\n", __func__);
}
*/

static int __init imp2_k_my_init(void)
{
    printk("%s, begin !!!!!\n", __func__);
    
    rwlock_init(&user_proc.lock);
    
    mysock = netlink_kernel_create(NETLINK_UNUSED, 0, my_receive, THIS_MODULE);
    if (!mysock) {
        printk("%s, netlink_kernel_create fail.. !!!!!\n", __func__);
        return -1;
    } 
    
    printk("%s, end !!!!!\n", __func__);

    return nf_register_hook(&my_icmp_hook);
}

static void __exit imp2_k_my_exit(void)
{
    printk("%s, begin !!!!!\n", __func__);
   // netlink_kernel_release(mysock);
    sock_release(mysock->sk_socket);
    nf_unregister_hook(&my_icmp_hook);
    printk("%s, end !!!!!\n", __func__);
}

module_init(imp2_k_my_init);
module_exit(imp2_k_my_exit);

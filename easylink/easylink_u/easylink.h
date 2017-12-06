/*imp1.h*/
#ifndef __IMP1_H__
#define __IMP1_H__

#define IMP1_OPS_BASIC 128
#define IMP1_SET IMP1_OPS_BASIC
#define IMP1_GET IMP1_OPS_BASIC
#define IMP1_MAX IMP1_OPS_BASIC + 1

#endif

#define IMP2_U_PID 0
#define IMP2_K_MSG 1
#define IMP2_CLOSE 2

struct packet_info{
	__u32 src;
	__u32 dest;
	struct ethhdr eth_hdrr;
	__u32 len;
};

struct rcv_link{
	__u32 len;
	char data[2];
	__u32 times;
	struct rcv_link *next;
};


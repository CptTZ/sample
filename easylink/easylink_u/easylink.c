#include <unistd.h>
#include <stdio.h>
#include <linux/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <asm/types.h>
#include <linux/netlink.h>
#include <signal.h>
#include <linux/if_ether.h>
#include "easylink.h"
#include <stdlib.h>
#include <time.h>
#include "notify.h"
#include "oid.h"
#include "common.h"
#include "list.h"
#include "time.h"
#define LEN_BEGIN 68
struct msg_to_kernel
{
    struct nlmsghdr hdr;
};

struct u_packet_info
{
  struct nlmsghdr hdr;
  struct packet_info icmp_info;
};

static int skfd;

static void sig_int(int signo)
{
    struct sockaddr_nl kpeer;
    struct msg_to_kernel message;

    memset(&kpeer, 0, sizeof(kpeer));
    kpeer.nl_family = AF_NETLINK;
    kpeer.nl_pid = 0;
    kpeer.nl_groups = 0;

    memset(&message, 0, sizeof(message));
    message.hdr.nlmsg_len = NLMSG_LENGTH(0);
    message.hdr.nlmsg_flags = 0;
    message.hdr.nlmsg_type = IMP2_CLOSE;
    message.hdr.nlmsg_pid = getpid();

    sendto(skfd, &message, message.hdr.nlmsg_len, 0, (struct sockaddr *)(&kpeer),
         sizeof(kpeer));

    close(skfd);
    exit(0);
}


void if_session_timeout()
{
	int i=0,chan;
	char buf[30];
	struct List *ret;
	struct session_link *sess_ret;
	struct timeval  now;
	gettimeofday(&now,NULL);	

	ret = session_head->next;
	while(ret != session_head){
		sess_ret = ENTRY_FIND(ret, struct session_link, list);
// 		printf("List %d\n",i);
// 		printf("MAC:%02x:%02x:%02x:%02x:%02x:%02x\n",
//				sess_ret->sess.mac[0],sess_ret->sess.mac[1],sess_ret->sess.mac[2],sess_ret->sess.mac[3],sess_ret->sess.mac[4],sess_ret->sess.mac[5]);	
 //		printf("Time_pre:%u,%u\n",sess_ret->sess.time_pre.tv_sec,sess_ret->sess.time_pre.tv_usec);
 //		printf("Time_now:%u,%u\n",now.tv_sec,now.tv_usec);
 //		printf("diff:%d,%d\n",now.tv_sec - sess_ret->sess.time_pre.tv_sec,now.tv_usec-sess_ret->sess.time_pre.tv_usec);
//		printf("------------------------------Time_out:%u,%u\n",sess_ret->sess.time_out.tv_sec,sess_ret->sess.time_out.tv_usec);
//		printf("#############################################    begin_len:%d\n",sess_ret->sess.beginlen);
		
//		if(sess_ret->sess.time_pre!=0)
		if(now.tv_sec - sess_ret->sess.time_pre.tv_sec > sess_ret->sess.time_out.tv_sec ||
		    (now.tv_sec - sess_ret->sess.time_pre.tv_sec == sess_ret->sess.time_out.tv_sec
			&& now.tv_usec-sess_ret->sess.time_pre.tv_usec > sess_ret->sess.time_out.tv_usec)){
			chan=sess_ret->sess.channel;
//			session_init(sess_ret);
			memset(&(sess_ret->sess),0,sizeof(struct session));
			sess_ret->sess.state = IDLE;
			sess_ret->sess.time_out.tv_sec=0;
			sess_ret->sess.time_out.tv_usec=400000;
			chan=chan%13+1;
			sess_ret->sess.channel=chan;
			sprintf(buf,"iwpriv ra0 set Channel=%d",chan);
/* 			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++%s\n",buf);
 */
			system(buf);
			gettimeofday(&(sess_ret->sess.time_pre),NULL);
			
//			session_del();
//			ssion_clear();
		}
		ret =  ret->next;
		i++;
	}
}

int mac_match(char * mac1, char* mac2)
{
	int i,sta=1;
	for(i=0;i<6;i++)
	 {
	 if(mac1[i]!=mac2[i]){
	 	sta=0;
		break;
	 	}	
	 }
	return sta;
}

int main(void)
{
    struct sockaddr_nl local;
    struct sockaddr_nl kpeer;
    int kpeerlen;
    struct msg_to_kernel message;
    struct u_packet_info info;
    int sendlen = 0;
    int rcvlen = 0;
//    int i=0;
    struct in_addr addr;
    struct ethhdr *ehdr;
    struct rcv_link rec_head={0};
    struct rcv_link *point,*pnew,*head=&rec_head;
    struct session_link *first_sess;
    int status=0;
    struct timeval timeout;
    fd_set rdfds;
	
    skfd = socket(PF_NETLINK, SOCK_RAW, NETLINK_UNUSED);
    if(skfd < 0) {
        printf("can not create a netlink socket\n");
        exit(0);
    }

    memset(&local, 0, sizeof(local));
    local.nl_family = AF_NETLINK;
    local.nl_pid = getpid();
    local.nl_groups = 0;
    if(bind(skfd, (struct sockaddr*)&local, sizeof(local)) != 0) {
        printf("bind() error\n");
        return -1;
    }
//////////¸ÄÎªº¯Êý
    signal(SIGINT, sig_int);

    memset(&kpeer, 0, sizeof(kpeer));
    kpeer.nl_family = AF_NETLINK;
    kpeer.nl_pid = 0;
    kpeer.nl_groups = 0;

    memset(&message, 0, sizeof(message));
    message.hdr.nlmsg_len = NLMSG_LENGTH(0);
    message.hdr.nlmsg_flags = 0;
    message.hdr.nlmsg_type = IMP2_U_PID;
    message.hdr.nlmsg_pid = local.nl_pid;

    sendto(skfd, &message, message.hdr.nlmsg_len, 0,
        (struct sockaddr*)&kpeer, sizeof(kpeer));
////////////////////////	

	session_head_init();
	first_sess = make_new_session();
	list_add(session_head,&(first_sess->list));
	
	
	timeout.tv_sec = 0;
	timeout.tv_usec = 100000;
    while(1) {	
	int i;
	if_session_timeout();
	FD_ZERO(&rdfds);
	FD_SET(skfd, &rdfds);

	int ret = select(skfd + 1, &rdfds, NULL, NULL, &timeout);
	if(ret < 0){
		printf("select err!\n");
		/**select err**/
//		continue;
	}else if(ret == 0){
//		printf("time out!\n");
//		continue;
	}else {
	
	
        	kpeerlen = sizeof(struct sockaddr_nl);
        	rcvlen = recvfrom(skfd, &info, sizeof(struct u_packet_info),
        		0, (struct sockaddr*)&kpeer, &kpeerlen);			
		ehdr=&info.icmp_info.eth_hdrr;
	
	/************select session********/	
		struct session_link *node=first_sess;	
//		session_idle();
//		node->sess.time_pre = time(NULL);
		
//  		printf("MAC:%02x:%02x:%02x:%02x:%02x:%02x\n", 				ehdr->h_dest[0], ehdr->h_dest[1], ehdr->h_dest[2], ehdr->h_dest[3], ehdr->h_dest[4], ehdr->h_dest[5]);	

		if(ehdr->h_dest[3] == 0x76 || ehdr->h_dest[3] == 0x7e)
		{
			
			gettimeofday(&(node->sess.time_pre),NULL);
			if(node->sess.time_out.tv_sec==0)
			{	
				node->sess.time_out.tv_sec=2;
				node->sess.time_out.tv_usec=0;
			}
		}
		if(node->sess.state == IDLE && node->sess.beginlen == 0 && info.icmp_info.len > 0
			&& ehdr->h_dest[3]==0x76 && ehdr->h_dest[4]==0x0
					&& ehdr->h_dest[5]==0x0 )
		{
			node->sess.beginlen = info.icmp_info.len;
		}
		if(node->sess.beginlen != 0)
		{
		switch(node->sess.state){
			case IDLE:
			
				if(ehdr->h_dest[3] == 0x76 && ehdr->h_dest[4] == 0x0
					&&ehdr->h_dest[5]==0x0&&info.icmp_info.len == node->sess.beginlen){
				/**************copy mac*******************/
					for(i=0;i<6;i++){
						node->sess.mac[i] = ehdr->h_source[i];
					}
					node->sess.state = GET_LEN;
				}
				break;
			case GET_LEN:
				if(mac_match(ehdr->h_source,node->sess.mac) && 
					ehdr->h_dest[3]==0x7e && info.icmp_info.len == node->sess.beginlen){
						node->sess.ssid_len = ehdr->h_dest[4];
						node->sess.pwd_len = ehdr->h_dest[5];
/* 						printf("ssid_len:%d,pwd_len:%d\n",node->sess.ssid_len,node->sess.pwd_len);
 */
						node->sess.state = RCV;
			 	}
				
				break;
			case RCV:
				if(mac_match(ehdr->h_source,node->sess.mac) &&
					ehdr->h_dest[3]==0x7e && info.icmp_info.len > node->sess.beginlen)
				{
					int length=(1+node->sess.ssid_len+node->sess.pwd_len)/2;
					if(info.icmp_info.len<= node->sess.beginlen +length){
				
						int i=(info.icmp_info.len-(node->sess.beginlen + 1))*2;
						node->sess.input[i] = (char)ehdr->h_dest[4];
						node->sess.input[i+1] = (char)ehdr->h_dest[5];
			
					}else if((info.icmp_info.len >= node->sess.beginlen + 1 + length) && (info.icmp_info.len < node->sess.beginlen + 3 + length)){
						if(ehdr->h_dest[4]==ehdr->h_dest[5]==0){
						node->sess.state = RCV_OK;
						}	
					}

				 }	
				break;
/* 			case RCV_OK:		
 * 				break;
 */
			case ERR:
				break;
			default:
				break;
			}

			if(node->sess.state == RCV_OK)
			{
				int i=0;
				for(i=0;i<node->sess.ssid_len+node->sess.pwd_len;i++)
	  			{
	  				if(node->sess.input[i]==0)
	  	 			{
	  	 				node->sess.state = IDLE;
						break;
	 	 	 		}	
	 	 		}
	 			if(node->sess.state==IDLE)
	  			{
//					memset(&(node->sess), 0, sizeof(struct session));
	  			}else
	  			{
	  				printf("SSID && PASSWD %s\n",node->sess.input);
					char username[64] = {0};
					char pwd[32] = {0};
					memcpy(username, node->sess.input, node->sess.ssid_len);
					memcpy(pwd, node->sess.input + node->sess.ssid_len, node->sess.pwd_len);
					nvram_set("ApCliSsid", username);
					nvram_set("ApCliWPAPSK", pwd);
					notification_send_rc(OID_WL_STA, NOTIFY_NOWAIT);
					return 0;
	  			}	
	 		}
/*         	printf("********************debug*******************\n");
                 printf("RECV STR:");
                 for(i=0;i<node->sess.ssid_len+node->sess.pwd_len;i++)
                printf("%c ",node->sess.input[i]);
                for(i=0;i<node->sess.ssid_len+node->sess.pwd_len;i++)
                printf("%02x ",node->sess.input[i]);
                printf("\nThe state is %d \n",node->sess.state);
                addr.s_addr = info.icmp_info.src;
                 printf("src: %s, ", inet_ntoa(addr));
                     addr.s_addr = info.icmp_info.dest;
                printf("dest: %s\n", inet_ntoa(addr));
                 printf("len: %d\n",info.icmp_info.len);
                 printf("src mac:\n");
                 printf("ehdr[h_dst(%02x:%02x:%02x:%02x:%02x:%02x)"
                          "h_source(%02x:%02x:%02x:%02x:%02x:%02x)]\n",
                          ehdr->h_dest[0], ehdr->h_dest[1], ehdr->h_dest[2],
                         ehdr->h_dest[3], ehdr->h_dest[4], ehdr->h_dest[5],
                        ehdr->h_source[0], ehdr->h_source[1], ehdr->h_source[2],
                        ehdr->h_source[3], ehdr->h_source[4], ehdr->h_source[5]);
 	        printf("********************end*******************\n");
*/
		}
		}
	}
    return 0;
}



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "common.h"
int session_head_init()
{
	session_head=(struct List *)malloc(sizeof(struct List));
	LIST_INIT(session_head);
}

void session_init(struct session_link *node)
{
	memset(node, 0, sizeof(struct session_link));
//	(node->sess).time_pre = time(NULL);
	(node->sess).state = IDLE;
	(node->sess).channel=1;
	gettimeofday(&(node->sess).time_pre,NULL);
	node->sess.time_out.tv_sec=0;
	node->sess.time_out.tv_usec=400000;
	system("iwpriv ra0 set Channel=1");
//	list_add(session_head , &node->list);
}
struct session_link *make_new_session()
{
	struct session_link *session_ret = (struct session_link*)malloc(sizeof(struct session_link));
	session_init(session_ret);
	return session_ret;
}

//int  begin_recv()
//{
//	if()
//		return 1;
//	return 0;
//}
/*void session_idle(struct session_link *node)
{
	switch(node->sess.state){
		case IDLE:
			if(begin_recv()){
				node->sess.state = RCV;
			}else {
				node->sess.state = ERR;
			}
			break;
		case RCV:
			break;
		case RCV_OK:
			break;
		case ERR:
			break;
	}
}
*/

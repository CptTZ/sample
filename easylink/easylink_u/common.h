#ifndef __COMMON__
#define __COMMON__
#include <time.h>
#include "list.h"
#define ENTRY_FIND(ptr, type, member) \
	((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))
#define INPUT_LEN	1024
struct List *session_head;
typedef enum {
	IDLE = 0,
	GET_LEN,
	RCV,
	RCV_OK,
	ERR,
}session_t;
struct session{
	char mac[6];		//flag of which dev;
	char input[INPUT_LEN];
	int ssid_len;
	int pwd_len;
	char ssid_PWD[64];
	session_t state;
	unsigned int channel;
	unsigned int beginlen;
	struct timeval time_out;
	struct timeval time_pre;		//flag of overtime;
};
struct session_link{
	struct session sess;
	struct List list;
};
#endif


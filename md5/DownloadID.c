#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

extern int MAC_to_DownloadID(const char *MAC, char *DownloadID);

static int mac_str_to_bin(const char *str, unsigned char *mac)
{
    int i;
    char *s,*e;
    if((mac == NULL) || (str == NULL))
    {
        return -1;
    }
    s = (char *) str;
    for (i = 0; i < 6; ++i)
    {
        mac[i] = s?strtoul(s, &e, 16) : 0;
        if (s)
           s = (*e)?e + 1:e;
    }
    return 0;
}

static int mac_check(const char *check_mac)
{
	int i=0, upper=0;
	if(check_mac == NULL)
		return -1;

	if(strlen(check_mac) != 17)
		return -2;

	for(i=0; i<17; i++)
	{
		if(i%3 == 2)
		{
			if(check_mac[i] == ':')
				continue;
			else
				return -2;
		} else {
			upper = toupper(check_mac[i]);
			if((upper > 'F') || (upper < '0') || ((upper > '9') && (upper < 'A')))
				return -2;
		}
	}
	return 0;
}
int MAC_to_DownloadID(const char *MAC, char *DownloadID)
{
	unsigned char addr[6]={0};
	unsigned char addr_str[16]={0};
	unsigned char addr_trans[6]={0};
	unsigned char addr_trans_str[16]={0};
	unsigned char md5sed[32]={0};
	unsigned char decrypt[16]={0};
	unsigned char decrypt_str[33]={0};
	unsigned char MAC_cpy[18]={0};
	int i = 0;
	struct MD5Context ctx;
	MD5Init(&ctx);

	if(0 != mac_check(MAC))
	{
		printf("Mac addr error!\n");
		return -1;
	}
	memset(MAC_cpy, 0, 18);
	memcpy(MAC_cpy, MAC, 17);
	mac_str_to_bin(MAC_cpy, addr);
	sprintf(addr_str, "%02X%02X%02X%02X%02X%02X", addr[0],addr[1],addr[2],addr[3],addr[4],addr[5]);
	strncpy(md5sed, addr_str, 12);
	strncat(md5sed, "PHICOMM", 7);
	for(i=0; i<6; i++)
	{
		addr_trans[i]=addr[5-i]^0xff;
	}
	sprintf(addr_trans_str, "%02X%02X%02X%02X%02X%02X", addr_trans[0],addr_trans[1],addr_trans[2],addr_trans[3],addr_trans[4],addr_trans[5]);
	strncat(md5sed, addr_trans_str, 12);
	MD5Update(&ctx, md5sed, strlen((char *)md5sed));
	MD5Final(decrypt, &ctx);
	sprintf(decrypt_str, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", decrypt[0],decrypt[1],decrypt[2],decrypt[3],decrypt[4],decrypt[5],decrypt[6],decrypt[7],decrypt[8],decrypt[9],decrypt[10],decrypt[11], decrypt[12],decrypt[13],decrypt[14],decrypt[15]);
	memset(DownloadID, 0, 33);
	memcpy(DownloadID, addr_str, 12);
	memcpy(DownloadID + 12, decrypt_str, 20);
	
	return 0;
}

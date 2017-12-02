#include <stdio.h>

#include "rsa.h"

int myrand( void *rng_state);

#define RSA_LEN (64 -1)
int parseasn1ofpubkey(rsa_context *prsa, unsigned char *pubkey)
{
	size_t size; /* Number of bytes read */
	int len = 0;
	int i = 0;
	int j = 0;
	unsigned char *ptemp = NULL;
	unsigned char *pc = NULL;

	if (pubkey == NULL)
		return -1;

	if (*(pubkey+22) != 0x02)
	{
		printf("not integer %02x\n", *(pubkey+23));
		return -1;
	}
	if ((*(pubkey+23) ) != 0x41 )
	{
		printf("wrong size %d %d \n", *(pubkey+24));
		return -1;
	}
	len = *(pubkey+23);
	printf("len = %d %d \n", len, sizeof(unsigned long));
	ptemp = pubkey+25; //skip 00, in host order, it is the end of CHAR ARRAY.
	prsa->N.p = malloc(16*sizeof(t_int));
	pc = prsa->N.p;
	for(i =0; i < 64; i=i+4)
	{
		printf("%02x %02x %02x %02x\n", ptemp[i], ptemp[i+1], 
				ptemp[i+2],ptemp[i+3]);
		pc[RSA_LEN-i] = ptemp[i];
		pc[RSA_LEN-(i+1)] = ptemp[i+1];
		pc[RSA_LEN-(i+2)] = ptemp[i+2];
		pc[RSA_LEN-(i+3)]   = ptemp[i+3];
	}
	//memcpy((unsigned char *)prsa->N.p, ptemp, len);
	prsa->len = 64;
	prsa->N.s = 1;
	prsa->N.n = 16;
	//for (i = 0; i < 16; i++)
	//{
	//	printf("%02x ", *(prsa->N.p+i));
	//}
	printf("\n");
	ptemp = ptemp+len -1;
	printf("%02x %02x %02x \n", *ptemp, *(ptemp+1), *(ptemp+2));

	//integer flag
	if (*ptemp != 0x02)
	{
		printf("wrong type\n");
		return -1;
	}

	//length
	if (*(ptemp+1) != 0x03)
	{
		printf("1 wrong size\n");
		return -1;
	}
	prsa->E.s =1;
	prsa->E.n =1;

	prsa->E.p = malloc(1*sizeof(t_int));
	ptemp = ptemp+2;
	//memcpy(prsa->E.p, ptemp+2, 3);
	pc = prsa->E.p;
	i = 0;

	pc[i+3]   = 0x0;
	pc[i+2] = ptemp[i];
	pc[i+1] = ptemp[i+1];
	pc[i+0] = ptemp[i+2];

	printf("prsa->E.p = %x\n", *prsa->E.p);

	return 0;
}
//#define ENCRYPT
#define DECRYPT
void main()
{
	FILE *fp = NULL;
	int len = 0;
	unsigned char buf[2048] = {0};
	int i = 0;
	rsa_context rsa;
	int rsa_key_len = 0;
	char data[8] = "hello\n";
	char pout[64] = {0};
	char *key="MFwwDQYJKoZIhvcNAQEBBQADSwAwSAJBAMKI7UsSNDveAbF8645q5gzio2b0A/tCBea2lkAnok8wzaia0BtRwk7JoC4egEpZ/iIWd4Wg3MC4eF8wM9NE8OUCAwEAAQ==";

	unsigned char en_data[] =
	{0x65,0x79,0x04,0x2d,0x17,0x8c,0xa4,0x2d,0xae,0xf8,0x86,0xb4,0x9f,0x7a,0xb2,0x53,
		0x33,0x2d,0x33,0x6c,0x22,0x56,0x6f,0xf3,0x59,0x90,0x0d,0xfc,0x5b,0xe3,0x3b,0x8d,
		0x0e,0x15,0xd1,0x82,0xd6,0x1f,0x3e,0xc3,0x8b,0x9c,0x9a,0x34,0x35,0x3b,0x01,0xf9,
		0x13,0xa9,0x99,0xa6,0x9c,0x2f,0x33,0xde,0x1a,0x5e,0x23,0x53,0xd5,0x91,0x0d,0xe1,0x00};

	unsigned char de_data[1024] = {0};
	//unsigned char en_data[1024] = {0};
	int a_len = 0;
	int out_len = 64;
	int j= 0;
	int ret = 0;
	rsa_key_base64_decode ((unsigned char *)key, buf, &rsa_key_len);
	rsa_init( &rsa, RSA_PKCS_V15, 0 );
	rsa_gen_key( &rsa, myrand, NULL, 512, 65537 );
	/*
	   fp = fopen("./test_pub_b.key", "r");
	   if (fp == NULL)
	   {
	   printf("fp == NULL\n");
	   return;
	   }

	   len = fread(buf, 1, 2048, fp);
	   printf("len = %d\n", len);
	   fclose(fp);
	   */

	printf("%02x %02x %02x \n", buf[0], buf[1], buf[2]);


	parseasn1ofpubkey(&rsa, buf);
	printf("rsa_test : ");
	for (i = 0; i < 16; i++)
	{
		printf("%02x ", *(rsa.N.p+i));
	}
	printf("\n");

	printf("rsa_test.N.n = %d rsa_test.N.s = %d\n", rsa.N.n, rsa.N.s);
	printf("rsa_test.E.n = %d rsa_test.E.s = %d\n", rsa.E.n, rsa.E.s);

	memset(pout, 0, out_len);
	// rsa_public( &rsa, buf, pout );
#ifdef ENCRYPT
	if( rsa_pkcs1_encrypt( &rsa, &myrand, NULL, RSA_PUBLIC, 8,
				data, pout ) != 0 )
	{
		printf("rsa_pkcs1 en fail \n");
		return;
	}
	fp = fopen("./test_out", "w");
	if (fp == NULL)
	{
		printf("fp == NULL\n");
		return;
	}
	len = fwrite(pout, 1, 64, fp);
	printf("len = %d\n", len);
	fclose(fp);
#endif

#ifdef DECRYPT
	/*
	   memset(en_data, 0, sizeof(en_data));
	   fp = fopen("./out.txt", "r");
	   if (fp == NULL)
	   {
	   printf("fp == NULL\n");
	   return;
	   }
	   memset(en_data, 0, sizeof(en_data));
	   len = fread(en_data, 1, 1024, fp);
	   printf("len = %d\n", len);
	   fclose(fp);
	   */


	i = 0;
	printf("en_data = %02x %02x\n", en_data[0], en_data[1]);
	while(en_data[i] != '\0')
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", en_data[i]);
		i++;
	}
	printf("\n");
	//en_data[len] = '\0';
	ret = rsa_pkcs1_decrypt( &rsa, RSA_PUBLIC, &a_len, en_data, de_data, 1024 ) ;
	if ( ret != 0)
	{
		printf("rsa_pkcs1 de fail %x \n", ret);
		return;
	}
	printf("de_data:%s\n", de_data);

	fp = fopen("./de_data", "w");
	if (fp == NULL)
	{
		printf("fp == NULL\n");
		return;
	}
	len = fwrite(de_data, 1, a_len, fp);
	printf("len = %d\n", len);
	fclose(fp);
#endif

	printf("rsa.ver = %d\n", rsa.ver);
	printf("rsa.padding = %d\n", rsa.padding);
	free(rsa.N.p);
	free(rsa.E.p);

	return;
}

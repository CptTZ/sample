
/*openssl genrsa -out private.pem 2048

���ɹ�Կ��
openssl rsa -in private.pem -pubout > public.pem


C����������ʾ��
��Linux�µı��룺gcc test.c -lcrypto -o test
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rsa.h"

int main()
{
    // ԭʼ����
    char plain[256]="���Բ���,hello123";

    // ��Կ��˽Կ�ļ�
    const char* pub_key_file="test_pub.key";
    const char* priv_key="test.key";
	//unsigned char tmp_autograph[64]; 
	int len = 0;
	int i = 0;
	unsigned char *rsa_pub_key_enc_buf = NULL;
	unsigned char *res_de_buf = NULL;
	FILE* fp = NULL;
	printf("strlen(plain) = %d\n", strlen(plain));
	rsa_pub_key_enc_buf = rsaEncrypt((char *)priv_key, plain);
	if ( !rsa_pub_key_enc_buf ) {
		printf("RSA encrypt failed\n");
		return -1;
	}


	char *pub_key;
	pub_key = getFileContent(pub_key_file);
	if ( !pub_key ) {
		return NULL;
	}

	len = strlen(rsa_pub_key_enc_buf);
	printf("rsa_pub_key_enc_buf len = %d\n", len);

	printf("en_buf : ");
	//for(i = 0; i < 64; i++)
	i = 0;
	while(rsa_pub_key_enc_buf[i] != '\0')
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", rsa_pub_key_enc_buf[i]);
		i++;
	}
	printf("\n");
	// ������ܺ������
	fp=fopen("out.txt","w");
	if(fp){
		fwrite(rsa_pub_key_enc_buf,len,1,fp);
		fclose(fp);
	}

#if 1
	res_de_buf = rsaDecrypt(pub_key, rsa_pub_key_enc_buf, len);
	if (res_de_buf == NULL)
	{
		printf("decrypto failed \n");
		return -1;
	}

	len = strlen(res_de_buf);
	printf("res_de_buf len = %d\n", len);

	// ������ܺ������
	fp=fopen("de_out.txt","w");
	if(fp){
		fwrite(res_de_buf,len,1,fp);
		fclose(fp);
	}
#endif
	free(rsa_pub_key_enc_buf);

}

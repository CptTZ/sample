#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <sys/stat.h>
#include <sys/types.h>

#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>

#include "rsa.h"

int padding = RSA_PKCS1_PADDING;

char *getFileContent(const char *filepath)
{
	struct stat filestat;
	int result = 0;
	result = stat(filepath, &filestat);
	if ( result == -1 ) {
		printf("Error: failed to get states of %s\n", filepath);
		return NULL;
	}
	char *content = malloc(filestat.st_size + 1);
	if ( !content ) {
		printf("Error: failed to malloc for public key\n");
		return NULL;
	}
	FILE *fp;
	fp = fopen(filepath, "r");
	if( !fp ) {
		printf("Error: failed to open %s\n", filepath);
		free(content);
		return NULL;
	}
	fseek(fp, 0, SEEK_SET);
	fread(content, filestat.st_size, sizeof(char), fp);
	fclose(fp);
	return content;
}


RSA *createRSA(unsigned char *key, int public)
{
	RSA *rsa = NULL;
	BIO *keybio;

	keybio = BIO_new_mem_buf(key, -1);

	if ( keybio == NULL ) {
		printf("Error: Failed to create key BIO\n");
	}

	if ( public ) {
		rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
	} else {
		rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
	}

	if( rsa == NULL ) {
		printf("Error: Failed to create RSA\n");
	}
	return rsa;
}

int private_encrypt(unsigned char *data, int data_len, unsigned char *key,
		unsigned char *encrypted)
{
	RSA *rsa = createRSA(key, 0);
	int result = RSA_private_encrypt(data_len, data, encrypted, rsa, padding);
	return result;
}

void printLastError(char *msg)
{
	char *err = malloc(130);;
	ERR_load_crypto_strings();
	ERR_error_string(ERR_get_error(), err);
	printf("%sERROR: %s\n", msg, err);
	free(err);
}


char *rsaEncrypt(char *KeyPath, char *inbuf)
{
	char *PrivateKey;
	PrivateKey = getFileContent(KeyPath);
	if ( !PrivateKey ) {
		return NULL;
	}
	int OutputLen = 0;
	int block = 64; // 512 位 RSA 加密的內容块以 64 字节为一个单位长度
	if ( strlen(inbuf) % block == 0 ) {
		OutputLen = strlen(inbuf);
	} else {
		OutputLen = (strlen(inbuf) / block + 1) * block;
	}
	char *output = malloc( OutputLen );
	if ( !output ) {
		printf("Error: failed to malloc output buf\n");
		free(PrivateKey);
		return NULL;
	}
	int enc_len = private_encrypt(inbuf, strlen(inbuf), PrivateKey, output);
	if( enc_len == -1 ) {
		printLastError("Private Encrypt failed\n");
		free(PrivateKey);
		return NULL;
	}
	printf("enc_len = %d inbuf_len = %d\n",enc_len, strlen(inbuf));
	free(PrivateKey);
	return output;
}
int public_decrypt(unsigned char *enc_data, int data_len, unsigned char *key,
		unsigned char *decrypted)
{
	RSA *rsa = createRSA(key, 1);
	int result = RSA_public_decrypt(data_len, enc_data, decrypted, rsa, padding);
	return result;
}

char *rsaDecrypt(char *key, char *enc_buf, int enc_len)
{
	printf("xxxxxxxxx1\n");
	if ( !key ) {
		return NULL;
	}
	printf("xxxxxxxxx2\n");
	char *output = malloc( 64 );
	if ( !output ) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}
	printf("xxxxxxxxx3\n");
	bzero(output, 64);
	int len = public_decrypt(enc_buf, enc_len, key, output);
	if( len == -1 ) {
		printLastError("Public Decrypt failed");
		return NULL;
	}
	printf("xxxxxxxxx4\n");
	return output;
}


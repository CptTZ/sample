
#include "base64.h"

const char* strstr_l(const char *str1, const char *str2)  
{  
    //assert(NULL != str1 && NULL != str2);  
    if (str1 == NULL || str2 == NULL )  
        return NULL;
    while(*str1 != '\0')  
    {  
        const char *p = str1;  
        const char *q = str2;  
        const char *res = NULL;  
        if(*p == *q)  
        {  
            res = p;  
            while(*p && *q && *p++ == *q++)  
            ;  

            if(*q == '\0')  
                return res;                      
        }  
        str1++;  
    }  
    return NULL;  
}  
char *strtok_l(char *s,const char *delim) 
{
    static char *last;
    char *tok;
    char *ucdelim;
    char *spanp;
    int c,sc;

    /*s为空，并且上次剩余值也为空，则直接返回NULL，否则s为last或当前值中有值的一方*/
    if (s == NULL ) 
    {
        s = last;
        if (s == NULL)
            return NULL;
    }
    
    int found = 0;//是否找到与delim匹配的字符
    
    //处理连续的待匹配的字符
cont:
    c=*s++;
    for (spanp = (char *)delim;(sc = *spanp++) != 0;)
    {
        if (c == sc)
            goto cont;
    }
    if (c == 0) 
    {
        last = NULL;
        return NULL;
    }

    tok = s-1;
    while (!found && *s != '\0') 
    {
        ucdelim = (char *) delim;
        while (*ucdelim) 
        {
            if (*s == *ucdelim) 
            {
                found = 1;
                *s = '\0';
                last = s + 1;
                break;
            }
            ucdelim++;
        }
        if (!found)
        {
            s++;
            if(*s=='\0')
                last = NULL;
        }
    }

    return tok;
}
char *strcat_l(char *str1, char *str2)
{
	char *pt = str1;

	if((str1==NULL)||(str2==NULL)) 
        return NULL;


    while(*str1!='\0') str1++;
	while(*str2!='\0') *str1++ = *str2++;
    
	*str1 = '\0';
	return pt;
}

void rsa_key_base64_decode(unsigned char *keybuf, unsigned char **res_key, int *len)
{
	unsigned char key[2048] = {0};
	unsigned char *ptoken = NULL;
    unsigned char *pub_key = NULL;
	unsigned int pubkey_len = 0;
	int i = 0;

	ptoken = (unsigned char *)strtok_l((char *)keybuf, "\n");

	while (ptoken != NULL)
	{
		//printf("ptoken = %s\n", ptoken);
		if (strstr_l((char *)ptoken, "PUBLIC") == NULL)
		{	
			strcat_l((char *)key, (char *)ptoken);
		}
		ptoken = (unsigned char *)strtok_l(NULL, "\n");
	}

	//printf("key = %s\n", key);
	//printf("key = %s len = %d\n", key, strlen((char *)key));
	pub_key = (unsigned char *)base64_decode((char *)key, &pubkey_len);
	//printf("pubkey_len = %d\n", pubkey_len);

    memcpy(res_key, pub_key, pubkey_len);
	*len = pubkey_len;
#if 1
	printf("key : ");	
	for (i = 0; i < pubkey_len; i++)
	{
		if ( i % 16 == 0)
		{
			printf("\n");
		}
		printf("%02x ", pub_key[i]);	
	}
	printf("\n");
#endif
    free(pub_key);
	return;
}


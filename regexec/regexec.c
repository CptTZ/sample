#include<stdio.h>                                                                                                        
#include<sys/types.h>
#include<regex.h>
#include<memory.h>
#include<stdlib.h>

int main(){

	char bematch[1024] = {0};
	char *pattern = "^aaa\\.bbb\\.|\\.aaa\\.bbb\\.|\\.aaa\\.bbb$|^aaa\\.bbb$";
	char errbuf[1024];
	char match[100];
	regex_t reg;
	int err,nm = 10;
	int len = 0;
	int i = 0;
	regmatch_t pmatch[nm];

	while(1){
		memset(bematch,0,sizeof(bematch));
		printf("please input a string!\n");
		scanf("%s", bematch);
		if(regcomp(&reg,pattern,REG_EXTENDED) < 0){
			regerror(err,&reg,errbuf,sizeof(errbuf));
			printf("err:%s\n",errbuf);
		}

		err = regexec(&reg,bematch,nm,pmatch,0);

		if(err == REG_NOMATCH) {
			printf("no match\n");
			continue;
		} else if(err) {
			regerror(err,&reg,errbuf,sizeof(errbuf));
			printf("err:%s\n",errbuf);
			exit(-1);
		}
		printf("receive match:\n");

		for(i=0;i<10 && pmatch[i].rm_so!=-1;i++){
			len = pmatch[i].rm_eo-pmatch[i].rm_so;
			if(len){
				memset(match,'\0',sizeof(match));
				memcpy(match,bematch+pmatch[i].rm_so,len);
				printf("%s\n",match);
			}
		}
	}
	return 0;
}

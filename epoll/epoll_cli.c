#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1024

int main(int argc, char **argv)
{
	int		    sockfd;
	char		recvline[MAXLINE + 1];
	struct sockaddr_in    servaddr;

	if (argc != 2)
	{
		printf("usage: a.out <IPaddress>");
		return 0;
	}

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error");
		return 0;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(5000);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
		printf("inet_pton error for %s", argv[1]);
		return 0;
	}

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
	{
		printf("socket error");
		return 0;
	}

	char input[100];
	while (fgets(input, 100, stdin) != NULL)
	{
		write(sockfd, input, strlen(input));

		int n = 0;
		int count = 0;
		while (1)
		{
			n = read(sockfd, recvline + count, MAXLINE);
			if (n == MAXLINE)
			{
				count += n;
				continue;
			}
			else 
				break;
		}
		printf("%s\n", recvline);
	}
	exit(0);
}

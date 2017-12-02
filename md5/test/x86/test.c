#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i;
	unsigned char downloadid[64];
	if(MAC_to_DownloadID( argv[1], downloadid) == 0)
	{
		printf("we got download id is:%s\n", downloadid);
	} else {
		printf("conv error!\n");
	}

	return 0;
}

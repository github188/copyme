#include<string.h>
#include<iconv.h>
#include<errno.h>
#include<stdio.h>

int chIconv( char *pSrc,size_t* sSrc, char* pDst, size_t* sDst )
{
	iconv_t fd = iconv_open("GBK","utf-8");
	if(fd == (iconv_t)-1) {
		if(errno == EINVAL)
			printf("Conversion not supported!\n");
		return -1;
	}

	iconv( fd, &pSrc, sSrc, &pDst, sDst );

	iconv_close(fd);

	return 0;
}



int main()
{

	char r1[5] = {"粤"};
	char d1[5] = {0};
	size_t size = sizeof(char) * 5;
	// memset(dst,0,SIZE);
	chIconv(r1, &size, d1, &size);

	printf("dst : %s \n",d1);

	return 0;
}

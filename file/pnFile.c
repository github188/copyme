
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

#include "pnFile.h"
#include "pnConstent.h"
#include "string.h"

size_t 
GetDataFromFile(
			const char *fileName, 
			const char **ptrData
			)
{
	static char name[LEN_MAX_FILENAME] = {0};
	static char* pMem = NULL;
	static size_t memlen = 0;

	/* Same file as before */
	if( 0 == strcmp(fileName,name) )
	{
		*ptrData = pMem;
		return memlen;
	}

	/* Not the same file, call unmap first */
	if(pMem) {
	  munmap(pMem, memlen);
	  pMem = NULL; memlen = 0;
	}

	struct stat statBuf;
	if( stat(fileName, &statBuf) )
	{
		perror("stat ");
		return 0;
	}

	int fd = open(fileName, O_RDONLY);
	if(fd == -1)
	{
		perror("open file");
		return 0;
	}
	
	pMem = (char*)mmap( NULL, statBuf.st_size, 
				PROT_READ, MAP_PRIVATE, fd, 0 );
	if( MAP_FAILED != (void*)pMem )	
	{
		*ptrData = pMem;
		memlen = statBuf.st_size;
	} else {
		pMem = NULL;
		memlen = 0;
	}
	return memlen;
}


int main()
{
	const char* ptr = NULL;
	size_t size = 0;
	size = GetDataFromFile("/home/peon/Workspace/pnlib/pnFile.c", 
				&ptr);
	if(0 < size)
	{
		printf("%s", ptr);
	}
	return 0;
}

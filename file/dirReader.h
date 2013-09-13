#ifndef DIR_READER_H
#define DIR_READER_H

#include"pnCommon.h"

/* [Platform]: PN_LINUX */
#ifdef PN_LINUX
#include <sys/types.h>
#include <dirent.h>
#endif
/* [Platform]: PN_WINDOWS */
#ifdef PN_WINDOWS
#include<io.h>
#endif // Windows

/* Class CDirReader: read a dir and access files */
class CDirReader{
	public:
		/* Constructor with dir's path and spec 
		 * when spec is not NULL,file name will 
		 * be filterd by spec */
		CDirReader(const char* path,
				const char* spec = 0);
		~CDirReader();
		/* Get Next file's name */
		bool NextFile(char* fname,int size);
		/* Close this dir */
		void Close(void);
		const static int LEN = 256;
	private:
		/* Is dir ready for reading */
		bool m_bReady;
		/* Filtration needed? */
		bool m_bSpec;
		/* Dir's full path */
		char m_aDir[LEN];
		/* Str used by filtration*/
		char m_aFilespec[LEN];
		/* Current file's full path&name */
		char m_aCurFile[LEN];

		/* Details */
#ifdef PN_LINUX
		DIR* m_pDir;
		struct dirent *m_pDirent;
#endif
#ifdef PN_WINDOWS
		bool m_bFirst;
		long m_hFile;
		struct _finddata_t m_fileinfo;
#endif
};

#endif // ifndef DIR_READER_H

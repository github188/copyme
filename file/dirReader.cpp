#include "dirReader.h"
#include <string.h>
#include <stdio.h>

CDirReader::CDirReader(const char* path,const char* spec)
{
	m_bReady = false;
	m_bSpec = false;
	memset(m_aDir,0,LEN);
	memset(m_aFilespec,0,LEN);
	memset(m_aCurFile,0,LEN);
	strncpy(m_aDir,path,LEN);
	if(spec){
		strncpy(m_aFilespec,spec,LEN);
		m_bSpec = true;
	}
#ifdef PN_LINUX
	m_pDir = NULL;
	m_pDirent = NULL;
	m_pDir = opendir(m_aDir);
	if(m_pDir == NULL){
		perror("Opendir: ");
	} else {
		m_bReady = true;
	}
#endif
#ifdef PN_WINDOWS
	char temp[LEN];
	memset(temp,0,LEN);
	strncpy(temp,m_aDir,LEN);
	if(m_bSpec)
		strncat(temp,m_aFilespec,LEN - strlen(temp));
	m_hFile = _findfirst(temp,&m_fileinfo);
	if(m_hFile == -1L){
		printf("dir(%s) open failed.\n",temp);
	} else {
		m_bReady = true;
		m_bFirst = true;
	}
#endif
}


CDirReader::~CDirReader()
{
	Close();
}

bool CDirReader::NextFile(char* fname,int size)
{
	memset(fname,0,size);
	if(m_bReady){
#ifdef PN_LINUX
		while( (m_pDirent = readdir(m_pDir) ) ){
			if( m_bSpec && !strstr(m_pDirent->d_name,m_aFilespec) ) continue;
			snprintf(fname,size,"%s/%s",m_aDir,m_pDirent->d_name);
			return true;
		}
		return false;
#endif
#ifdef PN_WINDOWS
		// static bool first = true;
		if(!m_bFirst){
			if( _findnext(m_hFile,&m_fileinfo) != 0)
				return false;
		}
		int i = 0;
		for(i = 0; i < size-1 && i < strlen(m_aDir);i++){
			fname[i] = m_aDir[i];
		}
		for(int j = 0;( i< (size-1) )&&( j < strlen(m_fileinfo.name) );i++,j++ ){
			fname[i] = m_fileinfo.name[j];
		}
		// fname[++i] = 0;
		m_bFirst = false;
		return true;
#endif
	} else {
		Close();
		return false;
	}
}

void CDirReader::Close()
{
#ifdef PN_LINUX
	if(m_pDir)
		closedir(m_pDir);
	m_pDir = NULL;
#endif
#ifdef PN_WINDOWS
	if(m_hFile != -1L)
		_findclose(m_hFile);
	m_hFile = -1L;
#endif 
	m_bReady = false;
}

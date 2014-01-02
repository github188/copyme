
#include "sliding_window.h"

#include <stdlib.h> 
#include <string.h>

#include <pthread.h>

struct sliding_window {
	
	unsigned size;      /* 窗口总大小 */
	unsigned readable;  /* 可读字节数 */
	
	unsigned wpos;      
	unsigned rpos;      /* 读写的位置 */
	
	char *data;         /* 数据 */
	char rwflag;        /* 读写状态标志 */

	pthread_mutex_t lock;   /* 访问控制，确保线程安全 */
};

inline void swindow_reset(swindow_t *pwin)
{
	if(pwin == NULL) return ;
	
	if( 0 != pthread_mutex_lock( &(pwin->lock) ) )
		return;

	pwin->readable = 0;
	pwin->wpos = 0;
	pwin->rpos = 0;
	pwin->rwflag = 0;

	pthread_mutex_unlock( &(pwin->lock) );
}

/* 1. 为新的窗口创建空间
 * 2. 将所有成员初始化为0
 * 3. 为成员data分配s大小的空间
 * 4. 初始化lock成员
 */
inline swindow_t *swindow_create(unsigned s)
{
	swindow_t *ptr = (swindow_t *)calloc(1, sizeof(struct sliding_window) );

	if(ptr == NULL)
		return NULL;

	if ( pthread_mutex_init( &(ptr->lock), NULL) != 0 ) {
		free(ptr);
		return NULL;
	}

	ptr->data = (char *) calloc(1, s);
	if(ptr->data == NULL) {
		pthread_mutex_destroy( &(ptr->lock)  );
		free(ptr);
		return NULL;
	}

	ptr->size = s;
	return ptr;
}

/* 释放data占用的空间，释放结构提本身占用的空间 */
inline void swindow_destroy(swindow_t **pwin)
{
	if(pwin != NULL && *pwin != NULL) {
		
		if( 0 == pthread_mutex_lock( &( (*pwin)->lock ) ) ) {
			swindow_t *temp = *pwin;
			*pwin = NULL;
			pthread_mutex_unlock( &(temp->lock) );

			if( temp->data != NULL )
				free( temp->data );

			pthread_mutex_destroy( &(temp->lock) );

			free(temp);
		}
	}
}


int swindow_putdata(swindow_t *pwin, const char *src, unsigned s)
{
	if(pwin == NULL || src == NULL) 
		return -1;

	if( 0 != pthread_mutex_lock( &(pwin->lock) ) )
		return -1;

	unsigned write = pwin->size - pwin->readable;
	if( s > write ) {
		pthread_mutex_unlock( &(pwin->lock) );
		return write;
	}

	if( !(pwin->rwflag) ) { 
		/* 位置关系:  |---r---w----|size */
		unsigned temp = pwin->size - pwin->wpos;

		char flag = (temp >= s);
		if(flag) {
			memcpy(pwin->data + pwin->wpos, src, s);
			pwin->wpos += s;
		}else {
			memcpy(pwin->data + pwin->wpos, src, temp);
			memcpy(pwin->data, src + temp, s - temp);
			pwin->wpos = s - temp;
			
			pwin->rwflag = !pwin->rwflag;
		}

	} else { 
		/* 位置关系:  |---w---r----|size */
		memcpy(pwin->data + pwin->wpos, src, s);
		pwin->wpos += s;
	}

	pwin->readable += s;

	pthread_mutex_unlock( &(pwin->lock) );

	return 0;
}

int swindow_getdata(swindow_t *pwin, char *dest, unsigned s)
{
	if(pwin == NULL || dest == NULL )
		return -1;

	if( 0 != pthread_mutex_lock( &(pwin->lock) ) )
		return -1;

	if(pwin->readable < s) {
		pthread_mutex_unlock( &(pwin->lock) );
	   	return -1;
	}

	if( !pwin->rwflag) {
		/* 位置关系:  |---r---w----|size */
		memcpy(dest, pwin->data + pwin->rpos, s);
		pwin->rpos += s;
	} else {
		/* 位置关系:  |---w---r----|size */
		unsigned temp = pwin->size - pwin->rpos;

		char enough = temp >= s;
		if(enough) {
			memcpy(dest, pwin->data + pwin->rpos, s);
			pwin->rpos += s;
		} else {
			memcpy(dest, pwin->data + pwin->rpos, temp);
			memcpy(dest + temp, pwin->data, s - temp);
			pwin->rpos = s - temp;

			pwin->rwflag = !pwin->rwflag;
		}
	}

	pwin->readable -= s;

	pthread_mutex_unlock( &(pwin->lock) );

	return 0;
}


int swindow_tryget(swindow_t *pwin, char *dest, unsigned s)
{
	if(pwin == NULL || dest == NULL)
		return -1;

	if( 0 != pthread_mutex_lock( &(pwin->lock) ) )
		return -1;

	int temp = (pwin->readable >= s) ? s : pwin->readable ;

	if( !pwin->rwflag) {
		/* 位置关系:  |---r---w----|size */
		memcpy(dest, pwin->data + pwin->rpos, temp);
	} else {
		/* 位置关系:  |---w---r----|size */
		unsigned i = pwin->size - pwin->rpos;
		char enough = i >= temp;
		if(enough) {
			memcpy(dest, pwin->data + pwin->rpos, temp);
		} else {
			memcpy(dest, pwin->data + pwin->rpos, i);
			memcpy(dest + i, pwin->data, temp - i);
		}
	}

	pthread_mutex_unlock( &(pwin->lock) );

	return temp;
}


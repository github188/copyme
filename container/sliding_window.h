
/* 滑动窗口 (FIFO) 接口
 * 滑动窗口用来放入和取出数据
 */

#ifndef SLIDING_WINDOW_H
#define SLIDING_WINDOW_H

typedef struct sliding_window swindow_t;

/* 函数 swindow_create: 创建一个窗口，大小为size 
 * size: 为新创建的窗口分配空间的大小 (bytes)
 * RETURN: 指向窗口的指针
 */
swindow_t *swindow_create(unsigned size);

/*函数 swindow_destroy: 销毁一个窗口，将*pwin置为NULL */
void swindow_destroy(swindow_t **pwin);

/* 重置，清空数据 */
void swindow_reset(swindow_t *pwin);

/* 函数 swindow_putdata: 往pwin中放入大小为size的数据data 
 * 成功返回0, 如果数据无法全部放入，则返回剩余空间的大小
 * 其他错误返回 -1
 */
int swindow_putdata(swindow_t *pwin, const char *data, unsigned size);


/* 读取大小为size的数据，并存放到data中,用户需保证data处有可用的空间
 * 成功返回0, 如果可读的数据小于size则返回可读数据的大小
 * 其他错误返回 -1
 */
int swindow_getdata(swindow_t *pwin, char *data, unsigned size);


/* 尝试从窗口中读取大小为size的数据
 * 这个操作不会改变窗口中的数据以及窗口的可用大小
 * RETURN: 实际读入data处数据的大小
 */
int swindow_tryget(swindow_t *pwin, char *data, unsigned size);

#endif


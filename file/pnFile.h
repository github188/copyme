

#ifndef PN_FILE_H
#define PN_FILE_H

/* 从文件读取所有的数据，函数内部分配内存, 不可重入 */
/* ptrData -> ptr -> data */
size_t GetDataFromFile(const char* fileName, const char** ptrData);


#endif

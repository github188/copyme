#ifndef PN_COMMON_H
#define PN_COMMON_H

#include "pnconst.h"

/* Platform,you can only use one of them */

#define PN_LINUX
// #define PN_WINDOWS

/* Platform end */


/* use namespace in c++ code */
#ifdef __cplusplus

#define PNNAMESPACEBEGIN namespace PNnet {
#define PNNAMESPACEEND };
#define PN(name) PNnet::name

#else

#define PNNAMESPACEBEGIN 
#define PNNAMESPACEEND
#define PN(name) name

#endif

PNNAMESPACEBEGIN

/* version of this lib */
const int version_major = 0;
const int version_minor = 1;

PNNAMESPACEEND

#endif // ifndef PN_COMMON_H

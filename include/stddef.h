#ifndef STDDEF_H
#define STDDEF_H

typedef unsigned long size_t;
typedef long ptrdiff_t;

#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif

#define offsetof(type, member) ((size_t) & (((type *)0)->member))

#endif

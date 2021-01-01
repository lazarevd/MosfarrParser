#include <stdio.h>
#include <tidy.h>
#include <tidybuffio.h>
size_t strlcpy(char * __restrict dst, const char * __restrict src, size_t dsize);
	//FROM FREEBSD source https://github.com/freebsd/freebsd-src/blob/master/sys/libkern/strlcpy.c
void printNode(TidyDoc tdoc, TidyNode tnode, int symbols);

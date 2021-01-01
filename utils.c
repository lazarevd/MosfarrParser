

#include <tidy.h>
#include <tidybuffio.h>
#include <stdio.h>
size_t strlcpy(char * __restrict dst, const char * __restrict src, size_t dsize)
{
	//FROM FREEBSD source https://github.com/freebsd/freebsd-src/blob/master/sys/libkern/strlcpy.c
	const char *osrc = src;
	size_t nleft = dsize;
	/* Copy as many bytes as will fit. */
	if (nleft != 0) {
		while (--nleft != 0) {
			if ((*dst++ = *src++) == '\0')
				break;
		}
	}
	/* Not enough room in dst, add NUL and traverse rest of src. */
	if (nleft == 0) {
		if (dsize != 0)
			*dst = '\0';		/* NUL-terminate dst */
		while (*src++)
			;
	}
	return(src - osrc - 1);	/* count does not include NUL */
}


void printNode(TidyDoc tdoc, TidyNode tnode, int symbols) {
TidyBuffer buf;
char * prtext = malloc(sizeof(char) * symbols);
      tidyBufInit(&buf);
      tidyNodeGetText(tdoc, tnode, &buf);
      strlcpy(prtext, buf.bp?(char *)buf.bp:"", symbols-1);
	//printf("\n--------%s\n-------", buf.bp?(char *)buf.bp:"");
      printf("\n--------\n%s\n-------\n", prtext);
      tidyBufFree(&buf);
      free(prtext);

}

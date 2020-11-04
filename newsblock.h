#include <stdlib.h>
#ifndef H_NEWSBLOCK
#define H_NEWSBLOCK
struct NewsBlock {
    int * id;
    char * date;
    char * title;
    char * url;
    char * body;
};
#endif

void initNewsBlock(struct NewsBlock ** newsBlock);

void freeNewsBlock(struct NewsBlock * newsBlock );

void initNewsBlocks(struct NewsBlock * newsBlock, size_t sz );

void freeNewsBlocks(struct NewsBlock * newsBlock, size_t sz );

#include <stdlib.h>
#ifndef H_NEWSBLOCK
#define H_NEWSBLOCK

#define MAX_DATE_LENGTH 14
#define MAX_URL_LENGTH 700
#define MAX_TITLE_LENGTH 300
#define MAX_BODY_LENGTH 500


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

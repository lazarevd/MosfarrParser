#include <stdlib.h>

struct NewsBlock {
    int id;
    char * date;
    char * title;
    char * url;
    char * body;
};


void freeNewsBlock(struct NewsBlock * newsBlock );

void initNewsBlock(struct NewsBlock ** newsBlock);

void initNewsBlocks(struct NewsBlock * newsBlock, size_t sz );

void freeNewsBlocks(struct NewsBlock * newsBlock, size_t sz );

#include <stdlib.h>

struct NewsBlock {
    int id;
    char * date;
    char * title;
    char * url;
    char * body;
};


/*
void initNewsBlock(struct NewsBlock ** newsBlock) {
*newsBlock =  malloc(sizeof(struct NewsBlock));
*(*newsBlock).date = malloc(sizeof(char) * 12);
**newsBlock.title = malloc(sizeof(char) * 500);
*newsBlock->url = malloc(sizeof(char) * 700);
*newsBlock->body = malloc(sizeof(char) * 700);
}
*/
/*
void freeNewsBlock(struct NewsBlock ** newsBlock ) {
free(*newsBlock->date);
free(*newsBlock->title);
free(*newsBlock->url);
free(*newsBlock->body);
free(*newsBlock);
}
*/
/*
void initNewsBlocks(struct NewsBlock * newsBlock, size_t sz ) {
for (int i = 0; i < sz; i++) {
initNewsBlock(*newsBlock + i);
}
}

void freeNewsBlocks(struct NewsBlock * newsBlock, size_t sz ) {
for (int i = 0; i < sz; i++) {
freeNewsBlock(*newsBlock + i);
}
*/


int main(int argc, char **argv)
{

struct NewsBlock * nb;

nb = malloc(sizeof(struct NewsBlock));


}


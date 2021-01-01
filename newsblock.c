#include <stdlib.h>
#include <string.h>
#include "newsblock.h"

#define UNICODE_BYTES 4

void mallocNBFields(struct NewsBlock * nb) {
nb->id = malloc(sizeof(int));
nb->date = malloc(sizeof(char) * MAX_DATE_LENGTH * UNICODE_BYTES);
nb->title = malloc(sizeof(char) * MAX_TITLE_LENGTH * UNICODE_BYTES);
nb->url = malloc(sizeof(char) * MAX_URL_LENGTH * UNICODE_BYTES);
nb->body = malloc(sizeof(char) * MAX_BODY_LENGTH * UNICODE_BYTES);
}


struct NewsBlock * mallocNewsBlock() {
struct NewsBlock * nbt;
nbt =  malloc(sizeof(struct NewsBlock));
mallocNBFields(nbt);
return nbt;
}



void freeNewsBlock(struct NewsBlock * newsBlock ) {
free(newsBlock->id);
free(newsBlock->date);
free(newsBlock->title);
free(newsBlock->url);
free(newsBlock->body);
free(newsBlock);
}

void initNewsBlock(struct NewsBlock ** newsBlock) {
struct NewsBlock * nbt = *newsBlock;
nbt = mallocNewsBlock();
*newsBlock = nbt;
}



void initNewsBlocks(struct NewsBlock * newsBlock, size_t sz ) {
for (int i = 0; i < sz; i++) {
mallocNBFields(newsBlock+i);
}
}

void freeNewsBlocks(struct NewsBlock * newsBlock, size_t sz ) {
for (int i = 0; i < sz; i++) {
free(newsBlock[i].id);
free(newsBlock[i].date);
free(newsBlock[i].title);
free(newsBlock[i].url);
free(newsBlock[i].body);
}
}

/*
int main(int argc, char **argv)
{
struct NewsBlock * nb;
initNewsBlock(&nb);
freeNewsBlock(nb);

(*nb).date = "20.10.20";


struct NewsBlock * arr = malloc(sizeof(struct NewsBlock) * 10);
initNewsBlocks(arr, 10);

strcpy(arr[0].url,"htto://strangeurl.com");
strcpy(arr[6].date, "02.12.85");
strcpy(arr[3].url,"http://www.ru");
//free(arr[0].date);

freeNewsBlocks(arr, 10);
free(arr);
}
*/

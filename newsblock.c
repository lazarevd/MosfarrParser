#include <stdlib.h>
#include <string.h>

struct NewsBlock {
    int id;
    char * date;
    char * title;
    char * url;
    char * body;
};

void mallocNBFields(struct NewsBlock * nb) {
nb->date = malloc(sizeof(char) * 12);
nb->title = malloc(sizeof(char) * 500);
nb->url = malloc(sizeof(char) * 700);
nb->body = malloc(sizeof(char) * 700);
}


struct NewsBlock * mallocNewsBlock() {
struct NewsBlock * nbt;
nbt =  malloc(sizeof(struct NewsBlock));
mallocNBFields(nbt);
return nbt;}



void freeNewsBlock(struct NewsBlock * newsBlock ) {
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
free(newsBlock[i].date);
free(newsBlock[i].title);
free(newsBlock[i].url);
free(newsBlock[i].body);
}
}



int main(int argc, char **argv)
{
/*
struct NewsBlock * nb;
struct NewsBlock ** nb1;
nb1 = &nb;
struct NewsBlock * z;
z = *nb1;
z = malloc(sizeof(struct NewsBlock));
z->date = malloc(sizeof(char) * 12);
free(z->date);
free(z);
*/


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

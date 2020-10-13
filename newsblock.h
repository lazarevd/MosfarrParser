#include <stdlib.h>

struct NewsBlock {
    int id;
    char * date;
    char * title;
    char * url;
    char * body;
};

void initNewsBlock(struct NewsBlock * newsBlock, size_t sz ) {
for (int i = 0; i < sz; i++) {
newsBlock[i].date = malloc(sizeof(char) * 12);
newsBlock[i].title = malloc(sizeof(char) * 500);
newsBlock[i].url = malloc(sizeof(char) * 700);
newsBlock[i].body = malloc(sizeof(char) * 700);
}
}
void freeNewsBlock(struct NewsBlock * newsBlock, size_t sz ) {
for (int i = 0; i < sz; i++) {
free(newsBlock[i].date);
free(newsBlock[i].title);
free(newsBlock[i].url);
free(newsBlock[i].body);
}
}

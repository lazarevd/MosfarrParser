#include <stdio.h>
#include <tidy.h>
#include <tidybuffio.h>

size_t write_cb(char *in, size_t size, size_t nmemb, TidyBuffer *userdata);

int hash(char * input);

int getHtml(char* url, TidyBuffer * docbuf);

int getNodeByClass(TidyNode parentNode, ctmbstr findName, TidyNode * resultArr, int resultInitSize);

int getNodeByName(TidyNode parentNode, ctmbstr findName, TidyNode * resultArr,int resultInitSize);

void nodeGetText(TidyDoc doc, TidyNode node, char * textDest);


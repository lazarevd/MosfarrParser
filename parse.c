#include <stdio.h>
#include <curl/curl.h>
#include <tidy.h>
#include <tidybuffio.h>
#include "newsblock.h"
#include <sqlite3.h>
#include "sql.h"

size_t write_cb(char *in, size_t size, size_t nmemb, TidyBuffer *userdata) {
uint r;
  r = size * nmemb;
  tidyBufAppend(userdata, in, r);
  printf("write %s\n", in);  
return r;
}


int getHtml(char* url, TidyBuffer * docbuf) {
int ret = 0;
CURL *curl;

int err;
curl = curl_easy_init();
curl_easy_setopt(curl, CURLOPT_URL, url);
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, docbuf);
curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);


err = curl_easy_perform(curl);
curl_easy_cleanup(curl);
return err;
}


void dumpNode(TidyDoc doc, TidyNode tnod, int indent)
{
  TidyNode child;
  int i = 0;
  for(child = tidyGetChild(tnod); child; child = tidyGetNext(child) ) {
    ctmbstr name = tidyNodeGetName(child);
    if(name) {
	printf("node name: %s\n", name);
      /* if it has a name, then it's an HTML tag ... */ 
      TidyAttr attr;
      //printf("%*.*s%s ", indent, indent, "<", name);
      /* walk the attribute list */ 
      for(attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr) ) {
        printf("attr name: %s\n", tidyAttrName(attr));
        tidyAttrValue(attr)?printf("attr val: %s\n",
                                   tidyAttrValue(attr)):printf(" ");
      }
      printf("\n");
    }
  //  else {
      /* if it doesn't have a name, then it's probably text, cdata, etc... */ 
//      TidyBuffer buf;
//      tidyBufInit(&buf);
//      tidyNodeGetText(doc, child, &buf);
//      printf("%*.*s\n", indent, indent, buf.bp?(char *)buf.bp:"");
//      tidyBufFree(&buf);
//    }
i++;
    //dumpNode(doc, child, indent + 1); /* recursive */ 
  }
}


void printNode(TidyDoc tdoc, TidyNode tnod)
{
  ctmbstr name = tidyNodeGetName(tnod);
  int i = 0;
    if(name) {
	printf("nod name: %s\n", name);
      TidyAttr attr;
      for(attr = tidyAttrFirst(tnod); attr; attr = tidyAttrNext(attr) ) {
        printf("attr name: %s\n", tidyAttrName(attr));
        tidyAttrValue(attr)?printf("attr val: %s\n",
                                   tidyAttrValue(attr)):printf(" ");
      }
      printf("\n");
    }
    else {
      /* if it doesn't have a name, then it's probably text, cdata, etc... */ 
      TidyBuffer buf;
      tidyBufInit(&buf);
      tidyNodeGetText(tdoc, tnod, &buf);
      printf("TEXT: %s\n", buf.bp?(char *)buf.bp:"");
      tidyBufFree(&buf);
    }
i++;
}




int getNodeByClass(TidyNode parentNode, ctmbstr findName, TidyNode * resultArr, int resultInitSize) {
  TidyNode child;
  int resultSize = 0;
  for(child = tidyGetChild(parentNode); child; child = tidyGetNext(child) ) {
    ctmbstr name = tidyNodeGetName(child);
    //printf("%s\n", name);
    if (name) {
      TidyAttr attr;
      for(attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr) ) {
	ctmbstr attName = tidyAttrName(attr);      
	ctmbstr attVal = tidyAttrValue(attr);      
        if (strcmp("class", attName) == 0 
	&& strcmp(findName, attVal) == 0
        && resultSize < resultInitSize) {
		resultArr[resultSize] = child;
		resultSize++;
        }
      }
    }
  }
return resultSize;
}


int getNodeByName(TidyNode parentNode, ctmbstr findName, TidyNode * resultArr,int resultInitSize) {
  TidyNode child; 
  int resultSize = 0;
  for(child = tidyGetChild(parentNode); child; child = tidyGetNext(child) ) {
    ctmbstr name = tidyNodeGetName(child);
//    printf("%s\n", name);
    if(name && strcmp(name, findName) == 0 
	&& resultSize < resultInitSize)  {
resultArr[resultSize] = child;resultSize++;
   }
}
return resultSize;
}



void nodeGetText(TidyDoc doc, TidyNode node, char * textDest) {

     // char * res = malloc(sz);
      TidyBuffer buf;
      tidyBufInit(&buf);
      tidyNodeGetText(doc, node, &buf);
      strcpy(textDest, buf.bp?(char *)buf.bp:"");
      tidyBufFree(&buf);
      //return res;
}

void setDate(TidyDoc tdoc,
		  TidyNode newsNode,
		  struct NewsBlock newsBlk) {

TidyNode tmpNode[1];
getNodeByClass(newsNode, "date", tmpNode, 1);
tmpNode[0] = tidyGetChild(tmpNode[0]); 
nodeGetText(tdoc, tmpNode[0], newsBlk.date);
}

void setUrl(TidyDoc tdoc,
		  TidyNode newsNode,
		  struct NewsBlock newsBlk) {

TidyNode tmpNode[1];
getNodeByName(newsNode, "a", tmpNode, 1);
      TidyAttr attr;
      for(attr = tidyAttrFirst(tmpNode[0]); attr; attr = tidyAttrNext(attr) ) {
	ctmbstr attName = tidyAttrName(attr);      
	ctmbstr attVal = tidyAttrValue(attr);      
        if (strcmp("href", attName) == 0) {
        strcpy(newsBlk.url, attVal);
	}
      }
}
int fillNewsStruct(TidyDoc tdoc,
		  TidyNode * nodesArr, 
		  size_t nodesArrSize, 
		  struct NewsBlock * newsArr,
		  size_t newsArrSize) {
int res = 0;

for (int i = 0; i < nodesArrSize && i < newsArrSize; i++) {

TidyNode tmpNode[1];
getNodeByClass(nodesArr[i], "item-block item-news", tmpNode, 1);

setDate(tdoc, tmpNode[0], newsArr[i]);
setUrl(tdoc, tmpNode[0], newsArr[i]);

res++;
//free(dt);
}
return res;
}





int parseHtml(TidyBuffer * docbuf, struct NewsBlock * out, size_t out_sz) {
int res = -1;
TidyDoc tdoc; 
int err;
tdoc = tidyCreate();
tidyOptSetBool(tdoc, TidyForceOutput, yes);
tidyOptSetInt(tdoc, TidyWrapLen, 4096);



if (docbuf)
{
tidyParseBuffer(tdoc, docbuf); 
TidyNode body = tidyGetBody(tdoc);


TidyNode resNd[out_sz];
res = getNodeByName(body, "main", resNd, 1); 
printf("main %d\n", res);
res = getNodeByClass(resNd[0], "container", resNd, 1); 
printf("container %d\n", res);
res = getNodeByClass(resNd[0], "row container-news", resNd, 1); 
printf("row container-news %d\n", res);
res = getNodeByClass(resNd[0], "col-sm-6", resNd, out_sz); 
printf("col-sm-6 %d\n", res);
//res = getNodeByName(resNd[0], "div", resNd, initSize); 
//printf("%d\n", res);

fillNewsStruct(tdoc, resNd, res, out, out_sz);

}

tidyBufFree(docbuf);
tidyRelease(tdoc);
return res;
}

/* Traverse the document tree */ 
int main(int argc, char **argv)
{


TidyBuffer docbuf = {0};
//tidyOptSetBool(tdoc, TidyForceOutput, yes);
//tidyOptSetInt(tdoc, TidyWrapLen, 4096);
tidyBufInit(&docbuf);
int err = getHtml("https://mosfarr.ru/category/%D0%BD%D0%BE%D0%B2%D0%BE%D1%81%D1%82%D0%B8/", &docbuf);

sqlite3 *db;
char *err_msg = 0; 
int rc = sqlite3_open_v2("rr.db", &db, SQLITE_OPEN_READWRITE,NULL);
size_t newsSize = 20;
struct NewsBlock news[newsSize];
initNewsBlocks(news, newsSize);
err = parseHtml(&docbuf, news, newsSize);
//printf("%s, %s, %s", news[0].date, news[0].url, news[0].title);
insertNewsBlock(db, news[0]);
freeNewsBlocks(news, newsSize);

sqlite3_close(db);
return err;

}

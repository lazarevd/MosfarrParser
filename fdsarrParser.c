#include <stdio.h>
#include <curl/curl.h>
#include <tidy.h>
#include <tidybuffio.h>
#include "newsblock.h"
#include <sqlite3.h>
#include "sql.h"
#include "sender.h"
#include "parse.h"
#include "utils.h"

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
	char * t = malloc(1000);
	strcpy(t,attVal);
	int i = hash(t);
	*newsBlk.id = i;
	printf("%s%d\n", "nb ", *newsBlk.id);	
}
      }
}

void setTitle(TidyDoc tdoc,
		  TidyNode newsNode,
		  struct NewsBlock newsBlk)
{
TidyNode tmpNode[1];
getNodeByName(newsNode, "a", tmpNode, 1);
getNodeByName(tmpNode[0], "h2", tmpNode, 1);
tmpNode[0] = tidyGetChild(tmpNode[0]); 
nodeGetText(tdoc, tmpNode[0], newsBlk.title);
}


void setBody(TidyDoc tdoc,
		  TidyNode newsNode,
		  struct NewsBlock newsBlk)
{
strcpy(newsBlk.body,"");
}




int fillNewsStruct(TidyDoc tdoc,
		  TidyNode * nodesArr, 
		  size_t nodesArrSize, 
		  struct NewsBlock * newsArr,
		  size_t newsArrSize) {
int res = 0;

for (int i = 0; i < nodesArrSize && i < newsArrSize; i++) {
printf("%d", i);
TidyNode tmpNode[1];

printNode(tdoc, nodesArr[i], 150);
//setDate(tdoc, tmpNode[0], newsArr[i]);
//setUrl(tdoc, tmpNode[0], newsArr[i]);
//setTitle(tdoc, tmpNode[0], newsArr[i]);
//setBody(tdoc, tmpNode[0], newsArr[i]);


TidyBuffer buf;
      tidyBufInit(&buf);
      tidyNodeGetText(tdoc, tmpNode[0], &buf);
      printf("%s\n", buf.bp?(char *)buf.bp:"");
      tidyBufFree(&buf);
res++;
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
res = getNodeByName(body, "section", resNd, 1); 
res = getNodeById(resNd[0], "newswrap", resNd, 1); 
res = getNodeByClass(resNd[0], "content-wrap", resNd, 1);
res = getNodeByClass(resNd[0], "news-list div-with-shadow", resNd, 1);
res = getNodeByName(resNd[0], "ul", resNd, 1); 
res = getNodeByName(resNd[0], "li", resNd, 20); 
fillNewsStruct(tdoc, resNd, res, out, out_sz);
}

tidyBufFree(docbuf);
tidyRelease(tdoc);
return res;
}



int main(int argc, char **argv)
{
if (argc < 3) {
printf("%s\n", "usage: ./parse token chat_id db_path");
exit(1);
}

TidyBuffer docbuf = {0};
//tidyOptSetBool(tdoc, TidyForceOutput, yes);
//tidyOptSetInt(tdoc, TidyWrapLen, 4096);
tidyBufInit(&docbuf);
int err = getHtml("https://fdsarr.ru/arr/news/", &docbuf);
if (err) {
printf("get%d\n", err);
exit(2);
}

sqlite3 *db;
char *err_msg = 0; 
int rc = sqlite3_open_v2(argv[3], &db, SQLITE_OPEN_READWRITE,NULL);
size_t newsSize = 20;
struct NewsBlock news[newsSize];
initNewsBlocks(news, newsSize);


int parsed = parseHtml(&docbuf, news, newsSize);
printf("parsed %d news\n", parsed);
/*for (int i = 0; i < parsed; i++){
	insertNewsBlock(db, news[i]);
}

int selected = selectUnsentNewsBlocksFromDb(db,news, newsSize);
if (selected > 0){
CURL *curl;
curl = curl_easy_init();
char url[200] = "https://api.telegram.org/bot";
strcat(url, argv[1]);
strcat(url, "/sendMessage");

printf("%s\n", url);

for (int i=0; i < selected; i++) {
setProcessing(db, news[i], 1);
sendNewsBlock(curl, url, argv[2], news[i],db);
setSent(db, news[i], 1);
setProcessing(db, news[i], 0);
}
curl_easy_cleanup(curl);
}

freeNewsBlocks(news, newsSize);

sqlite3_close(db);
return err;
*/
}

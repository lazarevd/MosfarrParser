#include <stdio.h>
#include <curl/curl.h>
#include <tidy.h>
#include <tidybuffio.h>
#include "newsblock.h"
#include <sqlite3.h>
#include "sql.h"
#include "sender.h"
#include "utils.h"

size_t write_cb(char *in, size_t size, size_t nmemb, TidyBuffer *userdata) {
uint r;
  r = size * nmemb;
  tidyBufAppend(userdata, in, r);
return r;
}

int hash(char * input) {
int res = 0;
int i = 0;
while(input[i] != '\0') {
res = 31 * res + input[i];
i++;
}
return res;
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



int getNodeByAttribute(TidyNode parentNode, ctmbstr findName, ctmbstr findAttName, 
		TidyNode * resultArr, int resultInitSize) {
  TidyNode child;
  int resultSize = 0;
  for(child = tidyGetChild(parentNode); child; child = tidyGetNext(child) ) {
    ctmbstr name = tidyNodeGetName(child);
    if (name) {
      TidyAttr attr;
      for(attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr) ) {
	ctmbstr attName = tidyAttrName(attr);      
	ctmbstr attVal = tidyAttrValue(attr);      
        if (strcmp(findAttName, attName) == 0 
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




int getNodeByClass(TidyNode parentNode, ctmbstr findName, TidyNode * resultArr, int resultInitSize) {
return getNodeByAttribute(parentNode, findName, "class", resultArr, resultInitSize);
}


int getNodeById(TidyNode parentNode, ctmbstr findName, TidyNode * resultArr, int resultInitSize) {
return getNodeByAttribute(parentNode, findName, "id", resultArr, resultInitSize);
}

int getNodeByName(TidyNode parentNode, ctmbstr findName, TidyNode * resultArr,int resultInitSize) {
  TidyNode child; 
  int resultSize = 0;
  for(child = tidyGetChild(parentNode); child; child = tidyGetNext(child) ) {
    ctmbstr name = tidyNodeGetName(child);
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
      char* text = buf.bp?(char *)buf.bp:"";
      strcpy(textDest, text);
      tidyBufFree(&buf);
      //return res;
}

void getAttrVal(TidyNode tNode, char* findAttrName, char* resultValue) {
	TidyAttr attr;
      for(attr = tidyAttrFirst(tNode); attr; attr = tidyAttrNext(attr) ) {
	ctmbstr attName = tidyAttrName(attr);      
	ctmbstr attVal = tidyAttrValue(attr);      
        	if (strcmp(findAttrName, attName) == 0) {
        	strlcpy(resultValue, attVal, 1000);
		}
	}
} 

#include <stdio.h>
#include <curl/curl.h>
#include <tidy.h>
#include <tidybuffio.h>
/*
TidyNode is a pointer by itself. But here we use arrays of them
TidyNode * nodes



*/


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
  TidyNode child;
  int i = 0;
  for(child = tidyGetChild(tnod); child; child = tidyGetNext(child) ) {
    ctmbstr name = tidyNodeGetName(child);
    if(name) {
	printf("node name: %s\n", name);
      TidyAttr attr;
      for(attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr) ) {
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
      tidyNodeGetText(tdoc, child, &buf);
      printf("TEXT: %s\n", buf.bp?(char *)buf.bp:"");
      tidyBufFree(&buf);
    }
i++;
  }
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
resultArr[resultSize] = child;
resultSize++;
   }
}
return resultSize;
}

struct NewsBlock {
    int id;
    char date[16];
    char title[200];
    char url[300];
    char body[300];
};


int fillNewsStruct(TidyDoc tdoc,
		  TidyNode * nodesArr, 
		  size_t nodesArrSize, 
		  struct NewsBlock * newsArr,
		  size_t newsArrSize) {
int res = 0;

for (int i = 0; i < nodesArrSize && i < newsArrSize; i++) {

TidyNode tmpNode[1];
getNodeByClass(nodesArr[i], "item-block item-news", tmpNode, 1);
getNodeByClass(tmpNode[0], "date", tmpNode, 1);

//printNode(tdoc, tmpNode[0]);
TidyNode child; 
 for(child = tidyGetChild(tmpNode[0]); child; child = tidyGetNext(child) )  { 

      TidyBuffer buf;
      tidyBufInit(&buf);
      tidyNodeGetText(tdoc, child, &buf);
      printf("%s%s\n", "TEXT", (char*)buf.bp);
      tidyBufFree(&buf);
}

/*

*/
/*
printf("%s%s\n","RESULT:" ,  tidyNodeGetName(nodesArr[i]));
      TidyBuffer buf;
      tidyBufInit(&buf);
      tidyNodeGetText(tdoc, nodesArr[i], &buf);
      printf("%s%s\n", "TEXT", (char*)buf.bp);
      tidyBufFree(&buf);
*/
}
return res;
}
int parseHtml(char * html, struct NewsBlock * out, size_t out_sz) {
int res = -1;
TidyDoc tdoc; 
int err;
tdoc = tidyCreate();
tidyOptSetBool(tdoc, TidyForceOutput, yes);
tidyOptSetInt(tdoc, TidyWrapLen, 4096);



if (html)
{
// printf("%s\n", buffer ); 
tidyParseString(tdoc, html);
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

tidyRelease(tdoc);
return res;
}




int main(int argc, char **argv)
{

TidyDoc tdoc; 
int err;
tdoc = tidyCreate();
tidyOptSetBool(tdoc, TidyForceOutput, yes);
tidyOptSetInt(tdoc, TidyWrapLen, 4096);




char * buffer = 0;
long length;
//FILE * f = fopen ("simple.html", "rb");
FILE * f = fopen ("dumped.html", "rb");
if (f)
{
  fseek (f, 0, SEEK_END);
  length = ftell (f);
  fseek (f, 0, SEEK_SET);
  buffer = malloc (length);
  if (buffer)
  {
    fread (buffer, 1, length, f);
  }
  fclose (f);
}

struct NewsBlock * news;

int r = 0;
parseHtml(buffer, news, 10);
printf("%d/n", r);
}





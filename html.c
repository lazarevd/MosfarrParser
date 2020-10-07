#include <stdio.h>
#include <curl/curl.h>
#include <tidy.h>
#include <tidybuffio.h>



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
     // printf(">\n");
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
    dumpNode(doc, child, indent + 1); /* recursive */ 
  }
}





int getNodeByName(TidyNode parentNode, ctmbstr findName, TidyNode * resultNode,int resultInitSize) {
  TidyNode child;
  int resultSize = 0;
  for(child = tidyGetChild(parentNode); child; child = tidyGetNext(child) ) {
    ctmbstr name = tidyNodeGetName(child);
//    printf("%s\n", name);
    if(name && strcmp(name, findName) == 0 
	&& resultSize < resultInitSize)  {
resultNode[resultSize] = child;
resultSize++;
   }
}
return resultSize;
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

if (buffer)
{
// printf("%s\n", buffer ); 
tidyParseString(tdoc, buffer);
TidyNode body = tidyGetBody(tdoc);
int res = -1;

int initSize = 10;
TidyNode resNd[initSize];
res = getNodeByName(body, "main", resNd, initSize); 
res = getNodeByName(resNd[0], "div", resNd, initSize); 
res = getNodeByName(resNd[0], "div", resNd, initSize); 
res = getNodeByName(resNd[0], "div", resNd, initSize); 
res = getNodeByName(resNd[0], "div", resNd, initSize); 
// start to process your data / extract strings here...
//printHtNodes(tdoc, root);

printf("%s%s\n","RESULT:" ,  tidyNodeGetName(resNd[0]));
      TidyBuffer buf;
      tidyBufInit(&buf);
      tidyNodeGetText(tdoc, resNd[0], &buf);
      printf("%s%s\n", "TEXT", (char*)buf.bp);
      tidyBufFree(&buf);

//dumpNode(tdoc, resNd, 0);
}

tidyRelease(tdoc);

}





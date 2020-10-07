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
      /* if it has a name, then it's an HTML tag ... */ 
      TidyAttr attr;
      printf("%*.*s%s ", indent, indent, "<", name);
      /* walk the attribute list */ 
      for(attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr) ) {
        printf("%s\n", tidyAttrName(attr));
        tidyAttrValue(attr)?printf("=\"%s\" ",
                                   tidyAttrValue(attr)):printf(" ");
      }
      printf(">\n");
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





int getNodeByName(TidyNode parentNode, ctmbstr findName, TidyNode * resultNode) {
  TidyNode child;
  for(child = tidyGetChild(parentNode); child; child = tidyGetNext(child) ) {
    ctmbstr name = tidyNodeGetName(child);
   // printf("%s\n", name);
    if(strcmp(name, findName) == 0)  {
*resultNode = child;
return 0;
   }
}
return 1;
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

TidyNode resNd;
res = getNodeByName(body, "main", &resNd); 
res = getNodeByName(resNd, "div", &resNd); 
//res = getNodeByName(resNd, "th", &resNd); 
// start to process your data / extract strings here...
//printHtNodes(tdoc, root);
printf("%s%s\n","RESULT:" ,  tidyNodeGetName(resNd));
      TidyBuffer buf;
      tidyBufInit(&buf);
      tidyNodeGetText(tdoc, resNd, &buf);
      printf("%s%s\n", "TEXT", (char*)buf.bp);
      tidyBufFree(&buf);
//dumpNode(tdoc, body, 0);
}

tidyRelease(tdoc);

}





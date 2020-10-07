#include <stdio.h>
#include <curl/curl.h>
#include <tidy.h>
#include <tidybuffio.h>

size_t write_cb(char *in, size_t size, size_t nmemb, TidyBuffer *userdata) {
uint r;
  r = size * nmemb;
  tidyBufAppend(userdata, in, r);
//  printf("write %s\n", in);  
return r;
}

/* Traverse the document tree */ 
void dumpNode(TidyDoc doc, TidyNode tnod, int indent)
{
  TidyNode child;
  for(child = tidyGetChild(tnod); child; child = tidyGetNext(child) ) {
    ctmbstr name = tidyNodeGetName(child);
    if(name) {
      /* if it has a name, then it's an HTML tag ... */ 
      TidyAttr attr;
      printf("%*.*s%s ", indent, indent, "<", name);
      /* walk the attribute list */ 
      for(attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr) ) {
        printf(tidyAttrName(attr));
        tidyAttrValue(attr)?printf("=\"%s\" ",
                                   tidyAttrValue(attr)):printf(" ");
      }
      printf(">\n");
    }
    else {
      /* if it doesn't have a name, then it's probably text, cdata, etc... */ 
      TidyBuffer buf;
      tidyBufInit(&buf);
      tidyNodeGetText(doc, child, &buf);
      printf("%*.*s\n", indent, indent, buf.bp?(char *)buf.bp:"");
      tidyBufFree(&buf);
    }
    dumpNode(doc, child, indent + 4); /* recursive */ 
  }
}

void dumpMosfarr(TidyDoc doc, TidyNode tnod, int indent)
{
  TidyNode child;

    ctmbstr name = tidyNodeGetName(tnod);

    
      TidyBuffer buf;
      tidyBufInit(&buf);
      tidyNodeGetText(doc, tnod, &buf);
      printf("%s\n", buf.bp);
      tidyBufFree(&buf);
  
   if(name == "body") {
child = tidyGetBody(tnod);


    name = tidyNodeGetName(child);

    printf("%s%s\n", " child ", name);
}

for(child = tidyGetChild(tnod); child; child = tidyGetNext(child) ) {
    name = tidyNodeGetName(child);
//    printf("farr %s\n", name);
    if(name) {
      /* if it has a name, then it's an HTML tag ... */ 
      printf("FARR %s%d\n", name, indent);
    		}
	dumpMosfarr(doc, child, indent++);
}
}
int main(int argc, char **argv)
{
printf("%s\n", "main");
CURL *curl;
TidyDoc tdoc; 
TidyBuffer docbuf = {0};
TidyBuffer tidy_errbuf = {0};
int err;
curl = curl_easy_init();
curl_easy_setopt(curl, CURLOPT_URL, "https://mosfarr.ru/category/новости");
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
tdoc = tidyCreate();
tidyOptSetBool(tdoc, TidyForceOutput, yes);
tidyOptSetInt(tdoc, TidyWrapLen, 4096);
tidyBufInit(&docbuf);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, &docbuf);

err = curl_easy_perform(curl);

printf("curl %s%d\n", curl_easy_strerror(err), err);
//printf("%d\n", err);

 if(!err) {
      err = tidyParseBuffer(tdoc, &docbuf); /* parse the input */
	printf("%d\n", err);
      if(err >= 0) {
        err = tidyCleanAndRepair(tdoc); /* fix any problems */ 
        if(err >= 0) {
          err = tidyRunDiagnostics(tdoc); /* load tidy error buffer */ 
          if(err >= 0) {
		TidyNode root = tidyGetRoot(tdoc);
           //dumpMosfarr(tdoc, root, 0); /* walk the tree */ 
           dumpNode(tdoc, root, 0); /* walk the tree */ 
            printf(stderr, "tidy %s\n", tidy_errbuf.bp); /* show errors */ 
          }
        }
      }
    }
    else
      
	printf("curl %s%d\n", curl_easy_strerror(err), err);
 
    /* clean-up */ 
    curl_easy_cleanup(curl);
  //  tidyBufFree(&docbuf);
    //tidyBufFree(&tidy_errbuf);
  //  tidyRelease(tdoc);
    return err;

}

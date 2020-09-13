#include <stdio.h>
#include <curl/curl.h>
#include <tidy.h>
#include <tidybuffio.h>

size_t write_cb(char *parseres, size_t size, size_t nmemb, TidyBuffer *userdata) {
uint r;
  r = size * nmemb;
  tidyBufAppend(userdata, parseres, r);
  return r;
return size*nmemb;
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


int main(int argc, char **argv)
{
printf("%s\n", "main");
CURL *curl;
int err;
curl = curl_easy_init();
curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
err = curl_easy_perform(curl);
printf("%s\n", curl_easy_strerror(err));
TidyDoc tdoc = tidyCreate();
TidyBuffer docbuf = {0};
tidyOptSetBool(tdoc, TidyForceOutput, yes);
tidyOptSetInt(tdoc, TidyWrapLen, 4096);
tidyBufInit(&docbuf);

 if(!err) {
      err = tidyParseBuffer(tdoc, &docbuf); /* parse the input */ 
      if(err >= 0) {
        err = tidyCleanAndRepair(tdoc); /* fix any problems */ 
        if(err >= 0) {
          err = tidyRunDiagnostics(tdoc); /* load tidy error buffer */ 
          if(err >= 0) {
            dumpNode(tdoc, tidyGetRoot(tdoc), 0); /* walk the tree */ 
            //fprintf(stderr, "%s\n", tidy_errbuf.bp); /* show errors */ 
          }
        }
      }
    }
   // else
   //   fprintf(stderr, "%s\n", curl_errbuf);
 
    /* clean-up */ 
    curl_easy_cleanup(curl);
    tidyBufFree(&docbuf);
    //tidyBufFree(&tidy_errbuf);
    tidyRelease(tdoc);
    return err;

}

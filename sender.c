#include <stdio.h>
#include <curl/curl.h>
#include "newsblock.h"


int sendNewsBlock(CURL * curl,
char * url,		 
struct NewsBlock * nb) {

int res = 0;
struct curl_slist *list = NULL;
list = curl_slist_append(list, "Content-Type: application/json");
curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
curl_easy_setopt(curl, CURLOPT_URL, url);
curl_easy_setopt(curl, CURLOPT_POST, 1L);
curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"chat_id\:w",\"text\":\"0_o\", \"parse_mode\":\"HTML\"}");
/*
strcat(query, ", \"");
strncat(query, nb.date, 12);
*/
res = curl_easy_perform(curl);
return res;
}

int main(int argc, char **argv){

CURL *curl;

curl = curl_easy_init();
struct NewsBlock * nbk;
initNewsBlock(&nbk);
int rs;
rs = sendNewsBlock(curl,
"https://api.telegram.org/bot:A/sendMessage",
nbk);
printf("%s%d", "res ", rs);
freeNewsBlock(nbk);

curl_easy_cleanup(curl);

}

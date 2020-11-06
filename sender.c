#include <stdio.h>
#include <curl/curl.h>
#include "newsblock.h"
#include <string.h>
#include "sql.h"

int sendNewsBlock(CURL * curl,
char * url,
char * chatId,		 
struct NewsBlock nb,
sqlite3 * db) {
setProcessing(db, nb, 1);
int res = 0;
struct curl_slist *list = NULL;
list = curl_slist_append(list, "Content-Type: application/json");
curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
curl_easy_setopt(curl, CURLOPT_URL, url);
curl_easy_setopt(curl, CURLOPT_POST, 1L);
char body[2000] = "{\"chat_id\":\""; 
strcat(body, chatId);
strcat(body, "\",\"text\":\"0_o\", \"parse_mode\":\"HTML\"}");
curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
res = curl_easy_perform(curl);
if (res == 0) {
setSent(db, nb, 1);
}
setProcessing(db, nb, 0);
return res;
}
/*
int main(int argc, char **argv){
CURL *curl;
curl = curl_easy_init();
struct NewsBlock * nbk;
initNewsBlock(&nbk);
int rs;
char url[200] = "https://api.telegram.org/bot";
strcat(url, argv[1]);
strcat(url, "/sendMessage");

printf("%s\n", url);
rs = sendNewsBlock(curl,url,argv[2],nbk);
printf("\n%s%d", "res ", rs);
freeNewsBlock(nbk);

curl_easy_cleanup(curl);

}*/

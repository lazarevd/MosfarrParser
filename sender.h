#include <stdio.h>
#include <curl/curl.h>
#include "newsblock.h"
#include <string.h>
#include "sql.h"

int sendNewsBlock(CURL * curl,
char * url,
char * chatId,		 
struct NewsBlock nb,
sqlite3 * db);

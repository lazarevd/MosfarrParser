#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include "newsblock.h"

int openDb(sqlite3 ** db, char* db_path) {
return sqlite3_open_v2(db_path, db, SQLITE_OPEN_READWRITE , NULL);
}

int selectUnsentNewsBlocksFromDb(char * db_path, 
			    struct NewsBlock * nbs,
			    size_t arrSz) {
char *sql = 	"SELECT * FROM news_blocks "
		"WHERE processing = 0 "
		"AND sent = 0";


sqlite3 *db = NULL;
int rc = openDb(&db, db_path);
sqlite3_stmt *stmt;

rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
if (rc != SQLITE_OK) {
    printf("%s%s\n", "error: ", sqlite3_errmsg(db));
}

int cnt = 0;
while ((rc = sqlite3_step(stmt)) == SQLITE_ROW && cnt < arrSz) {
    int id           = sqlite3_column_int (stmt, 0);
    *nbs[cnt].id = id;
    const char *date = sqlite3_column_text(stmt, 1);
    strcpy(nbs[cnt].date, date);
    const char *title = sqlite3_column_text(stmt, 2);
    strcpy(nbs[cnt].title, title);
    const char *url = sqlite3_column_text(stmt, 3);
    strcpy(nbs[cnt].url, url);   
    //printf("%d=%s\n", id, name); 
    cnt++;
}
sqlite3_finalize(stmt);
sqlite3_close(db);
return cnt;
}

int executeQuery(char * db_path, char * query) {
sqlite3 *db = NULL;
int rc = openDb(&db, db_path);
char *err_msg = 0;
rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
       // sqlite3_free(err_msg);        
       // sqlite3_close(db);
        
        return 1;
    } 

printf("%s\n", query);
sqlite3_close(db);
return rc;
}

int setProcessing(char * db_path, struct NewsBlock nb, int val) {

char query[200] = "update news_blocks set processing =  ";
char i[100];
sprintf(i, "%d", val);
strcat(query, &i[0]);
strcat(query, " where id = ");
sprintf(i, "%d", *nb.id);
strcat(query, &i[0]);
return executeQuery(db_path, &query[0]);
}


int setSent(char * db_path, struct NewsBlock nb, int val) {
char query[200] = "update news_blocks set sent = ";
char i[100];
sprintf(i, "%d", val);
strcat(query, &i[0]);
strcat(query, " where id = ");
sprintf(i, "%d", *nb.id);
strcat(query, &i[0]);
return executeQuery(db_path, &query[0]);
}

char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos){
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

int insertNewsBlock(char * db_path, struct NewsBlock nb) {

char query[4000] = "insert or ignore into news_blocks values(";

char  i[100] = {0};
sprintf(i, "%d", *nb.id);
strncat(query, &i[0],20);
strcat(query, ", \"");
strncat(query, nb.date, 12);
strcat(query, "\", \"");
replace_char(nb.title, '\"', '\'');
strncat(query, nb.title, 500);
strcat(query, "\", \"");
strncat(query, nb.url, 700);
strcat(query, "\", \"");
strncat(query, nb.body, 700);
strcat(query, "\", 0, 0)");


return executeQuery(db_path, &query[0]);
}


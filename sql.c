#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include "newsblock.h"
int callback(void *, int, char **, char **);

int main(void) {

sqlite3 *db;
sqlite3_stmt *stmt;
char *err_msg = 0; 

int rc = sqlite3_open_v2("rr.db", &db, SQLITE_OPEN_READWRITE,NULL);
printf("%s\n", sqlite3_libversion());
printf("%d\n", rc);

char *sql = "SELECT * FROM news_blocks";

size_t arrSz = 20;


struct NewsBlock * nbs = malloc(sizeof(struct NewsBlock) * arrSz);
initNewsBlocks(nbs, arrSz);



rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
if (rc != SQLITE_OK) {
    printf("%s%s\n", "error: ", sqlite3_errmsg(db));
    return 0;
}

int cnt = 0;

while ((rc = sqlite3_step(stmt)) == SQLITE_ROW && cnt < arrSz) {
    int id           = sqlite3_column_int (stmt, 0);
    const char *name = sqlite3_column_text(stmt, 1);
    strcpy(nbs[cnt].date, name);
    printf("%d=%s\n", id, name); 
    cnt++;
}
if (rc != SQLITE_DONE) {
    printf("%s%s\n","error: ", sqlite3_errmsg(db));
}
sqlite3_finalize(stmt);

printf("%s=%s\n", "nbs res",nbs[0].date);

free(nbs);
return 0;
}



int callback(void *newsBlk, int args, char **argv, char **azColName) {

printf("%s\n", argv[0]);
for(int i; i<args; i++) {
printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
}
printf("\n");
return 0;

}

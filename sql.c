#include <stdio.h>
#include <sqlite3.h>
#include <newsblock.h>
int callback(void *, int, char **, char **);

int main(void) {

sqlite3 *db;
sqlite3_stmt *res;
char *err_msg = 0; 

int rc = sqlite3_open_v2("rr.db", &db, SQLITE_OPEN_READWRITE,NULL);
printf("%s\n", sqlite3_libversion());
printf("%d\n", rc);

char *sql = "SELECT * FROM news_blocks";

rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

printf("%s\n","x");

return 0;
}



int callback(void *NotUsed, int args, char **argv, char **azColName) {

for(int i=0; i<args; i++) {
printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
}

return 0;

}

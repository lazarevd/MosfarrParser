rm parse
gcc -g -o parse  newsblock.h sql.h parse.c sql.c newsblock.c -L~/sqlite/sqlite -ltidy -lcurl -lsqlite3
./parse

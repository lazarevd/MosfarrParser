rm parse
gcc -g -o parse  newsblock.h sql.h sender.h parse.c sql.c newsblock.c sender.c -L~/sqlite/sqlite -ltidy -lcurl -lsqlite3
./parse

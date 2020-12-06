rm mosfarrParser
#for DO
#gcc -g -o mosfarrParser mosfarrParser.c  newsblock.h -I/usr/include/tidy sql.h sender.h parse.c parse.h sql.c newsblock.c sender.c -L~/sqlite/sqlite -ltidy -lcurl -lsqlite3
gcc -g -o mosfarrParser mosfarrParser.c  newsblock.h sql.h sender.h parse.c parse.h sql.c newsblock.c sender.c -L~/sqlite/sqlite -ltidy -lcurl -lsqlite3
./mosfarrParser

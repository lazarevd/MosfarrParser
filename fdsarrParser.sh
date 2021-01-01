rm fdsarrParser
#for DO
gcc -g -o fdsarrParser fdsarrParser.c utils.h utils.c newsblock.h -I/usr/include/tidy sql.h sender.h parse.c parse.h sql.c newsblock.c sender.c -L~/sqlite/sqlite -ltidy -lcurl -lsqlite3
#gcc -g -o fdsarrParser fdsarrParser.c utils.h  utils.c newsblock.h sql.h sender.h parse.c parse.h sql.c newsblock.c sender.c -L~/sqlite/sqlite -ltidy -lcurl -lsqlite3
./fdsarrParser

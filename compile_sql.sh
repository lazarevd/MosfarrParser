rm sql
gcc -o sql -I~/sqlite/sqlite -L~/sqlite/sqlite  -I/home/ubuntu/bot  newsblock.h sql.c -lsqlite3
./sql

rm sql
gcc -o sql -I~/sqlite/sqlite -L~/sqlite/sqlite  -I/home/ubuntu/bot  sql.c newsblock.c -lsqlite3
./sql

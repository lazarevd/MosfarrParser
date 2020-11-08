#include <stdio.h>
#include <sqlite3.h>
#include "newsblock.h"


int selectUnsentNewsBlocksFromDb(sqlite3 * db, 
			    struct NewsBlock * nbs,
			    size_t arrSz);

int insertNewsBlock(sqlite3 * db, struct NewsBlock  nb);

int setProcessing(sqlite3 * db, struct NewsBlock nb, int val);

int setSent(sqlite3 * db, struct NewsBlock nb, int val);

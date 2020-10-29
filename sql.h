#include <stdio.h>
#include <sqlite3.h>
#include "newsblock.h"

void selectNewsBlocksFromDb(sqlite3 * db, 
			    struct NewsBlock * nbs,
			    size_t arrSz);


int insertNewsBlock(sqlite3 * db, struct NewsBlock  nb);

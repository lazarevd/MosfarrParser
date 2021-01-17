#include <stdio.h>
#include <sqlite3.h>
#include "newsblock.h"


int selectUnsentNewsBlocksFromDb(char * db_path, 
			    struct NewsBlock * nbs,
			    size_t arrSz);

int insertNewsBlock(char * db_path, struct NewsBlock  nb);

int setProcessing(char * db_path, struct NewsBlock nb, int val);

int setSent(char * db_path, struct NewsBlock nb, int val);

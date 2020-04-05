#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "util.h"
#include "hashtable.h"

/* EXTERNALS */
extern int yylex(void);
extern FILE *yyin;

/* GLOBALS */
hashtable_t ht;
SAME_BOOL_T file_scanned = S_FALSE;

/* FUNCTIONS */
int main(int argc, char **argv){
	if(argc < 3){
		printf("Usage: %s <source file> <destination file(s)>\n", argv[0]);
		exit(1);
	}

	if(init_hashtable(&ht, 97) == FAILED){
		printf("Couldn't initialize hashtable\n");
		exit(1);
	}

	/* yyin is the file descriptor from which flex reads */
	yyin = fopen(argv[1], "r");
	if(NULL == yyin){
		printf("Couldn't open file %s\n", argv[1]);
		exit(1);
	}

	yylex();

	fclose(yyin);

	file_scanned = S_TRUE;

	/* Search for matches in the other files */
	for(int i = 2; i < argc; ++i){
		yyin = fopen(argv[i], "r");
		if(NULL == yyin){
			printf("Couldn't open file %s\n", argv[i]);
			exit(1);
		}

		printf("Matches in file %s:\n", argv[i]);
		yylex();

		fclose(yyin);
	}

	free_HT(ht);

	return 0;
}
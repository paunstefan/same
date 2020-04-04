#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "util.h"

/* EXTERNALS */
extern int yylex(void);
extern FILE *yyin;

/* GLOBALS */
char **words = NULL;
uint32_t wordc = 0;
SAME_BOOL_T file_scanned = S_FALSE;

/* FUNCTIONS */

int main(int argc, char **argv){
	if(argc < 3){
		printf("Usage: %s [source file] [destination file(s)]\n", argv[0]);
		exit(1);
	}

	/* yyin is the file descriptor from which flex reads */
	yyin = fopen(argv[1], "r+");
	if(NULL == yyin){
		printf("Couldn't open file %s\n", argv[1]);
		exit(1);
	}

	printf("Parsing source file %s\n\n", argv[1]);
	yylex();

	fclose(yyin);

	file_scanned = S_TRUE;

	for(int i = 2; i < argc; ++i){
		yyin = fopen(argv[i], "r+");
		if(NULL == yyin){
			printf("Couldn't open file %s\n", argv[i]);
			exit(1);
		}

		printf("Matches in file %s:\n", argv[i]);
		yylex();

		fclose(yyin);
	}

	for(int i = 0; i < wordc; ++i){
		free(words[i]);
	}
	free(words);

	return 0;
}
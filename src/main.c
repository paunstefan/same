#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "util.h"

/* EXTERNALS */
extern int yyparse();
extern FILE *yyin;

/* GLOBALS */
char **words = NULL;
uint32_t wordc = 0;

/* FUNCTIONS */

int main(int argc, char **argv){
	if(2 != argc){
		printf("Usage: %s [file]\n", argv[0]);
		exit(1);
	}

	yyin = fopen(argv[1], "r+");
	if(NULL == yyin){
		printf("Couldn't open file\n");
		exit(1);
	}

	yyparse();

	fclose(yyin);


	for(int i = 0; i < wordc; ++i){
		printf("%s\n", words[i]);
	}

	for(int i = 0; i < wordc; ++i){
		free(words[i]);
	}
	free(words);

	return 0;
}
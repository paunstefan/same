#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/* EXTERNALS */
extern char **words;
extern uint32_t wordc;

/* FUNCTIONS */
void add_word(char *word){
	words = (char**)realloc(words, wordc+1);
	if(NULL == words){
		printf("Couldn't realloc\n");
		exit(1);
	}
	words[wordc] = strdup(word);
	if(NULL == words[wordc]){
		printf("strdup failed\n");
		exit(1);
	}
	++wordc;
}
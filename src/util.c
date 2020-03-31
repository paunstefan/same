#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/* EXTERNALS */
extern char **words;
extern uint32_t wordc;
extern SAME_BOOL_T file_scanned;

/* FUNCTIONS */
void process_word(char *word){
	if(S_FALSE == file_scanned)
	{
		if(add_word(word) != SUCCESS){
			exit(1);
		}
	}
	else
	{
		if(check_exist(word) != SUCCESS){
			exit(1);
		}
	}
}

SAME_RC_T add_word(char *word){
	DBG(word);
	words = (char**)realloc(words, sizeof(char*)*(wordc+1));
	if(NULL == words){
		printf("Couldn't realloc\n");
		return FAILED;
	}

	words[wordc] = strdup(word);
	if(NULL == words[wordc]){
		printf("strdup failed\n");
		for(int i = 0; i < wordc; ++i){
			free(words[i]);
		}
		free(words);

		return FAILED;
	}
	++wordc;

	return SUCCESS;
}

SAME_RC_T check_exist(char *word){
	/* TODO: implement more efficient searching */
	for(int i = 0; i < wordc; ++i){
		if(strcmp(words[i], word) == 0)
		{
			printf("%s\n", word);
		}
	}

	DBG(word);

	return SUCCESS;
}

void DBG(char *str){
#ifdef S_DEBUG
	printf("DBG: %s\n", str);
#endif
}
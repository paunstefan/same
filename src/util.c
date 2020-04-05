#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "hashtable.h"

/* EXTERNALS */
extern hashtable_t ht;
extern SAME_BOOL_T file_scanned;

/* FUNCTIONS */
void process_word(char *word){
	if(S_FALSE == file_scanned)
	{
		if(add_word(word) != SUCCESS){
			free_HT(ht);
			exit(1);
		}
	}
	else
	{
		if(check_exist(word) != SUCCESS){
			free_HT(ht);
			exit(1);
		}
	}
}

SAME_RC_T add_word(char *word){
	DBG(word);

	return insert_HT(ht, word);
}

SAME_RC_T check_exist(char *word){
	DBG(word);

	if(is_HTitem(ht, word) == S_TRUE){
		printf("%s\n", word);
	}

	return SUCCESS;
}

void DBG(char *str){
#ifdef S_DEBUG
	printf("DBG: %s\n", str);
#endif
}
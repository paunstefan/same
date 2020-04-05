#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "util.h"


/**
	Creates the HashTable structure.

	@param ht: the hastable pointer
	@param dim: the wanted dimension
*/
SAME_RC_T init_hashtable(hashtable_t *ht, size_t dim){
	ht->size = dim;
	ht->buckets = (list_node_t**)malloc(sizeof(list_node_t*) * dim);
	if(NULL == ht->buckets){
		return FAILED;
	}
	memset(ht->buckets, 0, dim * sizeof(list_node_t*));

	return SUCCESS;
}

/**
	djb2 hashing algorithm

	@param key: the identifier
	@param size: size of the table
	@return the hash
*/
uint32_t hash(char* key, size_t size){
	uint32_t hash = 5381;
	uint32_t c;

	while((c = *key)){
		hash = ((hash << 5) + hash) + c;
		++key;
	}

	return hash % size;
}


/**
	Creates a list node.

	@param name: the identifier
	@return the ListNode structure
*/
list_node_t* create_node(char* name){
	char *info = strdup(name);
	if(NULL == info){
		return NULL;
	}

	list_node_t *node = (list_node_t*)malloc(sizeof(list_node_t));
	if(NULL == node){
		return NULL;
	}

	node->info = info;
	node->next = NULL;
	return node;
}


/**
	Inserts a new node into the list.

	@param list: pointer to the list
	@param name: the identifier
	@param addr: the label address
	@return the new pointer to the list
*/
SAME_RC_T insert_node(list_node_t **list, char *name){
	list_node_t *node = create_node(name);
	if(NULL == node){
		return FAILED;
	}

	if(*list){
		node->next = *list;
	}
	*list = node;

	return SUCCESS;
}


/**
	Inserts a new element into the HashTable struct. 
	It uses chaining for collision avoidance (using a circular linked list).

	@param ht: the hashtable structure
	@param name: the identifier
	@param addr: the label address
*/
SAME_RC_T insert_HT(hashtable_t ht, char* name){
	if(S_FALSE == is_HTitem(ht, name)){
		uint32_t position = hash(name, ht.size);
		list_node_t *list = ht.buckets[position];

		if(insert_node(&list, name) != SUCCESS){
			return FAILED;
		}

		ht.buckets[position] = list; 
	}

	return SUCCESS;
}

/**
	Checks if an item is present in the table.

	@param ht: the hashtable structure
	@param name: the identifier
	@return true if it is present, else false
*/
SAME_BOOL_T is_HTitem(hashtable_t ht, char* name){
	uint32_t position = hash(name, ht.size);
	list_node_t *list = ht.buckets[position];

	if(!list){
		return S_FALSE;
	}
	else{
		while(list != NULL){
			if(strcmp(list->info, name) == 0){
				return S_TRUE;
			}
			list = list->next;
		}

	}
	return S_FALSE;
}

/*
	Frees linked list.
*/
void free_list(list_node_t *ls){
	list_node_t *temp;

	while(ls != NULL){
		temp = ls;
		free(ls->info);
		ls = ls->next;
		free(temp);
	}

}

/*
	Frees hashtable.
*/
void free_HT(hashtable_t ht){
	if(ht.size > 0){
		for(size_t i = 0; i < ht.size; i++){
			if(ht.buckets[i]){
				free_list(ht.buckets[i]);
			}
		}
		free(ht.buckets);
	}
}

#ifdef S_DEBUG
/*
	Prints all elements in a list.
*/
void print_list(list_node_t *ls){
	while(ls != NULL){
		printf("%s\n", ls->info);
		ls = ls->next;
	}
}


/*
	Prints all elements in a table.
*/
void print_HT(hashtable_t ht){
	printf("\nPrinting hashtable:\n");
	if(ht.size > 0){
		for(size_t i = 0; i < ht.size; i++){
			if(ht.buckets[i]){
				printf("Position: %d\n", (int)i);
				print_list(ht.buckets[i]);
				printf("\n");
			}
		}
	}
}
#endif
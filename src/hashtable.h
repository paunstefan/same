/*
	The header file for the hash table implementation.
*/

#include <stdint.h>
#include <stdlib.h>
#include "util.h"

#ifndef SAME_HT
#define SAME_HT

typedef struct list_node_t list_node_t;
typedef struct hashtable_t hashtable_t;

struct list_node_t{
	char *info;
	list_node_t *next;
};

 struct hashtable_t{
	list_node_t **buckets;
	size_t size;
};

/**
	Creates the HashTable structure.

	@param ht: the hastable pointer
	@param dim: the wanted dimension
*/
SAME_RC_T init_hashtable(hashtable_t* ht, size_t dim);

/**
	djb2 hashing algorithm

	@param key: the identifier
	@param size: size of the table
	@return the hash
*/
uint32_t hash(char* key, size_t size);

/**
	Creates a list node.

	@param name: the identifier
	@param addr: the label address
	@return the ListNode structure
*/
list_node_t* create_node(char* name);

/**
	Inserts a new node into the list.

	@param list: pointer to the list
	@param name: the identifier
	@return the new pointer to the list
*/
SAME_RC_T insert_node(list_node_t **list, char *name);



/**
	Inserts a new element into the HashTable struct. 
	It uses chaining for collision avoidance (using a circular linked list).

	@param ht: the hashtable structure
	@param name: the identifier
*/
SAME_RC_T insert_HT(hashtable_t ht, char* name);

/*
	Prints all elements in a list.
*/
void print_HT(hashtable_t ht);

/*
	Prints all elements in a list.
*/
void print_list(list_node_t *ls);

/**
	Checks if an item is present in the table.

	@param ht: the hashtable structure
	@param name: the identifier
	@return true if it is present, else false
*/
SAME_BOOL_T is_HTitem(hashtable_t ht, char* name);

void free_list(list_node_t *ls);
void free_HT(hashtable_t ht);

#endif
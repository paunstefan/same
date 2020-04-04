#ifndef SAME_UTIL
#define SAME_UTIL

/* DEFINES */
//#define S_DEBUG 1

/* TYPES */
typedef enum {
	S_TRUE,
	S_FALSE
}SAME_BOOL_T;

typedef enum{
	SUCCESS,
	FAILED
}SAME_RC_T;

/* FORWARD DECLARATIONS */
void process_word(char *word);
SAME_RC_T add_word(char *word);
SAME_RC_T check_exist(char *word);
void DBG(char *str);

#endif
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define BORDERS "------------------------------------------------------------------------------------"
#define MENU "[1. View List]   [2. View Cupboard]   [3. Add]   [4. Remove]   [5. Edit]   [9. Exit]"
#define MAINMENU_1 "\t\t\t    [10. Save File] \t [11. Load File]"
#define MAINMENU_2 "\t\t\t       What would you like to do?"
#define LISTINTERFACE "\tItem : Amount \t\t\t\t\tChecked Item : Amount"
#define MAX_NAME_LENGTH 24

#if defined(_WIN32) || defined(__CYGWIN__)
	#define OS "Windows x64"
	#define CLEAR "cls"
#elif defined(__linux__)
	#define OS "Linux"
	#define CLEAR "clear"
#endif

typedef struct Item {
	char name[MAX_NAME_LENGTH];
	bool checked;
	int amount;
} Item;


typedef enum {
	GOOD_FLAG,
	EMPTY_FLAG,
	BREAK_FLAG,
	UNUSED_FLAG,
	SAVE_FLAG,
	LOAD_FLAG,
	SORT_FLAG,
} FlagType;


typedef struct Buffer {
	char word[MAX_NAME_LENGTH];
	FlagType flag; 	
} Buffer;


typedef struct Array {
	Item *array;
	size_t used;
	size_t size;
} Array;


void insert(Array *List, char *name_buffer, char *amount);
void printlist(Array *List);
void remove_nl(char *a);
int getindex(Array *List, char *s);
void checkinput(Buffer *buff);
void remove_item(Array *List, int index);
void swap(Item *a, Item *b);
void sort(Array *List);





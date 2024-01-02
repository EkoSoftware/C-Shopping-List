#include "functions.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void printui() {
	system(CLEAR);
	puts(BORDERS);
	puts(MENU);
	puts(BORDERS);
}

void insert(Array *List, char *name_buffer, char *amount) {
	Item *current = &List->array[List->used];
	if (List->used == List->size) 
	{
		List->size *=2;
		List->array = (Item *)realloc(List->array, List->size * sizeof(Item));
		if (List->array == NULL) {
			printf("Memory Allocation Failed!\nShutting Down!");
			free(List->array);
			free(List);
			exit(EXIT_FAILURE);
		}
	}
	strcpy(current->name, name_buffer);
	current->amount = atoi(amount);
	current->checked = false;
	List->used += 1;
}

void printlist(Array *List) {
	for (size_t i = 0; i < List->used;i++) {
		Item *current = &List->array[i];
		if (current->checked)
			printf("%-50c [X]%-20s %4d\n",' ',current->name, current->amount);
		else
			printf("%-20s %4d\n",current->name, current->amount);
	}
	printf("%84s","<\"quit\" to Quit>\n");
}

void remove_nl(char *a) {
    int len = strlen(a);
    if (len > 0 && a[len - 1] == '\n') {
        a[len - 1] = '\0';
    }
}


int getindex(Array *List, char *s) {
	size_t i = 0;
	int index;
	for (;i < List->used;i++) {
		Item *current = &List->array[i];
		if (strcmp(current->name, s) == 0) {
			index = i;
			return index;
		}
	}
	return -1;
}

void checkinput(Buffer *buff) {
	if (buff->word[0] == '\n')
		buff->flag = EMPTY_FLAG;
	else if (strcmp(buff->word, "quit\n") == 0) 
		buff->flag = BREAK_FLAG;
	else if (strcmp(buff->word, "save\n") == 0) 
		buff->flag = SAVE_FLAG;	
	else if (strcmp(buff->word, "load\n") == 0)
		buff->flag = LOAD_FLAG;	
	else if (strcmp(buff->word, "sort\n") == 0)
		buff->flag = SORT_FLAG;
	else {
		buff->word[0] = toupper(buff->word[0]);
		remove_nl(buff->word);
		buff->flag = GOOD_FLAG;
	}
}



void remove_item(Array *List, int index) {
	__uint32_t i = index;
	for (; i < List->used;++i){
		List->array[i] = List->array[i + 1];
	}
	List->used -= (size_t)1;
}

void swap(Item *a, Item *b) {
	Item temp = *a;
	*a = *b;
	*b = temp;
}

void sort(Array *List) {
	int len = List->used;
	for (int i = 0; i < (len); i++)
		for (int j = 0; j < (len - 1); j++)
		{
			if (List->array[j].name[0] > List->array[j + 1].name[0])
				swap(&List->array[j], &List->array[j + 1]);
		}
}

#endif /* FUNCTIONS_H */
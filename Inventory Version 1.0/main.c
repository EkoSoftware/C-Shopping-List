#include "functions.h"
/*
	Todo:
	Add Price
	Add sort by value
	Add upload to cloud
	Add get prices from web
*/

int main(void) {
// Set System Language
	setlocale(LC_ALL, "");

// Initialize Input Buffers
	int index, option = 8;
	Buffer Buff;
	Buffer NameBuff;
	Buffer AmountBuff;
	char PAUSE[24];

// Initialize Array
	Array *List = malloc(sizeof(Array));
	List->size = 8;
	List->used = 0;
	List->array = malloc(sizeof(Item) * List->size);
	
// Fill Array
	char product_names[5][MAX_NAME_LENGTH] = {"Milk","Butter","Egg","Bacon","Oats"};
	char product_amounts[5][24] = {"2\0", "500", "30","7\0", "2\0"};
	for (int i = 0; i < 5;i++) {
		Item *current = &List->array[i];
		strcpy(current->name, product_names[i]);
		current->amount = atoi(product_amounts[i]);
		List->used++;
	}
// Main Loop
	while (option != 9) 
	{
		// Print UI
		printui();
		puts(MAINMENU_1);
		puts(MAINMENU_2);
		printf("\t\t\t\t\t >");

		// Get Input
		fgets(Buff.word, 24, stdin);
		checkinput(&Buff);
		if      (Buff.flag == SAVE_FLAG) {
			option = 10;
		}
		else if (Buff.flag == LOAD_FLAG) {
			option = 11;
		}
		else {
			option = atoi(Buff.word);
		}
		

// Options
		switch (option)
		{
// 1. View List
		case 1: 
			while (Buff.flag != BREAK_FLAG)
			{
				printui();
				puts(LISTINTERFACE);
				printlist(List);
				puts(BORDERS);
				puts("Enter an Items name to check it off the list or write \"sort\" to sort list");
				printf("Check>");

				fgets(Buff.word, MAX_NAME_LENGTH, stdin);
				checkinput(&Buff);
				if (Buff.flag == GOOD_FLAG) 
				{
					index = getindex(List, Buff.word);
					if (index != -1) 
					{
						Item *current = &List->array[index];
						if (current->checked == false) {
							current->checked = true;
						}
						else if(current->checked == true) {
							current->checked = false;
						}
						printf("Item at Index %d\n",index);
					}
					else
						printf("No such item %s\n>",Buff.word);
				}
				else if (Buff.flag == EMPTY_FLAG)
					continue;
				else if (Buff.flag == BREAK_FLAG) 
					break;
				else if (Buff.flag == SORT_FLAG)
					sort(List);
			}
			Buff.flag = UNUSED_FLAG;
			break;
// 2. View Cupboard
		case 2: 
			printui();
			puts("Ingredients in Storage");
			puts(BORDERS);
			puts("Yellow Onion : 20");
			puts("Bell Peppers :  9");
			puts("Tomatoes     : 10");
			puts("Meat         :  7");
			puts("Egg          : 30");
			printf(">");
			fgets(PAUSE, 24, stdin);
			break;		
// 3. Add To List
		case 3: 
			while (true)
				{
				printui();
				puts(LISTINTERFACE);
				printlist(List);
				puts(BORDERS);

				printf("Product>");
				fgets(NameBuff.word, MAX_NAME_LENGTH, stdin);
				checkinput(&NameBuff);
					if (NameBuff.flag == EMPTY_FLAG)
						continue;
					if (NameBuff.flag == BREAK_FLAG)
						break;
				
				printf("Amount>");
				fgets(AmountBuff.word, 24, stdin);
				checkinput(&AmountBuff);
					if (AmountBuff.flag == EMPTY_FLAG)
						continue;
					if (AmountBuff.flag == BREAK_FLAG)
						break;

				insert(List, NameBuff.word, AmountBuff.word);
				}
			NameBuff.flag = UNUSED_FLAG;
			AmountBuff.flag = UNUSED_FLAG;
			break;		
// 4. Remove			
		case 4: 
			while (true)
			{
				printui();
				puts(LISTINTERFACE);
				printlist(List);
				puts(BORDERS);

				printf("Remove>");
				fgets(NameBuff.word, MAX_NAME_LENGTH, stdin);
				checkinput(&NameBuff);
					if (NameBuff.flag == EMPTY_FLAG)
						continue;
					if (NameBuff.flag == BREAK_FLAG)
						break;

				index = getindex(List, NameBuff.word);
				if (index != -1) {
					remove_item(List, index);
				} else {
					printf("Item \"%s\" is not in the list.\n", NameBuff.word);
				}
			}
			NameBuff.flag = UNUSED_FLAG;
			break;		
// 5. Edit			
		case 5: 
			while (true)
			{
			printui();
			puts(LISTINTERFACE);
			printlist(List);
			puts(BORDERS);
			puts("Which Item to edit?");


			printf("Item>");
			fgets(NameBuff.word, MAX_NAME_LENGTH, stdin);
			checkinput(&NameBuff);
				if (NameBuff.flag == EMPTY_FLAG)
					continue;
				if (NameBuff.flag == BREAK_FLAG)
					break;

			
			index = getindex(List, NameBuff.word);
				if (index == -1) 
				{
					printf("Item \"%s\" is not in the list.\n", NameBuff.word);
					fgets(PAUSE, 24, stdin);
					continue;
				}
			
				while (true)
				{
					puts("1. Edit Name");
					puts("2. Edit Amount");
					printf("Choice>");
					fgets(Buff.word, MAX_NAME_LENGTH, stdin);
					checkinput(&NameBuff);
						if (NameBuff.flag == EMPTY_FLAG)
							continue;
						if (NameBuff.flag == BREAK_FLAG)
							break;

					option = atoi(Buff.word);
					if (option)
						break;
				}
				
				if (option == 1) 
				{
					while (true) 
					{
					printf("Edit Name>");
					fgets(NameBuff.word, MAX_NAME_LENGTH, stdin);
					checkinput(&NameBuff);
						if (NameBuff.flag == EMPTY_FLAG)
							continue;
						if (NameBuff.flag == BREAK_FLAG)
							break;
					strcpy(List->array[index].name, NameBuff.word);
					break;
					}
				} 
				else if (option == 2) 
				{	
					while (true)
					{
					printf("Edit Amount>");
					fgets(AmountBuff.word, MAX_NAME_LENGTH, stdin);
					checkinput(&AmountBuff);
						if (NameBuff.flag == EMPTY_FLAG)
							continue;
						if (NameBuff.flag == BREAK_FLAG)
							break;
					List->array[index].amount = atoi(AmountBuff.word);
					break;
					}
				}
			}
			AmountBuff.flag = UNUSED_FLAG;
			NameBuff.flag = UNUSED_FLAG;
			break;		
// 9. Exit			
		case 9: 
			free(List->array);
			free(List);
			exit(EXIT_SUCCESS);
			break;		
// Save
		case 10:
			while (true)
			{
				printui();
				puts(LISTINTERFACE);
				printlist(List);
				puts(BORDERS);
				
				printf("Save file as: ");
				fgets(NameBuff.word, MAX_NAME_LENGTH, stdin);
				remove_nl(NameBuff.word);
				if (NameBuff.word[0] == '\n')
					continue;
				else if (strcmp(NameBuff.word, "quit") == 0) 
					break;

				if (access(NameBuff.word, F_OK) == 0) 
				{
					printf("File Exists \" %s \", do you want to overwrite it?\n", NameBuff.word);
					puts("1. Overwrite");
					puts("2. Cancel");
					fgets(Buff.word, 24, stdin);
					
					option = atoi(Buff.word);
				}
				if (option == 2)
					continue;

				// Writing or Overwriting
				FILE *savefile = fopen(NameBuff.word, "w");
				
					if (savefile == NULL)
					{
						perror("File error: ");
						fgets(PAUSE, 24, stdin);
						continue;
					}
				
				// Writing to file
				fprintf(savefile, "Size: %zu\n",List->size);
				
				for (size_t i = 0; i < List->used;i++) 
				{
					Item *current = &List->array[i];
					fprintf(savefile, "%s %d %d \n",\
					current->name, current->checked, current->amount);
				}
				fclose(savefile);
				printf("Inventory saved as: %s\n", NameBuff.word);
				fgets(PAUSE, 24, stdin);
				break;
			}
			Buff.flag = UNUSED_FLAG;
			break;
// Load
		case 11:
			while (true)
			{
				printui();
				puts(LISTINTERFACE);
				printlist(List);
				puts(BORDERS);

				puts("Load File:");
				printf(">");
				fgets(NameBuff.word, MAX_NAME_LENGTH, stdin);
				remove_nl(NameBuff.word);
				
				if (NameBuff.word[0] == '\n')
					continue;
				else if (strcmp(NameBuff.word, "quit") == 0) 
					break;
				else if (access(NameBuff.word, F_OK) != 0) 
				{
					printf("File \"%s\" does not exist.\n", NameBuff.word);
					fgets(PAUSE, 24, stdin);
					continue;
				}
				else if (access(NameBuff.word, R_OK) != 0) 
				{
					printf("Access denied to read file \"%s\"\n", NameBuff.word);
					fgets(PAUSE, 24, stdin);
					continue;
				}
				
				// Read File
				FILE *loadfile = fopen(NameBuff.word, "r");
				if (loadfile == NULL)
				{
					perror("File error:  ");
					fgets(PAUSE, 24, stdin);
					continue;
				}
				
				// Reset current List
				free(&List->array);
				List->size = 0;
				List->used = 0;

				// Prepare List for loading values from file.
				fscanf(loadfile,"Size: %zu", &List->size);
				List->array = malloc(sizeof(Item) * List->size);
				if (List->array == NULL) 
				{
					printf("Memory Allocation Failed!\nShutting Down!");
					free(List->array);
					free(List);
					exit(EXIT_FAILURE);
				}
				
				// Reading values from file.
				Item *c = &List->array[List->used];
				char fsbuff[MAX_NAME_LENGTH];
				int fbbuff;
				int fabuff;
				while(fscanf(loadfile, "%s %d %d", fsbuff, &fbbuff, &fabuff) == 3) 
				{
					strcpy(c->name, fsbuff);
					c->checked = fbbuff;
					c->amount = fabuff;

					List->used += 1;
					c = &List->array[List->used];
				}

				fclose(loadfile);
				puts("Items loaded");
				fgets(PAUSE, 24, stdin);
				break;
			}
			break;		
		default:
			break;
		}
	}
}

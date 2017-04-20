#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dungeon.h"
#include <unistd.h>

void printDungeon(room_t dlvls);
	
int main(int argc, char** argv) {
	
	// Read the first line from file to get the levels and make a linked list
	if(argc < 2)
	{
		fprintf(stderr, "No Level File Specified\n");
		exit(1);
	}
	if( access( argv[1], F_OK ) == -1 ) 
	{
		// File does not exist
		fprintf(stderr, "File does not exist\n");
		exit(1);
	}
	
	FILE * fp = fopen(argv[1], "r");
	char levels[MAX_LINE];
	
	fgets(levels, MAX_LINE, fp);
	
	levels[strlen(levels)-1] = '\0';
	
	//printf("%s\n", levels);
	
	// Parse string to create the structs
	int args = 1;
	char tempLevels[MAX_LINE];
	strcpy(tempLevels, levels);
	char * p = strtok(tempLevels, " ");
	while(p != NULL)
	{	
		p = strtok(NULL, " ");
		args++;	
	}
	args--;
	//printf("args : %d\n", args);
	
	/*char** rooms = (char**)malloc(sizeof(char*)*args);
	
	for(int i = 0; i < args; i++)
	{
		rooms[i] = (char*)malloc(sizeof(char)*MAX_LENGTH);
		//printf("Malloced: rooms[%d]times\n", i);
	}
	*/
	room_t* dlvls = (room_t*)malloc(sizeof(room_t)*args);
	
	for(int i = 0; i < args; ++i)
	{
		dlvls[i].north = NULL;
		dlvls[i].south = NULL;
		dlvls[i].east = NULL;
		dlvls[i].west = NULL;
	}
	
	char* q = strtok(levels, " ");
	
	int pos = 0;
	
	while(q != NULL)
	{	
		//strcpy(rooms[pos], q);
		strcpy(dlvls[pos].name, q);
		q = strtok(NULL, " ");
		//printf("pos: %d, string: %s\n", pos, rooms[pos]);
		pos++;	
	}
	
	//for(int i = 0; i < args; ++i)
	//{
	//	printf("levels:%s\n",dlvls[i].name);
	//}
	
	
	char directions[MAX_LINE]; // For storing fgets
	
	char blah[3][MAX_LENGTH];
	
	while(fgets(directions, MAX_LINE, fp))
	{
		directions[strlen(directions)-1] = '\0';
		
		//printf("directions: %s\n", directions);
		
		// Parse string here
		
		char* r = strtok(directions, " > ");
		
		int foo = 0;
		while(r != NULL)
		{
			strcpy(blah[foo], r);
			r = strtok(NULL, " > ");
			foo++;
		}
		//printf("blah[1]: %s\n", blah[1]);
		room_t* head;
		room_t* tail;
		//printf("blah[2]:%s\n", blah[2]);
		for(int i = 0; i < args; ++i)
		{
			//printf("i: %d, blah[1]: %s\n", i, blah[1]);
			if(strcmp(dlvls[i].name, blah[0]) == 0)
			{
				head = &dlvls[i];
			}
			if(strcmp(dlvls[i].name, blah[2]) == 0)
			{
				//printf("%s should be %s\n", blah[2], dlvls[i].name);
				//printf("address of dlvls[i]: %p\n", &dlvls[i]);
				tail = &dlvls[i];
				//printf("name of tail %s\n", tail->name);
				//printf("address of tail: %p\n", tail);
				//printf("address of dlvls: %p\n", &dlvls[i]);
			}
		}
			
			if(strcmp(blah[1], "NORTH") == 0)
			{
				head->north = tail;
			}
			if(strcmp(blah[1], "SOUTH") == 0)
			{
				//printf("blah[1]: %s\n", blah[1]);
				//printf("head: %s tail: %s\n", head->name, tail->name);
				head->south = tail;
			}
			if(strcmp(blah[1], "EAST") == 0)
			{
				head->east = tail;
			}
			if(strcmp(blah[1], "WEST") == 0)
			{
				head->west = tail;
			}
		}
	
		room_t* current = &dlvls[0];
	
		while(1)
		{	
			printDungeon(*current);
			printf("\n\n");
			
			char input[MAX_LENGTH];
			
			fgets(input, MAX_LENGTH, stdin);
			input[strlen(input)-1] = '\0';
			
			printf("\n");
			
			if(strcmp(input, "NORTH") == 0)
			{
				if(current->north != NULL)
				{
					current = current->north;
					continue;
				}
				else
				{
					printf("No path This Way\n\n");
					continue;
				}
			}
			else if(strcmp(input, "SOUTH") == 0)
			{
				if(current->south != NULL)
				{
					current = current->south;
					continue;
				}
				else
				{
					printf("No path This Way\n\n");
					continue;
				}
			}
			else if(strcmp(input, "EAST") == 0)
			{
				if(current->east != NULL)
				{
					current = current->east;
					continue;
				}
				else
				{
					printf("No path This Way\n\n");
					continue;
				}
			}
			else if(strcmp(input, "WEST") == 0)
			{
				if(current->west != NULL)
				{
					current = current->west;
					continue;
				}
				else
				{
					printf("No path This Way\n\n");
					continue;
				}
			}
			else if(strcmp(input, "QUIT") == 0)
			{
				return 0;
			}
			else
			{
				printf("What?\n\n");
				continue;
			}
		}
		
		
		//printf("Head: %s\n", head.name);
		//printf("Tail: %s\n", tail.name);
		
		/*
		for(int i = 0; i < 3; ++i)
		{
			printf("%s\n", blah[i]);
		}
		*/
	// Draw dungeons
		//printf("%s\n", dlvls[0].west->name);
		
	
	free(dlvls);
	fclose(fp);
	return 0;
}

void printDungeon(room_t dlvls)
{
			printf("%s\n", dlvls.name);
			// Draw top border
			for(int j = 0; j < 9; ++j)
			{
				if(j == 0 || j == 8)
				{
					printf(" ");
				}
				else if(j == 4)
				{
					if(dlvls.north != NULL)
					{
						printf("N");
					}
					else{
						printf("-");
					}
				}
				else
				{
					printf("-");
				}
			}
			printf("\n");
			for(int j = 0; j < 7; ++j)
			{
				for(int k = 0; k < 9; ++k)
				{
					if(k == 0 || k == 8)
					{
						if(k == 0 && j == 3 && dlvls.west != NULL)
						{
							printf("W");
						}
						else if(k == 8 && j == 3 && dlvls.east != NULL)
						{
							printf("E");
						}
						else
							printf("|");
					}
					else
					{
						printf(" ");
					}
				}
				printf("\n");
			}
			for(int j = 0; j < 9; ++j)
			{
				if(j == 0 || j == 8)
				{
					printf(" ");
				}
				else if(j == 4)
				{
					if(dlvls.south != NULL)
					{
						printf("S");
					}
					else{
						printf("-");
					}
				}
				else
				{
					printf("-");
				}
			}
			printf("\n");
}

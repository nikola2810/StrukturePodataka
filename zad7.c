#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_SIZE 64
#define BUFFER_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _directory* directory;
typedef struct _directory
{
	char name[MAX_NAME_SIZE];
	directory parent, previous, next;
}Directory;

directory create_directory(char* name, directory parent);
int create_subdirectory(char* name, directory current);
directory find_subdirectory(char* name, directory current);
int print_directory(directory current);
directory go_to_parent_directory(directory current);
int free_directory(directory current);
int print_full_path(directory current);
int dos_command(directory current);

int main()
{
	directory root = (directory)malloc(sizeof(Directory));
	strcpy(root->name, "root");
	root->parent = NULL;
	root->next = NULL;
	root->previous = NULL;

	dos_command(root);

	free_directory(root);

	return EXIT_SUCCESS;
}

directory create_directory(char* name, directory parent)
{
	directory new = (directory)malloc(sizeof(Directory));
	if (!new)
	{
		printf("Pogreška u alokaciji memorije!\n");
		return NULL;
	}

	strcpy(new->name, name);
	new->parent = parent;
	new->next = NULL; 
	new->previous = NULL; 

	return new;
}

int create_subdirectory(char* name, directory current)
{
	directory new = create_directory(name, current);

	if (!new) return EXIT_FAILURE;

	if (!current->next) current->next = new; 
	else
	{
		directory temp = current->next;
		while (temp->next) temp = temp->next;
		temp->next = new;
		new->previous = temp;
	}

	return EXIT_SUCCESS;
}

directory find_subdirectory(char* name, directory current)
{
	directory temp = current->next;

	while (temp)
	{
		if (strcmp(temp->name, name) == 0) return temp;
		temp = temp->next;
	}
	return NULL;
}


int print_directory(directory current)
{
	directory temp = current->next; 
	if (!temp)
	{
		printf("Direktorij '%s' nema poddirektorije!\n", current->name);
		return EXIT_FAILURE;
	}

	while (temp)
	{
		printf("Poddirektorij: ");
		print_full_path(temp);
		printf("\n");
		temp = temp->next; 
	}

	return EXIT_SUCCESS;
}

directory go_to_parent_directory(directory current)
{
	if (current->parent) return current->parent;

	return current;
}

int free_directory(directory current)
{
	if (!current)
	{
		printf("Direktorij je već slobodan!\n");
		return EXIT_FAILURE;
	}

	directory temp = current->next;
	while (temp)
	{
		directory to_delete = temp;
		temp = temp->next;
		free(to_delete);
	}

	free(current);

	return EXIT_SUCCESS;
}

int print_full_path(directory current)
{
	if (current == NULL) return EXIT_FAILURE;

	if (current->parent)
	{
		print_full_path(current->parent); 
		printf("\\%s", current->name);    
	}
	else printf("%s", current->name); 
	
	return EXIT_SUCCESS;
}

int dos_command(directory current)
{
	int choice;
	char name[MAX_NAME_SIZE];
	char command[MAX_NAME_SIZE];
	char buffer[BUFFER_SIZE];

	printf("Komande: \n");
	printf("1 - md [naziv direktorija]\n");
	printf("2 - cd [naziv direktorija]\n");
	printf("3 - cd..\n");
	printf("4 - dir \n");
	printf("5 - izlaz \n");

	while (1)
	{

		printf("Trenutni direktorij: ");
		print_full_path(current);
	
		printf("\nUnesi komandu: ");

		if (fgets(buffer, MAX_NAME_SIZE, stdin) == NULL)
		{
			printf("Greška u čitanju komande!\n");
			continue;
		}

		buffer[strcspn(buffer, "\n")] = 0;

		int argc = sscanf(buffer, "%s %s", command, name);
		if (argc == -1) continue;

		if (strcmp(command, "md") == 0) 
		{
			if (argc < 2) 
			{
				printf("Nedostaje ime direktorija nakon 'md'.\n");
				continue;
			}

			else if (find_subdirectory(name, current)) 
			{
				printf("Direktorij '%s' već postoji.\n", name);
				continue;
			}

			create_subdirectory(name, current);
			printf("Uspješno kreiran direktorij '%s'.\n", name);

		}
		else if (strcmp(command, "cd") == 0) 
		{
			if (argc < 2)
			{
				printf("Nedostaje ime direktorija nakon 'cd'.\n");
				continue;
			}
				
			directory sub_directory = find_subdirectory(name, current);
			if (sub_directory) current = sub_directory;
			else printf("Poddirektorij '%s' ne postoji.\n", name);
		}
		else if (strcmp(command, "cd..") == 0) current = go_to_parent_directory(current);

		else if (strcmp(command, "dir") == 0)
		{
			printf("Direktorij '%s':\n", current->name);
			print_directory(current);
		}
		else if (strcmp(command, "izlaz") == 0 || strcmp(buffer, "izlaz") == 0)
		{
			printf("Uspješni izlaz iz programa.\n");
			break;
		}
		else printf("Nepotnata komanda: '%s'\n", command);
		
	}
}

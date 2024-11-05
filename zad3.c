#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct _person* position;
typedef struct _person {
	char fname[50];
	char lname[50];
	int birth_year;
	position next;
}person;

position createPerson(char* name, char* lastname, int year);
position findLast(position head);
position findByLastName(position head, char* lastname);
position findPrev(position head, position P);
void addBegin(position head, char* name, char* lastname, int year);
void addEnd(position head, char* name, char* lastname, int year);
void delete(position head, char* lastname);
void print(position head);
void freeList(position head);



int main()
{
	person head;
	*head.fname = '\0';
	*head.lname = '\0';
	head.birth_year = 0;
	head.next = NULL;

	addBegin(&head, "Ana", "Jukic", 2005);
	addBegin(&head, "Ante", "Ivic", 2003);
	addEnd(&head, "Ive", "Matic", 2004);
	print(&head);
	delete(&head, "Matic");
	print(&head);

	freeList(&head);
	return 0;
}



position createPerson(char* name, char* lastname, int year)
{
	position newPerson = (position)malloc(sizeof(person));
	if (newPerson == NULL) {
		printf("Error");
		return NULL;
	}

	strncpy(newPerson->fname, name, sizeof(newPerson->fname));
	strncpy(newPerson->lname, lastname, sizeof(newPerson->lname));
	newPerson->birth_year = year;
	newPerson->next = NULL;

	return newPerson;
}

position findLast(position head)
{
	position temp = head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}

position findByLastName(position head, char* lastname)
{
	position temp = head;

	while (temp != NULL) {
		if (strcmp(temp->lname, lastname) == 0) {
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

position findPrev(position head, position P)
{
	position temp = head;

	while (temp->next != P) {
		temp = temp->next;
	}

	return temp;
}

void addBegin(position head, char* name, char* lastname, int year)
{
	position P = createPerson(name, lastname, year);

	P->next = head->next;
	head->next = P;
}

void addEnd(position head, char* name, char* lastname, int year)
{
	position P = createPerson(name, lastname, year);
	position last = findLast(head);

	P->next = last->next;
	last->next = P;
}

void delete(position head, char* lastname)
{
	position toDelete = findByLastName(head, lastname);
	position prev = findPrev(head, toDelete);

	prev->next = toDelete->next;
	free(toDelete);
}

void print(position head)
{
	position temp = head;

	while (temp != NULL) {
		if (temp->birth_year != 0) {
			printf("%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
	printf("\n");
}

void freeList(position head)
{
	position temp = head;
	position next;

	while (temp != NULL) {
		next = temp->next;
		free(temp);
		temp = next;
	}
}
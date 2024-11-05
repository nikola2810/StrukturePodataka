#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct _person* position;
typedef struct _person {
    char fname[50];
    char lname[50];
    int birth_year;
    position next;
} person;

position createPerson(char* name, char* lastname, int year);
position findLast(position head);
position findByLastName(position head, char* lastname);
position findPrev(position head, position P);
void addBegin(position head, char* name, char* lastname, int year);
void addEnd(position head, char* name, char* lastname, int year);
void addAfter(position head, char* targetLastName, char* name, char* lastname, int year);
void addBefore(position head, char* targetLastName, char* name, char* lastname, int year);
void sortList(position head);
void writeToFile(position head, const char* filename);
void readFromFile(position head, const char* filename);
void delete(position head, char* lastname);
void print(position head);
void freeList(position head);

int main() {
    person head;
    *head.fname = '\0';
    *head.lname = '\0';
    head.birth_year = 0;
    head.next = NULL;

    addBegin(&head, "Ana", "Jukic", 2005);
    addBegin(&head, "Ante", "Ivic", 2003);
    addEnd(&head, "Ive", "Matic", 2004);
    addAfter(&head, "Jukic", "Marko", "Kovacic", 2000);
    addBefore(&head, "Jukic", "Luka", "Vukic", 1998);
    sortList(&head);

    print(&head);
    writeToFile(&head, "people.txt");

    freeList(&head);
    readFromFile(&head, "people.txt");
    print(&head);

    freeList(&head);
    return 0;
}

position createPerson(char* name, char* lastname, int year) {
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

position findLast(position head) {
    position temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}


position findByLastName(position head, char* lastname) {
    position temp = head;
    while (temp != NULL) {
        if (strcmp(temp->lname, lastname) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

position findPrev(position head, position P) {
    position temp = head;
    while (temp->next != P) {
        temp = temp->next;
    }
    return temp;
}


void addBegin(position head, char* name, char* lastname, int year) {
    position P = createPerson(name, lastname, year);
    P->next = head->next;
    head->next = P;
}

void addEnd(position head, char* name, char* lastname, int year) {
    position P = createPerson(name, lastname, year);
    position last = findLast(head);
    P->next = last->next;
    last->next = P;
}

void addAfter(position head, char* targetLastName, char* name, char* lastname, int year) {
    position target = findByLastName(head, targetLastName);
    if (target == NULL) {
        printf("Person not found.\n");
        return;
    }

    position newPerson = createPerson(name, lastname, year);
    newPerson->next = target->next;
    target->next = newPerson;
}

void addBefore(position head, char* targetLastName, char* name, char* lastname, int year) {
    position target = findByLastName(head, targetLastName);
    if (target == NULL) {
        printf("Person not found.\n");
        return;
    }

    position prev = findPrev(head, target);
    position newPerson = createPerson(name, lastname, year);
    newPerson->next = prev->next;
    prev->next = newPerson;
}

void sortList(position head) {
    position i, j, prev_i, prev_j, temp;
    for (i = head->next; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->lname, j->lname) > 0) {
                char tempFname[50], tempLname[50];
                int tempYear;

                strcpy(tempFname, i->fname);
                strcpy(tempLname, i->lname);
                tempYear = i->birth_year;

                strcpy(i->fname, j->fname);
                strcpy(i->lname, j->lname);
                i->birth_year = j->birth_year;

                strcpy(j->fname, tempFname);
                strcpy(j->lname, tempLname);
                j->birth_year = tempYear;
            }
        }
    }
}

void writeToFile(position head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    position temp = head->next;
    while (temp != NULL) {
        fprintf(file, "%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }

    fclose(file);
}

void readFromFile(position head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char name[50], lastname[50];
    int year;
    while (fscanf(file, "%s %s %d", name, lastname, &year) == 3) {
        addEnd(head, name, lastname, year);
    }

    fclose(file);
}

void delete(position head, char* lastname) {
    position toDelete = findByLastName(head, lastname);
    if (toDelete == NULL) {
        printf("Person not found.\n");
        return;
    }

    position prev = findPrev(head, toDelete);
    prev->next = toDelete->next;
    free(toDelete);
}

void print(position head) {
    position temp = head->next;
    while (temp != NULL) {
        printf("%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(position head) {
    position temp = head->next;
    position next;
    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }
    head->next = NULL;
}

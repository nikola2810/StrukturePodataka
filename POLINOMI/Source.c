#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define BUFFER_SIZE 1024

typedef struct polinom* position;
typedef struct polinom {

    int exp;
    int coef;
    position next;

}polinom;

void insertSort(position, int, int);
void readFile(position, char*);
void print(position);
position addLists(position, position);
position multiplyLists(position, position);
void freeList(position);

int main() {

    position head = (position)malloc(sizeof(polinom)); if (head == NULL) { return -1; }
    head->next = NULL;
    readFile(head, "polinom1.txt");
    printf("\nPrvi polinom\n");
    print(head);
    printf("\n");


    position head1 = (position)malloc(sizeof(polinom)); if (head1 == NULL) { return -1; }
    head1->next = NULL;
    readFile(head1, "polinom2.txt");
    printf("\nDrugi polinom\n");
    print(head1);
    printf("\n_____\n");


    position new = addLists(head, head1);
    printf("\nZbrojeni polinomi\n");
    print(new);
    printf("\n");
    freeList(new);
    free(new);

    position pom = multiplyLists(head, head1);
    printf("\nPomnozeni polinomi\n");
    print(pom);
    printf("\n");
    freeList(pom);
    free(pom);

    freeList(head);
    free(head);

    freeList(head1);
    free(head1);

    return 0;
}

void insertSort(position head, int coef, int exp) {

    position new = (position)malloc(sizeof(polinom)); if (new == NULL) { return; }
    new->exp = exp;
    new->coef = coef;
    new->next = NULL;
    position curr = head;

    while (curr->next != NULL && curr->next->exp <= exp) {

        position tmp = curr->next;

        if (tmp->exp == new->exp) {


            new->coef = coef + tmp->coef;
            if (new->coef) {
                new->next = tmp->next;
                curr->next = new;

                free(tmp);
            }
            else if (!new->coef) {
                curr->next = tmp->next;
                free(new);
                free(tmp);
            }


            return;

        }
        curr = curr->next;
    }

    new->next = curr->next;
    curr->next = new;

}

void readFile(position head, char* filePath) {
    char buffer[BUFFER_SIZE];
    FILE* data = NULL;
    data = fopen(filePath, "r");
    {
        if (data == NULL) { return; }
    }

    int exp, coef, offset = 0, numBytes;

    fgets(buffer, BUFFER_SIZE, data);

    while (sscanf(buffer + offset, "%d %d %n,", &coef, &exp, &numBytes) == 2) {
        insertSort(head, coef, exp);
        offset += numBytes;

    }

    fclose(data);

}

void print(position head) {

    position curr = head->next;

    if (curr == NULL) {
        printf("Polinoma nema!!");
        return;
    }

    while (curr != NULL) {

        if (!curr->next) {
            printf("%dx^%d", curr->coef, curr->exp);
        }
        else {
            printf("%dx^%d + ", curr->coef, curr->exp);
        }


        curr = curr->next;
    }

}

position addLists(position head1, position head2) {

    position new = (position)malloc(sizeof(polinom)); {
        if (new == NULL) { return NULL; }
    }

    new->next = NULL;


    position curr1 = head1->next;
    position curr2 = head2->next;
    while (curr1 != NULL) {

        insertSort(new, curr1->coef, curr1->exp);
        curr1 = curr1->next;
    }



    while (curr2 != NULL) {

        insertSort(new, curr2->coef, curr2->exp);
        curr2 = curr2->next;
    }

    return new;

}


position multiplyLists(position head1, position head2) {

    position new = (position)malloc(sizeof(polinom)); {
        if (new == NULL) { return NULL; }
    }

    new->next = NULL;

    position curr1 = head1->next;

    while (curr1 != NULL) {

        position curr2 = head2->next;

        while (curr2 != NULL) {
            int exp, coef;
            exp = curr1->exp + curr2->exp;
            coef = curr1->coef * curr2->coef;

            insertSort(new, coef, exp);

            curr2 = curr2->next;
        }



        curr1 = curr1->next;
    }

    return new;

}

void freeList(position head) {
    position temp;

    while (head->next != NULL) {
        temp = head->next;
        head->next = head->next->next;
        free(temp);
    }
}
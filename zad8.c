#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node* PtrToNode;
typedef struct _Node {
    int value;
    PtrToNode leftChild, rightChild;
} Node;

PtrToNode CreateNewNode(int val);
PtrToNode AddElement(PtrToNode root, int val);
void DisplayInOrder(PtrToNode root);
void DisplayPreOrder(PtrToNode root);
void DisplayPostOrder(PtrToNode root);
int CalculateHeight(PtrToNode root);
void PrintCurrentLevel(PtrToNode root, int level);
void DisplayLevelOrder(PtrToNode root);
int FindElement(PtrToNode root, int val);
PtrToNode FindMin(PtrToNode root);
PtrToNode RemoveElement(PtrToNode root, int val);
void ShowMenu(PtrToNode root);

int main() {
    PtrToNode root = NULL;
    int elements[] = { 3, 1, 5, 2, 6, 4, 8 };
    int count = sizeof(elements) / sizeof(elements[0]);

    for (int i = 0; i < count; i++) {
        root = AddElement(root, elements[i]);
    }

    ShowMenu(root);

    return 0;
}

PtrToNode CreateNewNode(int val) {
    PtrToNode newNode = (PtrToNode)malloc(sizeof(Node));
    if (!newNode) {
        printf("Alokacija memorije neuspjesna!\n");
        return NULL;
    }

    newNode->value = val;
    newNode->leftChild = newNode->rightChild = NULL;

    return newNode;
}

PtrToNode AddElement(PtrToNode root, int val) {
    if (!root) return CreateNewNode(val);

    if (val < root->value) {
        root->leftChild = AddElement(root->leftChild, val);
    } else if (val > root->value) {
        root->rightChild = AddElement(root->rightChild, val);
    }

    return root;
}

void DisplayInOrder(PtrToNode root) {
    if (root) {
        DisplayInOrder(root->leftChild);
        printf("%d ", root->value);
        DisplayInOrder(root->rightChild);
    }
}

void DisplayPreOrder(PtrToNode root) {
    if (root) {
        printf("%d ", root->value);
        DisplayPreOrder(root->leftChild);
        DisplayPreOrder(root->rightChild);
    }
}

void DisplayPostOrder(PtrToNode root) {
    if (root) {
        DisplayPostOrder(root->leftChild);
        DisplayPostOrder(root->rightChild);
        printf("%d ", root->value);
    }
}

int CalculateHeight(PtrToNode root) {
    if (!root) return 0;

    int leftHeight = CalculateHeight(root->leftChild);
    int rightHeight = CalculateHeight(root->rightChild);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void PrintCurrentLevel(PtrToNode root, int level) {
    if (!root) return;

    if (level == 1) {
        printf("%d ", root->value);
    } else if (level > 1) {
        PrintCurrentLevel(root->leftChild, level - 1);
        PrintCurrentLevel(root->rightChild, level - 1);
    }
}

void DisplayLevelOrder(PtrToNode root) {
    int h = CalculateHeight(root);

    for (int i = 1; i <= h; i++) {
        PrintCurrentLevel(root, i);
    }
}

int FindElement(PtrToNode root, int val) {
    if (!root) return 0;

    if (root->value == val) return 1;

    if (val < root->value) {
        return FindElement(root->leftChild, val);
    }

    return FindElement(root->rightChild, val);
}

PtrToNode FindMin(PtrToNode root) {
    PtrToNode current = root;

    while (current && current->leftChild) {
        current = current->leftChild;
    }

    return current;
}

PtrToNode RemoveElement(PtrToNode root, int val) {
    if (!root) return root;

    if (val < root->value) {
        root->leftChild = RemoveElement(root->leftChild, val);
    } else if (val > root->value) {
        root->rightChild = RemoveElement(root->rightChild, val);
    } else {
        if (!root->leftChild) {
            PtrToNode temp = root->rightChild;
            free(root);
            return temp;
        } else if (!root->rightChild) {
            PtrToNode temp = root->leftChild;
            free(root);
            return temp;
        }

        PtrToNode temp = FindMin(root->rightChild);
        root->value = temp->value;
        root->rightChild = RemoveElement(root->rightChild, temp->value);
    }

    return root;
}

void ShowMenu(PtrToNode root) {
    int choice, val;

    printf("Binarno stablo meni\n\n");
    printf("1. Dodaj element\n");
    printf("2. Inorder\n");
    printf("3. Preorder\n");
    printf("4. Postorder\n");
    printf("5. Level order\n");
    printf("6. Pronadi element\n");
    printf("7. Izbrisi element\n");
    printf("8. Izadji\n");

    do {
        printf("\nUnesi odabir (1-8): ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Unesi element za dodavanje: ");
            scanf("%d", &val);
            root = AddElement(root, val);
            break;
        case 2:
            DisplayInOrder(root);
            printf("\n");
            break;
        case 3:
            DisplayPreOrder(root);
            printf("\n");
            break;
        case 4:
            DisplayPostOrder(root);
            printf("\n");
            break;
        case 5:
            DisplayLevelOrder(root);
            printf("\n");
            break;
        case 6:
            printf("Unesi element za pronalazenje: ");
            scanf("%d", &val);
            if (FindElement(root, val)) {
                printf("Element %d postoji u stablu.\n", val);
            } else {
                printf("Element %d ne postoji u stablu.\n", val);
            }
            break;
        case 7:
            printf("Unesi broj za uklanjanje: ");
            scanf("%d", &val);
            root = RemoveElement(root, val);
            printf("Element %d je uklonjen iz stabla.\n", val);
            break;
        case 8:
            printf("Izlazak iz izbornika.\n");
            break;
        default:
            printf("Neispravan izbor. Pokusaj ponovno.\n");
        }
    } while (choice != 8);
}

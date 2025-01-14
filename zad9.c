#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TreeNode* TreePosition;
typedef struct TreeNode {
    int value;
    TreePosition leftChild, rightChild;
} TreeNode;

TreePosition CreateNewNode(int value);
TreePosition AddNode(TreePosition root, int value);
int ReplaceNodeValues(TreePosition root);
int SaveToFile(TreePosition root, const char* fileName);
int WriteInOrderToFile(TreePosition root, FILE* filePointer);
int PrintInOrder(TreePosition root);
int PrintPreOrder(TreePosition root);
int PrintPostOrder(TreePosition root);
int CalculateHeight(TreePosition root);
int PrintCurrentLevel(TreePosition root, int level);
int PrintLevelOrder(TreePosition root);
int FindValue(TreePosition root, int value);
TreePosition FindMinimum(TreePosition root);
TreePosition RemoveNode(TreePosition root, int value);
void DisplayMenu(TreePosition root);

int main() {
    TreePosition root = NULL;
    srand((unsigned)time(NULL));

    int values[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
    for (int i = 0; i < 10; i++) {
        root = AddNode(root, values[i]);

    }

    DisplayMenu(root);

    return 0;
}

TreePosition CreateNewNode(int value) {
    TreePosition newNode = (TreePosition)malloc(sizeof(TreeNode));
    if (!newNode) {
        printf("Error allocating memory!\n");
        return NULL;
    }

    newNode->value = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;

    return newNode;
}

TreePosition AddNode(TreePosition root, int value) {
    if (!root) return CreateNewNode(value);

    if (value >= root->value) {
        root->leftChild = AddNode(root->leftChild, value);
    } else {
        root->rightChild = AddNode(root->rightChild, value);
    }

    return root;
}

int ReplaceNodeValues(TreePosition root) {
    if (!root) return 0;

    int leftSum = ReplaceNodeValues(root->leftChild);
    int rightSum = ReplaceNodeValues(root->rightChild);

    int oldValue = root->value;
    root->value = leftSum + rightSum;

    return root->value + oldValue;
}

int SaveToFile(TreePosition root, const char* fileName) {
    FILE* filePointer = fopen(fileName, "a");
    if (!filePointer) {
        printf("Error opening file!\n");
        return EXIT_FAILURE;
    }

    WriteInOrderToFile(root, filePointer);
    fprintf(filePointer, "\n");

    fclose(filePointer);
    return EXIT_SUCCESS;
}

int WriteInOrderToFile(TreePosition root, FILE* filePointer) {
    if (root) {
        WriteInOrderToFile(root->rightChild, filePointer);
        fprintf(filePointer, "%d ", root->value);
        WriteInOrderToFile(root->leftChild, filePointer);
    }
    return EXIT_SUCCESS;
}

int PrintInOrder(TreePosition root) {
    if (root) {
        PrintInOrder(root->leftChild);
        printf("%d ", root->value);
        PrintInOrder(root->rightChild);
    }
    return EXIT_SUCCESS;
}

int PrintPreOrder(TreePosition root) {
    if (root) {
        printf("%d ", root->value);
        PrintPreOrder(root->leftChild);
        PrintPreOrder(root->rightChild);
    }
    return EXIT_SUCCESS;
}

int PrintPostOrder(TreePosition root) {
    if (root) {
        PrintPostOrder(root->leftChild);
        PrintPostOrder(root->rightChild);
        printf("%d ", root->value);
    }
    return EXIT_SUCCESS;
}

int CalculateHeight(TreePosition root) {
    if (!root) return 0;

    int leftHeight = CalculateHeight(root->leftChild);
    int rightHeight = CalculateHeight(root->rightChild);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int PrintCurrentLevel(TreePosition root, int level) {
    if (!root) return EXIT_FAILURE;

    if (level == 1) {
        printf("%d ", root->value);
    } else if (level > 1) {
        PrintCurrentLevel(root->leftChild, level - 1);
        PrintCurrentLevel(root->rightChild, level - 1);
    }

    return EXIT_SUCCESS;
}

int PrintLevelOrder(TreePosition root) {
    int treeHeight = CalculateHeight(root);

    for (int i = 1; i <= treeHeight; i++) {
        PrintCurrentLevel(root, i);
    }

    return EXIT_SUCCESS;
}

int FindValue(TreePosition root, int value) {
    if (!root) return 0;
    if (root->value == value) return 1;
    if (value < root->value) return FindValue(root->leftChild, value);
    return FindValue(root->rightChild, value);
}

TreePosition FindMinimum(TreePosition root) {
    TreePosition current = root;
    while (current && current->leftChild) {
        current = current->leftChild;
    }
    return current;
}

TreePosition RemoveNode(TreePosition root, int value) {
    if (!root) return root;

    if (value < root->value) {
        root->leftChild = RemoveNode(root->leftChild, value);
    } else if (value > root->value) {
        root->rightChild = RemoveNode(root->rightChild, value);
    } else {
        if (!root->leftChild) {
            TreePosition temp = root->rightChild;
            free(root);
            return temp;
        } else if (!root->rightChild) {
            TreePosition temp = root->leftChild;
            free(root);
            return temp;
        }

        TreePosition temp = FindMinimum(root->rightChild);
        root->value = temp->value;
        root->rightChild = RemoveNode(root->rightChild, temp->value);
    }

    return root;
}

void DisplayMenu(TreePosition root) {
    int choice, value;
    const char* fileName = "tree_output.txt";

    printf("BINARY TREE MENU\n\n");
    printf("1. Add a new element\n");
    printf("2. Print In-Order\n");
    printf("3. Print Pre-Order\n");
    printf("4. Print Post-Order\n");
    printf("5. Print Level-Order\n");
    printf("6. Search for a value\n");
    printf("7. Remove a value\n");
    printf("8. Replace values with subtree sums\n");
    printf("9. Save In-Order to file\n");
    printf("10. Exit\n");

    do {
        printf("\nEnter your choice (1-10): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to add: ");
                scanf("%d", &value);
                root = AddNode(root, value);
                break;

            case 2:
                PrintInOrder(root);
                printf("\n");
                break;

            case 3:
                PrintPreOrder(root);
                printf("\n");
                break;

            case 4:
                PrintPostOrder(root);
                printf("\n");
                break;

            case 5:
                PrintLevelOrder(root);
                printf("\n");
                break;

            case 6:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (FindValue(root, value)) {
                    printf("Value %d found in the tree.\n", value);
                } else {
                    printf("Value %d not found in the tree.\n", value);
                }
                break;

            case 7:
                printf("Enter value to remove: ");
                scanf("%d", &value);
                root = RemoveNode(root, value);
                printf("Value %d removed successfully.\n", value);
                break;

            case 8:
                ReplaceNodeValues(root);
                printf("Tree values replaced with subtree sums.\n");
                break;

            case 9:
                SaveToFile(root, fileName);
                printf("Tree saved to file %s successfully.\n", fileName);
                break;

            case 10:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 10);
}

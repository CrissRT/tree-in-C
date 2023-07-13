#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node
{

    int key;
    struct Node *Left, *Right, *Middle;
}TreeNode;

typedef struct Tree
{
    TreeNode *root;
}Tree;

typedef struct QueueNode
{
    TreeNode *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

int meniu(int n);
Tree *_createTree();
TreeNode *_createNode(int *key);
TreeNode *push(Tree *tree);
void printTree(TreeNode *currentNode);
TreeNode* searchNode(TreeNode* node, int key);
void clearTree(TreeNode* node);
void freeTree(Tree* tree);
void deleteTree(Tree* tree);
void inorderTraversal(TreeNode *root);
void displayTreeNode(TreeNode *currentNode);
void launchBalance(Tree *tree);
void insert_node(Tree *tree, int *arr, int start, int end);
void create_balanced_bst(Tree *tree, int *arr, int n);
int compare(const void *a, const void *b);
int countNodes(TreeNode *node);
void putTreeElementsInArray(TreeNode* node, int* arr, int *index);

int main()
{
    char userAnswer;
    int n;
    Tree * tree = _createTree();
    // system("cls");
    begin:
    n = meniu(n);
    switch (n)
    {
    case 1:
    {
        if (tree->root)
            clearTree(tree->root);
        push(tree);
        break;
    }

    case 2:
    {
        if (tree->root == NULL)
            printf("The tree is empty\n");
        else
            printTree(tree->root);
        break;
    }  
    case 9:
    {
        if (tree->root == NULL)
            printf("The tree is empty\n");
        else
            launchBalance(tree);
        break;
    }

    case 11:
        freeTree(tree);
        printf("The tree is cleared\n");
    break;

    case 12:
        deleteTree(tree);
        printf("The tree was deleted\n");
        scanf("%d", &n);
        exit(0);    
    break;


    default:
        break;
    }
    
    printf("\nOther option:(y/n): ");
    scanf(" %c", &userAnswer);
    if (userAnswer == 'y')
    {
        // system("cls");
        goto begin;
    }
    scanf("%d", &n);
    return 0;
    
}




int meniu(int n)
{
    printf ("The meniu:\n"); 
    printf("1 - Reading tree elements from keyboard\n");
    printf("2 - Displaying tree elements to console\n");
    printf("9 - Balancing the tree and making BST\n");
    printf("11 - Clearing the tree elements\n");
    printf("12 - Releasing the memory of the tree\n");
    printf("Enter the desired option: ");
    scanf ("%d" , &n);
    printf ("\n"); 
    while (n > 12 || n < 1)
    {
        printf ("Insert other option: "); 
        scanf ("%d" , &n);
    }
    return n;
}

Tree *_createTree()
{
    Tree * tree = malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

TreeNode *_createNode(int *key)
{
    TreeNode * node = malloc(sizeof(TreeNode));
    node->key = *key;
    node->Left = NULL;
    node->Right = NULL;
    node->Middle = NULL;
    return node;
}

TreeNode *push(Tree *tree)
{
    int key;
    printf("Enter key(-1 for no data):");
    scanf("%d", &key);
    if (key <= -1 )
        return NULL;
    TreeNode * currentNode = _createNode(&key);
    printf("Enter left child of %d\n", key);
    if (tree->root == NULL)
        tree->root = currentNode;
    currentNode->Left = push(tree);
    printf("Enter right child of %d\n", key);
    currentNode->Right = push(tree);
    printf("Enter middle child of %d\n", key);
    currentNode->Middle = push(tree);
    return currentNode;
}

void printTree(TreeNode *currentNode)
{
    if (currentNode == NULL)
        return;
    displayTreeNode(currentNode);
    if (currentNode->Left) 
        printTree(currentNode->Left);
    if (currentNode->Right)
        printTree(currentNode->Right);
    if (currentNode->Middle)
        printTree(currentNode->Middle);
}

void displayTreeNode(TreeNode *currentNode)
{   
    printf("Key: %d\n", currentNode->key);
}

// Function to search for a node in a binary tree based on a search key
TreeNode* searchNode(TreeNode* node, int key) 
{
    if (node == NULL)
    {
        printf("The node with this key was not found!\n");  
        return NULL;
    }  
    if (node->key == key)
    {
        displayTreeNode(node);
        return NULL;
    }
    searchNode(node->Left, key);
    searchNode(node->Right, key);
    searchNode(node->Middle, key);
}

// Function to clear all the nodes in a binary tree
void clearTree(TreeNode* node) 
{
    if (node == NULL)
        return;
    clearTree(node->Left);
    clearTree(node->Right);
    free(node);
}

// FunctionfreeTree to free the memory used by a binary tree
void freeTree(Tree* tree) 
{
    clearTree(tree->root);
    tree->root = NULL;
}

void deleteTree(Tree* tree) 
{
    freeTree(tree);
    free(tree);
}

void launchBalance(Tree *tree)
{
    int count = countNodes(tree->root);
    int index = 0;
    int arr[count];
    putTreeElementsInArray(tree->root, arr, &index);
    freeTree(tree);
    create_balanced_bst(tree, arr, count);
    free(arr);
    printf("The tree is balanced ternary search tree\n");
}

void insert_node(Tree *tree, int *arr, int start, int end)
{
    if (start > end)
        return;
    int mid = (start + end) / 2;
    TreeNode *node = _createNode(&arr[mid]);

    if (tree->root == NULL)
        tree->root = node;
    else
    {
        TreeNode *curr = tree->root;
        while (1)
        {
            if (node->key < curr->key + 2)
            {
                if (curr->Left == NULL)
                {
                    curr->Left = node;
                    break;
                }
                else
                    curr = curr->Left;
            }
            else if (node->key > curr->key + 2)
            {
                if (curr->Right == NULL)
                {
                    curr->Right = node;
                    break;
                }
                else
                    curr = curr->Right;
            }
            else
            {
                if (curr->Middle == NULL)
                {
                    curr->Middle = node;
                    break;
                }
                else
                    curr = curr->Middle;
            }
        }
    }

    insert_node(tree, arr, start, mid - 1);
    insert_node(tree, arr, mid + 1, end);
}

void create_balanced_bst(Tree *tree, int *arr, int n)
{
    // Sort the array
    qsort(arr, n, sizeof(arr), compare);

    // Insert the middle element into the tree and recursively create left and right subtrees
    insert_node(tree, arr, 0, n - 1);
}

int compare(const void *a, const void *b)
{
    int *arr1 = (int*)a;
    int *arr2 = (int*)b;
    return arr1 - arr2;
}


int countNodes(TreeNode *node) 
{
    if (node == NULL)
        return 0;
    return 1 + countNodes(node->Left) + countNodes(node->Right);
}

void putTreeElementsInArray(TreeNode* node, int* arr, int *index)
{
    if (node == NULL)
        return;
    putTreeElementsInArray(node->Left, arr, index);
    arr[*index] = node->key;
    (*index)++;
    putTreeElementsInArray(node->Right, arr, index);
    putTreeElementsInArray(node->Middle, arr, index);
}
#include<stdio.h>
#include<stdlib.h>
#define COUNT 10

typedef struct Node
{
    int treeNumber;
    struct Node *Left, *Right;
}TreeNode;


typedef struct Tree
{
    TreeNode *root;
}Tree;

int meniu(int n);
Tree *_createTree();
TreeNode *_createNode(int *treeNumber);
TreeNode *push(int treeNumber,  Tree *tree);
void print2DUtil(TreeNode *currentNode, int space);
int treeMaxDepth(Tree* tree);
int maxDepth(TreeNode* node);
TreeNode* searchNode(TreeNode* node, int key);
TreeNode* searchNodeKey(TreeNode* node, int key); 
int max(int a, int b);
int heightOfSubtree(TreeNode* node);
int heightOfNode(TreeNode* node);
void displayLeaves(TreeNode* node);
void clearTree(TreeNode* node);
void freeTree(Tree* tree);
void deleteTree(Tree* tree);


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
        push(0, tree);
        break;
    }

    case 2:
    {
        if (tree->root == NULL)
            printf("The tree is empty\n");
        else
        {
            TreeNode *currentNode = tree->root;
            print2DUtil(currentNode, 0);
        }
        break;
    }
    
    case 3:
        printf("The depth of tree is %d", treeMaxDepth(tree));
    break;

    case 4:
    {
        int key;
        if (tree->root == NULL)
            printf("The tree is empty\n");
        else
        {
            printf("Insert the key of node: ");
            scanf("%d", &key);
            searchNode(tree->root, key);
        }
        break;    
    }

    case 5:
    {
        int key;
            if (tree->root == NULL)
                printf("The tree is empty\n");
            else
            {
                printf("Insert the key of node: ");
                scanf("%d", &key);
                printf("The depth of tree is %d from the key %d", maxDepth(searchNodeKey(tree->root, key)), key);
            }
            
        break;
    }

     case 6:
    {
        int key;
            if (tree->root == NULL)
                printf("The tree is empty\n");
            else
            {
                printf("Insert the key of node: ");
                scanf("%d", &key);
                printf("The height of tree is %d from the key %d", heightOfNode(searchNodeKey(tree->root, key)), key);
            }
            
        break;
    }

    case 7:
        if (tree->root == NULL)
                printf("The tree is empty\n");
            else
                displayLeaves(tree->root);
    break; 

    case 8:
        freeTree(tree);
    break;

    case 9:
        deleteTree(tree);
        printf("The tree was deleted\n");
        scanf("%d", &n);
        exit(0);    
    break;


    default:
        break;
    }
    //todo: -1 pentru a iesi complet din arbore, 0 pentru lipsa
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
    printf("1 - Reading the elements of the tree from the keyboard\n");
    printf("2 - Displaying the elements of the tree to the console\n");
    printf("3 - Calculating the depth of the tree\n");
    printf("4 - Searching for a node based on a search key\n"); 
    printf("5 - Calculating the depth of a node (the node will be selected based on a search key)\n"); 
    printf("6 - Calculating the height of a node (the node will be selected based on a search key)\n");
    printf("7 - Displaying all the leaves of the tree\n"); 
    printf("8 - Clearing the elements of the tree\n"); 
    printf("9 - Freeing the memory of the tree\n"); 
    printf("Enter the desired option: ");
    scanf ("%d" , &n);
    printf ("\n"); 
    while (n > 9 || n < 1)
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

TreeNode *_createNode(int *treeNumber)
{
    TreeNode * node = malloc(sizeof(TreeNode));
    node->treeNumber = *treeNumber;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

TreeNode *push(int treeNumber, Tree *tree)
{
    printf("Enter data(-1 for no data):");
    scanf("%d", &treeNumber);
    if (treeNumber == -1)
        return NULL;
    TreeNode * currentNode = _createNode(&treeNumber);
    if (tree->root == NULL)
        tree->root = currentNode;
    printf("Enter left child of %d\n", treeNumber);
    currentNode->Left = push(treeNumber, tree);

    printf("Enter right child of %d\n", treeNumber);
    currentNode->Right = push(treeNumber, tree);
    return currentNode;
}

void print2DUtil(TreeNode *currentNode, int space)
{
    // Increase distance between levels
    space += COUNT;
    
    // Process right child first
    if (currentNode->Right)
        print2DUtil(currentNode->Right, space); 
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", currentNode->treeNumber);
 
    // Process left child
    if (currentNode->Left)
        print2DUtil(currentNode->Left, space);    
}

int maxDepth(TreeNode* node) 
{
    if (node == NULL) 
        // Base case: the depth of an empty tree is 0
        return 0;
    else
    {
        // Recursive case: the maximum depth of a non-empty tree is 1 + the maximum depth of its subtrees
        int leftDepth = maxDepth(node->Left);
        int rightDepth = maxDepth(node->Right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }
}

// Function to calculate the maximum depth of a binary tree represented by a Tree structure
int treeMaxDepth(Tree* tree) 
{
    if (tree == NULL || tree->root == NULL)
        // Base case: the depth of an empty tree is 0
        return 0;
    else
        // Recursive case: the maximum depth of a non-empty tree is 1 + the maximum depth of its subtrees
        return maxDepth(tree->root);
}

// Function to search for a node in a binary tree based on a search key
TreeNode* searchNode(TreeNode* node, int key) 
{
    if (node == NULL)
    {
        printf("The node with this key was not found!\n");  
        return NULL;
    }  
    if (node->treeNumber == key)
    {
        printf("The node with this key %d was found!\n", key);
        // Base case: the node is either found or the tree is empty
        return NULL;
    }
    else if (key < node->treeNumber) 
        return searchNode(node->Left, key);// Recursive case: the search key is less than the current node's value, so search the left subtree
    else
        return searchNode(node->Right, key);// Recursive case: the search key is greater than the current node's value, so search the right subtree
}


TreeNode* searchNodeKey(TreeNode* node, int key) 
{
    if (node == NULL)
    {
        printf("The node with this key was not found!\n");  
        return NULL;
    }  
    if (node->treeNumber == key)
    {
        // Base case: the node is either found or the tree is empty
        return node;
    }
    else if (key < node->treeNumber) 
        return searchNodeKey(node->Left, key);// Recursive case: the search key is less than the current node's value, so search the left subtree
    else
        return searchNodeKey(node->Right, key);// Recursive case: the search key is greater than the current node's value, so search the right subtree
}

// Function to calculate the height of a node in a binary tree based on a search key
int heightOfNode(TreeNode* node) 
{
    // Search for the node with the given key in the binary tree
    if (node == NULL) 
    {
        // The node with the given key was not found
        return -1;
    } else 
    {
        // Calculate the height of the node using recursion
        int leftSubtreeHeight = heightOfSubtree(node->Left);
        int rightSubtreeHeight = heightOfSubtree(node->Right);
        return 1 + max(leftSubtreeHeight, rightSubtreeHeight);
    }
}

// Helper function to calculate the height of a subtree
int heightOfSubtree(TreeNode* node) 
{
    if (node == NULL) 
    {
        // The height of an empty subtree is -1
        return -1;
    } else 
    {
        // Calculate the height of the subtree using recursion
        int leftSubtreeHeight = heightOfSubtree(node->Left);
        int rightSubtreeHeight = heightOfSubtree(node->Right);
        return 1 + max(leftSubtreeHeight, rightSubtreeHeight);
    }
}

// Helper function to calculate the maximum of two integers
int max(int a, int b) 
{
    return (a > b) ? a : b;
}

// Function to display all the leaf nodes in a binary tree
void displayLeaves(TreeNode* node) 
{
    if (node == NULL) 
        return;
    if (node->Left == NULL && node->Right == NULL) 
        printf("%d ", node->treeNumber);
    displayLeaves(node->Left);
    displayLeaves(node->Right);
}

// Function to clear all the nodes in a binary tree
void clearTree(TreeNode* node) 
{
    if (node == NULL)
        return;
    clearTree(node->Left);
    clearTree(node->Right);
    printf("Deleteing Node : %d\n", node->treeNumber);
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
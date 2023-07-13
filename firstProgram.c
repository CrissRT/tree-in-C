#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node
{
    char *pacient, *disease;
    unsigned short age;
    int key;
    struct Node *Left, *Right;
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
TreeNode *_createNode(int *key, char *pacient, unsigned short *age, char *disease);
TreeNode *push(Tree *tree);
void printTree(TreeNode *currentNode);
TreeNode* searchNode(TreeNode* node, int key);
void clearTree(TreeNode* node);
void freeTree(Tree* tree);
void deleteTree(Tree* tree);
void inorderTraversal(TreeNode *root);
void displayTreeNode(TreeNode *currentNode);
void preorderTraversal(TreeNode *root);
int height(TreeNode *node);
int balance_factor(TreeNode *node);
void rotate_left(TreeNode *node_ptr);
void rotate_right(TreeNode *node_ptr);
void rotate_right(TreeNode *node_ptr);
void balance_tree_helper(TreeNode *node_ptr);
void balance_tree(Tree *tree);
void postorderTraversal(TreeNode *root);
void mirrorTree(TreeNode * node);
void launchMirrorTree(Tree *tree);
void dfs(TreeNode* node);
Queue* createQueue();
void enqueue(Queue* queue, TreeNode* data);
TreeNode* dequeue(Queue* queue);
void destroyQueue(Queue* queue);
void bfs(Tree *tree);


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

    case 3:
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

    case 4:
    {
        if (tree->root == NULL)
            printf("The tree is empty\n");
        else
        {    
            printf("Inorder traversal\n");
            inorderTraversal(tree->root);
        }   
        break;
    }   

    case 5:
         if (tree->root == NULL)
            printf("The tree is empty\n");
        else
        {    
            printf("Preorder traversal\n");
            preorderTraversal(tree->root);
        }   
    break;

    case 6:
         if (tree->root == NULL)
            printf("The tree is empty\n");
        else
        {    
            printf("Postorder traversal\n");
            postorderTraversal(tree->root);
        }   
    break;

    case 7:
         if (tree->root == NULL)
            printf("The tree is empty\n");
        else    
        {
            printf("DFS traversal:\n");
            dfs(tree->root); 
        } 
    break;

    case 8:
        if (tree->root == NULL)
            printf("The tree is empty\n");
        else    
        {
            printf("BFS traversal:\n");
            bfs(tree);
        }
    break;
    case 9:
    {
        if (tree->root == NULL)
            printf("The tree is empty\n");
        else
            balance_tree(tree);
        break;
    }

    case 10:
    {
        if (tree->root == NULL)
            printf("The tree is empty\n");
        else
            launchMirrorTree(tree);
        break;
    }

    case 11:
        freeTree(tree);
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

int height(TreeNode *node)
{
    if (node == NULL)
        return 0;
    int left_height = height(node->Left);
    int right_height = height(node->Right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

int balance_factor(TreeNode *node) 
{
    if (node == NULL)
        return 0;
    int left_height = height(node->Left);
    int right_height = height(node->Right);
    return left_height - right_height;
}

void rotate_left(TreeNode *node_ptr)
{
    TreeNode *pivot = node_ptr;
    TreeNode *new_root = pivot->Right;
    pivot->Right = new_root->Left;
    new_root->Left = pivot;
    node_ptr = new_root;
}

void rotate_right(TreeNode *node_ptr)
{
    TreeNode *pivot = node_ptr;
    TreeNode *new_root = pivot->Left;
    pivot->Left = new_root->Right;
    new_root->Right = pivot;
    node_ptr = new_root;
}

void balance_tree_helper(TreeNode *node_ptr) 
{
    if (node_ptr == NULL)
        return;
    int bf = balance_factor(node_ptr);
    if (bf > 1) 
    {
        if (balance_factor((node_ptr)->Left) < 0)
            rotate_left(node_ptr->Left);

        rotate_right(node_ptr);
    } else if (bf < -1) 
    {
        if (balance_factor(node_ptr->Right) > 0) 
            rotate_right(node_ptr->Right);
        rotate_left(node_ptr);
    }
    balance_tree_helper(node_ptr->Left);
    balance_tree_helper(node_ptr->Right);
}

void balance_tree(Tree *tree) 
{
    balance_tree_helper(tree->root);
    printf("The tree is balanced\n");
}


int meniu(int n)
{
    printf ("The meniu:\n"); 
    printf("1 - Reading tree elements from keyboard\n");
    printf("2 - Displaying tree elements to console\n");
    printf("3 - Searching a node based on key field and displaying the fields of the found node\n");
    printf("4 - Traversing the tree in inorder\n");
    printf("5 - Traversing the tree in preorder\n");
    printf("6 - Traversing the tree in postorder\n");
    printf("7 - Traversing the tree in depth-first search (DFS)\n");
    printf("8 - Traversing the tree in breadth-first search (BFS)\n");
    printf("9 - Balancing the tree\n");
    printf("10 - Mirroring the tree\n");
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

TreeNode *_createNode(int *key, char *pacient, unsigned short *age, char *disease)
{
    TreeNode * node = malloc(sizeof(TreeNode));
    node->key = *key;
    node->pacient = strdup(pacient);
    node->age = *age;
    node->disease = strdup(disease);
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

TreeNode *push(Tree *tree)
{
    int key;
    printf("Enter key(-1 for no data):");
    scanf("%d", &key);
    if (key <= -1 )
        return NULL;
    char pacient[50], disease[50];
    unsigned short age;
    printf("Enter pacient's full name: ");
    scanf(" %[^\n]s", pacient);
    printf("Enter pacient's age: ");
    scanf(" %hu", &age);
    printf("Enter pacient's disease: ");
    scanf(" %[^\n]s", disease);
    printf("Enter left child of %d\n", key);
    TreeNode * currentNode = _createNode(&key, pacient, &age, disease);
    if (tree->root == NULL)
        tree->root = currentNode;
    currentNode->Left = push(tree);
    printf("Enter right child of %d\n", key);
    currentNode->Right = push(tree);
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
}

void displayTreeNode(TreeNode *currentNode)
{   
    printf("Key: %d\n", currentNode->key);
    printf("Pacient's full name: %s\n", currentNode->pacient);
    printf("Pacient's age: %hu\n", currentNode->age);
    printf("Pacient's disease: %s\n\n", currentNode->disease);
}

void inorderTraversal(TreeNode *root) 
{
    if (root == NULL)
        return;
    if (root->Left)
        inorderTraversal(root->Left);
    displayTreeNode(root);
    if (root->Right)
        inorderTraversal(root->Right);
}

void preorderTraversal(TreeNode *root) 
{
    if (root == NULL)
        return;
    displayTreeNode(root);
    if (root->Left)
        preorderTraversal(root->Left);
    if (root->Right)
        preorderTraversal(root->Right);
}

void postorderTraversal(TreeNode *root) 
{
    if (root == NULL)
        return;
    if (root->Left)
        postorderTraversal(root->Left);
    if (root->Right)
        postorderTraversal(root->Right);
    displayTreeNode(root);
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
        // Base case: the node is either found or the tree is empty
        return NULL;
    }
    else if (key < node->key) 
        return searchNode(node->Left, key);// Recursive case: the search key is less than the current node's value, so search the left subtree
    else
        return searchNode(node->Right, key);// Recursive case: the search key is greater than the current node's value, so search the right subtree
}

// Function to clear all the nodes in a binary tree
void clearTree(TreeNode* node) 
{
    if (node == NULL)
        return;
    clearTree(node->Left);
    clearTree(node->Right);
    printf("Deleteing Node : %d\n", node->key);
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


void mirrorTree(TreeNode * node) 
{
  if (node!=NULL)
  {
    TreeNode* temp;

    /* do the subtrees */
    mirrorTree(node->Left);
    mirrorTree(node->Right);

    /* swap the pointers in this node */
    temp = node->Left;
    node->Left  = node->Right;
    node->Right = temp;
  }
} 
void launchMirrorTree(Tree *tree)
{
    mirrorTree(tree->root);
    printf("Tree was mirrored successfully\n");
}

void dfs(TreeNode* node) 
{
    if (node == NULL)
        return;
    displayTreeNode(node);

    dfs(node->Left);
    dfs(node->Right);
}

Queue* createQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, TreeNode* data)
{
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

TreeNode* dequeue(Queue* queue)
{
    if (queue->front == NULL) {
        return NULL;
    }

    QueueNode* temp = queue->front;
    TreeNode* data = temp->data;

    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return data;
}

int isEmpty(Queue* queue)
{
    return queue->front == NULL;
}

void destroyQueue(Queue* queue)
{
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}


void bfs(Tree *tree)
{
    if (tree->root == NULL) 
    {
        printf("Tree is empty\n");
        return;
    }

    Queue *queue = createQueue();
    enqueue(queue, tree->root);

    while (!isEmpty(queue)) {
        TreeNode *node = dequeue(queue);
        displayTreeNode(node);

        if (node->Left != NULL) {
            enqueue(queue, node->Left);
        }

        if (node->Right != NULL) {
            enqueue(queue, node->Right);
        }
    }

    destroyQueue(queue);
}
// CSE2025 Data Structures - Project #2
// Merve Rana Kýzýl
// 150119825

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct Node
{
	int data;
	struct Node* left, * right;
};

typedef struct Node Node;

Node* newNode();
int isDuplicated(int *array, int no_of_nodes);
int actualDepthLevel(int no_of_nodes);
int askedDepthLevel(int no_of_nodes);
int depthLevelDifference(int no_of_nodes);
int getLeftHeight(Node* node);
Node* getLeftMostNode(Node* node);
void findRightMostCase2(Node* node);
void findRightMostNodeCase1(Node* node);
Node* createBST(Node* root, int i, int n);
void inOrder(Node* root);
void insertData(Node* root, int* values, int* i);
Node* deleteLeaf(Node* root, int data);
void sortArray(int* nodes, int no_of_nodes);
int getNoOfNodesInDL(Node *node, int current, int asked);
void printInfo(Node *node, int curr, int no_of_nodes);
int getDepthLevel(Node *node, int data);
void getElementOrder(Node *node, int data);

Node* newNode() {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = 0;
	node->left = NULL;
	node->right = NULL;
	return node;
}


int isDuplicated(int *array,int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (array[i] == array[j]) {
                return 1;
            }
        }
    }
    return 0;
}


int actualDepthLevel(int no_of_nodes) {
	return floor(log(no_of_nodes)/log(2)) + 1;
}


int askedDepthLevel(int no_of_nodes) {
	return 3*floor(log(no_of_nodes)/log(4));
}


int depthLevelDifference(int no_of_nodes) {
	int actual = actualDepthLevel(no_of_nodes);
	int asked = askedDepthLevel(no_of_nodes);

	if(asked >= actual)
		return asked - actual;
    else
        return -1;
}


int getLeftHeight(Node* node) {
    int h = 0;
    while(node){
        h++;
        node = node->left;
    }
    return h;
}


Node* getLeftMostNode(Node* node){
    Node* leftmostNode;

    while(node != NULL){
        leftmostNode = node;
        node = node->left;
    }

    return leftmostNode;
}


void findRightMostCase2(Node* node){
    Node* rightmostNode;

    while(node != NULL){
        rightmostNode = node;
        node = node->right;
    }

    rightmostNode->data = -1;
}



void findRightMostNodeCase1(Node* node) {

    int h = getLeftHeight(node);

	// base case
	if(h==1){
		node->data = -1;
		return;
	}
    // node is in  rightsubtree
    else if((h-1) == getLeftHeight(node->right))
       findRightMostNodeCase1(node->right);
    // node is in  leftsubtree
    else findRightMostNodeCase1(node->left);
}


// Creates a balanced BST with empty nodes
Node* createBST(Node* root, int i, int n) {
    if (i < n)
    {
        Node* temp = newNode();
        root = temp;

        // insert left child
        root->left = createBST(root->left, 2*i + 1, n);

        // insert right child
        root->right = createBST(root->right, 2*i + 2, n);
    }
    return root;
}


void inOrder(Node* root) {
	if (root != NULL)
	{
		inOrder(root->left);
		printf("%d ", root->data);
		inOrder(root->right);
	}
}

// Fills the BST with given values
void insertData(Node* root, int* values, int* i) {
	if (root != NULL)
	{
		insertData(root->left, values, i);
		root->data=values[*i];
		insertData(root->right, values, i);
	}
	else{
		*i = *i + 1;
	}
}


// Deletes a specific leaf
Node* deleteLeaf(Node* root, int data) {
    if (root == NULL)
        return NULL;

    root->left = deleteLeaf(root->left, data);
    root->right = deleteLeaf(root->right, data);

    if (root->data == data && root->left == NULL && root->right == NULL) {
        return NULL;
    }

    return root;
}


void sortArray(int* nodes, int no_of_nodes) {
	int i, j, a;

	for (i = 0; i < no_of_nodes; ++i) {
        for (j = i + 1; j < no_of_nodes; ++j) {
            if (nodes[i] > nodes[j]) {
                a =  nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = a;
        	}
    	}
	}
}


// Returns the numbers of nodes in asked depth level
int getNoOfNodesInDL(Node *node, int current, int asked) {
    if (node == NULL)
		return 0;
    if (current == asked)
		return 1;
    return getNoOfNodesInDL(node->left,  current + 1, asked) + getNoOfNodesInDL(node->right, current + 1, asked);
}


// Prints information about number of nodes in depth levels
void printInfo(Node *node, int curr, int no_of_nodes) {

	int i;
	int last_depth_level = askedDepthLevel(no_of_nodes);

	printf("Depth level of BST is %d.\n", last_depth_level);

	for(i = 0; i < last_depth_level; i++){
		printf("Depth level %d -> %d\n", i, getNoOfNodesInDL(node, 0, i));

	}
}



// Finds the depth level of a specific node
int getDepthLevel(Node *node, int data) {

	int depthLevel = 0;

	while(node->data != data){
		// Check whether the data exist
		if(node == NULL){
			return -1;
		}

		if(data < node->data){
			node = node->left;
			if(node == NULL){
				return -1;
			}
		}
		else{
			node = node->right;
			if(node == NULL){
				return -1;
			}
		}

	depthLevel++;
	}

    return depthLevel;
}


// Return the order of a node in its depth level
void getElementOrder(Node *node, int data){

	Node* temp = node;
	int depthLevel = getDepthLevel(temp, data);

	// Check whether the data exist
	if(depthLevel == -1){
		printf("%d is not found in BST.\n", data);
		return;
	}

	int currentLevel = 1;
	int elementOrder = pow(2, depthLevel);

	while(node->data != data){

		if(data < node->data){
			node = node->left;
			elementOrder -= pow(2, depthLevel - currentLevel);
		}
		else{
			node = node->right;
		}
		currentLevel++;
	}


	if(elementOrder == 1){
		printf("At depth level %d, %dst element.\n", depthLevel, elementOrder);
	}else if(elementOrder == 2){
		printf("At depth level %d, %dnd element.\n", depthLevel, elementOrder);
	}else if(elementOrder == 3){
		printf("At depth level %d, %drd element.\n", depthLevel, elementOrder);
	}else{
		printf("At depth level %d, %dth element.\n", depthLevel, elementOrder);
	}
}



int main()
{

	FILE* file = fopen ("input.txt", "r");

	if(file == NULL){
        printf("Input file cannot be found.");
        exit(0);
	}


	int data = 0;
	int no_of_nodes = 0;
    file = fopen("input.txt","r");


    // Count the number of nodes
	while (!feof (file)) {
	  fscanf (file, "%d ", &data);
	  no_of_nodes++;
	}

	fclose (file);

	int values[no_of_nodes];
	int i = 0;

	FILE* file2 = fopen("input.txt","r");

	while (!feof (file2)) {
	    if(data <= 0){
	        printf("The given numbers cannot be less than or equal to 0.");
	        exit(0);
	    }

	     fscanf (file2, "%d ", &data);
	     values[i] = data;
	     i++;
	}

	sortArray(values, no_of_nodes);
	fclose(file2);


	if(isDuplicated(values,no_of_nodes)){
	    printf("The file cannot contain duplicated values.");

	    exit(0);
	}

	if(no_of_nodes < 16){
		printf("Number of nodes cannot be less than 16.");
		exit(0)	;
	}


	Node* root = createBST(root, 0, no_of_nodes);

    int caseNo = 1;

	// Case 2
    if(pow(2, actualDepthLevel(no_of_nodes) - 1) == no_of_nodes){
        caseNo = 2;
   	}
   	
   	


	// Arrange the nodes of the tree
	for(i = 0; i < depthLevelDifference(no_of_nodes); i++ ){
		// Find the rightmost node
		if(caseNo == 1){
            findRightMostNodeCase1(root);
		}
		else if(caseNo == 2){
            findRightMostCase2(root);
            //caseNo = 1;
		}
		

		// Find the leftmost node
		Node* leftmost = getLeftMostNode(root);
		// Delete the rightmost node
		root = deleteLeaf(root, -1);
		// Insert a new node to the leftmost node
		leftmost->left = newNode();
	}

	int index = -1;
	insertData(root, values, &index);
	printInfo(root, 0, no_of_nodes);

	// Get input from user
	while(1){

		int key;
		printf("\nKey value to be searched (Enter 0 to exit): ");
		scanf("%d", &key);

		if(key == 0){
			printf("Exit");
			break;
		}

		getElementOrder(root, key);
	}

	//inOrder(root);

	return 0;
}

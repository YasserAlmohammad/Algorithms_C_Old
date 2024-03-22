#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a,b) a>b?a:b
//define student struc
struct student{
	char fname[30];
	char lname[30];
	int id;
	int gpa;
	char major[30];
	int isInsured; //1 yes, 0 no
};

char* filename = "data.txt";
struct student students_array[100]; //( max )array to max of 100 students, the initial list of students
int student_count = 0; // (dynamic student count based on file) how many records we read from the file.

//linked list node definition
struct linkedListNode{
	struct student std;
	struct linkedListNode* next;
};

//double linked list node definition
struct doubleLinkedListNode{
	struct student std;
	struct doubleLinkedListNode* next;
	struct doubleLinkedListNode* prev;
};

//binary tree has similar definition of double linkedlist as well, however with names of left and right, so we 
//will update the definition for naming sake only.
struct binaryTreeNode{
	struct student std;
	struct binaryTreeNode* left;
	struct binaryTreeNode* right;
	int height; //to keep a balanced search tree
};

//struct linkedListNode* list; //linked list head pointer
//struct doubleLinkedListNode *doubleLinkedList; //double linked list head pointer
//linked queue has same node definition as linked list,but we define front and rear pointers.
//struct linkedListNode* front,rear; //queue front and rear pointers
//doubly linked stack has same node definition as doubly linked list.
//struct doubleLinkedListNode *stackTop;  //stack top pointer
//struct binaryTreeNode* root; //binary tree pointer.

void readStudentsFile(char* filename);
void printWelcomeScreen();
void viewListMenu();
void viewDoubleLinkedListMenu();
void viewLinkedQueueMenu();
void viewDoubleLinkedStackMenu();
void viewBinaryTreeMenu();

//linked list function declaration
void createLinkedList(struct linkedListNode**);
void viewLinkedList(struct linkedListNode*);
void insertLinkedList(struct linkedListNode**,struct student);
void deleteFromLinkedList(struct linkedListNode**,int);
void deletedAllGPAEquationFromLinkedList(int);

//double linked list function declaration
void createDoublyLinkedList(struct doubleLinkedListNode**);
void viewDoublyLinkedList(struct doubleLinkedListNode*);
void insertDoublyLinkedList(struct doubleLinkedListNode**, struct student);
void deleteFromDoubleLinkedList(struct doubleLinkedListNode**,char*,char*);
void deletedUnInsuredStudents(struct doubleLinkedListNode**);

//linked queue function declaractions
void createLinkedQueueOrderedByIDAscended(struct linkedListNode** front, struct linkedListNode** rear);
void viewLinkedQueue(struct linkedListNode* front);
void enqueue(struct linkedListNode** front, struct linkedListNode** rear,struct student std);
struct student* dequeue(struct linkedListNode** front, struct linkedListNode** rear);

//double linked stack declarations
void createDoublyLinkedStackOrderedByGPAAscended(struct doubleLinkedListNode**);
void insertDoublyLinkedSortedByGPA(struct doubleLinkedListNode** top, struct student std);
void viewDoublyLinkedStack(struct doubleLinkedListNode*);
void push(struct doubleLinkedListNode**,struct student);
struct student* pop(struct doubleLinkedListNode**);

//binary tree function declarations
struct binaryTreeNode* newNode(struct student);
void createBinaryTree(struct binaryTreeNode**);
void insertIntoBinaryTree(struct binaryTreeNode** root, struct student);
void viewNamesPreOrderBinaryTree();
void viewNamesPostOrderBinaryTree();
void generateAdjMatrix();
struct binaryTreeNode * rotateRight(struct binaryTreeNode *);
struct binaryTreeNode * rotateLeft(struct binaryTreeNode *);
int getBalanceValue(struct binaryTreeNode *N);
int height(struct binaryTreeNode *N);
struct binaryTreeNode* insertBalancedTree(struct binaryTreeNode* node, struct student std);
int findStudentIndex(struct student std);
void traverseBinaryTree(struct binaryTreeNode* root, int ** adj);

//read student data from file, we assume that file is formatted in this way:
//one student data is stored in one line separated by spaces in this order:
//firstname lastname id gpa major insured   for example:
//name1 lname1 22211 77 Math 1
void readStudentsFile(char* filename){
	FILE* file = fopen(filename, "r");
	while (!feof(file)){
		struct student std;
		fscanf(file, "%s", std.fname);
		fscanf(file, "%s", std.lname);
		fscanf(file, "%d", &std.id);
		fscanf(file, "%d", &std.gpa);
		fscanf(file, "%s", std.major);
		fscanf(file, "%d", &std.isInsured);
		students_array[student_count] = std;
		student_count++;
	}
	fclose(file);
}

void printStudentArray(){
	printf("======== Student File was read into Array with Content:\n");
	for (int i = 0; i < student_count; i++){
		printf("%10s %10s %10d %5d %10s %5d\n", students_array[i].fname, students_array[i].lname, students_array[i].id, students_array[i].gpa, students_array[i].major, students_array[i].isInsured);
	}
	printf("=======================================================\n");
}

void printWelcomeScreen(){
	printf("********** CE 368, C Data Structures, Lists, Qeues, Binary Trees, Stacks **********\n");
}

//create a list from the student array
void createLinkedList(struct linkedListNode** head){
	for (int i = 0; i < student_count; i++){
		insertLinkedList(&(*head), students_array[i]);
	}
	printf("Linked List Created ...\n");
}

//print the linked list out.
void viewLinkedList(struct linkedListNode* head){
	struct linkedListNode*
		temp = head;
	printf("================== Linked list =======================\n");
	while (temp != NULL){
		printf("%10s %10s %10d %5d %10s %5d\n", temp->std.fname, temp->std.lname, temp->std.id, temp->std.gpa, temp->std.major, temp->std.isInsured);
		temp = temp->next;
	}
	printf("=======================================================\n");
}

//insert student at the begining
void insertLinkedList(struct linkedListNode** head, struct student std){
	struct linkedListNode* temp = (struct linkedListNode*)malloc(sizeof(struct linkedListNode));
	temp->next = *head;
	//temp->std = std;
	strcpy(temp->std.fname, std.fname);
	strcpy(temp->std.lname, std.lname);
	strcpy(temp->std.major, std.major);
	temp->std.id = std.id;
	temp->std.gpa = std.gpa;
	temp->std.id = std.id;
	temp->std.isInsured = std.isInsured;
	*head = temp;
}
void deleteFromLinkedList(struct linkedListNode** head,int id){
	// Store head node
	struct linkedListNode* temp = *head, *prev=*head;
	// If head node itself holds the key to be deleted
	if (temp != NULL && temp->std.id == id)
	{
		*head = temp->next;   // Changed head
		free(temp);               // free old head
		printf("student record with id [%d] was deleted from linked list\n", id);
		return;
	}
	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (temp != NULL && temp->std.id != id)
	{
		prev = temp;
		temp = temp->next;
	}
	// If key was not present in linked list
	if (temp == NULL) {
		printf("no such student in the list\n");
		return;
	}
	// Unlink the node from linked list
	prev->next = temp->next;
	free(temp);  // Free memory
	printf("student record with id [%d] was deleted from linked list\n", id);
}

//delete all records for students with GPA less than parameter
void deletedAllGPAEquationFromLinkedList(struct linkedListNode** head, int gpa){

	// If head node itself holds the key to be deleted
	while (1){
		// Store head node
		struct linkedListNode* temp = *head, *prev = *head;
		temp = *head;
		prev = temp;
		if (temp != NULL && temp->std.gpa < gpa)
		{
			*head = temp->next;   // Changed head

			printf("student record with id [%d] gpa [%d] was deleted from linked list\n", temp->std.id,temp->std.gpa);
			free(temp);               // free old head
			continue;
		}
		// Search for the key to be deleted, keep track of the
		// previous node as we need to change 'prev->next'
		while (temp != NULL && temp->std.gpa >= gpa)
		{
			prev = temp;
			temp = temp->next;
		}
		// If key was not present in linked list
		if (temp != NULL){
			prev->next = temp->next;
			printf("student record with id [%d] gpa [%d] was deleted from linked list\n", temp->std.id, temp->std.gpa);
			free(temp);  // Free memory
			
			continue; //check to see if there are more elements to delete.
		}
		if (temp == NULL)
			return; //no more elements to delete
	}
}

//double linked list function declaration
void createDoublyLinkedList(struct doubleLinkedListNode** head){
	for (int i = 0; i < student_count; i++){
		insertDoublyLinkedList(&(*head), students_array[i]);
	}
	printf("Double Linked List Created ...\n");
}
void viewDoublyLinkedList(struct doubleLinkedListNode* head){
	struct doubleLinkedListNode*temp = head;
	printf("================== Double Linked list =======================\n");
	while (temp != NULL){
		printf("%10s %10s %10d %5d %10s %5d\n", temp->std.fname, temp->std.lname, temp->std.id, temp->std.gpa, temp->std.major, temp->std.isInsured);
		temp = temp->next;
	}
	printf("=======================================================\n");	
}

//we will insert to the begining
void insertDoublyLinkedList(struct doubleLinkedListNode** head, struct student std){
	struct doubleLinkedListNode* temp = (struct doubleLinkedListNode*)malloc(sizeof(struct doubleLinkedListNode));
	temp->next = *head;
	//temp->std = std;
	strcpy(temp->std.fname, std.fname);
	strcpy(temp->std.lname, std.lname);
	strcpy(temp->std.major, std.major);
	temp->std.id = std.id;
	temp->std.gpa = std.gpa;
	temp->std.id = std.id;
	temp->std.isInsured = std.isInsured;
	temp->next = *head;  //set previous and next pointers.
	temp->prev = NULL;
	if (*head != NULL)
		(*head)->prev = temp;
	*head = temp;
}
void deleteFromDoubleLinkedList(struct doubleLinkedListNode** head, char* fname,char* lname){
	// Store head node
	struct doubleLinkedListNode* temp = *head, *prev = *head;
	// If head node itself holds the key to be deleted
	if ((temp != NULL) && (strcmp(temp->std.fname, fname) == 0) && (strcmp(temp->std.lname, lname) == 0))
	{
		*head = temp->next;   // Changed head
		if (*head != NULL) //update new head previous pointer
			(*head)->prev = NULL;
		free(temp);               // free old head
		printf("student record with name [%s %s] was deleted from double linked list\n", fname,lname);
		return;
	}
	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while ((temp != NULL) && ((strcmp(temp->std.fname, fname) != 0) || (strcmp(temp->std.lname, lname) != 0)))
	{
		prev = temp;
		temp = temp->next;
	}
	// If key was not present in linked list
	if (temp == NULL) {
		printf("no such student found in the list\n");
		return;
	}
	//delete
	prev->next = temp->next;
	if (temp->next != NULL)
		temp->next->prev = prev;
	free(temp);  // Free memory
	printf("student record with name [%s %s] was deleted from double linked list\n", fname, lname);
}

//delete all students who dont have health insurance.
void deletedUnInsuredStudents(struct doubleLinkedListNode** head){
	// Store head node
	while (1){
		struct doubleLinkedListNode* temp = *head, *prev = *head;
		// If head node itself holds the key to be deleted
		if ((temp != NULL) && (!temp->std.isInsured))
		{
			*head = temp->next;   // Changed head
			printf("student with id [%d] with no health insurance was deleted from double linked list\n",temp->std.id);
			if (*head != NULL) //update new head previous pointer
				(*head)->prev = NULL;
			free(temp);               // free old head
			continue; //check the remaining list
		}
		// Search for the key to be deleted, keep track of the
		// previous node as we need to change 'prev->next'
		while ((temp != NULL) && (temp->std.isInsured))
		{
			prev = temp;
			temp = temp->next;
		}
		// If key was not present in linked list
		if (temp == NULL)
			return;
		//delete
		printf("student with id [%d] with no health insurance was deleted from double linked list\n", temp->std.id);
		prev->next = temp->next;
		if (temp->next != NULL)
			temp->next->prev = prev;
		free(temp);  // Free memory
		
	}
}

//linked queue function declaractions
//created from student array
void createLinkedQueueOrderedByIDAscended(struct linkedListNode** front, struct linkedListNode** rear){
	for (int i = 0; i < student_count; i++){
		enqueue(&(*front), &(*rear), students_array[i]);
	}
	printf("Ordered Queue Created ...\n");
}
void viewLinkedQueue(struct linkedListNode* front){
	struct linkedListNode*temp = front;
	printf("================== Ordered Qeueu=======================\n");
	while (temp != NULL){
		printf("%10s %10s %10d %5d %10s %5d\n", temp->std.fname, temp->std.lname, temp->std.id, temp->std.gpa, temp->std.major, temp->std.isInsured);
		temp = temp->next;
	}
	printf("=======================================================\n");
}

//we use this method for priority enqueue (Add sorted)
void enqueue(struct linkedListNode** front, struct linkedListNode** rear, struct student std){
	struct linkedListNode* temp = (struct linkedListNode*)malloc(sizeof(struct linkedListNode));
	temp->next = NULL;
	//temp->std = std;
	strcpy(temp->std.fname, std.fname);
	strcpy(temp->std.lname, std.lname);
	strcpy(temp->std.major, std.major);
	temp->std.id = std.id;
	temp->std.gpa = std.gpa;
	temp->std.id = std.id;
	temp->std.isInsured = std.isInsured;
//	*head = temp;
	if (*front == NULL){  //empty queue
		*front = temp;
		*rear = temp;
		return;
	}
	if (std.id >= (*front)->std.id){ //insert at front
		temp->next = *front;
		*front = temp;
		return;
	}
	//else we search for the right place
	struct linkedListNode* t = *front;
	struct linkedListNode* prev = t;
	while ((t != NULL) && (std.id<t->std.id)){
		prev = t;
		t = t->next;
	}
	//now if t is NULL, that means we are adding our student to the end of the queue.
	if (t == NULL){
		(*rear)->next = temp;
		*rear = temp;
		return;
	}
	//else
	temp->next = t;
	prev->next = temp;
}

//dequeue a student and return a pointer to the removed record.
//so we will dequeue from the front pointer
struct student* dequeue(struct linkedListNode** front, struct linkedListNode** rear){
	if ((*front) == NULL)
		return NULL;
	struct student* std = &(*front)->std;
	if ((*front) == (*rear))
		*front = *rear = NULL;
	else
		*front = (*front)->next;
	return std;

}

//double linked stack declarations
void createDoublyLinkedStackOrderedByGPAAscended(struct doubleLinkedListNode** top){
	for (int i = 0; i < student_count; i++){
		insertDoublyLinkedSortedByGPA(&(*top), students_array[i]);
	}
	printf("Double Linked Stack Created ...\n");
}

//insert sorted into double linked stack, descending order
void insertDoublyLinkedSortedByGPA(struct doubleLinkedListNode** top,struct student std){
	struct doubleLinkedListNode* temp = (struct doubleLinkedListNode*)malloc(sizeof(struct doubleLinkedListNode));
	//temp->std = std;
	strcpy(temp->std.fname, std.fname);
	strcpy(temp->std.lname, std.lname);
	strcpy(temp->std.major, std.major);
	temp->std.id = std.id;
	temp->std.gpa = std.gpa;
	temp->std.id = std.id;
	temp->std.isInsured = std.isInsured;
	temp->next = NULL;
	temp->prev = NULL;
	if (((*top) == NULL) || ((*top)->std.gpa <= std.gpa)){
		temp->next = *top;
		*top = temp;
		return;
	}
	struct doubleLinkedListNode* ptr = *top;
	while (ptr->next != NULL && (ptr->std.gpa > std.gpa))
		ptr = ptr->next;

	if (ptr->next == NULL){
		if (ptr->std.gpa < std.gpa){
			temp->prev = ptr->prev;
			temp->next = ptr;
			ptr->prev->next = temp;
			return;
		}
	}
	temp->prev = ptr;
	temp->next = ptr->next;

	ptr->next = temp;


}
void viewDoublyLinkedStack(struct doubleLinkedListNode* top){
	struct doubleLinkedListNode* temp = top;
	printf("================== Ordered by GPA Double Linked Stack=======================\n");
	while (temp != NULL){
		printf("%10s %10s %10d %5d %10s %5d\n", temp->std.fname, temp->std.lname, temp->std.id, temp->std.gpa, temp->std.major, temp->std.isInsured);
		temp = temp->next;
	}
	printf("=======================================================\n");
}

//push the student ordered by gpa! usually push should be to top.
void push(struct doubleLinkedListNode** top, struct student std){
	insertDoublyLinkedSortedByGPA(&(*top), std);
	//
}
struct student* pop(struct doubleLinkedListNode** top){
	if ((*top)==NULL)
		return NULL;
	struct doubleLinkedListNode* temp = *top;
	(*top) = (*top)->next;
	if ((*top)!=NULL)
		(*top)->prev = NULL;
	return  &temp->std;
}


//binary tree function declarations
struct binaryTreeNode* newTreeNode(struct student std){
	struct binaryTreeNode* temp = (struct binaryTreeNode*)malloc(sizeof(struct binaryTreeNode));
		//temp->std = std;
		strcpy(temp->std.fname, std.fname);
		strcpy(temp->std.lname, std.lname);
		strcpy(temp->std.major, std.major);
		temp->std.id = std.id;
		temp->std.gpa = std.gpa;
		temp->std.id = std.id;
		temp->std.isInsured = std.isInsured;
		temp->left = NULL;
		temp->right = NULL;
		temp->height = 1; 
		return temp;
}
//create from the array of students, and left balanced binary tree
void createBinaryTree(struct binaryTreeNode** root){
	for (int i = 0; i < student_count; i++){
		*root=insertBalancedTree(*root, students_array[i]);
	}
	printf("Binary Tree was Created ...\n");
}

/*
void createBinaryTree(struct binaryTreeNode** root){
for (int i = 0; i < student_count; i++){
insertIntoBinaryTree(&(*root), students_array[i]);
}
printf("Binary Tree was Created ...\n");
}
*/
//right rotate balanced tree to fix balance 
struct binaryTreeNode *rotateRight(struct binaryTreeNode *y)
{
	struct binaryTreeNode *x = y->left;
	struct binaryTreeNode *z = x->right;

	// Perform rotation
	x->right = y;
	y->left = z;

	// Update heights
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	// Return new root
	return x;
}

// left rotate subtree rooted with x
struct binaryTreeNode *rotateLeft(struct binaryTreeNode *x)
{
	struct binaryTreeNode *y = x->right;
	struct binaryTreeNode *z = y->left;

	//  rotation
	y->left = x;
	x->right = z;

	//  Update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y; //new root
}

//get height of the tree
int height(struct binaryTreeNode *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

// Get Balance value of node N
int getBalanceValue(struct binaryTreeNode *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
// Recursive function to insert key in subtree rooted
// with node and returns new root of subtree.
struct binaryTreeNode* insertBalancedTree(struct binaryTreeNode* node, struct student std)
{
	// normal  insertion 
	if (node == NULL)
		return(newTreeNode(std));

	if (strcmp(std.fname,node->std.fname) < 0)
		node->left = insertBalancedTree(node->left, std);
	else if (strcmp(std.fname, node->std.fname)>0)
		node->right = insertBalancedTree(node->right, std);
	else // no equal keys allowed
		return node;

	// Update height of this ancestor node 
	node->height = 1 + max(height(node->left),
		height(node->right));

	// Get the balance factor of this ancestor and check if node became unbalanced
	int balance = getBalanceValue(node);

	// If this node becomes unbalanced, then
	// there are 4 cases
	// Left Left 
	if (balance > 1 && (strcmp(std.fname, node->left->std.fname)<0))
		return rotateRight(node);

	// Right Right 
	if (balance < -1 && (strcmp(std.fname, node->right->std.fname)>0))
		return rotateLeft(node);

	// Left Right 
	if (balance > 1 && (strcmp(std.fname, node->left->std.fname)>0))
	{
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}

	// Right Left 
	if (balance < -1 && (strcmp(std.fname, node->right->std.fname)<0))
	{
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}

	return node;
}
/*
//insert into binary tree, sorting using name
void insertIntoBinaryTree(struct binaryTreeNode** root, struct student std){
	if ((*root) == NULL){
		*root = newTreeNode(std);
		return;
	}
	if (strcmp(std.fname,(*root)->std.fname)<=0) //go left
		insertIntoBinaryTree(&(*root)->left, std);
	else
		insertIntoBinaryTree(&(*root)->right, std);
}
*/
//this will print preorder, so print the current, then left, then right, thus it will print out sorted
void viewNamesPreOrderBinaryTree(struct binaryTreeNode* root){
	if (root == NULL)
		return;
	printf("[%s %s] \n", root->std.fname, root->std.lname);
	viewNamesPreOrderBinaryTree(root->left);
	viewNamesPreOrderBinaryTree(root->right);
}

//post order: prints  left then right sub trees before printing the current node
void viewNamesPostOrderBinaryTree(struct binaryTreeNode* root){
	if (root == NULL)
		return;
	viewNamesPostOrderBinaryTree(root->left);
	viewNamesPostOrderBinaryTree(root->right);
	printf("[%s %s] \n", root->std.fname, root->std.lname);
}

//adjacency matrix for NxN matric, such as N is number of student records in the binary tree
// a[i,j]=1 if there is a connection between i student and j student
//what we do is we travernse the three and connect current node with the left and right nodes.
//we use auxiliary function to find the index of a student in the student array.
void generateAdjMatrix(struct binaryTreeNode* root){
	//first we define a 2d array with nxn size
	int** array = (int**)malloc(student_count*sizeof(int*));
	for (int i = 0; i < student_count;i++)
		array[i] = (int*)malloc(student_count*sizeof(int));
	for (int i = 0; i < student_count; i++){
		for (int j = 0; j < student_count; j++){
			array[i][j] = 0;
		}
	}
	traverseBinaryTree(root, array);
	printf("\nadjacency matrix generated from the binary tree:\n");
	for (int i = 0; i < student_count; i++){
		for (int j = 0; j < student_count; j++){
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
}
//auxiliary function for the adjacency matrix creation, find index of current student in the students array
int findStudentIndex(struct student std){
	for (int i = 0; i < student_count; i++){
		if (students_array[i].id == std.id)
			return i;
	}
}

//auxiliary traverse function for the adjacency matrix
void traverseBinaryTree(struct binaryTreeNode* root,int ** adj){
	if (root == NULL)
		return;
	if (root->left != NULL){
		int x = findStudentIndex(root->std);
		int y = findStudentIndex(root->left->std);
		adj[x][y] = 1;

		traverseBinaryTree(root->left,adj);
	}
	if (root->right != NULL){
		int x = findStudentIndex(root->std);
		int y = findStudentIndex(root->right->std);
		adj[x][y] = 1;
		traverseBinaryTree(root->right, adj);
	}
	
}

void viewListMenu(){
	struct linkedListNode* head=NULL;
	int option = 1;
	while (option != 0)
	{
		printf("\n***LIST MENU *** \n");
		printf("0: Return To Main Menu\n");
		printf("1: Create a Linked List of all students.\n");
		printf("2: View the linked list\n");
		printf("3: Insert New Student\n");
		printf("4: Delete a student with specific ID.\n");
		printf("5: Delete all student with GPA less than the GPA entered by the user.\n");
		printf("input a choice:");
		scanf("%d", &option);
		switch (option){
		case 0:
			printf("Returning to Main Menu...\n");

			break;
		case 1:
			createLinkedList(&head);
			break;
		case 2:
			viewLinkedList(head);
			break;
		case 3:
			fflush(stdin);
			struct student std;
			printf("input first name:");
			scanf("%s", std.fname);
			printf("input last name:");
			scanf("%s", std.lname);
			printf("input id:");
			scanf("%d", &std.id);
			printf("input GPA:");
			scanf("%d", &std.gpa);
			printf("input major:");
			scanf("%s", std.major);
			printf("input insurance status (1 for insured) (0 for uninsured):");
			scanf("%d", &std.isInsured);

			insertLinkedList(&head,std);
			break;
		case 4:
			fflush(stdin);
			int id;
			printf("input student id:");
			scanf("%d", &id);
			deleteFromLinkedList(&head,id);
			break;
		case 5:
			fflush(stdin);
			int gpa;
			printf("input GPA:");
			scanf("%d", &gpa);
			deletedAllGPAEquationFromLinkedList(&head,gpa);
			break;
		default:
			printf("Wrong Input (choose 0..5)\n");
			break;
		}
	}

	//free memory
	return;
}

void viewDoubleLinkedListMenu(){
	struct doubleLinkedListNode* head = NULL;
	int option = 1;
	while (option != 0)
	{
		printf("\n***Doubly Linked LIST MENU ***\n");
		printf("0: Return To Main Menu\n");
		printf("1: Create a Doubly Linked List of all students.\n");
		printf("2: View the Doubly Linked List.\n");
		printf("3: Insert New Student\n");
		printf("4: Delete a student whose name is specified by the user.\n");
		printf("5: Delete all students that don’t have health insurance.\n");
		printf("input a choice:");
		scanf("%d", &option);
		switch (option){
		case 0:
			printf("Returning to Main Menu...\n");
			break;
		case 1:
			createDoublyLinkedList(&head);
			break;
		case 2:
			viewDoublyLinkedList(head);
			break;
		case 3:
			fflush(stdin);
			struct student std;
			printf("input first name:");
			scanf("%s", std.fname);
			printf("input last name:");
			scanf("%s", std.lname);
			printf("input id:");
			scanf("%d", &std.id);
			printf("input GPA:");
			scanf("%d", &std.gpa);
			printf("input major:");
			scanf("%s", std.major);
			printf("input insurance status (1 for insured) (0 for uninsured):");
			scanf("%d", &std.isInsured);

			insertDoublyLinkedList(&head,std);
			break;
		case 4:
			fflush(stdin);
			char fname[30];
			char lname[30];
			printf("input student first name:");
			scanf("%s", fname);
			printf("input student last name:");
			scanf("%s", lname);

			deleteFromDoubleLinkedList(&head,fname,lname);
			break;
		case 5:
			deletedUnInsuredStudents(&head);
			break;
		default:
			printf("Wrong Input (choose 0..5)\n");
			break;
		}
	}

	//free memory
	return;
}

//display all queue options
void viewLinkedQueueMenu(){
	int option = 1;
	struct linkedListNode* front=NULL, *rear=NULL;
	struct student *e;
	while (option != 0)
	{
		printf("\n***Linked Queue MENU ***\n");
		printf("0: Return To Main Menu\n");
		printf("1: Create a Linked Queue of all students from the highest ID to the lowest.\n");
		printf("2: View the Linked Queue.\n");
		printf("3: Enqueue.\n");
		printf("4: Dequeue.\n");
		printf("input a choice:");
		scanf("%d", &option);
		switch (option){
		case 0:
			printf("Returning to Main Menu...\n");

			break;
		case 1:
			createLinkedQueueOrderedByIDAscended(&front,&rear);
			break;
		case 2:
			viewLinkedQueue(front);
			break;
		case 3:
			fflush(stdin);
			struct student std;
			printf("input first name:");
			scanf("%s", std.fname);
			printf("input last name:");
			scanf("%s", std.lname);
			printf("input id:");
			scanf("%d", &std.id);
			printf("input GPA:");
			scanf("%d", &std.gpa);
			printf("input major:");
			scanf("%s", std.major);
			printf("input insurance status (1 for insured) (0 for uninsured):");
			scanf("%d", &std.isInsured);

			enqueue(&front,&rear,std);
			break;
		case 4:
			e=dequeue(&front,&rear);
			if (e != NULL)
				printf(" Dequeue of: %10s %10s %10d %5d %10s %5d\n", e->fname, e->lname, e->id, e->gpa, e->major, e->isInsured);
			else
				printf("no more students to dequeue\n");
		default:
			printf("Wrong Input (choose 0..4)\n");
			break;
		}
	}

	//free memory
	return;
}

void viewDoubleLinkedStackMenu(){
	int option = 1;
	struct doubleLinkedListNode* top = NULL;
	struct student* e=NULL; //element poped
	while (option != 0)
	{
		printf("\n***Doubly Linked Stack MENU ***\n");
		printf("0: Return To Main Menu\n");
		printf("1: Create a Doubly Linked Stack of all students from the highest GPA to the lowest.\n");
		printf("2: View the Doubly Linked Stack.\n");
		printf("3: Push.\n");
		printf("4: Pop.\n");
		printf("input a choice:");
		scanf("%d", &option);
		switch (option){
		case 0:
			printf("Returning to Main Menu...\n");

			break;
		case 1:
			createDoublyLinkedStackOrderedByGPAAscended(&top);
			break;
		case 2:
			viewDoublyLinkedStack(top);
			break;
		case 3:
			fflush(stdin);
			struct student std;
			printf("input first name:");
			scanf("%s", std.fname);
			printf("input last name:");
			scanf("%s", std.lname);
			printf("input id:");
			scanf("%d", &std.id);
			printf("input GPA:");
			scanf("%d", &std.gpa);
			printf("input major:");
			scanf("%s", std.major);
			printf("input insurance status (1 for insured) (0 for uninsured):");
			scanf("%d", &std.isInsured);

			push(&top,std);
			break;
		case 4:
			e = pop(&top);
			if (e != NULL)
				printf(" Dequeue of: %10s %10s %10d %5d %10s %5d\n", e->fname, e->lname, e->id, e->gpa, e->major, e->isInsured);
			else
				printf("no more students to dequeue\n");

			
		default:
			printf("Wrong Input (choose 0..5)\n");
			break;
		}
	}

	//free memory
	return;
}

void viewBinaryTreeMenu(){
	int option = 1;
	struct binaryTreeNode* root = NULL;
	while (option != 0)
	{
		printf("\n***BINARY TREE MENU ***\n");
		printf("0: Return To Main Menu\n");
		printf("1: Convert the array of Students into a balanced left justified binary tree.\n");
		printf("2: View the sequence of nodes (student names) of the binary tree in pre-order.\n");
		printf("3: View the sequence of nodes (student names) of the binary tree in post-order.\n");
		printf("4: Generate the adjacency matrix of the binary tree. \n");
		printf("input a choice:");
		scanf("%d", &option);
		switch (option){
		case 0:
			printf("Returning to Main Menu...\n");

			break;
		case 1:
			createBinaryTree(&root);
			break;
		case 2:
			viewNamesPreOrderBinaryTree(root);
			break;
		case 3:
			viewNamesPostOrderBinaryTree(root);
			break;
		case 4:
			generateAdjMatrix(root);
			break;
		default:
			printf("Wrong Input (choose 0..5)\n");
			break;
		}
	}
	//free memory
	return;
}

int main(int argc, char *argv[]){
	int option = 1;
	if (argc != 2){
		printf("You must supply file name as argument to the program");
		return 0;
	}
	filename = argv[1];  //first arg is program name, second arg is the data file data.txt
	readStudentsFile(filename);
	printWelcomeScreen();

	printStudentArray();
	
	while (option!=0)
	{
		printf("***********MAIN MENU ***********\n");
		printf("0: Exit\n");
		printf("1:Linked List Menu\n");
		printf("2:Doubly Linked List Menu\n");
		printf("3:Linked Queue Menu\n");
		printf("4:Doubly Linked Stack Menu\n");
		printf("5:Binary Tree Menu\n");
		printf("input a choice:");
		scanf("%d", &option);
		switch (option){
		case 0:
			printf("Program Exiting...\n");
			
			break;
		case 1:
			viewListMenu();
			break;
		case 2:
			viewDoubleLinkedListMenu();
			break;
		case 3:
			viewLinkedQueueMenu();
			break;
		case 4:
			viewDoubleLinkedStackMenu();
			break;
		case 5:
			viewBinaryTreeMenu();
			break;
		default:
			printf("Wrong Input (choose 0..5)\n");
			break;
		}
	}

	//free memory
	getchar();
	return 0;
}
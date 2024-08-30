#include <stdio.h>
#include <stdlib.h>

struct Node{
	struct Node *next;
	struct Node *prev;
	int val;
};

struct LinkedList{
	int len;
	struct Node *head;
	struct Node *tail;
};

struct Node* createNode(int value){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->val = value;
	newNode->next = NULL;
	return newNode;
}

struct LinkedList* createLinkedList(){
	struct LinkedList* queue = (struct LinkedList*)malloc(sizeof(struct LinkedList));
	queue->head = NULL;
	queue->tail = NULL;
	queue->len = 0;
	return queue;
}

void prepend(int value, struct LinkedList* linkedList){
	struct Node* newNode = createNode(value);

	if(linkedList->head == NULL){
		linkedList->head = linkedList-> tail = newNode;
		return;
	}

	linkedList->head->prev = newNode;
	newNode->next = linkedList->head;
	linkedList->head = newNode;
	linkedList->len++;
}

void append(int value, struct LinkedList* linkedList){
	struct Node* newNode = createNode(value);

	if(linkedList->head == NULL){
		linkedList->head = linkedList-> tail = newNode;
		return;
	}

	linkedList->tail->next = newNode;
	newNode->prev = linkedList->tail;
	linkedList->tail = newNode;
	linkedList->len++;
}

void insertAt(int value, int index, struct LinkedList* linkedList){
	if(index > linkedList->len){
		exit(0);
	}

	if(index == linkedList->len){
		append(value, linkedList);
	}

	if(index == 0){
		prepend(value, linkedList);
	}

	struct Node* current = linkedList->head;

	for(int i = 0; i < linkedList->len && current != NULL; ++i){
		current = current->next;
	}

	
	struct Node* newNode = createNode(value);
	current->prev = newNode;
	newNode->next = current;
	newNode->prev = current->prev;
	current->prev->next = newNode;

	linkedList->len++;
}

int main(int argc, char *argv[]){
	struct LinkedList* queue = createLinkedList();
	printf("%d\n", queue->head->val);
	printf("%d\n", queue->tail->val);
}

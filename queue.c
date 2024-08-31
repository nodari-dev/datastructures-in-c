#include <stdio.h>
#include <stdlib.h>

struct Node{
	struct Node *next;
	int val;
};

struct Qeue{
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

struct Qeue* createQeue(){
	struct Qeue* queue = (struct Qeue*)malloc(sizeof(struct Qeue));
	queue->head = NULL;
	queue->tail = NULL;
	queue->len = 0;
	return queue;
}

void enque(struct Qeue *queue, int value){
	struct Node* newNode = createNode(value);
	if(queue->tail == NULL){
		queue->head = queue->tail = newNode;
		return;
	}

	queue->tail->next = newNode;
	queue->tail = newNode;
}

int deque(struct Qeue *queue){
	int result;
	if(queue->head == NULL){
		printf("head was not found");
		result = -1;
	} else{
		struct Node* temp = queue->head;
		result = temp->val; 
		queue->head = queue->head->next;
		if(queue->head == NULL){
			queue->tail = NULL;
		}
		free(temp);
	}

	return result;
}

int main(int argc, char *argv[]){
	struct Qeue* queue = createQeue();
	enque(queue, 3);
	enque(queue, 2);
	enque(queue, 4);
	deque(queue);
	printf("%d\n", queue->head->val);
	printf("%d\n", queue->tail->val);
}

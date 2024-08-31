#include <stdio.h>
#include <stdlib.h>

struct Node{
	struct Node *prev;
	int val;
};

struct Stack{
	int len;
	struct Node *head;
};

struct Node* createNode(int value){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->val = value;
	newNode->prev = NULL;
	return newNode;
}

struct Stack* createStack(){
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	stack->head = NULL;
	stack->len = 0;
	return stack;
}

void push(struct Stack *stack, int value){
	struct Node* newNode = createNode(value);

	if(stack->head == NULL){
		stack->head = newNode;
		return;
	}

	newNode->prev = stack->head;
	stack->head = newNode;
}

int pop(struct Stack *stack){
	int result;
	if(stack->head == NULL){

		result = -1;
	} else{
		struct Node* head = stack->head;
		stack->head = stack->head->prev;
		result = head->val;
		free(head);
	}

	return result;
}

int main(int argc, char *argv[]){
	struct Stack* stack = createStack();
	push(stack, 1);
	push(stack, 2);
	push(stack, 3);
	printf("%d\n", pop(stack));
	printf("%d\n", pop(stack));
	printf("%d\n", pop(stack));
}

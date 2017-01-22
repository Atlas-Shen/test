/**
 * Template for stack
 * Stack implementation is a singly linked list with a header
 */

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node;
typedef struct Node *pointer_to_node;
typedef pointer_to_node Stack;

bool is_empty(Stack stack);
Stack create_stack();
void dispose_stack(Stack stack);
void make_empty(Stack stack);
void push(ElementType element, Stack stack);
ElementType top(Stack stack);
void pop(Stack stack);

struct Node {
	ElementType element;
	pointer_to_node next;
};

bool is_empty(Stack stack) {
	return stack->next == NULL;
}

Stack create_stack() {
	Stack stack;
	stack = malloc(sizeof(struct Node));
	if (stack == NULL) {
		fprintf(stderr, "Out of memory!\n");
		exit(EXIT_FAILURE);
	}
	else {
		make_empty(stack);
		return stack;
	}
}

void dispose_stack(Stack stack) {
	make_empty(stack);
	free(stack);
}

void make_empty(Stack stack) {
	if (stack == NULL) {
		fprintf(stderr, "Must use create_stack first!\n");
		exit(EXIT_FAILURE);
	}
	else
		while (!is_empty(stack)) {
			pop(stack);
		}
}

void push(ElementType element, Stack stack) {
	pointer_to_node temp_node;
	temp_node = malloc(sizeof(struct Node));
	if (temp_node == NULL) {
		fprintf(stderr, "Out of memory!\n");
		exit(EXIT_FAILURE);
	}
	else {
		temp_node->element = element;
		temp_node->next = stack->next;
		stack->next = temp_node;
	}
}

ElementType top(Stack stack) {
	if (!is_empty(stack))
		return stack->next->element;
	else {
		fprintf(stderr, "Empty stack!\n");
		exit(EXIT_FAILURE);
	}
}

void pop(Stack stack) {
	pointer_to_node first_node;
	if (is_empty(stack)) {
		fprintf(stderr, "Empty stack!\n");
		exit(EXIT_FAILURE);
	}
	else {
		first_node = stack->next;
		stack->next = stack->next->next;
		free(first_node);
	}
}

#endif // STACK_H

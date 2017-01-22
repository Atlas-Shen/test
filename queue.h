/**
 * Template for queue
 * Queue implementation is a singly linked list with a header and a tail pointer
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node;
typedef struct Node *pointer_to_node;
typedef pointer_to_node Queue;

bool is_empty(Queue queue);
Queue create_queue(Queue *tail);
void dispose_queue(Queue queue);
void make_empty(Queue queue);
Queue enqueue(ElementType element, Queue tail);
ElementType front(Queue queue);
void dequeue(Queue queue);
ElementType front_and_dequeue(Queue queue);
void print_queue(Queue queue);

/**
 * the node definition should be placed in the implementation file
 */
struct Node {
	ElementType element;
	pointer_to_node next;
};

bool is_empty(Queue queue) {
	if (queue == NULL) {
		fprintf(stderr, "Must use create_queue first!\n");
		exit(EXIT_FAILURE);
	}
	else
		return queue->next == NULL;
}

/**
 *
 * @param tail: the pointer to tail pointer, namely, the address of the tail pointer
 * @return the pointer to the header, namely, the address of the header
 */
Queue create_queue(Queue *tail) {
	Queue queue = malloc(sizeof(struct Node));
	if (queue == NULL) {
		fprintf(stderr, "Out of memory!\n");
		exit(EXIT_FAILURE);
	}
	else {
		*tail = queue;
		queue->next = NULL;
		return queue;
	}
}

void dispose_queue(Queue queue) {
	make_empty(queue);
	free(queue);
}

void make_empty(Queue queue) {
	if (queue == NULL) {
		fprintf(stderr, "Must use create_queue first!\n");
		exit(EXIT_FAILURE);
	}
	else
		while (!is_empty(queue))
			dequeue(queue);
}

/**
 *
 * @param element: the element which needs to enter the queue
 * @param tail: the tail pointer of the queue
 * @return the tail pointer after the enqueue operation
 */
Queue enqueue(ElementType element, Queue tail) {
	tail->next = malloc(sizeof(struct Node));
	if (tail->next == NULL) {
		fprintf(stderr, "Out of memory!\n");
		exit(EXIT_FAILURE);
	}
	else {
		tail = tail->next;
		tail->element = element;
		tail->next = NULL;
		return tail;
	}
}

ElementType front(Queue queue) {
	if (is_empty(queue)) {
		fprintf(stderr, "Empty queue!\n");
		exit(EXIT_FAILURE);
	}
	else
		return queue->next->element;
}

void dequeue(Queue queue) {
	if (is_empty(queue)) {
		fprintf(stderr, "Empty queue!\n");
		exit(EXIT_FAILURE);
	}
	else {
		pointer_to_node first_node = queue->next;
		queue->next = queue->next->next;
		free(first_node);
	}
}

ElementType front_and_dequeue(Queue queue) {
	if (is_empty(queue)) {
		fprintf(stderr, "Empty queue!\n");
		exit(EXIT_FAILURE);
	}
	else {
		ElementType temp_element = queue->next->element;
		pointer_to_node first_node = queue->next;
		queue->next = queue->next->next;
		free(first_node);
		return temp_element;
	}
}

/**
 * print_element needs to be implemented separately and specifically in the implementation file
 */
void print_queue(Queue queue) {
	if (is_empty(queue))
		printf("Empty queue!\n");
	else {
		queue = queue->next;
		while (queue != NULL) {
			print_element(queue->element);
			queue = queue->next;
		}
		putchar('\n');
	}
}

#endif // QUEUE_H

/**
 * Template for binary search tree
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node *Position;
typedef struct Node *BinarySearchTree;

void make_empty(BinarySearchTree tree);
Position find(ElementType element, BinarySearchTree tree);
Position find_min(BinarySearchTree tree);
Position find_max(BinarySearchTree tree);
BinarySearchTree insert(ElementType element, BinarySearchTree tree);
BinarySearchTree delete(ElementType element, BinarySearchTree tree);
BinarySearchTree delete_min(ElementType *pointer_to_element, BinarySearchTree tree);
ElementType retrieve(Position position);

/**
 * the node definition should be placed in the implementation file
 */
struct Node{
	ElementType element;
	BinarySearchTree left;
	BinarySearchTree right;
};

void make_empty(BinarySearchTree tree) {
	if (tree != NULL) {
		make_empty(tree->left);
		make_empty(tree->right);
		free(tree);
	}
}

/**
 * We'd better make sure that the tree is not empty before we apply this function
 * @return return the pointer to the found node,
 *         return NULL means there is no such element in this tree
 */
Position find(ElementType element, BinarySearchTree tree) {
	if (tree == NULL)
		return NULL;
	if (element < tree->element)
		return find(element, tree->left);
	else if(element > tree->element)
		return find(element, tree->right);
	else
		return tree;
}

/**
 * recursive version
 * @return return the pointer to the node which has the minimum key,
 *         return NULL means this tree is empty
 */
Position find_min(BinarySearchTree tree) {
	if (tree == NULL)
		return NULL;
	else if (tree->left == NULL)
		return tree;
	else
		return find_min(tree->left);
}

/**
 * recursive version
 * @return return the pointer to the node which has the maximum key,
 *         return NULL means this tree is empty
 */
Position find_max(BinarySearchTree tree) {
	if (tree == NULL)
		return NULL;
	else if (tree->right == NULL)
		return tree;
	else
		return find_max(tree->right);
}

// another version of find_max(), use iteration
// return NULL also means this tree is empty
/**
 * Position find_max(BinarySearchTree tree) {
 *     if (tree != NULL)
 *         while (tree->right != NULL)
 *             tree = tree->right;
 *     return tree;
 * }
 */

/**
 * Operate on the current node, insert the element to the tree rooted at the current node
 * @param element: element to be inserted
 * @param tree: the current node to be operated on
 * @return return the current node after the operation
 */
BinarySearchTree insert(ElementType element, BinarySearchTree tree) {
	if (tree == NULL) {
		tree = malloc(sizeof(struct Node));
		if (tree == NULL) {
			fprintf(stderr, "Out of memory!\n");
			exit(EXIT_FAILURE);
		}
		else {
			tree->element = element;
			tree->left = tree->right = NULL;
		}
	}
	else if (element < tree->element) // go left
		tree->left = insert(element, tree->left);
	else if (element > tree->element) // go right
		tree->right = insert(element, tree->right);
	// else the element is already in the tree, we will do nothing
	return tree;
}

/**
 * Operate on the current node, delete the element in the tree rooted at the current node
 * @param element: element to be deleted
 * @param tree: the current node to be operated on
 * @return return the current node after the operation
 */
BinarySearchTree delete(ElementType element, BinarySearchTree tree) {
	if (tree == NULL)
		fprintf(stderr, "Element not found!\n");
	else if (element < tree->element) // go left
		tree->left = delete(element, tree->left);
	else if (element > tree->element) // go right
		tree->right = delete(element, tree->right);
	else if (tree->left != NULL && tree->right != NULL) { // found element to be deleted and it has two children
		// replace the current node with the smallest in the right subtree
		// To avoid passing down the right subtree twice, we may need a helper method called delete_min()
		// So we only need to pass down the right subtree once
		ElementType temp_element;
		tree->right = delete_min(&temp_element, tree->right);
		tree->element = temp_element;
	}
	else { // found element to be deleted and it has one or zero children
		Position temp_node = tree;
		if (tree->left == NULL)
			tree = tree->right;
		else if (tree->right == NULL)
			tree = tree->left;
		free(temp_node);
	}
	return tree;
}

/**
 * The helper method of delete(), to improve efficiency
 * @param pointer_to_element: use the pointer to the element
 *                            to pass the value of the deleted element indirectly
 * @param tree: the current node to be operated on
 * @return return the current node after the operation
 */
BinarySearchTree delete_min(ElementType *pointer_to_element, BinarySearchTree tree) {
	if (tree == NULL)
		return NULL;
	else if (tree->left == NULL) {
		Position temp_node = tree;
		*pointer_to_element = tree->element;
		tree = tree->right;
		free(temp_node);
	}
	else {
		tree->left = delete_min(pointer_to_element, tree->left);
	}
	return tree;
}

#endif // BINARY_SEARCH_TREE_H


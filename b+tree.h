#ifndef __b_plus_tree__
#define __b_plus_tree__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_KEY 3
#define SPLITE(MAX) ((MAX / 2) + (MAX % 2))

struct b_plus_tree_node {

	bool is_leaf;
	int num_of_key;
	int key[MAX_KEY + 1];
	struct b_plus_tree_node *node_ptr[MAX_KEY + 1 + 1];
	void *page[MAX_KEY + 1 + 1];
};

typedef struct b_plus_tree_node Node;
typedef Node Root;

enum n_type { NON_LEAF = 0, LEAF = 1 };
enum n_type node_type;

//
// function
//
Root * insert(Root *root, int key);
Root * init_root(int key);
Node * find_proper_leaf(Root *root, int key, Node **parent_of_leaf);
int get_proper_index(Node *node, int key);
Node * create_node(int *key, int num_of_key, enum n_type);
Node * splite(Node *leaf);
void do_sort_in_index(Node *node, int index, int key, Node *new_node);
void simple_insert(Node *leaf, int key);
void clean_node(Node *node, int num_of_key);
int get_leaf_ptr_index(Node *parent, Node *leaf);
Node * promote(Node *parent, Node *leaf, Node *new_leaf);
Node * splite_non_leaf(Node *non_leaf);
Node * find_parent(Root *, Node *);

//
// print
//
void print_leaf(Root *root);
Node * find_first_leaf(Root *root);

#endif

#ifndef __b_plus_tree__
#define __b_plus_tree__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_KEY 4
#define SPLITE(MAX) ((MAX / 2) + (MAX % 2))

enum n_type { NON_LEAF = 0, LEAF = 1 };
enum n_type node_type;

struct b_plus_tree_node {
	bool is_leaf;
	int num_of_key;
	int key[MAX_KEY + 1];
	struct b_plus_tree_node *node_ptr[MAX_KEY + 1 + 1 + 1]; // key + 1 for non-leaf, +1 for 
	void *page[MAX_KEY + 1 + 1];
};
typedef struct b_plus_tree_node Node;
typedef Node Root;
Node *target_node;

struct Queue {
	Node *element;
	struct Queue *next;
};
typedef struct Queue Q;
Q *in, *out;

//
// main
//
void init(void);
void getcmd(char *timebuf);

//
// delete
//
Root * delete(Root *, int);
Node * find_target_leaf(Root *, int);

//
// insert
//
Root * insert(Root *root, int key);
Root * init_root(int key);
Node * find_proper_leaf(Root *root, int key, Node **parent_of_leaf);
int get_proper_index(Node *node, int key);
Node * create_node(int *key, int num_of_key, enum n_type);
Node * splite(Node *leaf, enum n_type);
void do_sort_in_index(Node *node, int index, int key, Node *new_node);
void simple_insert(Node *leaf, int key);
void clean_node(Node *node, int num_of_key);
int get_leaf_ptr_index(Node *parent, Node *leaf);
Node * promote(Node *parent, Node *leaf, Node *new_leaf);
Node * find_parent(Root *, Node *);
Node * find_first_leaf(Root *root);

//
// print
//
void enqueue(Node *);
Node * dequeue(void);
void print_usage(Root *, int *);
void print(Root *);
void print_leaf(Root *);

//
// for dot file
//
#define MAX_LEVEL 10
#define MAX_CHILD 100
int child[MAX_LEVEL];
int *child_node[MAX_LEVEL][MAX_CHILD];
void create_dot_file(Root *);

#endif

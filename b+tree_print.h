#ifndef __b_plus_tree_print__
#define __b_plus_tree_print__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

struct Queue {
	Node *element;
	struct Queue *next;
};
typedef struct Queue Q;
Q *in, *out;

void enqueue(Node *);
Node * dequeue(void);
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

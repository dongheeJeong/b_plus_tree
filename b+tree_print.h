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

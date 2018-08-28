#include "b+tree.h"
#include "b+tree_print.h"

void enqueue(Node *element)
{
	if(element == NULL)
		return ;

	Q *node = malloc(sizeof(Q));
	node->element = element;
	node->next = in;
	in = node;

	if(out == NULL)
		out = node;
}

Node * dequeue(void)
{
	Node *ret = NULL;
	Q *tmp;

	if(in == NULL && out == NULL) {
		printf("queue empty !!\n");
		exit(1);
	}
			
	if(out != NULL) {
  		ret = out->element;
		free(out);

		tmp = in;
		if(in != out) 
			while(tmp->next != out)
				tmp = tmp->next;	

		tmp->next = NULL;

		if(in == out)
			in = NULL;
		out = NULL;
	}

	if(in == NULL)
		return ret;

	out = in;
	while(out->next != NULL) 
		out = out->next;

	return ret;
}

void print(Root *root) 
{
	int i;
	Node *node;

	enqueue(root);

	while(in != NULL && out != NULL) {
		node = dequeue();

		for(i = 0; i < node->num_of_key+1; i++) 
			enqueue(node->node_ptr[i]);

		for(i = 0; i < node->num_of_key; i++)
			printf("%d, ", node->key[i]);
		printf("\n");
	}
}

void print_leaf(Root *root)
{
	int i;
	Node *leaf = find_first_leaf(root);

	while(leaf != NULL) {
		for(i = 0; i < leaf->num_of_key; i++)
			printf("%d ", leaf->key[i]);

		printf("--> ");
		leaf = leaf->node_ptr[MAX_KEY + 1];
	}
	printf("\n");
}

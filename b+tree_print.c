#include "b+tree_insert.h"
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

void create_dot_file(Root *root)
{
	int fd, i;
	Node *node;
	const char *fname = "b_plus_tree.dot";
	const char *dot_file_prefix = "digraph G {\n\tgraph [dpi = 300];\n\tnode    [style =     filled];\n\tedge   [color = red];\n\tcolor = red;\n\n";

	if((fd = open(fname, O_CREAT|O_RDWR|O_TRUNC, 0644)) < 0) {
		fprintf(stderr, "open %s error\n", fname);
		exit(1);
	}

	write(fd, (void*) dot_file_prefix, strlen(dot_file_prefix));

	//
	/* root is always 1 node */
	//
	int level = 0, level_node = 1, next_level_node = 0, index = 0;
	char ind[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j', 'k',	\
					 'l', 'm', 'n', 'o', 'p', 'q', 'r', 'x', 'y', 'z' };
	const char *node_str = "\tnode", *label_str = " [label = ";
	char str[256], ind_str[3];



	enqueue(root);

	while(in != NULL && out != NULL) {
		node = dequeue();
		strncpy(str, node_str, strlen(node_str));
		str[strlen(node_str)] = '\0';

		sprintf(ind_str, "%02d", level);
		strncat(str, ind_str, strlen(ind_str));

		strncat(str, &ind[index], 1);
		strncat(str, label_str, strlen(label_str));

		for(i = 0; i < node->num_of_key; i++) {
			if(i == 0 && node->num_of_key == 1)
				sprintf(ind_str, "\"%d\"", node->key[i]);
			else if(i == 0)
				sprintf(ind_str, "\"%d, ", node->key[i]);
			else if(i > 0 && i < node->num_of_key -1)
				sprintf(ind_str, "%d, ", node->key[i]);
			else 
				sprintf(ind_str, "%d\"", node->key[i]);

			strncat(str, ind_str, strlen(ind_str));
		}
		strncat(str, "];\n", 3);
		write(fd, str, strlen(str));

		for(i = 0; i < node->num_of_key+1; i++) 
			enqueue(node->node_ptr[i]);

		child_node[level][index] = &node->num_of_key;
		index++;
		next_level_node += node->num_of_key + 1;
		if(--level_node == 0) {
			level_node = next_level_node;
			child[level] = level_node;
			level++;
			next_level_node = 0;
			index = 0;
			write(fd, "\n", 1);
		}
	}

	level--;
	int new_level, index_before = 0, index_after = 0, tmp = 0;

	for(new_level = 0; new_level < level; index_after++, tmp++) {
		if(child[new_level] == index_after) {
			if(++new_level == level)
				break;
			index_before = 0;
			index_after = 0;
			tmp = 0;
		}

		if(*child_node[new_level][index_before] + 1 == tmp) {
			tmp = 0;
			index_before++;
		}

		/* before */
		strncpy(str, "\t\"node", 6);
		str[6] = '\0';
		sprintf(ind_str, "%02d", new_level);
		strncat(str, ind_str, strlen(str));
		strncat(str, &ind[index_before], 1);
		strncat(str, "\"", 1);

		/* direction */
		strncat(str, " -> ", 4);

		/* after  */
		strncat(str, "\"node", 5);
		sprintf(ind_str, "%02d", new_level + 1);
		strncat(str, ind_str, strlen(ind_str));
		strncat(str, &ind[index_after], 1);
		strncat(str, "\"\n", 2);
		write(fd, str, strlen(str));
	}

	write(fd, "}", 1);
	close(fd);
}














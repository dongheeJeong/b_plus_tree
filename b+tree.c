#include "b+tree.h"

Root *insert(Root *root, int key)
{
	if(root == NULL) 
		return init_root(key);

	int new_root_flag = 0;
	Node *leaf, *parent_leaf = NULL, *new_leaf, *new_root, *new_non_leaf;

   	leaf = find_proper_leaf(root, key, &parent_leaf);

	/* simple case, enough space for inserting a new key in leaf node  */
	if(leaf->num_of_key < MAX_KEY) {
		simple_insert(leaf, key);
	}
	else if(leaf->num_of_key == MAX_KEY
			&& parent_leaf == NULL) {
		new_root_flag = 1;
		simple_insert(leaf, key);
		new_leaf = splite(leaf);
		new_root = promote(parent_leaf, leaf, new_leaf);
	}
	/* leaf-overflow only case  */
	else if(leaf->num_of_key == MAX_KEY 
			&& parent_leaf != NULL 
			&& parent_leaf->num_of_key < MAX_KEY) {
		simple_insert(leaf, key);
		new_leaf = splite(leaf);
		promote(parent_leaf, leaf, new_leaf);
	}
	/* non-leaf-overflow  */
	else if(leaf->num_of_key == MAX_KEY
			&& parent_leaf != NULL
			&& parent_leaf->num_of_key == MAX_KEY) {

		simple_insert(leaf, key);
		new_leaf = splite(leaf);
		promote(parent_leaf, leaf, new_leaf);

		new_non_leaf = splite_non_leaf(parent_leaf);

		Node *parent_of_parent = find_parent(root, parent_leaf);
		if(parent_of_parent == NULL) 
			new_root_flag = 1;
		new_root = promote(parent_of_parent, parent_leaf, new_non_leaf);
	}

	return new_root_flag == 1? new_root : root;
}

Root *init_root(int key)
{
	node_type = LEAF;
	return create_node(&key, 1, node_type);	
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

Node *find_first_leaf(Root *root)
{
	Node *leaf;

	if(root->is_leaf == true)
		return root;
	else
		leaf = find_first_leaf(root->node_ptr[0]);

	return leaf;
}

/* parent_of_leaf will NULL if key is in root  */
Node * find_proper_leaf(Root *root, int key, Node **parent_of_leaf)
{
	int index;
	Node *node = root;

	while(node->is_leaf == false) {
		index = get_proper_index(node, key);

		*parent_of_leaf = node;
		node = node->node_ptr[index];
	}

	return node;
}

int get_proper_index(Node *node, int key)
{
	int i;
	for(i = 0; i < node->num_of_key; i++) {
		if(key < node->key[i])
			break;
	}

	return i;
}

Node * create_node(int *key, int num_of_key, enum n_type node_type)
{
	int i;
	Node *node = malloc(sizeof(Node));

	if(node_type == LEAF)
		node->is_leaf = true;
	else
		node->is_leaf = false;

	node->num_of_key = num_of_key;
	for(i = 0; i < MAX_KEY; i++) {
		node->key[i] = 0;
		node->page[i] = NULL;
	}

	for(i = 0; i < MAX_KEY + 1; i++) 
		node->node_ptr[i] = NULL;

	for(i = 0; i < num_of_key; i++)
		node->key[i] = key[i];

	return node;
}

/* new_leaf is made right side of leaf, which means having bigger elements */
Node * splite(Node *leaf)
{
	Node *new_leaf;
	node_type = LEAF;

	/* if MAX_KEY = 3, new_leaf_key = 2 and leaf_key = 2 */
	/* if MAX_KEY = 4, new_leaf_key = 2 and leaf_key = 3 */
	int new_leaf_num_key = (MAX_KEY + 1) / 2;
	int leaf_num_key = (MAX_KEY + 1) - new_leaf_num_key;

	new_leaf = create_node(&leaf->key[leaf_num_key], new_leaf_num_key, node_type);
	clean_node(leaf, leaf_num_key);
	leaf->node_ptr[MAX_KEY + 1] = new_leaf;

	return new_leaf;
}

/* insert and sort key and node_ptr  */
void do_sort_in_index(Node *node, int index, int key, Node *new_node)
{
	for(int i = node->num_of_key; i > index; i--) {
		node->key[i] = node->key[i - 1];
		node->node_ptr[i+1] = node->node_ptr[i];
	}

	node->key[index] = key;
	node->node_ptr[index+1] = new_node;
	node->num_of_key++;
}

void simple_insert(Node *leaf, int key)
{
	int index;
	index = get_proper_index(leaf, key);
	do_sort_in_index(leaf, index, key, NULL);
}

/* after splite, cut the original node */
void clean_node(Node *node, int num_of_key)
{
	for(int i = num_of_key; i < MAX_KEY+1; i++) {
		node->key[i] = 0;
		node->node_ptr[i] = NULL;
		node->page[i] = NULL;
	}
	node->node_ptr[MAX_KEY + 1] = NULL;
	node->page[MAX_KEY + 1] = NULL;

	node->num_of_key = num_of_key;
}

int get_leaf_ptr_index(Node *parent, Node *leaf)
{
	int i;
	for(i = 0; i < MAX_KEY + 1; i++) {
		if(parent->node_ptr[i] == leaf)
			break;
	}

	if(i == MAX_KEY + 1) 
		i = -1;

	return i;
}

Node * promote(Node *parent, Node *leaf, Node *new_leaf)
{
	Node *tmp;
	node_type = NON_LEAF;
	int promote_val;

	if(new_leaf->is_leaf == true)
		promote_val  = new_leaf->key[0];
	else
		promote_val = find_first_leaf(new_leaf)->key[0];

	tmp = parent;
	/* leaf == root  */
	if(tmp == NULL) {
		tmp = create_node((int *) NULL, 0, node_type);
		tmp->node_ptr[0] = leaf;
	}

	int new_leaf_index = get_leaf_ptr_index(tmp, leaf);
	do_sort_in_index(tmp, new_leaf_index, promote_val, new_leaf);

	return tmp;
}

Node * splite_non_leaf(Node *non_leaf)
{
	int new_key_num;
	Node *new_non_leaf = NULL;

	node_type = NON_LEAF;
	new_key_num = MAX_KEY - SPLITE(MAX_KEY);

	new_non_leaf = create_node(&non_leaf->key[SPLITE(MAX_KEY) + 1],	\
			new_key_num,	\
			node_type);
	for(int i = 0; i < new_key_num + 1; i++) 
		new_non_leaf->node_ptr[i] = non_leaf->node_ptr[SPLITE(MAX_KEY) + 1 + i];

	clean_node(non_leaf, SPLITE(MAX_KEY));

	return new_non_leaf;
}

Node * find_parent(Root *root, Node *node) 
{
 	Node *parent = NULL;

	if(root == NULL )
		return NULL;

	if(root->is_leaf == true)
		return NULL;

	for(int i = 0; i < root->num_of_key + 1; i++) {
		if(root->node_ptr[i] == node)
			return root;
		else
			parent = find_parent(root->node_ptr[i], node);
	}

	return parent;
}
























































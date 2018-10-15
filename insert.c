#include "b+tree.h"

Root *insert(Root *root, int key)
{
	if(root == NULL) 
		return init_root(key);

	int new_root_flag = 0;
	enum n_type leaf_t = LEAF, nleaf_t = NON_LEAF;
	Node *leaf, *parent = NULL, *new_leaf, *new_root, *new_non_leaf, *parent_of_parent;

   	leaf = find_proper_leaf(root, key, &parent);

	/* simple case, enough space for inserting a new key in leaf node  */
	if(leaf->num_of_key < MAX_KEY) {
		simple_insert(leaf, key);
	}
	else if(leaf->num_of_key == MAX_KEY
			&& parent == NULL) {
		new_root_flag = 1;
		simple_insert(leaf, key);
		new_leaf = splite(leaf, leaf_t);
		new_root = promote(parent, leaf, new_leaf);
	}
	/* leaf-overflow only case  */
	else if(leaf->num_of_key == MAX_KEY 
			&& parent != NULL 
			&& parent->num_of_key < MAX_KEY) {
		simple_insert(leaf, key);
		new_leaf = splite(leaf, leaf_t);
		promote(parent, leaf, new_leaf);
	}
	/* non-leaf-overflow  */
	else if(leaf->num_of_key == MAX_KEY
			&& parent != NULL
			&& parent->num_of_key == MAX_KEY) {

		simple_insert(leaf, key);
		new_leaf = splite(leaf, leaf_t);
		promote(parent, leaf, new_leaf);

		/* recursively check if parent is full because of promotion */
		new_root = parent;
		while(new_root->num_of_key > MAX_KEY) {
			new_non_leaf = splite(new_root, nleaf_t);
			parent_of_parent = find_parent(root, new_root);
			if(parent_of_parent == NULL) 
				new_root_flag = 1;
			new_root = promote(parent_of_parent, new_root, new_non_leaf);
		}
	}

	return new_root_flag == 1? new_root : root;
}

Root *init_root(int key)
{
	node_type = LEAF;
	return create_node(&key, 1, node_type);	
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
	for(i = 0; i < MAX_KEY + 1; i++) {
		node->key[i] = 0;
		node->page[i] = NULL;
	}

	for(i = 0; i < MAX_KEY + 3; i++) 
		node->node_ptr[i] = NULL;

	for(i = 0; i < num_of_key; i++)
		node->key[i] = key[i];

	return node;
}

/* new_leaf is made right side of leaf, which has bigger elements */
Node * splite(Node *node, enum n_type node_type)
{
	Node *new_node = NULL;

	/* if MAX_KEY = 3, node_key = 2 */
	/* if MAX_KEY = 4, node_key = 2 */
	/* if MAX_KEY = 5, node_key = 3 */
	int i, node_key = SPLITE(MAX_KEY), new_node_key;

	if(node_type == LEAF) {
		new_node_key = MAX_KEY - node_key + 1;
		new_node = create_node(&node->key[node_key], new_node_key, node_type);

		/* maintain the conections between leafs */
		new_node->node_ptr[MAX_KEY + 2] = node->node_ptr[MAX_KEY + 2];
		node->node_ptr[MAX_KEY + 2] = new_node;
	}
	else if(node_type == NON_LEAF) {
		new_node_key = MAX_KEY - node_key;
		new_node = create_node(&node->key[node_key+1], new_node_key, node_type);
		for(i = 0; i < new_node_key+1; i++)
			new_node->node_ptr[i] = node->node_ptr[node_key+1+i];
	}
	clean_node(node, node_key);

	return new_node;
}

/* insert and sort key and node_ptr  */
void do_sort_in_index(Node *node, int index, int key, Node *new_node)
{
	for(int i = node->num_of_key; i > index; i--) {
		node->key[i] = node->key[i - 1];
		node->node_ptr[i+1] = node->node_ptr[i];
	}

	node->key[index] = key;
	if(new_node != NULL)
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
	int i;
	for(i = num_of_key; i < MAX_KEY + 1; i++)
		node->key[i] = 0;

	for(i = num_of_key + 1; i < MAX_KEY + 2; i++) {
		node->node_ptr[i] = NULL;
		node->page[i] = NULL;
	}

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
		/* what is this?  */
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
























































#include "b+tree_insert.h"
#include "b+tree_delete.h"

Root * delete(Root *root, int key)
{
	Node *target_leaf = find_target_leaf(root, key);

	if(target_leaf == NULL) {
		fprintf(stderr, "no key(%d) in b+tree !\n", key);
		return root;
	}

		


	return root;		
}

/* if there is no key in b+tree, return NULL  */
Node * find_target_leaf(Root *root, int key)
{
	int i;
	Node *leaf = find_first_leaf(root);

	/* seqencial search */
	while(true) {
		if(leaf == NULL)
			break;

		for(i = 0; i < leaf->num_of_key; i++) 
			if(key == leaf->key[i])
				goto OUT;

		leaf = leaf->node_ptr[MAX_KEY+1];
	}

OUT:
	return leaf;
}







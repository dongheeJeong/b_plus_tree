#include "b+tree.h"
#include "b+tree_print.h"

int main(void)
{
	Root *root = NULL;

	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 50);
	root = insert(root, 45);
	root = insert(root, 60);
	root = insert(root, 70);
	root = insert(root, 75);
	root = insert(root, 55);
	//root = insert(root, 100);


	print_leaf(root);
	print(root);
	return 0;
}

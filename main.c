#include "b+tree.h"
#include "b+tree_print.h"

int main(void)
{
	int num = 1;
	Root *root = NULL;

	while(true) {
		printf("insert : ");
		scanf("%d", &num);
		if(num < 0)
			break;

		root = insert(root, num);
		create_dot_file(root);
		system("dot -Tpng b_plus_tree.dot -o 2.png");
	}


/*
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
	root = insert(root, 100);
	root = insert(root, 41);
	root = insert(root, 42);
	root = insert(root, 43);
	root = insert(root, 44);
	root = insert(root, 21);
	root = insert(root, 22);
	root = insert(root, 23);
	root = insert(root, 24);
	root = insert(root, 25);
	root = insert(root, 26);
	root = insert(root, 27);
	root = insert(root, 28);
*/
	/*
	for(int i = 0; i < 40; i++) 
		root = insert(root, i);
	*/

	/*
	print_leaf(root);
	print(root);
	*/
/*
	create_dot_file(root);
	system("dot -Tpng b_plus_tree.dot -o 2.png");
*/

	return 0;
}

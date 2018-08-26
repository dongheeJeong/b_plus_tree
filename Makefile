CFLAGS = -Wall -W -g
OBJS = b+tree_print.o b+tree.o main.o
TARGET = b+tree

b_plus_tree : b_plus_tree_print.o b_plus_tree.o main.o
	gcc b+tree_print.o b+tree.o main.o -o b+tree $(CFLAGS)

b_plus_tree_print.o : b+tree_print.c
	gcc -c b+tree_print.c $(CFLAGS)

b_plus_tree.o : b+tree.c
	gcc -c b+tree.c $(CFLAGS)

main.o : main.c
	gcc -c main.c $(CFLAGS)

clean :
	rm -f $(OBJS) $(TARGET)
	



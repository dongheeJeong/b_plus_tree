CFLAGS = -Wall -W -g
OBJS = b+tree_insert.o b+tree_delete.o b+tree_print.o main.o
TARGET = b+tree

b_plus_tree : insert.o delete.o print.o main.o
	gcc $(OBJS) -o b+tree $(CFLAGS)

insert.o : b+tree_insert.c
	gcc -c b+tree_insert.c $(CFLAGS)

delete.o : b+tree_delete.c
	gcc -c b+tree_delete.c $(CFLAGS)

print.o : b+tree_print.c
	gcc -c b+tree_print.c $(CFLAGS)

main.o : main.c
	gcc -c main.c $(CFLAGS)

clean :
	rm -f $(OBJS) $(TARGET)
	



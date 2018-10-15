CFLAGS = -Wall -W -g
OBJS = insert.o delete.o print.o main.o
TARGET = b+tree

b_plus_tree : insert.o delete.o print.o main.o
	gcc $(OBJS) -o b+tree $(CFLAGS)

insert.o : insert.c
	gcc -c insert.c $(CFLAGS)

delete.o : delete.c
	gcc -c delete.c $(CFLAGS)

print.o : print.c
	gcc -c print.c $(CFLAGS)

main.o : main.c
	gcc -c main.c $(CFLAGS)

clean :
	rm -f $(OBJS) $(TARGET)
	



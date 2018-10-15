#include <stdio.h>
#include "b+tree.h"

int main(void)
{
	int num = 1;
	Root *root = NULL;
	char command[BUFSIZ];

	print_usage();

	while(true) {
		printf("input : ");
		scanf("%d", &num);
		if(num < 0)
			break;

		root = insert(root, num);
		create_dot_file(root);
		getcmd(command);
		system(command);
	}

	print_leaf(root);
	print(root);

	exit(0);
}

void print_usage(void)
{
	const char *line20 = "====================";

	printf("%s%s%s%s\n", line20, line20, line20, line20);
	printf("for inserting a key, input positive key.\n");
	printf("for  deleting a key, input negative value of key.\n");
	printf("%s%s%s%s\n", line20, line20, line20, line20);
}

void getcmd(char *cmdbuf)
{
	time_t cur_time;
    struct tm *time_info;
	struct timeval usec_info;
	const char *cmd = "dot -Tpng b_plus_tree.dot -o";

    time(&cur_time);
    time_info = localtime(&cur_time);

    int year    = time_info->tm_year + 1900;
    int month   = time_info->tm_mon + 1;
    int day     = time_info->tm_mday;
    int hour    = time_info->tm_hour;
    int min     = time_info->tm_min;
    int sec     = time_info->tm_sec;

	gettimeofday(&usec_info, NULL);
	int usec	= usec_info.tv_usec;

    snprintf(cmdbuf, BUFSIZ, "%s %d-%d-%d-%02d%02d%02d%3d.png", cmd, year, month, day, hour, min, sec, usec);
	printf("%s\n", cmdbuf);
}









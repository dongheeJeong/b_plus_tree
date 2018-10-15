#include <stdio.h>
#include <dirent.h>
#include "b+tree.h"

char fname[BUFSIZ];

int main(void)
{
	int num = 1;
	Root *root = NULL;
	char command[BUFSIZ];

	init();

	while(true) {
		write(1,"\E[H\E[2J",7);
		print_usage(root, &num);
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

void init(void)
{
	DIR* dir = NULL;
	(dir = opendir("image"))? closedir(dir) : mkdir("image", 0755);
}

void getcmd(char *cmdbuf)
{
	time_t cur_time;
    struct tm *time_info;
	struct timeval usec_info;
	const char *fname_prefix = "./image/";
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

    snprintf(fname, BUFSIZ, "%d-%d-%d-%02d%02d%02d%06d.png", year, month, day, hour, min, sec, usec);
    snprintf(cmdbuf, BUFSIZ, "%s %s%s", cmd, fname_prefix, fname);

	printf("%s generated.\n", fname);
}









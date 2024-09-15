#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void read_file(const char *file_path)
{
	int fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open file");
		return;
	}

	char *line_;
	int i = 1;
	while ((line_ = get_next_line(fd)) != NULL)
	{
		//printf(":::: LINE READ AND NOT NULL\n");
		printf("%d - %s", i, line_);
		i++;
		free(line_);
	}
	close(fd);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
		return EXIT_FAILURE;
	}

	read_file(argv[1]);
	return EXIT_SUCCESS;
}

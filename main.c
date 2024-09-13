#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void read_file(const char *file_path) {
	int fd = open(file_path, O_RDONLY);
	if (fd == -1) {
		perror("Failed to open file");
		return;
	}

	char *line_;
	int i = 1;
	while ((line_ = get_next_line(fd)) != NULL) {
		//printf(":::: LINE READ AND NOT NULL\n");
		printf("%d - %s", i, line_);
		i++;
		free(line_);
	}
	close(fd);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
		return EXIT_FAILURE;
	}

	read_file(argv[1]);
	return EXIT_SUCCESS;
}

/*
   int	main(int argc, char *argv[])
   {
   if (argc != 2)
   return (-1);
//char	*file = "try1.txt";
int fd = open(argv[1], O_RDONLY);
if (fd == -1)
return (printf("Couldn't open file"), -1);
printf("File opened correctly FD: %d\n", fd);
int i = 1;
char *line = NULL;
//while (1){
line = get_next_line(fd);
if (!line)
{
printf("empty line\n");
//break;
}
printf("%d - %s\n", i++, line);
//}
if (close(fd) == -1)
{
char  *e = "error closing fd";
write(2, e, strlen(e) +1);	
}
return (0);
}
*/
//Check if line has  \n
/*for (int i = 0; i < strlen(line)+1; i++)
  {
  if (line[i] == '\n')
  printf("Has a new line here %d\n", i);
  printf("%d - %c\n", i, line[i]);
  }*/


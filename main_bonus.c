#include "get_next_line_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

// gcc -Wall -Wextra -Werror -pthread -D BUFFER_SIZE=42  get_next_line_bonus.c get_next_line_utils.c get_next_line_bonus.h main_bonus.c 
// ./a.out ../pruebas_gnl/multiple_nl.txt ../pruebas_gnl/try1.txt ../pruebas_gnl/one_line.txt 
typedef struct s_thread_data {
	int fd;
	const char *file_name;
} t_thread_data;

void *read_file(void *arg)
{
	t_thread_data *data = (t_thread_data *)arg;
	char *line_;
	int i = 1;
	pthread_t thread_id = pthread_self();

	printf("Thread %p reading from file: %s\n", (void *)thread_id, data->file_name);
	while ((line_ = get_next_line(data->fd)) != NULL)
	{
		//printf("THREAD: %p | FILE: %s - LINE: %d - %s", (void *)thread_id, data->file_name, i, line_);
		printf("FILE: %i - LINE: %d - %s", data->fd, i, line_);
		i++;
		free(line_);
		usleep(500000);
	}
	close(data->fd);
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s <file_path_1> <file_path_2> [...]\n", argv[0]);
		return EXIT_FAILURE;
	}

	int num_files = argc - 1;
	pthread_t threads[num_files];
	t_thread_data thread_data[num_files];

	for (int i = 0; i < num_files; i++)
	{
		int fd = open(argv[i + 1], O_RDONLY);
		if (fd == -1)
		{
			perror("Failed to open file");
			return EXIT_FAILURE;
		}

		thread_data[i].fd = fd;
		thread_data[i].file_name = argv[i + 1];

		if (pthread_create(&threads[i], NULL, read_file, &thread_data[i]) != 0)
		{
			perror("Failed to create thread");
			return EXIT_FAILURE;
		}
	}
	int i = 0;
	while(i < num_files)
	{
		pthread_join(threads[i], NULL);
		i++;
	}

	return EXIT_SUCCESS;
}

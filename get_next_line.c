#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	contains(const char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	print_str(const char *str)
{
	int	has_new_line = 0;
	for (size_t i = 0; i < strlen(str); i++)
	{
		if (str[i] == '\n')
		{
			printf("Has a new line at %zu\n", i);
			has_new_line = 1;
		}
		printf("%zu - %c ", i, str[i]);
	}
	printf("\n");
	return (has_new_line);
}

int	append_buff_to_line(char **line, char *buff, int bytes_read)
{
	int	len;
	char	*new_line;

	(void)bytes_read;
	//printf("\nWITHIN THE APPEND FUNC\n");
	print_str(buff);
	len = 0;
	while (buff[len])
	{
		if (buff[len] == '\n')
		{
			len++;
			break;
		}
		len++;
	}
	//printf("COMPUTED LEN OF BUFF %d\n", len);
	//printf("LENGTH OF LINE BEFORE: %zu\n", strlen(*line));
	print_str(*line);
	//SAVE COPY line before realloc OR YOU'LL LOSE IT'S CONTENT !!!!!!!!!!!!!
	char	temp[strlen(*line) + 1];
	temp[strlen(*line)] = '\0';
	strlcpy(temp, *line, strlen(*line) + 1);
	new_line = (char *) realloc(*line, (strlen(*line) + len + 1) * sizeof(char));
	if (!new_line)
		return (0);

	//printf("TEMP VARIABLE \n");
	//print_str(temp);
	//printf("LENGTH OF TEMP VARIABLE: %zu\n", strlen(temp));
	int i = 0;
	if (strlen(temp) > 0)
	{
		//printf("LINE READY TO COPY\n");
		//COPY LINE TO NEW_LINE
		while (temp[i])
		{
			new_line[i] = temp[i];
			i++;
		}
		//printf("COPIED LINE TO TEMP VARIABLE: %s\n", temp);
	}
	
	//APPEND BUFF TO NEW LINE
	printf("CURRENT BUFFER\n");
	print_str(buff);
	i = 0;
	while (i < len)
	{
		new_line[strlen(temp) + i] = buff[i];
		i++;
	}
	new_line[strlen(temp) + i] = '\0';
	*line = new_line;
	printf("CURRENT LINE\n");
	print_str(*line);
	//printf("Bytes_read %d - Computed len %d\n", bytes_read, len);
	printf("This the current value of LINE %s - LENGHT %lu \n", *line, strlen(*line));
	return (1);
}

char	*get_next_line(int fd)
{
	static char		*line;	
	char		buff[BUFFER_SIZE + 1];
	int			bytes_read;

	line = (char *) malloc(1 * sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (1)
	{
		//printf("::::::::::::IM ITERATING\n");
		bytes_read = read(fd, buff, BUFFER_SIZE);
		//printf("Bytes read %d\n", bytes_read);
		if (bytes_read == -1)
		       	return (free(line), NULL);
			//return (printf("read functions FAIL\n"), free(line), NULL);
		if (!bytes_read)
		{
			//printf("Leaving the function Loop\n");
			if (line[0] == '\0')
				return (free(line), NULL);
			break;
		}
		buff[bytes_read] = '\0';
		//print_str(buff);
		if (!append_buff_to_line(&line, buff, bytes_read))
		{
			//printf("::: REALLOC ERROR\n");
			return (free(line), NULL);
		}
		if (contains(line, '\n'))
			break;
	}
	//printf("::::::::::::RETURNING %s\n", line);
	return (line);
}
/*for (int i= 0; i < strlen(buff); i++)
  {
  if (buff[i] == '\n')
  printf("Found a new line\n");
  if (buff[i] == '\0')
  printf("Found EOF\n");
  printf("%d - %c ", i, buff[i]);
  }
  printf("\n");
  }
  */


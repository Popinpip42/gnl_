#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*get_line_n(char *static_str)
{
	int		len;
	char	*new_line;

	if (!static_str || static_str[0] == '\0')
		return (NULL);
	len = 0;
	while (static_str[len] && static_str[len] != '\n')
		len++;
	if (static_str[len] == '\n')
		len++;
	new_line = (char *)malloc((len + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	len = 0;
	while (static_str[len] && static_str[len] != '\n')
	{
		new_line[len] = static_str[len];
		len++;
	}
	if (static_str[len] == '\n')
	{
		new_line[len] = '\n';
		len++;
	}
	new_line[len] = '\0';
	return (new_line);
}

char	*get_line__(char **statica, int fd)
{
	int		bytes_read;
	char	buff[BUFFER_SIZE + 1];
	char	*new_line;

	bytes_read = 1;
	while (bytes_read > 0 && !contains(*statica, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buff[bytes_read] = '\0';
		if (buff[0] != '\0')
			*statica = append_to(*statica, buff);
	}
	new_line = get_line_n(*statica);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*staticca;
	char		*line;
	char		*rest;

	line = get_line__(&staticca, fd);
	if (!line)
	{
		free(staticca);
		staticca = NULL;
		return (NULL);
	}
	rest = ft_getrest(&staticca);
	free(staticca);
	staticca = rest;
	return (line);
}

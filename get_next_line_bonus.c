#include "get_next_line_bonus.h"

char	*get_remaining(char **buffer)
{
	char	*newline_pos;
	char	*remaining;

	if (!*buffer)
		return (NULL);
	newline_pos = ft_strchr(*buffer, '\n');
	if (!newline_pos)
		return (NULL);
	newline_pos++;
	remaining = ft_strdup(newline_pos);
	return (remaining);
}

char	*extract_line(char *buffer)
{
	int		len;
	char	*line;
	int		i;

	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		len++;
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

char	*get_line_(char **buffer, int fd)
{
	int		bytes_read;
	char	temp_buff[BUFFER_SIZE + 1];
	char	*new_line;

	bytes_read = 1;
	while (bytes_read > 0 && !contains(*buffer, '\n'))
	{
		bytes_read = read(fd, temp_buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		temp_buff[bytes_read] = '\0';
		if (temp_buff[0] != '\0')
			*buffer = append_to(*buffer, temp_buff);
	}
	if (!(*buffer) || *buffer[0] == '\0')
		return (NULL);
	new_line = extract_line(*buffer);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*statica[1024];
	char		*line;
	char		*remaining;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line_(&(statica[fd]), fd);
	if (!line)
	{
		free(statica[fd]);
		statica[fd] = NULL;
		return (NULL);
	}
	remaining = get_remaining(&(statica[fd]));
	free(statica[fd]);
	statica[fd] = remaining;
	return (line);
}

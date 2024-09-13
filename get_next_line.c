#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*append_to(char *statica_str, char *buff)
{
	int		i;
	char	*new_str;

	if (!statica_str)
	{
		statica_str= (char *)malloc(sizeof(char));
		if (!statica_str)
			return (NULL);
		statica_str[0] = '\0';
	}
	if (!statica_str || !buff)
		return (NULL);
	new_str = malloc((strlen(statica_str) + strlen(buff) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (statica_str[i])
	{
		new_str[i] = statica_str[i];
		i++;
	}
	i = 0;
	while (buff[i])
	{
		new_str[strlen(statica_str) + i] = buff[i];
		i++;
	}
	new_str[strlen(statica_str) + strlen(buff)] = '\0';
	free(statica_str);
	return (new_str);
}

char	*get_line_n(char *static_str)
{
	int		len;
	char	*new_line;

	if (!static_str || static_str[0] == '\0')
		return (free(static_str), NULL);
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

int	contains(char *string, int c)
{
	int	i;

	if (!string)
		return (0);
	i = 0;
	while (string[i])
	{
		if (string[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*get_line__(char **statica, int fd)
{
	int		bytes_read;
	char	buff[BUFFER_SIZE + 1];
	char	*new_line;

	bytes_read = 1;
	while (!contains(*statica, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(*statica), NULL);
		buff[bytes_read] = '\0';
		if (buff[0] != '\0')
			*statica = append_to(*statica, buff);
	}
	new_line = get_line_n(*statica);
	//printf("CURRENT LINE : %s\n", new_line);
	//printf("CURRENT STATICA : %s\n", *statica); //TODO: Print Statica
	return (new_line);
}

char	*ft_getrest(char **full_str)
{
	int		i;
	int		j;
	char	*restof;

	i = 0;
	/*
	if (*full_str)
	{
		printf("Is alive --> STATICA %s\n", *full_str);
	}else{
		printf("Is not alive --> STATICA %s\n", *full_str);
		return (NULL);
	}*/
	while ((*full_str)[i] && (*full_str)[i] != '\n')
		i++;
	if (!(*full_str)[i])
		return (free(*full_str), NULL);
	restof = (char *)malloc(sizeof(char) * (strlen(*full_str) - i + 1));
	if (!restof)
		return (NULL);
	i++;
	j = 0;
	while ((*full_str)[i])
		restof[j++] = (*full_str)[i++];
	restof[j] = '\0';
	free(*full_str);
	return (restof);
}

char	*get_next_line(int fd)
{
	static char	*staticca;
	char		*line;

	line = get_line__(&staticca, fd);
	if (!line)
		return (NULL);
	//printf("CURRENT STATICA --- 2: %s\n", staticca);
	staticca = ft_getrest(&staticca);
	
	//printf("STATICA AFTER --- 2_1: %s\n", staticca);
	return (line);
}

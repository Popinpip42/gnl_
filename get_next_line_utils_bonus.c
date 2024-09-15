#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *) s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

size_t	ft_strlen(const char *str)
{
	int	counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}

int	contains(const char *str, int c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*append_to(char *buffer, char *to_append)
{
	int		i;
	char	*new_str;

	if (!buffer)
	{
		buffer = (char *)malloc(sizeof(char));
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	new_str = (char *)malloc(ft_strlen(buffer) + ft_strlen(to_append) + 1);
	if (!new_str)
		return (free(buffer), NULL);
	i = -1;
	while (buffer[++i])
		new_str[i] = buffer[i];
	i = -1;
	while (to_append[++i])
		new_str[ft_strlen(buffer) + i] = to_append[i];
	new_str[ft_strlen(buffer) + ft_strlen(to_append)] = '\0';
	free(buffer);
	return (new_str);
}

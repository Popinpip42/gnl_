#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	counter;

	counter = 0;
	while (s[counter])
		counter++;
	return (counter);
}

int	contains(char *stri, int c)
{
	int	i;

	if (!stri)
		return (0);
	i = 0;
	while (stri[i])
	{
		if (stri[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_getrest(char **full_str)
{
	int		i;
	int		j;
	char	*restof;

	i = 0;
	while ((*full_str)[i] && (*full_str)[i] != '\n')
		i++;
	if (!(*full_str)[i])
		return (NULL);
	restof = (char *)malloc(sizeof(char) * (ft_strlen(*full_str) - i + 1));
	if (!restof)
		return (NULL);
	i++;
	j = 0;
	while ((*full_str)[i])
		restof[j++] = (*full_str)[i++];
	restof[j] = '\0';
	return (restof);
}

char *append_to(char *statica_str, char *buff)
{
    int		i;
    char	*new_str;

    if (!statica_str)
	{
        statica_str = (char *)malloc(sizeof(char));
        if (!statica_str)
            return (NULL);
        statica_str[0] = '\0';
    }
    new_str = (char *)malloc(ft_strlen(statica_str) + ft_strlen(buff) + 1);
    if (!new_str)
        return (free(statica_str), NULL);
    i = 0;
    while (statica_str[i])
	{
        new_str[i] = statica_str[i];
        i++;
    }
    i = 0;
    while (buff[i])
	{
        new_str[ft_strlen(statica_str) + i] = buff[i];
        i++;
    }
    new_str[ft_strlen(statica_str) + ft_strlen(buff)] = '\0';
    free(statica_str);
    return (new_str);
}

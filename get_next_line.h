#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

char	*get_next_line(int fd);
char	*get_remaining(char **full_str);
char	*append_to(char *statica_str, char *buff);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
int		contains(const char *stri, int c);
size_t	ft_strlen(const char *str);

#endif

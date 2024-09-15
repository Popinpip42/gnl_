#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
//# define BUFFER_SIZE 10

char	*get_next_line(int fd);
int     contains(char *stri, int c);
char    *ft_getrest(char **full_str);
char    *append_to(char *statica_str, char *buff);

#endif

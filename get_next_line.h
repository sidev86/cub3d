#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*f_strchr(char *s, int c);
char	*f_strdup(char *s1);
char	*f_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);

#endif

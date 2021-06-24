#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#   include <stdio.h>
#   include <fcntl.h>
#   include <stdlib.h>
#   include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4000
#endif

int     get_next_line(int fd, char **line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strnew(size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memalloc(size_t size);


#endif

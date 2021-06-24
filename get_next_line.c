#include "get_next_line.h"

size_t	gnl_strlen(const char *str)
{
	unsigned int	count;

	count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

void	*gnl_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*str == (unsigned char) c)
			return (str);
		str++;
	}
	return (NULL);
}

void	*gnl_memalloc(size_t size)
{
	unsigned char	*ptr;

	ptr = NULL;
	if (size)
	{
		if (!ptr)
			return (NULL);
		ptr = (unsigned char *)malloc(size);
		while (size)
			ptr[--size] = 0;
	}
	return ((void *)ptr);
}

int	fill_line(char **save, char **line)
{
	char	*tmp;
	int		len;

	len = 0;
	while ((*save)[len] != '\n' && (*save)[len])
		len++;
	if ((*save)[len] == '\n')
	{
		*line = gnl_substr(*save, 0, len);
		tmp = gnl_strdup((*save) + len + 1);
		free((*save));
		(*save) = tmp;
		if ((*save)[0] == '\0')
		{
			free(*save);
			save = NULL;
		}
	}
	else if ((*save)[len] == '\0')
	{
		*line = gnl_strdup(*save);
		free(*save);
		save = NULL;
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*save;
	char		buf[BUFFER_SIZE + 1];
	char		*temp;
	int			ret;

	if (fd < 0 || !line)
		return (-1);
	while (ret)
	{
		ret = read(fd, buf, BUFFER_SIZE) > 0;
		buf[ret] = '\0';
		if (!save)
			save = gnl_strnew(1);
		temp = gnl_strjoin(save, buf);
		free(save);
		save = temp;
		if (gnl_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (!save || save[0] == '\0'))
		return (0);
	return (fill_line(&save, line));
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc || argv)
		;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		printf("%s\n", line);
	close(fd);
	return (0);
}

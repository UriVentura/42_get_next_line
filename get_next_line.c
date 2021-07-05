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

int	fill_line(char **save, char **line)
{
	char	*temp;
	int		len;

	len = 0;
	while ((*save)[len] != '\n' && (*save)[len])
		len++;
	if ((*save)[len] == '\n')
	{
		*line = gnl_substr(*save, 0, len);
		temp = gnl_strdup((*save) + len + 1);
		free(*save);
		*save = temp;
	}
	else if ((*save)[len] == '\0')
	{
		*line = gnl_strdup(*save);
		free(*save);
		save = NULL;
		return (0);
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
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		if (!save)
		{
			save = gnl_strdup("");
			//printf("Entra\n");
		}
		//printf("save = %s\n", save);
		temp = gnl_strjoin(save, buf);
		free(save);
		save = temp;
		if (gnl_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (!save))
		return (0);
	return (fill_line(&save, line));
}

/*int main()
{
	int 	fd;
	char	*line;
	int		i = 1;
	fd = open("text.txt", O_RDONLY);
	while (i)
	{
		i = get_next_line(fd, &line);
		printf("%d ", i);
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	system("leaks gnl");
}*/
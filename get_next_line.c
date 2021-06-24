#include "get_next_line.h"

int fill_line(char **save, char **line)
{
    char *tmp;
    int len;

    len = 0;
    while ((*save)[len] != '\n' && (*save)[len])
        len++;
    if((*save)[len] == '\n')
    {
        *line = ft_substr(*save, 0, len);
        tmp = ft_strdup((*save) + len + 1);
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
        *line = ft_strdup(*save);
        free(*save);
        save = NULL;
    }
    return (1);
}

int get_next_line(int fd, char **line)
{
    static char *save;
    char buf[BUFFER_SIZE +1];
    char *temp;
    int ret;

    if (fd < 0 || !line)
        return (-1);
    while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[ret] = '\0';
        if (!save)
            save = ft_strnew(1);
        temp = ft_strjoin(save, buf);
        free(save);
        save = temp;
        if (ft_strchr(buf, '\n'))
            break;
    }
    if (ret < 0)
        return(-1);
    else if (ret == 0 && (!save || save[0] == '\0'))
        return (0);
    return (fill_line(&save, line));
}

int		main(int argc, char **argv)
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
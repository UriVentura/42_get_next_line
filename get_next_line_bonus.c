/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oventura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:43:13 by oventura          #+#    #+#             */
/*   Updated: 2021/07/15 17:43:14 by oventura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_read(int fd, char *buf, char **save)
{
	int		i;
	char	*temp;

	if (!*save || !gnl_strchr(*save, '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		while (i > 0)
		{
			buf[i] = 0;
			if (!*save)
				*save = gnl_substr(buf, 0, i);
			else
			{
				temp = *save;
				*save = gnl_strjoin(*save, buf);
				free(temp);
			}
			if (gnl_strchr(buf, '\n'))
				break ;
			i = read(fd, buf, BUFFER_SIZE);
		}
	}
	free(buf);
}

char	*gnl_fill_lane(char **save)
{
	int		i;
	int		j;
	char	*res;
	char	*temp;

	if (!*save)
		return (0);
	if (!gnl_strchr(*save, '\n'))
	{
		res = gnl_substr(*save, 0, gnl_strlen(*save));
		free(*save);
		*save = 0;
		return (res);
	}
	i = gnl_strlen(*save);
	j = gnl_strlen(gnl_strchr(*save, '\n'));
	res = gnl_substr(*save, 0, i - j + 1);
	temp = *save;
	*save = gnl_substr(gnl_strchr(*save, '\n'), 1, j);
	free(temp);
	return (res);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	save[FD_SETSIZE];

	buf = malloc(BUFFER_SIZE + 1);
	if (BUFFER_SIZE < 1 || fd == -1 || !buf || read(fd, buf, 0) == -1)
	{
		free(buf);
		return (NULL);
	}
	gnl_read(fd, buf, &save);
	return (gnl_fill_lane(&save));
}

int main(int argc, char **argv)
{
	int fd;
	int	fd2;
	int ret;
	char *line;
	int	i;

	line = 0;
	if (argc == 3)
	{
		fd = open(argv[1], O_RDONLY);
		i = 1;
		while ((line = get_next_line(fd)) != 0)
		{
			printf("Line #%s\n", line);
			free(line);
		}
		printf("Line #%s\n", line);
		if (ret == -1)
			printf("ERROR\n");
		else if (ret == 0)
			printf("EOF\n");
		fd2 = open(argv[2], O_RDONLY);
		close(fd);
		fd = fd2;
		while ((line = get_next_line(fd)) > 0)
		{
			printf("Line #%s\n", line);
			free(line);
		}
		printf("Line #%s\n", line);
		if (ret == -1)
			printf("ERROR\n");
		if (ret == 0)
			printf("EOF\n");
	}
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((line = get_next_line(fd)) != 0)
		{
			printf("Line #%s\n", line);
			free(line);
		}
		printf("Line #%s\n", line);
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("-----------\nEnd of file\n");
		close(fd);
	}
	if (argc == 1)
	{
		while ((line = get_next_line(fd)) != 0)
		{
			line = get_next_line(fd);
			printf("Line #%s\n", line);
			free(line);
		}
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("-----------\nEnd of stdin\n");
		close(fd);
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oventura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:13:15 by oventura          #+#    #+#             */
/*   Updated: 2021/07/15 18:13:16 by oventura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*save[FD_SETSIZE];

	buf = malloc(BUFFER_SIZE + 1);
	if (BUFFER_SIZE < 1 || fd == -1 || !buf || read(fd, buf, 0) == -1)
	{
		free(buf);
		return (NULL);
	}
	gnl_read(fd, buf, &save[fd]);
	return (gnl_fill_lane(&save[fd]));
}

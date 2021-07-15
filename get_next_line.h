/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oventura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:43:02 by oventura          #+#    #+#             */
/*   Updated: 2021/07/15 17:43:06 by oventura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char		*get_next_line(int fd);
char		*gnl_fill_lane(char **save);
void		gnl_read(int fd, char *buf, char **save);
char		*gnl_substr(char const *s, unsigned int start, size_t len);
char		*gnl_strdup(const char *s1);
char		*gnl_strchr(const char *s, int c);
char		*gnl_strjoin(char const *s1, char const *s2);
size_t		gnl_strlen(const char *str);

#endif

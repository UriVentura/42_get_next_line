#include "get_next_line.h"

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*aux;
	char	*str;

	if (!s)
		return (NULL);
	if (start > gnl_strlen(s) - 1)
		return (gnl_strdup(""));
	if (len > gnl_strlen(s) - start - 1)
		len = gnl_strlen(s) - start ;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	aux = str;
	while (len-- > 0 && *(s + start))
		*aux++ = *(s++ + start);
	*aux = '\0';
	return (str);
}

char	*gnl_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	i = 0;
	s2 = (char *) malloc(sizeof (*s1) * (gnl_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*gnl_strnew(size_t size)
{
	char	*tmp;
	tmp = (char *)malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	tmp[size + 1] = '\0';
	return (tmp);
}

char	*gnl_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*aux;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!str)
		return (NULL);
	aux = str;
	while (*s1)
		*aux++ = *s1++;
	while (*s2)
		*aux++ = *s2++;
	*aux = '\0';
	return (str);
}

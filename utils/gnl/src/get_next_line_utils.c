#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	f;
	char	*str;

	if (!s1)
	{
		s1 = (char *) malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc((gnl_strlen(s1) + gnl_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	f = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[f] != '\0')
		str[i++] = s2[f++];
	str[gnl_strlen(s1) + gnl_strlen(s2)] = '\0';
	free(s1);
	return (str);
}

char	*ft_line_read(char *lstr)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!lstr[i])
		return (NULL);
	while (lstr[i] && lstr[i] != '\n')
		i++;
	str = (char *) malloc((i + 1) * sizeof(char));
	i = 0;
	if (!str)
		return (NULL);
	while (lstr[i] && lstr[i] != '\n')
	{
		str[i] = lstr[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_update(char *lstr)
{
	size_t	i;
	size_t	f;
	char	*str;

	i = 0;
	f = 0;
	while (lstr[i] && lstr[i] != '\n')
		i++;
	if (!lstr[i])
	{
		free(lstr);
		return (NULL);
	}
	str = (char *) malloc((gnl_strlen(lstr) - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i++;
	while (lstr[i])
		str[f++] = lstr[i++];
	str[f] = '\0';
	free(lstr);
	return (str);
}

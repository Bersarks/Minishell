#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ss;

	ss = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s1 || !s2 || !ss)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ss[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ss[i++] = s2[j++];
	}
	ss[i] = '\0';
	return (ss);
}

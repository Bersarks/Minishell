#include "../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;

	dst = (char *) malloc(ft_strlen(s1) + 1);
	if (!dst)
		return (0);
	if (!s1)
	{
		free(dst);
		return (0);
	}
	ft_memcpy(dst, s1, ft_strlen(s1) + 1);
	return (dst);
}

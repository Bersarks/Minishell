#include "../inc/libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	int		i;
	char	*res;

	i = 0;
	res = dst;
	while (dst && *dst != '\0')
		dst++;
	while (src && src[i])
	{
		*dst = src[i];
		dst++;
		i++;
	}
	return (res);
}

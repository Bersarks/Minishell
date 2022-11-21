#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (((unsigned char *)str)[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	return (0);
}

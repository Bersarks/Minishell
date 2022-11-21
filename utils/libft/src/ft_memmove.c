#include "../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	count;

	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		while (len > 0)
		{
			((char *)dst)[len -1] = ((const char *)src)[len - 1];
			len--;
		}
	}
	else if (src > dst)
	{
		count = 0;
		while (count < len)
		{
			((char *)dst)[count] = ((const char *)src)[count];
			count++;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}

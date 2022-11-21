#include "../inc/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*dsts;

	dsts = dst;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*((char *)dst++) = *((const char *)src++);
	return (dsts);
}

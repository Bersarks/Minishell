#include "../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*dst;

	total = size * count;
	dst = malloc(total);
	if (!dst)
		return (0);
	ft_memset(dst, 0, total);
	return (dst);
}

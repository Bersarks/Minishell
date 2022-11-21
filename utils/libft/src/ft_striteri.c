#include "../inc/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	x;

	x = 0;
	if (!s || !f)
		return ;
	while (s[x])
	{
		(*f)(x, &s[x]);
		x++;
	}
}

#include "ft_printf.h"

void	ft_puthex(int fd, unsigned long long a)
{
	if (a >= 16)
	{
		ft_puthex(fd, a / 16);
		ft_puthex(fd, a % 16);
	}
	else
	{
		if (a <= 9)
			ft_putchar(fd, a + '0');
		else
			ft_putchar(fd, (a - 10) + 'a');
	}
}

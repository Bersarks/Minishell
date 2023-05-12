#include "ft_printf.h"

static int	ft_count(unsigned long long a)
{
	int	i;

	i = 0;
	while (a)
	{
		a = a / 16;
		i++;
	}
	return (i);
}

int	ft_putchar_p(int fd, unsigned long long a)
{
	int	len;

	len = 0;
	write (fd, "0x", 2);
	len += 2;
	if (a == 0)
	{
		write (fd, "0", 1);
		return (len + 1);
	}	
	else
		ft_puthex(fd, a);
	len += ft_count(a);
	return (len);
}

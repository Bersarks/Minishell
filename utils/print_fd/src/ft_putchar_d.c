#include "ft_printf.h"

static int	ft_count(long a)
{
	int	i;

	i = 0;
	if (a == 0)
		return (1);
	if (a < 0)
		a = -a;
	while (a)
	{
		a = a / 10;
		i++;
	}
	return (i);
}

int	ft_putchar_d(int fd, int a)
{
	int	len;

	len = ft_count(a);
	if (a == -2147483648)
	{
		len += ft_putchar(fd, '-');
		ft_putchar(fd, '2');
		a = 147483648;
	}
	if (a < 0)
	{
		a = a * -1;
		len += ft_putchar(fd, '-');
	}
	if (a < 10)
	{
		ft_putchar(fd, a + '0');
		return (len);
	}
	else
	{
		ft_putchar_d(fd, a / 10);
	}
	ft_putchar_d(fd, a % 10);
	return (len);
}

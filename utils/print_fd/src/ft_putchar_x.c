#include "ft_printf.h"

static int	ft_count(unsigned int a)
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

static void	ft_uplow(int fd, unsigned int a, int c)
{
	if (c == 'X')
		ft_putchar(fd, (a - 10) + 'A');
	else
		ft_putchar(fd, (a - 10) + 'a');
}

int	ft_putchar_x(int fd, unsigned int a, int c)
{
	int	len;

	len = ft_count(a);
	if (a == 0)
	{
		write (fd, "0", 1);
		return (len + 1);
	}
	else
	{
		if (a >= 16)
		{
			ft_putchar_x(fd, (a / 16), c);
			ft_putchar_x(fd, (a % 16), c);
		}
		else
		{
			if (a <= 9)
				ft_putchar(fd, a + '0');
			else
				ft_uplow(fd, a, c);
		}
	}
	return (len);
}

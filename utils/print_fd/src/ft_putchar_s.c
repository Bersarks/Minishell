#include "ft_printf.h"

int	ft_putchar_s(int fd, char *c)
{
	int	len;
	int	a;

	a = 0;
	len = 0;
	if (c == NULL)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (c[a] != '\0')
	{
		write (fd, &c[a++], 1);
		len++;
	}
	return (len);
}

#include "ft_printf.h"

int	ft_putchar_u(int fd, unsigned int a)
{
	int		len;
	char	*num;

	len = 0;
	if (a == 0)
	{
		len += ft_putchar(fd, '0');
		return (len);
	}
	if (a <= 0)
	{
		if ((int)a == -1)
			a = 4294967295;
		else
			a = 4294967295 + a;
	}	
	num = ft_uitoa(a);
	len += ft_putchar_s(fd, num);
	free(num);
	return (len);
}

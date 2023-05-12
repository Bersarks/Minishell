#include "ft_printf.h"

int	ft_putchar(int fd, int c)
{
	return (write(fd, &c, 1));
}

static int	ft_form(int fd, va_list arg, char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_putchar(fd, va_arg(arg, int));
	else if (c == 's')
		len += ft_putchar_s(fd, va_arg(arg, char *));
	else if (c == 'p')
		len += ft_putchar_p(fd, va_arg(arg, unsigned long long));
	else if (c == 'd' || c == 'i')
		len += ft_putchar_d(fd, va_arg(arg, int));
	else if (c == 'u')
		len += ft_putchar_u(fd, va_arg(arg, unsigned int));
	else if (c == 'x' || c == 'X')
		len += ft_putchar_x(fd, va_arg(arg, unsigned int), c);
	else if (c == '%')
		len += ft_putchar(fd, '%');
	else
		len += ft_putchar(fd, c);
	return (len);
}

int	ft_printf(int fd, const char *str, ...)
{
	int		i;
	int		len;
	va_list	arg;

	va_start(arg, str);
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			len += ft_form(fd, arg, str[i++]);
		}
		else
			len += ft_putchar(fd, str[i++]);
	}
	va_end(arg);
	return (len);
}

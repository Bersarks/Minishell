#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>

char		*ft_uitoa(unsigned int a);

int			ft_printf(int fd, const char *str, ...);
int			ft_putchar(int fd, int c);
int			ft_putchar_s(int fd, char *c);
int			ft_putchar_u(int fd, unsigned int a);
int			ft_putchar_d(int fd, int a);
int			ft_putchar_p(int fd, unsigned long long a);
void		ft_puthex(int fd, unsigned long long a);
int			ft_putchar_x(int fd, unsigned int a, int c);

#endif

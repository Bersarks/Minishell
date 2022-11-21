int	ft_atoi(const char *str)
{
	int				a;
	int				b;
	unsigned long	c;

	a = 0;
	b = 1;
	c = 0;
	while (str[a] == ' ' || str[a] == '\n' || str[a] == '\t'
		|| str[a] == '\v' || str[a] == '\f' || str[a] == '\r')
		a++;
	if (str[a] == '+' || str[a] == '-')
	{
		if (str[a] == '-')
			b = -1;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		c = (c * 10) + (str[a] - '0');
		a++;
	}
	return (c * b);
}

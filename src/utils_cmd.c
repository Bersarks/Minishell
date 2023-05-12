#include "../inc/minishell.h"

int	quote_check(char *usr_cmd, int quote_count)
{
	char	temp;

	while (*usr_cmd)
	{
		if (*usr_cmd == '\'' || *usr_cmd == '\"')
		{
			temp = *usr_cmd;
			quote_count++;
			usr_cmd++;
			while (*usr_cmd && *usr_cmd != temp)
				usr_cmd++;
			if (*usr_cmd == temp)
				quote_count++;
		}
		if (*usr_cmd)
			usr_cmd++;
	}
	if (quote_count % 2 == 0)
		return (1);
	return (0);
}

char	*skip_quotes(char *str)
{
	char	quote;

	if (*str == '\'' || *str == '\"')
	{
		quote = *str;
		str++;
		while (*str && *str != quote)
			str++;
	}
	return (str);
}

int	pipe_redir_count(char *usr_cmd)
{
	int	count;

	count = 0;
	while (*usr_cmd)
	{
		if (*usr_cmd == '\'' || *usr_cmd == '\"')
			usr_cmd = skip_quotes(usr_cmd);
		if (ft_strchr("|><", *usr_cmd) && *(usr_cmd + 1) == *usr_cmd)
		{
			count++;
			usr_cmd++;
		}
		else if (ft_strchr("|><", *usr_cmd))
			count++;
		usr_cmd++;
	}
	return (count);
}

int	skip_inout(char **str, int len)
{
	while (*str[0] && ft_strchr("<|>", *str[0]))
	{
		str[0]++;
		len++;
	}
	return (len);
}

int	word_len(char *usr_cmd, int len)
{
	char	*tmp;

	if (ft_strchr("\"\'", *usr_cmd))
	{
		tmp = skip_quotes(usr_cmd);
		len = tmp - usr_cmd + 1;
	}
	else if (ft_strchr("|><", *usr_cmd))
		len = skip_inout(&usr_cmd, len);
	else
	{
		tmp = usr_cmd;
		while (*tmp && !ft_strchr("|>< \"\'", *tmp))
			tmp++;
		len = tmp - usr_cmd;
	}
	return (len);
}

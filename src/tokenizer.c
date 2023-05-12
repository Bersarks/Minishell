#include "../inc/minishell.h"

static int	cmd_next(char *str)
{
	int	i;

	i = 0;
	while (!ft_strchr("|<> \"\'$?", str[i]))
		i++;
	return (i + 1);
}

int	dollar_len(char *split_cmds, int len)
{
	char	*tmp;

	tmp = split_cmds;
	while (*tmp)
	{
		if (*tmp == '$' && strtrim_len(tmp, "\"") > 1)
		{
			tmp++;
			len += free_strlen(get_value(tmp, 0));
			if (*(tmp - 1) == '$')
			{
				len += cmd_next(tmp);
				tmp += cmd_next(tmp) - 1;
			}
			else
				tmp += cmd_next(tmp);
			if (*(tmp - 1) == '\"')
				len++;
			continue ;
		}
		len++;
		tmp++;
	}
	return (len);
}

char	*get_dollar_val(char *cmd, int i, int idx)
{
	char	*new;

	new = ft_calloc(dollar_len(cmd, 0) + 1, sizeof(char));
	while (*cmd)
	{
		if (*cmd == '$' && strtrim_len(cmd, "\"") > 1)
		{
			idx = free_strlen(get_value(cmd + 1, 0));
			if (*(cmd + 1) == '$' || *(cmd + 1) == '?')
			{
				i += idx;
				new = free_strcat(new, get_value(cmd + 1, 0));
				cmd += 2;
				continue ;
			}
			i += idx;
			new = free_strcat(new, get_value(cmd + 1, 0));
			cmd += cmd_next(cmd + 1);
		}
		else
			new[i++] = *cmd++;
	}
	return (new);
}

static void	token_proccess(char **split_cmds)
{
	char	*tmp;

	if (!*split_cmds)
		return ;
	else if (ft_strchr(*split_cmds, '$') && (ft_strchr(*split_cmds, '\"')
			|| ft_strchr(*split_cmds, '\'')))
	{
		tmp = with_quotes(*split_cmds);
		if (*tmp == '\"')
			free(*split_cmds);
		*split_cmds = tmp;
	}
	else if (ft_strchr(*split_cmds, '$') || ft_strchr(*split_cmds, '?'))
	{
		tmp = get_dollar_val(*split_cmds, 0, 0);
		free(*split_cmds);
		*split_cmds = tmp;
	}
}

void	tokenizer(char **split_cmds)
{
	char	*tmp;
	int		i;

	i = -1;
	while (split_cmds[++i])
	{
		if (!ft_strncmp("~", split_cmds[i], 2))
		{
			tmp = get_value("HOME", 0);
			free(split_cmds[i]);
			split_cmds[i] = tmp;
		}
		else
			token_proccess(&split_cmds[i]);
	}
}

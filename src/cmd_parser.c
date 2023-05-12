#include "../inc/minishell.h"

static int	word_counter(char *usr_cmd)
{
	int		len;
	int		trigger;

	len = pipe_redir_count(usr_cmd);
	trigger = 0;
	while (*usr_cmd)
	{
		if (ft_strchr("\"\'", *usr_cmd))
		{
			usr_cmd = skip_quotes(usr_cmd);
			len++;
		}
		if (*usr_cmd && !ft_strchr("|<> \"\'", *usr_cmd) && trigger == 0)
		{
			len++;
			trigger = 1;
		}
		else if (*usr_cmd && (ft_strchr("|<> ", *usr_cmd)
				|| ((*(usr_cmd - 1) == '\"' || *(usr_cmd - 1) == '\'')
					&& !ft_strchr("|<> \"\'", *usr_cmd))))
			trigger = 0;
		usr_cmd++;
	}
	return (len);
}

static char	*cmd_separator(char *usr_cmd)
{
	char	*tmp_cmd;
	int		index;

	index = 0;
	if (*usr_cmd && ft_strchr("\'\"", *usr_cmd))
		tmp_cmd = quoted_words(usr_cmd);
	else if (*usr_cmd && !ft_strchr("|>< \"\'", *usr_cmd))
		tmp_cmd = only_word(usr_cmd);
	else
	{
		tmp_cmd = malloc(sizeof(char) * word_len(usr_cmd, 0) + 1);
		while (*usr_cmd && ft_strchr("<|>", *usr_cmd))
		{
			tmp_cmd[index] = *usr_cmd;
			usr_cmd++;
			index++;
		}
		tmp_cmd[index] = '\0';
	}
	return (tmp_cmd);
}

char	**cmd_parser(char *usr_cmd, int index)
{
	char	**split_cmds;

	split_cmds = (char **)ft_calloc((word_counter(usr_cmd) + 1),
			sizeof(char *));
	while (*usr_cmd)
	{
		split_cmds[index] = cmd_separator(usr_cmd);
		usr_cmd += ft_strlen(split_cmds[index]);
		while (*usr_cmd == 32)
			usr_cmd++;
		index++;
	}
	split_cmds[index] = NULL;
	return (split_cmds);
}

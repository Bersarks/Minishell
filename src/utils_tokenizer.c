#include "../inc/minishell.h"

int	free_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str && str[i])
		i++;
	free(str);
	return (i);
}

char	*free_strcat(char *dst, char *src)
{
	int		i;
	char	*res;

	i = 0;
	res = dst;
	if (!src)
		return (res);
	while (dst && *dst != '\0')
		dst++;
	while (src && src[i])
	{
		*dst = src[i];
		dst++;
		i++;
	}
	free(src);
	return (res);
}

char	*get_value(char *split_cmds, int i)
{
	char	*value;
	char	*res;

	value = NULL;
	while (!ft_strchr("|<> \"\'$?", split_cmds[i]))
		i++;
	if (ft_strchr("?", split_cmds[i]) && split_cmds[i] != '\0' && i == 0)
		return (ft_itoa(g_shell->exit_status));
	if (i > 0)
		value = ft_substr(split_cmds, 0, i);
	res = find_in_env(value);
	if (value != NULL)
		free(value);
	if (!res && *(split_cmds) == '\"' && *(split_cmds - 1) == '$')
		return (ft_strdup("$"));
	else if (!res && *(split_cmds) == '\"' && *(split_cmds - 1) == '?')
		return (ft_strdup("?"));
	else if (!res && *(split_cmds) == ' ' && *(split_cmds - 1) == '$')
		return (ft_strdup("$"));
	return (ft_strdup(res));
}

char	*with_quotes(char *split_cmds)
{
	if (*split_cmds == '\"')
		return (get_dollar_val(split_cmds, 0, 0));
	return (split_cmds);
}

int	strtrim_len(char *cmd, char *set)
{
	int		len;
	char	*tmp;

	if (!cmd || !set)
		return (0);
	while (*cmd && ft_strchr(set, *cmd))
		cmd++;
	len = ft_strlen(cmd);
	while (len && ft_strchr(set, cmd[len]))
		len--;
	tmp = ft_substr(cmd, 0, len + 1);
	len = ft_strlen(tmp);
	free(tmp);
	return (len);
}

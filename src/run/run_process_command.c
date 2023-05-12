#include "../../inc/minishell.h"

static int	ft_isalpha2(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

char	**my_split(char **str)
{
	char	**res;
	int		idx;
	int		idx2;
	int		len;

	len = 0;
	idx2 = 0;
	idx = 0;
	res = malloc(sizeof(char *) * 3);
	while (str[1][len] != '=' && str[1][len])
		len++;
	res[0] = malloc(sizeof(char) * len + 1);
	while (str[1][idx] && str[1][idx] != '=')
		res[0][idx2++] = str[1][idx++];
	res[0][idx2] = '\0';
	idx = 0;
	idx2 = 0;
	res[1] = malloc(sizeof(char) * ft_strlen(str[2]) + 1);
	while (str[2][idx])
		res[1][idx2++] = str[2][idx++];
	res[1][idx2] = '\0';
	res[2] = NULL;
	return (res);
}

int	check_key(char *key)
{
	int	idx;

	idx = 0;
	while (key[idx])
	{
		if (!ft_isalpha2(key[idx]))
			return (0);
		idx++;
	}
	return (1);
}

void	execute_command(char **no_pipe)
{
	int		i;

	i = 0;
	if (no_pipe[i] && is_builtin(no_pipe[i]))
		execute_builtin(&no_pipe[i]);
	else
		commands(no_pipe);
}

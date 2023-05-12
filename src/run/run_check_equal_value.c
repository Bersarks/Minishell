#include "../../inc/minishell.h"

int	last_pipe_check(void)
{
	char	*last_pipe;

	while (1)
	{
		last_pipe = readline("> ");
		if (!*last_pipe)
		{
			free(last_pipe);
			continue ;
		}
		cmd_operations(last_pipe);
		free(last_pipe);
		return (1);
	}
}

int	check_env(char **double_str)
{
	t_env	*temp;

	temp = g_shell->env;
	while (temp)
	{
		if (!ft_strncmp(temp->key, double_str[0], ft_strlen(double_str[0])))
		{
			free(temp->value);
			temp->value = ft_strdup(double_str[1]);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	check_equal_value(char **split)
{
	char	**double_str;

	double_str = split;
	if (check_env(double_str))
		return ;
}

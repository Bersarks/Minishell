#include "../../inc/minishell.h"

int	pipe_check(t_token *tmp)
{
	int		check_last_pipe;

	check_last_pipe = 0;
	if (tmp->next == NULL)
		check_last_pipe = last_pipe_check();
	if (check_last_pipe == 1)
		return (1);
	return (0);
}

static int	free_get_value(char *str)
{
	int	check;

	if (str)
		check = 1;
	else
		check = 0;
	free(str);
	str = NULL;
	return (check);
}

static void	multiple_del(char *key, t_env **env)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env;
	if (temp != NULL && temp->key == key)
	{
		*env = temp->next;
		free(temp);
		return ;
	}
	while (temp != NULL && ft_strncmp(temp->key, key, ft_strlen(key) + 1))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp->value);
	free(temp->key);
	free(temp);
	temp = NULL;
}

static void	delete_from_env(char *del, t_env **env)
{
	t_env	*temp;
	t_env	*temp2;

	temp = *env;
	if (!temp)
		return ;
	else if (temp->next && !ft_strncmp(temp->key, del, ft_strlen(del) + 1))
	{
		temp2 = temp;
		*env = temp->next;
		free(temp2->key);
		free(temp2->value);
		free(temp2);
		return ;
	}
	else
		multiple_del(del, env);
	return ;
}

void	unset(char **str)
{
	int	index;

	index = 1;
	while (str[index])
	{
		if (str[index] && free_get_value(get_value(str[index], 0)))
			delete_from_env(str[index], &g_shell->env);
		index++;
	}
	g_shell->exit_status = 0;
}

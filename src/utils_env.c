#include "../inc/minishell.h"

char	*find_in_env(char *split_cmds)
{
	t_env	*tmp;

	tmp = g_shell->env;
	if (split_cmds == NULL)
		return (NULL);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, split_cmds, ft_strlen(tmp->key))
			&& (ft_strlen(tmp->key) == ft_strlen(split_cmds)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_oldpwd(char *oldpwd, char *new_pwd)
{
	t_env	*tmp;

	tmp = g_shell->env;
	if (oldpwd == NULL)
	{
		add_env("OLDPWD", new_pwd);
		return ;
	}
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD", 6))
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_pwd);
			return ;
		}
		tmp = tmp->next;
	}
}

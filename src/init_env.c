#include "../inc/minishell.h"

static t_env	*new_list(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

static void	env_addback(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	init_env(char **envp)
{
	int		len;
	t_env	*env;

	while (*envp)
	{
		len = ft_strlen(*envp);
		env = new_list();
		env->key = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		env->value = ft_substr(*envp, ft_strchr(*envp, '=') - *envp + 1, len);
		env_addback(&g_shell->env, env);
		envp++;
	}
}

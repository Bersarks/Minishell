#include "../inc/minishell.h"

static t_env	*new_list(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = NULL;
	new->value = NULL;
	new->flag = 0;
	new->next = NULL;
	return (new);
}

static t_env	*env_lstlast(t_env *env)
{
	while (env)
	{
		if (!env->next)
			return (env);
		env = env->next;
	}
	return (env);
}

static void	env_addback(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (env)
	{
		if (!*env)
			*env = new;
		else
		{
			tmp = env_lstlast(*env);
			tmp->next = new;
		}
	}
}

void	add_env(char *key, char *value)
{
	t_env	*env;
	t_env	*tmp;

	tmp = g_shell->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	env = new_list();
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->flag = 2;
	env_addback(&g_shell->env, env);
}

void	init_env(char **envp)
{
	t_env	*env;

	while (*envp)
	{
		env = new_list();
		env->key = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		env->value = ft_strdup(getenv(env->key));
		env->flag = 1;
		env_addback(&g_shell->env, env);
		envp++;
	}
}

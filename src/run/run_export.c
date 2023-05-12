#include "../../inc/minishell.h"

static void	export_swap(t_env *tmp, t_env *tmp2)
{
	char	*tmp_str;

	tmp_str = tmp->key;
	tmp->key = tmp2->key;
	tmp2->key = tmp_str;
	tmp_str = tmp->value;
	tmp->value = tmp2->value;
	tmp2->value = tmp_str;
}

static void	print_export_alphabetically(void)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = g_shell->env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strncmp(tmp->key, tmp2->key, ft_strlen(tmp->key)) > 0)
				export_swap(tmp, tmp2);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	tmp = g_shell->env;
	while (tmp)
	{
		ft_printf(OUT, "declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

static void	export_env(char **str)
{
	char	**double_str;
	int		i;

	i = 1;
	while (str[i])
	{
		if (ft_strchr(str[i], '='))
		{
			if (str[2])
				double_str = my_split(str);
			else
				double_str = ft_split(str[i], '=');
			if (!check_key(*double_str))
			{
				error_message("%s=%s: command not found\n", 127, *double_str,
					*(double_str + 1));
				return ;
			}
			check_equal_value(double_str);
			add_env(double_str[0], double_str[1]);
			free_2d_array(double_str);
		}
		i++;
	}
}

void	export(char **str)
{
	if (!str[1])
		print_export_alphabetically();
	else if (str[1])
		export_env(str);
}

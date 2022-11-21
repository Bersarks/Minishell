#include "../inc/minishell.h"

int	quote_check(char *input, int quote_count)
{
	char	quote;

	while (*input)
	{
		if (*input == '\'' || *input == '\"')
		{
			quote = *input;
			quote_count++;
			input++;
			while (*input && *input != quote)
				input++;
			if (*input == quote)
				quote_count++;
		}
		if (*input)
			input++;
	}
	if (quote_count % 2 == 0)
		return (1);
	return (0);
}

// Açılan tırnak kapanana kadar adresi arttırır ve return eder.
char	*skip_quotes(char *str)
{
	char	quote;

	if (*str == '\'' || *str == '\"')
	{
		quote = *str;
		str++;
		while (*str && *str != quote)
			str++;
	}
	return (str);
}

char	*find_env_home(void)
{
	t_env	*temp;

	temp = g_shell->env;
	while (temp)
	{
		if (!ft_strncmp(temp->key, "HOME", 5))
			return (temp->value);
		temp = temp->next;
	}
	printf("NO HOME env\n");
	return (NULL);
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*find_in_env(char *find)
{
	t_env	*tmp;

	tmp = g_shell->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, find, ft_strlen(tmp->value)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

#include "../inc/minishell.h"

void	assignment_process(char **input, char **str, int idx)
{
	*str[idx] = **input;
	(*str)[idx]++;
	(*input)++;
}

int skip_inout(char **str, int len)
{
	while (*str[0] && ft_strchr("<|>", *str[0]))
	{
		str[0]++;
		len++;
	}
	return (len);
}

char	*quoted_words(char *input, int *idx)
{
	char	quote;
	int		i;
	char	*temp;

	temp = malloc(sizeof(char) * word_len(input, 0) + 1);
	i = -1;
	quote = *input;
	printf("quote: %c\n", quote);
	temp[++i] = *input;
	input++;
	while (*input != quote)
	{
		printf("input: %c\n", *input);
		temp[++i] = *input;
		printf("temp[%d]: %c\n", i, temp[i]);
		input++;
	}
	temp[++i] = *input;
	temp[++i] = '\0';
	*idx = i;
	return (temp);
}

char	*only_word(char *input, int *idx)
{
	char	*str;
	int		i;

	i = -1;
	str = malloc(sizeof(char) * word_len(input, 0) + 1);
	while (*input && ft_strchr("<|>", *input) == NULL)
	{
		str[++i] = *input;
		input++;
	}
	str[++i] = '\0';
	*idx = i;
	return (str);
}

// verilen stringi localin keylerinde arar bulursa localin valuesini returnler.
char	*find_in_local(char *find)
{
	t_local	*tmp;

	tmp = g_shell->local;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, find, ft_strlen(tmp->key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
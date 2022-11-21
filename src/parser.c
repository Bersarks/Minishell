#include "../inc/minishell.h"

int	pipe_redir_count(char *str)
{
	int		len;

	len = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			str = skip_quotes(str);
		if (ft_strchr("<|>", *str))
			len++;
		str++;
	}
	return (len);
}

// Kopyalanacak stringin uzunluğunu bulur tırnakla başlıyorsa uzunluk tırnağın uzunluğu kadar değilse boşluğa kadar olur.
int	word_len(char *str, int len)
{
	char	quote;

	if (*str == '\'' || *str == '\"')
	{
		quote = *str;
		str++;
		while (*str && *str != quote)
		{
			len++;
			str++;
		}
		len += 2;
	}
	else if (ft_strchr("<|>", *str))
		len = skip_inout(&str, len);
	else
	{
		while (*str && *str != 32 && ft_strchr("<|> \"\'", *str) == NULL)
		{
			str++;
			len++;
		}
	}
	return (len);
}

// Matrix'in boyutlarini delimiter'a gore ayirir.
static int	wordcounter(char *p)
{
	int	trigger;
	int	len;

	len = pipe_redir_count(p);
	trigger = 0;
	while (*p)
	{
		if (*p == '\'' || *p == '\"')
			p = skip_quotes(p);
		if (*p != ' ' && trigger == 0 && ft_strchr("<|>", *p) == NULL)
		{
			trigger = 1;
			len++;
		}
		else if (*p == ' ' || ft_strchr("<|>", *p))
			trigger = 0;
		p++;
	}
	return (len);
}

char	*word_dup(char *input, int idx, char quote, int *start)
{
	int		blanks;
	char	*str;

	blanks = 0;
	while (*input == 32)
	{
		input++;
		blanks++;
	}
	if (*input == '\'' || *input == '\"') // tirnakla baslıyorsa
		str = quoted_words(input, &idx);
	else if(*input && ft_strchr("|<> \'\"", *input) == NULL) // <|>'" dışındaki karakterlerden biriyse
		str = only_word(input, &idx);
	else
	{
		str = malloc(sizeof(char) * word_len(input, 0) + 1);
		while (ft_strchr("<|>", *input)) // <|> bu karakterlerden biriyse al
		{
			str[++idx] = *input;
			input++;
		}
	}
	str[++idx] = '\0';
	*start += ft_strlen(str) + blanks;
	return (str);
}

char **cmds_parser(char *input, int idx)
{
	char	**split_input;
	int		start;

	start = 0;
	split_input = malloc(sizeof(char *) * wordcounter(input) + 1);
	while (input[start] == 32)
		start++;
	while (start < ft_strlen(input))
		split_input[++idx] = word_dup(input + start, -1, 0, &start);
	printf("split_input[%d]: %s\n", idx, split_input[idx]);
	split_input[++idx] = NULL;
	return (split_input);
}

#include "../inc/minishell.h"

static char	*remove_quotes_str(char *str)
{
	char	*delimiter;
	char	*rmv_str;

	delimiter = malloc(sizeof(char) * 2);
	*delimiter = str[0];
	*(delimiter + 1) = '\0';
	rmv_str = ft_strtrim(str, delimiter);
	free(delimiter);
	return (rmv_str);
}

static void	remove_quote_list(t_token **lst)
{
	t_token	*tmp;
	char	*rmv_str;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strchr("\"\'", tmp->value[0])
			&& ft_strchr("\"\'", tmp->value[ft_strlen(tmp->value) - 1]))
		{
			tmp->quote_check = 1;
			rmv_str = remove_quotes_str(tmp->value);
			if (tmp->value != NULL)
				free(tmp->value);
			tmp->value = rmv_str;
		}
		tmp = tmp->next;
	}
}

static t_token	*new_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->value = NULL;
	new->type = 0;
	new->quote_check = 0;
	new->heredoc_check = 0;
	new->next = NULL;
	return (new);
}

static void	add_back_token(t_token **lst, t_token *new)
{
	t_token	*tmp;

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

void	add_token_lst(char **input, t_token **token_lst)
{
	int		idx;
	t_token	*temp;

	*token_lst = NULL;
	idx = 0;
	while (input[idx])
	{
		temp = new_token();
		temp->value = ft_strdup(input[idx]);
		add_back_token(token_lst, temp);
		idx++;
	}
	remove_quote_list(token_lst);
}

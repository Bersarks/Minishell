#include "../inc/minishell.h"

static void	check_2(t_token **tmp)
{
	if (is_builtin((*tmp)->value)
		&& !is_redirect((*tmp)->next->value))
		(*tmp)->type = BUILTIN;
	else if (is_operator((*tmp)->value))
	{
		(*tmp)->type = find_operator((*tmp)->value);
		if (!ft_strncmp((*tmp)->value, "<<", 3))
			g_shell->heredoc_count += 1;
	}
	else
		(*tmp)->type = COMMAND;
}

static void	single_command(t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	if (tmp->quote_check == 1)
		tmp->type = COMMAND;
	else if (is_builtin(tmp->value))
		tmp->type = BUILTIN;
	else if (is_operator(tmp->value))
		tmp->type = find_operator(tmp->value);
	else
		tmp->type = COMMAND;
}

static t_token	*multiple_command(t_token **tkn)
{
	t_token	*tmp;

	tmp = *tkn;
	while (tmp && tmp->next)
	{
		check_2(&tmp);
		if (tmp->quote_check == 1)
			tmp->type = COMMAND;
		else if (is_redirect(tmp->value) && !is_operator(tmp->next->value))
		{
			tmp->next->type = T_FILE;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

void	define_types(t_token *token_lst)
{
	t_token	*tmp;

	tmp = token_lst;
	if (!tmp->next)
	{
		single_command(&tmp);
		return ;
	}
	if (tmp && tmp->next)
		tmp = multiple_command(&tmp);
	if (tmp)
	{
		if (tmp->quote_check == 1)
			tmp->type = COMMAND;
		else if (is_builtin(tmp->value))
			tmp->type = BUILTIN;
		else if (is_operator(tmp->value))
			tmp->type = find_operator(tmp->value);
		else
			tmp->type = COMMAND;
		return ;
	}
}

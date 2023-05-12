#include "../../inc/minishell.h"

int	is_command_or_argument(int type)
{
	if (type == COMMAND || type == BUILTIN)
		return (1);
	return (0);
}

int	get_commands_length(t_token *current, t_token *command)
{
	int		length;
	t_token	*temp;

	length = 0;
	temp = current;
	while (temp != command)
	{
		if (is_command_or_argument(temp->type))
			length++;
		temp = temp->next;
	}
	return (length);
}

char	**before_pipe(t_token *token_lst, t_token *command)
{
	t_token	*tmp;
	char	**no_pipe;
	int		counter;
	int		len;

	if (token_lst && token_lst->next
		&& !ft_strncmp(token_lst->value, ">", 2))
		token_lst = token_lst->next->next;
	len = get_commands_length(token_lst, command);
	counter = 0;
	tmp = token_lst;
	no_pipe = (char **)malloc(sizeof(char *) * (len + 1));
	no_pipe[len] = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (is_command_or_argument(tmp->type))
		{
			no_pipe[counter] = tmp->value;
			counter++;
		}
		tmp = tmp->next;
	}
	return (no_pipe);
}

int	redirect_file_check(t_token *token_list)
{
	t_token	*tmp;

	tmp = token_list;
	if (token_list->type == REDIRECT && token_list->next == NULL)
		return (0);
	while (tmp && tmp->next)
	{
		if (tmp->type == REDIRECT && tmp->next->type != T_FILE)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	*get_path(void)
{
	char	*temp;

	temp = get_value("PATH", 0);
	if (!temp)
	{
		g_shell->exit_status = 1;
		ft_putendl_fd("no such file or directory.", 2);
		free(temp);
		return (NULL);
	}
	free(temp);
	g_shell->exit_status = 0;
	return (get_value("PATH", 0));
}

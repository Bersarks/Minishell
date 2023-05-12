#include "../../inc/minishell.h"

static void	writable(char *file_name, int flag)
{
	int	fd;

	fd = open(file_name, flag, 0644);
	if (fd == -1)
	{
		ft_printf(ERR, "File can't opened !\n");
		g_shell->exit_status = 1;
		g_shell->file_error_check = 1;
		return ;
	}
	dup2(fd, OUT);
	close(fd);
}

static void	readable(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_printf(ERR, "File can't opened !\n");
		g_shell->exit_status = 1;
		g_shell->file_error_check = 1;
		return ;
	}
	dup2(fd, IN);
	close(fd);
}

static int	redirect_heredoc_check(char *file_name,
							t_token *token_lst, int *heredoc_count)
{
	int	fd;

	*heredoc_count += 1;
	fd = open(".heredoc_temp",
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf(ERR, "File can't opened !\n");
		g_shell->exit_status = 1;
		g_shell->file_error_check = 1;
		return (1);
	}
	heredoc(file_name, fd);
	if (g_shell->heredoc_count == *heredoc_count)
		readable_for_heredoc(".heredoc_temp", token_lst);
	return (0);
}

static int	execute_redirect(char *file_name, char *str,
							t_token *token_lst, int *heredoc_count)
{
	if (!ft_strncmp(">", str, 2))
		writable(file_name, O_WRONLY | O_CREAT | O_TRUNC);
	else if (!ft_strncmp("<", str, 2))
		readable(file_name);
	else if (!ft_strncmp(">>", str, 3))
		writable(file_name, O_WRONLY | O_CREAT | O_APPEND);
	else if (!ft_strncmp("<<", str, 3))
	{
		if (redirect_heredoc_check(file_name, token_lst, heredoc_count))
			return (1);
		return (0);
	}
	return (1);
}

void	redirect_proccess(t_token *token_lst, int *heredoc_count)
{
	t_token	*tmp;

	tmp = token_lst;
	while (tmp && tmp->next && tmp->type != PIPE)
	{
		if (tmp->type == REDIRECT && tmp->heredoc_check != 1)
		{
			execute_redirect(tmp->next->value, tmp->value,
				token_lst, heredoc_count);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

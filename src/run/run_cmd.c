#include "../../inc/minishell.h"

static void	restore_fd(void)
{
	dup2(g_shell->dup_fd[0], STDIN_FILENO);
	close(g_shell->dup_fd[0]);
	dup2(g_shell->dup_fd[1], STDOUT_FILENO);
	close(g_shell->dup_fd[1]);
}

static void	create_pipe(t_token *pipe_token, int *old_pipe_in)
{
	int	new_pipe[2];

	dup2(*old_pipe_in, IN);
	if (!pipe_token)
		return ;
	pipe(new_pipe);
	dup2(new_pipe[1], OUT);
	close(new_pipe[1]);
	*old_pipe_in = dup(new_pipe[0]);
	close(new_pipe[0]);
}

static int	check_redirect(t_token *token_lst, int *pipe_fd)
{
	t_token	*tmp;

	tmp = token_lst;
	while (tmp && tmp->next && tmp->type != PIPE)
	{
		if (tmp && tmp->next->type == REDIRECT
			&& !ft_strncmp(tmp->next->value, "<<", 2))
		{
			if (!ft_strncmp(tmp->value, "cat", 4)
				|| !ft_strncmp(tmp->value, "head", 5)
				|| !ft_strncmp(tmp->value, "tail", 5)
				|| !ft_strncmp(tmp->value, "sort", 5))
			{
				if (*pipe_fd != 0)
					close(*pipe_fd);
				*pipe_fd = 0;
				return (0);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	process_with_pipe(t_token *before, t_token *after,
				int *pipe_fd, int *heredoc_count)
{
	char	**cmd;

	if (!redirect_file_check(before))
	{
		error_message("bash: syntax error near unexpected token `newline\'\n", 2);
		return ;
	}
	g_shell->dup_fd[0] = dup(IN);
	g_shell->dup_fd[1] = dup(OUT);
	if (!check_redirect(before, pipe_fd))
		create_pipe(after, pipe_fd);
	redirect_proccess(before, heredoc_count);
	cmd = before_pipe(before, after);
	if (!g_shell->file_error_check)
		execute_command(cmd);
	g_shell->file_error_check = 0;
	restore_fd();
	free(cmd);
	return ;
}

void	run_cmd(t_token *token_lst)
{
	t_token	*tmp;
	int		pipe_fd;
	int		heredoc_count;

	heredoc_count = 0;
	pipe_fd = 0;
	tmp = token_lst;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			process_with_pipe(token_lst, tmp, &pipe_fd, &heredoc_count);
			if (pipe_check(tmp))
				return ;
			token_lst = tmp->next;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		process_with_pipe(token_lst, tmp, &pipe_fd, &heredoc_count);
	if (pipe_fd != 0)
		close(pipe_fd);
}

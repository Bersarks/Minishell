#include "../../inc/minishell.h"

int	redirect_check(t_token *token_lst)
{
	t_token	*tmp;

	tmp = token_lst;
	while (tmp)
	{
		if (tmp->type == REDIRECT && !ft_strncmp(tmp->value, "<<", 2))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	free_token_tmp(char **token_tmp, char *line)
{
	free(line);
	free_2d_array(token_tmp);
}

void	readable_for_heredoc(char *file_name, t_token *token_lst)
{
	t_token	*tmp;
	int		fd;

	tmp = token_lst;
	while (tmp && tmp->next && ft_strncmp(tmp->next->value, "<<", 2))
			tmp = tmp->next;
	if (!ft_strncmp(tmp->value, "cat", 4)
		|| !ft_strncmp(tmp->value, "head", 5)
		|| !ft_strncmp(tmp->value, "tail", 5)
		|| !ft_strncmp(tmp->value, "sort", 5))
	{
		fd = open(file_name, O_RDONLY, 0644);
		if (fd == -1)
		{
			ft_printf(ERR, "File can't opened !\n");
			return ;
		}
		dup2(fd, IN);
		close(fd);
	}
}

void	heredoc(char *delimiter, int fd)
{
	char	*line;
	char	**token_tmp;

	while (1)
	{
		token_tmp = (char **)malloc(sizeof(char *) * 2);
		ft_printf(IN, "> ");
		line = get_next_line(0);
		token_tmp[0] = ft_strdup(line);
		token_tmp[1] = 0;
		if (!line)
			break ;
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free_token_tmp(token_tmp, line);
			break ;
		}
		tokenizer(token_tmp);
		ft_printf(fd, "%s\n", token_tmp[0]);
		free_token_tmp(token_tmp, line);
	}
	close(fd);
}

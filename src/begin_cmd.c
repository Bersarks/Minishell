#include "../inc/minishell.h"

static void	cmd_clear(void)
{
	ft_putstr_fd("\033[2J", 1);
	ft_putstr_fd("\033[1;1H", 1);
}

static void	free_tlist(t_token **lst)
{
	t_token	*tmp;

	tmp = *lst;
	while (tmp->next)
	{
		tmp = (*lst)->next;
		free((*lst)->value);
		free (*lst);
		*lst = tmp;
	}
	free((*lst)->value);
	free (*lst);
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

void	cmd_operations(char *usr_cmd)
{
	char	**split_cmds;
	t_token	*token_lst;

	if (!quote_check(usr_cmd, 0))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return ;
	}
	split_cmds = cmd_parser(usr_cmd, 0);
	tokenizer(split_cmds);
	add_token_lst(split_cmds, &token_lst);
	define_types(token_lst);
	run_cmd(token_lst);
	free_tlist(&token_lst);
	free_2d_array(split_cmds);
	g_shell->heredoc_count = 0;
}

void	begin_cmd(void)
{
	char	*usr_cmd;
	char	*tmp;

	while (1)
	{
		usr_cmd = readline("\033[32mminishell$> \033[0m");
		if (!usr_cmd)
			exit(0);
		tmp = ft_strtrim(usr_cmd, " \t");
		if (!*usr_cmd || !*tmp)
		{
			free(usr_cmd);
			free(tmp);
			continue ;
		}
		if (ft_strncmp(tmp, "exit", 5) == 0 || ft_strncmp(tmp, "exit ", 5) == 0)
			exit (EXIT_SUCCESS);
		if (ft_strncmp(tmp, "clear", 6) == 0)
			cmd_clear();
		else
			cmd_operations(tmp);
		cmd_history(tmp);
		free(usr_cmd);
		free(tmp);
	}
}

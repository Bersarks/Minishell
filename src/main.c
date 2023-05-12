#include "../inc/minishell.h"

t_shell	*g_shell;

static void	sig_handler(int s_no)
{
	(void)s_no;
	ft_printf(OUT, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_shell->exit_status = 130;
}

static void	error_msg(char *str)
{
	ft_printf(ERR, str);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		error_msg("Error: too many arguments.\n");
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	g_shell = (t_shell *)malloc(sizeof(t_shell));
	g_shell->env = NULL;
	g_shell->local = NULL;
	g_shell->exit_status = 0;
	g_shell->file_error_check = 0;
	g_shell->heredoc_count = 0;
	init_env(envp);
	load_history(ft_strjoin(find_in_env("HOME"), "/.minishell_history"));
	begin_cmd();
}

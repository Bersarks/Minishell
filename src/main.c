#include "../inc/minishell.h"

t_shell	*g_shell;

static void	error_msg(char *str)
{
	printf("%s\n", str);
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		error_msg("Error: too many arguments");
	g_shell = (t_shell *)malloc(sizeof(t_shell));
	g_shell->env = NULL;
	g_shell->local = NULL;
	g_shell->exit_status = 0;
	init_env(envp);
	begin_cmds();
	return (0);
}

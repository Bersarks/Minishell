#include "../inc/minishell.h"

int	is_builtin(char *str)
{
	if ((!ft_strncmp("echo", str, 5))
		|| !ft_strncmp("exit", str, 5)
		|| !ft_strncmp("cd", str, 3)
		|| !ft_strncmp("unset", str, 6)
		|| !ft_strncmp("export", str, 7))
		return (1);
	if (!ft_strncmp("pwd", str, 4))
		return (1);
	if (!ft_strncmp("env", str, 4))
		return (1);
	return (0);
}

int	is_operator(char *str)
{
	if (!ft_strncmp("|", str, 2)
		|| !ft_strncmp("<", str, 2)
		|| !ft_strncmp(">", str, 2)
		|| !ft_strncmp(">>", str, 3)
		|| !ft_strncmp("<<", str, 3))
		return (1);
	return (0);
}

int	is_redirect(char *str)
{
	if (!ft_strncmp("<", str, 2)
		|| !ft_strncmp(">", str, 2)
		|| !ft_strncmp(">>", str, 3)
		|| !ft_strncmp("<<", str, 3))
		return (1);
	return (0);
}

int	find_operator(char *str)
{
	int	type;

	if (!ft_strncmp("|", str, 2))
		type = PIPE;
	else
		type = REDIRECT;
	return (type);
}

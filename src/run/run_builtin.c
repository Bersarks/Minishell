#include "../../inc/minishell.h"

static void	echo_no_option(char **str)
{
	int	idx;

	idx = 1;
	while (str[idx] && str)
	{
		ft_printf(OUT, "%s", str[idx]);
		if (str[idx + 1])
			ft_printf(OUT, "%c", ' ');
		idx++;
	}
	ft_printf(OUT, "%c", '\n');
	g_shell->exit_status = EXIT_SUCCESS;
}

void	echo_option_n(char **str)
{
	int		idx;

	if (str[1] && !ft_strncmp("-n", str[1], 3))
	{
		idx = 2;
		while (str[idx] && str)
		{
			ft_printf(OUT, "%s", str[idx]);
			if (str[idx + 1])
				ft_printf(OUT, "%c", ' ');
			idx++;
		}
		g_shell->exit_status = EXIT_SUCCESS;
		return ;
	}
	else
	{
		echo_no_option(str);
		return ;
	}
	g_shell->exit_status = EXIT_FAILURE;
}

void	pwd_no_option(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
	{
		perror("Error getcwd failed");
		g_shell->exit_status = 126;
		return ;
	}
	ft_printf(OUT, "%s\n", cwd);
	free(cwd);
	g_shell->exit_status = EXIT_SUCCESS;
}

void	env(char **argv)
{
	t_env	*tmp;

	tmp = g_shell->env;
	if (argv != NULL && argv[1] != NULL)
	{
		if (access(argv[1], F_OK) == 0)
		{
			error_message("env: %s: Premission denied\n", 126, argv[1]);
			return ;
		}
		error_message("env: %s: No such file or directory\n", 127, argv[1]);
		return ;
	}
	while (tmp && tmp->value != NULL)
	{
		if (ft_printf(OUT, "%s=%s\n", tmp->key, tmp->value) == 0)
		{
			g_shell->exit_status = EXIT_FAILURE;
			return ;
		}
		tmp = tmp->next;
	}
	g_shell->exit_status = EXIT_SUCCESS;
}

void	cd(char **str)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!str[1])
	{
		update_oldpwd(find_in_env("OLDPWD"), pwd);
		chdir(find_in_env("HOME"));
	}
	else if (!ft_strncmp("-", str[1], 2))
	{
		if (chdir(find_in_env("OLDPWD")) == -1)
			ft_printf(ERR, "%s", "cd: OLDPWD not set\n");
		update_oldpwd(find_in_env("OLDPWD"), pwd);
	}
	else
	{
		update_oldpwd(find_in_env("OLDPWD"), pwd);
		if (chdir(*(str + 1)) == -1)
			ft_printf(ERR, "cd: %s: No such file or directory\n", *(str + 1));
	}
	free(pwd);
}

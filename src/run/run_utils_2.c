#include "../../inc/minishell.h"

static char	*find_path(char *str, char *path_part)
{
	char	*final_path;
	char	*f_path;

	final_path = NULL;
	if (ft_strncmp(path_part, str, ft_strlen(path_part)) == 0)
	{
		final_path = ft_strdup(path_part);
	}
	else if (ft_strncmp(str, "/", 1))
	{
		f_path = ft_strjoin(path_part, "/");
		final_path = ft_strjoin(f_path, str);
		free(f_path);
	}
	else
		final_path = ft_strdup(str);
	return (final_path);
}

static void	run_other_command(char **str, char *lib_cmmd)
{
	int		pid;
	int		res;

	pid = fork();
	if (pid == 0)
	{
		execve(lib_cmmd, str, 0);
		if (pid > 0)
			exit (0);
	}
	waitpid(pid, &res, 0);
	unlink(".heredoc_temp");
	if (WIFEXITED(res))
		g_shell->exit_status = WEXITSTATUS(res);
}

static int	is_executable(char *cmd_path)
{
	struct stat	buffer;

	if (stat(cmd_path, &buffer) != 0)
		return (0);
	if ((buffer.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	if ((buffer.st_mode & S_IXUSR))
		return (1);
	return (0);
}

static char	*run_exec_path(char **str, char *path)
{
	char		**double_path;
	char		*lib_cmd;
	int			idx;

	idx = 0;
	double_path = ft_split(path, ':');
	while (double_path && double_path[idx])
	{
		lib_cmd = find_path(str[0], double_path[idx]);
		if (is_executable(lib_cmd))
			break ;
		if (lib_cmd)
			free(lib_cmd);
		lib_cmd = NULL;
		idx++;
	}
	free_2d_array(double_path);
	return (lib_cmd);
}

void	commands(char **str)
{
	char	*lib_cmmd;
	char	*paths;

	paths = get_path();
	if (!paths || !*str)
		return ;
	lib_cmmd = run_exec_path(str, paths);
	free(paths);
	if (!lib_cmmd)
	{
		ft_printf(2, "%s: No such file or directory\n", str[0]);
		g_shell->exit_status = 127;
		return ;
	}
	run_other_command(str, lib_cmmd);
	free(lib_cmmd);
}

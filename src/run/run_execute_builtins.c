#include "../../inc/minishell.h"

void	execute_builtin(char **str)
{
	if (!ft_strncmp("echo", str[0], 5))
		echo_option_n(str);
	else if (!ft_strncmp("cd", str[0], 3))
		cd(str);
	else if (!ft_strncmp("pwd", str[0], 4) && !str[1])
		pwd_no_option();
	else if (!ft_strncmp("export", str[0], 7))
		export(str);
	else if (!ft_strncmp("unset", str[0], 6))
		unset(str);
	else if (!ft_strncmp("env", str[0], 4) && !str[1])
		env(str);
}

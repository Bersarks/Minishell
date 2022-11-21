#include "../inc/minishell.h"

static void	process_cmds(char *cmds)
{
	char	**split_cmds;

	if (!quote_check(cmds, 0))
	{
		printf("Bad Quotes !\n");
		return ;
	}
	split_cmds = cmds_parser(cmds, -1);
	tokenizer(split_cmds);
}

void	begin_cmds(void)
{
	char	*cmds;

	while (1)
	{
		cmds = readline("$> ");
		if (ft_strncmp(cmds, "exit", ft_strlen("exit")) == 0)
			exit(0);
		if (!*cmds)
		{
			free(cmds);
			continue ;
		}
		else
			process_cmds(cmds);
		add_history(cmds);
		free(cmds);
	}
}

#include "../inc/minishell.h"

char	*only_word(char *input)
{
	char	*str;
	int		i;

	i = -1;
	str = malloc(sizeof(char) * word_len(input, 0) + 1);
	while (*input && ft_strchr("<|> \"\'", *input) == NULL)
	{
		str[++i] = *input;
		input++;
	}
	str[++i] = '\0';
	return (str);
}

char	*quoted_words(char	*usr_cmd)
{
	char	*word;
	char	quote;
	int		index;

	word = malloc(sizeof(char) * word_len(usr_cmd, 0) + 1);
	index = 0;
	quote = *usr_cmd;
	word[index++] = *usr_cmd++;
	while (*usr_cmd && *usr_cmd != quote)
		word[index++] = *usr_cmd++;
	word[index++] = *usr_cmd;
	word[index] = '\0';
	return (word);
}

void	remove_quotes(char **cmd)
{
	char	*tmp;
	int		i;

	i = -1;
	while (cmd && cmd[++i])
	{
		if (ft_strchr("\'\"", cmd[i][0]))
		{
			tmp = ft_substr(cmd[i], 1, ft_strlen(cmd[i]) - 2);
			free(cmd[i]);
			cmd[i] = tmp;
		}
	}
}

void	load_history(char *path)
{
	int		fd;
	char	*line;

	if (access(path, F_OK) == -1)
	{
		error_message("minishell: history file not found\n", 127);
		return ;
	}
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
	{
		error_message("minishell: error opening history file\n", 1);
		return ;
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		add_history(line);
		free(line);
	}
	close(fd);
}

void	cmd_history(char *cmd)
{
	int		fd;
	char	*path;

	path = ft_strjoin(find_in_env("HOME"), "/.minishell_history");
	fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0644);
	free(path);
	if (fd == -1)
	{
		error_message("minishell: error opening history file\n", 1);
		return ;
	}
	ft_printf(fd, "%s\n", cmd);
	add_history(cmd);
	close(fd);
}

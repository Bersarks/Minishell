#include "../inc/minishell.h"

// gelen char'a göre return yapar ~ işareti demek home directory demek onu returnler $$ demek pid demek ve $? exit status demek.
char	*get_paid(char c)
{
	char	*tmp;

	if (c == '~')
		return (find_env_home());
	else if (c == 'p')
	{
		tmp = ft_itoa(getpid());
		return (tmp);
	}
	else if (c == 'e')
		return (ft_itoa(g_shell->exit_status));
	return (0);
}

// stringin içinde sadece dolar veya tilda varsa one göre bir değer return eder.
char	*only_tilda_or_dollar(char *str)
{
	int	i;

	i = -1;
	if (!ft_strncmp("~", str, 2))
		return (get_paid('~'));
	else if (!ft_strncmp("$$", str, 3))
		return (get_paid('p'));
	else if (!ft_strncmp("$?", str, 3))
		return (get_paid('e'));
	else
	{
		while (str[++i])
			if (str[i] != '$')
				return (NULL);
		if (i > 2)
			return (ft_strdup("1den fazla pid gstermek gibi bir gorevim yok"));
	}
	return (NULL);
}

// get_dollar_value'de ki new için açılması gereken yeri hesaplar.
int	get_dollar_len(char *str, int len, char *paid)
{
	char	*value;

	while (*str)
	{
		if (*str == '$')
		{
			str++;
			if (*str == '$')
			{
				str++;
				len += ft_strlen(paid);
				free(paid);
				continue ;
			}
			value = get_value(str, 0);
			len += ft_strlen(value);
			while (ft_strchr("<|> \'\"$", *str) == NULL)
				str++;
		}
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}

// dolardan sonra gelen isme göre veriyi envden veya localden çeker.
char	*get_dollar_value(char *str, int idx)
{
	char	*new;
	char	*paid;
	char	*value;
	char	*tmp;

	new = ft_calloc(get_dollar_len(str, 0, get_paid('p') + 1), sizeof(char));
	tmp = str;
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			if (*str == '$') // ard arda dolar gelirse pid dönmeli
			{
				paid = get_paid('p');
				new = ft_strcat(new, paid);
				str++;
				idx += ft_strlen(paid);
				free(paid);
				continue ;
			}
			value = get_value(str, 0);
			idx += ft_strlen(value);
			new = ft_strcat(new, value);
			while (ft_strchr("<|> \'\"$", *str) == NULL)
				str++;
		}
		else
		{
			new[++idx] = *str;
			str++;
		}
	}
	new[++idx] = 0;
	free(tmp);
	return (new);
}

// dolar karakterini ayrıştırır ve değeri localden veya envden çekerek değiştirir.
char	*token_proccess(char *str)
{
	if (!str)
		return (NULL);
	if (only_tilda_or_dollar(str) != NULL)
		str = only_tilda_or_dollar(str);
	else if (ft_strchr(str, '$') && (ft_strchr(str, '\'')
		|| ft_strchr(str, '\"'))) // eğer ki string, dolar ve tırnak içeriyorsa.
		str = with_quotes(str);
	else if (ft_strchr(str, '$'))
		str = get_dollar_value(str, -1);
	return (str);
}

// parçalanmış inputta gezer ve tırnağın içinde $ görürse tırnağı parçalar içindeki değişkenlerin valuelerini çeker mesela $HOME var ise onun yerine /home/canodis yazar tırnak dışındaki değişkenlere de aynısını yapar.
char	**tokenizer(char **d_input)
{
	int	i;

	i = -1;
	while (d_input[++i])
		d_input[i] = token_proccess(d_input[i]);
	return (d_input);
}
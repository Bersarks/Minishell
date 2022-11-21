#include "../inc/minishell.h"

// doların valuesini döndürür.
char	*get_value(char *str, int i)
{
	char	*value;
	char	*res;

	while (ft_strchr("<|> \'\"$", str[i]) == NULL)
		i++;
	if (i > 0)
		value = ft_substr(str, 0, i);
	res = find_in_env(value);
	if (!res)
		res = find_in_local(value);
	free(value);
	return (res);
}

// tırnağın içi parçalara ayrılır ve doların değeri envden veya localden çekilir.
char	*with_quotes(char *str)
{
	char	*new; // yeri bulmak için fonksiyon yazılacak ! :/

	if (*str == '\'')
		return (str);
	else if (*str == '\"')
		new = get_dollar_value(str, -1);
	return (new);
}

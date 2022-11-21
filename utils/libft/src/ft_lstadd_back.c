#include "../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*swap;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			swap = ft_lstlast(*lst);
			swap->next = new;
		}
	}
}

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *acc;

	while (*lst)
	{
		del((*lst)->content);
		acc = (*lst)->next;
		free(*lst);
		*lst = acc;
	}
}

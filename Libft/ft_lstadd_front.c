#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*begin;

	begin = new;
	begin->next = *lst;
	*lst = begin;
}

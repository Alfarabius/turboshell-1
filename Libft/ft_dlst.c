#include "libft.h"

t_dlst	*ft_dlst_new(void *content)
{
	t_dlst *new_dlst;

	new_dlst = (t_dlst *)malloc(sizeof(t_dlst));
	if (new_dlst == NULL)
		return (NULL);
	new_dlst->content = content;
	new_dlst->next = NULL;
	new_dlst->prev = NULL;
	return (new_dlst);
}

void	ft_dlstadd_back(t_dlst **dlst, t_dlst *new)
{
	t_dlst	*last;
	t_dlst	*curr;

	if (*dlst == NULL)
	{
		*dlst = new;
		return ;
	}
	curr = *dlst;
	while (curr->next != NULL)
		curr = curr->next;
	last = new;
	curr->next = last;
	last->prev = curr;
}

int	ft_dlstsize(t_dlst *dlst)
{
	int		size;

	size = 0;
	while (dlst)
	{
		size++;
		dlst = dlst->next;
	}
	return (size);
}

t_dlst	*ft_dlstlast(t_dlst *dlst)
{
	t_dlst	*ptr;

	if (!dlst)
		return (dlst);
	ptr = dlst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

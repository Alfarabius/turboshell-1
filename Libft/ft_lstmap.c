/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:42:54 by mrosie            #+#    #+#             */
/*   Updated: 2020/11/03 14:33:35 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*begin_new_lst;

	if (!lst)
		return (NULL);
	new_lst = ft_lstnew(f(lst->content));
	if (!new_lst)
		return (NULL);
	begin_new_lst = new_lst;
	lst = lst->next;
	while (lst)
	{
		new_lst->next = ft_lstnew(f(lst->content));
		if (!new_lst)
			ft_lstclear(&begin_new_lst, *del);
		lst = lst->next;
		new_lst = new_lst->next;
	}
	return (begin_new_lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:37:57 by mrosie            #+#    #+#             */
/*   Updated: 2020/10/31 17:52:11 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *ptr;
	unsigned char acc;

	ptr = (unsigned char *)s;
	acc = (unsigned char)c;
	while (n--)
		if (*ptr++ == acc)
			return (ptr - 1);
	return (NULL);
}

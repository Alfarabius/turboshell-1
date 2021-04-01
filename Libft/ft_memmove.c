/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:29:14 by mrosie            #+#    #+#             */
/*   Updated: 2020/11/05 11:13:18 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d < s)
		while (len--)
			*(d++) = *(s++);
	else
	{
		d += (len - 1);
		s += (len - 1);
		while (len--)
			*(d--) = *(s--);
	}
	return (dst);
}

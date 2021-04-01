/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:37:52 by mrosie            #+#    #+#             */
/*   Updated: 2020/11/05 10:44:13 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dst_len;
	size_t i;

	dst_len = 0;
	i = 0;
	while (dst[dst_len] && dst_len < dstsize)
		dst_len++;
	if (dst_len < dstsize)
	{
		while (src[i] && (dst_len + i) < dstsize - 1)
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[i + dst_len] = '\0';
	}
	return (dst_len + ft_strlen(src));
}

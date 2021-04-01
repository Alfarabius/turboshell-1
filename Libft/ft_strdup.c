/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 09:47:58 by mrosie            #+#    #+#             */
/*   Updated: 2020/11/02 18:32:47 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	dest_size;

	dest_size = ft_strlen(s1) + 1;
	dest = (char *)malloc(dest_size * sizeof(char));
	if (NULL == dest)
		return (NULL);
	ft_memcpy(dest, s1, dest_size);
	return (dest);
}

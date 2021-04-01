/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:04:42 by mrosie            #+#    #+#             */
/*   Updated: 2020/11/05 17:15:33 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_size;

	if (*needle == '\0')
		return ((char *)haystack);
	needle_size = ft_strlen(needle);
	while (*haystack != '\0' && len-- >= needle_size)
	{
		if (*haystack == *needle)
			if (ft_strncmp(haystack, needle, needle_size) == 0)
				return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

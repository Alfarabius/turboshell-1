/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:32:32 by mrosie            #+#    #+#             */
/*   Updated: 2020/11/02 11:41:39 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_string;
	size_t	length;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined_string = (char *)malloc(length);
	if (!joined_string)
		return (NULL);
	ft_memcpy(joined_string, s1, length);
	ft_strlcat(joined_string, s2, length);
	return (joined_string);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:47:05 by mrosie            #+#    #+#             */
/*   Updated: 2020/10/31 18:09:43 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t len;

	len = ft_strlen(s);
	while (s[len] != (char)c && len)
		len--;
	if (s[len] == (char)c)
		return ((char *)&s[len]);
	return (NULL);
}

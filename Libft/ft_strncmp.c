/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:42:34 by mrosie            #+#    #+#             */
/*   Updated: 2020/10/31 16:12:39 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	while ((tmp1[i] != '\0' || tmp2[i] != '\0') && i != n)
	{
		if ((tmp1[i] - tmp2[i]) != 0)
			return (tmp1[i] - tmp2[i]);
		i++;
	}
	return (0);
}

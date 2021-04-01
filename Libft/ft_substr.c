/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfarabi <alfarabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:18:48 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/01 18:05:22 by alfarabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	str_size;
	size_t	sub_size;

	if (!s)
		return (NULL);
	str_size = ft_strlen(s);
	if (start >= str_size || !*s)
		return (ft_strdup(""));
	if ((str_size - start) > len)
		sub_size = len;
	else
		sub_size = str_size - start;
	substring = (char *)malloc((sub_size + 1) * sizeof(char));
	if (NULL == substring)
		return (NULL);
	if (start < str_size)
		ft_memcpy(substring, &s[start], sub_size);
	substring[sub_size] = '\0';
	return (substring);
}

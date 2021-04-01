/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:45:39 by mrosie            #+#    #+#             */
/*   Updated: 2020/11/02 12:50:21 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_string;
	size_t	end;
	size_t	start;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end && ft_strchr(set, s1[end]))
		end--;
	len = (end - start + 1);
	new_string = ft_substr(s1, start, len);
	return (new_string);
}

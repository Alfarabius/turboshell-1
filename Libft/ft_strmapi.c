/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:55:01 by mrosie            #+#    #+#             */
/*   Updated: 2020/11/03 11:58:09 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_string;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	new_string = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_string)
		return (NULL);
	while (s[i++])
		new_string[i - 1] = f(i - 1, s[i - 1]);
	new_string[i - 1] = '\0';
	return (new_string);
}

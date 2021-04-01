/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 09:21:52 by mrosie            #+#    #+#             */
/*   Updated: 2020/10/30 09:45:08 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *memory;

	memory = malloc(count * size);
	if (NULL == memory)
		return (NULL);
	ft_bzero(memory, size * count);
	return (memory);
}

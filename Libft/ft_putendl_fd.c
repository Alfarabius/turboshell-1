/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:56:31 by mrosie            #+#    #+#             */
/*   Updated: 2020/11/01 16:08:52 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t num_bytes;

	if (!s)
		return ;
	num_bytes = 0;
	while (s[num_bytes])
		num_bytes++;
	write(fd, s, num_bytes);
	write(fd, "\n", 1);
}

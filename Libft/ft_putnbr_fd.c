/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:02:18 by mrosie            #+#    #+#             */
/*   Updated: 2020/10/31 15:16:00 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	show_num[32];
	int		i;
	long	tmp;

	i = 0;
	tmp = (long)n;
	if (!n)
		write(fd, "0", 1);
	if (tmp < 0)
	{
		write(fd, "-", 1);
		tmp *= -1;
	}
	while (tmp)
	{
		show_num[i] = (tmp % 10) + '0';
		tmp = tmp / 10;
		i++;
	}
	while (i)
		write(fd, &show_num[--i], 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:32:22 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/10 16:32:25 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_symamount_base(long n, int base)
{
	int amount;

	amount = 0;
	if (n == 0)
		return (1);
	if (n < 0 && (amount += 1))
		n *= -1;
	while (n)
	{
		amount++;
		n /= base;
	}
	return (amount);
}

char		*ft_itoa_base(long n, int base, char uppercase)
{
	char	*str;
	int		start;
	int		end;
	long	tmp;

	start = 0;
	end = ft_symamount_base(n, base);
	if (!(str = (char *)malloc(end + 1)))
		return (NULL);
	if (n < 0 && (str[0] = '-') && (n *= -1))
		start += 1;
	str[end] = '\0';
	while (end-- > start)
	{
		tmp = n % base;
		if (tmp >= 10 && uppercase)
			str[end] = (char)(tmp - 10 + 'A');
		else if (tmp >= 10 && !uppercase)
			str[end] = (char)(tmp - 10 + 'a');
		else
			str[end] = (char)(tmp + '0');
		n /= base;
	}
	return (str);
}

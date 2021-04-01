/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:30:59 by mrosie            #+#    #+#             */
/*   Updated: 2020/11/05 17:10:11 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_symamount(int n)
{
	size_t	symb_amount;

	symb_amount = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		symb_amount += 1;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		symb_amount++;
	}
	return (symb_amount);
}

char		*ft_itoa(int n)
{
	char	*n_str;
	int		size;
	int		i;

	i = 0;
	size = ft_symamount(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	n_str = (char *)malloc(size + 1);
	if (!n_str)
		return (NULL);
	if (n < 0)
	{
		n_str[0] = '-';
		n *= -1;
		i += 1;
	}
	n_str[size] = '\0';
	while (size-- > i)
	{
		n_str[size] = (char)(n % 10 + '0');
		n /= 10;
	}
	return (n_str);
}

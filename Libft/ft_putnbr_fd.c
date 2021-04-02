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

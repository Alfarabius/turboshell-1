#include "libft.h"

void	ft_putnbr_fd_base(int n, int fd, int base)
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
	while (n)
	{
		tmp = n % base;
		if (tmp >= 10)
			show_num[i] = (char)(tmp - 10 + 'A');
		else
			show_num[i] = (char)(tmp + '0');
		n /= base;
		i++;
	}
	while (i)
		write(fd, &show_num[--i], 1);
}

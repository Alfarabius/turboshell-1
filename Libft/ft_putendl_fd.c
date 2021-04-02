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

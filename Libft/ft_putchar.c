#include "libft.h"

int	ft_putchar(int ch)
{
	write(1, &ch, 1);
	return (0);
}

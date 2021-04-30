#include "libft.h"

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		ft_putendl_fd(arr[i++], 1);
}

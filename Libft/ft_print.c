#include "libft.h"

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		ft_putendl_fd(arr[i++], 1);
}

// void	print_dict(t_list *lstd)
// {
// 	while(lstd)
// 	{
// 		printf("\nkey = %s value = %s\n", ((t_dict *)(lstd->content))->key, ((t_dict *)(lstd->content))->value);
// 		lstd = lstd->next;
// 	}
// }

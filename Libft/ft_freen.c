#include "libft.h"

void	ft_freen(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

#include "libft.h"

void	ft_freen(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;

	memory = malloc(count * size);
	if (NULL == memory)
		return (NULL);
	ft_bzero(memory, size * count);
	return (memory);
}

#include "libft.h"

void	*ft_memjoin(void *s1, void *s2, size_t l1, size_t l2)
{
	char	*new_mem;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = l1 + l2;
	new_mem = (char *)malloc(len);
	if (new_mem != NULL)
	{
		ft_memcpy(new_mem, s1, l1);
		ft_memcpy(new_mem + l1, s2, l2);
	}
	return (new_mem);
}

void	*ft_memdup(const void* mem, size_t size)
{
	void*	new_mem;

	new_mem = malloc(size);
	if(new_mem != NULL)
		ft_memcpy(new_mem, mem, size);
	return (new_mem);
}

char	**ft_freearr(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i])
		ft_freen((void **)&arr[i++]);
	if (arr)
		free(arr);
	return (NULL);
}

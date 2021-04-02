#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	dest_size;

	dest_size = ft_strlen(s1) + 1;
	dest = (char *)malloc(dest_size * sizeof(char));
	if (NULL == dest)
		return (NULL);
	ft_memcpy(dest, s1, dest_size);
	return (dest);
}

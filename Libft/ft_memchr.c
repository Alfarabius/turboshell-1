#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *ptr;
	unsigned char acc;

	ptr = (unsigned char *)s;
	acc = (unsigned char)c;
	while (n--)
		if (*ptr++ == acc)
			return (ptr - 1);
	return (NULL);
}

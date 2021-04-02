#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*d;
	unsigned char			*s;
	unsigned char			acc;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	acc = (unsigned char)c;
	if (!d && !s)
		return (NULL);
	while (n--)
	{
		*(d++) = *(s++);
		if (*(s - 1) == acc)
			return (d);
	}
	return (NULL);
}

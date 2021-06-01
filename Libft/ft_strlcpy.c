#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_size;

	if (src == NULL && dst == NULL)
		return (0);
	i = dstsize - 1;
	src_size = ft_strlen(src);
	if (dstsize)
	{
		while (i-- && *src)
			*(dst++) = *(src++);
		*dst = '\0';
	}
	return (src_size);
}

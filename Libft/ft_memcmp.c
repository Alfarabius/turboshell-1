#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *s1_ptr;
	const unsigned char *s2_ptr;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	while (n--)
		if ((*s1_ptr - *s2_ptr) != 0)
			return (*s1_ptr - *s2_ptr);
		else
		{
			s1_ptr++;
			s2_ptr++;
		}
	return (0);
}

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t len;

	len = ft_strlen(s);
	while (s[len] != (char)c && len)
		len--;
	if (s[len] == (char)c)
		return ((char *)&s[len]);
	return (NULL);
}

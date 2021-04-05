#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	while ((tmp1[i] != '\0' || tmp2[i] != '\0'))
	{
		if ((tmp1[i] - tmp2[i]) != 0)
			return (tmp1[i] - tmp2[i]);
		i++;
	}
	return (0);
}

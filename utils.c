#include "minishell.h"

int		ft_putint(int c)
{
	return (write(1, &c, 1));
}

char	*ft_memjoin_tsh(char *s1, char *s2)
{
	char *str;

	str = ft_strjoin(s1, s2);
	error_checker(!str, "memmory doesn't allocated", 1);
	ft_freen(s1);
	return (str);
}

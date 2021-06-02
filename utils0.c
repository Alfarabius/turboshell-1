#include "minishell.h"

void	arg_to_lower(t_tsh *tsh)
{
	int		len;
	char	*res;

	if (tsh->prsr.args[0])
	{
		len = ft_strlen(tsh->prsr.args[0]);
		res = (char *)malloc(sizeof(char) * (len + 1));
		res[len] = '\0';
		while (--len >= 0)
			res[len] = ft_tolower(tsh->prsr.args[0][len]);
		free(tsh->prsr.args[0]);
		tsh->prsr.args[0] = res;
	}
}

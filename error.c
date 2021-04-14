#include "minishell.h"

int	error_handler(char *msg, char flg)
{
	ft_putstr_fd(msg, 2);
	if (flg)
		exit(1);
	return (1);
}

void error_checker(int cond, char *msg, char flg)
{
	if (cond)
		error_handler(msg, flg);
}

#include "minishell.h"

int	error_handler(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

void error_checker(int cond, char *msg)
{
	if (cond)
		error_handler(msg);
}

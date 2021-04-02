#include "minishell.h"

int	error_handler(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
	return(1);
}

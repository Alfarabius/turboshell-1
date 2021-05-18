#include "minishell.h"

int	error_handler(char *msg, char flg)
{
	ft_putstr_fd(msg, 2);
	g_exit_status = 1;
	if (flg)
		exit(1);
	return (1);
}

void	error_checker(int cond, char *msg, char flg)
{
	if (cond)
		error_handler(msg, flg);
}

void	error_template(char *head, char *arg, char *error)
{
	ft_putstr_fd(head, 2);
	write(2, ": ", 2);
	ft_putstr_fd(arg, 2);
	write(2, ": ", 2);
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
}

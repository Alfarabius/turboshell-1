#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
	}
	else if (signum == SIGQUIT)
	{
		g_exit_status = 131;
		ft_putstr_fd("Quit: 3\n", 1);
	}
	signal(signum, signal_handler);
}

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_exit_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_exit_status = 131;
	}
}

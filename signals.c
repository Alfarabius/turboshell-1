#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
		write(1, "\n", 1);
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
	signal(signum, signal_handler);
}

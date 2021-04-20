#include "minishell.h"

static	void	interrupt(int segnum)
{
	write(1, "CTRL-C", 6);
	signal(SIGINT, interrupt);
}

static	void	quit(int segnum)
{
	write(1, "CTRL-\\", 6);
	signal(SIGQUIT, quit);
}

int	signal_handler(t_tsh *tsh)
{
	signal(SIGINT, interrupt); // ctrl-c
	signal(SIGQUIT, quit);	 /* ctrl-\ */
	return (0);
}

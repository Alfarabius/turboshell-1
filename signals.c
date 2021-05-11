#include "minishell.h"

static	void	interrupt(int segnum)
{
	g_exit_status = 130;
}

static	void	quit(int segnum)
{
	g_exit_status = 131;
}

int	signal_handler(t_tsh *tsh)
{
	signal(SIGINT, interrupt);
	signal(SIGQUIT, quit);
	return (0);
}

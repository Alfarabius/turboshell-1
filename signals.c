#include "minishell.h"

static	void	interrupt(int segnum)
{
	g_exit_status = 130;
}

static	void	quit(int segnum)
{
	g_exit_status = 131;
}

void	swich_signals(t_tsh *tsh)
{
	if (tsh->term.c_lflag & ISIG)
		tsh->term.c_lflag &= ~ISIG;
	else
		tsh->term.c_lflag |= ISIG;
	tcsetattr(0, TCSANOW, &tsh->term);
}

int	signal_handler(t_tsh *tsh)
{
	signal(SIGINT, interrupt);
	signal(SIGQUIT, quit);
	return (0);
}

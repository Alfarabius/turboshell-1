#include "minishell.h"

int	termcap_processor(char *buf, t_tsh *tsh)
{
	if (!ft_strcmp(buf, "\033[A"))
		tsh->is_termcap = history_up(tsh);
	else if (!ft_strcmp(buf, "\033[B"))
		tsh->is_termcap = history_down(tsh);
	else if (!ft_strcmp(buf, "\177"))
		tsh->is_termcap = erase_symbol(tsh);
	else if (!ft_strcmp(buf, "\033[D"))
	{
		tputs(cursor_right, 1, ft_putint);
		tsh->is_termcap = 1;
	}
	else if (!ft_strcmp(buf, "\033[C"))
	{
		tputs(cursor_left, 1, ft_putint);
		tsh->is_termcap = 1;
	}
	return (0);
}

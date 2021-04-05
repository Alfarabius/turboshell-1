#include "minishell.h"

int	history_up(t_tsh *tsh)
{
	term_clean_up();
	ft_putstr_fd("history up", 1);
	return (0);
}

int	history_down(t_tsh *tsh)
{
	term_clean_up();
	ft_putstr_fd("history down", 1);
	return (0);
}

int	move_right_line(t_tsh *tsh)
{
	term_clean_up();
	ft_putstr_fd("right", 1);
	return (0);
}

int	move_left_line(t_tsh *tsh)
{
	term_clean_up();
	ft_putstr_fd("left", 1);
	return (0);
}

int	erase_symbol(t_tsh *tsh)
{
	term_clean_up();
	ft_putstr_fd("<-", 1);
	return (0);
}

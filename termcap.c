#include "minishell.h"

int	term_clean_up(void)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	return (0);
}

int	termcap_processor(char *line, t_tsh *tsh)
{
	if (!ft_strcmp(line, "\033[A"))
		history_up(tsh);
	else if (!ft_strcmp(line, "\033[B"))
		history_down(tsh);
	else if (!ft_strcmp(line, "\033[C"))
		move_right_line(tsh);
	else if (!ft_strcmp(line, "\033[D"))
		move_left_line(tsh);
	else if (!ft_strcmp(line, "\177"))
		erase_symbol(tsh);
	return (0);
}

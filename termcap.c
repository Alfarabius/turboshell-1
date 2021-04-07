#include "minishell.h"

int	add_to_history(t_tsh tsh)
{
	return (0);
}

int	termcap_processor(char *line, t_tsh *tsh)
{

	if (!ft_strcmp(line, "\033[A"))
		history_up(tsh);
	else if (!ft_strcmp(line, "\033[B"))
		history_down(tsh);
	else if (!ft_strcmp(line, "\177"))
		erase_symbol(tsh);
	return (0);
}

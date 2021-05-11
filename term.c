#include "minishell.h"

int	new_prompt(t_tsh *tsh)
{
	tsh->end_line = 0;
	tsh->his_ptr = ft_dlstlast(tsh->his);
	write(1, TSH_NAME, 26);
	tputs(save_cursor, 1, ft_putchar);
	return (0);
}

void	switch_term_attr(t_tsh *tsh)
{
	char	*err_msg;

	if (tsh->term.c_lflag & (ECHO | ICANON | ISIG))
		tsh->term.c_lflag &= ~(ECHO | ICANON | ISIG);
	else
		tsh->term.c_lflag |= (ECHO | ICANON | ISIG);
	if (tcsetattr(0, TCSANOW, &tsh->term) == -1)
	{
		err_msg = strerror(errno);
		error_handler(err_msg, 1);
	}
}

#include "minishell.h"

void	ctrl_d(t_tsh *tsh)
{
	free(tsh->line);
	tsh->end_line = 1;
	tsh->line = ft_strdup("exit");
	if (!tsh->line)
		error_handler("memmory doesn't allocated", 0);
}

void	ctrl_c(t_tsh *tsh)
{
	ft_bzero(tsh->line, ft_strlen(tsh->line));
	ft_bzero(tsh->buf, 1024);
	g_exit_status = 1;
	write(1, "\n", 1);
	new_prompt(tsh);
}

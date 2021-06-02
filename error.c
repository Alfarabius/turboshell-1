#include "minishell.h"

int	error_handler(char *msg, char flg)
{
	ft_putstr_fd(msg, 2);
	if (flg)
		exit(g_exit_status);
	return (1);
}

void	error_checker(int cond, char *msg, char flg)
{
	if (cond)
		error_handler(msg, flg);
}

void	error_template(char *head, char *arg, char *error)
{
	ft_putstr_fd(head, 2);
	write(2, ": ", 2);
	ft_putstr_fd(arg, 2);
	write(2, ": ", 2);
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
}

void	error_template_prsr(char *head, char *arg, char *error, t_tsh *tsh)
{
	ft_putstr_fd(head, 2);
	write(2, ": ", 2);
	ft_putstr_fd(arg, 2);
	write(2, ": ", 2);
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
	tsh->prsr.parse_status = 0;
}

void	print_syntax_error(int i, t_tsh *tsh)
{
	g_exit_status = 2;
	write(2, "turboshell-1.0: syntax error near unexpected token `", 52);
	write(2, &tsh->line[i], 1);
	if (tsh->line[i] == tsh->line[i + 1] && ft_strchr(";>", tsh->line[i]))
		write(2, &tsh->line[i], 1);
	write(2, "'\n", 2);
}

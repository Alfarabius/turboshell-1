#include "minishell.h"

static void	not_numeric_proc(char *arg, t_tsh *tsh)
{
	error_template("turboshell-1.0: exit", \
	arg, "numeric argument required");
	save_history_exit(255, tsh);
}

static void	too_many_args_proc()
{
	g_exit_status = 1;
	error_template("turboshell-1.0", "exit", "too many arguments");
}

void	ft_exit(t_tsh *tsh, int i)
{
	if (!tsh->prsr.pipe.count)
		write(1, "exit\n", 6);
	if (tsh->prsr.args[1] && \
	(tsh->prsr.args[1][0] == '-' || tsh->prsr.args[1][0] == '+'))
	{
		if (!tsh->prsr.args[1][1])
			not_numeric_proc(tsh->prsr.args[1], tsh);
		i = 0;
	}
	while (tsh->prsr.args[1] && tsh->prsr.args[1][++i])
	{
		if (!ft_isdigit(tsh->prsr.args[1][i]))
			not_numeric_proc(tsh->prsr.args[1], tsh);
	}
	i = 1;
	while (tsh->prsr.args[i])
		i++;
	if (i > 2)
		return (too_many_args_proc());
	if (i == 2)
		save_history_exit(ft_atoi(tsh->prsr.args[1]), tsh);
	save_history_exit(0, tsh);
}

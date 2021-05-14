#include "minishell.h"

int	cmd_processor(t_tsh *tsh)
{
	open_redirects(tsh);
	if (tsh->prsr.parse_status == 99)
		return (1);
	if (tsh->prsr.args[0] && !ft_strcmp("exit", tsh->prsr.args[0]))
		ft_exit(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("echo", tsh->prsr.args[0]))
		ft_echo(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("cd", tsh->prsr.args[0]))
		ft_cd(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("pwd", tsh->prsr.args[0]))
		ft_pwd(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("export", tsh->prsr.args[0]))
		ft_export(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("unset", tsh->prsr.args[0]))
		ft_unset(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("env", tsh->prsr.args[0]))
		ft_env(tsh);
	else if (tsh->prsr.args[0])
		binary_processor(tsh);
	close_redirects(tsh);
	return (0);
}

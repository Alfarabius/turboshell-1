#include "minishell.h"

int	cmd_processor(t_tsh *tsh)
{
	if (tsh->prsr->args[0] && !ft_strcmp("exit", tsh->prsr->args[0]))
		ft_exit(*tsh);
	else if(tsh->prsr->args[0] && !ft_strcmp("echo", tsh->prsr->args[0]))
		ft_echo(tsh);
	else if(tsh->prsr->args[0] && !ft_strcmp("cd", tsh->prsr->args[0]))
		;
	else if(tsh->prsr->args[0] && !ft_strcmp("pwd", tsh->prsr->args[0]))
		ft_pwd(tsh);
	else if(tsh->prsr->args[0] && !ft_strcmp("export", tsh->prsr->args[0]))
		;
	else if(tsh->prsr->args[0] && !ft_strcmp("unset", tsh->prsr->args[0]))
		ft_unset(tsh);
	else if(tsh->prsr->args[0] && !ft_strcmp("env", tsh->prsr->args[0]))
		ft_env(tsh);
	return (0);
}

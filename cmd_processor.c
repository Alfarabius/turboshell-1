#include "minishell.h"

int	cmd_processor(t_tsh *tsh)
{
	if (!ft_strcmp("exit", tsh->prsr->args[0]))
		ft_exit(*tsh);
	else if(!ft_strcmp("echo", tsh->prsr->args[0]))
		;
	else if(!ft_strcmp("cd", tsh->prsr->args[0]))
		;
	else if(!ft_strcmp("pwd", tsh->prsr->args[0]))
		;
	else if(!ft_strcmp("export", tsh->prsr->args[0]))
		;
	else if(!ft_strcmp("unset", tsh->prsr->args[0]))
		;
	else if(!ft_strcmp("env", tsh->prsr->args[0]))
		ft_env(tsh);
	return (0);
}

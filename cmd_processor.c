#include "minishell.h"

int	cmd_processor(t_prsr *prsr)
{
	if (!ft_strcmp("exit", prsr->args[0]))
		ft_exit();
	else if(!ft_strcmp("echo", prsr->args[0]))
		;
	else if(!ft_strcmp("cd", prsr->args[0]))
		;
	else if(!ft_strcmp("pwd", prsr->args[0]))
		;
	else if(!ft_strcmp("export", prsr->args[0]))
		;
	else if(!ft_strcmp("unset", prsr->args[0]))
		;
	else if(!ft_strcmp("env", prsr->args[0]))
		;
	return (0);
}

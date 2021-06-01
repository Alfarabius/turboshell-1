#include "minishell.h"

void	ft_env(t_tsh *tsh)
{
	t_list	*temp;

	temp = tsh->env;
	while (tsh->env)
	{
		if (((t_dict *)(tsh->env->content))->is_set)
		{
			printf("%s=", ((t_dict *)(tsh->env->content))->key);
			printf("%s\n", ((t_dict *)(tsh->env->content))->value);
		}
		if (!tsh->env->next)
			break ;
		tsh->env = tsh->env->next;
	}
	tsh->env = temp;
	g_exit_status = 0;
}

void	ft_pwd(void)
{
	char	wpath[PATH_MAX];

	getcwd((char *)wpath, PATH_MAX);
	ft_putendl_fd(wpath, 1);
	g_exit_status = 0;
}

void	ft_echo(t_tsh *tsh)
{
	int	cur_arg;
	int	flag_n;

	flag_n = 0;
	cur_arg = 1;
	while (tsh->prsr.args[cur_arg] && !ft_strcmp(tsh->prsr.args[cur_arg], "-n"))
	{
		flag_n = 1;
		cur_arg++;
	}
	while (tsh->prsr.args[cur_arg])
	{
		ft_putstr_fd(tsh->prsr.args[cur_arg], 1);
		if (tsh->prsr.args[cur_arg + 1])
			write(1, " ", 1);
		cur_arg++;
	}
	if (!flag_n)
		write(1, "\n", 1);
	g_exit_status = 0;
}

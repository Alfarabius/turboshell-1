#include "minishell.h"

void	ft_exit(t_tsh *tsh)
{
	int	i;

	if (!tsh->prsr.pipe.count)
		write(1, "exit\n", 6);
	i = -1;
	if(tsh->prsr.args[1] &&
	(tsh->prsr.args[1][0] == '-' || tsh->prsr.args[1][0] == '+'))
		i = 0;
	while (tsh->prsr.args[1] && tsh->prsr.args[1][++i])
	{
		if (!ft_isdigit(tsh->prsr.args[1][i]))
		{
			error_template("turboshell-1.0: exit", \
			tsh->prsr.args[1], "numeric argument required");
			save_history_exit(255, tsh);
		}
	}
	i = 1;
	while (tsh->prsr.args[i])
		i++;
	if (i > 2)
	{
		g_exit_status = 1;
		return (error_template("turboshell-1.0", "exit", "too many arguments"));
	}
	if (i == 2)
		save_history_exit(ft_atoi(tsh->prsr.args[1]), tsh);
	save_history_exit(0, tsh);
}

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

void	ft_unset(t_tsh *tsh)
{
	int		i;
	t_list	*current;
	t_list	*prev;

	i = 0;
	while (tsh->prsr.args[++i])
	{
		if (!ft_isalpha(tsh->prsr.args[i][0]))
		{
			builtin_error("` not a valid identifier", tsh->prsr.args[i], "unset: '");
			continue ;
		}
		current = tsh->env;
		prev = tsh->env;
		while (current)
		{
			if (!ft_strcmp(((t_dict *)current->content)->key, tsh->prsr.args[i]))
				break ;
			prev = current;
			current = current->next;
		}
		if (current)
		{
			prev->next = current->next;
			if (prev == current)
				tsh->env = current->next;
			((t_dict *)current->content)->is_set = 0;
		}
	}
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

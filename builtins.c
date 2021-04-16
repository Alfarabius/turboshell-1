#include "minishell.h"

void ft_exit(t_tsh tsh)
{
	int i;

	write(1, "\nexit\n", 6);
	i = -1;
	while(tsh.prsr->args[1] && tsh.prsr->args[1][++i])
	{
		if (!ft_isdigit(tsh.prsr->args[1][i]))
		{
			write(2, "turboshell-1.0: exit: ", 23);
			ft_putstr_fd(tsh.prsr->args[1], 2);
			write(2, ": numeric argument required\n", 28);
			exit (255);
		}
	}
	i = 1;
	while(tsh.prsr->args[i])
		i++;
	if (i > 2)
	{
		write(2, "turboshell-1.0: exit: too many arguments\n", 41);
		return ;
	}
	if (i == 2)
		exit(ft_atoi(tsh.prsr->args[1]));
	exit(0);
}

void ft_env(t_tsh *tsh)
{
	t_list *temp;

	temp = tsh->env;
	while (tsh->env)
	{
		printf("%s=",((t_dict *)(tsh->env->content))->key);
		printf("%s\n",((t_dict *)(tsh->env->content))->value);
		if (!tsh->env->next)
			break ;
		tsh->env = tsh->env->next;
	}
	tsh->env = temp;
}

void ft_unset(t_tsh *tsh)
{
	int		i;
	t_list	*current;
	t_list	*prev;

	i = 0;
	while (tsh->prsr->args[++i])
	{
		current = tsh->env;
		prev = tsh->env;
		while (current)
		{
			if (!ft_strncmp(((t_dict *)current->content)->key, tsh->prsr->args[i], ft_strlen(((t_dict *)current->content)->key)))
				break ;
			prev = current;
			current = current->next;
		}
		if (current)
		{
			prev->next = current->next;
			if (prev == current)
				tsh->env = current->next;
			free(((t_dict *)current->content)->key);
			free(((t_dict *)current->content)->value);
			free(((t_dict *)current->content));
			free((t_dict *)current);
		}
	}
}

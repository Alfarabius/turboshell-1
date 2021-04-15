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
	int		i;
	int		j;
	t_list	*temp;
	char	**current;

	i = 1;
	while (tsh->prsr->args[i])
		i++;
	if (i >= 2)
	{
		if (tsh->prsr->args[1][0] == '=')
		{
			write(2, "env: setenv ", 12);
			ft_putstr_fd(tsh->prsr->args[1], 2);
			write(2, ": Invalid argument\n", 19);
			return ;
		}
		elem_to_lst(tsh->prsr->args[1], &tsh->env);
	}
	temp = tsh->env;
	//удалить после выполнения ласт эелемент
	//отправить на выполнение команду из аргументов
	//обработка кейса когда отсутсвует =
	//посмотреть что происходит если встречаются вайтспейсы
	while (tsh->env)
	{
		printf("%s=",((t_dict *)(tsh->env->content))->key);
		printf("%s\n",((t_dict *)(tsh->env->content))->value);
		tsh->env = tsh->env->next;
	}
	tsh->env = temp;
}

#include "minishell.h"

static	void	write_export(t_tsh *tsh)
{
	t_list	*temp;

	temp = tsh->env;
	sort_dict_ascii(&tsh->env);
	while (tsh->env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(((t_dict *)(tsh->env->content))->key, 1);
		if (((t_dict *)(tsh->env->content))->is_set)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(((t_dict *)(tsh->env->content))->value, 1);
			ft_putstr_fd("\"", 1);
		}
		write(1, "\n", 1);
		if (!tsh->env->next)
			break ;
		tsh->env = tsh->env->next;
	}
	tsh->env = temp;
}

void	ft_export(t_tsh *tsh)
{
	int		current;
	t_dict	*elem;
	t_list	*temp;

	if (!tsh->prsr.args[1])
		write_export(tsh);
	else
	{
		current = 0;
		temp = NULL;
		while (tsh->prsr.args[++current])
		{
			elem_to_lst(tsh->prsr.args[current], &temp);
			elem = get_env_elem(*tsh, ((t_dict *)(temp->content))->key);
			if (elem)
			{
				ft_freen((void **)&elem->value);
				elem->value = ((t_dict *)(temp->content))->value;
			}
			else
			{
				elem_to_lst(tsh->prsr.args[current], &tsh->env);
				ft_freen((void **)&((t_dict *)(temp->content))->value);
			}
		}
		ft_freen((void **)&((t_dict *)(temp->content))->key);
		ft_freen((void **)&(temp->content));
		ft_freen((void **)&temp);
	}
}

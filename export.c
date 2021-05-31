#include "minishell.h"

static	void	write_export(t_tsh *tsh)
{
	t_list	*sorted;
	t_list	*temp;

	sorted = dictlstdup(tsh->env);
	temp = sorted;
	sort_dict_ascii(&sorted);
	while (sorted)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(((t_dict *)(sorted->content))->key, 1);
		if (((t_dict *)(sorted->content))->is_separ)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(((t_dict *)(sorted->content))->value, 1);
			ft_putstr_fd("\"", 1);
		}
		write(1, "\n", 1);
		if (!sorted->next)
			break ;
		sorted = sorted->next;
	}
	sorted = temp;
	ft_lstclear(&sorted, dictdelone);
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
			if (tsh->prsr.args[current][0] && \
			!ft_isalpha(tsh->prsr.args[current][0]))
			{
				builtin_error("` not a valid identifier", \
				tsh->prsr.args[current], "export: '");
				continue ;
			}
			elem_to_lst(tsh->prsr.args[current], &temp);
			elem = get_env_elem(*tsh, ((t_dict *)(temp->content))->key);
			if (elem)
			{
				if (((t_dict *)(temp->content))->is_separ)
				{
					ft_freen((void **)&elem->value);
					elem->value = ((t_dict *)(temp->content))->value;
					elem->is_separ = ((t_dict *)(temp->content))->is_separ;
				}
				else
					ft_freen((void **)&((t_dict *)(temp->content))->value);
			}
			else
			{
				elem_to_lst(tsh->prsr.args[current], &tsh->env);
				ft_freen((void **)&((t_dict *)(temp->content))->value);
			}
			ft_freen((void **)&((t_dict *)(temp->content))->key);
			ft_freen((void **)&(temp->content));
			ft_freen((void **)&temp);
		}
	}
	g_exit_status = 0;
}

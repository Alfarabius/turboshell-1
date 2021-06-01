#include "minishell.h"

static int	check_unset_error(t_tsh *tsh, int i, t_list **c, t_list **p)
{
	if (!ft_isalpha(tsh->prsr.args[i][0]))
	{
		builtin_error("` not a valid identifier", \
		tsh->prsr.args[i], "unset: '");
		g_exit_status = 1;
		return (0);
	}
	*c = tsh->env;
	*p = tsh->env;
	return (1);
}

static void	clear_unset(t_list **current)
{
	free(((t_dict *)(*current)->content)->key);
	free(((t_dict *)(*current)->content)->value);
	free((t_dict *)(*current)->content);
	free((t_dict *)(*current));
}

void	ft_unset(t_tsh *tsh, int i)
{
	t_list	*current;
	t_list	*prev;

	g_exit_status = 0;
	while (tsh->prsr.args[++i])
	{
		if (!check_unset_error(tsh, i, &current, &prev))
			continue ;
		while (current)
		{
			if (!ft_strcmp(((t_dict *)current->content)->key, \
			tsh->prsr.args[i]))
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
			clear_unset(&current);
		}
	}
}

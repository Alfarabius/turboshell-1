#include "minishell.h"

static	void	swap(t_dict *a, t_dict *b)
{
	t_dict	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_dict	*get_env_elem(t_tsh tsh, char *key)
{
	t_dict	*elem;

	elem = NULL;
	while (tsh.env)
	{
		if (!ft_strcmp(key, ((t_dict *)(tsh.env->content))->key))
		{
			elem = ((t_dict *)(tsh.env->content));
			break ;
		}
		tsh.env = tsh.env->next;
	}
	return (elem);
}

t_list	*sort_dict_ascii(t_list **dict)
{
	t_list	*dict_ptr;
	t_list	*curr_dict;
	t_dict	*curr;
	t_dict	*next;

	dict_ptr = *dict;
	while (dict_ptr->next)
	{
		curr_dict = *dict;
		while (curr_dict->next)
		{
			curr = ((t_dict *)(curr_dict->content));
			next = ((t_dict *)(curr_dict->next->content));
			if (ft_strcmp(curr->key, next->key) > 0)
				swap(curr, next);
			curr_dict = curr_dict->next;
		}
		dict_ptr = dict_ptr->next;
	}
	return (*dict);
}

void	clear_arr(char ***arr)
{
	int	i;

	i = -1;
	if (*arr)
	{
		while ((*arr)[++i])
			ft_freen((void **)(&(*arr)[i]));
		free(*arr);
		*arr = NULL;
	}
}

void	exit_status_handler(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			g_exit_status = 130;
		else if (WTERMSIG(status) == 3)
			g_exit_status = 131;
	}
}

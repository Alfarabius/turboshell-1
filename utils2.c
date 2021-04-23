#include "minishell.h"

void	deinit(t_tsh *tsh)
{
	tsh->term.c_lflag |= (ECHO|ICANON);
	tcsetattr(0, TCSANOW, &tsh->term);
}

t_dict *get_env_elem(t_tsh tsh, char *key)
{
	t_dict *elem;

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

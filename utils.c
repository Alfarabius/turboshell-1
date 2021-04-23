#include "minishell.h"

int		ft_putint(int c)
{
	return (write(1, &c, 1));
}

char	*ft_memjoin_tsh(char *s1, char *s2)
{
	char *str;

	str = ft_strjoin(s1, s2);
	error_checker(!str, "memmory doesn't allocated", 1);
	ft_freen((void **)&s1);
	return (str);
}

void	deinit(t_tsh *tsh)
{
	tsh->term.c_lflag |= (ECHO|ICANON);
	tcsetattr(0, TCSANOW, &tsh->term);
}

char	*get_env_value(t_tsh tsh, char *key)
{
	char *value;

	value = NULL;
	while (tsh.env)
	{
		if (!ft_strcmp(key, ((t_dict *)(tsh.env->content))->key))
		{
			value = ((t_dict *)(tsh.env->content))->value;
			break ;
		}
		tsh.env = tsh.env->next;
	}
	return (value);
}

int		envlist_to_arr(t_tsh *tsh)
{
	t_list	*env_ptr;
	int		i;

	i = 0;
	env_ptr = tsh->env;
	if (tsh->env_arr)
		ft_freearr(tsh->env_arr);
	tsh->env_arr = (char **)malloc(sizeof(tsh->env_arr));
	while (env_ptr)
	{
		tsh->env_arr[i] = ft_strdup((char *)env_ptr->content);
		error_checker(!tsh->env_arr[i], "memmory doesn't allocated", 1);
		env_ptr = env_ptr->next;
	}
	return (0);
}

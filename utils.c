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
	ft_freen(s1);
	return (str);
}

void	deinit(t_tsh *tsh)
{
	tsh->term.c_lflag |= (ECHO|ICANON);
	tcsetattr(0, TCSANOW, &tsh->term);
	if (tsh->dir.wpath)
		ft_freen(tsh->dir.wpath);
	closedir(tsh->dir.curr_dir);
}

char *get_env_value(t_tsh tsh, char *key)
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

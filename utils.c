#include "minishell.h"

char	*ft_memjoin_tsh(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	error_checker(!str, "memmory doesn't allocated", 1);
	ft_freen((void **)&s1);
	return (str);
}

char	*get_env_value(t_tsh tsh, char *key)
{
	char	*value;

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

char	*dict_to_str(t_dict *elem)
{
	char	*str;
	size_t	len;

	len = ft_strlen(elem->key) + ft_strlen(elem->value) + 2;
	str = (char *)malloc(len);
	error_checker(!str, "memmory doesn't allocated", 1);
	str[0] = '\0';
	ft_strlcat(str, elem->key, len);
	if (elem->is_separ)
	{
		ft_strlcat(str, "=", len);
		ft_strlcat(str, elem->value, len);
	}
	return (str);
}

int	envlist_to_arr(t_tsh *tsh)
{
	t_list	*env_ptr;
	t_dict	*curr_dict;
	int		i;

	i = 0;
	env_ptr = tsh->env;
	if (tsh->env_arr)
		tsh->env_arr = ft_freearr(tsh->env_arr);
	tsh->env_arr = (char **)malloc(sizeof(char *) * (ft_lstsize(tsh->env) + 1));
	while (env_ptr)
	{
		curr_dict = ((t_dict *)(env_ptr->content));
		tsh->env_arr[i++] = dict_to_str(curr_dict);
		env_ptr = env_ptr->next;
	}
	tsh->env_arr[i] = NULL;
	return (0);
}

void	clear_redirects(t_tsh *tsh)
{
	int	i;

	i = -1;
	while (tsh->prsr.redirects[++i])
	{
		if (tsh->prsr.redirects[i]->file_path)
			free(tsh->prsr.redirects[i]->file_path);
		if (tsh->prsr.redirects[i]->fd > 0)
			close(tsh->prsr.redirects[i]->fd);
		free(tsh->prsr.redirects[i]);
	}
	free(tsh->prsr.redirects[i]);
	free(tsh->prsr.redirects);
}

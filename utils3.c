#include "minishell.h"

t_list	*dictlstdup(t_list *lst)
{
	t_list	*lst_copy;
	t_dict	*dict;
	t_dict	*dict_copy;

	lst_copy = NULL;
	while (lst)
	{
		dict = ((t_dict *)(lst->content));
		dict_copy = (t_dict *)malloc(sizeof(t_dict));
		dict_copy->is_separ = dict->is_separ;
		dict_copy->is_set = dict->is_set;
		dict_copy->key = ft_strdup(dict->key);
		dict_copy->value = ft_strdup(dict->value);
		error_checker((!dict_copy->key || !dict_copy->value), "NULL", 1);
		ft_lstadd_back(&lst_copy, ft_lstnew(dict_copy));
		lst = lst->next;
	}
	return (lst_copy);
}

void	dictdelone(void *dict)
{
	if (((t_dict *)(dict))->key)
		free(((t_dict *)(dict))->key);
	if (((t_dict *)(dict))->value)
		free(((t_dict *)(dict))->value);
	free(dict);
}

char	*get_dir_for_history(t_tsh *tsh, char *path)
{
	char	*dir;
	char	*tmp;
	char	*value;

	value = get_env_value(*tsh, "HOME");
	if (value)
	{
		tmp = ft_strdup(value);
		error_checker(!tmp, "memmory doesn't allocated", 1);
		dir = ft_strjoin(tmp, "/tsh_history");
		free(tmp);
	}
	else
	{
		tmp = ft_strtrim(path, "minishell");
		error_checker(!tmp, "memmory doesn't allocated", 1);
		dir = ft_strjoin(tmp, "/tsh_history");
		free(tmp);
	}
	error_checker(!dir, "memmory doesn't allocated", 1);
	return (dir);
}

void	save_history_exit(int status, t_tsh *tsh)
{
	add_to_history(tsh);
	history_to_file(tsh);
	exit(status);
}

int	is_file_accessible(const char *file, int flag)
{
	struct stat	state;
	mode_t		mode;
	int			err;

	err = lstat(file, &state);
	error_checker(err == -1, strerror(errno), 0);
	mode = state.st_mode;
	if (flag == 1 && mode & S_IXUSR)
		return (1);
	if (flag == 0 && mode & S_IWUSR)
		return (1);
	if (flag == 2 && mode & S_IWUSR & S_IXUSR)
		return (1);
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

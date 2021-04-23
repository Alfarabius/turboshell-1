#include "minishell.h"

void	ft_cd(t_tsh *tsh)
{
	t_list	*current;
	t_dict	*pwd;
	t_dict	*old_pwd;
	t_dict	*dir;

	current = tsh->env;
	old_pwd = NULL;
	dir = tsh->prsr.args[1];
	if (!dir)
		while (current)
		{
			if (!ft_strcmp("HOME", ((t_dict *)(current->content))->key))
				dir = ((t_dict *)(current->content))->value;
			current = current->next;
		}
	current = tsh->env;
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("turboshell: cd:", 1);
		ft_putstr_fd(dir, 1);
		ft_putendl_fd(": No such file or directory", 1);
		return ;
	}
	while (current)
	{
		if (!ft_strcmp("PWD", ((t_dict *)(current->content))->key))
			pwd = (t_dict *)(current->content);
		if (!ft_strcmp("OLDPWD", ((t_dict *)(current->content))->key))
			old_pwd = (t_dict *)(current->content);
		current = current->next;
	}
	if (!old_pwd->value)
	{
		old_pwd->value = ft_strjoin("OLDPWD=", pwd->value);
		error_checker(!old_pwd->value, "memmory doesn't allocated", 1);
		elem_to_lst(old_pwd->value, &tsh->env);
	}
	else
	{
		ft_freen ((void **)&old_pwd->value);
		old_pwd->value = ft_strdup(pwd->value);
		error_checker(!old_pwd->value, "memmory doesn't allocated", 1);
	}
	if (pwd->value)
		ft_freen ((void **)&pwd->value);
	pwd->value = ft_strdup(dir);
	error_checker(!pwd, "memmory doesn't allocated", 1);
}

static void			write_export(t_tsh *tsh)
{
	t_list *temp;

	temp = tsh->env;
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

void				ft_export(t_tsh *tsh)
{
	int current;
	t_dict *elem;
	t_list *temp;

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

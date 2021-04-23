#include "minishell.h"

void	ft_cd(t_tsh *tsh)
{
	t_list	*current;
	t_dict	*pwd;
	t_dict	*old_pwd;
	char	*dir;

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
	tsh->dir.wpath = getcwd(NULL, 0);
	error_checker(!tsh->dir.wpath, "getcwd return error", 1);
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
		ft_freen (old_pwd->value);
		old_pwd->value = ft_strdup(pwd->value);
		error_checker(!old_pwd->value, "memmory doesn't allocated", 1);
	}
	if (pwd->value)
		ft_freen (pwd->value);
	pwd->value = ft_strdup(dir);
	error_checker(!pwd, "memmory doesn't allocated", 1);
}

void	ft_export(t_tsh *tsh)
{
	int current;
	char *key;
	char *value;
	t_list *temp;

	temp = tsh->env;
	if (!tsh->prsr.args[1])
	{
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
	else
	{
		current = 1;
		while (tsh->prsr.args[current])
		{
			if (is_separ_exist(tsh->prsr.args[current]))
			{
				key = ft_substr(tsh->prsr.args[current], 0, keylen(tsh->prsr.args[current]));
				value = ft_substr(tsh->prsr.args[current], keylen(tsh->prsr.args[current]) + 1, ft_strlen(tsh->prsr.args[current]));
			}
			else
			{
				key = ft_substr(tsh->prsr.args[current], 0, keylen(tsh->prsr.args[current]));
				value = NULL;
			}
			if (get_env_value(*tsh, key))
				;
			else
				elem_to_lst(tsh->prsr.args[current], &tsh->env);
			ft_freen(key);
			ft_freen(value);
			current++;
		}
	}
}

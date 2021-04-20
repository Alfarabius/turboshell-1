#include "minishell.h"

void	ft_cd(t_tsh *tsh)
{
	t_list	*current;
	t_dict	*pwd;
	t_dict	*old_pwd;
	char	*dir;

	current = tsh->env;
	old_pwd = NULL;
	dir = tsh->prsr->args[1];
	if (!dir)
		while (current)
		{
			if (!ft_strcmp("HOME", ((t_dict *)(current->content))->key))
				dir = ((t_dict *)(current->content))->value;
			current = current->next;
		}
	current = tsh->env;
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

}

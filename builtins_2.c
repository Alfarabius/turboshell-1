#include "minishell.h"

void	ft_cd(t_tsh *tsh)
{
	t_list	*current;
	char	*dir;
	char	*pwd;
	char	*old_pwd;

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
			pwd = ((t_dict *)(current->content))->value;
		if (!ft_strcmp("OLDPWD", ((t_dict *)(current->content))->key))
			old_pwd = ((t_dict *)(current->content))->value;
	}
	if (!old_pwd)
	{
		old_pwd = ft_strjoin("OLDPWD=", pwd);
		error_checker(!old_pwd, "memmory doesn't allocated", 1);
		elem_to_lst(old_pwd, &tsh->env);
	}
	else
	{
		free(old_pwd);
		old_pwd = ft_strdup(pwd);
		error_checker(!old_pwd, "memmory doesn't allocated", 1);
	}
	free (pwd);
	pwd = ft_strdup(dir);
	error_checker(!pwd, "memmory doesn't allocated", 1);
}

void	ft_export(t_tsh *tsh)
{

}

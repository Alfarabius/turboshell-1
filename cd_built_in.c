#include "minishell.h"

void	builtin_error(char *msg, char *name, char *btin)
{
	ft_putstr_fd("turboshell: ", 1);
	ft_putstr_fd(btin, 1);
	ft_putstr_fd(name, 1);
	ft_putendl_fd(msg, 1);
}

void	change_oldpwd(int cond, t_tsh *tsh, t_dict **old_pwd, t_dict *pwd)
{
	if (cond)
	{
		(*old_pwd)->value = ft_strjoin("OLDPWD=", pwd->value);
		error_checker(!(*old_pwd)->value, "memmory doesn't allocated", 1);
		elem_to_lst((*old_pwd)->value, &tsh->env);
	}
	else
	{
		ft_freen((void **)&((*old_pwd)->value));
		(*old_pwd)->value = ft_strdup(pwd->value);
		error_checker(!(*old_pwd)->value, "memmory doesn't allocated", 1);
	}
}

void	ft_cd(t_tsh *tsh, char *dir)
{
	t_list	*current;
	t_dict	*pwd;
	t_dict	*old_pwd;

	current = tsh->env;
	old_pwd = NULL;
	if (!dir)
	{
		dir = get_env_value(*tsh, "HOME");
		if (!dir)
			return (builtin_error("HOME not set", "", "cd: "));
	}
	current = tsh->env;
	if (chdir(dir) == -1)
		return (builtin_error(": No such file or directory", dir, "cd: "));
	pwd = get_env_elem(*tsh, "PWD");
	old_pwd = get_env_elem(*tsh, "OLDPWD");
	if (!pwd || !old_pwd || !dir)
		return ;
	change_oldpwd(!old_pwd->value, tsh, &old_pwd, pwd);
	if (pwd->value)
		ft_freen ((void **)&pwd->value);
	pwd->value = ft_strdup(dir);
	error_checker(!pwd, "memmory doesn't allocated", 1);
}

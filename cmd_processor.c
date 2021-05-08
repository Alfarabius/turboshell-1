#include "minishell.h"

static char *get_bpath(int current_path, t_tsh *tsh)
{
	char	*bpath;
	char	*paths;
	int		i;
	int		current;

	bpath = (char *)malloc(1);
	error_checker(!bpath, "memmory doesn't allocated", 1);
	bpath[0] = '\0';
	paths = get_env_value(*tsh, "PATH");
	current = 0;
	i = 0;
	while (current < current_path)
	{
		if (paths[i] == ':')
			current++;
		i++;
	}
	while (paths[i] && paths[i] != ':')
	{
		bpath = ft_realloc(bpath, 1, paths[i]);
		i++;
	}
	return (bpath);
}

int	path_len(t_tsh *tsh)
{
	char	*path;
	int		i;
	int		len;

	path = get_env_value(*tsh, "PATH");
	i = -1;
	len = 1;
	while (path[++i])
		if (path[i] == ':')
			len++;
	return (len);
}

static	int	binary_in_dir(char *path, char* bin)
{
	DIR				*dir;
	struct	dirent	*entry;

	dir = opendir(path);
	entry = readdir(dir);
	while(entry)
	{
		if (!ft_strcmp(bin, entry->d_name))
		{
			closedir(dir);
			return(1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return(0);
}

int	binary_processor(t_tsh *tsh)
{
	char	*binary_path;
	int		current_path;
	int		len;
	int		i;
	pid_t	pid;
	void	*buf;

	current_path = 0;
	len = path_len(tsh);
	envlist_to_arr(tsh);
	while (current_path < len)
	{
		binary_path = get_bpath(current_path++, tsh);
		if (binary_in_dir(binary_path, tsh->prsr.args[0]))
		{
			binary_path = ft_realloc(binary_path, 1, '/');
			i = -1;
			while (tsh->prsr.args[0] && tsh->prsr.args[0][++i])
			binary_path = ft_realloc(binary_path, 1, tsh->prsr.args[0][i]);
			pid = fork();
			if (!pid)
			{
				execve(binary_path, tsh->prsr.args, tsh->env_arr);
				exit(1);
			}
			else
				waitpid(pid, &g_exit_status, 0);
		}
		ft_freen((void **)&binary_path);
	}
	return(0);
}

int	cmd_processor(t_tsh *tsh)
{
	if (tsh->prsr.args[0] && !ft_strcmp("exit", tsh->prsr.args[0]))
		ft_exit(tsh);
	else if(tsh->prsr.args[0] && !ft_strcmp("echo", tsh->prsr.args[0]))
		ft_echo(tsh);
	else if(tsh->prsr.args[0] && !ft_strcmp("cd", tsh->prsr.args[0]))
		ft_cd(tsh);
	else if(tsh->prsr.args[0] && !ft_strcmp("pwd", tsh->prsr.args[0]))
		ft_pwd(tsh);
	else if(tsh->prsr.args[0] && !ft_strcmp("export", tsh->prsr.args[0]))
		ft_export(tsh);
	else if(tsh->prsr.args[0] && !ft_strcmp("unset", tsh->prsr.args[0]))
		ft_unset(tsh);
	else if(tsh->prsr.args[0] && !ft_strcmp("env", tsh->prsr.args[0]))
		ft_env(tsh);
	else binary_processor(tsh);
	return (0);
}

#include "minishell.h"

static	char	*get_bpath(int current_path, t_tsh *tsh)
{
	char	*bpath;
	char	*paths;
	int		i;
	int		current;

	arg_to_lower(tsh);
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
	if (!path)
		return (0);
	i = -1;
	len = 1;
	while (path[++i])
		if (path[i] == ':')
			len++;
	return (len);
}

int	binary_in_dir(char *path, char *bin)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (dir == NULL)
		return (0);
	entry = readdir(dir);
	while (entry)
	{
		if (!ft_strcmp(bin, entry->d_name))
		{
			closedir(dir);
			return (1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

static	void	open_binary(t_tsh *tsh, char **binary_path, int status)
{
	int		i;
	pid_t	pid;

	i = -1;
	*binary_path = ft_realloc(*binary_path, 1, '/');
	while (tsh->prsr.args[0] && tsh->prsr.args[0][++i])
		*binary_path = ft_realloc(*binary_path, 1, tsh->prsr.args[0][i]);
	if (!tsh->prsr.pipe.count)
	{
		pid = fork();
		if (pid < 0)
			return (error_template_prsr("turboshell-1.0: ", \
			"", strerror(errno), tsh));
		if (!pid)
		{
			execve(*binary_path, tsh->prsr.args, tsh->env_arr);
			exit(0);
		}
		else
			waitpid(pid, &status, 0);
	}
	else
		execve(*binary_path, tsh->prsr.args, tsh->env_arr);
	exit_status_handler(status);
}

void	binary_processor(t_tsh *tsh, int status)
{
	char	*binary_path;
	int		current_path;
	int		len;

	current_path = 0;
	len = path_len(tsh);
	envlist_to_arr(tsh);
	while (current_path < len)
	{
		binary_path = get_bpath(current_path++, tsh);
		status = binary_in_dir(binary_path, tsh->prsr.args[0]);
		if (status)
		{
			open_binary(tsh, &binary_path, 0);
			break ;
		}
		ft_freen((void **)&binary_path);
	}
	if (!status)
	{
		g_exit_status = 127;
		error_template("turboshell-1.0", \
		tsh->prsr.args[0], "command not found");
	}
	ft_freen((void **)&binary_path);
}

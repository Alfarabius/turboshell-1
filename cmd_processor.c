#include "minishell.h"

static int	curr_dir_check(t_tsh *tsh, char **path_to_exec)
{
	if (tsh->prsr.args[0][0] == '.' && ft_strlen(tsh->prsr.args[0]) == 1)
	{
		write(2, "turboshell-1.0: .: filename argument required\n", 46);
		write(2, ".: usage: . filename [arguments]\n", 33);
		return (0);
	}
	*path_to_exec = getcwd(NULL, 0);
	error_checker(!*path_to_exec, "getcwd return error", 1);
	*path_to_exec = ft_strjoin_gnl(*path_to_exec, "/");
	*path_to_exec = ft_strjoin_gnl(*path_to_exec, tsh->prsr.args[0]);
	error_checker(!path_to_exec, "Memmory doesn't allocated", 1);
	return (1);
}

static int	check_bin(char *path_bin)
{
	char	*path;
	char	*bin;
	int		i;

	i = ft_strlen(path_bin);
	bin = NULL;
	path = NULL;
	while (--i >= 0 && path_bin[i] != '/')
		;
	i++;
	bin = ft_strdup(&path_bin[i]);
	path_bin[i] = '\0';
	path = ft_strdup(path_bin);
	path_bin[i] = bin[0];
	error_checker(!path || !bin, "Memmory doesn't allocated", 1);
	i = binary_in_dir(path, bin);
	free(bin);
	free(path);
	return (i);
}

static void	start_exec(t_tsh *tsh, char *path)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!tsh->prsr.pipe.count)
	{
		pid = fork();
		if (pid < 0)
			return (error_template_prsr("turboshell-1.0: ", \
			"", strerror(errno), tsh));
		if (!pid)
		{
			if (is_file_accessible(path, 1))
				execve(path, tsh->prsr.args, tsh->env_arr);
			exit(0);
		}
		else
			waitpid(pid, &status, 0);
	}
	else if (is_file_accessible(path, 1))
		execve(path, tsh->prsr.args, tsh->env_arr);
	exit_status_handler(status);
}

static void	start_by_path(t_tsh *tsh, char *path_to_exec)
{
	DIR	*dir;

	if (path_to_exec)
		path_to_exec = ft_strjoin("./", path_to_exec);
	else if (tsh->prsr.args[0][0] == '.' && !curr_dir_check(tsh, &path_to_exec))
		return ;
	else if (!path_to_exec)
		path_to_exec = ft_strdup(tsh->prsr.args[0]);
	error_checker(!path_to_exec, "Memmory doesn't allocated", 1);
	dir = opendir(path_to_exec);
	if (dir)
	{
		g_exit_status = 126;
		error_template("turboshell-1.0", tsh->prsr.args[0], "is a directory");
		closedir(dir);
		return (free(path_to_exec));
	}
	if (!check_bin(path_to_exec))
	{
		error_template("turboshell-1.0", tsh->prsr.args[0], \
		"No such file or directory");
		return (free(path_to_exec));
	}
	start_exec(tsh, path_to_exec);
	free(path_to_exec);
}

void	cmd_processor(t_tsh *tsh)
{
	open_redirects(tsh);
	if (tsh->prsr.parse_status < 0)
		return ;
	if (tsh->prsr.args[0] && (ft_strchr(tsh->prsr.args[0], '/') || (tsh->prsr.args[0][0] \
	== '.' && (tsh->prsr.args[0][1] == '.' || !tsh->prsr.args[0][1]))))
		start_by_path(tsh, NULL);
	else if (tsh->prsr.args[0] && !ft_strcmp("exit", tsh->prsr.args[0]))
		ft_exit(tsh, -1);
	else if (tsh->prsr.args[0] && !ft_strcmp("echo", tsh->prsr.args[0]))
		ft_echo(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("cd", tsh->prsr.args[0]))
		ft_cd(tsh, tsh->prsr.args[1]);
	else if (tsh->prsr.args[0] && !ft_strcmp("pwd", tsh->prsr.args[0]))
		ft_pwd();
	else if (tsh->prsr.args[0] && !ft_strcmp("export", tsh->prsr.args[0]))
		ft_export(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("unset", tsh->prsr.args[0]))
		ft_unset(tsh, 0);
	else if (tsh->prsr.args[0] && !ft_strcmp("env", tsh->prsr.args[0]))
		ft_env(tsh);
	else if (tsh->prsr.args[0] && get_env_value(*tsh, "PATH"))
		binary_processor(tsh, 0);
	else if (tsh->prsr.args[0] && !get_env_value(*tsh, "PATH"))
		start_by_path(tsh, tsh->prsr.args[0]);
	close_redirects(tsh);
}

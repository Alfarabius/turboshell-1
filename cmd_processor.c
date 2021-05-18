#include "minishell.h"

static void arg_to_lower(t_tsh *tsh)
{
	int		len;
	char	*res;

	if (tsh->prsr.args[0])
	{
		len = ft_strlen(tsh->prsr.args[0]);
		res = (char *)malloc(sizeof(char) * (len + 1));
		res[len] = '\0';
		while (--len >= 0)
			res[len] = ft_tolower(tsh->prsr.args[0][len]);
		free(tsh->prsr.args[0]);
		tsh->prsr.args[0] = res;
	}
}

//сделать проверку на наличие файла
static void start_by_path(t_tsh *tsh)
{
	pid_t	pid;
	char	*path_to_exec;

	path_to_exec = NULL;
	if (tsh->prsr.args[0][0] == '.')
	{
		path_to_exec = getcwd(NULL, 0);
		error_checker(!path_to_exec, "getcwd return error", 1);
		path_to_exec = ft_strjoin_gnl(path_to_exec, "/");
		path_to_exec = ft_strjoin_gnl(path_to_exec, tsh->prsr.args[0]);
	}
	else
		path_to_exec = ft_strdup(tsh->prsr.args[0]);
	if (!tsh->prsr.pipe.count)
	{
		pid = fork();
		if (!pid)
		{
			execve(path_to_exec, tsh->prsr.args, tsh->env_arr);
			exit(0);
		}
		else
			waitpid(pid, &g_exit_status, 0);
	}
	else
		execve(path_to_exec, tsh->prsr.args, tsh->env_arr);
	exit_status_handler(pid);
	if (path_to_exec)
		free(path_to_exec);
}

int	cmd_processor(t_tsh *tsh)
{
	open_redirects(tsh);
	arg_to_lower(tsh);
	if (tsh->prsr.parse_status < 0)
		return (1);
	if (tsh->prsr.args[0] && (tsh->prsr.args[0][0] == '/' || (tsh->prsr.args[0][0]\
	== '.' && (tsh->prsr.args[0][1] == '/' || tsh->prsr.args[0][1] == '.'))))
		start_by_path(tsh);
	if (tsh->prsr.args[0] && !ft_strcmp("exit", tsh->prsr.args[0]))
		ft_exit(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("echo", tsh->prsr.args[0]))
		ft_echo(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("cd", tsh->prsr.args[0]))
		ft_cd(tsh, tsh->prsr.args[1]);
	else if (tsh->prsr.args[0] && !ft_strcmp("pwd", tsh->prsr.args[0]))
		ft_pwd(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("export", tsh->prsr.args[0]))
		ft_export(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("unset", tsh->prsr.args[0]))
		ft_unset(tsh);
	else if (tsh->prsr.args[0] && !ft_strcmp("env", tsh->prsr.args[0]))
		ft_env(tsh);
	else if (tsh->prsr.args[0])
		binary_processor(tsh);
	close_redirects(tsh);
	return (0);
}

#include "minishell.h"

static void	close_pipes_fd(t_tsh *tsh)
{
	close(tsh->prsr.pipe.fd[tsh->prsr.pipe.current][1]);
	close(tsh->prsr.pipe.fd[tsh->prsr.pipe.current][0]);
}

static void	wait_error_pipes(t_tsh *tsh)
{
	int	status;

	dup2(tsh->original_fd[1], 1);
	dup2(tsh->original_fd[0], 0);
	close_pipes_fd(tsh);
	(error_template_prsr("turboshell-1.0: ", "", strerror(errno), tsh));
	tsh->prsr.pipe.current = 0;
	while (tsh->prsr.pipe.count)
	{
		wait(&status);
		exit_status_handler(status);
		tsh->prsr.pipe.count--;
	}
}

static void	child_handler(t_tsh *tsh, int status)
{
	cmd_processor(tsh);
	exit(status);
}

void	pipe_processor(t_tsh *tsh)
{
	pid_t	pid;

	pipe(tsh->prsr.pipe.fd[tsh->prsr.pipe.current]);
	pid = fork();
	if (pid < 0)
		return (wait_error_pipes(tsh));
	if (!pid)
	{
		dup2(tsh->prsr.pipe.fd[tsh->prsr.pipe.current][1], 1);
		close_pipes_fd(tsh);
		child_handler(tsh, 0);
	}
	else
	{
		dup2(tsh->prsr.pipe.fd[tsh->prsr.pipe.current][0], 0);
		close_pipes_fd(tsh);
	}
	tsh->prsr.pipe.current++;
}

void	wait_pipes(t_tsh *tsh)
{
	pid_t	pid;
	int		status;

	pipe(tsh->prsr.pipe.fd[tsh->prsr.pipe.current]);
	pid = fork();
	if (pid < 0)
		return (wait_error_pipes(tsh));
	tsh->prsr.pipe.count++;
	dup2(tsh->original_fd[1], 1);
	if (!pid)
		child_handler(tsh, g_exit_status);
	else
	{
		dup2(tsh->original_fd[0], 0);
		close_pipes_fd(tsh);
		tsh->prsr.pipe.current = 0;
		while (tsh->prsr.pipe.count)
		{
			wait(&status);
			exit_status_handler(status);
			tsh->prsr.pipe.count--;
		}
	}
}

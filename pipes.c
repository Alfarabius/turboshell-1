#include "minishell.h"

void pipe_processor(t_tsh *tsh)
{
	pid_t pid;

	pipe(tsh->prsr.pipe.fd[tsh->prsr.pipe.current]);
	pid = fork();
	if (!pid)
	{
		dup2(tsh->prsr.pipe.fd[tsh->prsr.pipe.current][1], 1);
		close(tsh->prsr.pipe.fd[tsh->prsr.pipe.current][0]);
		close(tsh->prsr.pipe.fd[tsh->prsr.pipe.current][1]);
		cmd_processor(tsh);
		exit(1);
	}
	else
	{
		dup2(tsh->prsr.pipe.fd[tsh->prsr.pipe.current][0], 0);
		close(tsh->prsr.pipe.fd[tsh->prsr.pipe.current][1]);
		close(tsh->prsr.pipe.fd[tsh->prsr.pipe.current][0]);
	}
	tsh->prsr.pipe.current++;
}

void wait_pipes(t_tsh *tsh)
{
	int status;
	pid_t pid;

	pipe(tsh->prsr.pipe.fd[tsh->prsr.pipe.current]);
	pid = fork();
	tsh->prsr.pipe.count++;
	dup2(tsh->original_fd[1], 1);
	if (!pid)
	{
		cmd_processor(tsh);
		exit(1);
	}
	else
	{
		dup2(tsh->original_fd[0], 0);
		while (tsh->prsr.pipe.count)
		{
			wait(&status);
			tsh->prsr.pipe.count--;
		}
	}
}

#include "minishell.h"
void go_work(t_tsh *tsh)
{
	int  fd2[2];
	int	status;
	pid_t pid;

	pipe(fd2);
	pid = fork();
	if (!pid)
	{
		dup2(fd2[1], 1);
		close(fd2[0]);
		close(fd2[1]);
		cmd_processor(tsh);
	}
	else
	{
		dup2(fd2[0], 0);
		close(fd2[0]);
		close(fd2[1]);
		waitpid(pid, &status, 0);
	}
}

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
	//pipe_processor(tsh);
}

//встречаем | отправляем сюда
//считаем кол-во пайпов
//ласт функцию отправляем в обычную функцию
//после выполнения ласт функции декрементим кол-во | в цикле и запускаем waitpid

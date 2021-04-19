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
		waitpid(pid, &status, NULL);
	}
}
//встречаем | отправляем сюда
//считаем кол-во пайпов
//ласт функцию отправляем в обычную функцию
//после выполнения ласт функции декрементим кол-во | в цикле и запускаем waitpid

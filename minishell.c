#include "minishell.h"

static	int	init_shell(t_tsh *tsh)
{
	tsh->is_running = 1;
	tsh->symbols = 0;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_tsh	tsh;

	init_shell(&tsh);
	env_to_lst(&tsh.env, env);
	while(tsh.env)
	{
		printf("%s=",((t_dict *)(tsh.env->content))->key);
		printf("%s\n",((t_dict *)(tsh.env->content))->value);
		tsh.env = tsh.env->next;
	}
	(void)argc;
	(void)argv;
	(void)env;
	while (tsh.is_running)
	{
		write(1, YELLOW, 6);
		write(1, "turboshell-1.0$ ", 17);
		write(1, STANDART, 5);
		tsh.symbols = read(0, tsh.buf, 1024);
		if (!tsh.symbols)
			write(1, "\n", 2);
		if (tsh.buf[0] != '\n')
			printf("out: %s", tsh.buf);
		line_parser(tsh.buf);
		ft_bzero(tsh.buf, 1024);
	}
	return (0);
}

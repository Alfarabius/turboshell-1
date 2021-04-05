#include "minishell.h"

static	int	init_shell(t_tsh *tsh)
{
	tcgetattr(0, &tsh->term);
	tsh->term.c_lflag &= ~ECHO;
	tsh->term.c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, &tsh->term);
	tgetent(0, TERM_NAME);
	// tsh->term.c_cc[VMIN] = 2;
	// tsh->term.c_cc[VTIME] = 0;
	tsh->hfd = open("tsh_history", O_CREAT | O_RDWR, 0755);
	tsh->is_running = 1;
	tsh->symbols = 0;
	tsh->line = malloc(1);
	tsh->line[0] = '\0';
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_tsh	tsh;
	char	end_line;
	char	*tmp;

	end_line = 0;
	(void)argc;
	(void)argv;
	init_shell(&tsh);
	env_to_lst(&tsh.env, env);
	// while(tsh.env) // debug
	// {
	// 	printf("%s=",((t_dict *)(tsh.env->content))->key);
	// 	printf("%s\n",((t_dict *)(tsh.env->content))->value);
	// 	tsh.env = tsh.env->next;
	// }
	while (tsh.is_running)
	{
		write(1, TSH_NAME, 27);
		tputs(save_cursor, 1, ft_putchar);
		while (!end_line)
		{
			tsh.symbols = read(0, tsh.buf, 1024);
			write(1, tsh.buf, tsh.symbols);
			termcap_processor(tsh.buf, &tsh);
			if (tsh.buf[tsh.symbols - 1] == '\n')
				end_line = 1;
			if (!ft_strcmp(tsh.buf, "\4"))
			{
				end_line = 1;
				tsh.is_running = 0;
			}
			tmp = ft_strjoin(tsh.line, tsh.buf);
			free(tsh.line);
			tsh.line = tmp;
		}
		line_parser(tsh);
		ft_bzero(tsh.buf, 1024);
		ft_bzero(tsh.line, ft_strlen(tsh.line));
		end_line = 0;
	}
	return (0);
}

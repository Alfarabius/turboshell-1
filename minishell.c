#include "minishell.h"

static	int	ctrl_d(t_tsh *tsh)
{
	free(tsh->line);
	tsh->end_line = 1;
	tsh->line = ft_strdup("exit");
	if (!tsh->line)
		return(error_handler("memmory doesn't allocated", 0));
	return(0);
}

static	int	ctrl_c(t_tsh *tsh)
{
	ft_bzero(tsh->line, ft_strlen(tsh->line));
	ft_bzero(tsh->buf, 1024);
	g_exit_status = 1;
	write(1, "\n", 1);
	return(new_prompt(tsh));
}

int		new_prompt(t_tsh *tsh)
{
	tsh->his_ptr = ft_dlstlast(tsh->his);
	write(1, TSH_NAME, 27);
	tputs(save_cursor, 1, ft_putchar);
	return (0);
}

static	int	init_shell(t_tsh *tsh)
{
	char	*term_type;

	term_type = getenv("TERM");
	tcgetattr(0, &tsh->term);
	// tsh->term.c_lflag &= ~(ECHO|ICANON|ISIG);
	tsh->term.c_cc[VMIN] = 1;
	tsh->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &tsh->term);
	tgetent(0, TERM_NAME); // for DEBUG!!!
	//if (!term_type || tgetent(0, term_type) != 1) // term_type -> TERM  term_type -> !term_type
	//	return (error_handler("Can not find terminal or termcap base."));
	tsh->hfd = open("tsh_history", O_CREAT | O_RDWR | O_APPEND, 0755);
	if (tsh->hfd == -1)
		return(error_handler("history file doesn't open", 1));
	tsh->env = NULL;
	tsh->his = NULL;
	tsh->env_arr = NULL;
	file_to_history(tsh);
	ft_dlstadd_back(&tsh->his, ft_dlst_new(ft_strdup("\0")));
	tsh->is_running = 1;
	tsh->symbols = 0;
	tsh->end_line = 0;
	tsh->prsr.pipe.count = 0;
	tsh->prsr.pipe.current = 0;
	pipe(tsh->original_fd);
	dup2(1, tsh->original_fd[1]);
	dup2(0, tsh->original_fd[0]);
	tsh->line = (char *)malloc(1);
	if (!tsh->line)
		return(error_handler("memmory doesn't allocated", 1));
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_tsh	tsh;
	char	*tmp;

	(void)argc;
	(void)argv;
	init_shell(&tsh);
	env_to_lst(&tsh.env, env);
	while (tsh.is_running)
	{
		new_prompt(&tsh);
		while (!tsh.end_line)
		{
			tsh.term.c_lflag &= ~(ECHO|ICANON|ISIG);
			tcsetattr(0, TCSANOW, &tsh.term);
			tsh.is_termcap = 0;
			tsh.symbols = read(0, tsh.buf, 1024);
			tsh.buf[tsh.symbols] = '\0';
			write(1, tsh.buf, tsh.symbols);
			if (tsh.buf[tsh.symbols - 1] == '\n')
				tsh.end_line = 1;
			if (tsh.buf[tsh.symbols - 1] == '\3')
				ctrl_c(&tsh);
			termcap_processor(tsh.buf, &tsh);
			tsh.term.c_lflag |= (ECHO|ICANON|ISIG);
			tcsetattr(0, TCSANOW, &tsh.term);
			if(!tsh.is_termcap)
			{
				tsh.line = ft_memjoin_tsh(tsh.line, tsh.buf);
				if (tsh.his_ptr && tsh.his_ptr->content)
					history_editor(&tsh);
			}
			ft_bzero(tsh.buf, 1024);
			if (!ft_strcmp(tsh.line, "\4"))
				ctrl_d(&tsh);
		}
		if (ft_strcmp(tsh.line, "\n"))
		{
			swich_signals(&tsh);
			signal_handler(&tsh);
			line_parser(&tsh);
			swich_signals(&tsh);
			add_to_history(&tsh);
		}
		ft_bzero(tsh.line, ft_strlen(tsh.line));
		tsh.end_line = 0;

	}
	return (0);
}

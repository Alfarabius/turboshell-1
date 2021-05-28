#include "minishell.h"

static	void	init_term_attr(t_tsh *tsh)
{
	char	*term_type;

	term_type = getenv("TERM");
	if (tcgetattr(0, &tsh->term) == -1)
		error_handler("error in tcgetattr", 0);
	switch_term_attr(tsh);
	tsh->term.c_cc[VMIN] = 1;
	tsh->term.c_cc[VTIME] = 0;
	//tgetent(0, TERM_NAME);
	if (!term_type || tgetent(0, term_type) != 1)
		error_handler("Can not find terminal or termcap base.", 1);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

static	void	init_history(t_tsh *tsh, char *path)
{
	tsh->wdir = get_dir_for_history(tsh, path);
	tsh->hfd = open(tsh->wdir, O_CREAT | O_RDWR | O_APPEND, 0755);
	if (tsh->hfd == -1)
		error_handler("history file doesn't open", 1);
	tsh->his = NULL;
	tsh->env_arr = NULL;
	file_to_history(tsh);
	ft_dlstadd_back(&tsh->his, ft_dlst_new(ft_strdup("\0")));
	if (!tsh->his || !tsh->his->content)
		error_handler("memmory doesn't allocated", 1);
	tsh->curr_his = ft_dlstlast(tsh->his);
}

static	void	init_line(t_tsh *tsh)
{
	tsh->is_running = 1;
	tsh->symbols = 0;
	tsh->end_line = 0;
	tsh->line = (char *)malloc(1);
	if (!tsh->line)
		error_handler("memmory doesn't allocated", 1);
}

static	void	init_pipes(t_tsh *tsh)
{
	tsh->prsr.pipe.count = 0;
	tsh->prsr.pipe.current = 0;
	tsh->output_fd = 0;
	tsh->input_fd = 0;
	tsh->redirect_fd = 0;
	tsh->is_termcap = 1;
	pipe(tsh->original_fd);
	dup2(1, tsh->original_fd[1]);
	dup2(0, tsh->original_fd[0]);
}

void	init_shell(t_tsh *tsh, char *path)
{
	init_term_attr(tsh);
	init_history(tsh, path);
	init_line(tsh);
	init_pipes(tsh);
}

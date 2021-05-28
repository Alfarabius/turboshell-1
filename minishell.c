#include "minishell.h"

static	void	ctrl_char_handler(t_tsh *tsh)
{
	if (tsh->buf[tsh->symbols - 1] == '\t')
		tsh->buf[tsh->symbols - 1] = 0;
	else if (tsh->buf[tsh->symbols - 1] == 126)
		ft_bzero(tsh->buf, 1024);
	else if (tsh->buf[tsh->symbols - 1] < 0)
		ft_bzero(tsh->buf, 1024);
	else if (tsh->buf[tsh->symbols - 1] > 127)
		tsh->buf[tsh->symbols - 1] = 0;
	else if (tsh->buf[tsh->symbols - 1] == '\n')
		tsh->end_line = 1;
	else if (tsh->buf[tsh->symbols - 1] == '\3')
		ctrl_c(tsh);
	else if (tsh->buf[tsh->symbols - 1] == '\4')
		return ;
	else if (!ft_strcmp(tsh->buf, "\177"))
		return ;
	else if (!ft_isprint(tsh->buf[tsh->symbols - 1]))
		tsh->buf[tsh->symbols - 1] = 0;
}

static	void	get_next_symbol(t_tsh *tsh)
{
	tsh->is_termcap = 0;
	tsh->symbols = read(0, tsh->buf, 1024);
	tsh->buf[tsh->symbols] = '\0';
	ctrl_char_handler(tsh);
}

static	void	terminal_input(t_tsh *tsh)
{
	get_next_symbol(tsh);
	termcap_processor(tsh->buf, tsh);
	write(1, tsh->buf, tsh->symbols);
	if (!tsh->is_termcap)
	{
		tsh->line = ft_memjoin_tsh(tsh->line, tsh->buf);
		if (tsh->his_ptr && tsh->his_ptr->content)
			history_editor(tsh);
	}
	if (!ft_strcmp(tsh->line, "\4"))
		ctrl_d(tsh);
	ft_bzero(tsh->buf, 1024);
}

static	void	terminal_output(t_tsh *tsh)
{
	switch_term_attr(tsh);
	line_parser(tsh);
	switch_term_attr(tsh);
	add_to_history(tsh);
}

int	main(int argc, char **argv, char **env)
{
	t_tsh	tsh;

	(void)argc;
	(void)argv;
	tsh.env = NULL;
	env_to_lst(&tsh.env, env);
	init_shell(&tsh, argv[0]);
	envlist_to_arr(&tsh);
	while (tsh.is_running)
	{
		new_prompt(&tsh);
		while (!tsh.end_line)
			terminal_input(&tsh);
		if (ft_strcmp(tsh.line, "\n"))
			terminal_output(&tsh);
		ft_bzero(tsh.line, ft_strlen(tsh.line));
	}
	return (0);
}

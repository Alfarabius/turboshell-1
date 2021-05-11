#include "minishell.h"

static	void	manual_signal_handler(t_tsh *tsh)
{
	if (tsh->buf[tsh->symbols - 1] == '\n')
		tsh->end_line = 1;
	if (tsh->buf[tsh->symbols - 1] == '\3')
		ctrl_c(tsh);
}

static	void	get_next_symbol(t_tsh *tsh)
{
	tsh->is_termcap = 0;
	tsh->symbols = read(0, tsh->buf, 1024);
	tsh->buf[tsh->symbols] = '\0';
	write(1, tsh->buf, tsh->symbols);
}

static	void	terminal_input(t_tsh *tsh)
{
	get_next_symbol(tsh);
	manual_signal_handler(tsh);
	termcap_processor(tsh->buf, tsh);
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
	signal_handler(tsh);
	line_parser(tsh);
	switch_term_attr(tsh);
	add_to_history(tsh);
}

int	main(int argc, char **argv, char **env)
{
	t_tsh	tsh;

	(void)argc;
	(void)argv;
	init_shell(&tsh);
	env_to_lst(&tsh.env, env);
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

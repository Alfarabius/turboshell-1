#ifndef MINISHELL_H
# define MINISHELL_H
# define TERM_NAME "xterm-256color"
# define TSH_NAME "\x1B[33m turboshell-1.0$ \x1B[0m"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "./Libft/libft.h"
# include <term.h>
# include <curses.h>

typedef	struct		s_dict
{
	char			*key;
	char			*value;
	char			is_separ;
	char			is_set;
}					t_dict;

typedef	struct		s_msh
{
	struct	termios	term;
	t_list			*env;
	char			buf[1024];
	char			*line;
	char			is_running;
	int				symbols;
	int				hfd;
}					t_tsh;

void				line_parser(t_tsh tsh);
int					env_to_lst(t_list **lst, char **env);
int					error_handler(char *msg);
int					termcap_processor(char *line, t_tsh *tsh);
int					history_up(t_tsh *tsh);
int					history_down(t_tsh *tsh);
int					move_right_line(t_tsh *tsh);
int					move_left_line(t_tsh *tsh);
int					erase_symbol(t_tsh *tsh);
int					term_clean_up(void);

#endif

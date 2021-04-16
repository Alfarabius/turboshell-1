#ifndef MINISHELL_H
# define MINISHELL_H
# define TERM_NAME "xterm-256color"
# define TSH_NAME "\x1B[33m turboshell-1.0$ \x1B[0m"
# define BUFFER_SIZE 1024
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "./Libft/libft.h"
# include <term.h>
# include <curses.h>
# include <stdlib.h>
# include <signal.h>

typedef	struct	s_gnl
{
	char		*buf;
	ssize_t		bwr;
	int			fd;
}				t_gnl;

typedef	struct		s_prsr
{
	char			**args;
	char			*line;
	int				l_index;
	int				current_arg;
	int				parse_status;
}					t_prsr;

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
	t_dlst			*his;
	t_dlst			*his_ptr;
	t_prsr			*prsr;
	char			buf[1024];
	char			*line;
	char			*tmp;
	char			is_running;
	char			end_line;
	char			is_termcap;
	int				symbols;
	int				hfd;
}					t_tsh;

void				ft_exit(t_tsh tsh);
void				ft_env(t_tsh *tsh);
void				ft_unset(t_tsh *tsh);
void				line_parser(t_tsh *tsh);
void				ft_pwd(t_tsh *tsh);
void				error_checker(int cond, char *msg, char flg);
void				del_elem(void *elem);
int					env_to_lst(t_list **lst, char **env);
int					elem_to_lst(char *env_elem, t_list **lst);
int					error_handler(char *msg, char flg);
int					termcap_processor(char *line, t_tsh *tsh);
int					history_up(t_tsh *tsh);
int					history_down(t_tsh *tsh);
int					history_editor(t_tsh *tsh);
int					file_to_history(t_tsh *tsh);
int					erase_symbol(t_tsh *tsh);
int					add_to_history(t_tsh *tsh);
int					ft_putint(int c);
int					cmd_processor(t_tsh *tsh);
int					file_to_history(t_tsh *tsh);
int					get_next_line(int fd, char **line);
char				*ft_newreminder(char *rem, char *err);
char				*ft_strjoin_gnl(char *s1, char *s2);
char				*ft_nextline(char *rem);
char				*ft_realloc(char *str, int num, int c);
void				*ft_memdup(const void* mem, size_t size);
void				*ft_memjoin(void *s1, void *s2, size_t l1, size_t l2);

#endif

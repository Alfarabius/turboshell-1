#ifndef MINISHELL_H
# define MINISHELL_H
# define TERM_NAME "xterm-256color"
# define TSH_NAME "\x1B[33mturboshell-1.0$ \x1B[0m"
# define BUFFER_SIZE 1024
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "./Libft/libft.h"
# include <term.h>
# include <curses.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef struct	s_ppe
{
	int			status;
	int			count;
	int			fd[2];
}				t_ppe;

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
	t_ppe			*pipe;
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
void				ft_echo(t_tsh *tsh);
void				line_parser(t_tsh *tsh);
void				ft_pwd(t_tsh *tsh);
void				error_checker(int cond, char *msg, char flg);
void				del_elem(void *elem);
void				ft_cd(t_tsh *tsh);
void				ft_export(t_tsh *tsh);
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
int					signal_handler(t_tsh *tsh);
char				*ft_newreminder(char *rem, char *err);
char				*ft_strjoin_gnl(char *s1, char *s2);
char				*ft_nextline(char *rem);
char				*ft_realloc(char *str, int num, int c);
char				*ft_memjoin_tsh(char *s1, char *s2);
void				*ft_memdup(const void* mem, size_t size);

#endif

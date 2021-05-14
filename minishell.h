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
//# include <curses.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>

int				g_exit_status;

typedef struct s_ppe
{
	int			current;
	int			count;
	int			fd[1024][2];
}				t_ppe;

typedef struct s_gnl
{
	char		*buf;
	ssize_t		bwr;
	int			fd;
}				t_gnl;

typedef struct s_redrct
{
	int				type;
	int				fd;
	int				arg_num;
	char			*file_path;
}					t_redrct;

typedef struct s_prsr
{
	t_redrct		**redirects;
	char			**args;
	char			*line;
	int				l_index;
	int				current_arg;
	int				parse_status;
	t_ppe			pipe;
}					t_prsr;

typedef struct s_dict
{
	char			*key;
	char			*value;
	char			is_separ;
	char			is_set;
}					t_dict;

typedef struct s_msh
{
	struct termios	term;
	t_list			*env;
	t_dlst			*his;
	t_dlst			*his_ptr;
	t_prsr			prsr;
	char			**env_arr;
	char			buf[1024];
	char			*line;
	char			is_running;
	char			end_line;
	char			is_termcap;
	int				symbols;
	int				hfd;
	int				original_fd[2];
	int				redirect_fd;
	int				input_fd;
	int				output_fd;
}					t_tsh;

void				ft_exit(t_tsh *tsh);
void				ft_env(t_tsh *tsh);
void				ft_unset(t_tsh *tsh);
void				ft_echo(t_tsh *tsh);
void				line_parser(t_tsh *tsh);
void				ft_pwd(t_tsh *tsh);
void				error_checker(int cond, char *msg, char flg);
void				del_elem(void *elem);
void				ft_cd(t_tsh *tsh);
void				ft_export(t_tsh *tsh);
void				pipe_processor(t_tsh *tsh);
void				wait_pipes(t_tsh *tsh);
void				switch_term_attr(t_tsh *tsh);
void				init_shell(t_tsh *tsh);
void				ctrl_c(t_tsh *tsh);
void				ctrl_d(t_tsh *tsh);
void				open_redirects(t_tsh *tsh);
void				close_redirects(t_tsh *tsh);
void				redirect_handler(t_tsh *tsh);
void				clear_redirects(t_tsh *tsh);
void				clear_arr(char ***arr);
int					env_to_lst(t_list **lst, char **env);
int					elem_to_lst(char *env_elem, t_list **lst);
int					error_handler(char *msg, char flg);
int					termcap_processor(char *line, t_tsh *tsh);
int					history_editor(t_tsh *tsh);
int					file_to_history(t_tsh *tsh);
int					add_to_history(t_tsh *tsh);
int					ft_putint(int c);
int					cmd_processor(t_tsh *tsh);
int					get_next_line(int fd, char **line);
int					signal_handler(t_tsh *tsh);
int					is_separ_exist(char *env_elem);
int					new_prompt(t_tsh *tsh);
int					binary_processor(t_tsh *tsh);
int					envlist_to_arr(t_tsh *tsh);
size_t				keylen(char *env_elem);
char				*ft_newreminder(char *rem, char *err);
char				*ft_strjoin_gnl(char *s1, char *s2);
char				*ft_nextline(char *rem);
char				*ft_realloc(char *str, int num, int c);
char				*ft_memjoin_tsh(char *s1, char *s2);
char				*get_env_value(t_tsh tsh, char *key);
void				*ft_memdup(const void *mem, size_t size);
t_dict				*get_env_elem(t_tsh tsh, char *key);
t_list				*sort_dict_ascii(t_list **dict);
char				*dict_to_str(t_dict *elem);

#endif

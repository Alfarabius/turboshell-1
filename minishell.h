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
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/syslimits.h>

int			g_exit_status;

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
	t_dlst			*curr_his;
	t_dlst			*his;
	t_dlst			*his_ptr;
	t_prsr			prsr;
	char			**env_arr;
	char			buf[1024];
	char			term_buf[2048];
	char			*line;
	char			*wdir;
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

void				ft_exit(t_tsh *tsh, int i);
void				ft_env(t_tsh *tsh);
void				ft_unset(t_tsh *tsh);
void				ft_echo(t_tsh *tsh);
void				line_parser(t_tsh *tsh);
void				ft_pwd(void);
void				error_checker(int cond, char *msg, char flg);
void				save_history_exit(int status, t_tsh *tsh);
void				del_elem(void *elem);
void				ft_cd(t_tsh *tsh, char *dir);
void				ft_export(t_tsh *tsh);
void				pipe_processor(t_tsh *tsh);
void				wait_pipes(t_tsh *tsh);
void				switch_term_attr(t_tsh *tsh);
void				init_shell(t_tsh *tsh, char *path);
void				ctrl_c(t_tsh *tsh);
void				ctrl_d(t_tsh *tsh);
void				open_redirects(t_tsh *tsh);
void				close_redirects(t_tsh *tsh);
void				redirect_handler(t_tsh *tsh);
void				clear_redirects(t_tsh *tsh);
void				clear_arr(char ***arr);
void				signal_handler(int signum);
void				dictdelone(void *dict);
void				error_template(char *head, char *arg, char *error);
void				error_template_prsr(char *head, char *arg, \
					char *error, t_tsh *tsh);
void				print_syntax_error(int i, t_tsh *tsh);
void				arg_to_lower(t_tsh *tsh);
void				exit_status_handler(int status);
void				builtin_error(char *msg, char *name, char *btin);
int					env_to_lst(t_list **lst, char **env);
int					elem_to_lst(char *env_elem, t_list **lst);
int					error_handler(char *msg, char flg);
int					termcap_processor(char *line, t_tsh *tsh);
int					history_editor(t_tsh *tsh);
int					file_to_history(t_tsh *tsh);
int					add_to_history(t_tsh *tsh);
void				history_to_file(t_tsh *tsh);
int					ft_putint(int c);
int					cmd_processor(t_tsh *tsh);
int					get_next_line(int fd, char **line);
int					is_separ_exist(char *env_elem);
int					new_prompt(t_tsh *tsh);
void				binary_processor(t_tsh *tsh, int status);
int					envlist_to_arr(t_tsh *tsh);
int					binary_in_dir(char *path, char *bin);
int					is_file_accessible(const char *file, int flag);
size_t				keylen(char *env_elem);
char				*get_dir_for_history(t_tsh *tsh, char *path);
char				*ft_newreminder(char *rem, char *err);
char				*ft_strjoin_gnl(char *s1, char *s2);
char				*ft_nextline(char *rem);
char				*ft_memjoin_tsh(char *s1, char *s2);
char				*get_env_value(t_tsh tsh, char *key);
char				*ft_realloc(char *str, int num, int c);
void				*ft_memdup(const void *mem, size_t size);
t_dict				*dictdup(t_dict *dict);
t_dict				*get_env_elem(t_tsh tsh, char *key);
t_list				*sort_dict_ascii(t_list **dict);
t_list				*dictlstdup(t_list *lst);
char				*dict_to_str(t_dict *elem);
void				single_qoutes_case(t_prsr *prsr);
void				double_qoutes_case(t_prsr *prsr);
void				redirect_case(t_prsr *prsr);
void				common_case(t_prsr *prsr);
void				distributor(t_prsr *prsr);
void				syntax_checker(t_tsh *tsh);
void				add_line(char ***arr, char *line, t_prsr *prsr);
void				add_redrct(t_redrct ***arr, t_redrct *redrct);
int					skip_whitespaces(char *str, int i);
int					is_whitespace(char c);
char				*get_env(t_tsh tsh, int *i, char *line);
char				*preparser(char **line, t_tsh *tsh);

#endif

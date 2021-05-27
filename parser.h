#ifndef PARSER_H

#include "minishell.h"

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

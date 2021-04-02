/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:25:35 by mrosie            #+#    #+#             */
/*   Updated: 2021/04/02 17:52:57 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define STANDART  "\x1B[0m"
# define YELLOW  "\x1B[33m"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "./Libft/libft.h"
# include <termcap.h>

typedef	struct	s_dict
{
	char	*key;
	char	*value;
	char	is_separ;
	char	is_set;
}				t_dict;

typedef	struct	s_msh
{
	t_list	*env;
	char	buf[1024];
	char	is_running;
	int		symbols;
}				t_tsh;

void	line_parser(char *str);
int		env_to_lst(t_list **lst, char **env);
int		error_handler(char *msg);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plurlene <plurlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:25:35 by mrosie            #+#    #+#             */
/*   Updated: 2021/04/01 19:46:15 by plurlene         ###   ########.fr       */
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

typedef	struct	s_dict
{
	char	*key;
	char	*value;
	char	separ;
}				t_dict;

void line_parser(char *str);

#endif

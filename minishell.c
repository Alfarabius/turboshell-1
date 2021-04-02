/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plurlene <plurlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:25:30 by mrosie            #+#    #+#             */
/*   Updated: 2021/04/02 17:07:08 by plurlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	buf[1024];
	char	shell_is_running;
	int		num_read;

	shell_is_running = 1;
	num_read = 0;
	(void)argc;
	(void)argv;
	(void)env;
	while (shell_is_running)
	{
		write(1, YELLOW, 6);
		write(1, "turboshell-1.0$ ", 17);
		write(1, STANDART, 5);
		num_read = read(0, buf, 1024);
		if (!num_read)
			write(1, "\n", 2);
		if (buf[0] != '\n')
			printf("out: %s", buf);
		line_parser(buf);
		ft_bzero(buf, 1024);
	}
	return (0);
}

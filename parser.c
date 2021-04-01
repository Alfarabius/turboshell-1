/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plurlene <plurlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:27:59 by plurlene          #+#    #+#             */
/*   Updated: 2021/04/01 20:19:22 by plurlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static char *ft_strndup(char *str, int n)
{
	char *res;
	char *temp;

	temp = ft_strdup(str);
	temp[n] = '\0';
	res = ft_strdup(temp);
	free(temp);
	return (res);
}

static char *ft_clear_strdup(char *str)
{
	char *res;

	res = ft_strdup(str);
	free(str);
	return (res);
}

static void add_line(char ***arr, char *line, int n)
{
	int		len;
	char	**result_arr;

	len = 0;
	while ((*arr)[len] != NULL)
		len++;
	result_arr = (char **)malloc(sizeof(char *) * (len + 2));
	result_arr[len + 1] = NULL;
	result_arr[len] = ft_strndup(line, n);
	while (--len >= 0)
		result_arr[len] = ft_clear_strdup((*arr)[len]);
	free(*arr);
	*arr = result_arr;
}

void line_parser(char *str)
{
/*--- really specsigns : " $\"\'" ---*/
//	char *specsigns = " ";
	char **args;
	int i;
	int n;

	(void) str;
	args = (char **)malloc(sizeof(char *));
	args[0] = NULL;
	i = 0;
	while (str[i])
	{
		n = 0;
		while (str[i] && str[i] == ' ')
			i++;
		n = i;
		while (str[n] && str[n] != ' ')
			n++;
		add_line(&args, &str[i], n - i);
		i = n;
	}
	i = -1;
	while (args[++i])
		printf("args: %s\n", args[i]);
}

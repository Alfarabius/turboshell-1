/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plurlene <plurlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:27:59 by plurlene          #+#    #+#             */
/*   Updated: 2021/04/02 17:54:50 by plurlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void clear_arr(char ***arr)
{
	int i;

	i = -1;
	if (*arr)
	{
		while ((*arr)[++i])
		{

			free((*arr)[i]);
		}
		free(*arr);
		*arr = NULL;
	}
}

static char *ft_clear_strdup(char *str)
{
	char *res;

	res = ft_strdup(str);
	free(str);
	return (res);
}

static void add_line(char ***arr, char *line)
{
	int		len;
	char	**result_arr;

	len = 0;
	while ((*arr)[len] != NULL)
		len++;
	result_arr = (char **)malloc(sizeof(char *) * (len + 2));
	result_arr[len + 1] = NULL;
	result_arr[len] = ft_strdup(line);
	while (--len >= 0)
		result_arr[len] = ft_clear_strdup((*arr)[len]);
	free(*arr);
	*arr = result_arr;
}

int skip_whitespaces(char *str, int i)
{
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

// NULL to the pointer after free
static void ft_free(void **bfree)
{
	if (*bfree)
		free(*bfree);
	*bfree = NULL;
}

static char *ft_realloc(char *str, int num, int c)
{
	char	*res;
	int		len;
	int		i;

	len =  ft_strlen(str);
	len += num + 1;
	res = (char *)malloc(len);
	res[len - 1] = '\0';
	i = -1;
	while (str[++i])
		res[i] = str[i];
	while (i < len - 1)
	{
		res[i] = c;
		i++;
	}
	ft_free((void **)&str);
	return (res);
}

void line_parser(char *str)
{
	char **args;
	char *current_arg;
	int i;

	args = (char **)malloc(sizeof(char *));
	args[0] = NULL;
	current_arg = (char *)malloc(1);
	current_arg[0] = '\0';
	i = skip_whitespaces(str, 0) - 1;
	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '\n') //воткнуть свич кейс на спец символы и кавычки
			current_arg = ft_realloc(current_arg, 1, str[i]);
		else
		{
			i = skip_whitespaces(str, i) - 1;
			add_line(&args, current_arg);
			ft_free((void **)&current_arg);
			current_arg = (char *)malloc(1);
			current_arg[0] = '\0';
		}
	}
	i = -1;
	while (args[++i])
		printf("args: %s\n", args[i]);
	clear_arr(&args);
	if (current_arg)
		free(current_arg);
}

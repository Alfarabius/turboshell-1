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
		result_arr[len] = (*arr)[len];
	*arr = result_arr;
}

int skip_whitespaces(char *str, int i)
{
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
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

// static int	parser_case(char *str, char *str_case, int n)
// {
// 	if (ft_strnstr(str, str_case, n))
// 		return (1);
// 	return (0);
// }

// void	switch_case(char *str, char *current)
// {
// 	if (parser_case(str, "$", 1))
// 		(void *)str;
// 	if (parser_case(str, "\"", 1))
// 		(void *)str;
// 	if (parser_case(str, "\'", 1))
// 		(void *)str;
// }

int is_separ(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char *get_env_arg(char *str, t_tsh tsh)
{
	int i;
	char *key;
	char *separs = " 	\'\"=";

	key = (char *)malloc(1);
	key[0] = '\0';
	i = -1;
	while (str[++i])
	{
		if (ft_strrchr(separs, str[i]))
			break ;
		ft_realloc(key, 1, str[i]);
	}
	printf ("i: %d len: %zu\n", i, ft_strlen(key));
	while (tsh.env)
	{
		if (ft_strncmp(key, ((t_dict *)(tsh.env->content))->key, i))
		{
			free(key);
			key = ((t_dict *)(tsh.env->content))->value;
		}
		tsh.env = tsh.env->next;
	}
	if (!tsh.env)
		key = NULL;
	return (key);
}

char *double_quotes_case(char *str, t_tsh tsh, int *i)
{
	char *res;
	char *env_arg;
	char *temp;

	res = (char *)malloc(1);
	res[0] = '\0';
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] != '$')
			res = ft_realloc(res, 1, str[*i]);
		else
		{
			env_arg = get_env_arg(&(str[*i]), tsh);
			if (env_arg)
			{
				temp = ft_strjoin(res, env_arg);
				free(res);
				res = temp;
			}
		}
		(*i)++;
	}

	return (res);
}

char *common_case(char *str, int *i)
{
	char *res;
	res = (char *)malloc(1);
	res[0] = '\0';
	while(str[*i] && !is_separ(str[*i]))
	{
		res = ft_realloc(res, 1, str[*i]);
		(*i)++;
	}
	(*i) = skip_whitespaces(str, (*i)) - 1;
	return (res);
}

int distributor(char *str, t_tsh tsh, char ***args)
{
	int i;

	i = 0;
	if (*str == '\"')
		add_line(args, double_quotes_case(str, tsh, &i));
	if (*str != '\"')
		add_line(args, common_case(str, &i));
	return (i);
}

void line_parser(t_tsh tsh)
{
	char **args;
	char *current_arg;
	int i;

	args = (char **)malloc(sizeof(char *));
	args[0] = NULL;
	current_arg = (char *)malloc(1);
	current_arg[0] = '\0';
	i = skip_whitespaces(tsh.line, 0) - 1;
	while (tsh.line[++i])
	{
		// if (tsh.line[i] != ' ' && tsh.line[i] != '\n') //воткнуть свич кейс на спец символы и кавычки
		// 	current_arg = ft_realloc(current_arg, 1, tsh.line[i]);
		// //свич на кавычки с передачей указателя на i
		// else
		// {
		// 	i = skip_whitespaces(tsh.line, i) - 1;
		// 	add_line(&args, current_arg);
		// 	ft_free((void **)&current_arg);
		// 	current_arg = (char *)malloc(1);
		// 	current_arg[0] = '\0';
		// }
		i += distributor(&(tsh.line[i]), tsh, &args);
	}
	i = -1;
	// while (args[++i])
	// 	printf("args: %s\n", args[i]);
	clear_arr(&args);
	if (current_arg)
		free(current_arg);
}

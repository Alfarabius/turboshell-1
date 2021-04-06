# include "minishell.h"

// NULL to the pointer after free
static void ft_free(void **bfree)
{
	if (*bfree)
		free(*bfree);
	*bfree = NULL;
}

void clear_arr(char ***arr)
{
	int i;

	i = -1;
	if (*arr)
	{
		while ((*arr)[++i])
		{
			ft_free((void **)(&(*arr)[i]));
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

int is_separ(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void enivroment_case(t_tsh tsh, char ***args, int *i, int *current)
{
	char *key;
	char *value;

	key = (char *)malloc(1);
	key[0] = '\0';
	value = NULL;
	(*i)++;
	while (tsh.line[*i])
	{
		if (tsh.line[*i] == '$' || is_separ(tsh.line[*i]))
			break ;
		key = ft_realloc(key, 1, tsh.line[*i]);
		(*i)++;
	}
	while (tsh.env)
	{
		if (!ft_strncmp(key, ((t_dict *)(tsh.env->content))->key, ft_strlen(key)))
		{
			value = ((t_dict *)(tsh.env->content))->value;
			break ;
		}
		tsh.env = tsh.env->next;
	}
	if (!value)
		value = ft_strjoin("$", key);
	(*args)[*current] = ft_strjoin((*args)[*current], value);
	free(key);
}

void double_qoutes_case2(t_tsh tsh, char ***args, int *i, int *current)
{
	(*i)++;
	while (tsh.line[*i] && tsh.line[*i] != '\"')
	{
		if (tsh.line[*i] == '$')
			enivroment_case(tsh, args, i, current);
		(*args)[*current] = ft_realloc((*args)[*current], 1, tsh.line[*i]);
		(*i)++;
	}
	if (tsh.line[*i] == '\"')
		(*i)++;
}

void common_case2(t_tsh tsh, char ***args, int *i, int *current)
{
	*i = skip_whitespaces(tsh.line, *i);
	while (tsh.line[*i])
	{
		if (is_separ(tsh.line[*i]))
		{
			add_line(args, "\0");
			(*current)++;
			return ;
		}
		if (tsh.line[*i] == '$' || tsh.line[*i] == '\"' || tsh.line[*i] == '\'')
			return ;
		(*args)[*current] = ft_realloc((*args)[*current], 1, tsh.line[*i]);
		(*i)++;
	}
}

void distributor2(t_tsh tsh, char ***args, int *i, int *current)
{
	if (tsh.line[*i] == '\"')
		double_qoutes_case2(tsh, args, i, current);
	if (tsh.line[*i] == '$' )
		enivroment_case(tsh, args, i, current);
	if (tsh.line[*i] != '\"' && tsh.line[*i] != '$')
		common_case2(tsh, args, i, current);
}

void line_parser(t_tsh tsh)
{
	char **args;
	int current_arg;
	int i;

	args = (char **)malloc(sizeof(char *) * 2);
	args[0] = (char *)malloc(1);
	args[0][0] = '\0';
	args[1] = NULL;
	current_arg = 0;
	i = 0;
	while (tsh.line[i])
	{
		distributor2(tsh, &args, &i, &current_arg);
		i++;
	}
	i = -1;
	while (args[++i])
		printf("args: %s\n", args[i]);
	clear_arr(&args);
}

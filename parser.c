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

void enivroment_case(t_tsh tsh, t_prsr *prsr)
{
	char *key;
	char *value;

	key = (char *)malloc(1);
	key[0] = '\0';
	value = NULL;
	(prsr->l_index)++;
	while (tsh.line[prsr->l_index])
	{
		if (tsh.line[prsr->l_index] == '\n')
		{
			prsr->parse_status = 0;
			break ;
		}
		if (tsh.line[prsr->l_index] == '$' || is_separ(tsh.line[prsr->l_index]))
			break ;
		key = ft_realloc(key, 1, tsh.line[prsr->l_index]);
		(prsr->l_index)++;
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
	(prsr->args)[prsr->current_arg] = ft_strjoin((prsr->args)[prsr->current_arg], value);
	free(key);
}

void double_qoutes_case2(t_tsh tsh, t_prsr *prsr)
{
	(prsr->l_index)++;
	while (tsh.line[prsr->l_index] && tsh.line[prsr->l_index] != '\"')
	{
		if (tsh.line[prsr->l_index] == '\n')
		{
			prsr->parse_status = 0;
			break ;
		}
		if (tsh.line[prsr->l_index] == '$')
			enivroment_case(tsh, prsr);
		(prsr->args)[prsr->current_arg] = ft_realloc((prsr->args)[prsr->current_arg], 1, tsh.line[prsr->l_index]);
		(prsr->l_index)++;
	}
	if (tsh.line[prsr->l_index] == '\"')
		(prsr->l_index)++;
}

void common_case2(t_tsh tsh, t_prsr *prsr)
{
	prsr->l_index = skip_whitespaces(tsh.line, prsr->l_index);
	while (tsh.line[prsr->l_index])
	{
		if (tsh.line[prsr->l_index] == '\n')
		{
			prsr->parse_status = 0;
			break ;
		}
		if (is_separ(tsh.line[prsr->l_index]))
		{
			add_line(&prsr->args, "\0");
			(prsr->current_arg)++;
			return ;
		}
		if (tsh.line[prsr->l_index] == '$' || tsh.line[prsr->l_index] == '\"' || tsh.line[prsr->l_index] == '\'')
			return ;
		(prsr->args)[prsr->current_arg] = ft_realloc((prsr->args)[prsr->current_arg], 1, tsh.line[prsr->l_index]);
		(prsr->l_index)++;
	}
}

void distributor2(t_tsh tsh, t_prsr *prsr)
{
	if (tsh.line[prsr->l_index] == '\"')
		double_qoutes_case2(tsh, prsr);
	if (tsh.line[prsr->l_index] == '$' )
		enivroment_case(tsh, prsr);
	if (tsh.line[prsr->l_index] != '\"' && tsh.line[prsr->l_index] != '$')
		common_case2(tsh, prsr);
}

void line_parser(t_tsh tsh)
{
	t_prsr prsr;

	prsr.args = (char **)malloc(sizeof(char *) * 2);
	prsr.args[0] = (char *)malloc(1);
	prsr.args[0][0] = '\0';
	prsr.args[1] = NULL;
	prsr.current_arg = 0;
	prsr.l_index = 0;
	prsr.parse_status = 1;
	while (tsh.line[prsr.l_index] && tsh.line[prsr.l_index] != '\n')
	{
		distributor2(tsh, &prsr);
		if (prsr.l_index >= ft_strlen(tsh.line) || !prsr.parse_status || tsh.line[prsr.l_index] == '\n')
			break ;
		prsr.l_index++;
	}
	prsr.parse_status = 0;
	prsr.l_index = -1;
	while (prsr.args[++prsr.l_index])
		printf("args: %s\n", prsr.args[prsr.l_index]);
	clear_arr(&prsr.args);
}

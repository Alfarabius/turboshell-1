# include "minishell.h"

void clear_arr(char ***arr)
{
	int i;

	i = -1;
	if (*arr)
	{
		while ((*arr)[++i])
		{
			ft_freen((void **)(&(*arr)[i]));
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
	error_checker(!result_arr, "memmory doesn't allocated", 1);
	result_arr[len + 1] = NULL;
	result_arr[len] = ft_strdup(line);
	error_checker(!result_arr[len], "memmory doesn't allocated", 1);
	while (--len >= 0)
		result_arr[len] = (*arr)[len];
	free(*arr);
	*arr = result_arr;
}

int is_whitespace(char c)
{
	if (c == 9 || c == 32)
		return (1);
	return (0);
}

int skip_whitespaces(char *str, int i)
{
	while (str[i] && is_whitespace(str[i]))
		i++;
	return (i);
}

char *ft_realloc(char *str, int num, int c)
{
	char	*res;
	int		len;
	int		i;

	len =  ft_strlen(str);
	len += num + 1;
	res = (char *)malloc(len);
	error_checker(!res, "memmory doesn't allocated", 1);
	res[len - 1] = '\0';
	i = -1;
	while (str[++i])
		res[i] = str[i];
	while (i < len - 1)
	{
		res[i] = c;
		i++;
	}
	ft_freen((void **)&str);
	return (res);
}

void single_qoutes_case(t_prsr *prsr)
{
	(prsr->l_index)++;
	while (prsr->line[prsr->l_index] && prsr->line[prsr->l_index] != '\'')
	{
		if (prsr->line[prsr->l_index] == '\n')
		{
			prsr->parse_status = 0;
			break ;
		}
		(prsr->args)[prsr->current_arg] = ft_realloc((prsr->args)[prsr->current_arg], 1, prsr->line[prsr->l_index]);
		(prsr->l_index)++;
	}
	if (prsr->line[prsr->l_index] && is_whitespace(prsr->line[prsr->l_index + 1]) && prsr->line[skip_whitespaces(prsr->line, prsr->l_index + 1)] != '\n')
	{
		add_line(&prsr->args, "\0");
		(prsr->current_arg)++;
	}
	if (prsr->line[prsr->l_index] != '\'')
		error_handler("Syntax error\n", 1);
}

void double_qoutes_case(t_prsr *prsr)
{
	int shielding;

	shielding = 0;
	(prsr->l_index)++;
	while (prsr->line[prsr->l_index] && (prsr->line[prsr->l_index] != '\"' || (prsr->line[prsr->l_index] == '\"' && shielding)))
	{
		if (prsr->line[prsr->l_index] == '\n')
		{
			prsr->parse_status = 0;
			break ;
		}
		if (prsr->line[prsr->l_index] == '\\' && ft_strchr("$\\`\"", prsr->line[prsr->l_index + 1]))
		{
			(prsr->l_index)++;
			shielding = 1;
			continue ;
		}
		else
		{
			(prsr->args)[prsr->current_arg] = ft_realloc((prsr->args)[prsr->current_arg], 1, prsr->line[prsr->l_index]);
			(prsr->l_index)++;
		}
		shielding = 0;
	}
	if (prsr->line[prsr->l_index] != '\"' && !shielding)
		error_handler("Syntax error\n", 1);
	if (prsr->line[prsr->l_index] && is_whitespace(prsr->line[prsr->l_index + 1]) && prsr->line[skip_whitespaces(prsr->line, prsr->l_index + 1)] != '\n')
	{
		add_line(&prsr->args, "\0");
		(prsr->current_arg)++;
	}
}

void common_case(t_prsr *prsr)
{
	int shielding;

	shielding = 0;
	prsr->l_index = skip_whitespaces(prsr->line, prsr->l_index);
	while (prsr->line[prsr->l_index])
	{
		if (prsr->line[prsr->l_index] == '\n')
		{
			prsr->parse_status = 0;
			break ;
		}
		if (is_whitespace(prsr->line[prsr->l_index]))
		{
			add_line(&prsr->args, "\0");
			(prsr->current_arg)++;
			return ;
		}
		if (prsr->line[prsr->l_index] == '\\')
		{
			(prsr->l_index)++;
			shielding = 1;
		}
		if (!shielding && (prsr->line[prsr->l_index] == '$' || prsr->line[prsr->l_index] == '\"' || prsr->line[prsr->l_index] == '\''))
			return ;
		(prsr->args)[prsr->current_arg] = ft_realloc((prsr->args)[prsr->current_arg], 1, prsr->line[prsr->l_index]);
		(prsr->l_index)++;
		shielding = 0;
	}
}

void distributor(t_prsr *prsr)
{
	if (prsr->line[prsr->l_index] != '\"' && prsr->line[prsr->l_index] != '\'')
		common_case(prsr);
	if (prsr->line[prsr->l_index] == '\"')
		double_qoutes_case(prsr);
	if (prsr->line[prsr->l_index] == '\'')
		single_qoutes_case(prsr);
}

char *get_env(t_tsh tsh, int *i)
{
	char *key;
	char *value;
	char *spec_signs = "$\"\'\\,;|<> 	";

	key = (char *)malloc(1);
	error_checker(!key, "memmory doesn't allocated", 1);
	key[0] = '\0';
	value = NULL;
	(*i)++;
	if (ft_isdigit(tsh.line[*i]))
	{
		(*i)++;
		free(key);
		return ("");
	}
	while (tsh.line[*i])
	{
		if (tsh.line[*i] == '\n')
			break ;
		if (ft_strchr(spec_signs, tsh.line[*i]))
			break ;
		key = ft_realloc(key, 1, tsh.line[*i]);
		(*i)++;
	}
	while (tsh.env && key[0])
	{
		if (!ft_strncmp(key, ((t_dict *)(tsh.env->content))->key, ft_strlen(key)))
		{
			value = ((t_dict *)(tsh.env->content))->value;
			break ;
		}
		tsh.env = tsh.env->next;
	}
	if (!key[0])
		value = "$";
	if (!value)
		value = "";
	free(key);
	return (value);
}

char *preparser(t_tsh *tsh)
{
	int		q_flag;
	int		i;
	int		j;
	char	*res;
	char	*env;

	res = (char *)malloc(1);
	error_checker(!res, "memmory doesn't allocated", 1);
	res[0] = '\0';
	i = 0;
	q_flag = 1;
	while (tsh->line[i])
	{
		if (tsh->line[i] == '\'')
			q_flag = !q_flag;
		if (tsh->line[i] == '\"')
		{
			if (q_flag == 0)
				q_flag = 0;
			else if (q_flag == 1)
				q_flag = 2;
			else if (q_flag == 2)
				q_flag = 1;
		}
		else if ((tsh->line[i] == '$' && tsh->line[i - 1] == '\\') || !q_flag || tsh->line[i] != '$')
			res = ft_realloc(res, 1, tsh->line[i]);
		else if (q_flag && ((i && tsh->line[i - 1] != '\\') || !i))
		{
			env = get_env(*tsh, &i);
			j = 0;
			while (env[j])
			{
				res = ft_realloc(res, 1, env[j]);
				j++;
			}
			continue ;
		}
		i++;
	}
	return (res);
}

void line_parser(t_tsh *tsh)
{
	tsh->prsr.args = (char **)malloc(sizeof(char *) * 2);
	error_checker(!tsh->prsr.args, "memmory doesn't allocated", 1);
	tsh->prsr.args[0] = (char *)malloc(1);
	error_checker(!tsh->prsr.args[0], "memmory doesn't allocated", 1);
	tsh->prsr.args[0][0] = '\0';
	tsh->prsr.args[1] = NULL;
	tsh->prsr.current_arg = 0;
	tsh->prsr.l_index = 0;
	tsh->prsr.parse_status = 1;
	tsh->prsr.line = preparser(tsh);
	while (tsh->prsr.line[tsh->prsr.l_index] && tsh->prsr.line[tsh->prsr.l_index] != '\n')
	{
		distributor(&tsh->prsr);
		if (tsh->prsr.l_index >= ft_strlen(tsh->prsr.line) || !tsh->prsr.parse_status || tsh->prsr.line[tsh->prsr.l_index] == '\n')
			break ;
		tsh->prsr.l_index++;
	}
	tsh->prsr.parse_status = 0;
	tsh->prsr.l_index = -1;
	// while (prsr.args[++prsr.l_index])
	// 	printf("args: %s\n", prsr.args[prsr.l_index]);
	free(tsh->prsr.line);
	cmd_processor(tsh);
	clear_arr(&tsh->prsr.args);
}

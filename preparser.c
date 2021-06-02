#include "minishell.h"

static void	set_qflag(char **line, int i, int *q_flag)
{
	if ((*line)[i] == '\'')
	{
		if (*q_flag == 0)
			*q_flag = 1;
		else if (*q_flag == 1)
			*q_flag = 0;
		else if (*q_flag == 2)
			*q_flag = 2;
	}
	if ((*line)[i] == '\"')
	{
		if (*q_flag == 0)
			*q_flag = 0;
		else if (*q_flag == 1)
			*q_flag = 2;
		else if (*q_flag == 2)
			*q_flag = 1;
	}
}

static void	set_quotes(char **res, char *env)
{
	int	j;

	j = 0;
	if (env[0] && ft_strlen(*res))
		*res = ft_realloc(*res, 1, '\"');
	while (env[j])
	{
		*res = ft_realloc(*res, 1, env[j]);
		j++;
	}
	if (env[0] && ft_strlen(*res) - ft_strlen(env))
		*res = ft_realloc(*res, 1, '\"');
}

static void	set_env(char **line, char **res, int *i, t_tsh *tsh)
{
	int		j;
	int		e;
	char	*env;

	j = *i;
	e = j;
	env = get_env(*tsh, i, *line);
	while (j && (*line)[--j] && !ft_strchr("<>", (*line)[j]))
		;
	if (ft_strchr("<>", (*line)[j]) && !env[0])
	{
		write(2, "turboshell-1.0: $", 16);
		while (ft_isalnum((*line)[++e]))
			write(2, &(*line)[e], 1);
		write(2, ": ambiguous redirect\n", 21);
		tsh->prsr.parse_status = 0;
	}
	set_quotes(res, env);
	if ((*line)[(*i) - 1] == '?')
		free(env);
}

static char	*general_cycle(char **line, t_tsh *tsh, int *i, int q_flag)
{
	char	*res;

	res = (char *)malloc(1);
	error_checker(!res, "memmory doesn't allocated", 1);
	res[0] = '\0';
	while ((*line)[*i])
	{
		set_qflag(line, *i, &q_flag);
		if ((*line)[*i] == ';' && q_flag == 1 && i && (*line)[(*i) - 1] != '\\')
		{
			res = ft_realloc(res, 1, (*line)[*i]);
			break ;
		}
		if (((*line)[*i] == '$' && (*line)[(*i) - 1] == '\\') || \
		!q_flag || (*line)[*i] != '$')
			res = ft_realloc(res, 1, (*line)[*i]);
		else if (q_flag && ((*i && (*line)[(*i) - 1] != '\\') || !(*i)))
		{
			set_env(line, &res, i, tsh);
			continue ;
		}
		(*i)++;
	}
	return (res);
}

char	*preparser(char **line, t_tsh *tsh)
{
	int		q_flag;
	int		i;
	char	*res;
	char	*env;

	if (!tsh->prsr.parse_status)
	{
		res = (char *)malloc(1);
		res[0] = '\0';
		return (res);
	}
	i = 0;
	q_flag = 1;
	res = general_cycle(line, tsh, &i, q_flag);
	env = *line;
	*line = ft_strdup(&((*line)[i + 1]));
	free(env);
	return (res);
}

#include "minishell.h"

static void	set_qflag(char **line, int i, int *q_flag)
{
	if ((*line)[i] == '\'')
		*q_flag = !*(q_flag);
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

static void	set_env(char **line, char **res, int *i, t_tsh tsh)
{
	int		j;
	char	*env;

	env = get_env(tsh, i, *line);
	j = 0;
	while (env[j])
	{
		*res = ft_realloc(*res, 1, env[j]);
		j++;
	}
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
			set_env(line, &res, i, *tsh);
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

	i = 0;
	q_flag = 1;
	res = general_cycle(line, tsh, &i, q_flag);
	env = *line;
	*line = ft_strdup(&((*line)[i + 1]));
	free(env);
	return (res);
}

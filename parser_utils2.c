#include "minishell.h"

void	distributor(t_prsr *prsr)
{
	if (prsr->line[prsr->l_index] != '\"' && prsr->line[prsr->l_index] != '\'')
		common_case(prsr);
	if (prsr->line[prsr->l_index] == '\"')
		double_qoutes_case(prsr);
	if (prsr->line[prsr->l_index] == '\'')
		single_qoutes_case(prsr);
}

void	redirect_case(t_prsr *prsr)
{
	t_redrct	redrct;

	if (prsr->args[prsr->current_arg][0])
		add_line(&prsr->args, "\0", prsr);
	redrct.type = 0;
	redrct.file_path = NULL;
	redrct.arg_num = prsr->current_arg;
	redrct.fd = -1;
	while (prsr->line[prsr->l_index] == '>')
	{
		redrct.type++;
		prsr->l_index++;
	}
	if (prsr->line[prsr->l_index] == '<')
	{
		redrct.type = 3;
		prsr->l_index++;
	}
	prsr->l_index = skip_whitespaces(prsr->line, prsr->l_index);
	add_redrct(&prsr->redirects, &redrct);
}

static char	*find_key(int *i, char *line)
{
	char	*key;

	key = (char *)malloc(1);
	error_checker(!key, "memmory doesn't allocated", 1);
	key[0] = '\0';
	if (ft_isdigit(line[*i]))
	{
		(*i)++;
		free(key);
		return ("");
	}
	while (line[*i])
	{
		if (line[*i] == '\n')
			break ;
		if (!ft_isalnum(line[*i]) && line[*i] != '?')
			break ;
		key = ft_realloc(key, 1, line[*i]);
		(*i)++;
		if (line[*i - 1] == '?')
			break ;
	}
	return (key);
}

char	*get_env(t_tsh tsh, int *i, char *line)
{
	char	*key;
	char	*value;

	(*i)++;
	key = find_key(i, line);
	if (ft_isdigit(line[*i]))
		return ("");
	while (tsh.env && key[0])
	{
		if (!ft_strncmp(key, \
		((t_dict *)(tsh.env->content))->key, ft_strlen(key)))
		{
			value = ((t_dict *)(tsh.env->content))->value;
			break ;
		}
		tsh.env = tsh.env->next;
	}
	if (!key[0])
		value = "$";
	if (key[0] == '?')
		value = ft_itoa(g_exit_status);
	if (!value)
		value = "";
	free(key);
	return (value);
}

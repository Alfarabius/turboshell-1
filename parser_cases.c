#include "parser.h"

void	single_qoutes_case(t_prsr *prsr)
{
	prsr->l_index++;
	while (prsr->line[prsr->l_index] && prsr->line[prsr->l_index] != '\'')
	{
		if (prsr->line[prsr->l_index] == '\n')
		{
			prsr->parse_status = 0;
			break ;
		}
		prsr->args[prsr->current_arg] = \
		ft_realloc(prsr->args[prsr->current_arg], 1, prsr->line[prsr->l_index]);
		prsr->l_index++;
	}
	if (prsr->line[prsr->l_index] && is_whitespace(prsr->line[prsr->l_index + 1]) \
	&& prsr->line[skip_whitespaces(prsr->line, prsr->l_index + 1)] != '\n')
		add_line(&prsr->args, "\0", prsr);
	if (prsr->line[prsr->l_index] != '\'')
		error_handler("Syntax error\n", 1);
}

static int	double_quotes_conditions(t_prsr *prsr, int *sh)
{
	if (prsr->line[prsr->l_index] == '\\' && \
	ft_strchr("$\\`\"", prsr->line[prsr->l_index + 1]) && !(*sh))
	{
		prsr->l_index++;
		*sh = 1;
		return (0);
	}
	else
	{
		(prsr->args)[prsr->current_arg] = ft_realloc \
		((prsr->args)[prsr->current_arg], 1, prsr->line[prsr->l_index]);
		prsr->l_index++;
	}
	return (1);
}

void	double_qoutes_case(t_prsr *prsr)
{
	int	shielding;

	shielding = 0;
	prsr->l_index++;
	while (prsr->line[prsr->l_index] && (prsr->line[prsr->l_index] != '\"' \
	|| (prsr->line[prsr->l_index] == '\"' && shielding)))
	{
		if (prsr->line[prsr->l_index] == '\n')
		{
			prsr->parse_status = 0;
			break ;
		}
		if (!double_quotes_conditions(prsr, &shielding))
			continue ;
		shielding = 0;
	}
	if (prsr->line[prsr->l_index] != '\"' && !shielding)
		error_handler("Syntax error\n", 1);
	if (prsr->line[prsr->l_index] && is_whitespace(prsr->line[prsr->l_index + 1]) \
	&& prsr->line[skip_whitespaces(prsr->line, prsr->l_index + 1)] != '\n')
		add_line(&prsr->args, "\0", prsr);
}

static int	common_case_conditions(t_prsr *prsr)
{
	if (prsr->line[prsr->l_index] == '|')
	{
		prsr->pipe.count++;
		prsr->parse_status = 2;
		if (prsr->line[skip_whitespaces(prsr->line, prsr->l_index + 1)] == \
		'\n')
			prsr->l_index = skip_whitespaces(prsr->line, prsr->l_index + 1);
		return (0);
	}
	if (prsr->line[prsr->l_index] == ';' || prsr->line[prsr->l_index] == '\n')
	{
		if (prsr->line[prsr->l_index] == ';')
			prsr->parse_status = 3;
		if (prsr->line[prsr->l_index] == '\n')
			prsr->parse_status = 0;
		return (0);
	}
	if (prsr->line[prsr->l_index] == '>' || prsr->line[prsr->l_index] == '<')
		redirect_case(prsr);
	if (is_whitespace(prsr->line[prsr->l_index]))
		if (!ft_strchr("\n|;", \
		prsr->line[skip_whitespaces(prsr->line, prsr->l_index + 1)]))
			add_line(&prsr->args, "\0", prsr);
	return (1);
}

void	common_case(t_prsr *prsr)
{
	int	shielding;

	shielding = 0;
	prsr->l_index = skip_whitespaces(prsr->line, prsr->l_index);
	while (prsr->line[prsr->l_index])
	{
		if (!common_case_conditions(prsr))
			break ;
		if (is_whitespace(prsr->line[prsr->l_index]))
			return ;
		if (prsr->line[prsr->l_index] == '\\')
		{
			(prsr->l_index)++;
			shielding = 1;
		}
		if (!shielding && ((prsr->line[prsr->l_index] == '$' && \
		ft_isalnum(prsr->line[prsr->l_index + 1])) || \
		prsr->line[prsr->l_index] == '\"' || prsr->line[prsr->l_index] == '\''))
			return ;
		(prsr->args)[prsr->current_arg] = ft_realloc \
		((prsr->args)[prsr->current_arg], 1, prsr->line[prsr->l_index]);
		(prsr->l_index)++;
		shielding = 0;
	}
}

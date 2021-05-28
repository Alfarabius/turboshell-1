#include "minishell.h"

static int	set_flags(char c, int *shield, int *dquote, int *squote)
{
	if (c == '\\' && !(*squote) && !(*shield))
	{
		*shield = !(*shield);
		return (0);
	}
	if (c == '\"' && !(*squote) && !(*shield))
		(*dquote) = !(*dquote);
	if (c == '\'' && !(*dquote) && !(*shield))
		*squote = !(*squote);
	return (1);
}

static int	general_check(int i, t_tsh *tsh, int flags)
{
	if (ft_strchr("|><", tsh->line[i]) && !flags)
	{
		if (tsh->line[skip_whitespaces(tsh->line, i + 1)] == '\n' \
		|| tsh->line[skip_whitespaces(tsh->line, i + 1)] == '\0')
		{
			if (tsh->line[i] == '|')
				error_template("turboshell-1.0", \
				"syntax error", "need more commands");
			else
				write(2, "turboshell-1.0: syntax error near unexpected token `newline'\n", \
				61);
			tsh->prsr.parse_status = 0;
			return (0);
		}
	}
	return (1);
}

static int	check_first_symbol(t_tsh *tsh)
{
	int	i;

	i = skip_whitespaces(tsh->line, 0);
	if (tsh->line[i] == ';' || tsh->line[i] == '|')
	{
		write(2, "turboshell-1.0: syntax error near unexpected token `", 52);
		write(2, &tsh->line[i], 1);
		write(2, "'\n", 2);
		tsh->prsr.parse_status = 0;
		return (0);
	}
	return (1);
}

void	syntax_checker(t_tsh *tsh)
{
	int	i;
	int	shield;
	int	dquote;
	int	squote;

	if (!check_first_symbol(tsh))
		return ;
	dquote = 0;
	squote = 0;
	shield = 0;
	i = -1;
	while (tsh->line[++i])
	{
		if (!set_flags(tsh->line[i], &shield, &dquote, &squote))
			continue ;
		if (!general_check(i, tsh, shield + dquote + squote))
			return ;
		shield = 0;
	}
	if (dquote || squote)
	{
		error_template("turboshell-1.0", "syntax error", "need more quotes");
		tsh->prsr.parse_status = 0;
	}
}

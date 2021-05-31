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

static int	semicolon_check(int i, t_tsh *tsh, int flags)
{
	char	*spec_char;

	spec_char = "|;";
	if (ft_strchr(";", tsh->line[i]) && !flags)
	{
		if (ft_strchr(spec_char, \
		tsh->line[skip_whitespaces(tsh->line, i + 1)]) || !i)
		{
			if (tsh->line[skip_whitespaces(tsh->line, i + 1)] == ';' || !i)
				print_syntax_error(i, tsh);
			else
				print_syntax_error(skip_whitespaces(tsh->line, i + 1), tsh);
			tsh->prsr.parse_status = 0;
			return (0);
		}
	}
	return (1);
}

static int	pipes_check(int i, t_tsh *tsh, int flags)
{
	char	*spec_char;

	spec_char = "|;\n";
	if (ft_strchr("|", tsh->line[i]) && !flags)
	{
		if (ft_strchr(spec_char, tsh->line[skip_whitespaces(tsh->line, i + 1)]))
		{
			if (tsh->line[skip_whitespaces(tsh->line, i + 1)] == ';')
				print_syntax_error(skip_whitespaces(tsh->line, i + 1), tsh);
			else
				print_syntax_error(i, tsh);
			tsh->prsr.parse_status = 0;
			return (0);
		}
	}
	return (1);
}

static int	redirects_check(int i, t_tsh *tsh, int flags)
{
	char	*spec_char;

	spec_char = "|;><";
	if (ft_strchr("><", tsh->line[i]) && !flags)
	{
		if (!tsh->line[skip_whitespaces(tsh->line, i + 1)] || \
		tsh->line[skip_whitespaces(tsh->line, i + 1)] == '\n')
		{
			write(2, "turboshell-1.0: syntax error near unexpected token `newline'\n", \
			61);
			tsh->prsr.parse_status = 0;
			return (0);
		}
		if (tsh->line[i] == '>' && tsh->line[i + 1] == '>')
			++i;
		if (ft_strchr(spec_char, tsh->line[skip_whitespaces(tsh->line, i + 1)]))
		{
			print_syntax_error(skip_whitespaces(tsh->line, i + 1), tsh);
			tsh->prsr.parse_status = 0;
			return (0);
		}
	}
	return (1);
}

void	syntax_checker(t_tsh *tsh)
{
	int	i;
	int	shield;
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	shield = 0;
	i = -1;
	while (tsh->line[++i])
	{
		if (!set_flags(tsh->line[i], &shield, &dquote, &squote))
			continue ;
		if (!semicolon_check(i, tsh, shield + dquote + squote) || \
		!pipes_check(i, tsh, shield + dquote + squote) || \
		!redirects_check(i, tsh, shield + dquote + squote))
			return ;
		shield = 0;
	}
	if (dquote || squote)
	{
		g_exit_status = 2;
		error_template("turboshell-1.0", "syntax error", "need more quotes");
		tsh->prsr.parse_status = 0;
	}
}

#include "minishell.h"

int	add_to_history(t_tsh *tsh)
{
	int		err;
	size_t	len;
	t_dlst	*new;
	char	*tmp;

	len = ft_strlen(tsh->line);
	err = write(tsh->hfd, tsh->line, len);
	tmp = ft_strdup(tsh->line);
	new = ft_dlst_new(tmp);
	if (err == -1 || !new || !tmp)
		return (error_handler("error while add to history"));
	ft_dlstadd_back(&tsh->his, new);
	return (0);
}

int	termcap_processor(char *line, t_tsh *tsh)
{
	if (!ft_strcmp(line, "\033[A"))
		history_up(tsh);
	else if (!ft_strcmp(line, "\033[B"))
		history_down(tsh);
	else if (!ft_strcmp(line, "\177"))
		erase_symbol(tsh);
	return (0);
}

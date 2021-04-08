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

int	termcap_processor(char *buf, t_tsh *tsh)
{
	if (!ft_strcmp(buf, "\033[A"))
		tsh->is_termcap = istory_up(tsh);
	else if (!ft_strcmp(buf, "\033[B"))
		tsh->is_termcap = history_down(tsh);
	else if (!ft_strcmp(buf, "\177"))
		tsh->is_termcap = erase_symbol(tsh);
	return (0);
}

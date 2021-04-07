#include "minishell.h"

static	int	term_clean_up(void)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	return (0);
}

int	history_up(t_tsh *tsh)
{
	term_clean_up();
	if (tsh->his && tsh->his->prev)
	{
		tsh->his_ptr = tsh->his->prev;
		tsh->line = ft_strdup(tsh->his_ptr->prev->content);
	}
	ft_putstr_fd(tsh->line, 1);
	return (0);
}

int	history_down(t_tsh *tsh)
{
	term_clean_up();
	if (tsh->his && tsh->his->next)
	{
		tsh->his_ptr = tsh->his->next;
		tsh->line = ft_strdup(tsh->his_ptr->next->content);
	}
	ft_putstr_fd(tsh->line, 1);
	return (0);
}

int	erase_symbol(t_tsh *tsh)
{
	size_t	len;

	len = ft_strlen(tsh->line);
	if (len > 1)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1 ,ft_putchar);
		tsh->line[len - 2] = '\0';
	}
	if (!ft_strcmp(tsh->line, "\0"))
		tputs(restore_cursor, 1, ft_putchar);
	return (0);
}

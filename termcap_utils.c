#include "minishell.h"

static	int	term_clean_up(void)
{
	tputs(restore_cursor, 1, ft_putint);
	tputs(tigetstr("ed"), 1, ft_putint);
	return (0);
}

int	history_up(t_tsh *tsh)
{
	size_t	len;

	len = ft_strlen(tsh->line);
	term_clean_up();
	if (tsh->his_ptr && tsh->his_ptr->prev)
	{
		tsh->his_ptr = tsh->his_ptr->prev;
		len = ft_strlen(tsh->his_ptr->content);
		ft_freen(tsh->line);
		tsh->line = ft_strdup((char *)tsh->his_ptr->content);
		error_checker(!tsh->line, "memmory doesn't allocated", 0);
	}
	write(1, tsh->line, len);
	return (1);
}

int	history_down(t_tsh *tsh)
{
	size_t	len;

	len = ft_strlen(tsh->line);
	term_clean_up();
	if (tsh->his_ptr && tsh->his_ptr->next)
	{
		tsh->his_ptr = tsh->his_ptr->next;
		len = ft_strlen(tsh->his_ptr->content);
		ft_freen(tsh->line);
		tsh->line = ft_strdup((char *)tsh->his_ptr->content);
		error_checker(!tsh->line, "memmory doesn't allocated", 0);
	}
	write(1, tsh->line, len);
	return (1);
}

int	erase_symbol(t_tsh *tsh)
{
	size_t	len;

	len = ft_strlen(tsh->line);
	if (len > 0)
	{
		tputs(cursor_left, 1, ft_putint);
		tputs(delete_character, 1 ,ft_putint);
		tsh->line[len - 1] = '\0';
	}
	if (!ft_strcmp(tsh->line, "\0"))
		tputs(restore_cursor, 1, ft_putint);
	return (1);
}

#include "minishell.h"

static	int	check_history_file(t_tsh *tsh)
{
	int		check;

	if (!is_file_accessible(tsh->wdir, 0))
		return (0);
	check = open(tsh->wdir, O_RDONLY);
	if (check == -1)
	{
		tsh->hfd = open(tsh->wdir, O_CREAT | O_RDWR | O_APPEND, 0755);
		if (tsh->hfd == -1)
			error_handler("history file doesn't open\n", 0);
	}
	close(check);
	return (1);
}

int	file_to_history(t_tsh *tsh)
{
	int		fd;
	char	*line;

	if (!is_file_accessible(tsh->wdir, 3))
		return (0);
	fd = open(tsh->wdir, O_RDONLY);
	if (fd == -1)
		return (error_handler("tsh_history file fd = -1", 0));
	while (get_next_line(fd, &line))
	{
		if (ft_strcmp(line, "\0"))
			ft_dlstadd_back(&tsh->his, ft_dlst_new(line));
		else
			free(line);
	}
	if (ft_strcmp(line, "\0"))
		ft_dlstadd_back(&tsh->his, ft_dlst_new(line));
	else
		free(line);
	close(fd);
	return (0);
}

int	add_to_history(t_tsh *tsh)
{
	size_t	len;
	t_dlst	*dlst;

	len = ft_strlen(tsh->line);
	dlst = ft_dlstlast(tsh->his);
	ft_freen((void **)&dlst->content);
	dlst->content = ft_strdup(tsh->line);
	error_checker(!dlst->content, "memmory doesn't allocated", 1);
	((char *)(dlst->content))[len - 1] = '\0';
	ft_dlstadd_back(&tsh->his, ft_dlst_new(ft_strdup("\0")));
	return (0);
}

int	history_editor(t_tsh *tsh)
{
	size_t	len;

	len = ft_strlen(tsh->line);
	ft_freen((void **)&tsh->his_ptr->content);
	tsh->his_ptr->content = ft_strdup(tsh->line);
	error_checker(!tsh->his_ptr->content, "memmory doesn't allocated", 1);
	((char *)(tsh->his_ptr->content))[len] = '\0';
	if (((char *)(tsh->his_ptr->content))[len - 1] == '\n')
		((char *)(tsh->his_ptr->content))[len - 1] = '\0';
	return (0);
}

void	history_to_file(t_tsh *tsh)
{
	t_dlst	*ptr;

	if (tsh->curr_his)
	{
		ptr = tsh->curr_his;
		if (!check_history_file(tsh))
			return ;
		while (ptr->next)
		{
			ft_putendl_fd(ptr->content, tsh->hfd);
			ptr = ptr->next;
		}
	}
}

#include "minishell.h"

int	file_to_history(t_tsh *tsh)
{
	int		fd;
	char	*line;

	fd = open("tsh_history", O_RDONLY);
	if (fd == -1)
		return(error_handler("tsh_history file fd = -1", 0));
	while(get_next_line(fd, &line))
		if (ft_strcmp(line, "\0"))
			ft_dlstadd_back(&tsh->his, ft_dlst_new(line));
		else
			free(line);
	if (ft_strcmp(line, "\0"))
		ft_dlstadd_back(&tsh->his, ft_dlst_new(line));
	else
		free(line);
	return (0);
}

int	add_to_history(t_tsh *tsh)
{
	int		err;
	size_t	len;
	t_dlst	*new;
	char	*tmp;

	len = ft_strlen(tsh->line) - 1;
	err = write(tsh->hfd, tsh->line, len + 1);
	tsh->his->content = (char *)malloc(len);
	tsh->tmp = (char *)malloc(1);
	if (!tsh->his->content || !tsh->tmp)
		return(error_handler("memmory doesn't allocated", 1));
	ft_memcpy(tsh->his->content, tsh->line, len);
	if (err == -1)
		return (error_handler("error while add to history", 0));
	ft_dlstadd_back(&tsh->his, ft_dlst_new(tsh->tmp));
	return (0);
}

int	history_editor(t_tsh *tsh)
{
	size_t	len;

	len = ft_strlen(tsh->line);
	free(tsh->his_ptr->content);
	tsh->his_ptr->content = (char *)malloc(len);
	error_checker(!tsh->his->content, "memmory doesn't allocated", 1);
	ft_memcpy(tsh->his_ptr->content, tsh->line, len);
	return (0);
}

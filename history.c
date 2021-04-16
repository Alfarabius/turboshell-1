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
	char	*new;

	len = ft_strlen(tsh->line);
	err = write(tsh->hfd, tsh->line, len);
	new = ft_strdup(tsh->line);
	error_checker(!new, "memmory doesn't allocated", 1);
	new[len - 1] = '\0';
	ft_dlstadd_back(&tsh->his, ft_dlst_new(new));
	if (err == -1)
		return (error_handler("error while add to history", 0));
	return (0);
}

int	history_editor(t_tsh *tsh)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(tsh->line);
	ft_freen(tsh->his_ptr->content);
	tsh->his_ptr->content = ft_strdup(tsh->line);
	error_checker(!tsh->his_ptr->content, "memmory doesn't allocated", 1);
	((char *)(tsh->his_ptr->content))[len - 1] = '\0';
	return (0);
}

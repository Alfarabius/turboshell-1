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
	if (ft_strcmp(line, "\0"))
		ft_dlstadd_back(&tsh->his, ft_dlst_new(line));
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
	tmp = (char *)malloc(len);
	if (!tmp)
		return(error_handler("memmory doesn't allocated", 1));
	ft_memcpy(tmp, tsh->line, len);
	new = ft_dlst_new(tmp);
	if (err == -1 || !new)
		return (error_handler("error while add to history", 0));
	ft_dlstadd_back(&tsh->his, new);
	return (0);
}

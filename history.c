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

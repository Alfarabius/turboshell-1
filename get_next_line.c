#include "minishell.h"

static	int	ft_error_handler(char *mem)
{
	free(mem);
	return (-1);
}

static	char	is_nonl(char *str)
{
	if (!str)
		return (1);
	while (*str)
		if (*(str++) == '\n')
			return (0);
	return (1);
}

static	int	create_reminder(char **reminder, t_gnl *gnl)
{
	while (is_nonl(*reminder) && gnl->bwr)
	{
		gnl->bwr = read(gnl->fd, gnl->buf, 1000);
		if (gnl->bwr == -1)
			return (ft_error_handler(gnl->buf));
		gnl->buf[gnl->bwr] = '\0';
		*reminder = ft_strjoin_gnl(*reminder, gnl->buf);
		if (!*reminder)
			return (-1);
	}
	free(gnl->buf);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	t_gnl		gnl;
	static char	*reminder = NULL;

	if (!line || fd < 0)
		return (-1);
	gnl.buf = (char *)malloc(1001);
	if (!gnl.buf)
		return (-1);
	gnl.bwr = 1;
	gnl.fd = fd;
	if (create_reminder(&reminder, &gnl) == -1)
		return (-1);
	*line = ft_nextline(reminder);
	if (!*line)
		return (ft_error_handler(reminder));
	reminder = ft_newreminder(reminder, (char *)&gnl.bwr);
	if (reminder == (char *)&gnl.bwr)
		return (-1);
	if (gnl.bwr == 0)
		return (0);
	return (1);
}

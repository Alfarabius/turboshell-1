#include "minishell.h"

char	*get_dir_for_history(t_tsh *tsh)
{
	char *dir;
	char *tmp;
	char *ptr;
	char *value;

	value = get_env_value(*tsh, "_");
	if (value)
	{
		tmp = ft_strdup(value);
		error_checker(!tmp, "memmory doesn't allocated", 1);
		ptr = ft_strrchr(tmp, '.');
		*ptr = '\0';
		dir = ft_strjoin(tmp, "tsh_history");
		free(tmp);
	}
	else
	{
		dir = ft_strdup("./tsh_history");
		error_checker(!dir, "memmory doesn't allocated", 1);
	}
	return (dir);
}

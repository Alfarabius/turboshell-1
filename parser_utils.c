#include "parser.h"

void	add_line(char ***arr, char *line, t_prsr *prsr)
{
	int		len;
	char	**result_arr;

	len = 0;
	while ((*arr)[len] != NULL)
		len++;
	result_arr = (char **)malloc(sizeof(char *) * (len + 2));
	error_checker(!result_arr, "memmory doesn't allocated", 1);
	result_arr[len + 1] = NULL;
	result_arr[len] = ft_strdup(line);
	error_checker(!result_arr[len], "memmory doesn't allocated", 1);
	while (--len >= 0)
		result_arr[len] = (*arr)[len];
	free(*arr);
	*arr = result_arr;
	prsr->current_arg++;
}

void	add_redrct(t_redrct ***arr, t_redrct *redrct)
{
	int			len;
	t_redrct	**result_arr;

	len = 0;
	while ((*arr)[len] != NULL)
		len++;
	result_arr = (t_redrct **)malloc(sizeof(t_redrct *) * (len + 2));
	error_checker(!result_arr, "memmory doesn't allocated", 1);
	result_arr[len + 1] = NULL;
	result_arr[len] = (t_redrct *)malloc(sizeof(t_redrct));
	error_checker(!result_arr[len], "memmory doesn't allocated", 1);
	result_arr[len]->arg_num = redrct->arg_num;
	result_arr[len]->fd = redrct->fd;
	result_arr[len]->file_path = redrct->file_path;
	result_arr[len]->type = redrct->type;
	while (--len >= 0)
		result_arr[len] = (*arr)[len];
	free(*arr);
	*arr = result_arr;
}

int	is_whitespace(char c)
{
	if (c == 9 || c == 32)
		return (1);
	return (0);
}

int	skip_whitespaces(char *str, int i)
{
	while (str[i] && is_whitespace(str[i]))
		i++;
	return (i);
}

char	*ft_realloc(char *str, int num, int c)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(str);
	len += num + 1;
	res = (char *)malloc(len);
	error_checker(!res, "memmory doesn't allocated", 1);
	res[len - 1] = '\0';
	i = -1;
	while (str[++i])
		res[i] = str[i];
	while (i < len - 1)
	{
		res[i] = c;
		i++;
	}
	ft_freen((void **)&str);
	return (res);
}

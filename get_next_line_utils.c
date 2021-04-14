#include "minishell.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*joined_string;
	size_t	length;
	size_t	s1_length;

	s1_length = 0;
	if (s1)
		s1_length = ft_strlen(s1);
	length = s1_length + ft_strlen(s2);
	if (!(joined_string = (char *)malloc(length + 1)))
	{
		if (s1)
			free(s1);
		free(s2);
		return (NULL);
	}
	if (s1)
		ft_memcpy(joined_string, s1, s1_length);
	ft_memcpy((joined_string + s1_length), s2, (length - s1_length));
	joined_string[length] = '\0';
	if (s1)
		free(s1);
	return (joined_string);
}

char	*ft_newreminder(char *rem, char *err)
{
	char	*new_rem_begin;
	char	*new_reminder;
	size_t	new_rem_size;

	new_rem_begin = rem;
	while (*new_rem_begin != '\0' && *new_rem_begin != '\n')
		new_rem_begin++;
	if (!*(new_rem_begin))
	{
		free(rem);
		return (NULL);
	}
	new_rem_begin++;
	new_rem_size = ft_strlen(new_rem_begin);
	new_reminder = (char *)malloc(new_rem_size + 1);
	if (!new_reminder)
	{
		free(rem);
		return (err);
	}
	ft_memcpy(new_reminder, new_rem_begin, new_rem_size);
	new_reminder[new_rem_size] = '\0';
	free(rem);
	return (new_reminder);
}

char	*ft_nextline(char *rem)
{
	char	*next_line;
	size_t	size;

	size = 0;
	while (rem[size] != '\n' && rem[size] != '\0')
		size++;
	next_line = (char *)malloc(size + 1);
	if (!next_line)
		return (NULL);
	ft_memcpy(next_line, rem, size);
	next_line[size] = '\0';
	return (next_line);
}

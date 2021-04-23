#include "libft.h"

static	size_t	ft_amochr(char const *s, char c)
{
	size_t	amount;

	amount = 0;
	while (*s != '\0')
	{
		if ((*s == c && *(s + 1) != c && *(s + 1) != '\0')
			|| (*s != c && *(s + 1) == '\0'))
			amount++;
		s++;
	}
	return (amount);
}

static	char	**ft_sfreearr(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	size_t	last_pos;
	size_t	i;
	size_t	j;
	char	**arr_str;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	last_pos = 0;
	arr_str = (char **)malloc(sizeof(char *) * (ft_amochr(s, c) + 1));
	if (arr_str == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			last_pos = i + 1;
		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			if (!(arr_str[j++] = ft_substr(s, last_pos, (i - last_pos + 1))))
				return (ft_sfreearr(arr_str));
		i++;
	}
	arr_str[j] = NULL;
	return (arr_str);
}

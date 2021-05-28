#include "minishell.h"

int	is_separ_exist(char *env_elem)
{
	while (*env_elem && *env_elem != '=')
		env_elem++;
	if (*env_elem == '=')
		return (1);
	return (0);
}

size_t	keylen(char *env_elem)
{
	int	len;

	len = 0;
	while (env_elem[len] != '=' && env_elem[len])
		len++;
	return (len);
}

int	elem_to_lst(char *env_elem, t_list **lst)
{
	t_dict	*content;
	size_t	len;

	len = keylen(env_elem);
	content = (t_dict *)malloc(sizeof(t_dict));
	if (!content)
		return (error_handler("memmory doesn't allocated", 1));
	content->is_separ = is_separ_exist(env_elem);
	content->is_set = 0;
	if (content->is_separ)
		content->is_set = 1;
	content->key = ft_substr(env_elem, 0, len);
	content->value = ft_substr(env_elem, len + 1, ft_strlen(env_elem));
	if (!content->key || !content->value)
		return (error_handler("memmory doesn't allocated", 1));
	ft_lstadd_back(lst, ft_lstnew(content));
	return (0);
}

int	env_to_lst(t_list **lst, char **env)
{
	while (*env)
	{
		elem_to_lst(*env, lst);
		env++;
	}
	return (0);
}

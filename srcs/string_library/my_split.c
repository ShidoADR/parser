#include "../../headers/minishell.h"

static int	get_index(char const *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (my_isspace (s[i]) == FALSE)
		{
			if (my_isspace (s[i + 1]) == TRUE || s[i + 1] == '\0')
				count++;
		}
		i++;
	}
	return (count);
}

static char	**free_result(char **result, int index)
{
	while (index--)
		free (result[index]);
	free (result);
	return (0);
}

static char	**get_chain(char const *s, char **result)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && my_isspace (s[i]) == TRUE)
			i++;
		if (s[i])
		{
			len = 0;
			while (s[i + len] && my_isspace (s[i + len]) == FALSE)
				len++;
			result[j] = my_substr(s, i, len);
			if (!result[j])
				return (free_result(result, j));
			j++;
			i += len;
		}
	}
	return (result);
}

char	**my_split(char const *s)
{
	char	**result;
	size_t	len;

	len = get_index (s);
	result = malloc (sizeof(char *) * (len + 1));
	if (!(result) || !(s))
		return (0);
	result[len] = NULL;
	return (get_chain (s, result));
}

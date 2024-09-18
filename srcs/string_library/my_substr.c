#include "../../headers/minishell.h"

char	*my_substr(const char *s, int start, int len)
{
	char			*result;
	unsigned int	i;

	if (start >= my_strlen(s) || my_strlen(s) == 0)
	{
		result = malloc(1);
		if (!result)
			return (0);
		result[0] = '\0';
		return (result);
	}
	else if (len > my_strlen(s) - start)
		result = malloc((sizeof(char) * (my_strlen(s) - start)) + 1);
	else
		result = malloc((sizeof(char) * len) + 1);
	if (!result)
		return (0);
	i = 0;
	while (len-- && s[start])
	{
		result[i++] = s[start];
		start++;
	}
	result[i] = '\0';
	return (result);
}

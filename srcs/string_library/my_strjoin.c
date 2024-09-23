#include "../../headers/minishell.h"

char	*my_strjoin(const char *s1, const char *s2)
{
	char	*result;
	int		length;
	int		i;
	int		j;

	length = my_strlen (s1) + my_strlen (s2) + 1;
	result = (char *)malloc (sizeof (char) * length);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

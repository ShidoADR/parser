#include "../../headers/minishell.h"

char	*my_strchr(const char *s, int c)
{
	char	*ch;

	ch = (char *)s;
	while (*ch)
	{
		if ((char)c == *ch)
			return (ch);
		ch++;
	}
	if ((char)c == '\0')
		return (ch);
	return (0);
}

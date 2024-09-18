#include "../../headers/minishell.h"

t_bool	my_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (TRUE);
	return (FALSE);
}

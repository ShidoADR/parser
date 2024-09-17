#include "headers/minishell.h"

int	main(void)
{
	char	*str;

	while (1)
	{
		write (1, ">>", 2);
		str = get_next_line (0);
		printf ("%s\n", str);
		free (str);
	}
	return (0);
}

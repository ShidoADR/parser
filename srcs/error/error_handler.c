#include "../../headers/minishell.h"

void	print_error(char *s, int status)
{
	perror (s);
	exit (status >> 8);
}

void	print_custom_error(char *s, int status)
{
	write (2, s, my_strlen (s));
	exit (status >> 8);
}

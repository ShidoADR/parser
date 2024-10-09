#include "headers/minishell.h"

void	print_token(t_token *token)
{
	if (token != NULL)
	{
		while (token != NULL)
		{
			printf ("{type = %d, value = %s}\n", token->type, token->content);
			token = token->next;
		}
	}
}

void	print_prompt(void)
{
	printf (VIBRANT_BLUE BOLD_UNDERLINED "MiniShell" RESET " :");
	printf (DARK_GREEN BOLD " %s " RESET "in ", getenv ("USER"));
	printf (LIGHT_BLUE ITALIC "%s\n", getenv ("PWD"));
	printf(RED"->" RESET "\n");
	write (0, "  \033[A", 5);
}

int	main(void)
{
	char	*str;
	t_token	*token;

	printf (CLEAR);
	while (1)
	{
		print_prompt ();
		str = get_next_line (0);
		if (my_strncmp (str, "exit\n\0", 6) == 0)
		{
			free (str);
			exit (EXIT_SUCCESS);
		}
		token = lexer (str);
		expander (&token);
		print_token (token);
		clear_token(&token);
		free (str);
	}
	return (0);
}

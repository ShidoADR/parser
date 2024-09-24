#include "headers/color.h"
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

int	main(void)
{
	char	*str;
	t_token	*token;

	while (1)
	{
		printf("%s->%s\n", RED, RESET);
		write (0, "  \033[A", 5);
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

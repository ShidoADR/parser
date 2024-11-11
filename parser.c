/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:37 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/11 13:39:08 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	print_args(char **args)
{
	int	i;

	if (args != NULL)
	{
		i = 0;
		while (args[i] != NULL)
		{
			printf ("%s ", args[i]);
			i++;
		}
	}
}

void	print_command(t_command *command)
{
	if (command != NULL)
	{
		while (command != NULL)
		{
			printf ("{command = %s, arg = ", command->command);
			print_args (command->arguments);
			printf ("}\n");
			command = command->next;
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
	t_shell	shell;

	printf (CLEAR);
	shell.status = 0;
	while (1)
	{
		print_prompt ();
		shell.prompt = get_next_line (0);
		if (my_strncmp (shell.prompt, "exit\n\0", 6) == 0)
		{
			free (shell.prompt);
			exit (EXIT_SUCCESS);
		}
		shell.token = lexer (shell.prompt, &shell);
		if (is_valid_token (shell.token) == 0)
		{
			expander (&shell.token);
			shell.command = parser (&shell.token);
			printf ("------redir------\n");
			print_token (shell.command.redir);
			printf ("--------command--------\n");
			print_command(shell.command.command);
			clear_command(&shell.command.command);
			clear_token (&shell.command.redir);
			shell.status = 0;
		}
		else
			shell.status = 2;
		printf ("---------token---------\n");
		print_token (shell.token);
		clear_token(&shell.token);
		free (shell.prompt);
		printf ("status = %d\n", shell.status);
	}
	return (0);
}

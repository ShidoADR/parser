/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:37 by hariandr          #+#    #+#             */
/*   Updated: 2024/10/16 14:30:57 by hariandr         ###   ########.fr       */
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

void	print_prompt(void)
{
	printf (VIBRANT_BLUE BOLD_UNDERLINED "MiniShell" RESET " :");
	printf (DARK_GREEN BOLD " %s " RESET "in ", getenv ("USER"));
	printf (LIGHT_BLUE ITALIC "%s\n", getenv ("PWD"));
	printf(RED"->" RESET "\n");
	write (0, "  \033[A", 5);
}

t_command_table	init_command(void)
{
	t_command_table	command;

	command.command = NULL;
	command.here_doc = NULL;
	command.input = NULL;
	command.output = NULL;
	return (command);
}

t_bool	check_input(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == REDIR_IN || token->type == HEREDOC)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

t_bool	check_output(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == REDIR_OUT || token->type == APPEND)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

void	add_redir(t_token **token, t_command_table *command)
{
	t_token	*prev;
	t_token	*next;

	prev = (*token)->prev;
	next = (*token)->next;
	free ((*token)->content);
	free (*token);
	command->input = next->content;
	if (next->next != NULL)
	{
		next->next->prev = prev;
		if (prev != NULL)
			prev->next = next->next;
		else
			(*token) = next->next;
		free (next);
	}
}

t_bool	handle_input(t_token **token, t_command_table *command)
{
	t_token	*var;

	var = *token;
	while (var != NULL)
	{
		if (var->type == REDIR_IN && var->next != NULL)
		{
			if (var->next->type != WORD)
				return (FALSE);
			add_redir (&var, command);
		}
		else if (var->type == REDIR_IN)
			return (FALSE);
		else
			var = var->next;
	}
	return (TRUE);
}

t_bool	handle_output(t_token **token, t_command_table *command)
{
	t_token	*var;

	var = *token;
	while (var != NULL)
	{
		if (var->type == REDIR_OUT && var->next != NULL)
		{
			if (var->next->type != WORD)
				return (FALSE);
			add_redir (&var, command);
		}
		else if (var->type == REDIR_OUT)
			return (FALSE);
		else
			var = var->next;
	}
	return (TRUE);
}

t_bool	handle_redirection(t_token **token, t_command_table *command)
{
	if (check_input (*token) == TRUE)
	{
		if (handle_input (token, command) == FALSE)
			return (FALSE);
	}
	if (check_output (*token) == TRUE)
	{
		if (handle_output(token, command) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

t_command_table	parser(t_token **token)
{
	t_command_table	command;

	command = init_command ();
	handle_redirection (token, &command);
	return (command);
}

int	main(void)
{
	char			*str;
	t_token			*token;
	t_command_table	command;

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
		command = parser (&token);
		printf ("[redir_in = %s redir_out = %s]\n", command.input,
			command.output);
		clear_token(&token);
		free (str);
	}
	return (0);
}

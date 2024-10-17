/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:22:04 by hariandr          #+#    #+#             */
/*   Updated: 2024/10/17 14:38:00 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command_table	init_command(void)
{
	t_command_table	command;

	command.command = NULL;
	command.here_doc = NULL;
	command.input = NULL;
	command.output = NULL;
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

	if (command->input != NULL)
	{
		free (command->input);
		command->input = NULL;
	}
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

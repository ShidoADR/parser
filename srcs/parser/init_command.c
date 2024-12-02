/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:21:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/25 13:40:50 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	command_size(t_command *command)
{
	if (command == NULL)
		return (0);
	if (command->next != NULL)
		return (command_size (command->next) + 1);
	return (1);
}

t_command	*new_command(char *cmd, char **arg, t_token *redir)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->redir = redir;
	command->input = NULL;
	command->output = NULL;
	command->command = cmd;
	command->arguments = arg;
	command->next = NULL;
	command->prev = NULL;
	return (command);
}

void	add_command(t_command **cmd, t_command *new_command)
{
	t_command	*last;

	if (*cmd != NULL)
	{
		last = last_command (cmd);
		last->next = new_command;
		if (new_command != NULL)
			new_command->prev = last;
	}
	else
		*cmd = new_command;
}

void	delete_command(t_command **command)
{
	if (*command != NULL)
	{
		if ((*command)->command != NULL)
			free ((*command)->command);
		(*command)->command = NULL;
		if ((*command)->arguments != NULL)
			free_args((*command)->arguments);
		(*command)->arguments = NULL;
		if ((*command)->redir != NULL)
			clear_token (&(*command)->redir);
		(*command)->redir = NULL;
		free (*command);
		(*command) = NULL;
	}
}

void	clear_command(t_command **command)
{
	if ((*command) != NULL)
	{
		if ((*command)->next != NULL)
			clear_command (&(*command)->next);
		delete_command (command);
	}
}

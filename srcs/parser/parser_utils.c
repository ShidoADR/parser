/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:02:52 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/11 12:44:22 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command_table	init_command(void)
{
	t_command_table	command;

	command.command = NULL;
	command.redir = NULL;
	return (command);
}

void	free_args(char	**args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free (args[i]);
		args[i] = NULL;
		i++;
	}
	free (args);
	args = NULL;
}

t_command	*last_command(t_command **command)
{
	if (*command == NULL)
		return (NULL);
	if ((*command)->next != NULL)
		return (last_command (&(*command)->next));
	return (*command);
}

void	handle_redirection(t_token **token, t_command_table *command)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp != NULL)
	{
		if (check_redir (tmp) == TRUE && tmp->next->type == WORD)
		{
			add_back (&command->redir, get_redir (tmp));
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

int	arg_size(t_token *token)
{
	int	i;

	i = 0;
	while (token != NULL)
	{
		if (token->type != PIPE)
		{
			if (token->type == WORD)
				i++;
			if (check_redir (token) == TRUE)
				token = token->next;
		}
		else
			break ;
		token = token->next;
	}
	return (i);
}

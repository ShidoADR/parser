/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:34:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/11 12:44:31 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_args(int *i, char **args, t_token **token)
{
	if ((*token)->type == WORD)
	{
		args[*i] = my_strdup ((*token)->content);
		*i += 1;
	}
	if (check_redir (*token) == TRUE)
		(*token) = (*token)->next;
}

char	**get_args(t_token **token)
{
	int		i;
	int		size;
	char	**args;

	size = arg_size (*token);
	args = (char **)malloc(sizeof (char *) * (size + 1));
	if (args == NULL)
		return (NULL);
	i = 0;
	while (*token != NULL)
	{
		if ((*token)->type != PIPE)
			add_args (&i, args, token);
		else
			break ;
		(*token) = (*token)->next;
	}
	args[i] = NULL;
	return (args);
}

t_command	*get_command(t_token **token)
{
	char		*cmd;
	char		**args;
	t_command	*command;

	cmd = my_strdup ((*token)->content);
	*token = (*token)->next;
	args = get_args (token);
	command = new_command (cmd, args);
	return (command);
}

t_command	*handle_command(t_token **token)
{
	t_token		*tmp;
	t_command	*command;

	tmp = *token;
	command = NULL;
	while (tmp != NULL)
	{
		if (tmp->type == WORD)
		{
			if (tmp->prev != NULL && check_redir (tmp->prev) == FALSE)
				add_command (&command, get_command(&tmp));
			else if (tmp->prev == NULL)
				add_command (&command, get_command(&tmp));
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
	return (command);
}

t_command_table	parser(t_token **token)
{
	t_command_table	command;

	command = init_command ();
	handle_redirection (token, &command);
	command.command = handle_command (token);
	return (command);
}

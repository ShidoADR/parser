/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:11:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/27 12:19:02 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:34:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/18 15:51:38 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_args(int *i, char **args, t_token **token)
{
	if (check_redir (*token) == TRUE)
		(*token) = (*token)->next;
	else if ((*token)->type == WORD && (*token)->content != NULL)
	{
		if ((*token)->prev != NULL && check_redir ((*token)->prev) == FALSE)
		{
			args[*i] = my_strdup ((*token)->content);
			*i += 1;
		}
		else if ((*token)->prev == NULL)
		{
			args[*i] = my_strdup ((*token)->content);
			*i += 1;
		}
		else
			(*token) = (*token)->next;
	}
}

char	**get_args(t_token **token)
{
	int		i;
	int		size;
	char	**args;

	size = arg_size (*token);
	args = (char **)malloc (sizeof (char *) * (size + 1));
	if (args == NULL)
		return (NULL);
	i = 0;
	while (*token != NULL)
	{
		if ((*token)->type != PIPE)
			add_args (&i, args, token);
		else
			break ;
		if ((*token) != NULL)
			*token = (*token)->next;
	}
	args[i] = NULL;
	if (size == 0)
	{
		free_args (args);
		args = NULL;
	}
	return (args);
}

char	*get_command_content(t_token **token)
{
	char	*command;

	command = NULL;
	while (*token != NULL && command == NULL && (*token)->type != PIPE)
	{
		if ((*token)->type == WORD && (*token)->content != NULL)
		{
			if ((*token)->prev != NULL)
			{
				if (check_redir ((*token)->prev) == FALSE)
					command = my_strdup ((*token)->content);
			}
			else
				command = my_strdup ((*token)->content);
		}
		(*token) = (*token)->next;
	}
	return (command);
}

t_command	*get_command(t_token **token)
{
	char		*cmd;
	t_token		*redir;
	char		**args;
	t_command	*command;

	redir = handle_redirection (token);
	cmd = get_command_content (token);
	args = get_args (token);
	command = new_command (cmd, args, redir);
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
		if (tmp->type != PIPE && tmp->content != NULL)
			add_command (&command, get_command (&tmp));
		if (tmp != NULL)
			tmp = tmp->next;
	}
	return (command);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:52:33 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/04 13:20:32 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_args(char	**args)
{
	int	i;

	i = 0;
	if (args != NULL)
	{
		while (args[i] != NULL)
		{
			free (args[i]);
			args[i] = NULL;
			i++;
		}
		free (args);
		args = NULL;
	}
}

t_command	*last_command(t_command **command)
{
	if (*command == NULL)
		return (NULL);
	if ((*command)->next != NULL)
		return (last_command (&(*command)->next));
	return (*command);
}

t_token	*handle_redirection(t_token **token)
{
	t_token	*tmp;
	t_token	*redir;

	tmp = *token;
	redir = NULL;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (check_redir (tmp) == TRUE && tmp->next != NULL
			&& tmp->next->type == WORD)
		{
			add_back (&redir, get_redir (tmp));
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (redir);
}

int	arg_size(t_token *token)
{
	int	i;

	i = 0;
	while (token != NULL)
	{
		if (token->type != PIPE)
		{
			if (check_redir (token) == TRUE)
				token = token->next;
			else if (token->type == WORD && token->content != NULL)
				i++;
		}
		else
			break ;
		token = token->next;
	}
	return (i);
}

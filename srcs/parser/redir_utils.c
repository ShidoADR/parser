/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:42:07 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/02 10:52:33 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*get_redir(t_token *token)
{
	t_token	*next;
	t_token	*redir;
	char	*content;

	redir = NULL;
	next = token->next;
	content = my_strdup (next->content);
	redir = new_token (token->type, content, token->shell);
	return (redir);
}

t_bool	check_redir(t_token *token)
{
	if (token != NULL)
	{
		if (token->type == REDIR_IN || token->type == HEREDOC)
			return (TRUE);
		if (token->type == REDIR_OUT || token->type == APPEND)
			return (TRUE);
	}
	return (FALSE);
}

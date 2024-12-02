/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:11:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/29 10:48:51 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	check_next_redir(t_token *redir)
{
	if (redir != NULL)
	{
		while (redir != NULL)
		{
			if (redir->type == REDIR_IN)
				return (TRUE);
			if (redir->type == HEREDOC)
				return (TRUE);
			redir = redir->next;
		}
	}
	return (FALSE);
}

int	redir_in(t_shell *shell, t_token **token, t_command **command)
{
	int		redirection;
	t_token	*redir;

	redir = *token;
	if (redir->type == REDIR_IN)
	{
		redirection = open (redir->content, O_RDONLY);
		if (redirection == -1)
		{
			perror ("Minishell");
			shell->status = 1;
			return (1);
		}
		close(redirection);
		(*command)->input = redir;
	}
	return (0);
}

int	redir_out(t_shell *shell, t_token **token, t_command **command)
{
	int		redirection;
	t_token	*redir;

	redir = *token;
	if (redir->type == REDIR_OUT)
	{
		redirection = open (redir->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (redirection == -1)
		{
			perror ("Minishell");
			shell->status = 1;
			return (1);
		}
		close (redirection);
		(*command)->output = redir;
	}
	return (0);
}

int	redir_append(t_shell *shell, t_token **token, t_command **command)
{
	int		redirection;
	t_token	*redir;

	redir = *token;
	if (redir->type == APPEND)
	{
		redirection = open (redir->content, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (redirection == -1)
		{
			perror ("Minishell");
			shell->status = 1;
			return (1);
		}
		close (redirection);
		(*command)->output = redir;
	}
	return (0);
}

t_status	handle_redir(t_shell *shell, t_command *command)
{
	t_token	*redir;

	redir = command->redir;
	if (redir != NULL)
	{
		while (redir != NULL)
		{
			if (redir_in (shell, &redir, &command) == 1)
				return (1);
			if (redir_out (shell, &redir, &command) == 1)
				return (1);
			if (redir_append (shell, &redir, &command) == 1)
				return (1);
			redir = redir->next;
		}
	}
	return (0);
}

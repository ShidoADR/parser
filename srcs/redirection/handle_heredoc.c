/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 07:07:06 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/29 07:23:07 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_heredoc_child(t_token *redir, t_command **command)
{
	int	status;

	close ((*command)->here_doc.here_doc[0]);
	my_signal_heredoc();
	status = cmd_here_doc (redir, command);
	if (status == 1)
	{
		perror ("heredoc");
		clear_shell (redir->shell);
		exit (1);
	}
	clear_shell (redir->shell);
	if (g_sig == 130)
		exit (g_sig);
	exit (status);
}

t_status	excec_heredoc_parent(t_token **token, t_command **command)
{
	t_status	status;
	t_token		*redir;

	redir = *token;
	signal (SIGINT, SIG_IGN);
	waitpid ((*command)->here_doc.pid, &status, 0);
	status = get_exit_status (status);
	signal (SIGINT, handle_signal);
	(*command)->input = redir;
	if (redir->next != NULL && check_next_redir (redir->next) == TRUE)
		close ((*command)->here_doc.here_doc[0]);
	close ((*command)->here_doc.here_doc[1]);
	if (status != 0)
		(*token)->shell->status = status;
	if (status == 130)
	{
		printf ("\n");
		close ((*command)->here_doc.here_doc[0]);
	}
	return (status);
}

int	redir_heredoc(t_shell *shell, t_token **token, t_command **command)
{
	t_token	*redir;

	redir = *token;
	if (redir->type == HEREDOC)
	{
		if (pipe ((*command)->here_doc.here_doc) == -1)
		{
			perror ("pipe");
			shell->status = 1;
			return (1);
		}
		(*command)->here_doc.pid = fork ();
		if ((*command)->here_doc.pid == -1)
		{
			perror ("pipe");
			shell->status = 1;
			return (1);
		}
		if ((*command)->here_doc.pid == 0)
			exec_heredoc_child (redir, command);
		if (excec_heredoc_parent (&redir, command) != 0)
			return (shell->status);
	}
	return (0);
}

t_bool	check_heredoc(t_token **redir)
{
	while ((*redir) != NULL)
	{
		if ((*redir)->type == HEREDOC)
			return (TRUE);
		(*redir) = (*redir)->next;
	}
	return (FALSE);
}

t_status	here_doc(t_command *command, t_shell *shell)
{
	t_token	*redir;

	while (command != NULL)
	{
		redir = command->redir;
		while (check_heredoc (&redir) == TRUE)
		{
			if (redir_heredoc (shell, &redir, &command) == 130)
				return (130);
			redir = redir->next;
		}
		command = command->next;
	}
	return (0);
}

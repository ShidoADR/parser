/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 08:05:09 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/12/04 10:40:17 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_fork(int sig)
{
	if (sig == SIGINT)
		here_is_a_signal (sig, SET);
	close(STDIN_FILENO);
}

void	builtin_redirection(t_command *command)
{
	int		redirection;
	t_token	*output;

	redirect_stdin(command);
	if (command->output != NULL)
	{
		output = command->output;
		if (output->type == APPEND)
			redirection = open(output->content, O_CREAT | O_RDWR | O_APPEND,
					0644);
		else
			redirection = open(output->content, O_CREAT | O_RDWR | O_TRUNC,
					0644);
		dup2(redirection, STDOUT_FILENO);
		close(redirection);
	}
}

t_status	redir_builtins(t_shell *shell)
{
	if (here_doc(shell->command, shell) == 130)
	{
		clear_command(&shell->command);
		return (130);
	}
	if (handle_redir(shell, shell->command) != 0)
	{
		clear_command(&shell->command);
		return (shell->status);
	}
	builtin_redirection(shell->command);
	return (0);
}

int	redir_here_doc(t_token **token, t_command **command)
{
	t_token	*redir;

	redir = *token;
	if (redir->type == HEREDOC)
		(*command)->input = redir;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/22 11:11:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/27 15:01:49 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	redirect_stdin(t_command *command)
{
	int	redirection;

	if (command->input != NULL)
	{
		if (command->input->type == HEREDOC)
		{
			dup2(command->here_doc.here_doc[0], STDIN_FILENO);
			close(command->here_doc.here_doc[0]);
		}
		else
		{
			redirection = open(command->input->content, O_RDONLY);
			dup2(redirection, STDIN_FILENO);
			close(redirection);
		}
	}
}

void	redirect_stdout(t_command *command, int backup[2], int fd[2])
{
	int		redirection;
	t_token	*output;

	output = command->output;
	if (output != NULL)
	{
		if (output->type == APPEND)
			redirection = open(output->content, O_CREAT | O_RDWR | O_APPEND,
					0644);
		else
			redirection = open(output->content, O_CREAT | O_RDWR | O_TRUNC,
					0644);
		dup2(redirection, STDOUT_FILENO);
		close(redirection);
	}
	else if (command->next == NULL)
		dup2(backup[1], STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(backup[1]);
	close(fd[1]);
}

void	exec_child(t_command *command, t_shell *shell, int backup[2],
		int pipe_fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipe_fd[0]);
	close(backup[0]);
	if (handle_redir(shell, command) != 0)
	{
		clear_shell(shell);
		exit(shell->status);
	}
	redirect_stdin(command);
	redirect_stdout(command, backup, pipe_fd);
	if (command->command != NULL)
		cmd(shell, command);
	clear_shell(shell);
	exit(shell->status);
}

void	exec_parent(int pipe_fd[2], t_command *command)
{
	if (command->input != NULL && command->input->type == HEREDOC)
		close(command->here_doc.here_doc[0]);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}

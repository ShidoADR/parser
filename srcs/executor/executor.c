/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:54:16 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/15 13:54:16 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_fd(int *i, int **fd, t_shell *data)
{
  int cmd_size;

  cmd_size = command_size(data->command.command);
	while ((*i) <= cmd_size - 1)
	{
		fd[*i] = malloc(sizeof(int) * 2);
		(*i)++;
	}
}

void	check_fd(int *i, int ***fd, t_shell *data)
{
    int cmd_size;

	(*i) = 0;
    cmd_size = command_size(data->command.command);
	while ((*i) <= cmd_size - 1)
	{
		if (pipe((*fd)[*i]) < 0)
			return ;
		(*i) ++;
	}
}

void close_all_fd(int **fd, t_shell *data)
{
	int cmd_size;
	int i;

    cmd_size = command_size(data->command.command);
	i = 0;
	while (i <= cmd_size - 1)
	{
		if (close(fd[i][0]) < 0)
			perror("");
		if (close(fd[i][1]) < 0)
			perror("");
		i ++;
	}
}

int	get_exit_status(int exit_status)
{
	int	res;

	res = 0;
	if (WIFEXITED (exit_status))
		res = WEXITSTATUS (exit_status);
	else if (WIFSIGNALED (exit_status))
		res = WTERMSIG (exit_status) + 128;
	return (res);
}

int	cmd_pipe(t_shell *shell, t_command **command)
{
	int			pipe_fd[2];
	int			backup[2];
	int			redir[2];
	t_command	*tmp;

	tmp = *command;
	backup[0] = dup (STDIN_FILENO);
	backup[1] = dup (STDOUT_FILENO);
	while (tmp != NULL)
	{
		if (pipe (pipe_fd) == -1)
		{
			perror ("Pipe");
			return (1);
		}
		tmp->pid = fork ();
		if (tmp->pid == -1)
		{
			perror ("fork");
			return (1);
		}
		if (tmp->pid == 0)
		{
			// Child
			signal (SIGINT, SIG_DFL);
			close(pipe_fd[0]);
			close (backup[0]);
			if (tmp->next == NULL && shell->command.output != NULL)
			{
				if (shell->command.output->type == APPEND)
					redir[1] = open (shell->command.output->content, O_CREAT | O_RDWR | O_APPEND, 0777);
				else
					redir[1] = open (shell->command.output->content, O_WRONLY | O_CREAT | O_TRUNC, 0777);
				dup2 (redir[1], STDOUT_FILENO);
				close (redir[1]);
			}
			else if (tmp->next == NULL)
				dup2 (backup[1], STDOUT_FILENO);
			close (backup[1]);
			if (tmp->prev == NULL && shell->command.input != NULL)
			{
				if (shell->command.input->type == HEREDOC)
				{
					dup2 (shell->command.here_doc.here_doc[0], STDIN_FILENO);
					close (shell->command.here_doc.here_doc[0]);
				}
				else
				{
					redir[0] = open (shell->command.input->content, O_RDONLY);
					dup2 (redir[0], STDIN_FILENO);
					close (redir[0]);
				}
			}
			if (tmp->next != NULL)
				dup2 (pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			cmd (shell, tmp);
			clear_shell (shell);
			exit (get_exit_status (shell->status));
		}
		else
		{
			// Parent
			if (tmp->prev != NULL  && shell->command.input != NULL && shell->command.input->type == HEREDOC)
				close (shell->command.here_doc.here_doc[0]);
			close (pipe_fd[1]);
			dup2 (pipe_fd[0], STDIN_FILENO);
			close (pipe_fd[0]);
			tmp = (tmp)->next;
		}
	}
	// Parent
	tmp = *command;
	while (tmp != NULL)
	{
		if (tmp->next != NULL)
		{
			signal (SIGINT, SIG_IGN);
			waitpid (tmp->pid, NULL, 0);
			signal (SIGINT, handle_signal);
		}
		else
		{
			signal (SIGINT, SIG_IGN);
			waitpid (tmp->pid, &shell->status, 0);
			shell->status = get_exit_status (shell->status);
			if (shell->status == 130)
				printf("\n");
			signal (SIGINT, handle_signal);
		}
		tmp = tmp->next;
	}
	dup2 (backup[0], STDIN_FILENO);
	close (backup[0]);
	dup2 (backup[1], STDOUT_FILENO);
	close (backup[1]);
	clear_command (command);
	return (shell->status);
}
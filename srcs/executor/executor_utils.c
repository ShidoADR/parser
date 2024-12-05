/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:35:12 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/05 11:12:23 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_exec(t_command **command, t_shell *shell)
{
	t_command	*tmp;

	tmp = *command;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (tmp != NULL)
	{
		waitpid(tmp->pid, &tmp->status, 0);
		if (tmp->next == NULL)
			shell->status = get_exit_status (tmp->status);
		tmp = tmp->next;
	}
	if (is_signaled (command) && shell->status
		!= 130 && shell->status != 131)
		ft_putendl_fd ("", 1);
}

int	pipe_and_fork(int pipe_fd[2], pid_t *pid)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		return (1);
	}
	return (0);
}

int	get_exit_status(int exit_status)
{
	int	res;

	res = 0;
	if (WIFEXITED (exit_status))
		res = WEXITSTATUS (exit_status);
	else if (WIFSIGNALED (exit_status))
	{
		res = WTERMSIG (exit_status) + 128;
		ft_putendl_fd ("", 1);
	}
	return (res);
}

t_status	init_backup_heredoc(t_command **command, t_shell *data,
		int backup[2])
{
	if (here_doc (*command, data) == 130)
	{
		clear_command(command);
		return (130);
	}
	dup_fd (backup);
	return (0);
}

int	cmd_pipe(t_shell *data, t_command **command)
{
	int			pipe_fd[2];
	int			backup[2];
	t_command	*tmp;

	tmp = *command;
	if (init_backup_heredoc(command, data, backup) == 130)
		return (130);
	while (tmp != NULL)
	{
		if (pipe_and_fork(pipe_fd, &tmp->pid) == 1)
			return (1);
		if (tmp->pid == 0)
			exec_child(tmp, data, backup, pipe_fd);
		else
		{
			exec_parent(pipe_fd, tmp);
			tmp = tmp->next;
		}
	}
	wait_exec(command, data);
	restore_fd(backup);
	clear_command(&data->command);
	return (data->status);
}

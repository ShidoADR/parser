/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:52:33 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/02 12:21:14 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:22:56 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/12/02 08:50:11 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_exec(t_command **command, t_shell *shell)
{
	t_command	*tmp;
	t_status	sig;

	tmp = *command;
	while (tmp != NULL)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (tmp->next != NULL)
		{
			waitpid(tmp->pid, &sig, 0);
			if (handle_sig (sig) == TRUE)
				break ;
		}
		else
		{
			waitpid(tmp->pid, &shell->status, 0);
			shell->status = get_exit_status(shell->status);
		}
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		if ((shell->status == 130) || (shell->status == 131))
			break ;
		tmp = tmp->next;
	}
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
			exec_parent(pipe_fd, *command);
			tmp = tmp->next;
		}
	}
	wait_exec(command, data);
	restore_fd(backup);
	clear_command(&data->command);
	return (data->status);
}

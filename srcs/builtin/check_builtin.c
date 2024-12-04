/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:05:40 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/04 16:19:35 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin(t_command *command)
{
	if ((my_strcmp(command->command, "cd") == 0) || (my_strcmp(command->command,
				"exit") == 0) || (my_strcmp(command->command, "env") == 0)
		|| (my_strcmp(command->command, "export") == 0)
		|| (my_strcmp(command->command, "unset") == 0)
		|| (my_strcmp(command->command, "echo") == 0)
		|| (my_strcmp(command->command, "pwd") == 0))
		return (0);
	return (1);
}

int	cmd(t_shell *data, t_command *command)
{
	char	**args;

	args = command->arguments;
	if ((my_strcmp(command->command, "cd") == 0))
		return (ft_cd(args, data));
	if ((strcmp(command->command, "echo") == 0))
		return (ft_echo(args));
	else if ((strcmp(command->command, "pwd") == 0))
		return (ft_pwd(data));
	else if ((strcmp(command->command, "env") == 0))
		return (ft_env(data));
	else if ((strcmp(command->command, "export") == 0))
		return (ft_export(data, args));
	else if ((strcmp(command->command, "unset") == 0))
		return (ft_unset(data, args));
	else if ((strcmp(command->command, "exit") == 0))
		return (exit_shell(command, data));
	else
		return (cmd_excve(args, data, command));
}

void	dup_fd_builtins(int backup[2], char *command, t_shell *s)
{
	if ((my_strcmp (command, "exit") != 0))
	{
		backup[0] = dup(STDIN_FILENO);
		backup[1] = dup(STDOUT_FILENO);
	}
	else
		s->to_restore = FALSE;
}

void	dup_fd(int backup[2])
{
	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
}

t_status	exec_builtins(t_shell *shell, char *command, char **args)
{
	int	backup[2];

	dup_fd_builtins (backup, command, shell);
	if (redir_builtins(shell) != 0)
	{
		restore_fd_builtins(backup, &shell->to_restore);
		return (shell->status);
	}
	if ((my_strcmp(command, "cd") == 0))
		shell->status = ft_cd(args, shell);
	else if ((my_strcmp(command, "env") == 0))
		shell->status = ft_env(shell);
	else if ((my_strcmp(command, "echo") == 0))
		shell->status = ft_echo(args);
	else if ((my_strcmp(command, "pwd") == 0))
		shell->status = (ft_pwd(shell));
	else if ((my_strcmp(command, "export") == 0))
		shell->status = ft_export(shell, args);
	else if ((my_strcmp(command, "unset") == 0))
		shell->status = ft_unset(shell, args);
	else if ((my_strcmp(command, "exit") == 0))
		shell->status = exit_shell(shell->command, shell);
	clear_command(&shell->command);
	restore_fd_builtins (backup, &shell->to_restore);
	return (shell->status);
}

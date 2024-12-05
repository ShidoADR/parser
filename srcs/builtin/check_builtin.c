/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:05:40 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/05 11:05:35 by hariandr         ###   ########.fr       */
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

void	dup_fd(int backup[2])
{
	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
}

t_status	exec_builtins(t_shell *shell, char *command, char **args)
{
	int	backup[2];

	dup_fd (backup);
	if (redir_builtins (shell) != 0)
	{
		restore_fd (backup);
		return (shell->status);
	}
	if ((my_strcmp(command, "exit") == 0))
		exit_builtins (shell, backup);
	else
	{
		other_builtins (shell, command, args);
		restore_fd (backup);
	}
	clear_command(&shell->command);
	return (shell->status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:04:16 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/05 11:15:02 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_builtins(t_shell *shell, int backup[2])
{
	restore_fd (backup);
	shell->status = exit_shell(shell->command, shell);
}

void	other_builtins(t_shell *shell, char *command, char **args)
{
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
}

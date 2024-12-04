/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:05:40 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/04 16:19:55 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clear_shell(t_shell *shell)
{
	if (shell != NULL)
	{
		if (shell->env != NULL)
			free_args(shell->env);
		shell->env = NULL;
		if (shell->export != NULL)
			free_args(shell->export);
		shell->export = NULL;
		clear_command(&shell->command);
		rl_clear_history ();
	}
}

void	exit_signal(t_shell *shell)
{
	ft_putendl_fd("exit", 0);
	clear_shell(shell);
	exit(shell->status);
}

void	restore_fd_builtins(int backup[2], t_bool *to_restore)
{
	if (*to_restore == TRUE)
	{
		dup2(backup[0], STDIN_FILENO);
		dup2(backup[1], STDOUT_FILENO);
		close_fd (backup);
	}
	else
		*to_restore = TRUE;
}

void	restore_fd(int backup[2])
{
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	close_fd(backup);
}
